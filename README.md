# Shooting Star

 자원을 채굴해 무기를 제작하고, 팀원과 협력해 상대 팀을 제압하는 3D 탑다운 전술 슈팅 게임입니다. 절차적으로 생성되는 전장과 좁아지는 안전 영역에서 자원 확보와 교전 시점을 판단하며 전투합니다.

<div align="center">

| 구분 | 내용 |
| --- | --- |
| 기간 | 2025.03 ~ 2025.06 |
| 팀 | 4명 |
| 환경 | Unreal Engine 5.5, C++ |
| 주요 담당 | 맵 생성, 공간 검증, 자원 재배치, 보급, 카메라 가림 처리 |
| 추가 기여 | GameMode 중심의 초기 전투 흐름 설계, 안전 영역 초기 구현 |

</div>


## 플레이 영상

### 전체 플레이 데모

<table width="100%"><tr><td width="15%"></td><td width="70%" align="center">
  <a href="https://www.youtube.com/watch?v=m5du1KtTWZ0">
    <img src="https://img.youtube.com/vi/m5du1KtTWZ0/hqdefault.jpg" alt="Shooting Star 플레이 영상" width="2000">
  </a>
  <br>
  <sub>Shooting Star 게임 플레이 데모</sub>
</td><td width="15%"></td></tr></table>

### 전투 플레이

<table width="100%"><tr><td width="15%"></td><td width="70%">

https://github.com/user-attachments/assets/742f9eb4-b533-4154-b291-3433c4f77793

</td><td width="15%"></td></tr></table>


## 핵심 구현

### 1. 충돌 범위와 여유 공간을 반영한 절차적 배치

중심 좌표만 확인하는 방식으로는 크기가 다른 오브젝트의 겹침이나 이동 공간 침범을 충분히 막을 수 없었습니다. 메시의 충돌 범위와 유형별 여유 영역을 좌표 점유 배열에 반영하고, 배치할 수 없는 후보 주변에서 대체 위치를 탐색하도록 했습니다.

후보 위치 검증은 맵 생성 컴포넌트에 모으고, 장애물과 펜스, 자원 등의 생성 규칙은 유형별 Generator로 분리했습니다.

- [MapGeneratorComponent.cpp](Source/Source/ShootingStar/Private/MapGeneratorComponent.cpp)
- [Generator 인터페이스](Source/Source/ShootingStar/Public/IObjectGenerator.h)
- [PR: 생성 구조 분리](https://github.com/floweryclover/shooting-star/pull/39)

### 2. 라운드별 자원 재배치와 공통 공간 검증

라운드가 바뀔 때 자원 Actor와 해당 유형의 점유 상태를 제거하고, 기존 생성 규칙으로 다시 배치하도록 했습니다. 다른 맵 오브젝트를 유지하면서 자원만 갱신하는 흐름입니다.

보급 이벤트도 위치 검증과 Actor 생성 흐름에 연결했습니다. 보급품 후보가 현재 안전 영역과 맵 경계를 벗어나지 않도록 검사했습니다.

- [자원 생성 코드](Source/Source/ShootingStar/Private/ResourceGenerator.cpp)
- [보급 위치 선정](Source/Source/ShootingStar/Private/MapGeneratorComponent.cpp#L440-L475), [보급품 생성](Source/Source/ShootingStar/Private/CompetitiveGameMode.cpp#L348-L368)
- [보급품 Actor](Source/Source/ShootingStar/Private/SupplyActor.cpp)
- [PR: 자원 재배치](https://github.com/floweryclover/shooting-star/pull/158)
- [PR: 보급 이벤트](https://github.com/floweryclover/shooting-star/pull/129)


## 추가 담당 기능

### 카메라 가림 처리

플레이어와 카메라 사이의 오브젝트를 Multi Trace로 추적하고, 현재와 이전 가림 집합을 비교하여 새로 가린 오브젝트는 반투명하게 만들고 시야에서 벗어난 오브젝트는 원래 재질로 복구했습니다.

- [가림 집합 추적](Source/Source/ShootingStar/Private/CompetitivePlayerCharacter.cpp#L1189-L1231)
- [재질 전환](Source/Source/ShootingStar/Private/MapObjectActor.cpp)
- [PR: 카메라 가림 처리](https://github.com/floweryclover/shooting-star/pull/179)

<table width="100%"><tr><td width="15%"></td><td width="70%">

https://github.com/user-attachments/assets/37ab7ece-31b8-4225-9d73-cf62d646eea1

</td><td width="15%"></td></tr></table>

### 전투 흐름과 안전 영역

GameMode가 맵 생성과 플레이어 배치, 경기 페이즈 전환, 안전 영역 갱신, 라운드 정리를 조율하도록 초기 전투 흐름을 설계했습니다. 안전 영역 밖의 플레이어 판정과 주기적인 피해 적용도 서버의 경기 흐름에 연결했습니다.

- [전투 흐름 조율](Source/Source/ShootingStar/Private/CompetitiveGameMode.cpp#L53-L126)
- [경기 상태 관리](Source/Source/ShootingStar/Private/CompetitiveSystemComponent.cpp#L31-L224)
- [안전 영역 Actor](Source/Source/ShootingStar/Private/SafeZoneActor.cpp)

<table width="100%"><tr><td width="15%"></td><td width="70%">

https://github.com/user-attachments/assets/3362463d-bf0f-438d-aa3c-484b2fdbbe27

</td><td width="15%"></td></tr></table>
