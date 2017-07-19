INCLUDES := $(INCLUDES) -Isrc -Iext/src -I./
EXTRA_LIBS ?= -l$(NAME)-ext -framework GLUT -framework OpenGL -framework Cocoa -L/usr/lib -lz
#EXTRA_LIBS ?= -l$(NAME)-ext -L/usr/lib -lz -lGL -lglut

CPPFLAGS := $(CPPFLAGS) $(INCLUDES)
CFLAGS := $(CFLAGS) -g -pipe -MMD -MP
CXXFLAGS := $(CFLAGS) -std=gnu++11

BIN := bin
OBJ := obj

NAME := tdme

LIB = lib$(NAME).a
EXT_LIB = lib$(NAME)-ext.a

LIBS = $(BIN)/$(LIB) $(BIN)/$(EXT_LIB)

SRC = src
STUB = stub
NATIVE = native
TINYXML = tinyxml
JSONBOX = jsonbox
LIBPNG = libpng

SRCS = \
	src/j2c.cpp \
	src/tdme/audio/Audio.cpp \
	src/tdme/audio/AudioBufferManager.cpp \
	src/tdme/audio/AudioBufferManager_AudioBufferManaged.cpp \
	src/tdme/audio/AudioEntity.cpp \
	src/tdme/audio/AudioStream.cpp \
	src/tdme/audio/Sound.cpp \
	src/tdme/audio/decoder/AudioDecoder.cpp \
	src/tdme/audio/decoder/AudioDecoderException.cpp \
	src/tdme/engine/Application.cpp \
	src/tdme/engine/ApplicationInputEventsHandler.cpp \
	src/tdme/engine/Camera.cpp \
	src/tdme/engine/Engine.cpp \
	src/tdme/engine/Engine_AnimationProcessingTarget.cpp \
	src/tdme/engine/Engine_initialize_1.cpp \
	src/tdme/engine/Engine_initialize_2.cpp \
	src/tdme/engine/Entity.cpp \
	src/tdme/engine/EntityPickingFilter.cpp \
	src/tdme/engine/FrameBuffer.cpp \
	src/tdme/engine/Frustum.cpp \
	src/tdme/engine/Light.cpp \
	src/tdme/engine/ModelUtilities.cpp \
	src/tdme/engine/Object3D.cpp \
	src/tdme/engine/Object3DModel.cpp \
	src/tdme/engine/ObjectParticleSystemEntity.cpp \
	src/tdme/engine/Partition.cpp \
	src/tdme/engine/PartitionNone.cpp \
	src/tdme/engine/PartitionOctTree.cpp \
	src/tdme/engine/PartitionOctTree_PartitionTreeNode.cpp \
	src/tdme/engine/PartitionOctTree_reset_1.cpp \
	src/tdme/engine/PartitionOctTree_reset_2.cpp \
	src/tdme/engine/PartitionOctTree_reset_3.cpp \
	src/tdme/engine/PartitionOctTree_reset_6.cpp \
	src/tdme/engine/PointsParticleSystemEntity.cpp \
	src/tdme/engine/Rotation.cpp \
	src/tdme/engine/Rotations.cpp \
	src/tdme/engine/Timing.cpp \
	src/tdme/engine/Transformations.cpp \
	src/tdme/engine/fileio/models/DAEReader.cpp \
	src/tdme/engine/fileio/models/DAEReader_AuthoringTool.cpp \
	src/tdme/engine/fileio/models/DAEReader_determineDisplacementFilename_1.cpp \
	src/tdme/engine/fileio/models/ModelFileIOException.cpp \
	src/tdme/engine/fileio/models/TMReader.cpp \
	src/tdme/engine/fileio/models/TMWriter.cpp \
	src/tdme/engine/fileio/models/WFObjReader.cpp \
	src/tdme/engine/fileio/textures/Texture.cpp \
	src/tdme/engine/fileio/textures/TextureLoader.cpp \
	src/tdme/engine/model/Animation.cpp \
	src/tdme/engine/model/AnimationSetup.cpp \
	src/tdme/engine/model/Color4.cpp \
	src/tdme/engine/model/Color4Base.cpp \
	src/tdme/engine/model/Face.cpp \
	src/tdme/engine/model/FacesEntity.cpp \
	src/tdme/engine/model/Group.cpp \
	src/tdme/engine/model/Joint.cpp \
	src/tdme/engine/model/JointWeight.cpp \
	src/tdme/engine/model/Material.cpp \
	src/tdme/engine/model/Model.cpp \
	src/tdme/engine/model/ModelHelper.cpp \
	src/tdme/engine/model/ModelHelper_VertexOrder.cpp \
	src/tdme/engine/model/Model_UpVector.cpp \
	src/tdme/engine/model/RotationOrder.cpp \
	src/tdme/engine/model/Skinning.cpp \
	src/tdme/engine/model/TextureCoordinate.cpp \
	src/tdme/engine/physics/CollisionDetection.cpp \
	src/tdme/engine/physics/CollisionListener.cpp \
	src/tdme/engine/physics/CollisionResponse.cpp \
	src/tdme/engine/physics/CollisionResponse_Entity.cpp \
	src/tdme/engine/physics/ConstraintsEntity.cpp \
	src/tdme/engine/physics/ConstraintsSolver.cpp \
	src/tdme/engine/physics/ContactCache.cpp \
	src/tdme/engine/physics/ContactCache_ContactCacheInfo.cpp \
	src/tdme/engine/physics/DynamicVector.cpp \
	src/tdme/engine/physics/Matrix1x6.cpp \
	src/tdme/engine/physics/Matrix6x6.cpp \
	src/tdme/engine/physics/PhysicsPartition.cpp \
	src/tdme/engine/physics/PhysicsPartitionNone.cpp \
	src/tdme/engine/physics/PhysicsPartitionOctTree.cpp \
	src/tdme/engine/physics/PhysicsPartitionOctTree_PartitionTreeNode.cpp \
	src/tdme/engine/physics/PhysicsPartitionOctTree_reset_1.cpp \
	src/tdme/engine/physics/PhysicsPartitionOctTree_reset_2.cpp \
	src/tdme/engine/physics/PhysicsPartitionOctTree_reset_3.cpp \
	src/tdme/engine/physics/PhysicsPartitionOctTree_reset_6.cpp \
	src/tdme/engine/physics/RigidBody.cpp \
	src/tdme/engine/physics/Vector6.cpp \
	src/tdme/engine/physics/World.cpp \
	src/tdme/engine/physics/World_1.cpp \
	src/tdme/engine/physics/World_2.cpp \
	src/tdme/engine/primitives/BoundingBox.cpp \
	src/tdme/engine/primitives/BoundingVolume.cpp \
	src/tdme/engine/primitives/Capsule.cpp \
	src/tdme/engine/primitives/ConvexMesh.cpp \
	src/tdme/engine/primitives/LineSegment.cpp \
	src/tdme/engine/primitives/OrientedBoundingBox.cpp \
	src/tdme/engine/primitives/Plane.cpp \
	src/tdme/engine/primitives/PrimitiveModel.cpp \
	src/tdme/engine/primitives/Sphere.cpp \
	src/tdme/engine/primitives/Triangle.cpp \
	src/tdme/engine/subsystems/lighting/LightingShader.cpp \
	src/tdme/engine/subsystems/manager/MeshManager.cpp \
	src/tdme/engine/subsystems/manager/MeshManager_MeshManaged.cpp \
	src/tdme/engine/subsystems/manager/TextureManager.cpp \
	src/tdme/engine/subsystems/manager/TextureManager_TextureManaged.cpp \
	src/tdme/engine/subsystems/manager/VBOManager.cpp \
	src/tdme/engine/subsystems/manager/VBOManager_VBOManaged.cpp \
	src/tdme/engine/subsystems/object/AnimationState.cpp \
	src/tdme/engine/subsystems/object/BatchVBORendererPoints.cpp \
	src/tdme/engine/subsystems/object/BatchVBORendererTriangles.cpp \
	src/tdme/engine/subsystems/object/ModelUtilitiesInternal.cpp \
	src/tdme/engine/subsystems/object/ModelUtilitiesInternal_ModelStatistics.cpp \
	src/tdme/engine/subsystems/object/Object3DBase.cpp \
	src/tdme/engine/subsystems/object/Object3DBase_TransformedFacesIterator.cpp \
	src/tdme/engine/subsystems/object/Object3DGroup.cpp \
	src/tdme/engine/subsystems/object/Object3DGroupMesh.cpp \
	src/tdme/engine/subsystems/object/Object3DGroupVBORenderer.cpp \
	src/tdme/engine/subsystems/object/Object3DInternal.cpp \
	src/tdme/engine/subsystems/object/Object3DModelInternal.cpp \
	src/tdme/engine/subsystems/object/Object3DVBORenderer.cpp \
	src/tdme/engine/subsystems/object/Object3DVBORenderer_1.cpp \
	src/tdme/engine/subsystems/object/Object3DVBORenderer_Object3DVBORenderer_2.cpp \
	src/tdme/engine/subsystems/object/Object3DVBORenderer_Object3DVBORenderer_3.cpp \
	src/tdme/engine/subsystems/object/TransparentRenderFace.cpp \
	src/tdme/engine/subsystems/object/TransparentRenderFacesGroup.cpp \
	src/tdme/engine/subsystems/object/TransparentRenderFacesPool.cpp \
	src/tdme/engine/subsystems/object/TransparentRenderFacesPool_TransparentRenderFacesPool_1.cpp \
	src/tdme/engine/subsystems/object/TransparentRenderPoint.cpp \
	src/tdme/engine/subsystems/object/TransparentRenderPointsPool.cpp \
	src/tdme/engine/subsystems/object/_Buffer.cpp \
	src/tdme/engine/subsystems/particlesystem/BoundingBoxParticleEmitter.cpp \
	src/tdme/engine/subsystems/particlesystem/CircleParticleEmitter.cpp \
	src/tdme/engine/subsystems/particlesystem/CircleParticleEmitterPlaneVelocity.cpp \
	src/tdme/engine/subsystems/particlesystem/ObjectParticleSystemEntityInternal.cpp \
	src/tdme/engine/subsystems/particlesystem/Particle.cpp \
	src/tdme/engine/subsystems/particlesystem/ParticleEmitter.cpp \
	src/tdme/engine/subsystems/particlesystem/ParticleSystemEntity.cpp \
	src/tdme/engine/subsystems/particlesystem/ParticlesShader.cpp \
	src/tdme/engine/subsystems/particlesystem/PointParticleEmitter.cpp \
	src/tdme/engine/subsystems/particlesystem/PointsParticleSystemEntityInternal.cpp \
	src/tdme/engine/subsystems/particlesystem/SphereParticleEmitter.cpp \
	src/tdme/engine/subsystems/renderer/GL3Renderer.cpp \
	src/tdme/engine/subsystems/renderer/GL2Renderer.cpp \
	src/tdme/engine/subsystems/renderer/GLRenderer.cpp \
	src/tdme/engine/subsystems/renderer/GLRenderer_Light.cpp \
	src/tdme/engine/subsystems/renderer/GLRenderer_Material.cpp \
	src/tdme/engine/subsystems/shadowmapping/ShadowMap.cpp \
	src/tdme/engine/subsystems/shadowmapping/ShadowMapping.cpp \
	src/tdme/engine/subsystems/shadowmapping/ShadowMappingShaderPre.cpp \
	src/tdme/engine/subsystems/shadowmapping/ShadowMappingShaderRender.cpp \
	src/tdme/engine/subsystems/shadowmapping/ShadowMapping_RunState.cpp \
	src/tdme/gui/GUI.cpp \
	src/tdme/gui/GUIParser.cpp \
	src/tdme/gui/GUIParserException.cpp \
	src/tdme/gui/GUI_1.cpp \
	src/tdme/gui/GUI_2.cpp \
	src/tdme/gui/effects/GUIColorEffect.cpp \
	src/tdme/gui/effects/GUIEffect.cpp \
	src/tdme/gui/effects/GUIPositionEffect.cpp \
	src/tdme/gui/elements/GUIButton.cpp \
	src/tdme/gui/elements/GUIButtonController.cpp \
	src/tdme/gui/elements/GUICheckbox.cpp \
	src/tdme/gui/elements/GUICheckboxController.cpp \
	src/tdme/gui/elements/GUIDropDown.cpp \
	src/tdme/gui/elements/GUIDropDownController.cpp \
	src/tdme/gui/elements/GUIDropDownOption.cpp \
	src/tdme/gui/elements/GUIDropDownOptionController.cpp \
	src/tdme/gui/elements/GUIElement.cpp \
	src/tdme/gui/elements/GUIInput.cpp \
	src/tdme/gui/elements/GUIInputController.cpp \
	src/tdme/gui/elements/GUIRadioButton.cpp \
	src/tdme/gui/elements/GUIRadioButtonController.cpp \
	src/tdme/gui/elements/GUIScrollArea.cpp \
	src/tdme/gui/elements/GUIScrollAreaController.cpp \
	src/tdme/gui/elements/GUIScrollAreaController_initialize_1.cpp \
	src/tdme/gui/elements/GUIScrollAreaHorizontal.cpp \
	src/tdme/gui/elements/GUIScrollAreaHorizontalController.cpp \
	src/tdme/gui/elements/GUIScrollAreaHorizontalController_initialize_1.cpp \
	src/tdme/gui/elements/GUIScrollAreaVertical.cpp \
	src/tdme/gui/elements/GUIScrollAreaVerticalController.cpp \
	src/tdme/gui/elements/GUIScrollAreaVerticalController_initialize_1.cpp \
	src/tdme/gui/elements/GUISelectBox.cpp \
	src/tdme/gui/elements/GUISelectBoxController.cpp \
	src/tdme/gui/elements/GUISelectBoxMultiple.cpp \
	src/tdme/gui/elements/GUISelectBoxMultipleController.cpp \
	src/tdme/gui/elements/GUISelectBoxMultipleOption.cpp \
	src/tdme/gui/elements/GUISelectBoxMultipleOptionController.cpp \
	src/tdme/gui/elements/GUISelectBoxOption.cpp \
	src/tdme/gui/elements/GUISelectBoxOptionController.cpp \
	src/tdme/gui/elements/GUITab.cpp \
	src/tdme/gui/elements/GUITabContent.cpp \
	src/tdme/gui/elements/GUITabContentController.cpp \
	src/tdme/gui/elements/GUITabController.cpp \
	src/tdme/gui/elements/GUITabs.cpp \
	src/tdme/gui/elements/GUITabsContent.cpp \
	src/tdme/gui/elements/GUITabsController.cpp \
	src/tdme/gui/elements/GUITabsHeader.cpp \
	src/tdme/gui/elements/GUITabsHeaderController.cpp \
	src/tdme/gui/events/Action.cpp \
	src/tdme/gui/events/GUIActionListener.cpp \
	src/tdme/gui/events/GUIActionListener_Type.cpp \
	src/tdme/gui/events/GUIChangeListener.cpp \
	src/tdme/gui/events/GUIInputEventHandler.cpp \
	src/tdme/gui/events/GUIKeyboardEvent.cpp \
	src/tdme/gui/events/GUIKeyboardEvent_Type.cpp \
	src/tdme/gui/events/GUIMouseEvent.cpp \
	src/tdme/gui/events/GUIMouseEvent_Type.cpp \
	src/tdme/gui/nodes/GUIColor.cpp \
	src/tdme/gui/nodes/GUIElementController.cpp \
	src/tdme/gui/nodes/GUIElementIgnoreEventsController.cpp \
	src/tdme/gui/nodes/GUIElementNode.cpp \
	src/tdme/gui/nodes/GUIHorizontalScrollbarInternalController.cpp \
	src/tdme/gui/nodes/GUIHorizontalScrollbarInternalController_State.cpp \
	src/tdme/gui/nodes/GUIHorizontalScrollbarInternalNode.cpp \
	src/tdme/gui/nodes/GUIImageNode.cpp \
	src/tdme/gui/nodes/GUIInputInternalController.cpp \
	src/tdme/gui/nodes/GUIInputInternalController_CursorMode.cpp \
	src/tdme/gui/nodes/GUIInputInternalNode.cpp \
	src/tdme/gui/nodes/GUILayoutNode.cpp \
	src/tdme/gui/nodes/GUILayoutNode_Alignment.cpp \
	src/tdme/gui/nodes/GUINode.cpp \
	src/tdme/gui/nodes/GUINodeConditions.cpp \
	src/tdme/gui/nodes/GUINodeController.cpp \
	src/tdme/gui/nodes/GUINode_AlignmentHorizontal.cpp \
	src/tdme/gui/nodes/GUINode_AlignmentVertical.cpp \
	src/tdme/gui/nodes/GUINode_Alignments.cpp \
	src/tdme/gui/nodes/GUINode_Border.cpp \
	src/tdme/gui/nodes/GUINode_ComputedConstraints.cpp \
	src/tdme/gui/nodes/GUINode_Flow.cpp \
	src/tdme/gui/nodes/GUINode_Padding.cpp \
	src/tdme/gui/nodes/GUINode_RequestedConstraints.cpp \
	src/tdme/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.cpp \
	src/tdme/gui/nodes/GUIPanelNode.cpp \
	src/tdme/gui/nodes/GUIParentNode.cpp \
	src/tdme/gui/nodes/GUIParentNode_Overflow.cpp \
	src/tdme/gui/nodes/GUIScreenNode.cpp \
	src/tdme/gui/nodes/GUISpaceNode.cpp \
	src/tdme/gui/nodes/GUITextNode.cpp \
	src/tdme/gui/nodes/GUIVerticalScrollbarInternalController.cpp \
	src/tdme/gui/nodes/GUIVerticalScrollbarInternalController_State.cpp \
	src/tdme/gui/nodes/GUIVerticalScrollbarInternalNode.cpp \
	src/tdme/gui/renderer/GUIFont.cpp \
	src/tdme/gui/renderer/GUIFont_CharacterDefinition.cpp \
	src/tdme/gui/renderer/GUIRenderer.cpp \
	src/tdme/gui/renderer/GUIShader.cpp \
	src/tdme/math/MathTools.cpp \
	src/tdme/math/Matrix4x4.cpp \
	src/tdme/math/Matrix4x4Negative.cpp \
	src/tdme/math/Quaternion.cpp \
	src/tdme/math/SeparatingAxisTheorem.cpp \
	src/tdme/math/TriangleTriangleIntersection.cpp \
	src/tdme/math/TriangleTriangleIntersection_ReturnValue.cpp \
	src/tdme/math/Vector2.cpp \
	src/tdme/math/Vector3.cpp \
	src/tdme/math/Vector4.cpp \
	src/tdme/os/_FileSystem.cpp \
	src/tdme/os/_FileSystemException.cpp \
	src/tdme/os/_FileSystemInterface.cpp \
	src/tdme/os/_StandardFileSystem.cpp \
	src/tdme/tests/AngleTest.cpp \
	src/tdme/tests/AudioTest.cpp \
	src/tdme/tests/AudioTest_main_1.cpp \
	src/tdme/tests/EngineTest.cpp \
	src/tdme/tests/GUITest.cpp \
	src/tdme/tests/GUITest_init_1.cpp \
	src/tdme/tests/GUITest_init_2.cpp \
	src/tdme/tests/PhysicsTest1.cpp \
	src/tdme/tests/PhysicsTest2.cpp \
	src/tdme/tests/PhysicsTest3.cpp \
	src/tdme/tools/leveleditor/TDMELevelEditor.cpp \
	src/tdme/tools/leveleditor/controller/EmptyScreenController.cpp \
	src/tdme/tools/leveleditor/controller/EmptyScreenController_EmptyScreenController_1.cpp \
	src/tdme/tools/leveleditor/controller/LevelEditorEntityLibraryScreenController.cpp \
	src/tdme/tools/leveleditor/controller/LevelEditorEntityLibraryScreenController_onValueChanged_1.cpp \
	src/tdme/tools/leveleditor/controller/LevelEditorScreenController.cpp \
	src/tdme/tools/leveleditor/controller/LevelEditorScreenController_onMapLoad_1.cpp \
	src/tdme/tools/leveleditor/controller/LevelEditorScreenController_onMapSave_2.cpp \
	src/tdme/tools/leveleditor/controller/TriggerScreenController.cpp \
	src/tdme/tools/leveleditor/controller/TriggerScreenController_TriggerScreenController_1.cpp \
	src/tdme/tools/leveleditor/logic/Level.cpp \
	src/tdme/tools/leveleditor/views/EmptyView.cpp \
	src/tdme/tools/leveleditor/views/LevelEditorView.cpp \
	src/tdme/tools/leveleditor/views/LevelEditorView_LevelEditorView_1.cpp \
	src/tdme/tools/leveleditor/views/LevelEditorView_ObjectColor.cpp \
	src/tdme/tools/leveleditor/views/ModelViewerView.cpp \
	src/tdme/tools/leveleditor/views/ParticleSystemView.cpp \
	src/tdme/tools/leveleditor/views/TriggerView.cpp \
	src/tdme/tools/particlesystem/TDMEParticleSystem.cpp \
	src/tdme/tools/shared/controller/EntityBaseSubScreenController.cpp \
	src/tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController.cpp \
	src/tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController_BoundingVolumeType.cpp \
	src/tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshFile_1.cpp \
	src/tdme/tools/shared/controller/EntityDisplaySubScreenController.cpp \
	src/tdme/tools/shared/controller/FileDialogPath.cpp \
	src/tdme/tools/shared/controller/FileDialogScreenController.cpp \
	src/tdme/tools/shared/controller/FileDialogScreenController_setupFileDialogListBox_1.cpp \
	src/tdme/tools/shared/controller/InfoDialogScreenController.cpp \
	src/tdme/tools/shared/controller/ModelViewerScreenController.cpp \
	src/tdme/tools/shared/controller/ModelViewerScreenController_ModelViewerScreenController_1.cpp \
	src/tdme/tools/shared/controller/ModelViewerScreenController_onModelLoad_2.cpp \
	src/tdme/tools/shared/controller/ModelViewerScreenController_onModelSave_3.cpp \
	src/tdme/tools/shared/controller/ParticleSystemScreenController.cpp \
	src/tdme/tools/shared/controller/ParticleSystemScreenController_ParticleSystemScreenController_1.cpp \
	src/tdme/tools/shared/controller/ParticleSystemScreenController_onActionPerformed_4.cpp \
	src/tdme/tools/shared/controller/ParticleSystemScreenController_onEntitySave_3.cpp \
	src/tdme/tools/shared/controller/ParticleSystemScreenController_onParticleSystemLoad_2.cpp \
	src/tdme/tools/shared/controller/ScreenController.cpp \
	src/tdme/tools/shared/files/LevelFileExport.cpp \
	src/tdme/tools/shared/files/LevelFileImport.cpp \
	src/tdme/tools/shared/files/ModelMetaDataFileExport.cpp \
	src/tdme/tools/shared/files/ModelMetaDataFileImport.cpp \
	src/tdme/tools/shared/model/LevelEditorEntity.cpp \
	src/tdme/tools/shared/model/LevelEditorEntityBoundingVolume.cpp \
	src/tdme/tools/shared/model/LevelEditorEntityLibrary.cpp \
	src/tdme/tools/shared/model/LevelEditorEntityParticleSystem.cpp \
	src/tdme/tools/shared/model/LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter.cpp \
	src/tdme/tools/shared/model/LevelEditorEntityParticleSystem_CircleParticleEmitter.cpp \
	src/tdme/tools/shared/model/LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity.cpp \
	src/tdme/tools/shared/model/LevelEditorEntityParticleSystem_Emitter.cpp \
	src/tdme/tools/shared/model/LevelEditorEntityParticleSystem_ObjectParticleSystem.cpp \
	src/tdme/tools/shared/model/LevelEditorEntityParticleSystem_PointParticleEmitter.cpp \
	src/tdme/tools/shared/model/LevelEditorEntityParticleSystem_PointParticleSystem.cpp \
	src/tdme/tools/shared/model/LevelEditorEntityParticleSystem_SphereParticleEmitter.cpp \
	src/tdme/tools/shared/model/LevelEditorEntityParticleSystem_Type.cpp \
	src/tdme/tools/shared/model/LevelEditorEntity_EntityType.cpp \
	src/tdme/tools/shared/model/LevelEditorLevel.cpp \
	src/tdme/tools/shared/model/LevelEditorLight.cpp \
	src/tdme/tools/shared/model/LevelEditorObject.cpp \
	src/tdme/tools/shared/model/LevelPropertyPresets.cpp \
	src/tdme/tools/shared/model/ModelProperties.cpp \
	src/tdme/tools/shared/model/PropertyModelClass.cpp \
	src/tdme/tools/shared/tools/Tools.cpp \
	src/tdme/tools/shared/views/CameraRotationInputHandler.cpp \
	src/tdme/tools/shared/views/EntityBaseView.cpp \
	src/tdme/tools/shared/views/EntityBoundingVolumeView.cpp \
	src/tdme/tools/shared/views/EntityDisplayView.cpp \
	src/tdme/tools/shared/views/PopUps.cpp \
	src/tdme/tools/shared/views/SharedModelViewerView.cpp \
	src/tdme/tools/shared/views/SharedParticleSystemView.cpp \
	src/tdme/tools/shared/views/View.cpp \
	src/tdme/tools/viewer/TDMEViewer.cpp \
	src/tdme/utils/Key.cpp \
	src/tdme/utils/MutableString.cpp \
	src/tdme/utils/Pool.cpp \
	src/tdme/utils/StringConverter.cpp \
	src/tdme/utils/_ArrayList.cpp \
	src/tdme/utils/_ExceptionBase.cpp \
	src/tdme/utils/_Console.cpp \
	src/tdme/utils/_HashMap.cpp \
	src/tdme/utils/_HashMap_1.cpp \
	src/tdme/utils/_HashMap_KeysIterator.cpp \
	src/tdme/utils/_HashMap_Pair.cpp \
	src/tdme/utils/_HashMap_ValuesIterator.cpp \

