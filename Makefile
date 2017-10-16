STACKFLAGS =

# set platform specific flags
OS := $(shell sh -c 'uname -s 2>/dev/null')
ifeq ($(OS), Darwin)
	INCLUDES := $(INCLUDES) -Isrc -Iext -Iext/src -I./
	EXTRA_LIBS ?= -l$(NAME)-ext -framework GLUT -framework OpenGL -framework Cocoa -framework Carbon -framework OpenAL -pthread
else ifeq ($(OS), Linux)
	INCLUDES := $(INCLUDES) -Isrc -Iext -Iext/src -I./
	EXTRA_LIBS ?= -ltdme -l$(NAME)-ext -ltdme -ltdme-ext -L/usr/lib64 -lGL -lglut -lopenal -pthread
	#GL2ES on ARM, WIP
	#EXTRA_LIBS ?= -ltdme -l$(NAME)-ext -ltdme -ltdme-ext -L/usr/lib64 -L/usr/local/lib -lGL -lfreeglut-gles -lopenal -pthread 
else
	# Win-MINGW, WIP
	INCLUDES := $(INCLUDES) -Isrc -Iext -Iext/src -I. -Iext/glew/include -Iext/openal-soft/include -Iext/freeglut/include
	EXTRA_LIBS ?= -Lext\glew\bin\Release\x64 -lglew32 -lopengl32 -Lext/freeglut/lib/x64 -lfreeglut -Lext/openal-soft/libs/Win64/ -lOpenAL32 -l$(NAME) -l$(NAME)-ext
	STACKFLAGS := -Wl,--stack,8388608
endif

CPPFLAGS := $(CPPFLAGS) $(INCLUDES)
CFLAGS := $(CFLAGS) -g -pipe -MMD -MP
#CFLAGS := $(CFLAGS) -O3 -pipe -MMD -MP
CXXFLAGS := $(CFLAGS) -std=gnu++11

BIN := bin
OBJ := obj

NAME := tdme

LIB = lib$(NAME).a
EXT_LIB = lib$(NAME)-ext.a

LIBS = $(BIN)/$(LIB) $(BIN)/$(EXT_LIB)

SRC = src
TINYXML = tinyxml
JSONBOX = jsonbox
ZLIB = zlib
LIBPNG = libpng
VORBIS = vorbis
OGG = ogg

