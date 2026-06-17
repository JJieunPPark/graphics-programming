
# Phong Reflection Model

OpenGL을 이용하여 **Per-Pixel Phong Reflection Model**을 구현한 프로젝트입니다.

## Overview

이번 과제에서는 기존 **Per-Vertex Lighting**을 **Per-Pixel Lighting**으로 변경하여 보다 자연스러운 조명 효과를 구현했습니다.

또한 모델별로 **Smooth Shading**과 **Flat Shading**을 선택할 수 있도록 구현했습니다. :contentReference[oaicite:0]{index=0}

## Features

- Per-Pixel Phong Lighting
- Ambient / Diffuse / Specular Reflection
- Smooth Shading
- Flat Shading
- Multiple Mesh / Model Rendering
- ImGui를 이용한 실시간 조명 및 렌더링 옵션 변경
  - Light Direction
  - Light Color
  - Background Color
  - Shading Mode

## Implementation

### Shader

- Vertex Shader
  - Position 및 Normal 전달
  - Fragment Shader에서 사용할 데이터 전달

- Fragment Shader
  - Ambient Lighting
  - Diffuse Lighting (Lambert)
  - Specular Lighting (Phong)
  - 최종 색상 계산

### Rendering

- Model 클래스에서 여러 Mesh 관리
- Material 정보 전달
- Normal Matrix 적용
- Camera Position을 이용한 Specular 계산

## Controls

| Option | Description |
|--------|-------------|
| Smooth | Vertex Normal 기반 부드러운 쉐이딩 |
| Flat | Face Normal 기반 평면 쉐이딩 |
| Light Direction | 광원 방향 변경 |
| Light Color | 광원 색상 변경 |
| Background | 배경색 변경 |

## Result

### Smooth Shading

![Smooth](Images/Smooth.png)

### Flat Shading

![Flat](Images/Flat.png)

## Environment

- C++
- OpenGL
- GLSL 1.20
- GLFW
- GLEW
- ImGui
- Assimp

## References

- LearnOpenGL - Basic Lighting
- LearnOpenGL - Mesh
- LearnOpenGL - Model
- Phong Reflection
