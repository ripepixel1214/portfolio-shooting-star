# 소스 출처

[프로젝트](../README.md) / [전체 코드](CodeIndex.md)

원본 작업 경로는 `D:/Unreal Projects/ShootingStar`, 기준 커밋은 `851a1a5786135ebde66cf98cacb0bd46a15b98fc`입니다. 파일에서 맨 앞 `Source/` 하나를 제외한 경로가 원본의 상대 경로입니다.

팀 공동 코드가 포함되어 있으며 담당 범위는 팀 PR과 확인된 기여를 기준으로 합니다. GameMode는 초기 설계와 안전 영역 판정을 담당했습니다. 무기, 인벤토리와 전투 복제 전체는 담당 범위에 포함하지 않습니다.

후속 수정 파일은 기준 커밋 이후 원본 프로젝트에 적용한 변경입니다. 파일 버전은 [해시 목록](SourceManifest.json)에 기록했으며, 회귀 테스트는 2026년 후속 수정 시 추가했습니다.

MapInstancedMeshActor, ResourceDataAsset, ResourceType, TeamComponent와 WeaponData는 공동 의존 코드입니다. 에셋, Blueprint, SDK와 일부 실행 의존성이 없는 소스 발췌본으로, 단독 빌드는 지원하지 않습니다.

| 파일 | 버전 구분 |
| --- | --- |
| [Source/ShootingStar/Private/CompetitiveGameMode.cpp](../Source/Source/ShootingStar/Private/CompetitiveGameMode.cpp) | 기준 커밋 + 후속 수정 |
| [Source/ShootingStar/Private/CompetitiveGameState.cpp](../Source/Source/ShootingStar/Private/CompetitiveGameState.cpp) | 기준 커밋 |
| [Source/ShootingStar/Private/CompetitivePlayerCharacter.cpp](../Source/Source/ShootingStar/Private/CompetitivePlayerCharacter.cpp) | 기준 커밋 + 후속 수정 |
| [Source/ShootingStar/Private/CompetitiveSystemComponent.cpp](../Source/Source/ShootingStar/Private/CompetitiveSystemComponent.cpp) | 기준 커밋 + 후속 수정 |
| [Source/ShootingStar/Private/DecorationGenerator.cpp](../Source/Source/ShootingStar/Private/DecorationGenerator.cpp) | 기준 커밋 + 후속 수정 |
| [Source/ShootingStar/Private/FenceGenerator.cpp](../Source/Source/ShootingStar/Private/FenceGenerator.cpp) | 기준 커밋 + 후속 수정 |
| [Source/ShootingStar/Private/MapGeneratorComponent.cpp](../Source/Source/ShootingStar/Private/MapGeneratorComponent.cpp) | 기준 커밋 + 후속 수정 |
| [Source/ShootingStar/Private/MapInstancedMeshActor.cpp](../Source/Source/ShootingStar/Private/MapInstancedMeshActor.cpp) | 기준 커밋 |
| [Source/ShootingStar/Private/MapObjectActor.cpp](../Source/Source/ShootingStar/Private/MapObjectActor.cpp) | 기준 커밋 |
| [Source/ShootingStar/Private/ObstacleGenerator.cpp](../Source/Source/ShootingStar/Private/ObstacleGenerator.cpp) | 기준 커밋 + 후속 수정 |
| [Source/ShootingStar/Private/ResourceActor.cpp](../Source/Source/ShootingStar/Private/ResourceActor.cpp) | 기준 커밋 |
| [Source/ShootingStar/Private/ResourceDataAsset.cpp](../Source/Source/ShootingStar/Private/ResourceDataAsset.cpp) | 기준 커밋 |
| [Source/ShootingStar/Private/ResourceGenerator.cpp](../Source/Source/ShootingStar/Private/ResourceGenerator.cpp) | 기준 커밋 + 후속 수정 |
| [Source/ShootingStar/Private/SafeZoneActor.cpp](../Source/Source/ShootingStar/Private/SafeZoneActor.cpp) | 기준 커밋 |
| [Source/ShootingStar/Private/SubObstacleGenerator.cpp](../Source/Source/ShootingStar/Private/SubObstacleGenerator.cpp) | 기준 커밋 + 후속 수정 |
| [Source/ShootingStar/Private/SupplyActor.cpp](../Source/Source/ShootingStar/Private/SupplyActor.cpp) | 기준 커밋 |
| [Source/ShootingStar/Private/SupplyIndicatorUI.cpp](../Source/Source/ShootingStar/Private/SupplyIndicatorUI.cpp) | 기준 커밋 |
| [Source/ShootingStar/Private/TeamComponent.cpp](../Source/Source/ShootingStar/Private/TeamComponent.cpp) | 기준 커밋 / 공동 의존 코드 |
| [Source/ShootingStar/Private/Tests/GenerationRegressionTests.cpp](../Source/Source/ShootingStar/Private/Tests/GenerationRegressionTests.cpp) | 기준 커밋 + 후속 수정 |
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
