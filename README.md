# Shooting Star

자원을 채굴해 무기를 제작하고 팀원과 협력해 상대 팀을 제압하는 3D 탑다운 전술 슈팅 게임입니다. 절차적으로 생성되는 전장과 좁아지는 안전 영역에서 자원 확보와 교전 시점을 판단하며 전투합니다.

<table align="center" width="100%">
  <tr>
    <th width="360">구분</th>
    <th width="840">내용</th>
  </tr>
  <tr>
    <td>기간</td>
    <td>2025.03~2025.06</td>
  </tr>
  <tr>
    <td>팀</td>
    <td>4명</td>
  </tr>
  <tr>
    <td>환경</td>
    <td>Unreal Engine 5.5, C++</td>
  </tr>
  <tr>
    <td>담당</td>
    <td>맵 생성, 공간 검증, 자원 재배치, 보급, 카메라 가림 처리</td>
  </tr>
  <tr>
    <td>추가 기여</td>
    <td>GameMode 초기 전투 흐름 설계, 안전 영역 판정</td>
  </tr>
</table>

## 주요 기여

- **공간 배치:** 메시 범위와 유형별 여유 공간을 점유 배열에 반영하고 주변 후보를 탐색해 오브젝트 겹침과 이동 공간 침범에 대응했습니다.
- **생성 규칙 분리:** 유형별 Generator가 배치 규칙을 담당하고 공통 위치 검증은 맵 생성 컴포넌트에서 처리하도록 했습니다.
- **전투 흐름 연동:** 초기 GameMode 구조를 설계하고 자원 재배치, 보급과 안전 영역 판정을 경기 진행에 연결했습니다.
- **카메라 가림:** 플레이어와 카메라 사이의 오브젝트를 추적해 반투명 처리와 원래 재질 복구를 구현했습니다.

## 구현 상세와 코드

<table align="center" width="100%">
  <tr>
    <th width="360">기능</th>
    <th width="840">설명</th>
  </tr>
  <tr>
    <td><a href="Docs/SpatialGeneration.md">공간 검증과 맵 생성</a></td>
    <td>점유 배열, 메시 범위, 대체 위치, 유형별 생성과 자원 재배치</td>
  </tr>
  <tr>
    <td><a href="Docs/Gameplay.md">경기 진행과 화면 피드백</a></td>
    <td>보급, 안전 영역, GameMode 기여, 카메라와 피격 효과</td>
  </tr>
  <tr>
    <td><a href="Docs/Verification.md">후속 수정과 검증</a></td>
    <td>보급 탐색 종료, 재질 갱신, null 처리, 자원 반복문, 회귀 테스트</td>
  </tr>
  <tr>
    <td><a href="Docs/CodeIndex.md">전체 코드 목록</a></td>
    <td>구현과 연동에 필요한 파일 탐색</td>
  </tr>
  <tr>
    <td><a href="Docs/SourceMap.md">소스 출처</a></td>
    <td>원본 기준 커밋, 공동 코드와 후속 수정 구분</td>
  </tr>
</table>

## 플레이 영상

### 전체 플레이 데모

<table align="center" width="100%"><tr><td width="1200" align="center">
  <a href="https://www.youtube.com/watch?v=m5du1KtTWZ0">
    <img src="https://img.youtube.com/vi/m5du1KtTWZ0/hqdefault.jpg" alt="Shooting Star 플레이 영상" width="100%">
  </a>
  <br>
  <sub>Shooting Star 게임 플레이 데모</sub>
</td></tr></table>

### 전투 플레이

<table align="center" width="100%"><tr><td width="1200" align="center">

https://github.com/user-attachments/assets/742f9eb4-b533-4154-b291-3433c4f77793

</td></tr></table>

### 카메라 가림 처리

<table align="center" width="100%"><tr><td width="1200" align="center">

https://github.com/user-attachments/assets/37ab7ece-31b8-4225-9d73-cf62d646eea1

</td></tr></table>

### 안전 영역

<table align="center" width="100%"><tr><td width="1200" align="center">

https://github.com/user-attachments/assets/3362463d-bf0f-438d-aa3c-484b2fdbbe27

</td></tr></table>
