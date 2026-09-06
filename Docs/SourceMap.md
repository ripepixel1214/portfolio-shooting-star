# 소스 출처

[프로젝트](../README.md) / [전체 코드](CodeIndex.md)

원본 작업 경로는 `D:/Unreal Projects/ShootingStar`, 기준 커밋은 `851a1a5786135ebde66cf98cacb0bd46a15b98fc`입니다. 공개 파일에서 맨 앞 `Source/` 하나를 제외한 경로가 원본의 상대 경로입니다. 기존 링크를 보존하기 위해 `Source/Source/ShootingStar` 구조를 유지했습니다.

기준 커밋은 팀 개발 이력을 가져온 스냅샷입니다. 반입 커밋 작성자를 모든 파일의 구현자로 해석하지 않습니다. 담당 범위는 팀 PR과 확인된 기여를 기준으로 하며 무기, 인벤토리와 전투 복제 전체는 담당 주장에 포함하지 않습니다. GameMode 초기 설계와 안전 영역 판정 기여는 유지하되 현재 공동 모듈 전체의 단독 구현을 뜻하지 않습니다.

후속 수정으로 표시한 파일은 2단계와 5단계에서 원본 작업 트리에 반영한 변경을 포함합니다. 기준 커밋만으로는 그 내용을 복원할 수 없으므로 [파일별 해시](SourceManifest.json)와 이 저장소의 파일 버전을 함께 확인합니다. 추가 회귀 테스트도 후속 작업이며 과거 개발 당시 검증으로 소급하지 않습니다.

MapInstancedMeshActor, ResourceDataAsset과 ResourceType, TeamComponent 및 WeaponData 등은 생성과 경기 흐름을 읽기 위한 공동 의존 코드입니다. 자원 종류별 에셋 분리와 ISM 구현 전체를 개인 성과로 포함하지 않습니다. 에셋, Blueprint, SDK와 무기 및 인벤토리의 전체 실행 의존성은 반입하지 않았으며 독립 빌드용 저장소가 아닙니다.