#	src/tdme/engine/Engine_initialize_3.cpp \
#	src/tdme/engine/subsystems/renderer/GLES2Renderer.cpp \

STUB_SRCS = \


NATIVE_SRCS = \


EXT_SRCS = \


EXT_STUB_SRCS = \
	ext/stub/java/io/BufferedReader-stub.cpp \
	ext/stub/java/io/ByteArrayInputStream-stub.cpp \
	ext/stub/java/io/DataInputStream-stub.cpp \
	ext/stub/java/io/File-stub.cpp \
	ext/stub/java/io/FileInputStream-stub.cpp \
	ext/stub/java/io/FileNotFoundException-stub.cpp \
	ext/stub/java/io/FileOutputStream-stub.cpp \
	ext/stub/java/io/File_LazyInitialization-stub.cpp \
	ext/stub/java/io/FilterInputStream-stub.cpp \
	ext/stub/java/io/FilterOutputStream-stub.cpp \
	ext/stub/java/io/IOException-stub.cpp \
	ext/stub/java/io/InputStream-stub.cpp \
	ext/stub/java/io/InputStreamReader-stub.cpp \
	ext/stub/java/io/OutputStream-stub.cpp \
	ext/stub/java/io/PrintStream-stub.cpp \
	ext/stub/java/io/Reader-stub.cpp \
	ext/stub/java/lang/AbstractStringBuilder-stub.cpp \
	ext/stub/java/lang/ArrayStoreException-stub.cpp \
	ext/stub/java/lang/Byte-stub.cpp \
	ext/stub/java/lang/Byte_ByteCache-stub.cpp \
	ext/stub/java/lang/Character-stub.cpp \
	ext/stub/java/lang/Character_CharacterCache-stub.cpp \
	ext/stub/java/lang/Character_Subset-stub.cpp \
	ext/stub/java/lang/Character_UnicodeBlock-stub.cpp \
	ext/stub/java/lang/Class-stub.cpp \
	ext/stub/java/lang/ClassCastException-stub.cpp \
	ext/stub/java/lang/ClassLoader-stub.cpp \
	ext/stub/java/lang/ClassLoader_NativeLibrary-stub.cpp \
	ext/stub/java/lang/ClassNotFoundException-stub.cpp \
	ext/stub/java/lang/Class_EnclosingMethodInfo-stub.cpp \
	ext/stub/java/lang/Class_MethodArray-stub.cpp \
	ext/stub/java/lang/Enum-stub.cpp \
	ext/stub/java/lang/Exception-stub.cpp \
	ext/stub/java/lang/Float-stub.cpp \
	ext/stub/java/lang/IllegalArgumentException-stub.cpp \
	ext/stub/java/lang/Integer-stub.cpp \
	ext/stub/java/lang/Integer_IntegerCache-stub.cpp \
	ext/stub/java/lang/InterruptedException-stub.cpp \
	ext/stub/java/lang/Math-stub.cpp \
	ext/stub/java/lang/NullPointerException-stub.cpp \
	ext/stub/java/lang/Number-stub.cpp \
	ext/stub/java/lang/NumberFormatException-stub.cpp \
	ext/stub/java/lang/Object-stub.cpp \
	ext/stub/java/lang/RuntimeException-stub.cpp \
	ext/stub/java/lang/Short-stub.cpp \
	ext/stub/java/lang/Short_ShortCache-stub.cpp \
	ext/stub/java/lang/StackTraceElement-stub.cpp \
	ext/stub/java/lang/String-stub.cpp \
	ext/stub/java/lang/String-stub-regex.cpp \
	ext/stub/java/lang/StringBuffer-stub.cpp \
	ext/stub/java/lang/StringBuilder-stub.cpp \
	ext/stub/java/lang/String_CaseInsensitiveComparator-stub.cpp \
	ext/stub/java/lang/System-stub.cpp \
	ext/stub/java/lang/Thread-stub.cpp \
	ext/stub/java/lang/Thread_State-stub.cpp \
	ext/stub/java/lang/Throwable-stub.cpp \
	ext/stub/java/lang/UnsupportedOperationException-stub.cpp \
	ext/stub/java/net/URL-stub.cpp \
	ext/stub/java/nio/Buffer-stub.cpp \
	ext/stub/java/nio/ByteBuffer-stub.cpp \
	ext/stub/java/nio/ByteOrder-stub.cpp \
	ext/stub/java/nio/FloatBuffer-stub.cpp \
	ext/stub/java/nio/IntBuffer-stub.cpp \
	ext/stub/java/nio/ShortBuffer-stub.cpp \
	ext/stub/java/security/CodeSource-stub.cpp \
	ext/stub/java/security/ProtectionDomain-stub.cpp \
	ext/stub/java/security/ProtectionDomain_Key-stub.cpp \
	ext/stub/java/util/AbstractCollection-stub.cpp \
	ext/stub/java/util/AbstractList-stub.cpp \
	ext/stub/java/util/AbstractList_Itr-stub.cpp \
	ext/stub/java/util/AbstractList_ListItr-stub.cpp \
	ext/stub/java/util/AbstractMap-stub.cpp \
	ext/stub/java/util/AbstractMap_SimpleEntry-stub.cpp \
	ext/stub/java/util/AbstractMap_SimpleImmutableEntry-stub.cpp \
	ext/stub/java/util/AbstractSet-stub.cpp \
	ext/stub/java/util/Arrays-stub.cpp \
	ext/stub/java/util/Arrays_ArrayList-stub.cpp \
	ext/stub/java/util/Dictionary-stub.cpp \
	ext/stub/java/util/EventObject-stub.cpp \
	ext/stub/java/util/HashMap-stub.cpp \
	ext/stub/java/util/HashMap_Entry-stub.cpp \
	ext/stub/java/util/HashMap_EntryIterator-stub.cpp \
	ext/stub/java/util/HashMap_EntrySet-stub.cpp \
	ext/stub/java/util/HashMap_HashIterator-stub.cpp \
	ext/stub/java/util/HashMap_KeyIterator-stub.cpp \
	ext/stub/java/util/HashMap_KeySet-stub.cpp \
	ext/stub/java/util/HashMap_ValueIterator-stub.cpp \
	ext/stub/java/util/HashMap_Values-stub.cpp \
	ext/stub/java/util/HashSet-stub.cpp \
	ext/stub/java/util/Hashtable-stub.cpp \
	ext/stub/java/util/Hashtable_EmptyEnumerator-stub.cpp \
	ext/stub/java/util/Hashtable_EmptyIterator-stub.cpp \
	ext/stub/java/util/Hashtable_Entry-stub.cpp \
	ext/stub/java/util/Hashtable_EntrySet-stub.cpp \
	ext/stub/java/util/Hashtable_Enumerator-stub.cpp \
	ext/stub/java/util/Hashtable_KeySet-stub.cpp \
	ext/stub/java/util/Hashtable_ValueCollection-stub.cpp \
	ext/stub/java/util/Locale-stub.cpp \
	ext/stub/java/util/Locale_LocaleNameGetter-stub.cpp \
	ext/stub/java/util/Properties-stub.cpp \
	ext/stub/java/util/Properties_LineReader-stub.cpp \
	ext/stub/java/util/StringTokenizer-stub.cpp \
	ext/stub/java/util/TimerTask-stub.cpp \
	ext/stub/java/util/concurrent/locks/AbstractOwnableSynchronizer-stub.cpp \
	ext/stub/java/util/concurrent/locks/AbstractQueuedSynchronizer-stub.cpp \
	ext/stub/java/util/concurrent/locks/AbstractQueuedSynchronizer_ConditionObject-stub.cpp \
	ext/stub/java/util/concurrent/locks/AbstractQueuedSynchronizer_Node-stub.cpp \
	ext/stub/java/util/concurrent/locks/ReentrantLock-stub.cpp \
	ext/stub/java/util/concurrent/locks/ReentrantLock_FairSync-stub.cpp \
	ext/stub/java/util/concurrent/locks/ReentrantLock_NonfairSync-stub.cpp \
	ext/stub/java/util/concurrent/locks/ReentrantLock_Sync-stub.cpp \
	ext/stub/java/util/logging/Level-stub.cpp \
	ext/stub/java/util/logging/Level_KnownLevel-stub.cpp \
	ext/stub/java/util/logging/Logger-stub.cpp \
	ext/stub/java/util/logging/Logger_SystemLoggerHelper-stub.cpp \
	ext/stub/java/util/spi/LocaleNameProvider-stub.cpp \
	ext/stub/java/util/spi/LocaleServiceProvider-stub.cpp \
	ext/stub/java/util/zip/InflaterInputStream-stub.cpp \
	ext/stub/java/util/zip/ZipEntry-stub.cpp \
	ext/stub/java/util/zip/ZipInputStream-stub.cpp \