SRCS = \
	src/tdme/audio/Audio.cpp \
	src/tdme/audio/AudioBufferManager.cpp \
	src/tdme/audio/AudioBufferManager_AudioBufferManaged.cpp \
	src/tdme/audio/AudioEntity.cpp \
	src/tdme/audio/AudioStream.cpp \
	src/tdme/audio/Sound.cpp \
	src/tdme/audio/decoder/AudioDecoder.cpp \
	src/tdme/audio/decoder/AudioDecoderException.cpp \
	src/tdme/audio/decoder/VorbisDecoder.cpp \
	src/tdme/engine/Application.cpp \
	src/tdme/engine/ApplicationInputEventsHandler.cpp \
	src/tdme/engine/Camera.cpp \
	src/tdme/engine/Engine.cpp \
	src/tdme/engine/EngineGL3Renderer.cpp \
	src/tdme/engine/EngineGL2Renderer.cpp \
	src/tdme/engine/FrameBuffer.cpp \
	src/tdme/engine/Frustum.cpp \
	src/tdme/engine/Light.cpp \
	src/tdme/engine/Object3D.cpp \
	src/tdme/engine/Object3DModel.cpp \
	src/tdme/engine/ObjectParticleSystemEntity.cpp \
	src/tdme/engine/PartitionNone.cpp \
	src/tdme/engine/PartitionOctTree.cpp \
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
	src/tdme/engine/physics/ConstraintsSolver.cpp \
	src/tdme/engine/physics/PhysicsPartitionNone.cpp \
	src/tdme/engine/physics/PhysicsPartitionOctTree.cpp \
	src/tdme/engine/physics/RigidBody.cpp \
	src/tdme/engine/physics/World.cpp \
	src/tdme/engine/primitives/BoundingBox.cpp \
	src/tdme/engine/primitives/Capsule.cpp \
	src/tdme/engine/primitives/ConvexMesh.cpp \
	src/tdme/engine/primitives/LineSegment.cpp \
	src/tdme/engine/primitives/OrientedBoundingBox.cpp \
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
	src/tdme/engine/subsystems/object/BatchVBORendererPoints.cpp \
	src/tdme/engine/subsystems/object/BatchVBORendererTriangles.cpp \
	src/tdme/engine/subsystems/object/ModelUtilitiesInternal.cpp \
	src/tdme/engine/subsystems/object/Object3DBase.cpp \
	src/tdme/engine/subsystems/object/Object3DBase_TransformedFacesIterator.cpp \
	src/tdme/engine/subsystems/object/Object3DGroup.cpp \
	src/tdme/engine/subsystems/object/Object3DGroupMesh.cpp \
	src/tdme/engine/subsystems/object/Object3DGroupVBORenderer.cpp \
	src/tdme/engine/subsystems/object/Object3DInternal.cpp \
	src/tdme/engine/subsystems/object/Object3DModelInternal.cpp \
	src/tdme/engine/subsystems/object/Object3DVBORenderer.cpp \
	src/tdme/engine/subsystems/object/Object3DVBORenderer_TransparentRenderFacesGroupPool.cpp \
	src/tdme/engine/subsystems/object/ObjectBuffer.cpp \
	src/tdme/engine/subsystems/object/TransparentRenderFacesGroup.cpp \
	src/tdme/engine/subsystems/object/TransparentRenderFacesPool.cpp \
	src/tdme/engine/subsystems/object/TransparentRenderFacesPool_TransparentRenderFacesPool.cpp \
	src/tdme/engine/subsystems/object/TransparentRenderPointsPool.cpp \
	src/tdme/engine/subsystems/particlesystem/BoundingBoxParticleEmitter.cpp \
	src/tdme/engine/subsystems/particlesystem/CircleParticleEmitter.cpp \
	src/tdme/engine/subsystems/particlesystem/CircleParticleEmitterPlaneVelocity.cpp \
	src/tdme/engine/subsystems/particlesystem/ObjectParticleSystemEntityInternal.cpp \
	src/tdme/engine/subsystems/particlesystem/ParticlesShader.cpp \
	src/tdme/engine/subsystems/particlesystem/PointParticleEmitter.cpp \
	src/tdme/engine/subsystems/particlesystem/PointsParticleSystemEntityInternal.cpp \
	src/tdme/engine/subsystems/particlesystem/SphereParticleEmitter.cpp \
	src/tdme/engine/subsystems/renderer/GL3Renderer.cpp \
	src/tdme/engine/subsystems/renderer/GL2Renderer.cpp \
	src/tdme/engine/subsystems/renderer/GLRenderer.cpp \
	src/tdme/engine/subsystems/shadowmapping/ShadowMap.cpp \
	src/tdme/engine/subsystems/shadowmapping/ShadowMapping.cpp \
	src/tdme/engine/subsystems/shadowmapping/ShadowMappingShaderPre.cpp \
	src/tdme/engine/subsystems/shadowmapping/ShadowMappingShaderRender.cpp \
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
	src/tdme/gui/events/GUIActionListener_Type.cpp \
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
	src/tdme/math/TriangleTriangleIntersection.cpp \
	src/tdme/os/filesystem/FileSystem.cpp \
	src/tdme/os/filesystem/FileSystemException.cpp \
	src/tdme/os/filesystem/StandardFileSystem.cpp \
	src/tdme/os/threading/Barrier.cpp \
	src/tdme/os/threading/Condition.cpp \
	src/tdme/os/threading/Mutex.cpp \
	src/tdme/os/threading/ReadWriteLock.cpp \
	src/tdme/os/threading/Thread.cpp \
	src/tdme/tests/AngleTest.cpp \
	src/tdme/tests/AudioTest.cpp \
	src/tdme/tests/EngineTest.cpp \
	src/tdme/tests/GUITest.cpp \
	src/tdme/tests/GUITest_init_1.cpp \
	src/tdme/tests/GUITest_init_2.cpp \
	src/tdme/tests/PhysicsTest1.cpp \
	src/tdme/tests/PhysicsTest2.cpp \
	src/tdme/tests/PhysicsTest3.cpp \
	src/tdme/tests/ThreadingTest_ConsumerThread.cpp \
	src/tdme/tests/ThreadingTest_ProducerThread.cpp \
	src/tdme/tests/ThreadingTest_TestThread.cpp \
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
	src/tdme/tools/viewer/TDMEViewer.cpp \
	src/tdme/utils/Character.cpp \
	src/tdme/utils/Enum.cpp \
	src/tdme/utils/Float.cpp \
	src/tdme/utils/Integer.cpp \
	src/tdme/utils/MutableString.cpp \
	src/tdme/utils/Properties.cpp \
	src/tdme/utils/StringConverter.cpp \
	src/tdme/utils/StringUtils.cpp \
	src/tdme/utils/StringTokenizer.cpp \
	src/tdme/utils/ExceptionBase.cpp \
	src/tdme/utils/Console.cpp \
	# src/tdme/engine/EngineGLES2Renderer.cpp \
	# src/tdme/engine/subsystems/renderer/GLES2Renderer.cpp \

