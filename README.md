# 3D Chess Engine

A real-time **3D chess visualization engine** developed in **C++** and **OpenGL**.

The project combines computer graphics, object-oriented software architecture, and interactive gameplay to render a fully playable chess game in a 3D environment. It also introduces several probability-based mechanics that create dynamic game variations.

> **Technologies:** C++, OpenGL, GLSL, Modern C++, Dear ImGui

---

## Features

### Graphics

- Real-time 3D rendering using OpenGL
- Imported custom 3D chess models
- Skybox environment
- Dual lighting system
- Efficient mesh instancing by loading each model only once and rendering multiple instances through transformation matrices

### Gameplay

- Interactive chessboard
- Legal move highlighting
- Pawn promotion
- End-game detection

### Camera

- Trackball camera for board exploration

### Random Events

The game extends traditional chess with stochastic gameplay mechanics based on probability distributions.

| Event | Distribution |
|--------|--------------|
| Random board tile colors | Uniform |
| Trapped square | Markov Chain |
| Piece color inversion | Exponential |
| Queen rescue opportunity | Bernoulli |
| Bonus turn | Binomial |
| King blockade | Poisson |
| Crazy pawn movement | Cauchy |
| Variable game timer | Normal |

---

# Architecture

The project follows a modular object-oriented architecture designed to separate rendering, gameplay, and mathematical components.

```
src/
├── main.cpp
├── Model3D/
├── Chessboard/
├── Piece/
├── Helper/
├── Math/
└── Utils/
```

### Model3D

Responsible for:

- loading 3D meshes
- creating OpenGL buffers (VAO/VBO/EBO)
- rendering models
- managing transformation matrices

### Chessboard

- board representation
- interactive mouse input
- game visualization

### Piece

Represents every chess piece and stores:

- movement rules
- piece state
- game-specific properties

### Helper

Implements chess movement validation and utility algorithms.

### Math

Implements the probability distributions used by the custom gameplay events.

### Utils

Shared utilities including the `Position` structure.

---

# Technical Highlights

- Modern C++ object-oriented design
- Memory management using `std::unique_ptr`
- OpenGL rendering pipeline
- Mesh instancing through transformation matrices
- Interactive scene management
- Modular architecture
- Probability-based gameplay systems

---

# Gallery

## 3D Scene

<img width="1907" height="976" alt="Screenshot 2026-07-16 114538" src="https://github.com/user-attachments/assets/18c65c3c-ae42-4353-9c60-00cfaa761338" />

## Imported 3D Models

<img width="884" height="252" alt="Screenshot 2026-07-16 133758" src="https://github.com/user-attachments/assets/bbc150fb-b3d7-4df5-8d2e-509e7f86d08b" />

## Move Highlighting

<img width="646" height="552" alt="Capture d&#39;écran 2025-04-10 205030" src="https://github.com/user-attachments/assets/be6ba806-ecfa-40f1-a050-cf22941b6791" />

## Pawn Promotion

<img width="1027" height="556" alt="Capture d&#39;écran 2025-04-10 204954" src="https://github.com/user-attachments/assets/73d2a15e-f049-4b0a-b3a9-cbba52628b50" />

## Dual Lighting

<img width="1194" height="945" alt="Capture d&#39;écran 2025-04-11 084937" src="https://github.com/user-attachments/assets/6bc8310c-e294-40c0-8b96-3b3cac9bedd5" />
<img width="1186" height="945" alt="Capture d&#39;écran 2025-04-11 085000" src="https://github.com/user-attachments/assets/23a65dbd-a508-489f-a6da-d2830e7b9804" />

## End Game

<img width="748" height="698" alt="Capture d&#39;écran 2025-04-10 205047" src="https://github.com/user-attachments/assets/1610d2d6-3df8-4f08-953a-031bfe23d27d" />

---

# What I Learned

This project strengthened my understanding of:

- OpenGL rendering
- Modern C++ architecture
- Smart pointer ownership (`std::unique_ptr`)
- 3D transformations and scene management
- Efficient rendering through model instancing
- Interactive graphics programming
- Probability distributions applied to gameplay mechanics

---

# Future Improvements

Potential extensions include:

- Physically based rendering (PBR)
- Shadow mapping
- Skeletal animations for pieces
- Particle effects
- Sound effects
- Improved shaders