EXT_TINYXML_SRCS = \
	ext/tinyxml/tinystr.cpp \
	ext/tinyxml/tinyxml.cpp \
	ext/tinyxml/tinyxmlerror.cpp \
	ext/tinyxml/tinyxmlparser.cpp \

EXT_JSONBOX_SRCS = \
	ext/jsonbox/Array.cpp \
	ext/jsonbox/Convert.cpp \
	ext/jsonbox/Escaper.cpp \
	ext/jsonbox/IndentCanceller.cpp \
	ext/jsonbox/Indenter.cpp \
	ext/jsonbox/JsonException.cpp \
	ext/jsonbox/Object.cpp \
	ext/jsonbox/SolidusEscaper.cpp \
	ext/jsonbox/Value.cpp \

EXT_LIBPNG_SRCS = \
	ext/libpng/pngrio.c \
	ext/libpng/pngwio.c \
	ext/libpng/pngmem.c \
	ext/libpng/pngwtran.c \
	ext/libpng/pngtrans.c \
	ext/libpng/pngerror.c \
	ext/libpng/pngpread.c \
	ext/libpng/pngget.c \
	ext/libpng/pngset.c \
	ext/libpng/pngwrite.c \
	ext/libpng/pngwutil.c \
	ext/libpng/pngread.c \
	ext/libpng/pngrutil.c \
	ext/libpng/png.c \
	ext/libpng/pngrtran.c \