EXT_SRCS = \

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

EXT_ZLIB_SRCS = \
	ext/zlib/adler32.c \
	ext/zlib/crc32.c \
	ext/zlib/deflate.c \
	ext/zlib/infback.c \
	ext/zlib/inffast.c \
	ext/zlib/inflate.c \
	ext/zlib/inftrees.c \
	ext/zlib/trees.c \
	ext/zlib/zutil.c \
	ext/zlib/compress.c \
	ext/zlib/uncompr.c \
	ext/zlib/gzclose.c \
	ext/zlib/gzlib.c \
	ext/zlib/gzread.c \
	ext/zlib/gzwrite.c  \

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

EXT_VORBIS_SRCS = \
	ext/vorbis/analysis.c \
	ext/vorbis/barkmel.c \
	ext/vorbis/bitrate.c \
	ext/vorbis/block.c \
	ext/vorbis/codebook.c \
	ext/vorbis/envelope.c \
	ext/vorbis/floor0.c \
	ext/vorbis/floor1.c \
	ext/vorbis/info.c \
	ext/vorbis/lookup.c \
	ext/vorbis/lpc.c \
	ext/vorbis/lsp.c \
	ext/vorbis/mapping0.c \
	ext/vorbis/mdct.c \
	ext/vorbis/misc.c \
	ext/vorbis/psy.c \
	ext/vorbis/registry.c \
	ext/vorbis/res0.c \
	ext/vorbis/sharedbook.c \
	ext/vorbis/smallft.c \
	ext/vorbis/synthesis.c \
	ext/vorbis/tone.c \
	ext/vorbis/vorbisenc.c \
	ext/vorbis/vorbisfile.c \
	ext/vorbis/window.c \

EXT_OGG_SRCS = \
	ext/ogg/bitwise.c \
	ext/ogg/framing.c \

MAIN_SRCS = \
	src/tdme/tests/AngleTest-main.cpp \
	src/tdme/tests/AudioTest-main.cpp \
	src/tdme/tests/EngineTest-main.cpp \
	src/tdme/tests/GUITest-main.cpp \
	src/tdme/tests/PhysicsTest1-main.cpp \
	src/tdme/tests/PhysicsTest2-main.cpp \
	src/tdme/tests/PhysicsTest3-main.cpp \
	src/tdme/tests/DAETests-main.cpp \
	src/tdme/tests/ThreadingTest-main.cpp \
	src/tdme/tools/leveleditor/TDMELevelEditor-main.cpp \
	src/tdme/tools/particlesystem/TDMEParticleSystem-main.cpp \
	src/tdme/tools/viewer/TDMEViewer-main.cpp \