| 공개 파일 | 버전 구분 |
| --- | --- |
| [Source/ShootingStar/Private/CompetitiveGameMode.cpp](../Source/Source/ShootingStar/Private/CompetitiveGameMode.cpp) | 기준 커밋 + 후속 수정 |
| [Source/ShootingStar/Private/CompetitiveGameState.cpp](../Source/Source/ShootingStar/Private/CompetitiveGameState.cpp) | 기준 커밋 |
| [Source/ShootingStar/Private/CompetitivePlayerCharacter.cpp](../Source/Source/ShootingStar/Private/CompetitivePlayerCharacter.cpp) | 기준 커밋 + 후속 수정 |
| [Source/ShootingStar/Private/CompetitiveSystemComponent.cpp](../Source/Source/ShootingStar/Private/CompetitiveSystemComponent.cpp) | 기준 커밋 + 후속 수정 |
| [Source/ShootingStar/Private/DecorationGenerator.cpp](../Source/Source/ShootingStar/Private/DecorationGenerator.cpp) | 기준 커밋 + 후속 수정 (5단계) |
| [Source/ShootingStar/Private/FenceGenerator.cpp](../Source/Source/ShootingStar/Private/FenceGenerator.cpp) | 기준 커밋 + 후속 수정 (5단계) |
| [Source/ShootingStar/Private/MapGeneratorComponent.cpp](../Source/Source/ShootingStar/Private/MapGeneratorComponent.cpp) | 기준 커밋 + 후속 수정 (5단계) |
| [Source/ShootingStar/Private/MapInstancedMeshActor.cpp](../Source/Source/ShootingStar/Private/MapInstancedMeshActor.cpp) | 기준 커밋 |
| [Source/ShootingStar/Private/MapObjectActor.cpp](../Source/Source/ShootingStar/Private/MapObjectActor.cpp) | 기준 커밋 |
| [Source/ShootingStar/Private/ObstacleGenerator.cpp](../Source/Source/ShootingStar/Private/ObstacleGenerator.cpp) | 기준 커밋 + 후속 수정 (5단계) |
| [Source/ShootingStar/Private/ResourceActor.cpp](../Source/Source/ShootingStar/Private/ResourceActor.cpp) | 기준 커밋 |
| [Source/ShootingStar/Private/ResourceDataAsset.cpp](../Source/Source/ShootingStar/Private/ResourceDataAsset.cpp) | 기준 커밋 |
| [Source/ShootingStar/Private/ResourceGenerator.cpp](../Source/Source/ShootingStar/Private/ResourceGenerator.cpp) | 기준 커밋 + 후속 수정 |
| [Source/ShootingStar/Private/SafeZoneActor.cpp](../Source/Source/ShootingStar/Private/SafeZoneActor.cpp) | 기준 커밋 |
| [Source/ShootingStar/Private/SubObstacleGenerator.cpp](../Source/Source/ShootingStar/Private/SubObstacleGenerator.cpp) | 기준 커밋 + 후속 수정 (5단계) |
| [Source/ShootingStar/Private/SupplyActor.cpp](../Source/Source/ShootingStar/Private/SupplyActor.cpp) | 기준 커밋 |
| [Source/ShootingStar/Private/SupplyIndicatorUI.cpp](../Source/Source/ShootingStar/Private/SupplyIndicatorUI.cpp) | 기준 커밋 |
| [Source/ShootingStar/Private/TeamComponent.cpp](../Source/Source/ShootingStar/Private/TeamComponent.cpp) | 기준 커밋 / 공동 의존 코드 |
| [Source/ShootingStar/Private/Tests/GenerationRegressionTests.cpp](../Source/Source/ShootingStar/Private/Tests/GenerationRegressionTests.cpp) | 기준 커밋 + 후속 수정 (5단계) |
| [Source/ShootingStar/Private/TumbleWeed.cpp](../Source/Source/ShootingStar/Private/TumbleWeed.cpp) | 기준 커밋 |
| [Source/ShootingStar/Public/CompetitiveGameMode.h](../Source/Source/ShootingStar/Public/CompetitiveGameMode.h) | 기준 커밋 |
| [Source/ShootingStar/Public/CompetitiveGameState.h](../Source/Source/ShootingStar/Public/CompetitiveGameState.h) | 기준 커밋 |
| [Source/ShootingStar/Public/CompetitivePlayerCharacter.h](../Source/Source/ShootingStar/Public/CompetitivePlayerCharacter.h) | 기준 커밋 |
| [Source/ShootingStar/Public/CompetitiveSystemComponent.h](../Source/Source/ShootingStar/Public/CompetitiveSystemComponent.h) | 기준 커밋 |
| [Source/ShootingStar/Public/DecorationGenerator.h](../Source/Source/ShootingStar/Public/DecorationGenerator.h) | 기준 커밋 |
| [Source/ShootingStar/Public/FenceData.h](../Source/Source/ShootingStar/Public/FenceData.h) | 기준 커밋 |
| [Source/ShootingStar/Public/FenceGenerator.h](../Source/Source/ShootingStar/Public/FenceGenerator.h) | 기준 커밋 |
| [Source/ShootingStar/Public/IObjectGenerator.h](../Source/Source/ShootingStar/Public/IObjectGenerator.h) | 기준 커밋 |
| [Source/ShootingStar/Public/MapEnum.h](../Source/Source/ShootingStar/Public/MapEnum.h) | 기준 커밋 |
| [Source/ShootingStar/Public/MapGeneratorComponent.h](../Source/Source/ShootingStar/Public/MapGeneratorComponent.h) | 기준 커밋 + 후속 수정 |
| [Source/ShootingStar/Public/MapInstancedMeshActor.h](../Source/Source/ShootingStar/Public/MapInstancedMeshActor.h) | 기준 커밋 |
| [Source/ShootingStar/Public/MapObjectActor.h](../Source/Source/ShootingStar/Public/MapObjectActor.h) | 기준 커밋 |
| [Source/ShootingStar/Public/ObstacleGenerator.h](../Source/Source/ShootingStar/Public/ObstacleGenerator.h) | 기준 커밋 |
| [Source/ShootingStar/Public/ResourceActor.h](../Source/Source/ShootingStar/Public/ResourceActor.h) | 기준 커밋 |
| [Source/ShootingStar/Public/ResourceDataAsset.h](../Source/Source/ShootingStar/Public/ResourceDataAsset.h) | 기준 커밋 |
| [Source/ShootingStar/Public/ResourceGenerator.h](../Source/Source/ShootingStar/Public/ResourceGenerator.h) | 기준 커밋 |
| [Source/ShootingStar/Public/ResourceType.h](../Source/Source/ShootingStar/Public/ResourceType.h) | 기준 커밋 |
| [Source/ShootingStar/Public/SafeZoneActor.h](../Source/Source/ShootingStar/Public/SafeZoneActor.h) | 기준 커밋 |
| [Source/ShootingStar/Public/SubObstacleGenerator.h](../Source/Source/ShootingStar/Public/SubObstacleGenerator.h) | 기준 커밋 |
| [Source/ShootingStar/Public/SupplyActor.h](../Source/Source/ShootingStar/Public/SupplyActor.h) | 기준 커밋 |
| [Source/ShootingStar/Public/SupplyIndicatorUI.h](../Source/Source/ShootingStar/Public/SupplyIndicatorUI.h) | 기준 커밋 |
| [Source/ShootingStar/Public/TeamComponent.h](../Source/Source/ShootingStar/Public/TeamComponent.h) | 기준 커밋 / 공동 의존 코드 |
| [Source/ShootingStar/Public/TumbleWeed.h](../Source/Source/ShootingStar/Public/TumbleWeed.h) | 기준 커밋 |
| [Source/ShootingStar/Public/WeaponData.h](../Source/Source/ShootingStar/Public/WeaponData.h) | 기준 커밋 / 공동 의존 코드 |
| [Source/ShootingStar/ShootingStar.cpp](../Source/Source/ShootingStar/ShootingStar.cpp) | 기준 커밋 / 공동 의존 코드 |
| [Source/ShootingStar/ShootingStar.h](../Source/Source/ShootingStar/ShootingStar.h) | 기준 커밋 / 공동 의존 코드 |