EXT_NATIVE_SRCS = \
	ext/native/java/io/FileInputStream-native.cpp \
	ext/native/java/io/FileOutputStream-native.cpp \
	ext/native/java/lang/Class-native.cpp \
	ext/native/java/lang/ClassLoader-native.cpp \
	ext/native/java/lang/ClassLoader_NativeLibrary-native.cpp \
	ext/native/java/lang/Float-native.cpp \
	ext/native/java/lang/Object-native.cpp \
	ext/native/java/lang/String-native.cpp \
	ext/native/java/lang/System-native.cpp \
	ext/native/java/lang/Thread-native.cpp \
	ext/native/java/lang/Throwable-native.cpp \
	ext/native/java/util/zip/ZipEntry-native.cpp \


MAIN_SRCS = \
	src/tdme/tests/AngleTest-main.cpp \
	src/tdme/tests/AudioTest-main.cpp \
	src/tdme/tests/EngineTest-main.cpp \
	src/tdme/tests/GUITest-main.cpp \
	src/tdme/tests/PhysicsTest1-main.cpp \
	src/tdme/tests/PhysicsTest2-main.cpp \
	src/tdme/tests/PhysicsTest3-main.cpp \
	src/tdme/tests/STLTests-main.cpp \
	src/tdme/tools/leveleditor/TDMELevelEditor-main.cpp \
	src/tdme/tools/particlesystem/TDMEParticleSystem-main.cpp \
	src/tdme/tools/viewer/TDMEViewer-main.cpp \


