# ThreeDimensions
<img width="1024" height="1024" alt="ChatGPT Image Mar 1, 2026, 09_40_22 AM" src="https://github.com/user-attachments/assets/f07c4899-ef07-43af-b00b-03e90cc3af77" />

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
```

## Build Instructions

### Prerequisites

- CMake 3.15+
- C++20 compliant compiler (GCC 10+, Clang 10+, MSVC 2019+)
- Python 3.11+
- pip

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
