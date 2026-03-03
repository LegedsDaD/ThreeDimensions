# ThreeDimensions
<img width="1024" height="1024" alt="ChatGPT Image Mar 1, 2026, 09_40_22 AM" src="https://github.com/user-attachments/assets/f07c4899-ef07-43af-b00b-03e90cc3af77" />

<p align="center">

<!-- Animated Typing Banner -->
<img src="https://readme-typing-svg.herokuapp.com?font=Orbitron&size=28&duration=3000&pause=1000&color=8A2BE2&center=true&vCenter=true&width=900&lines=ThreeDimensions+3D+Modeling+Engine;High-Performance+Python+Interface;C%2B%2B+Powered+Core;Professional+3D+Toolkit;Built+for+Creators;pip+install+threedimensions+%F0%9F%9A%80" />

</p>

---


## Send your creations using ThreeDimensions in [Models](https://github.com/LegedsDaD/Models) by filling in the [Form](https://forms.gle/Z8WpocwLCv92MZU17). The best models will be added to the examples of ThreeDimensions. Others will be added to the models groups. See current submissions in [Submissions](https://github.com/LegedsDaD/Models/blob/main/README.md). Do participate !

<h1 align="center">⚡ ThreeDimensions</h1>

<h3 align="center">
A Next-Generation 3D Modeling Engine <br>
Built with Python + C++ Core
</h3>

---

<p align="center">

<img src="https://img.shields.io/github/stars/LegedsDaD/ThreeDimensions?style=for-the-badge&logo=github" />
<img src="https://img.shields.io/github/forks/LegedsDaD/ThreeDimensions?style=for-the-badge&logo=github" />
<img src="https://img.shields.io/github/issues/LegedsDaD/ThreeDimensions?style=for-the-badge&logo=github" />
<img src="https://img.shields.io/github/license/LegedsDaD/ThreeDimensions?style=for-the-badge" />

<br>

<img src="https://img.shields.io/badge/Python-Interface-3776AB?style=for-the-badge&logo=python&logoColor=white" />
<img src="https://img.shields.io/badge/C%2B%2B-High%20Performance%20Core-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" />
<img src="https://img.shields.io/badge/Engine-3D%20Professional-8A2BE2?style=for-the-badge" />

<br>

<img src="https://img.shields.io/github/repo-size/LegedsDaD/ThreeDimensions?style=for-the-badge" />
<img src="https://img.shields.io/github/last-commit/LegedsDaD/ThreeDimensions?style=for-the-badge" />
<img src="https://img.shields.io/github/languages/top/LegedsDaD/ThreeDimensions?style=for-the-badge" />

</p>

---

## 🌠 Vision

ThreeDimensions is designed to deliver **professional-grade 3D modeling tools**
with the performance of C++ and the flexibility of Python —
empowering developers, creators, and engine builders.

---

## ⚙️ Core Philosophy

- 🔷 High Performance Rendering Core (C++)
- 🔷 Pythonic Modeling API
- 🔷 Modular Tool Architecture
- 🔷 Production-Ready Design
- 🔷 Cross-Platform Engine Structure

---

<p align="center">
✨ Engineered for Power • Designed for Precision • Built for the Future ✨
</p>



**Professional 3D Modeling Engine & SDK**

ThreeDimensions is a high-performance, hybrid C++20/Python 3D modeling library designed to provide a complete toolset comparable to Blender's modeling capabilities. It features a modern C++ core for heavy lifting and a flexible Python SDK for scripting and tool development.

## Features

- **Hybrid Architecture**: 
  - **C++20 Core**: High-performance mesh kernel, geometry processing, and math engine.
  - **Python SDK**: Object-oriented API, scene graph, and modifier system.
- **Mesh Engine**: Efficient topology, support for N-gons, and large mesh optimization.
- **Modeling Tools**: 
  - Primitives: Cube, Sphere, Cylinder, Cone, Torus, Plane.
  - Edit Mode: Vertex/Edge/Face operations (Extrude, Bevel, Inset, etc.).
  - Advanced: Booleans, Subdivision Surface, Decimate, Remesh.
- **Non-Destructive Workflow**: Modifier stack system (Subdivision, Mirror, Array, Boolean).
- **Scene System**: Hierarchical scene graph, object instancing, and collections.
- **Export**: OBJ, STL support.

## Project Structure

```
ThreeDimensions/
├── cpp_core/           # C++20 Core Engine
├── python/             # Python SDK
├── examples/           # Usage examples (chair.py, baseball_bat.py)
├── LICENSE
├── Manual.md
├── CMakeLists.txt
├── README.md
├── pyproject.toml
```

## Build Instructions

### Prerequisites

- CMake 3.15+
- C++20 compliant compiler (GCC 10+, Clang 10+, MSVC 2019+)
- Python 3.11+
- pip

### Download From PyPI or CMD or Terminal
```
pip install threedimensions
```

### Building from Source

1. Clone the repository:
   ```bash
   git clone https://github.com/LegendsDaD/ThreeDimensions.git
   cd ThreeDimensions
   ```

2. Install dependencies and build the Python extension:
   ```bash
   pip install .
   ```
   
   If a C++ compiler is not found, the library will fallback to a pure Python implementation automatically.

## Usage

See [manual.md](https://github.com/LegedsDaD/ThreeDimensions/blob/main/Manual.md) for detailed documentation.

```python
import threedimensions as td

# Create a scene
bat = td.Mesh.create_cylinder(radius=0.15, height=1.0)
bat.save("bat.obj")
```

## Authors

- **LegedsDaD** (legendsdad001@gmail.com)

## License

MIT License