MAINS = $(MAIN_SRCS:$(SRC)/%-main.cpp=$(BIN)/%)
OBJS = $(SRCS:$(SRC)/%.cpp=$(OBJ)/%.o)
STUB_OBJS = $(STUB_SRCS:$(STUB)/%.cpp=$(OBJ)/%.o)
NATIVE_OBJS = $(NATIVE_SRCS:$(NATIVE)/%.cpp=$(OBJ)/%.o)

EXT_OBJS = $(EXT_SRCS:ext/$(SRC)/%.cpp=$(OBJ)/%.o)
EXT_STUB_OBJS = $(EXT_STUB_SRCS:ext/$(STUB)/%.cpp=$(OBJ)/%.o)
EXT_NATIVE_OBJS = $(EXT_NATIVE_SRCS:ext/$(NATIVE)/%.cpp=$(OBJ)/%.o)
EXT_TINYXML_OBJS = $(EXT_TINYXML_SRCS:ext/$(TINYXML)/%.cpp=$(OBJ)/%.o)
EXT_JSONBOX_OBJS = $(EXT_JSONBOX_SRCS:ext/$(JSONBOX)/%.cpp=$(OBJ)/%.o)
EXT_LIBPNG_OBJS = $(EXT_LIBPNG_SRCS:ext/$(LIBPNG)/%.c=$(OBJ)/%.o)

