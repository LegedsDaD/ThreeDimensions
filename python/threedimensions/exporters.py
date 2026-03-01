from .mesh import Mesh
import struct

class Exporter:
    @staticmethod
    def export_obj(mesh: Mesh, filepath: str):
        """Export mesh to OBJ format."""
        with open(filepath, 'w') as f:
            f.write(f"# ThreeDimensions OBJ Export: {mesh.name}\n")
            
            # Write Vertices
            for v in mesh.vertices:
                p = v.position
                f.write(f"v {p.x:.6f} {p.y:.6f} {p.z:.6f}\n")
            
            # Write Normals
            for v in mesh.vertices:
                n = v.normal
                f.write(f"vn {n.x:.6f} {n.y:.6f} {n.z:.6f}\n")
            
            # Write Faces
            # OBJ indices are 1-based
            for face in mesh.faces:
                indices = face.indices
                # Format: f v1//vn1 v2//vn2 ...
                # Using double slash because we aren't exporting UVs yet (vt)
                line_parts = []
                for idx in indices:
                    obj_idx = idx + 1
                    line_parts.append(f"{obj_idx}//{obj_idx}")
                
                f.write("f " + " ".join(line_parts) + "\n")
            
            print(f"Exported {mesh.name} to {filepath}")

    @staticmethod
    def export_stl(mesh: Mesh, filepath: str):
        """Export mesh to Binary STL format."""
        with open(filepath, 'wb') as f:
            # 80 byte header
            header = f"ThreeDimensions Export: {mesh.name}".ljust(80, ' ')
            f.write(header.encode('ascii'))
            
            # Calculate triangle count (triangulate faces if needed)
            triangles = []
            for face in mesh.faces:
                indices = face.indices
                if len(indices) < 3: continue
                # Triangle fan triangulation
                v0 = mesh.vertices[indices[0]].position
                for i in range(1, len(indices) - 1):
                    v1 = mesh.vertices[indices[i]].position
                    v2 = mesh.vertices[indices[i+1]].position
                    triangles.append((face.normal, v0, v1, v2))
            
            # Number of triangles (4 bytes unsigned int)
            f.write(struct.pack('<I', len(triangles)))
            
            # Triangles
            for normal, v0, v1, v2 in triangles:
                # Normal (3 floats), V1 (3 floats), V2 (3 floats), V3 (3 floats), Attribute (2 bytes)
                f.write(struct.pack('<3f', normal.x, normal.y, normal.z))
                f.write(struct.pack('<3f', v0.x, v0.y, v0.z))
                f.write(struct.pack('<3f', v1.x, v1.y, v1.z))
                f.write(struct.pack('<3f', v2.x, v2.y, v2.z))
                f.write(struct.pack('<H', 0)) # Attribute byte count
                
            print(f"Exported {mesh.name} to {filepath} (STL)")

class Importer:
    pass
