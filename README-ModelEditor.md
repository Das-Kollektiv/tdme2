TDMEModelEditor
===============

    - What is it?
        - TDME based 3D model asset viewer/editor 

    - What is already working
        - model loading
            - DAE, Wavefront OBJ, FBX, TM model files and TMM meta data files
        - model meta data file saving 
            - TMM
                - stores its model as TM file additionally
        - render with generated ground, shadowing, bounding volume
        - rotate, zoom
        - setting up model properties
            - key, value map for what ever reason
        - setting up the model pivot
        - setting up up to 8 bounding volumes (WIP)
            - none
            - sphere
            - capsule
            - bounding box
            - oriented bounding box
            - convex mesh
              - multiple convex meshes can be automatically generated from any mesh using V-HACD
            - concave terrain mesh
        - LOD level editor
            - type, distance, model, adjustment add/mul color, ... 
        - material editor
            - adjust colors, textures, masked transparency
        - animations editor
            - create, edit and delete animations
        - set up rendering options
            - use dynamic shadowing
        - see statistics
            - opaque faces
            - transparent faces
            - material count

    - What is WIP
        - setting up physic properties

    - Technology
        - uses TDME2

    - Links
        - No links yet

    - Credits
        - Dominik Hepp
        - others