all: $(LIBS)

define cc-command
@mkdir -p $(dir $@); 
@echo Compile $<; $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
endef

$(OBJS):$(OBJ)/%.o: $(SRC)/%.cpp | print-opts
	$(cc-command)
	
$(STUB_OBJS):$(OBJ)/%.o: $(STUB)/%.cpp | print-opts
	$(cc-command)

$(NATIVE_OBJS):$(OBJ)/%.o: $(NATIVE)/%.cpp | print-opts
	$(cc-command)

$(EXT_OBJS):$(OBJ)/%.o: ext/$(SRC)/%.cpp | print-opts
	$(cc-command)

$(EXT_STUB_OBJS):$(OBJ)/%.o: ext/$(STUB)/%.cpp | print-opts
	$(cc-command)

$(EXT_NATIVE_OBJS):$(OBJ)/%.o: ext/$(NATIVE)/%.cpp | print-opts
	$(cc-command)

$(EXT_TINYXML_OBJS):$(OBJ)/%.o: ext/$(TINYXML)/%.cpp | print-opts
	$(cc-command)

$(EXT_JSONBOX_OBJS):$(OBJ)/%.o: ext/$(JSONBOX)/%.cpp | print-opts
	$(cc-command)

$(EXT_LIBPNG_OBJS):$(OBJ)/%.o: ext/$(LIBPNG)/%.c | print-opts
	$(cc-command)

%.a:
	@echo Archive $@
	@mkdir -p $(dir $@)
	@rm -f $@
	@ar rcs $@ $^

$(BIN)/$(LIB): $(OBJS) $(STUB_OBJS) $(NATIVE_OBJS)

$(BIN)/$(EXT_LIB): $(EXT_OBJS) $(EXT_STUB_OBJS) $(EXT_NATIVE_OBJS) $(EXT_TINYXML_OBJS) $(EXT_JSONBOX_OBJS) $(EXT_LIBPNG_OBJS)

$(MAINS):$(BIN)/%:$(SRC)/%-main.cpp $(LIBS)
	@mkdir -p $(dir $@); 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -L$(BIN) -o $@ $< -l$(NAME) $(EXTRA_LIBS)

mains: $(MAINS)

clean:
	rm -rf $(OBJ) $(BIN)

print-opts:
	@echo Building with \"$(CXX) $(CPPFLAGS) $(CXXFLAGS)\"
	
.PHONY: all mains clean print-opts

-include $(OBJS:%.o=%.d)
