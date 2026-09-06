# 경기 진행과 화면 피드백

[프로젝트](../README.md) / [전체 코드](CodeIndex.md)

## 경기 진행과 안전 영역

GameMode 초기 전투 흐름 설계와 안전 영역 판정에 기여했고 생성 기능을 경기 흐름에 연결했습니다. 현재 [CompetitiveGameMode](../Source/Source/ShootingStar/Private/CompetitiveGameMode.cpp)와 [CompetitiveSystemComponent](../Source/Source/ShootingStar/Private/CompetitiveSystemComponent.cpp)는 팀 공동 코드입니다. 팀 구성, 무기, 인벤토리와 전투 복제 전체를 담당 구현으로 포함하지 않습니다.

경기는 고정 3라운드가 아니라 3승 조건으로 종료됩니다. `CompetitiveSystemComponent`가 진행 단계를 관리하고 [SafeZoneActor](../Source/Source/ShootingStar/Public/SafeZoneActor.h)의 반경을 시간 진행에 맞춰 변경합니다. `CompetitiveGameMode`는 캐릭터 위치의 2차원 제곱 거리와 반경의 제곱을 비교해 영역 밖 피해를 처리합니다. 현재 피해 및 스폰 판정은 원점 중심을 전제로 하며 이동한 안전 영역 중심까지 일반화한 구현은 아닙니다.

PR: [생성 기능 통합 #47](https://github.com/floweryclover/shooting-star/pull/47), [생성 컴포넌트 분리 #50](https://github.com/floweryclover/shooting-star/pull/50)

## 보급 요청과 생성 성공의 분리

`CheckAndTriggerSupplyDrop`은 예정 시각에 해당 회차를 처리한 것으로 표시하고 `TryGetSupplySpawnLocation`을 호출합니다. 이 함수가 실패하면 해당 회차를 생략하고 로그를 남깁니다. 매 프레임 같은 보급을 재시도하지 않습니다.

위치 탐색 성공은 `OnSupplyDropped`를 통해 `CompetitiveGameMode.HandleSupplyDrop`으로 전달됩니다. 실제 [SupplyActor](../Source/Source/ShootingStar/Private/SupplyActor.cpp) 생성이 성공했을 때만 Actor 목록과 전체 점유 영역을 등록합니다. 관련 UI 타입은 [SupplyIndicatorUI](../Source/Source/ShootingStar/Public/SupplyIndicatorUI.h)에 수록했습니다.

현재 처리 플래그는 최초 `StartGame`에서 초기화됩니다. 다음 라운드 전환에서 같은 플래그를 재설정하지 않으므로 매 라운드 같은 보급 일정이 반복된다고 설명하지 않습니다. 보급 범위 계산과 실패 정책 변경은 [후속 수정과 검증](Verification.md)을 참고합니다.

PR: [보급 Actor 전환 #129](https://github.com/floweryclover/shooting-star/pull/129)

## 카메라 가림과 재질 복구

[CompetitivePlayerCharacter.CheckObstaclesBetweenCamera](../Source/Source/ShootingStar/Private/CompetitivePlayerCharacter.cpp)는 플레이어와 카메라 사이 Visibility 트레이스에 잡힌 `MapObjectActor`로 현재 집합을 완성합니다. 이전 집합에서 빠진 Actor는 복구하고 새로 들어온 Actor만 반투명으로 변경합니다. 계속 포함된 Actor에는 재질 전환을 다시 요청하지 않습니다.

[MapObjectActor.SetTranslucent](../Source/Source/ShootingStar/Private/MapObjectActor.cpp)에서 실제 재질 적용을 확인할 수 있습니다. 트레이스의 검출 여부와 반투명 표현은 메시 충돌 응답과 재질 설정에도 의존합니다. 기존 README 영상은 기능 소개이며 후속 수정 버전의 회귀 검증 영상은 아닙니다.

PR: [카메라 가림과 충돌 범위 #179](https://github.com/floweryclover/shooting-star/pull/179)

## 피격 효과와 에디터 연동

[ResourceActor.PlayHitParticle](../Source/Source/ShootingStar/Private/ResourceActor.cpp)는 자원 타입에 맞는 효과를 선택하고 기존 파티클 컴포넌트를 제거한 뒤 새 효과를 재생합니다. 자원 피격 효과와 사운드 연결에 기여했으며 자원 종류별 데이터 에셋 분리 및 현재 Actor 전체는 단독 구현으로 설명하지 않습니다.

전투 레벨, BGM과 충돌 설정 작업은 코드 파일만으로 확인할 수 없습니다. Blueprint의 메시와 효과 연결, Visibility 응답 및 레벨 배치 자료가 보완 대상입니다. 에셋 원본은 이 저장소에 포함하지 않습니다.

PR: [피격 효과와 펜스 보완 #160](https://github.com/floweryclover/shooting-star/pull/160), [충돌 설정 #184](https://github.com/floweryclover/shooting-star/pull/184), [BGM과 에셋 #187](https://github.com/floweryclover/shooting-star/pull/187)
