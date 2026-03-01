try:
    from ._threedimensions_core import *
except ImportError:
    # Fallback for development/IDE if the extension isn't built yet
    import sys
    import math
    print("Warning: C++ core extension not found. Using mock/pure python fallback if available.", file=sys.stderr)
    
    class Vector3:
        def __init__(self, x=0, y=0, z=0):
            self.x, self.y, self.z = x, y, z
        def __repr__(self):
            return f"<Vector3 ({self.x}, {self.y}, {self.z})>"
        def __add__(self, other):
            return Vector3(self.x + other.x, self.y + other.y, self.z + other.z)
        def __sub__(self, other):
            return Vector3(self.x - other.x, self.y - other.y, self.z - other.z)
        def __mul__(self, scalar):
            return Vector3(self.x * scalar, self.y * scalar, self.z * scalar)
            
    class Vertex:
        def __init__(self):
            self.position = Vector3()
            self.normal = Vector3()
            self.uv = Vector3()
            self.index = 0

    class Face:
        def __init__(self):
            self.indices = []
            self.normal = Vector3()

    class Mesh:
        def __init__(self, name="Mesh"):
            self.name = name
            self.vertices = []
            self.faces = []
            
        @property
        def vertex_count(self): return len(self.vertices)
        @property
        def face_count(self): return len(self.faces)
            
        def add_vertex(self, v):
            ver = Vertex()
            ver.position = v
            ver.index = len(self.vertices)
            self.vertices.append(ver)
            
        def add_face(self, indices):
            f = Face()
            f.indices = indices
            # Compute normal for face
            if len(indices) >= 3:
                v0 = self.vertices[indices[0]].position
                v1 = self.vertices[indices[1]].position
                v2 = self.vertices[indices[2]].position
                edge1 = v1 - v0
                edge2 = v2 - v0
                # Cross product
                nx = edge1.y * edge2.z - edge1.z * edge2.y
                ny = edge1.z * edge2.x - edge1.x * edge2.z
                nz = edge1.x * edge2.y - edge1.y * edge2.x
                l = math.sqrt(nx*nx + ny*ny + nz*nz)
                if l > 0:
                    f.normal = Vector3(nx/l, ny/l, nz/l)
            self.faces.append(f)
            
        def calculate_normals(self):
            pass 
            
        def translate(self, v):
            for vert in self.vertices:
                vert.position = vert.position + v
                
        def scale(self, v):
            for vert in self.vertices:
                vert.position.x *= v.x
                vert.position.y *= v.y
                vert.position.z *= v.z
                
        def rotate_x(self, angle): pass
        def rotate_y(self, angle): pass
        def rotate_z(self, angle): pass
        
        def extrude_face(self, face_index, distance):
            if face_index >= len(self.faces): return
            face = self.faces[face_index]
            new_indices = []
            
            # Duplicate vertices and move them
            # Use face normal for direction
            direction = face.normal
            if direction.x == 0 and direction.y == 0 and direction.z == 0:
                direction = Vector3(0, 1, 0) # Default up if no normal

            for idx in face.indices:
                orig_v = self.vertices[idx]
                new_v = Vector3(
                    orig_v.position.x + direction.x * distance,
                    orig_v.position.y + direction.y * distance,
                    orig_v.position.z + direction.z * distance
                )
                self.add_vertex(new_v)
                new_indices.append(len(self.vertices) - 1)
            
            # Add side faces
            n = len(face.indices)
            for i in range(n):
                next_i = (i + 1) % n
                b1 = face.indices[i]
                b2 = face.indices[next_i]
                t1 = new_indices[i]
                t2 = new_indices[next_i]
                self.add_face([b1, b2, t2, t1])
                
            # Update top face
            face.indices = new_indices

        def scale_face(self, face_index, scale):
            if face_index >= len(self.faces): return
            face = self.faces[face_index]
            center = Vector3()
            for idx in face.indices:
                center = center + self.vertices[idx].position
            center = center * (1.0 / len(face.indices))
            
            for idx in face.indices:
                v = self.vertices[idx]
                diff = v.position - center
                v.position = center + (diff * scale)
                
        def translate_face(self, face_index, v):
            if face_index >= len(self.faces): return
            face = self.faces[face_index]
            for idx in face.indices:
                vert = self.vertices[idx]
                vert.position = vert.position + v

    def create_cube(size=1.0):
        m = Mesh("Cube")
        h = size * 0.5
        # Vertices
        verts = [
            Vector3(-h, -h, -h), Vector3(h, -h, -h), Vector3(h, h, -h), Vector3(-h, h, -h),
            Vector3(-h, -h, h), Vector3(h, -h, h), Vector3(h, h, h), Vector3(-h, h, h)
        ]
        for v in verts: m.add_vertex(v)
        # Faces
        faces = [
            [0, 1, 2, 3], [4, 5, 6, 7], [0, 3, 7, 4],
            [1, 2, 6, 5], [0, 1, 5, 4], [3, 2, 6, 7]
        ]
        for f in faces: m.add_face(f)
        return m
        
    def create_sphere(radius=1.0, segments=16, rings=16):
        m = Mesh("Sphere")
        for i in range(rings + 1):
            v = i / rings
            phi = v * math.pi
            for j in range(segments + 1):
                u = j / segments
                theta = u * 2.0 * math.pi
                x = radius * math.sin(phi) * math.cos(theta)
                y = radius * math.cos(phi)
                z = radius * math.sin(phi) * math.sin(theta)
                m.add_vertex(Vector3(x, y, z))
        
        for i in range(rings):
            for j in range(segments):
                current = i * (segments + 1) + j
                next_val = current + segments + 1
                m.add_face([current, next_val, next_val + 1, current + 1])
        return m
        
    def create_cylinder(radius=1.0, height=2.0, segments=16):
        m = Mesh("Cylinder")
        half = height * 0.5
        m.add_vertex(Vector3(0, -half, 0)) # 0
        m.add_vertex(Vector3(0, half, 0))  # 1
        
        for i in range(segments):
            theta = (i / segments) * 2.0 * math.pi
            x = radius * math.cos(theta)
            z = radius * math.sin(theta)
            m.add_vertex(Vector3(x, -half, z))
            m.add_vertex(Vector3(x, half, z))
            
        for i in range(segments):
            next_i = (i + 1) % segments
            b1 = 2 + 2 * i
            t1 = 3 + 2 * i
            b2 = 2 + 2 * next_i
            t2 = 3 + 2 * next_i
            m.add_face([b1, b2, t2, t1])
            m.add_face([0, b2, b1])
            m.add_face([1, t1, t2])
        return m

    def create_cone(radius=1.0, height=2.0, segments=16):
        m = Mesh("Cone")
        half = height * 0.5
        m.add_vertex(Vector3(0, -half, 0)) # 0: Bottom Center
        m.add_vertex(Vector3(0, half, 0))  # 1: Tip
        
        for i in range(segments):
            theta = (i / segments) * 2.0 * math.pi
            x = radius * math.cos(theta)
            z = radius * math.sin(theta)
            m.add_vertex(Vector3(x, -half, z))
            
        for i in range(segments):
            next_i = (i + 1) % segments
            b1 = 2 + i
            b2 = 2 + next_i
            m.add_face([b1, b2, 1]) # Side to tip
            m.add_face([0, b2, b1]) # Bottom
        return m

    def create_torus(main_radius=1.0, tube_radius=0.4, main_segments=32, tube_segments=16):
        m = Mesh("Torus")
        for i in range(main_segments + 1):
            theta = (i / main_segments) * 2.0 * math.pi
            cos_theta = math.cos(theta)
            sin_theta = math.sin(theta)
            for j in range(tube_segments + 1):
                phi = (j / tube_segments) * 2.0 * math.pi
                cos_phi = math.cos(phi)
                sin_phi = math.sin(phi)
                x = (main_radius + tube_radius * cos_phi) * cos_theta
                y = tube_radius * sin_phi
                z = (main_radius + tube_radius * cos_phi) * sin_theta
                m.add_vertex(Vector3(x, y, z))
                
        for i in range(main_segments):
            for j in range(tube_segments):
                current = i * (tube_segments + 1) + j
                next_val = current + tube_segments + 1
                m.add_face([current, next_val, next_val + 1, current + 1])
        return m

    def create_plane(size=2.0, subdivisions=1):
        m = Mesh("Plane")
        half = size * 0.5
        step = size / subdivisions
        for z in range(subdivisions + 1):
            for x in range(subdivisions + 1):
                px = -half + x * step
                pz = -half + z * step
                m.add_vertex(Vector3(px, 0, pz))
                
        for z in range(subdivisions):
            for x in range(subdivisions):
                row1 = z * (subdivisions + 1)
                row2 = (z + 1) * (subdivisions + 1)
                m.add_face([row1 + x, row2 + x, row2 + x + 1, row1 + x + 1])
        return m
