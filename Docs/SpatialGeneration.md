# 공간 검증과 맵 생성

[프로젝트](../README.md) / [전체 코드](CodeIndex.md)

## 좌표와 점유 범위

[MapGeneratorComponent](../Source/Source/ShootingStar/Private/MapGeneratorComponent.cpp)는 2차원 좌표를 1차원 `TArray<uint8>`로 관리합니다. `GetIndex`는 음수 좌표에 맵 반경을 더한 뒤 행과 열을 배열 위치로 변환합니다. 한 셀에는 [EObjectMask](../Source/Source/ShootingStar/Public/MapEnum.h)의 유형별 비트를 기록합니다.

`CalculateExtent`는 메시의 첫 단순 충돌 Box의 절반 크기를 사용하고, Box가 없으면 메시 Bounds를 사용합니다. 유형별 여유 영역을 더한 뒤 `CheckLocation`에서 영역을 검사하고, 생성 성공 후 `SetObjectRegion`에서 점유 비트를 기록합니다. 펜스는 저장된 90도 방향에 따라 X와 Y 크기를 교환하며 검사 시 통행 여유를 추가합니다.

이는 복합 충돌 형상의 정확한 투영이 아닙니다. 여러 Box, Box 중심 오프셋, 임의 회전과 Actor 스케일 전체를 반영하지 않습니다. 일반 배치 검사는 맵 안쪽으로 잘라낸 범위를 검사하므로 오브젝트 전체가 맵 안에 있다는 보장과도 다릅니다. 보급의 전체 범위 검사는 [후속 수정](Verification.md)에서 별도로 설명합니다.

## 배열 비용과 후보 탐색

기본 `mapHalfSize=2500`이면 배열은 5000×5000, 25,000,000개 셀입니다. 원소 저장 공간은 약 23.8 MiB이며 컨테이너 여유 공간을 제외한 계산값입니다. 한 셀 조회는 직접 인덱싱하지만 영역 검사는 그 영역의 셀 수만큼 순회합니다. `ClearObjectTypeFromMap`은 전체 배열을 순회하므로 시스템 전체를 O(1)이라고 설명하지 않습니다.

`FindNearestValidLocation`은 50 단위 간격의 반경을 늘리며 각 반경의 16개 방향을 검사하고 첫 유효 후보를 반환합니다. 자원 생성에서 탐색 반경 500을 주면 최대 160개 후보를 검사합니다. 연속 공간의 모든 위치를 탐색하지 않으므로 정확한 최근접점이나 배치 성공을 보장하지 않습니다. 실패는 `FVector::ZeroVector`로 반환해 원점과 구분되지 않는 기존 제약이 있습니다.

## 유형별 규칙과 스폰 후보

| 기능 | 코드와 역할 |
| --- | --- |
| 큰 장애물과 주변 장애물 | [ObstacleGenerator](../Source/Source/ShootingStar/Private/ObstacleGenerator.cpp), [SubObstacleGenerator](../Source/Source/ShootingStar/Private/SubObstacleGenerator.cpp)에서 위치 후보와 배치 규칙 처리 |
| 펜스 패턴 | [FenceGenerator](../Source/Source/ShootingStar/Private/FenceGenerator.cpp), [FenceData](../Source/Source/ShootingStar/Public/FenceData.h)에서 사각형, U형과 L형 패턴 및 방향별 위치 구성 |
| 장식 군집 | [DecorationGenerator](../Source/Source/ShootingStar/Private/DecorationGenerator.cpp)에서 군집 중심과 주변 배치 처리 |
| 플레이어 시작 후보 | `InitializeSpawnPoints`에서 사분면별 후보를 생성하고 `IsValidSpawnLocation`에서 기존 후보와 거리 및 점 점유 확인 |
| 렌더링 연결 | [MapInstancedMeshActor](../Source/Source/ShootingStar/Private/MapInstancedMeshActor.cpp)는 생성 위치가 실제 인스턴스로 연결되는 흐름을 확인하는 공동 의존 코드 |

생성기 공통 진입점은 [IObjectGenerator](../Source/Source/ShootingStar/Public/IObjectGenerator.h)입니다. 유형별 규칙과 공통 위치 검사를 분리했지만 생성기 전체의 실패 경로가 동일하게 보장되는 구조는 아닙니다. 플레이어 후보도 각 후보당 최대 100회 시도하며 목표 개수보다 적게 만들어질 수 있습니다.

후속 수정에서는 장애물, 주변 장애물, 장식의 외부 생성 반복문에 목표 수의 3배, 펜스에는 2배의 시도 예산을 적용하고 대체 위치 탐색 실패도 한 회차로 계산하도록 했습니다. 장식의 군집 내부 처리나 펜스 패턴 하나에 포함된 실제 인스턴스 수까지 외부 반복문의 성공 횟수와 같다는 뜻은 아닙니다. 부분 생성 로그도 이러한 생성 단위 기준입니다.

점 위치 검사 `CheckLocation(const FVector&)`는 비유한 좌표와 배열 미초기화 상태를 거절하고, 반올림한 X와 Y가 정수 좌표 범위 안에 있는지 다시 확인합니다. 실수 좌표가 상한 바로 안쪽에 있더라도 반올림 결과가 바깥이면 거절합니다.

PR: [유형별 생성기 분리 #39](https://github.com/floweryclover/shooting-star/pull/39), [펜스 패턴 #52](https://github.com/floweryclover/shooting-star/pull/52), [스폰 후보 #83](https://github.com/floweryclover/shooting-star/pull/83)

## 자원 Actor와 점유 상태의 재생성

[CompetitiveSystemComponent.Update_RoundEnd](../Source/Source/ShootingStar/Private/CompetitiveSystemComponent.cpp)에서 다음 라운드로 전환할 때 `MapGeneratorComponent.RegenerateResources`를 호출합니다. 전체 점유 배열에서 자원 비트만 지운 뒤 [ResourceGenerator.GenerateObjects](../Source/Source/ShootingStar/Private/ResourceGenerator.cpp)가 기존 자원 Actor를 제거하고 다시 생성합니다. 성공한 Actor는 목록에 보관하고 해당 영역을 점유로 등록합니다.

`ClearSpawnedResources`는 이미 파괴된 Actor를 유효성 검사로 건너뛰고 목록을 비웁니다. 채굴에 따른 크기 변경과 제거는 [ResourceActor.UpdateMesh_AfterHarvest](../Source/Source/ShootingStar/Private/ResourceActor.cpp)에서 확인할 수 있습니다. 채굴 때마다 개별 점유 셀을 해제하는 방식은 아니며 자원 비트는 라운드 재생성 시 일괄 초기화합니다.

자원 데이터나 메시가 없고 후보 탐색 또는 생성이 실패해도 후속 수정된 자원 반복문은 목표 개수의 3배 시도 후 반환합니다. 목표 개수 미달은 로그로 남기며 부족한 개수를 반드시 채우지는 않습니다. 보급도 같은 자원 비트를 사용하므로 라운드 경계의 보급 Actor 제거 순서와 함께 읽어야 합니다.

PR: [라운드 자원 재생성 #158](https://github.com/floweryclover/shooting-star/pull/158)
