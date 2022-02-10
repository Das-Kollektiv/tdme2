D:

rem gizmo
cd D:\Programme\Blender\
blender D:\Projekte\AScottishWarstory\tdme2\design-drafts\gizmo\gizmo.blend --background --python "C:\Users\Epilog\AppData\Roaming\Blender Foundation\Blender\3.0\scripts\addons\gltf_batch_export.py" -- --filepath=D:\Projekte\AScottishWarstory\tdme2\resources\engine\models\
cd D:\Projekte\AScottishWarstory\tdme2
D:\Projekte\AScottishWarstory\tdme2\bin\tdme\tools\cli\importtmodel  D:\Projekte\AScottishWarstory\tdme2\resources\engine\models\gizmo_all.tmodel D:\Projekte\AScottishWarstory\tdme2\resources\engine\models\gizmo_all.glb
D:\Projekte\AScottishWarstory\tdme2\bin\tdme\tools\cli\importtmodel  D:\Projekte\AScottishWarstory\tdme2\resources\engine\models\gizmo_translate.tmodel D:\Projekte\AScottishWarstory\tdme2\resources\engine\models\gizmo_translate.glb
D:\Projekte\AScottishWarstory\tdme2\bin\tdme\tools\cli\importtmodel  D:\Projekte\AScottishWarstory\tdme2\resources\engine\models\gizmo_scale.tmodel D:\Projekte\AScottishWarstory\tdme2\resources\engine\models\gizmo_scale.glb
D:\Projekte\AScottishWarstory\tdme2\bin\tdme\tools\cli\importtmodel  D:\Projekte\AScottishWarstory\tdme2\resources\engine\models\gizmo_rotate.tmodel D:\Projekte\AScottishWarstory\tdme2\resources\engine\models\gizmo_rotate.glb
D:\Projekte\AScottishWarstory\tdme2\bin\tdme\tools\cli\importtmodel  D:\Projekte\AScottishWarstory\tdme2\resources\engine\models\gizmo_transscale.tmodel D:\Projekte\AScottishWarstory\tdme2\resources\engine\models\gizmo_transscale.glb
del D:\Projekte\AScottishWarstory\tdme2\resources\engine\models\gizmo*.glb