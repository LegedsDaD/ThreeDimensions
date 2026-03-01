from .mesh import Mesh

class Sculpt:
    """Sculpting tools interface."""
    
    @staticmethod
    def inflate(mesh: Mesh, center, radius, strength):
        """Inflate vertices within radius of center."""
        mesh.inflate(center, radius, strength)
        
    @staticmethod
    def smooth(mesh: Mesh, center, radius, strength):
        """Smooth vertices within radius of center."""
        pass
