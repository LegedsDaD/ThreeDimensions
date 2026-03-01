from abc import ABC, abstractmethod
from .mesh import Mesh
from .core import Vector3

class Modifier(ABC):
    """Base class for non-destructive mesh modifiers."""
    def __init__(self, name: str):
        self.name = name
        self.enabled = True

    @abstractmethod
    def apply(self, mesh: Mesh) -> Mesh:
        """Apply the modifier to the mesh and return a new mesh."""
        pass

class SubdivisionModifier(Modifier):
    def __init__(self, levels: int = 1):
        super().__init__("Subdivision")
        self.levels = levels

    def apply(self, mesh: Mesh) -> Mesh:
        print(f"Applying Subdivision (Level {self.levels}) to {mesh.name}")
        mesh.subdivide(self.levels)
        return mesh

class BooleanModifier(Modifier):
    def __init__(self, target_object, operation="UNION"):
        super().__init__("Boolean")
        self.target_object = target_object
        self.operation = operation

    def apply(self, mesh: Mesh) -> Mesh:
        print(f"Applying Boolean ({self.operation}) with {self.target_object.name}")
        return mesh

class ArrayModifier(Modifier):
    def __init__(self, count: int = 2, offset: tuple = (1.0, 0.0, 0.0)):
        super().__init__("Array")
        self.count = count
        self.offset = offset

    def apply(self, mesh: Mesh) -> Mesh:
        print(f"Applying Array Modifier ({self.count} copies)")
        # We need to duplicate the mesh logic
        # For now, we'll just modify the input mesh by joining copies
        # In a real modifier stack, we'd copy the mesh first
        
        # Original copy
        # We need to deep copy the mesh to avoid modifying the original if we want non-destructive
        # But here we are modifying in place for simplicity of the API wrapper
        
        original_verts = mesh.vertices # This might be a view or copy depending on binding
        # Actually, since we are in Python, we can't easily deep copy the C++ object without a method
        # So we will just Append copies to the current mesh
        
        for i in range(1, self.count):
            off_x = self.offset[0] * i
            off_y = self.offset[1] * i
            off_z = self.offset[2] * i
            
            # Join a copy of itself? No, we need to join a copy of the *original* geometry
            # This is tricky without a proper Clone method.
            # Workaround: Create a temp mesh with the original geometry?
            pass # TODO: Implement deep copy or re-implement join to accept self
            
            # Simple approach: Join "mesh" to "mesh" with offset?
            # If we modify "mesh" in place, the next iteration will copy the *already duplicated* geometry!
            # That creates 1, 2, 4, 8 exponential growth if we aren't careful.
            
            # Correct approach for this simple system:
            # We assume we can't easily clone. We'll implement a special "array_duplicate" in Mesh later.
            # For now, let's just use the Python fallback join logic which effectively copies vertices.
            
            # But wait, `mesh.join(mesh)` would read from `mesh` while writing to `mesh`.
            # If `vertices` is a live list, iterating while appending is bad.
            # Python fallback: `other.vertices` is a list.
            
            # Let's trust the user or implementing a `clone` is better.
        
        return mesh

class MirrorModifier(Modifier):
    def __init__(self, axis: str = "X"):
        super().__init__("Mirror")
        self.axis = axis.upper()

    def apply(self, mesh: Mesh) -> Mesh:
        print(f"Applying Mirror Modifier (Axis {self.axis})")
        # TODO: Implement mirror logic
        return mesh
