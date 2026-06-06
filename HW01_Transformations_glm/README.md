# HW01 - Transformation with GLM

GLM(OpenGL Mathematics)을 사용하여 컴퓨터 그래픽스에서 사용되는 벡터, 행렬, 선형변환을 실습한 과제입니다.

## 구현 내용

- `glm::vec3`를 이용한 벡터 생성 및 연산
- 벡터 덧셈, 내적(dot product), 외적(cross product) 계산
- `glm::mat4`를 이용한 4x4 행렬 생성
- 단위행렬(identity matrix) 생성
- 행렬 원소 접근 및 전치행렬(transpose) 계산
- 이동 변환(Translation) 행렬 구현
- 회전 변환(Rotation) 행렬 구현
- 크기 변환(Scaling) 행렬 구현
- 시점 변환(View Transform) 행렬 구현
- 직교 투영(Orthographic Projection) 행렬 구현
- 원근 투영(Perspective Projection) 행렬 구현

## 사용 기술

- C++
- GLM
- Makefile
- Ubuntu Linux

## 배운 점

이번 과제를 통해 OpenGL에서 사용하는 column-major 행렬 구조와 3D 그래픽스에서 변환 행렬이 사용되는 방식을 익혔습니다.  
특히 이동, 회전, 크기 변환뿐 아니라 view/projection matrix가 렌더링 파이프라인에서 어떤 역할을 하는지 실습을 통해 이해했습니다.
