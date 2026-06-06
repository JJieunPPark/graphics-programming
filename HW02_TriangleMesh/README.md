# HW02 - Triangle Mesh Rendering

OpenGL의 Vertex Buffer Object(VBO)와 Index Buffer Object(IBO)를 이용하여 다양한 3D 모델을 렌더링하는 과제입니다.

## Result

![Cube](images/cube.png)

![Avocado](images/avocado.png)

![Donut](images/donut.png)

## 구현 내용

- Triangle Soup 방식 렌더링
- Vertex List & Triangles 방식 렌더링
- VBO(Vertex Buffer Object) 생성 및 관리
- IBO(Index Buffer Object) 생성 및 관리
- 모델 데이터 업로드 및 GPU 버퍼 구성
- 키보드 입력에 따른 모델 및 렌더링 방식 전환

## 렌더링 모델

### Triangle Soup

- Cube
- Avocado
- Donut

### Vertex List & Triangles

- Cube
- Avocado
- Donut

## 사용 기술

- C++
- OpenGL
- GLFW
- GLEW
- GLM

## 배운 점

이번 과제를 통해 GPU 버퍼 객체의 동작 방식을 이해하고, 동일한 메시를 서로 다른 데이터 표현 방식으로 렌더링하는 방법을 학습했습니다.

특히 Triangle Soup 방식과 Vertex List + Index Buffer 방식을 비교하며 정점 데이터 중복 문제와 인덱스 버퍼를 이용한 메모리 절약 방법을 이해할 수 있었습니다.

또한 OpenGL 렌더링 파이프라인에서 VBO와 IBO가 실제로 어떻게 사용되는지 직접 구현하며 GPU 데이터 관리에 대한 기초를 익혔습니다.
