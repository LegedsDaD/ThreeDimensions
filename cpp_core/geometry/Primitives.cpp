#include "Primitives.h"
#include <cmath>
#include <numbers>

namespace ThreeDimensions {
namespace Geometry {

std::unique_ptr<Core::Mesh> Primitives::CreateCube(float size) {
    auto mesh = std::make_unique<Core::Mesh>("Cube");
    float half = size * 0.5f;
    
    // Vertices
    mesh->addVertex(Math::Vec3(-half, -half, -half));
    mesh->addVertex(Math::Vec3( half, -half, -half));
    mesh->addVertex(Math::Vec3( half,  half, -half));
    mesh->addVertex(Math::Vec3(-half,  half, -half));
    mesh->addVertex(Math::Vec3(-half, -half,  half));
    mesh->addVertex(Math::Vec3( half, -half,  half));
    mesh->addVertex(Math::Vec3( half,  half,  half));
    mesh->addVertex(Math::Vec3(-half,  half,  half));

    // Faces (Indices)
    mesh->addFace({0, 1, 2, 3}); // Back
    mesh->addFace({4, 5, 6, 7}); // Front
    mesh->addFace({0, 3, 7, 4}); // Left
    mesh->addFace({1, 2, 6, 5}); // Right
    mesh->addFace({0, 1, 5, 4}); // Bottom
    mesh->addFace({3, 2, 6, 7}); // Top
    
    mesh->calculateNormals();
    return mesh;
}

std::unique_ptr<Core::Mesh> Primitives::CreateSphere(float radius, int segments, int rings) {
    auto mesh = std::make_unique<Core::Mesh>("Sphere");
    const float PI = 3.14159265359f;
    
    // Vertices
    for (int i = 0; i <= rings; ++i) {
        float v = (float)i / (float)rings;
        float phi = v * PI;
        
        for (int j = 0; j <= segments; ++j) {
            float u = (float)j / (float)segments;
            float theta = u * 2.0f * PI;
            
            float x = radius * std::sin(phi) * std::cos(theta);
            float y = radius * std::cos(phi);
            float z = radius * std::sin(phi) * std::sin(theta);
            
            mesh->addVertex(Math::Vec3(x, y, z));
        }
    }
    
    // Faces
    for (int i = 0; i < rings; ++i) {
        for (int j = 0; j < segments; ++j) {
            int current = i * (segments + 1) + j;
            int next = current + segments + 1;
            
            mesh->addFace({current, next, next + 1, current + 1});
        }
    }
    
    mesh->calculateNormals();
    return mesh;
}

std::unique_ptr<Core::Mesh> Primitives::CreateCylinder(float radius, float height, int segments) {
    auto mesh = std::make_unique<Core::Mesh>("Cylinder");
    const float PI = 3.14159265359f;
    float halfHeight = height * 0.5f;

    // Top and Bottom center vertices
    mesh->addVertex(Math::Vec3(0, -halfHeight, 0)); // Bottom Center (Index 0)
    mesh->addVertex(Math::Vec3(0, halfHeight, 0));  // Top Center (Index 1)

    // Ring vertices
    for (int i = 0; i < segments; ++i) {
        float theta = (float)i / segments * 2.0f * PI;
        float x = radius * std::cos(theta);
        float z = radius * std::sin(theta);
        
        // Bottom ring
        mesh->addVertex(Math::Vec3(x, -halfHeight, z));
        // Top ring
        mesh->addVertex(Math::Vec3(x, halfHeight, z));
    }

    // Faces
    for (int i = 0; i < segments; ++i) {
        int next = (i + 1) % segments;
        
        // Indices for the ring vertices start at 2
        // Bottom ring: 2 + 2*i
        // Top ring: 3 + 2*i
        
        int b1 = 2 + 2 * i;
        int t1 = 3 + 2 * i;
        int b2 = 2 + 2 * next;
        int t2 = 3 + 2 * next;

        // Side Quad
        mesh->addFace({b1, b2, t2, t1});

        // Bottom Cap (Triangle Fan)
        mesh->addFace({0, b2, b1}); 

        // Top Cap (Triangle Fan)
        mesh->addFace({1, t1, t2});
    }

    mesh->calculateNormals();
    return mesh;
}

std::unique_ptr<Core::Mesh> Primitives::CreateCone(float radius, float height, int segments) {
    auto mesh = std::make_unique<Core::Mesh>("Cone");
    const float PI = 3.14159265359f;
    float halfHeight = height * 0.5f;

    // Center vertices
    mesh->addVertex(Math::Vec3(0, -halfHeight, 0)); // Bottom Center (Index 0)
    mesh->addVertex(Math::Vec3(0, halfHeight, 0));  // Top Tip (Index 1)

    // Bottom Ring vertices
    for (int i = 0; i < segments; ++i) {
        float theta = (float)i / segments * 2.0f * PI;
        float x = radius * std::cos(theta);
        float z = radius * std::sin(theta);
        mesh->addVertex(Math::Vec3(x, -halfHeight, z));
    }

    // Faces
    for (int i = 0; i < segments; ++i) {
        int next = (i + 1) % segments;
        
        // Indices for the ring vertices start at 2
        int b1 = 2 + i;
        int b2 = 2 + next;
        int tip = 1;

        // Side Triangle
        mesh->addFace({b1, b2, tip});

        // Bottom Cap (Triangle Fan)
        mesh->addFace({0, b2, b1});
    }

    mesh->calculateNormals();
    return mesh;
}

std::unique_ptr<Core::Mesh> Primitives::CreateTorus(float mainRadius, float tubeRadius, int mainSegments, int tubeSegments) {
    auto mesh = std::make_unique<Core::Mesh>("Torus");
    const float PI = 3.14159265359f;

    for (int i = 0; i <= mainSegments; ++i) {
        float theta = (float)i / mainSegments * 2.0f * PI;
        float cosTheta = std::cos(theta);
        float sinTheta = std::sin(theta);

        for (int j = 0; j <= tubeSegments; ++j) {
            float phi = (float)j / tubeSegments * 2.0f * PI;
            float cosPhi = std::cos(phi);
            float sinPhi = std::sin(phi);

            float x = (mainRadius + tubeRadius * cosPhi) * cosTheta;
            float y = tubeRadius * sinPhi;
            float z = (mainRadius + tubeRadius * cosPhi) * sinTheta;

            mesh->addVertex(Math::Vec3(x, y, z));
        }
    }

    for (int i = 0; i < mainSegments; ++i) {
        for (int j = 0; j < tubeSegments; ++j) {
            int current = i * (tubeSegments + 1) + j;
            int next = current + tubeSegments + 1;

            mesh->addFace({current, next, next + 1, current + 1});
        }
    }

    mesh->calculateNormals();
    return mesh;
}

std::unique_ptr<Core::Mesh> Primitives::CreatePlane(float size, int subdivisions) {
    auto mesh = std::make_unique<Core::Mesh>("Plane");
    float half = size * 0.5f;
    float step = size / subdivisions;

    // Vertices
    for (int z = 0; z <= subdivisions; ++z) {
        for (int x = 0; x <= subdivisions; ++x) {
            float px = -half + x * step;
            float pz = -half + z * step;
            mesh->addVertex(Math::Vec3(px, 0, pz));
        }
    }

    // Faces
    for (int z = 0; z < subdivisions; ++z) {
        for (int x = 0; x < subdivisions; ++x) {
            int row1 = z * (subdivisions + 1);
            int row2 = (z + 1) * (subdivisions + 1);
            
            // Quad
            mesh->addFace({
                row1 + x,
                row2 + x,
                row2 + x + 1,
                row1 + x + 1
            });
        }
    }

    mesh->calculateNormals();
    return mesh;
}

}
}
