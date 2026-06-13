# HW03 - User Interaction

GLFW와 ImGui를 사용하여 사용자의 입력에 따라 3D 객체의 이동, 크기 변환, 회전을 조작하는 프로그램을 구현한 과제입니다. :contentReference[oaicite:0]{index=0}

## 구현 결과

### InterI
![InterI](images/InterI.png)

### InterI1
![InterI1](images/InterI1.png)

## 구현 내용

- GLFW Keyboard Callback을 이용한 사용자 입력 처리
- 객체의 Translation(이동) 구현
- 객체의 Scaling(크기 변환) 구현
- 객체의 Rotation(회전) 구현
- ImGui Slider를 이용한 위치 조작
- ImGui Slider를 이용한 크기 조작
- imGuIZMO.quat를 이용한 마우스 기반 회전 조작
- Model Matrix 실시간 업데이트
- 객체 변환 정보 및 행렬 출력 UI 구현

## 조작 방법

### Keyboard

| Key | Function |
|------|------|
| H | -X 방향 이동 |
| L | +X 방향 이동 |
| J | -Y 방향 이동 |
| K | +Y 방향 이동 |
| - | 축소 |
| + | 확대 |

### GUI

- Translation Slider
- Scaling Slider
- Rotation Gizmo (Quaternion)

## 사용 기술

- C++
- OpenGL
- GLFW
- ImGui
- imGuIZMO.quat
- GLM

## 배운 점

이번 과제를 통해 그래픽스 프로그램에서 사용자 입력을 처리하는 방법과 Model Matrix가 객체의 이동, 회전, 크기 변환에 어떻게 사용되는지 학습했습니다.

특히 ImGui를 활용하여 실시간으로 객체 상태를 제어하는 방법을 익혔으며, Quaternion 기반 회전을 적용하면서 Euler Angle과는 다른 3차원 회전 표현 방식을 경험할 수 있었습니다.

또한 사용자 입력 → 변환 행렬 계산 → 렌더링 결과 반영으로 이어지는 그래픽스 프로그램의 전체 흐름을 이해할 수 있었습니다.
