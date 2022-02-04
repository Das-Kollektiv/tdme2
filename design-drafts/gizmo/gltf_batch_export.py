# ##### BEGIN GPL LICENSE BLOCK #####
#
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software Foundation,
#  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
#
# ##### END GPL LICENSE BLOCK #####
# <pep8 compliant>

bl_info = {
    "name": "Batch export glTF/glb files",
    "author": "brockmann",
    "version": (0, 0, 2),
    "blender": (2, 83, 0),
    "location": "File > Import-Export",
    "description": "Batch Export Collections to glTF/glb",
    "warning": "",
    "wiki_url": "",
    "tracker_url": "",
    "category": "Import-Export"}


import bpy
import os
import sys

from bpy_extras.io_utils import ExportHelper
from bpy.props import (BoolProperty,
                       IntProperty,
                       StringProperty,
                       EnumProperty,
                       CollectionProperty
                       )


def file_name(s):
    """Return valid file name from string"""
    #return "".join(x for x in s if x.isalnum())
    return "".join( x for x in s if (x.isalnum() or x in "._- "))

def col_hierarchy(root_col, levels=1):
    """Read hierarchy of the collections in the scene"""
    level_lookup = {}
    def recurse(root_col, parent, depth):
        if depth > levels: 
            return
        if isinstance(parent,  bpy.types.Collection):
            level_lookup.setdefault(parent, []).append(root_col)
        for child in root_col.children:
            recurse(child, root_col,  depth + 1)
    recurse(root_col, root_col.children, 0)
    return level_lookup


