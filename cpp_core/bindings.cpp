#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "math/Vector3.h"
#include "mesh/Mesh.h"
#include "geometry/Primitives.h"

namespace py = pybind11;
using namespace ThreeDimensions;

PYBIND11_MODULE(_threedimensions_core, m) {
    m.doc() = "ThreeDimensions Core C++ Module";

    // Math
    py::class_<Math::Vec3>(m, "Vector3")
        .def(py::init<float, float, float>())
        .def_readwrite("x", &Math::Vec3::x)
        .def_readwrite("y", &Math::Vec3::y)
        .def_readwrite("z", &Math::Vec3::z)
        .def("length", &Math::Vec3::length)
        .def("normalize", &Math::Vec3::normalize)
        .def("__add__", &Math::Vec3::operator+)
        .def("__sub__", &Math::Vec3::operator-)
        .def("__mul__", &Math::Vec3::operator*)
        .def("__repr__", [](const Math::Vec3& v) {
            return "<Vector3 (" + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + ")>";
        });

    // Mesh
    py::class_<Core::Vertex>(m, "Vertex")
        .def_readwrite("position", &Core::Vertex::position)
        .def_readwrite("normal", &Core::Vertex::normal)
        .def_readwrite("uv", &Core::Vertex::uv)
        .def_readwrite("index", &Core::Vertex::index);

    py::class_<Core::Face>(m, "Face")
        .def_readwrite("indices", &Core::Face::indices)
        .def_readwrite("normal", &Core::Face::normal);

    py::class_<Core::Mesh>(m, "Mesh")
        .def(py::init<std::string>())
        .def_readwrite("name", &Core::Mesh::name)
        .def("add_vertex", &Core::Mesh::addVertex)
        .def("add_face", &Core::Mesh::addFace)
        .def("calculate_normals", &Core::Mesh::calculateNormals)
        .def("clear", &Core::Mesh::clear)
        // Transforms
        .def("translate", &Core::Mesh::translate)
        .def("scale", &Core::Mesh::scale)
        .def("rotate_x", &Core::Mesh::rotateX)
        .def("rotate_y", &Core::Mesh::rotateY)
        .def("rotate_z", &Core::Mesh::rotateZ)
        // Editing
        .def("extrude_face", &Core::Mesh::extrudeFace)
        .def("scale_face", &Core::Mesh::scaleFace)
        .def("translate_face", &Core::Mesh::translateFace)
        .def("join", &Core::Mesh::join)
        // Properties
        .def_property_readonly("vertex_count", &Core::Mesh::vertexCount)
        .def_property_readonly("face_count", &Core::Mesh::faceCount)
        .def_readonly("vertices", &Core::Mesh::vertices)
        .def_readonly("faces", &Core::Mesh::faces);

    // Geometry Primitives
    m.def("create_cube", &Geometry::Primitives::CreateCube, "Create a cube mesh", py::arg("size") = 1.0f);
    m.def("create_sphere", &Geometry::Primitives::CreateSphere, "Create a sphere mesh", py::arg("radius") = 1.0f, py::arg("segments") = 16, py::arg("rings") = 16);
    m.def("create_cylinder", &Geometry::Primitives::CreateCylinder, "Create a cylinder mesh", py::arg("radius") = 1.0f, py::arg("height") = 2.0f, py::arg("segments") = 16);
    m.def("create_cone", &Geometry::Primitives::CreateCone, "Create a cone mesh", py::arg("radius") = 1.0f, py::arg("height") = 2.0f, py::arg("segments") = 16);
    m.def("create_torus", &Geometry::Primitives::CreateTorus, "Create a torus mesh", py::arg("main_radius") = 1.0f, py::arg("tube_radius") = 0.4f, py::arg("main_segments") = 32, py::arg("tube_segments") = 16);
    m.def("create_plane", &Geometry::Primitives::CreatePlane, "Create a plane mesh", py::arg("size") = 2.0f, py::arg("subdivisions") = 1);
}
