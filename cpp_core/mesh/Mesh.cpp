#include "Mesh.h"
#include <cmath>
#include <algorithm>
#include <map>

namespace ThreeDimensions {
namespace Core {

Mesh::Mesh(const std::string& name) : name(name) {}

Mesh::~Mesh() {}

void Mesh::addVertex(const Vec3& position) {
    Vertex v;
    v.position = position;
    v.index = vertices.size();
    vertices.push_back(v);
}

void Mesh::addFace(const std::vector<int>& indices) {
    Face f;
    f.indices = indices;
    faces.push_back(f);
}

void Mesh::calculateNormals() {
    // Simple face normal calculation
    for (auto& face : faces) {
        if (face.indices.size() < 3) continue;
        
        const Vec3& v0 = vertices[face.indices[0]].position;
        const Vec3& v1 = vertices[face.indices[1]].position;
        const Vec3& v2 = vertices[face.indices[2]].position;
        
        Vec3 edge1 = v1 - v0;
        Vec3 edge2 = v2 - v0;
        
        face.normal = edge1.cross(edge2);
        face.normal.normalize();
    }
    
    // Vertex normals (averaging face normals)
    for (auto& v : vertices) {
        v.normal = Vec3(0, 0, 0);
    }
    
    for (const auto& face : faces) {
        for (int idx : face.indices) {
            vertices[idx].normal = vertices[idx].normal + face.normal;
        }
    }
    
    for (auto& v : vertices) {
        v.normal.normalize();
    }
}

void Mesh::clear() {
    vertices.clear();
    faces.clear();
}

// Transforms

void Mesh::translate(const Vec3& translation) {
    for (auto& v : vertices) {
        v.position = v.position + translation;
    }
}

void Mesh::scale(const Vec3& scaleFactor) {
    for (auto& v : vertices) {
        v.position.x *= scaleFactor.x;
        v.position.y *= scaleFactor.y;
        v.position.z *= scaleFactor.z;
    }
}

void Mesh::rotateX(float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    for (auto& v : vertices) {
        float y = v.position.y * c - v.position.z * s;
        float z = v.position.y * s + v.position.z * c;
        v.position.y = y;
        v.position.z = z;
    }
    calculateNormals();
}

void Mesh::rotateY(float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    for (auto& v : vertices) {
        float x = v.position.x * c + v.position.z * s;
        float z = -v.position.x * s + v.position.z * c;
        v.position.x = x;
        v.position.z = z;
    }
    calculateNormals();
}

void Mesh::rotateZ(float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    for (auto& v : vertices) {
        float x = v.position.x * c - v.position.y * s;
        float y = v.position.x * s + v.position.y * c;
        v.position.x = x;
        v.position.y = y;
    }
    calculateNormals();
}

// Basic Editing

void Mesh::extrudeFace(int faceIndex, float distance) {
    if (faceIndex < 0 || faceIndex >= faces.size()) return;

    // 1. Identify the face and its vertices
    Face& originalFace = faces[faceIndex];
    std::vector<int> originalIndices = originalFace.indices;
    std::vector<int> newIndices;

    // 2. Duplicate vertices
    for (int idx : originalIndices) {
        Vertex newV = vertices[idx]; // Copy
        newV.index = vertices.size();
        // Move new vertex along normal
        newV.position = newV.position + (originalFace.normal * distance);
        vertices.push_back(newV);
        newIndices.push_back(newV.index);
    }

    // 3. Create side faces (quads)
    int n = originalIndices.size();
    for (int i = 0; i < n; ++i) {
        int next = (i + 1) % n;
        
        int bottom1 = originalIndices[i];
        int bottom2 = originalIndices[next];
        int top1 = newIndices[i];
        int top2 = newIndices[next];

        // Create side quad. Winding order depends on normal direction.
        // Assuming original face normal points OUT.
        // Side face normal should also point OUT.
        addFace({bottom1, bottom2, top2, top1});
    }

    // 4. Update the original face to use new vertices (effectively moving the cap)
    // Actually, extrude usually leaves the hole behind. 
    // In this simple implementation, we just "move" the face by reassigning its indices to the new ones.
    // The "original" face geometry stays as the "floor" of the extrusion, but we often want to remove it 
    // if it's internal.
    // For a solid extrusion (like lengthening a cylinder), we want to KEEP the sides and MOVE the cap.
    // So the original face object becomes the top cap.
    
    originalFace.indices = newIndices;
    
    calculateNormals();
}

void Mesh::translateFace(int faceIndex, const Vec3& translation) {
    if (faceIndex < 0 || faceIndex >= faces.size()) return;
    
    Face& face = faces[faceIndex];
    for (int idx : face.indices) {
        vertices[idx].position = vertices[idx].position + translation;
    }
    calculateNormals(); // Recompute normals
}

void Mesh::scaleFace(int faceIndex, float scaleFactor) {
    if (faceIndex < 0 || faceIndex >= faces.size()) return;
    
    Face& face = faces[faceIndex];
    
    // Calculate center of face
    Vec3 center(0, 0, 0);
    for (int idx : face.indices) {
        center = center + vertices[idx].position;
    }
    center = center * (1.0f / face.indices.size());
    
    // Scale vertices relative to center
    for (int idx : face.indices) {
        Vec3 diff = vertices[idx].position - center;
        vertices[idx].position = center + (diff * scaleFactor);
    }
    calculateNormals();
}

void Mesh::join(const Mesh& other, const Vec3& offset) {
    int vertexOffset = vertices.size();
    
    // Copy vertices with offset
    for (const auto& v : other.vertices) {
        Vertex newV = v;
        newV.position = newV.position + offset;
        newV.index = vertices.size();
        vertices.push_back(newV);
    }
    
    // Copy faces with index offset
    for (const auto& f : other.faces) {
        Face newF = f;
        for (auto& idx : newF.indices) {
            idx += vertexOffset;
        }
        faces.push_back(newF);
    }
    calculateNormals();
}

}
}