class SCENE_OT_batch_gltf(bpy.types.Operator, ExportHelper):
    """Batch export collections to glTF/glb files"""
    bl_idname = "export_scene.batch_gltf"
    bl_label = "Collections to glTF/glb"
    bl_options = {'PRESET', 'UNDO'}

    # ExportHelper mixin class uses this
    filename_ext = ''

    filter_glob: StringProperty(
            default='*.glb;*.gltf', 
            options={'HIDDEN'}
    )

    # List of operator properties, the attributes will be assigned
    # to the class instance from the operator setting before calling.
    batch_export_format: EnumProperty(
        name='Format',
        items=(('GLB', 'glTF Binary (.glb)',
                'Exports a single file, with all data packed in binary form. '
                'Most efficient and portable, but more difficult to edit later'),
               ('GLTF_EMBEDDED', 'glTF Embedded (.gltf)',
                'Exports a single file, with all data packed in JSON. '
                'Less efficient than binary, but easier to edit later'),
               ('GLTF_SEPARATE', 'glTF Separate (.gltf + .bin + textures)',
                'Exports multiple files, with separate JSON, binary and texture data. '
                'Easiest to edit later')),
        description=(
            'Output format and embedding options. Binary is most efficient, '
            'but JSON (embedded or separate) may be easier to edit later'
        ),
        default='GLB'
    )

    batch_export_copyright: StringProperty(
        name='Copyright',
        description='Legal rights and conditions for the model',
        default=''
    )

    batch_export_image_format: EnumProperty(
        name='Images',
        items=(('AUTO', 'Automatic',
                'Save PNGs as PNGs and JPEGs as JPEGs.\n'
                'If neither one, use PNG'),
                ('JPEG', 'JPEG Format (.jpg)',
                'Save images as JPEGs. (Images that need alpha are saved as PNGs though.)\n'
                'Be aware of a possible loss in quality'),
               ),
        description=(
            'Output format for images. PNG is lossless and generally preferred, but JPEG might be preferable for web '
            'applications due to the smaller file size'
        ),
        default='AUTO'
    )

    batch_export_levels: IntProperty(
        name='Collection Levels',
        description='Set the levels of collections',
        default=1
    )

    batch_export_materials: EnumProperty(
            name='Export Materials',
			items=(('EXPORT', 'Export', 'Export'),
                   ('PLACEHOLDER', 'Placeholder', 'Placeholder'),
				   ('NONE', 'None', 'None')
               ),
            description='Export materials',
            default='EXPORT'
    )

    batch_export_colors: BoolProperty(
        name='Export Vertex Colors',
        description='Export vertex colors with meshes',
        default=False
    )

    batch_export_cameras: BoolProperty(
        name='Export Cameras',
        description='Export cameras',
        default=False
    )

    batch_export_extras: BoolProperty(
        name='Export Custom Properties',
        description='Export custom properties as glTF extras',
        default=False
    )

    batch_export_apply: BoolProperty(
        name='Export Apply Modifiers',
        description='Apply modifiers (excluding Armatures) to mesh objects -'
                    'WARNING: prevents exporting shape keys',
        default=True
    )

    batch_export_yup: BoolProperty(
        name='+Y Up',
        description='Export using glTF convention, +Y up',
        default=True
    )


    def execute(self, context):                
        argv = sys.argv
        argv = argv[argv.index("--") + 1:]

        filePath = ""
        for argvValue in argv:
            if argvValue.find("--filepath=") != -1:
                filePath = argvValue[argvValue.rfind("=") + 1:len(argvValue)]

        # Get the folder
        folder_path = filePath if len(filePath) > 0 else os.path.dirname(self.filepath)
        scn_col = context.scene.collection

        # Lookups (Collections per level and Parents)
        lkp_col = col_hierarchy(scn_col, levels=self.batch_export_levels)
        prt_col = {i : k for k, v in lkp_col.items() for i in v}

        scn_obj = [o for o in scn_col.objects]
        candidates = [x for v in lkp_col.values() for x in v]

        if not candidates:
            self.report({'INFO'}, "Nothing to export")
            return {'CANCELLED'}        

        # Unlink all Collections and objects
        for c in candidates:
            prt_col.get(c).children.unlink(c)
        for o in scn_obj: 
            scn_col.objects.unlink(o)

        # (Re-)link collections of choice to root level and export
        cIdx = 0
        for c in candidates:
            scn_col.children.link(c)
	
            sceneName = bpy.path.basename(bpy.data.filepath)
            sceneName = sceneName[:sceneName.rfind(".")]
            if c.name == "hp" or c.name == "lp":
                continue			
            if cIdx == 0:
                fname = file_name(sceneName)
            else:
                fname = file_name(sceneName + "_" + c.name)
            fpath = os.path.join(folder_path, fname)

            bpy.ops.export_scene.gltf(
                filepath = fpath,
                export_format = self.batch_export_format,
                export_copyright = self.batch_export_copyright,
                export_image_format = self.batch_export_image_format,
                export_materials = self.batch_export_materials,
                export_colors = self.batch_export_colors,
                export_cameras = self.batch_export_cameras,
                export_extras = self.batch_export_extras,
                export_yup = self.batch_export_yup,
                export_apply = self.batch_export_apply,
                export_tangents=False,
                export_lights=False				
            )

            scn_col.children.unlink(c)

            cIdx = cIdx + 1

        # Reset all back
        for o in scn_obj: 
            scn_col.objects.link(o)
        for c in candidates: 
            prt_col.get(c).children.link(c)

        return {'FINISHED'}


# Only needed if you want to add into a dynamic menu
def menu_func_import(self, context):
    self.layout.operator(SCENE_OT_batch_gltf.bl_idname, text="glTF Batch Export (.glb/gltf)")


def register():
    bpy.utils.register_class(SCENE_OT_batch_gltf)
    bpy.types.TOPBAR_MT_file_export.append(menu_func_import)


def unregister():
    #bpy.utils.unregister_class(SCENE_OT_batch_gltf)
    #bpy.types.TOPBAR_MT_file_export.remove(menu_func_import)


if __name__ == "__main__":
    register()
    bpy.ops.export_scene.batch_gltf(filepath='.', check_existing=False)
