# ThreeDimensions Documentation

Welcome to the official documentation for **ThreeDimensions**, a professional 3D modeling engine and SDK.

## Table of Contents

1. [Installation](#install)
2. [Quick Start](#start)
3. [User Guide](#guide)
    - [Creating Objects](#create)
    - [Transforming Objects](#transform)
    - [Combining Objects](#combine)
    - [Saving and Exporting](#save)
4. [API Reference](#api)
5. [Examples](#examples)

<a name="install"></a>
## 1. Installation

ThreeDimensions is a hybrid C++/Python library.

### Prerequisites
- Python 3.11+
- C++20 Compiler (Optional, but recommended for performance)
- CMake 3.15+ (Optional)

### Install via PyPi or CMD
```bash
pip install threedimensions
```

### Installing via pip

```bash
pip install .
```

If you do not have a C++ compiler, the library will automatically fallback to a pure Python implementation.

<a name="start"></a>
## 2. Quick Start

Here is a simple example to create a Cube and save it.

```python
import threedimensions as td

# Create a Cube of size 2.0
cube = td.Mesh.create_cube(size=2.0)

# Move it up by 1 unit
cube.translate(0, 1, 0)

# Save to OBJ file
cube.save("my_cube.obj")
```

<a name="guide"></a>
## 3. User Guide

### <a name="create"></a> Creating Objects

You can create various geometric primitives.

**Cube**
```python
# Create a 1x1x1 cube
box = td.Mesh.create_cube(size=1.0)
```

**Sphere**
```python
# Create a sphere with radius 1.0
ball = td.Mesh.create_sphere(radius=1.0, segments=32, rings=16)
```

**Cylinder**
```python
# Create a cylinder (radius=0.5, height=2.0)
pole = td.Mesh.create_cylinder(radius=0.5, height=2.0, segments=16)
```

**Other Primitives**
- `create_cone(radius, height, segments)`
- `create_torus(main_radius, tube_radius, main_segments, tube_segments)`
- `create_plane(size, subdivisions)`

### <a name="transform"></a> Transforming Objects

You can move, rotate, and scale your meshes.

**Translation (Move)**
```python
# Move x=1, y=2, z=0
mesh.translate(1.0, 2.0, 0.0)
```

**Scaling (Resize)**
```python
# Scale x=2 (double width), y=0.5 (half height), z=1 (same depth)
mesh.scale(2.0, 0.5, 1.0)
```

**Rotation**
```python
import math
# Rotate 90 degrees around Y axis
mesh.rotate_y(math.pi / 2)
```

### <a name="combine"></a> Combining Objects

To build complex objects (like furniture), you can join multiple meshes together.

```python
# Create a seat
seat = td.Mesh.create_cube(size=1.0)
seat.scale(1.0, 0.1, 1.0)

# Create a leg
leg = td.Mesh.create_cube(size=1.0)
leg.scale(0.1, 1.0, 0.1)

# Attach leg to seat at specific offset
# This merges the leg geometry INTO the seat mesh
seat.join(leg, offset_x=0.4, offset_y=-0.5, offset_z=0.4)
```

### <a name="save"></a> Saving and Exporting

The library supports `.obj` and `.stl` formats.

```python
# Save as OBJ (Wavefront) - Good for rendering
mesh.save("model.obj")

# Save as STL (Stereolithography) - Good for 3D Printing
mesh.save("model.stl")
```

<a name="api"></a>
## 4. API Reference

### `threedimensions.Mesh`

The core class representing a 3D object.

#### Properties
- `vertex_count`: Number of vertices.
- `face_count`: Number of faces.

#### Methods
- `add_vertex(x, y, z)`: Add a single vertex manually.
- `add_face(indices)`: Add a face manually using vertex indices.
- `translate(x, y, z)`: Move the entire mesh.
- `scale(x, y, z)`: Scale the entire mesh.
- `rotate_x(angle)`: Rotate around X axis (radians).
- `rotate_y(angle)`: Rotate around Y axis (radians).
- `rotate_z(angle)`: Rotate around Z axis (radians).
- `extrude_face(index, distance)`: Extrude a specific face along its normal.
- `join(other_mesh, offset_x, offset_y, offset_z)`: Merge another mesh into this one.
- `save(filepath)`: Auto-detects format from extension and saves file.

<a name="examples"></a>
## 5. Examples

Check the `examples/` directory for full scripts:
- `baseball_bat.py`: Demonstrates extrusion and scaling to model a bat.
- `chair.py`: Demonstrates `join()` to compose a complex object from primitives.
