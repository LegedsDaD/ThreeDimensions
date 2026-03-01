from typing import List, Optional, Dict
from .mesh import Mesh
from .core import Vector3
import os

class Transform:
    """Represents a 3D transformation."""
    def __init__(self):
        self.position = Vector3(0, 0, 0)
        self.rotation = Vector3(0, 0, 0) # Euler angles for simplicity
        self.scale = Vector3(1, 1, 1)

class Object:
    """Base class for all scene objects."""
    def __init__(self, name: str = "Object", mesh: Optional[Mesh] = None):
        self.name = name
        self.mesh = mesh
        self.transform = Transform()
        self.children: List['Object'] = []
        self.parent: Optional['Object'] = None
        self.modifiers: List = [] # To be filled with Modifier objects

    def add_child(self, child: 'Object'):
        if child.parent:
            child.parent.remove_child(child)
        child.parent = self
        self.children.append(child)

    def remove_child(self, child: 'Object'):
        if child in self.children:
            self.children.remove(child)
            child.parent = None

    def __repr__(self):
        return f"<Object '{self.name}'>"

class Scene:
    """Represents a 3D scene graph."""
    def __init__(self, name: str = "Scene"):
        self.name = name
        self.root = Object("Root")
        self.objects: Dict[str, Object] = {} # Flat registry for lookup

    def add_object(self, obj: Object, parent: Optional[Object] = None):
        if parent is None:
            parent = self.root
        parent.add_child(obj)
        self.objects[obj.name] = obj

    def get_object(self, name: str) -> Optional[Object]:
        return self.objects.get(name)

    def update(self):
        """Update scene state, apply modifiers, etc."""
        # Traverse graph and update transforms, apply modifiers...
        pass

    def save(self, filepath: str):
        """
        Export the entire scene to a file.
        Currently merges all objects into one file.
        """
        # For simplicity, we'll export individual objects or the first object
        # In a real engine, we'd merge meshes or use a scene format like GLTF
        print(f"Saving scene {self.name} to {filepath}...")
        
        # Simple implementation: Export the first object found
        if not self.objects:
            print("Scene is empty, nothing to save.")
            return

        # TODO: Merge meshes for export
        # For now, just export the first object's mesh as a demo
        first_obj = list(self.objects.values())[0]
        if first_obj.mesh:
            print(f"Exporting object: {first_obj.name}")
            first_obj.mesh.save(filepath)
        else:
            print(f"Object {first_obj.name} has no mesh.")
