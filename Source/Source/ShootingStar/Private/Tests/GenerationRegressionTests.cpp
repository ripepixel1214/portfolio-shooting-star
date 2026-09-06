// Copyright 2025 ShootingStar. All Rights Reserved.
#if WITH_DEV_AUTOMATION_TESTS
#include "Misc/AutomationTest.h"
#include "MapGeneratorComponent.h"
#include "ResourceGenerator.h"
#include "ObstacleGenerator.h"
#include "SubObstacleGenerator.h"
#include "DecorationGenerator.h"
#include "FenceGenerator.h"
#include <limits>
#include "Engine/StaticMesh.h"
#include "PhysicsEngine/BodySetup.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGenerationMeshFallbackTest,
    "ShootingStar.Regression.Generation.MeshFallback",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FGenerationMeshFallbackTest::RunTest(const FString& Parameters)
{
    UMapGeneratorComponent* Map = NewObject<UMapGeneratorComponent>();
    Map->InitializeMapCoordinate(Map->GetMapHalfSize() * 2);
    const FVector Origin = FVector::ZeroVector;
    TestFalse(TEXT("Missing mesh rejects placement"), Map->CheckLocation(Origin, nullptr, EObjectMask::ResourceMask));
    UStaticMesh* Mesh = NewObject<UStaticMesh>();
    TestNull(TEXT("Test mesh has no BodySetup"), Mesh->GetBodySetup());
    TestTrue(TEXT("No BodySetup uses bounds without dereference"), Map->CheckLocation(Origin, Mesh, EObjectMask::ResourceMask));
    Mesh->CreateBodySetup();
    TestTrue(TEXT("Empty collision geometry uses bounds"), Map->CheckLocation(Origin, Mesh, EObjectMask::ResourceMask));
    FKBoxElem Box;
    Box.X = Box.Y = Box.Z = 20.f;
    Mesh->GetBodySetup()->AggGeom.BoxElems.Add(Box);
    Map->SetObjectAtArray(55, 0, EObjectMask::ObstacleMask);
    TestFalse(TEXT("Box half extent plus resource margin detects occupied cell"), Map->CheckLocation(Origin, Mesh, EObjectMask::ResourceMask));
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSupplyMissingOwnerTest,
    "ShootingStar.Regression.Generation.SupplyMissingOwner",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FSupplyMissingOwnerTest::RunTest(const FString& Parameters)
{
    UMapGeneratorComponent* Map = NewObject<UMapGeneratorComponent>();
    FVector Location(1.f, 2.f, 3.f);
    TestFalse(TEXT("Missing game mode rejects supply search"), Map->TryGetSupplySpawnLocation(Location));
    TestTrue(TEXT("Failure does not write a fake location"), Location.Equals(FVector(1.f, 2.f, 3.f)));
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FInvalidResourceDataTest,
    "ShootingStar.Regression.Generation.InvalidResourceData",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FInvalidResourceDataTest::RunTest(const FString& Parameters)
{
    UMapGeneratorComponent* Map = NewObject<UMapGeneratorComponent>();
    Map->InitializeMapCoordinate(Map->GetMapHalfSize() * 2);
    UResourceGenerator* Generator = NewObject<UResourceGenerator>();
    Generator->Initialize(Map);
    Generator->ResourceActorClass = AResourceActor::StaticClass();
    Generator->numResources = 2;
    TestNull(TEXT("Empty data table returns no resource"), Generator->SelectResourceDataAsset());
    Generator->GenerateObjects();
    FResourceSpawnData Entry{};
    Entry.SpawnProbability = 1.f;
    Generator->ResourceSpawnData.Add(Entry);
    Generator->GenerateObjects();
    Generator->ResourceSpawnData[0].ResourceData = NewObject<UResourceDataAsset>();
    Generator->GenerateObjects();
    TestFalse(TEXT("Invalid data cannot spawn an actor"), Generator->SpawnResourceActor(FVector::ZeroVector, nullptr));

    UStaticMesh* ResourceMesh = NewObject<UStaticMesh>();
    Generator->ResourceSpawnData[0].ResourceData->LargeMesh = ResourceMesh;
    TestFalse(TEXT("Missing world fails actor creation"), Generator->SpawnResourceActor(FVector::ZeroVector, Generator->ResourceSpawnData[0].ResourceData));
    Generator->GenerateObjects();
    TestFalse(TEXT("Failed creation leaves no resource occupancy"), Map->HasObjectAtArray(0, 0, EObjectMask::ResourceMask));

    UStaticMesh* BlockingMesh = NewObject<UStaticMesh>();
    BlockingMesh->CreateBodySetup();
    FKBoxElem Block;
    Block.X = Block.Y = Map->GetMapHalfSize() * 2.f;
    Block.Z = 20.f;
    BlockingMesh->GetBodySetup()->AggGeom.BoxElems.Add(Block);
    Map->SetObjectRegion(FVector::ZeroVector, BlockingMesh, EObjectMask::ObstacleMask);
    Generator->GenerateObjects();
    TestFalse(TEXT("Fully occupied map leaves no resource occupancy"), Map->HasObjectAtArray(0, 0, EObjectMask::ResourceMask));
    // 각 호출은 최대 6회 후 종료하고 0/2 생성 로그를 남깁니다.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPointBoundaryTest,
    "ShootingStar.Regression.Generation.PointBoundary",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPointBoundaryTest::RunTest(const FString& Parameters)
{
    UMapGeneratorComponent* Map = NewObject<UMapGeneratorComponent>();
    TestFalse(TEXT("Uninitialized grid rejects access"), Map->CheckLocation(FVector::ZeroVector));
    const int32 Half = Map->GetMapHalfSize();
    Map->InitializeMapCoordinate(Half * 2);
    TestTrue(TEXT("Interior rounds to valid final cell"), Map->CheckLocation(FVector(Half - 0.51, Half - 0.51, 0)));
    TestFalse(TEXT("X rounding must not alias next row"), Map->CheckLocation(FVector(Half - 0.25, 0, 0)));
    TestFalse(TEXT("Y rounding must not exceed storage"), Map->CheckLocation(FVector(0, Half - 0.25, 0)));
    TestFalse(TEXT("Both rounded axes reject upper boundary"), Map->CheckLocation(FVector(Half - 0.25, Half - 0.25, 0)));
    TestTrue(TEXT("Lower boundary is inclusive"), Map->CheckLocation(FVector(-Half, -Half, 0)));
    TestFalse(TEXT("Below lower X rejects before rounding"), Map->CheckLocation(FVector(-Half - 0.1, 0, 0)));
    TestFalse(TEXT("Below lower Y rejects before rounding"), Map->CheckLocation(FVector(0, -Half - 0.1, 0)));
    TestFalse(TEXT("Exact upper X excluded"), Map->CheckLocation(FVector(Half, 0, 0)));
    TestFalse(TEXT("Exact upper Y excluded"), Map->CheckLocation(FVector(0, Half, 0)));
    FVector NonFinite = FVector::ZeroVector;
    NonFinite.X = std::numeric_limits<double>::quiet_NaN();
    TestFalse(TEXT("NaN rejected"), Map->CheckLocation(NonFinite));
    NonFinite.X = 0; NonFinite.Y = std::numeric_limits<double>::infinity();
    TestFalse(TEXT("Infinity rejected"), Map->CheckLocation(NonFinite));
    Map->SetObjectAtArray(Half - 1, Half - 1, EObjectMask::ObstacleMask);
    TestFalse(TEXT("Interior still checks actual occupancy"), Map->CheckLocation(FVector(Half - 0.51, Half - 0.51, 0)));
    Map->InitializeMapCoordinate(2);
    TestFalse(TEXT("Wrong grid dimensions reject access"), Map->CheckLocation(FVector::ZeroVector));
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeneratorAttemptLimitsTest,
    "ShootingStar.Regression.Generation.GeneratorAttemptLimits",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FGeneratorAttemptLimitsTest::RunTest(const FString& Parameters)
{
    UMapGeneratorComponent* Map = NewObject<UMapGeneratorComponent>();
    Map->InitializeMapCoordinate(Map->GetMapHalfSize() * 2);
    UStaticMesh* Mesh = NewObject<UStaticMesh>();
    Mesh->CreateBodySetup();
    FKBoxElem Box; Box.X = Box.Y = 20; Box.Z = 20;
    Mesh->GetBodySetup()->AggGeom.BoxElems.Add(Box);
    UStaticMesh* BlockingMesh = NewObject<UStaticMesh>();
    BlockingMesh->CreateBodySetup();
    FKBoxElem Block; Block.X = Block.Y = Map->GetMapHalfSize() * 2.0f; Block.Z = 20;
    BlockingMesh->GetBodySetup()->AggGeom.BoxElems.Add(Block);
    // SubObstacle blocks all placement while keeping the fence's obstacle candidate list empty.
    Map->SetObjectRegion(FVector::ZeroVector, BlockingMesh, EObjectMask::SubObstacleMask);
    AddExpectedMessagePlain(TEXT("(Obstacle) Placed 0/2 generation units after 6 attempts"), ELogVerbosity::Warning, EAutomationExpectedMessageFlags::Exact, 1);
    AddExpectedMessagePlain(TEXT("(SubObstacle) Placed 0/2 generation units after 6 attempts"), ELogVerbosity::Warning, EAutomationExpectedMessageFlags::Exact, 1);
    AddExpectedMessagePlain(TEXT("(Deco) Placed 0/2 generation units after 6 attempts"), ELogVerbosity::Warning, EAutomationExpectedMessageFlags::Exact, 1);
    AddExpectedMessagePlain(TEXT("(Fence) Placed 0/2 generation units after 4 attempts"), ELogVerbosity::Warning, EAutomationExpectedMessageFlags::Exact, 1);
    AddExpectedMessagePlain(TEXT("(Fence) No obstacles found to generate fence around."), ELogVerbosity::Warning, EAutomationExpectedMessageFlags::Exact, 0);
    UObstacleGenerator* Obstacle = NewObject<UObstacleGenerator>();
    Obstacle->Initialize(Map); Obstacle->numObstacles = 2; Obstacle->obstacleMeshes = {Mesh};
    Obstacle->GenerateObjects();
    USubObstacleGenerator* Sub = NewObject<USubObstacleGenerator>();
    Sub->Initialize(Map); Sub->numSubObstacles = 2; Sub->subObstacleMeshes = {Mesh};
    Sub->GenerateObjects();
    UDecorationGenerator* Deco = NewObject<UDecorationGenerator>();
    Deco->Initialize(Map); Deco->numDecos = 2; Deco->decoMeshes = {Mesh};
    Deco->GenerateObjects();
    UFenceGenerator* Fence = NewObject<UFenceGenerator>();
    Fence->Initialize(Map); Fence->numFences = 2; Fence->fenceMesh = Mesh;
    FMath::RandInit(1729);
    Fence->GenerateObjects();
    TestTrue(TEXT("Blocked cell stays occupied"), Map->HasObjectAtArray(0, 0, EObjectMask::SubObstacleMask));
    return true;
}

#endif