MAINS = $(MAIN_SRCS:$(SRC)/%-main.cpp=$(BIN)/%)
OBJS = $(SRCS:$(SRC)/%.cpp=$(OBJ)/%.o)

EXT_OBJS = $(EXT_SRCS:ext/$(SRC)/%.cpp=$(OBJ)/%.o)
EXT_TINYXML_OBJS = $(EXT_TINYXML_SRCS:ext/$(TINYXML)/%.cpp=$(OBJ)/%.o)
EXT_JSONBOX_OBJS = $(EXT_JSONBOX_SRCS:ext/$(JSONBOX)/%.cpp=$(OBJ)/%.o)
EXT_ZLIB_OBJS = $(EXT_ZLIB_SRCS:ext/$(ZLIB)/%.c=$(OBJ)/%.o)
EXT_LIBPNG_OBJS = $(EXT_LIBPNG_SRCS:ext/$(LIBPNG)/%.c=$(OBJ)/%.o)
EXT_VORBIS_OBJS = $(EXT_VORBIS_SRCS:ext/$(VORBIS)/%.c=$(OBJ)/%.o)
EXT_OGG_OBJS = $(EXT_OGG_SRCS:ext/$(OGG)/%.c=$(OBJ)/%.o)

all: $(LIBS)

define cpp-command
@mkdir -p $(dir $@); 
@echo Compile $<; $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
endef

define c-command
@mkdir -p $(dir $@); 
@echo Compile $<; $(CXX) -x c $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
endef

$(OBJS):$(OBJ)/%.o: $(SRC)/%.cpp | print-opts
	$(cpp-command)

$(EXT_OBJS):$(OBJ)/%.o: ext/$(SRC)/%.cpp | print-opts
	$(cpp-command)

$(EXT_TINYXML_OBJS):$(OBJ)/%.o: ext/$(TINYXML)/%.cpp | print-opts
	$(cpp-command)

$(EXT_JSONBOX_OBJS):$(OBJ)/%.o: ext/$(JSONBOX)/%.cpp | print-opts
	$(cpp-command)

$(EXT_ZLIB_OBJS):$(OBJ)/%.o: ext/$(ZLIB)/%.c | print-opts
	$(c-command)

$(EXT_LIBPNG_OBJS):$(OBJ)/%.o: ext/$(LIBPNG)/%.c | print-opts
	$(c-command)

$(EXT_VORBIS_OBJS):$(OBJ)/%.o: ext/$(VORBIS)/%.c | print-opts
	$(c-command)

$(EXT_OGG_OBJS):$(OBJ)/%.o: ext/$(OGG)/%.c | print-opts
	$(c-command)

%.a:
	@echo Archive $@
	@mkdir -p $(dir $@)
	@rm -f $@
	@ar rcs $@ $^

$(BIN)/$(LIB): $(OBJS)

$(BIN)/$(EXT_LIB): $(EXT_OBJS) $(EXT_TINYXML_OBJS) $(EXT_JSONBOX_OBJS) $(EXT_ZLIB_OBJS) $(EXT_LIBPNG_OBJS) $(EXT_VORBIS_OBJS) $(EXT_OGG_OBJS)

$(MAINS):$(BIN)/%:$(SRC)/%-main.cpp $(LIBS)
	@mkdir -p $(dir $@); 
	$(CXX) $(STACKFLAGS) $(CPPFLAGS) $(CXXFLAGS) -L$(BIN) -o $@ $< -l$(NAME) $(EXTRA_LIBS)

mains: $(MAINS)

clean:
	rm -rf $(OBJ) $(BIN)

print-opts:
	@echo Building with \"$(CXX) $(CPPFLAGS) $(CXXFLAGS)\"
	
.PHONY: all mains clean print-opts

-include $(OBJS:%.o=%.d)
