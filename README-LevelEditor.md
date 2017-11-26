TDMELevelEditor
===============

    - What is it?
        - TDME based level editor 

    - What is already working
        - entity library
            - in general
                - setting up entity properties
                    - key, value map for what ever reason
            - models
                - model loading
                    - DAE, FBX, Wavefront OBJ, TM, TMM meta data files
                - setup name, description
                - render with generated ground, shadowing, bounding volume
                - setting up the model pivot
                - see statistics
            - particle systems
            - empties
            - trigger
        - level editor
            - setting up a grid where to place objects on
            - load, save maps, showing level dimension
            - import maps from DAE files, which
                - takes first level model groups as objects by converting them to .TM files, ...
            - setting up map properties
                - key, value map for what ever reason
            - objects
                 - set up name, description
                 - see model name, center
            - setting up object transformations for a single or multiple objects
                 - translation
                 - scaling
                 - rotation
                 - color your objects
                 - center objects
                 - remove objects
             - setting up object properties
                 - key, value map for what ever reason
            - set up up to 8 lights (for now)
            - see and select entities(models, particle systems, empties and trigger) from entity library to place them on map
            - rotate, zoom and pan map, selecting objects
            - copy and paste

    - What is WIP
        - set up arbitrary lights as entities
        - import maps from model files(not only DAE)

    - Technology
        - uses TDME2

    - Links
        - no links yet

    - Credits
        - Dominik Hepp
        - Kolja Gumpert
        - others
