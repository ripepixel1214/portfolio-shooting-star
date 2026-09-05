# Shooting Star

[![Shooting Star 데모 영상](https://img.youtube.com/vi/m5du1KtTWZ0/hqdefault.jpg)](https://www.youtube.com/watch?v=m5du1KtTWZ0)

[데모 영상]

자원을 수집하고 전투를 진행하는 Unreal Engine 기반 3D 멀티플레이 슈팅 게임입니다. 절차적 맵 생성과 공간 점유 판정, 라운드별 자원 갱신, 보급품 배치와 카메라 가림 처리를 담당했습니다.

| 구분 | 내용 |
| --- | --- |
| 기간 | 2025.03 ~ 2025.06 |
| 팀 | 4명 |
| 환경 | Unreal Engine 5.5, C++ |
| 주요 담당 | 맵 생성, 공간 검증, 자원 재배치, 보급, 카메라 가림 처리 |
| 추가 기여 | GameMode 중심의 초기 전투 흐름 설계, 안전 영역 초기 구현 |

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
- [PR: 자원 재배치](https://github.com/floweryclover/shooting-star/pull/158)
- [PR: 보급 이벤트](https://github.com/floweryclover/shooting-star/pull/129)

## 추가 담당 기능

플레이어와 카메라 사이의 오브젝트를 Multi Trace로 추적하고, 현재와 이전 가림 집합을 비교하여 반투명 처리와 원래 재질 복구를 연결했습니다. [PR: 카메라 가림 처리](https://github.com/floweryclover/shooting-star/pull/179)

GameMode 중심 전투 흐름을 설계하고, 안전 영역의 초기 구조를 구현했습니다.
