#
BIN = bin
LIB_DIR = lib
OBJ := obj
OBJ_DEBUG = obj-debug

# determine platform
OSSHORT := $(shell sh -c 'uname -o 2>/dev/null')
OS := $(shell sh -c 'uname -s 2>/dev/null')
MACHINE := $(shell sh -c 'uname -m 2>/dev/null')

#
NAME = tdme2
EXT_NAME = tdme2-ext
YANNET_NAME = yannet
MINITSCRIPT_NAME = minitscript
ifeq ($(OS), Darwin)
	LIB_EXT = .dylib
else ifeq ($(OSSHORT), Msys)
	LIB_EXT = .dll
else
	LIB_EXT = .so
endif
LIB := lib$(NAME)$(LIB_EXT)
EXT_LIB := lib$(NAME)-ext$(LIB_EXT)
YANNET_LIB  := libyannet$(LIB_EXT)
MINITSCRIPT_LIB  := libminitscript$(LIB_EXT)
OPENGL2_RENDERER_LIB := libopengl2renderer$(LIB_EXT)
OPENGL3CORE_RENDERER_LIB := libopengl3corerenderer$(LIB_EXT)
VULKAN_RENDERER_LIB := libvulkanrenderer$(LIB_EXT)
OPENGLES2_RENDERER_LIB := libopengles2renderer$(LIB_EXT)
VULKAN_RENDERER_LDFLAGS =
LIBS_LDFLAGS =
MAIN_LDFLAGS =
LDFLAG_LIB := $(NAME)
LDFLAG_EXT_LIB := $(EXT_NAME)
LDFLAG_YANNET_LIB := $(YANNET_NAME)
LDFLAG_MINITSCRIPT_LIB := $(MINITSCRIPT_NAME)

SUBDIRS := $(MINITSCRIPT_NAME) $(YANNET_NAME)

#
SRCS_PLATFORM =

#
CPPVERSION = -std=c++2a
OFLAGS =
EXTRAFLAGS = -DRAPIDJSON_HAS_STDSTRING
INCLUDES = -Isrc -Iext -I. -Iext/reactphysics3d/include/ -Iext/vhacd/include/ -Iext/cpp-spline/src -Iext/zlib -Iext/minitscript/src -Iext/yannet/src

#
CXX := $(CXX) -fPIC

# set platform specific flags
ifeq ($(OS), Darwin)
	# MacOSX
	EXTRAFLAGS := $(EXTRAFLAGS) -DHAVE_UNISTD_H
	OPENGL_RENDERER_LDFLAGS := -framework Cocoa -framework IOKit -framework Carbon -framework OpenGL -framework OpenCL
	VULKAN_RENDERER_LDFLAGS := -framework Cocoa -framework IOKit -framework Carbon -lvulkan.1
	OPENGLES2_RENDERER_LDFLAGS := -framework Cocoa -framework IOKit -framework Carbon -framework OpenGL -framework OpenCL
	ifeq ($(MACHINE), x86_64)
		SRCS_PLATFORM := $(SRCS_PLATFORM) \
			src/tdme/engine/fileio/models/FBXReader.cpp \
			src/tdme/engine/fileio/models/ModelReaderFBX.cpp
		INCLUDES := $(INCLUDES) -Iext/fbx/macosx/include -Iext/glfw3/include -Iext/freetype/include
		LIBS_LDFLAGS := -framework Cocoa -framework IOKit -framework Carbon -framework OpenAL -Lext/glfw3/lib/macosx/x64 -lglfw.3  -Lext/freetype/lib/macosx/x64 -lfreetype.6 -Lext/fbx/macosx/lib -lfbxsdk -lssl -lcrypto
		OPENGL_RENDERER_LDFLAGS := $(OPENGL_RENDERER_LDFLAGS) -Lext/glfw3/lib/macosx/x64 -lglfw.3
		VULKAN_RENDERER_LDFLAGS := $(VULKAN_RENDERER_LDFLAGS) -Lext/glfw3/lib/macosx/x64 -lglfw.3
		OPENGLES2_RENDERER_LDFLAGS := $(OPENGLES2_RENDERER_LDFLAGS) -Lext/glfw3/lib/macosx/x64 -lglfw.3
	else ifeq ($(MACHINE), arm64)
		SRCS_PLATFORM := $(SRCS_PLATFORM) \
			src/tdme/engine/fileio/models/ModelReader.cpp
		INCLUDES := $(INCLUDES) -Iext/glfw3/include -Iext/freetype/include
		LIBS_LDFLAGS := -framework Cocoa -framework IOKit -framework Carbon -framework OpenAL -Lext/glfw3/lib/macosx/arm64 -lglfw.3  -Lext/freetype/lib/macosx/arm64 -lfreetype.6 -lssl -lcrypto
		OPENGL_RENDERER_LDFLAGS := $(OPENGL_RENDERER_LDFLAGS) -Lext/glfw3/lib/macosx/arm64 -lglfw.3
		VULKAN_RENDERER_LDFLAGS := $(VULKAN_RENDERER_LDFLAGS) -Lext/glfw3/lib/macosx/arm64 -lglfw.3
		OPENGLES2_RENDERER_LDFLAGS := $(OPENGLES2_RENDERER_LDFLAGS) -Lext/glfw3/lib/macosx/arm64 -lglfw.3
	endif
	OFLAGS := -O3
else ifeq ($(OS), FreeBSD)
	# FreeBSD
	SRCS_PLATFORM := $(SRCS_PLATFORM) \
		src/tdme/engine/fileio/models/ModelReader.cpp
	INCLUDES := $(INCLUDES) -I/usr/local/include -I/usr/local/include/freetype2
	OPENGL_RENDERER_LDFLAGS := -L/usr/local/lib -lGLEW -lGL -lglfw
	VULKAN_RENDERER_LDFLAGS := -L/usr/local/lib -lvulkan -lglfw
	OPENGLES2_RENDERER_LDFLAGS := -L/usr/local/lib -lGLESv2 -lEGL -lglfw
	LIBS_LDFLAGS := -L/usr/local/lib -ldl -lglfw -lopenal -lexecinfo -lssl -lcrypto
	OFLAGS := -O3
else ifeq ($(OS), NetBSD)
	# NetBSD
	SRCS_PLATFORM := $(SRCS_PLATFORM) \
		src/tdme/engine/fileio/models/ModelReader.cpp
	INCLUDES := $(INCLUDES) -I/usr/X11R7/include -I/usr/pkg/include -I/usr/pkg/include/freetype2
	OPENGL_RENDERER_LDFLAGS := -L/usr/X11R7/lib -L/usr/pkg/lib -lGLEW -lGL -lglfw
	VULKAN_RENDERER_LDFLAGS := -L/usr/X11R7/lib -L/usr/pkg/lib -lvulkan -lglfw
	OPENGLES2_RENDERER_LDFLAGS := -L/usr/X11R7/lib -L/usr/pkg/lib -lGLESv2 -lEGL -lglfw
	LIBS_LDFLAGS := -L/usr/X11R7/lib -L/usr/pkg/lib -lglfw -lopenal -lexecinfo -lfreetype -lssl -lcrypto
	OFLAGS := -O3
else ifeq ($(OS), OpenBSD)
	# OpenBSD
	SRCS_PLATFORM := $(SRCS_PLATFORM) \
		src/tdme/engine/fileio/models/ModelReader.cpp
	INCLUDES := $(INCLUDES) -I/usr/X11R6/include -I/usr/local/include -I/usr/local/include/freetype2
	OPENGL_RENDERER_LDFLAGS := -L/usr/X11R6/lib -L/usr/local/lib -lm -lstdc++ -lGLEW -lGL -lglfw
	VULKAN_RENDERER_LDFLAGS := -L/usr/X11R6/lib -L/usr/local/lib -lm -lstdc++ -lvulkan -lglfw
	OPENGLES2_RENDERER_LDFLAGS := -L/usr/X11R6/lib -L/usr/local/lib -lm -lstdc++ -lGLESv2 -lEGL -lglfw
	LIBS_LDFLAGS := -L/usr/X11R6/lib -L/usr/local/lib -lm -lstdc++ -ldl -lglfw -lopenal -lssl -lcrypto
	OFLAGS := -O3
else ifeq ($(OS), Haiku)
	# Haiku
	SRCS_PLATFORM := $(SRCS_PLATFORM) \
		src/tdme/engine/fileio/models/ModelReader.cpp
	INCLUDES := $(INCLUDES) -I/boot/system/develop/headers -I/boot/system/develop/headers/freetype2
	OPENGL_RENDERER_LDFLAGS := -lGLEW -lGL -lglfw
	VULKAN_RENDERER_LDFLAGS := -lvulkan -lglfw
	OPENGLES2_RENDERER_LDFLAGS := -lGLESv2 -lEGL -lglfw
	LIBS_LDFLAGS := -lnetwork -lglfw -lopenal -lfreetype -lssl -lcrypto
	OFLAGS := -O3
else ifeq ($(OS), Linux)
	# Linux
	INCLUDES := $(INCLUDES) -I/usr/include/freetype2
	OPENGL_RENDERER_LDFLAGS := -L/usr/lib64 -lGLEW -lGL -lglfw
	VULKAN_RENDERER_LDFLAGS := -L/usr/lib64 -lvulkan -lglfw
	OPENGLES2_RENDERER_LDFLAGS := -L/usr/lib64 -lGLESv2 -lEGL -lglfw
	LIBS_LDFLAGS := -L/usr/lib64 -ldl -lglfw -lopenal -lfreetype -lssl -lcrypto
	OFLAGS := -O3
	ifeq ($(MACHINE), x86_64)
		SRCS_PLATFORM := $(SRCS_PLATFORM) \
			src/tdme/engine/fileio/models/FBXReader.cpp \
			src/tdme/engine/fileio/models/ModelReaderFBX.cpp
		INCLUDES := $(INCLUDES) -Iext/fbx/linux/include
		LIBS_LDFLAGS := $(LIBS_LDFLAGS) -Lext/fbx/linux/lib -lfbxsdk -lxml2
	else
		SRCS_PLATFORM := $(SRCS_PLATFORM) \
			src/tdme/engine/fileio/models/ModelReader.cpp
	endif
else
	# Windows
	SRCS_PLATFORM:= $(SRCS_PLATFORM) \
		src/tdme/engine/fileio/models/ModelReader.cpp
	# TODO: No console flags: -Wl,-subsystem,windows
	EXTRAFLAGS := $(EXTRAFLAGS)
	#-D_GLIBCXX_DEBUG
	INCLUDES := $(INCLUDES) -I/mingw64/include -I/mingw64/include/freetype2
	OPENGL_RENDERER_LDFLAGS := -L/mingw64/lib -lglfw3 -lglew32 -lopengl32
	VULKAN_RENDERER_LDFLAGS := -L/mingw64/lib -lglfw3 -Lext/vulkan/runtime/mingw64 -lvulkan-1
	LIBS_LDFLAGS := -L/mingw64/lib -lws2_32 -ldl -lglfw3 -lopenal -lfreetype -ldbghelp -lssl -lcrypto
	LDFLAG_LIB := $(NAME)$(LIB_EXT)
	LDFLAG_EXT_LIB := $(EXT_NAME)$(LIB_EXT)
	LDFLAG_YANNET_LIB := $(YANNET_NAME)$(LIB_EXT)
	LDFLAG_MINITSCRIPT_LIB := $(MINITSCRIPT_NAME)$(LIB_EXT)
	OFLAGS := -O3
endif

CPPFLAGS := $(INCLUDES)
CFLAGS := -g $(OFLAGS) $(EXTRAFLAGS) -pipe -MMD -MP -DNDEBUG
#CFLAGS := -g $(OFLAGS) $(EXTRAFLAGS) -pipe -MMD -MP
#CFLAGS := $(OFLAGS) $(EXTRAFLAGS) -pipe -MMD -MP -DNDEBUG
CFLAGS_EXT_RP3D := -g $(OFLAGS) -pipe -MMD -MP -DNDEBUG
#CFLAGS_EXT_RP3D := -g $(OFLAGS) -pipe -MMD -MP
#CFLAGS_EXT_RP3D := $(OFLAGS) -pipe -MMD -MP -DNDEBUG
CFLAGS_DEBUG := -g -pipe -MMD -MP
CXXFLAGS := $(CFLAGS) $(CPPVERSION)
CXXFLAGS_DEBUG := $(CFLAGS_DEBUG) $(CPPVERSION)
CXXFLAGS_EXT_RP3D = $(CFLAGS_EXT_RP3D) $(CPPVERSION)

LIBS := $(LIB_DIR)/$(LIB) $(LIB_DIR)/$(EXT_LIB)
ifneq ($(OS), Darwin)
	LIBS:= $(LIBS) $(LIB_DIR)/$(OPENGL2_RENDERER_LIB)
endif
LIBS := $(LIBS) $(LIB_DIR)/$(OPENGL3CORE_RENDERER_LIB)
ifeq ($(VULKAN), YES)
	LIBS:= $(LIBS) $(LIB_DIR)/$(VULKAN_RENDERER_LIB)
endif
ifeq ($(GLES2), YES)
	LIBS:= $(LIBS) $(LIB_DIR)/$(OPENGLES2_RENDERER_LIB)
endif 

# subdirs
LIBS:= $(LIBS) make-subdirs

SRC = src
TINYXML = tinyxml
ZLIB = zlib
LIBPNG = libpng
VORBIS = vorbis
OGG = ogg
REACTPHYSICS3D = reactphysics3d
SPIRV = vulkan/spirv
GLSLANG = vulkan/glslang
OGLCOMPILERSDLL = vulkan/OGLCompilersDLL
VMA = vulkan/vma
CPPSPLINE = cpp-spline
BC7 = bc7enc_rdo

SRCS_DEBUG =

SRCS = \
	src/tdme/audio/Audio.cpp \
	src/tdme/audio/AudioBufferManager.cpp \
	src/tdme/audio/AudioStream.cpp \
	src/tdme/audio/PacketAudioStream.cpp \
	src/tdme/audio/VorbisAudioStream.cpp \
	src/tdme/audio/Sound.cpp \
	src/tdme/audio/decoder/AudioDecoderException.cpp \
	src/tdme/audio/decoder/VorbisDecoder.cpp \
	src/tdme/application/Application.cpp \
	src/tdme/engine/Camera.cpp \
	src/tdme/engine/ColorTextureCanvas.cpp \
	src/tdme/engine/Decal.cpp \
	src/tdme/engine/DynamicColorTexture.cpp \
	src/tdme/engine/Engine.cpp \
	src/tdme/engine/EntityHierarchy.cpp \
	src/tdme/engine/EntityShaderParameters.cpp \
	src/tdme/engine/EnvironmentMapping.cpp \
	src/tdme/engine/FogParticleSystem.cpp \
	src/tdme/engine/FrameBuffer.cpp \
	src/tdme/engine/Frustum.cpp \
	src/tdme/engine/GeometryBuffer.cpp \
	src/tdme/engine/ImposterObject.cpp \
	src/tdme/engine/Light.cpp \
	src/tdme/engine/Lines.cpp \
	src/tdme/engine/LODObject.cpp \
	src/tdme/engine/LODObjectImposter.cpp \
	src/tdme/engine/Object.cpp \
	src/tdme/engine/ObjectModel.cpp \
	src/tdme/engine/ObjectRenderGroup.cpp \
	src/tdme/engine/ObjectParticleSystem.cpp \
	src/tdme/engine/OctTreePartition.cpp \
	src/tdme/engine/ParticleSystemGroup.cpp \
	src/tdme/engine/PointsParticleSystem.cpp \
	src/tdme/engine/Rotation.cpp \
	src/tdme/engine/SceneConnector.cpp \
	src/tdme/engine/SimplePartition.cpp \
	src/tdme/engine/Texture.cpp \
	src/tdme/engine/Timing.cpp \
	src/tdme/engine/Transform.cpp \
	src/tdme/engine/Version.cpp \
	src/tdme/engine/fileio/models/DAEReader.cpp \
	src/tdme/engine/fileio/models/GLTFReader.cpp \
	src/tdme/engine/fileio/models/ModelFileIOException.cpp \
	src/tdme/engine/fileio/models/TMReader.cpp \
	src/tdme/engine/fileio/models/TMWriter.cpp \
	src/tdme/engine/fileio/models/WFObjWriter.cpp \
	src/tdme/engine/fileio/prototypes/PrototypeWriter.cpp \
	src/tdme/engine/fileio/prototypes/PrototypeReader.cpp \
	src/tdme/engine/fileio/scenes/SceneWriter.cpp \
	src/tdme/engine/fileio/scenes/SceneReader.cpp \
	src/tdme/engine/fileio/textures/BC7TextureReader.cpp \
	src/tdme/engine/fileio/textures/BC7TextureWriter.cpp \
	src/tdme/engine/fileio/textures/PNGTextureReader.cpp \
	src/tdme/engine/fileio/textures/PNGTextureWriter.cpp \
	src/tdme/engine/fileio/textures/TextureReader.cpp \
	src/tdme/engine/logics/ApplicationClient.cpp \
	src/tdme/engine/logics/ApplicationServer.cpp \
	src/tdme/engine/logics/ApplicationServerClient.cpp \
	src/tdme/engine/logics/Context.cpp \
	src/tdme/engine/logics/Logic.cpp \
	src/tdme/engine/logics/LogicMinitScript.cpp \
	src/tdme/engine/logics/NetworkLogic.cpp \
	src/tdme/engine/logics/ServerThread.cpp \
	src/tdme/engine/model/Animation.cpp \
	src/tdme/engine/model/AnimationSetup.cpp \
	src/tdme/engine/model/Face.cpp \
	src/tdme/engine/model/FacesEntity.cpp \
	src/tdme/engine/model/Node.cpp \
	src/tdme/engine/model/Joint.cpp \
	src/tdme/engine/model/JointWeight.cpp \
	src/tdme/engine/model/Material.cpp \
	src/tdme/engine/model/Model.cpp \
	src/tdme/engine/model/PBRMaterialProperties.cpp \
	src/tdme/engine/model/UpVector.cpp \
	src/tdme/engine/model/RotationOrder.cpp \
	src/tdme/engine/model/Skinning.cpp \
	src/tdme/engine/model/ShaderModel.cpp \
	src/tdme/engine/model/SpecularMaterialProperties.cpp \
	src/tdme/engine/physics/Body.cpp \
	src/tdme/engine/physics/BodyHierarchy.cpp \
	src/tdme/engine/physics/World.cpp \
	src/tdme/engine/primitives/BoundingBox.cpp \
	src/tdme/engine/primitives/BoundingVolume.cpp \
	src/tdme/engine/primitives/Capsule.cpp \
	src/tdme/engine/primitives/ConvexMesh.cpp \
	src/tdme/engine/primitives/HeightMap.cpp \
	src/tdme/engine/primitives/LineSegment.cpp \
	src/tdme/engine/primitives/OrientedBoundingBox.cpp \
	src/tdme/engine/primitives/Sphere.cpp \
	src/tdme/engine/primitives/TerrainMesh.cpp \
	src/tdme/engine/primitives/Triangle.cpp \
	src/tdme/engine/prototype/BaseProperties.cpp \
	src/tdme/engine/prototype/BaseProperty.cpp \
	src/tdme/engine/prototype/Prototype.cpp \
	src/tdme/engine/prototype/PrototypeAudio.cpp \
	src/tdme/engine/prototype/PrototypeBoundingVolume.cpp \
	src/tdme/engine/prototype/PrototypeDecal.cpp \
	src/tdme/engine/prototype/PrototypeImposterLOD.cpp \
	src/tdme/engine/prototype/PrototypeLODLevel.cpp \
	src/tdme/engine/prototype/PrototypeParticleSystem.cpp \
	src/tdme/engine/prototype/PrototypeParticleSystem_BoundingBoxParticleEmitter.cpp \
	src/tdme/engine/prototype/PrototypeParticleSystem_CircleParticleEmitter.cpp \
	src/tdme/engine/prototype/PrototypeParticleSystem_CircleParticleEmitterPlaneVelocity.cpp \
	src/tdme/engine/prototype/PrototypeParticleSystem_Emitter.cpp \
	src/tdme/engine/prototype/PrototypeParticleSystem_FogParticleSystem.cpp \
	src/tdme/engine/prototype/PrototypeParticleSystem_ObjectParticleSystem.cpp \
	src/tdme/engine/prototype/PrototypeParticleSystem_PointParticleEmitter.cpp \
	src/tdme/engine/prototype/PrototypeParticleSystem_PointParticleSystem.cpp \
	src/tdme/engine/prototype/PrototypeParticleSystem_SphereParticleEmitter.cpp \
	src/tdme/engine/prototype/PrototypeParticleSystem_Type.cpp \
	src/tdme/engine/prototype/PrototypePhysics.cpp \
	src/tdme/engine/prototype/PrototypePhysics_BodyType.cpp \
	src/tdme/engine/prototype/Prototype_Type.cpp \
	src/tdme/engine/scene/Scene.cpp \
	src/tdme/engine/scene/SceneEntity.cpp \
	src/tdme/engine/scene/SceneLibrary.cpp \
	src/tdme/engine/scene/SceneLight.cpp \
	src/tdme/engine/scene/ScenePropertyPresets.cpp \
	src/tdme/engine/subsystems/decals/DecalInternal.cpp \
	src/tdme/engine/subsystems/environmentmapping/EnvironmentMappingRenderer.cpp \
	src/tdme/engine/subsystems/framebuffer/BRDFLUTShader.cpp \
	src/tdme/engine/subsystems/framebuffer/DeferredLightingRenderShader.cpp \
	src/tdme/engine/subsystems/framebuffer/FrameBufferRenderShader.cpp \
	src/tdme/engine/subsystems/framebuffer/SkyRenderShader.cpp \
	src/tdme/engine/subsystems/lighting/DeferredLightingShaderDefaultImplementation.cpp \
	src/tdme/engine/subsystems/lighting/DeferredLightingShaderFoliageImplementation.cpp \
	src/tdme/engine/subsystems/lighting/DeferredLightingShaderPBRDefaultImplementation.cpp \
	src/tdme/engine/subsystems/lighting/DeferredLightingShaderPBRFoliageImplementation.cpp \
	src/tdme/engine/subsystems/lighting/DeferredLightingShaderPBRTreeImplementation.cpp \
	src/tdme/engine/subsystems/lighting/DeferredLightingShaderSolidImplementation.cpp \
	src/tdme/engine/subsystems/lighting/DeferredLightingShaderTerrainImplementation.cpp \
	src/tdme/engine/subsystems/lighting/DeferredLightingShaderTreeImplementation.cpp \
	src/tdme/engine/subsystems/lighting/LightingShader.cpp \
	src/tdme/engine/subsystems/lighting/LightingShaderBaseImplementation.cpp \
	src/tdme/engine/subsystems/lighting/LightingShaderDefaultImplementation.cpp \
	src/tdme/engine/subsystems/lighting/LightingShaderFoliageImplementation.cpp \
	src/tdme/engine/subsystems/lighting/LightingShaderLightScatteringDefaultImplementation.cpp \
	src/tdme/engine/subsystems/lighting/LightingShaderLightScatteringFoliageImplementation.cpp \
	src/tdme/engine/subsystems/lighting/LightingShaderLightScatteringTreeImplementation.cpp \
	src/tdme/engine/subsystems/lighting/LightingShaderPBRBaseImplementation.cpp \
	src/tdme/engine/subsystems/lighting/LightingShaderPBRDefaultImplementation.cpp \
	src/tdme/engine/subsystems/lighting/LightingShaderPBRFoliageImplementation.cpp \
	src/tdme/engine/subsystems/lighting/LightingShaderPBRTreeImplementation.cpp \
	src/tdme/engine/subsystems/lighting/LightingShaderSolidImplementation.cpp \
	src/tdme/engine/subsystems/lighting/LightingShaderTerrainEditorImplementation.cpp \
	src/tdme/engine/subsystems/lighting/LightingShaderTerrainImplementation.cpp \
	src/tdme/engine/subsystems/lighting/LightingShaderTreeImplementation.cpp \
	src/tdme/engine/subsystems/lighting/LightingShaderWaterImplementation.cpp \
	src/tdme/engine/subsystems/lines/LinesShader.cpp \
	src/tdme/engine/subsystems/lines/LinesInternal.cpp \
	src/tdme/engine/subsystems/manager/MeshManager.cpp \
	src/tdme/engine/subsystems/manager/MeshManager_MeshManaged.cpp \
	src/tdme/engine/subsystems/manager/TextureManager.cpp \
	src/tdme/engine/subsystems/manager/TextureManager_TextureManaged.cpp \
	src/tdme/engine/subsystems/manager/VBOManager.cpp \
	src/tdme/engine/subsystems/manager/VBOManager_VBOManaged.cpp \
	src/tdme/engine/subsystems/rendering/BatchRendererPoints.cpp \
	src/tdme/engine/subsystems/rendering/BatchRendererTriangles.cpp \
	src/tdme/engine/subsystems/rendering/ModelUtilitiesInternal.cpp \
	src/tdme/engine/subsystems/rendering/ObjectAnimation.cpp \
	src/tdme/engine/subsystems/rendering/ObjectBase.cpp \
	src/tdme/engine/subsystems/rendering/ObjectNode.cpp \
	src/tdme/engine/subsystems/rendering/ObjectNodeMesh.cpp \
	src/tdme/engine/subsystems/rendering/ObjectNodeRenderer.cpp \
	src/tdme/engine/subsystems/rendering/ObjectInternal.cpp \
	src/tdme/engine/subsystems/rendering/ObjectModelInternal.cpp \
	src/tdme/engine/subsystems/rendering/EntityRenderer.cpp \
	src/tdme/engine/subsystems/rendering/ObjectBuffer.cpp \
	src/tdme/engine/subsystems/rendering/RenderTransparentRenderPointsPool.cpp \
	src/tdme/engine/subsystems/rendering/TransparentRenderFacesGroup.cpp \
	src/tdme/engine/subsystems/rendering/TransparentRenderPointsPool.cpp \
	src/tdme/engine/subsystems/particlesystem/BoundingBoxParticleEmitter.cpp \
	src/tdme/engine/subsystems/particlesystem/CircleParticleEmitter.cpp \
	src/tdme/engine/subsystems/particlesystem/CircleParticleEmitterPlaneVelocity.cpp \
	src/tdme/engine/subsystems/particlesystem/FogParticleSystemInternal.cpp \
	src/tdme/engine/subsystems/particlesystem/ObjectParticleSystemInternal.cpp \
	src/tdme/engine/subsystems/particlesystem/ParticlesShader.cpp \
	src/tdme/engine/subsystems/particlesystem/PointParticleEmitter.cpp \
	src/tdme/engine/subsystems/particlesystem/PointsParticleSystemInternal.cpp \
	src/tdme/engine/subsystems/particlesystem/SphereParticleEmitter.cpp \
	src/tdme/engine/subsystems/renderer/Renderer.cpp \
	src/tdme/engine/subsystems/postprocessing/PostProcessing.cpp \
	src/tdme/engine/subsystems/postprocessing/PostProcessingProgram.cpp \
	src/tdme/engine/subsystems/postprocessing/PostProcessingShader.cpp \
	src/tdme/engine/subsystems/postprocessing/PostProcessingShaderBaseImplementation.cpp \
	src/tdme/engine/subsystems/postprocessing/PostProcessingShaderDepthBlurImplementation.cpp \
	src/tdme/engine/subsystems/postprocessing/PostProcessingShaderDefaultImplementation.cpp \
	src/tdme/engine/subsystems/postprocessing/PostProcessingShaderDesaturationImplementation.cpp \
	src/tdme/engine/subsystems/postprocessing/PostProcessingShaderLightScatteringImplementation.cpp \
	src/tdme/engine/subsystems/postprocessing/PostProcessingShaderSSAOImplementation.cpp \
	src/tdme/engine/subsystems/postprocessing/PostProcessingShaderSSAOMapImplementation.cpp \
	src/tdme/engine/subsystems/postprocessing/PostProcessingShaderVignetteImplementation.cpp \
	src/tdme/engine/subsystems/shadowmapping/ShadowMap.cpp \
	src/tdme/engine/subsystems/shadowmapping/ShadowMapping.cpp \
	src/tdme/engine/subsystems/shadowmapping/ShadowMapCreationShader.cpp \
	src/tdme/engine/subsystems/shadowmapping/ShadowMapCreationShaderBaseImplementation.cpp \
	src/tdme/engine/subsystems/shadowmapping/ShadowMapCreationShaderDefaultImplementation.cpp \
	src/tdme/engine/subsystems/shadowmapping/ShadowMapCreationShaderFoliageImplementation.cpp \
	src/tdme/engine/subsystems/shadowmapping/ShadowMapCreationShaderTreeImplementation.cpp \
	src/tdme/engine/subsystems/shadowmapping/ShadowMapRenderShader.cpp \
	src/tdme/engine/subsystems/shadowmapping/ShadowMapRenderShaderBaseImplementation.cpp \
	src/tdme/engine/subsystems/shadowmapping/ShadowMapRenderShaderDefaultImplementation.cpp \
	src/tdme/engine/subsystems/shadowmapping/ShadowMapRenderShaderFoliageImplementation.cpp \
	src/tdme/engine/subsystems/shadowmapping/ShadowMapRenderShaderTreeImplementation.cpp \
	src/tdme/engine/subsystems/skinning/SkinningShader.cpp \
	src/tdme/engine/subsystems/texture2D/Texture2DRenderShader.cpp \
	src/tdme/gui/GUI.cpp \
	src/tdme/gui/GUIParser.cpp \
	src/tdme/gui/GUIParserException.cpp \
	src/tdme/gui/effects/GUIColorEffect.cpp \
	src/tdme/gui/effects/GUIEffect.cpp \
	src/tdme/gui/effects/GUIPositionEffect.cpp \
	src/tdme/gui/elements/GUIButton.cpp \
	src/tdme/gui/elements/GUIButtonController.cpp \
	src/tdme/gui/elements/GUICheckbox.cpp \
	src/tdme/gui/elements/GUICheckboxController.cpp \
	src/tdme/gui/elements/GUIContextMenu.cpp \
	src/tdme/gui/elements/GUIContextMenuController.cpp \
	src/tdme/gui/elements/GUIContextMenuItem.cpp \
	src/tdme/gui/elements/GUIContextMenuItemController.cpp \
	src/tdme/gui/elements/GUIDropDown.cpp \
	src/tdme/gui/elements/GUIDropDownController.cpp \
	src/tdme/gui/elements/GUIDropDownOption.cpp \
	src/tdme/gui/elements/GUIDropDownOptionController.cpp \
	src/tdme/gui/elements/GUIGrid.cpp \
	src/tdme/gui/elements/GUIGridController.cpp \
	src/tdme/gui/elements/GUIGridItem.cpp \
	src/tdme/gui/elements/GUIGridItemController.cpp \
	src/tdme/gui/elements/GUIImageButton.cpp \
	src/tdme/gui/elements/GUIInput.cpp \
	src/tdme/gui/elements/GUIInputController.cpp \
	src/tdme/gui/elements/GUIKnob.cpp \
	src/tdme/gui/elements/GUIKnobController.cpp \
	src/tdme/gui/elements/GUIMenuHeader.cpp \
	src/tdme/gui/elements/GUIMenuHeaderController.cpp \
	src/tdme/gui/elements/GUIMenuHeaderItem.cpp \
	src/tdme/gui/elements/GUIMenuHeaderItemController.cpp \
	src/tdme/gui/elements/GUIMenuItem.cpp \
	src/tdme/gui/elements/GUIMenuItemController.cpp \
	src/tdme/gui/elements/GUIMenuSeparator.cpp \
	src/tdme/gui/elements/GUIMoveable.cpp \
	src/tdme/gui/elements/GUIMoveableController.cpp \
	src/tdme/gui/elements/GUIProgressBar.cpp \
	src/tdme/gui/elements/GUIProgressBarController.cpp \
	src/tdme/gui/elements/GUIRadioButton.cpp \
	src/tdme/gui/elements/GUIRadioButtonController.cpp \
	src/tdme/gui/elements/GUISelectorH.cpp \
	src/tdme/gui/elements/GUISelectorHController.cpp \
	src/tdme/gui/elements/GUISelectorHOption.cpp \
	src/tdme/gui/elements/GUISelectorHOptionController.cpp \
	src/tdme/gui/elements/GUIScrollArea.cpp \
	src/tdme/gui/elements/GUIScrollAreaController.cpp \
	src/tdme/gui/elements/GUISelectBox.cpp \
	src/tdme/gui/elements/GUISelectBoxController.cpp \
	src/tdme/gui/elements/GUISelectBoxOption.cpp \
	src/tdme/gui/elements/GUISelectBoxOptionController.cpp \
	src/tdme/gui/elements/GUISelectBoxParentOption.cpp \
	src/tdme/gui/elements/GUISelectBoxParentOptionController.cpp \
	src/tdme/gui/elements/GUISliderH.cpp \
	src/tdme/gui/elements/GUISliderHController.cpp \
	src/tdme/gui/elements/GUISliderV.cpp \
	src/tdme/gui/elements/GUISliderVController.cpp \
	src/tdme/gui/elements/GUIStyledInput.cpp \
	src/tdme/gui/elements/GUIStyledInputController.cpp \
	src/tdme/gui/elements/GUITab.cpp \
	src/tdme/gui/elements/GUITabContent.cpp \
	src/tdme/gui/elements/GUITabContentController.cpp \
	src/tdme/gui/elements/GUITabController.cpp \
	src/tdme/gui/elements/GUITabs.cpp \
	src/tdme/gui/elements/GUITabsContent.cpp \
	src/tdme/gui/elements/GUITabsController.cpp \
	src/tdme/gui/elements/GUITabsHeader.cpp \
	src/tdme/gui/elements/GUITabsHeaderController.cpp \
	src/tdme/gui/nodes/GUIColor.cpp \
	src/tdme/gui/nodes/GUIElementController.cpp \
	src/tdme/gui/nodes/GUIElementIgnoreEventsController.cpp \
	src/tdme/gui/nodes/GUIElementNode.cpp \
	src/tdme/gui/nodes/GUIGradientNode.cpp \
	src/tdme/gui/nodes/GUIHorizontalScrollbarInternalController.cpp \
	src/tdme/gui/nodes/GUIHorizontalScrollbarInternalNode.cpp \
	src/tdme/gui/nodes/GUIImageNode.cpp \
	src/tdme/gui/nodes/GUIInputInternalController.cpp \
	src/tdme/gui/nodes/GUIInputInternalNode.cpp \
	src/tdme/gui/nodes/GUILayerNode.cpp \
	src/tdme/gui/nodes/GUILayoutNode.cpp \
	src/tdme/gui/nodes/GUILayoutNode_Alignment.cpp \
	src/tdme/gui/nodes/GUINode.cpp \
	src/tdme/gui/nodes/GUINodeConditions.cpp \
	src/tdme/gui/nodes/GUINode_AlignmentHorizontal.cpp \
	src/tdme/gui/nodes/GUINode_AlignmentVertical.cpp \
	src/tdme/gui/nodes/GUINode_Flow.cpp \
	src/tdme/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.cpp \
	src/tdme/gui/nodes/GUIPanelNode.cpp \
	src/tdme/gui/nodes/GUIParentNode.cpp \
	src/tdme/gui/nodes/GUIParentNode_Overflow.cpp \
	src/tdme/gui/nodes/GUIScreenNode.cpp \
	src/tdme/gui/nodes/GUISpaceNode.cpp \
	src/tdme/gui/nodes/GUIStyledTextNode.cpp \
	src/tdme/gui/nodes/GUIStyledTextNodeController.cpp \
	src/tdme/gui/nodes/GUITableNode.cpp \
	src/tdme/gui/nodes/GUITableCellNode.cpp \
	src/tdme/gui/nodes/GUITableRowNode.cpp \
	src/tdme/gui/nodes/GUITextNode.cpp \
	src/tdme/gui/nodes/GUITextureBaseNode.cpp \
	src/tdme/gui/nodes/GUIVerticalScrollbarInternalController.cpp \
	src/tdme/gui/nodes/GUIVerticalScrollbarInternalNode.cpp \
	src/tdme/gui/nodes/GUIVideoNode.cpp \
	src/tdme/gui/renderer/GUIFont.cpp \
	src/tdme/gui/renderer/GUIRenderer.cpp \
	src/tdme/gui/renderer/GUIShader.cpp \
	src/tdme/gui/scripting/GUIMinitScript.cpp \
	src/tdme/minitscript/EngineMinitScript.cpp \
	src/tdme/minitscript/MinitScriptMatrix3x3.cpp \
	src/tdme/minitscript/MinitScriptMatrix4x4.cpp \
	src/tdme/minitscript/MinitScriptQuaternion.cpp \
	src/tdme/minitscript/MinitScriptTransform.cpp \
	src/tdme/minitscript/MinitScriptVector2.cpp \
	src/tdme/minitscript/MinitScriptVector3.cpp \
	src/tdme/minitscript/MinitScriptVector4.cpp \
	src/tdme/os/filesystem/ArchiveFileSystem.cpp \
	src/tdme/os/filesystem/FileSystem.cpp \
	src/tdme/os/filesystem/FileSystemException.cpp \
	src/tdme/os/filesystem/StandardFileSystem.cpp \
	src/tdme/os/threading/Barrier.cpp \
	src/tdme/tests/EngineTest.cpp \
	src/tdme/tests/EntityHierarchyTest.cpp \
	src/tdme/tests/LODTest.cpp \
	src/tdme/tests/FlowMapTest.cpp \
	src/tdme/tests/FlowMapTest2.cpp \
	src/tdme/tests/FoliageTest.cpp \
	src/tdme/tests/MathOperatorTest.cpp \
	src/tdme/tests/PathFindingTest.cpp \
	src/tdme/tests/PhysicsTest1.cpp \
	src/tdme/tests/PhysicsTest2.cpp \
	src/tdme/tests/PhysicsTest3.cpp \
	src/tdme/tests/PhysicsTest4.cpp \
	src/tdme/tests/PhysicsTest5.cpp \
	src/tdme/tests/RayTracingTest.cpp \
	src/tdme/tests/ThreadingTest_ConsumerThread.cpp \
	src/tdme/tests/ThreadingTest_ProducerThread.cpp \
	src/tdme/tests/ThreadingTest_TestThread.cpp \
	src/tdme/tests/UDPServerTest_UDPServer.cpp \
	src/tdme/tests/UDPServerTest_UDPServerClient.cpp \
	src/tdme/tests/SkinningTest.cpp \
	src/tdme/tests/TreeTest.cpp \
	src/tdme/tests/VideoTest.cpp \
	src/tdme/tests/WaterTest.cpp \
	src/tdme/tools/editor/Editor.cpp \
	src/tdme/tools/editor/controllers/AboutDialogScreenController.cpp \
	src/tdme/tools/editor/controllers/ColorPickerImageController.cpp \
	src/tdme/tools/editor/controllers/ColorPickerScreenController.cpp \
	src/tdme/tools/editor/controllers/ContextMenuScreenController.cpp \
	src/tdme/tools/editor/controllers/DraggingScreenController.cpp \
	src/tdme/tools/editor/controllers/EditorScreenController.cpp \
	src/tdme/tools/editor/controllers/FileDialogScreenController.cpp \
	src/tdme/tools/editor/controllers/FindReplaceDialogScreenController.cpp \
	src/tdme/tools/editor/controllers/ImportDialogScreenController.cpp \
	src/tdme/tools/editor/controllers/InfoDialogScreenController.cpp \
	src/tdme/tools/editor/controllers/InputDialogScreenController.cpp \
	src/tdme/tools/editor/controllers/ProgressBarScreenController.cpp \
	src/tdme/tools/editor/controllers/SelectorDialogScreenController.cpp \
	src/tdme/tools/editor/controllers/TooltipScreenController.cpp \
	src/tdme/tools/editor/misc/CameraInputHandler.cpp \
	src/tdme/tools/editor/misc/CameraRotationInputHandler.cpp \
	src/tdme/tools/editor/misc/GenerateBillboardLOD.cpp \
	src/tdme/tools/editor/misc/GenerateConvexMeshes.cpp \
	src/tdme/tools/editor/misc/GenerateImposterLOD.cpp \
	src/tdme/tools/editor/misc/Gizmo.cpp \
	src/tdme/tools/editor/misc/Markdown.cpp \
	src/tdme/tools/editor/misc/PopUps.cpp \
	src/tdme/tools/editor/misc/TextFormatter.cpp \
	src/tdme/tools/editor/misc/TextTools.cpp \
	src/tdme/tools/editor/misc/Tools.cpp \
	src/tdme/tools/editor/tabcontrollers/DecalEditorTabController.cpp \
	src/tdme/tools/editor/tabcontrollers/EmptyEditorTabController.cpp \
	src/tdme/tools/editor/tabcontrollers/EnvMapEditorTabController.cpp \
	src/tdme/tools/editor/tabcontrollers/FontTabController.cpp \
	src/tdme/tools/editor/tabcontrollers/MarkdownTabController.cpp \
	src/tdme/tools/editor/tabcontrollers/ModelEditorTabController.cpp \
	src/tdme/tools/editor/tabcontrollers/ParticleSystemEditorTabController.cpp \
	src/tdme/tools/editor/tabcontrollers/SceneEditorTabController.cpp \
	src/tdme/tools/editor/tabcontrollers/SoundTabController.cpp \
	src/tdme/tools/editor/tabcontrollers/TerrainEditorTabController.cpp \
	src/tdme/tools/editor/tabcontrollers/TextureTabController.cpp \
	src/tdme/tools/editor/tabcontrollers/TextEditorTabController.cpp \
	src/tdme/tools/editor/tabcontrollers/TriggerEditorTabController.cpp \
	src/tdme/tools/editor/tabcontrollers/UIEditorTabController.cpp \
	src/tdme/tools/editor/tabcontrollers/VideoTabController.cpp \
	src/tdme/tools/editor/tabcontrollers/subcontrollers/BasePropertiesSubController.cpp \
	src/tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeDisplaySubController.cpp \
	src/tdme/tools/editor/tabcontrollers/subcontrollers/PrototypePhysicsSubController.cpp \
	src/tdme/tools/editor/tabcontrollers/subcontrollers/PrototypePhysicsSubController_BoundingVolumeType.cpp \
	src/tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeScriptSubController.cpp \
	src/tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeSoundsSubController.cpp \
	src/tdme/tools/editor/tabviews/DecalEditorTabView.cpp \
	src/tdme/tools/editor/tabviews/EmptyEditorTabView.cpp \
	src/tdme/tools/editor/tabviews/EnvMapEditorTabView.cpp \
	src/tdme/tools/editor/tabviews/FontTabView.cpp \
	src/tdme/tools/editor/tabviews/MarkdownTabView.cpp \
	src/tdme/tools/editor/tabviews/ModelEditorTabView.cpp \
	src/tdme/tools/editor/tabviews/ParticleSystemEditorTabView.cpp \
	src/tdme/tools/editor/tabviews/SceneEditorTabView.cpp \
	src/tdme/tools/editor/tabviews/SoundTabView.cpp \
	src/tdme/tools/editor/tabviews/TerrainEditorTabView.cpp \
	src/tdme/tools/editor/tabviews/TextureTabView.cpp \
	src/tdme/tools/editor/tabviews/TextEditorTabView.cpp \
	src/tdme/tools/editor/tabviews/TriggerEditorTabView.cpp \
	src/tdme/tools/editor/tabviews/UIEditorTabView.cpp \
	src/tdme/tools/editor/tabviews/VideoTabView.cpp \
	src/tdme/tools/editor/tabviews/subviews/BasePropertiesSubView.cpp \
	src/tdme/tools/editor/tabviews/subviews/PrototypeDisplaySubView.cpp \
	src/tdme/tools/editor/tabviews/subviews/PrototypePhysicsSubView.cpp \
	src/tdme/tools/editor/tabviews/subviews/PrototypeScriptSubView.cpp \
	src/tdme/tools/editor/tabviews/subviews/PrototypeSoundsSubView.cpp \
	src/tdme/tools/editor/views/EditorView.cpp \
	src/tdme/tools/installer/Installer.cpp \
	src/tdme/utilities/Base64.cpp \
	src/tdme/utilities/Console.cpp \
	src/tdme/utilities/ExceptionBase.cpp \
	src/tdme/utilities/Float.cpp \
	src/tdme/utilities/Hex.cpp \
	src/tdme/utilities/Integer.cpp \
	src/tdme/utilities/ModelTools.cpp \
	src/tdme/utilities/PathFinding.cpp \
	src/tdme/utilities/Primitives.cpp \
	src/tdme/utilities/Properties.cpp \
	src/tdme/utilities/RTTI.cpp \
	src/tdme/utilities/SimpleTextureAtlas.cpp \
	src/tdme/utilities/SHA256.cpp \
	src/tdme/utilities/StringTools.cpp \
	src/tdme/utilities/StringTokenizer.cpp \
	src/tdme/utilities/Terrain.cpp \
	src/tdme/utilities/TextureAtlas.cpp \
	src/tdme/utilities/UTF8StringTokenizer.cpp \
	src/tdme/utilities/UTF8StringTools.cpp \
	src/tdme/video/decoder/MPEG1Decoder.cpp \
	src/tdme/video/decoder/VideoDecoderException.cpp \
	$(SRCS_PLATFORM)

EXT_TINYXML_SRCS = \
	ext/tinyxml/tinystr.cpp \
	ext/tinyxml/tinyxml.cpp \
	ext/tinyxml/tinyxmlerror.cpp \
	ext/tinyxml/tinyxmlparser.cpp

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
	ext/zlib/gzwrite.c

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
	ext/libpng/pngrtran.c

EXT_VORBIS_SRCS = \
	ext/vorbis/analysis.c \
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
	ext/vorbis/psy.c \
	ext/vorbis/registry.c \
	ext/vorbis/res0.c \
	ext/vorbis/sharedbook.c \
	ext/vorbis/smallft.c \
	ext/vorbis/synthesis.c \
	ext/vorbis/vorbisenc.c \
	ext/vorbis/vorbisfile.c \
	ext/vorbis/window.c

EXT_OGG_SRCS = \
	ext/ogg/bitwise.c \
	ext/ogg/framing.c

EXT_REACTPHYSICS3D_SRCS = \
	ext/reactphysics3d/src/body/Body.cpp \
	ext/reactphysics3d/src/body/RigidBody.cpp \
	ext/reactphysics3d/src/collision/broadphase/DynamicAABBTree.cpp \
	ext/reactphysics3d/src/collision/Collider.cpp \
	ext/reactphysics3d/src/collision/CollisionCallback.cpp \
	ext/reactphysics3d/src/collision/ContactManifold.cpp \
	ext/reactphysics3d/src/collision/ConvexMesh.cpp \
	ext/reactphysics3d/src/collision/HalfEdgeStructure.cpp \
	ext/reactphysics3d/src/collision/HeightField.cpp \
	ext/reactphysics3d/src/collision/narrowphase/CapsuleVsCapsuleAlgorithm.cpp \
	ext/reactphysics3d/src/collision/narrowphase/CapsuleVsConvexPolyhedronAlgorithm.cpp \
	ext/reactphysics3d/src/collision/narrowphase/CollisionDispatch.cpp \
	ext/reactphysics3d/src/collision/narrowphase/ConvexPolyhedronVsConvexPolyhedronAlgorithm.cpp \
	ext/reactphysics3d/src/collision/narrowphase/GJK/GJKAlgorithm.cpp \
	ext/reactphysics3d/src/collision/narrowphase/GJK/VoronoiSimplex.cpp \
	ext/reactphysics3d/src/collision/narrowphase/NarrowPhaseInfoBatch.cpp \
	ext/reactphysics3d/src/collision/narrowphase/NarrowPhaseInput.cpp \
	ext/reactphysics3d/src/collision/narrowphase/SAT/SATAlgorithm.cpp \
	ext/reactphysics3d/src/collision/narrowphase/SphereVsCapsuleAlgorithm.cpp \
	ext/reactphysics3d/src/collision/narrowphase/SphereVsConvexPolyhedronAlgorithm.cpp \
	ext/reactphysics3d/src/collision/narrowphase/SphereVsSphereAlgorithm.cpp \
	ext/reactphysics3d/src/collision/OverlapCallback.cpp \
	ext/reactphysics3d/src/collision/PolygonVertexArray.cpp \
	ext/reactphysics3d/src/collision/RaycastInfo.cpp \
	ext/reactphysics3d/src/collision/shapes/AABB.cpp \
	ext/reactphysics3d/src/collision/shapes/BoxShape.cpp \
	ext/reactphysics3d/src/collision/shapes/CapsuleShape.cpp \
	ext/reactphysics3d/src/collision/shapes/CollisionShape.cpp \
	ext/reactphysics3d/src/collision/shapes/ConcaveMeshShape.cpp \
	ext/reactphysics3d/src/collision/shapes/ConcaveShape.cpp \
	ext/reactphysics3d/src/collision/shapes/ConvexMeshShape.cpp \
	ext/reactphysics3d/src/collision/shapes/ConvexPolyhedronShape.cpp \
	ext/reactphysics3d/src/collision/shapes/ConvexShape.cpp \
	ext/reactphysics3d/src/collision/shapes/HeightFieldShape.cpp \
	ext/reactphysics3d/src/collision/shapes/SphereShape.cpp \
	ext/reactphysics3d/src/collision/shapes/TriangleShape.cpp \
	ext/reactphysics3d/src/collision/TriangleMesh.cpp \
	ext/reactphysics3d/src/collision/TriangleVertexArray.cpp \
	ext/reactphysics3d/src/collision/VertexArray.cpp \
	ext/reactphysics3d/src/components/BallAndSocketJointComponents.cpp \
	ext/reactphysics3d/src/components/BodyComponents.cpp \
	ext/reactphysics3d/src/components/ColliderComponents.cpp \
	ext/reactphysics3d/src/components/Components.cpp \
	ext/reactphysics3d/src/components/FixedJointComponents.cpp \
	ext/reactphysics3d/src/components/HingeJointComponents.cpp \
	ext/reactphysics3d/src/components/JointComponents.cpp \
	ext/reactphysics3d/src/components/RigidBodyComponents.cpp \
	ext/reactphysics3d/src/components/SliderJointComponents.cpp \
	ext/reactphysics3d/src/components/TransformComponents.cpp \
	ext/reactphysics3d/src/constraint/BallAndSocketJoint.cpp \
	ext/reactphysics3d/src/constraint/ContactPoint.cpp \
	ext/reactphysics3d/src/constraint/FixedJoint.cpp \
	ext/reactphysics3d/src/constraint/HingeJoint.cpp \
	ext/reactphysics3d/src/constraint/Joint.cpp \
	ext/reactphysics3d/src/constraint/SliderJoint.cpp \
	ext/reactphysics3d/src/engine/Entity.cpp \
	ext/reactphysics3d/src/engine/EntityManager.cpp \
	ext/reactphysics3d/src/engine/Island.cpp \
	ext/reactphysics3d/src/engine/Material.cpp \
	ext/reactphysics3d/src/engine/OverlappingPairs.cpp \
	ext/reactphysics3d/src/engine/PhysicsCommon.cpp \
	ext/reactphysics3d/src/engine/PhysicsWorld.cpp \
	ext/reactphysics3d/src/mathematics/Matrix2x2.cpp \
	ext/reactphysics3d/src/mathematics/Matrix3x3.cpp \
	ext/reactphysics3d/src/mathematics/Quaternion.cpp \
	ext/reactphysics3d/src/mathematics/Transform.cpp \
	ext/reactphysics3d/src/mathematics/Vector2.cpp \
	ext/reactphysics3d/src/mathematics/Vector3.cpp \
	ext/reactphysics3d/src/memory/HeapAllocator.cpp \
	ext/reactphysics3d/src/memory/MemoryAllocator.cpp \
	ext/reactphysics3d/src/memory/MemoryManager.cpp \
	ext/reactphysics3d/src/memory/PoolAllocator.cpp \
	ext/reactphysics3d/src/memory/SingleFrameAllocator.cpp \
	ext/reactphysics3d/src/systems/BroadPhaseSystem.cpp \
	ext/reactphysics3d/src/systems/CollisionDetectionSystem.cpp \
	ext/reactphysics3d/src/systems/ConstraintSolverSystem.cpp \
	ext/reactphysics3d/src/systems/ContactSolverSystem.cpp \
	ext/reactphysics3d/src/systems/DynamicsSystem.cpp \
	ext/reactphysics3d/src/systems/SolveBallAndSocketJointSystem.cpp \
	ext/reactphysics3d/src/systems/SolveFixedJointSystem.cpp \
	ext/reactphysics3d/src/systems/SolveHingeJointSystem.cpp \
	ext/reactphysics3d/src/systems/SolveSliderJointSystem.cpp \
	ext/reactphysics3d/src/utils/DebugRenderer.cpp \
	ext/reactphysics3d/src/utils/DefaultLogger.cpp \
	ext/reactphysics3d/src/utils/Profiler.cpp \
	ext/reactphysics3d/src/utils/quickhull/QHHalfEdgeStructure.cpp \
	ext/reactphysics3d/src/utils/quickhull/QuickHull.cpp

EXT_CPPSPLINE_SRCS = \
	ext/cpp-spline/src/Bezier.cpp \
	ext/cpp-spline/src/BSpline.cpp \
	ext/cpp-spline/src/CatmullRom.cpp \
	ext/cpp-spline/src/Curve.cpp \
	ext/cpp-spline/src/Vector.cpp

EXT_BC7_SRCS = \
	ext/bc7enc_rdo/bc7decomp.cpp \
	ext/bc7enc_rdo/bc7enc.cpp

OPENGL2_RENDERER_LIB_SRCS = \
	src/tdme/engine/subsystems/renderer/EngineGL2Renderer.cpp \
	src/tdme/engine/subsystems/renderer/GL2Renderer.cpp

OPENGL3CORE_RENDERER_LIB_SRCS = \
	src/tdme/engine/subsystems/renderer/EngineGL3Renderer.cpp \
	src/tdme/engine/subsystems/renderer/GL3Renderer.cpp

ifeq ($(VULKAN), YES)
	ifeq ($(OSSHORT), Msys)
		EXT_GLSLANG_PLATFORM_SRCS = \
			ext/vulkan/glslang/OSDependent/Windows/ossource.cpp
	else
		EXT_GLSLANG_PLATFORM_SRCS = \
			ext/vulkan/glslang/OSDependent/Unix/ossource.cpp
	endif

	EXT_SPIRV_SRCS = \
		ext/vulkan/spirv/GlslangToSpv.cpp \
		ext/vulkan/spirv/InReadableOrder.cpp \
		ext/vulkan/spirv/Logger.cpp \
		ext/vulkan/spirv/SPVRemapper.cpp \
		ext/vulkan/spirv/SpvBuilder.cpp \
		ext/vulkan/spirv/SpvPostProcess.cpp \
		ext/vulkan/spirv/SpvTools.cpp \
		ext/vulkan/spirv/disassemble.cpp \
		ext/vulkan/spirv/doc.cpp

	EXT_GLSLANG_SRCS := \
		ext/vulkan/glslang/MachineIndependent/glslang_tab.cpp \
		ext/vulkan/glslang/MachineIndependent/attribute.cpp \
		ext/vulkan/glslang/MachineIndependent/Constant.cpp \
		ext/vulkan/glslang/MachineIndependent/iomapper.cpp \
		ext/vulkan/glslang/MachineIndependent/InfoSink.cpp \
		ext/vulkan/glslang/MachineIndependent/Initialize.cpp \
		ext/vulkan/glslang/MachineIndependent/IntermTraverse.cpp \
		ext/vulkan/glslang/MachineIndependent/Intermediate.cpp \
		ext/vulkan/glslang/MachineIndependent/ParseContextBase.cpp \
		ext/vulkan/glslang/MachineIndependent/ParseHelper.cpp \
		ext/vulkan/glslang/MachineIndependent/PoolAlloc.cpp \
		ext/vulkan/glslang/MachineIndependent/RemoveTree.cpp \
		ext/vulkan/glslang/MachineIndependent/Scan.cpp \
		ext/vulkan/glslang/MachineIndependent/ShaderLang.cpp \
		ext/vulkan/glslang/MachineIndependent/SymbolTable.cpp \
		ext/vulkan/glslang/MachineIndependent/Versions.cpp \
		ext/vulkan/glslang/MachineIndependent/intermOut.cpp \
		ext/vulkan/glslang/MachineIndependent/limits.cpp \
		ext/vulkan/glslang/MachineIndependent/linkValidate.cpp \
		ext/vulkan/glslang/MachineIndependent/parseConst.cpp \
		ext/vulkan/glslang/MachineIndependent/reflection.cpp \
		ext/vulkan/glslang/MachineIndependent/preprocessor/Pp.cpp \
		ext/vulkan/glslang/MachineIndependent/preprocessor/PpAtom.cpp \
		ext/vulkan/glslang/MachineIndependent/preprocessor/PpContext.cpp \
		ext/vulkan/glslang/MachineIndependent/preprocessor/PpScanner.cpp \
		ext/vulkan/glslang/MachineIndependent/preprocessor/PpTokens.cpp \
		ext/vulkan/glslang/MachineIndependent/propagateNoContraction.cpp \
		ext/vulkan/glslang/GenericCodeGen/CodeGen.cpp \
		ext/vulkan/glslang/GenericCodeGen/Link.cpp \
		$(EXT_GLSLANG_PLATFORM_SRCS)
    	
	EXT_OGLCOMPILERSDLL_SRCS = \
		ext/vulkan/OGLCompilersDLL/InitializeDll.cpp

	EXT_VMA_SRCS = \
		ext/vulkan/vma/src/VmaUsage.cpp

	VULKAN_RENDERER_LIB_SRCS = \
		src/tdme/engine/subsystems/renderer/EngineVKRenderer.cpp \
		src/tdme/engine/subsystems/renderer/VKGL3CoreShaderProgram.cpp \
		src/tdme/engine/subsystems/renderer/VKRenderer.cpp
	
else
	EXT_GLSLANG_PLATFORM_SRCS =
	EXT_SPIRV_SRCS =
	EXT_GLSLANG_SRCS =
	EXT_OGLCOMPILERSDLL_SRCS =
	EXT_VMA_SRCS =
	VULKAN_RENDERER_LIB_SRCS =
endif

ifeq ($(GLES2), YES)
	OPENGLES2_RENDERER_LIB_SRCS = \
		src/tdme/engine/subsystems/renderer/EngineGLES2Renderer.cpp \
		src/tdme/engine/subsystems/renderer/GLES2Renderer.cpp
else
	OPENGLES2_RENDERER_LIB_SRCS =
endif

MAIN_SRCS = \
	src/tdme/tests/AudioTest-main.cpp \
	src/tdme/tests/ContainerTest-main.cpp \
	src/tdme/tests/CrashTest-main.cpp \
	src/tdme/tests/EngineTest-main.cpp \
	src/tdme/tests/EntityHierarchyTest-main.cpp \
	src/tdme/tests/HTTPClientTest-main.cpp \
	src/tdme/tests/HTTPDownloadClientTest-main.cpp \
	src/tdme/tests/LODTest-main.cpp \
	src/tdme/tests/FlowMapTest-main.cpp \
	src/tdme/tests/FlowMapTest2-main.cpp \
	src/tdme/tests/FoliageTest-main.cpp \
	src/tdme/tests/MathOperatorTest-main.cpp \
	src/tdme/tests/MinitScriptTest-main.cpp \
	src/tdme/tests/PathFindingTest-main.cpp \
	src/tdme/tests/PhysicsTest1-main.cpp \
	src/tdme/tests/PhysicsTest2-main.cpp \
	src/tdme/tests/PhysicsTest3-main.cpp \
	src/tdme/tests/PhysicsTest4-main.cpp \
	src/tdme/tests/PhysicsTest5-main.cpp \
	src/tdme/tests/RayTracingTest-main.cpp \
	src/tdme/tests/SkinningTest-main.cpp \
	src/tdme/tests/SplineTest-main.cpp \
	src/tdme/tests/TextureAtlasTest-main.cpp \
	src/tdme/tests/ThreadingTest-main.cpp \
	src/tdme/tests/TreeTest-main.cpp \
	src/tdme/tests/UDPClientTest-main.cpp \
	src/tdme/tests/UDPServerTest-main.cpp \
	src/tdme/tests/VideoTest-main.cpp \
	src/tdme/tests/WaterTest-main.cpp \
	src/tdme/tools/editor/Editor-main.cpp \
	src/tdme/tools/installer/Installer-main.cpp \
	src/tdme/tools/cli/archive-main.cpp \
	src/tdme/tools/cli/collectguitags-main.cpp \
	src/tdme/tools/cli/converttotm-main.cpp \
	src/tdme/tools/cli/copyanimationsetups-main.cpp \
	src/tdme/tools/cli/createinstaller-main.cpp \
	src/tdme/tools/cli/minitscriptcodecompletion-main.cpp \
	src/tdme/tools/cli/minitscriptdocumentation-main.cpp \
	src/tdme/tools/cli/minitscriptlibrary-main.cpp \
	src/tdme/tools/cli/minitscriptmakefile-main.cpp \
	src/tdme/tools/cli/minitscriptnmakefile-main.cpp \
	src/tdme/tools/cli/minitscripttranspiler-main.cpp \
	src/tdme/tools/cli/minitscriptuntranspiler-main.cpp \
	src/tdme/tools/cli/createrc-main.cpp \
	src/tdme/tools/cli/dumpmodel-main.cpp \
	src/tdme/tools/cli/imageprocessor-main.cpp \
	src/tdme/tools/cli/msclib2dll-main.cpp \
	src/tdme/tools/cli/generatelicenses-main.cpp \
	src/tdme/tools/cli/importtmodel-main.cpp \
	src/tdme/tools/cli/importtscene-main.cpp \
	src/tdme/tools/cli/makefilegenerator-main.cpp \
	src/tdme/tools/cli/nmakefilegenerator-main.cpp \
	src/tdme/tools/cli/optimizemodel-main.cpp \
	src/tdme/tools/cli/parseh++-main.cpp \
	src/tdme/tools/cli/recreatevkcache-main.cpp \
	src/tdme/tools/cli/scenefixmodelszup2yup-main.cpp \
	src/tdme/tools/cli/sortincludes-main.cpp

MAINS = $(MAIN_SRCS:$(SRC)/%-main.cpp=$(BIN)/%)
OBJS = $(SRCS:$(SRC)/%.cpp=$(OBJ)/%.o)
OBJS_DEBUG = $(SRCS_DEBUG:$(SRC)/%.cpp=$(OBJ_DEBUG)/%.o)

EXT_TINYXML_OBJS = $(EXT_TINYXML_SRCS:ext/$(TINYXML)/%.cpp=$(OBJ)/%.o)
EXT_ZLIB_OBJS = $(EXT_ZLIB_SRCS:ext/$(ZLIB)/%.c=$(OBJ)/%.o)
EXT_LIBPNG_OBJS = $(EXT_LIBPNG_SRCS:ext/$(LIBPNG)/%.c=$(OBJ)/%.o)
EXT_VORBIS_OBJS = $(EXT_VORBIS_SRCS:ext/$(VORBIS)/%.c=$(OBJ)/%.o)
EXT_OGG_OBJS = $(EXT_OGG_SRCS:ext/$(OGG)/%.c=$(OBJ)/%.o)
EXT_REACTPHYSICS3D_OBJS = $(EXT_REACTPHYSICS3D_SRCS:ext/$(REACTPHYSICS3D)/%.cpp=$(OBJ)/%.o)
EXT_CPPSPLINE_OBJS = $(EXT_CPPSPLINE_SRCS:ext/$(CPPSPLINE)/%.cpp=$(OBJ)/%.o)
EXT_BC7_OBJS = $(EXT_BC7_SRCS:ext/$(BC7)/%.cpp=$(OBJ)/%.o)
EXT_SPIRV_OBJS = $(EXT_SPIRV_SRCS:ext/$(SPIRV)/%.cpp=$(OBJ)/vulkan/%.o)
EXT_GLSLANG_OBJS = $(EXT_GLSLANG_SRCS:ext/$(GLSLANG)/%.cpp=$(OBJ)/vulkan/%.o)
EXT_OGLCOMPILERSDLL_OBJS = $(EXT_OGLCOMPILERSDLL_SRCS:ext/$(OGLCOMPILERSDLL)/%.cpp=$(OBJ)/vulkan/%.o)
EXT_VMA_OBJS = $(EXT_VMA_SRCS:ext/$(VMA)/%.cpp=$(OBJ)/vulkan/%.o)

OPENGL2_RENDERER_LIB_OBJS = $(OPENGL2_RENDERER_LIB_SRCS:$(SRC)/%.cpp=$(OBJ)/%.o)
OPENGL3CORE_RENDERER_LIB_OBJS = $(OPENGL3CORE_RENDERER_LIB_SRCS:$(SRC)/%.cpp=$(OBJ)/%.o)
VULKAN_RENDERER_LIB_OBJS = $(VULKAN_RENDERER_LIB_SRCS:$(SRC)/%.cpp=$(OBJ)/%.o)
OPENGLES2_RENDERER_LIB_OBJS = $(OPENGLES2_RENDERER_LIB_SRCS:$(SRC)/%.cpp=$(OBJ)/%.o)

define cpp-command
@mkdir -p $(dir $@);
@echo Compile $<; $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
endef

define cpp-command-debug
@mkdir -p $(dir $@);
@echo Compile $<; $(CXX) $(CPPFLAGS) $(CXXFLAGS_DEBUG) -c -o $@ $<
endef

define c-command
@mkdir -p $(dir $@);
@echo Compile $<; $(CXX) -x c $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
endef

$(LIB_DIR)/$(LIB): $(OBJS) $(OBJS_DEBUG)

$(LIB_DIR)/$(EXT_LIB): $(EXT_OBJS) $(EXT_TINYXML_OBJS) $(EXT_ZLIB_OBJS) $(EXT_LIBPNG_OBJS) $(EXT_VORBIS_OBJS) $(EXT_OGG_OBJS) $(EXT_REACTPHYSICS3D_OBJS) $(EXT_CPPSPLINE_OBJS) $(EXT_BC7_OBJS)

$(LIB_DIR)/$(OPENGL2_RENDERER_LIB): $(OPENGL2_RENDERER_LIB_OBJS)

$(LIB_DIR)/$(OPENGL3CORE_RENDERER_LIB): $(OPENGL3CORE_RENDERER_LIB_OBJS)

$(LIB_DIR)/$(VULKAN_RENDERER_LIB): $(EXT_SPIRV_OBJS) $(EXT_GLSLANG_OBJS) $(EXT_OGLCOMPILERSDLL_OBJS) $(EXT_VMA_OBJS) $(VULKAN_RENDERER_LIB_OBJS)

$(LIB_DIR)/$(OPENGLES2_RENDERER_LIB): $(OPENGLES2_RENDERER_LIB_OBJS)

$(OBJS):$(OBJ)/%.o: $(SRC)/%.cpp | print-opts
	$(cpp-command)

$(OBJS_DEBUG):$(OBJ_DEBUG)/%.o: $(SRC)/%.cpp | print-opts
	$(cpp-command-debug)

$(EXT_TINYXML_OBJS):$(OBJ)/%.o: ext/$(TINYXML)/%.cpp | print-opts
	$(cpp-command)

$(EXT_ZLIB_OBJS):$(OBJ)/%.o: ext/$(ZLIB)/%.c | print-opts
	$(c-command)

$(EXT_LIBPNG_OBJS):$(OBJ)/%.o: ext/$(LIBPNG)/%.c | print-opts
	$(c-command)

$(EXT_VORBIS_OBJS):$(OBJ)/%.o: ext/$(VORBIS)/%.c | print-opts
	$(c-command)

$(EXT_OGG_OBJS):$(OBJ)/%.o: ext/$(OGG)/%.c | print-opts
	$(c-command)

$(EXT_REACTPHYSICS3D_OBJS):$(OBJ)/%.o: ext/$(REACTPHYSICS3D)/%.cpp | print-opts
	$(cpp-command)

$(EXT_CPPSPLINE_OBJS):$(OBJ)/%.o: ext/$(CPPSPLINE)/%.cpp | print-opts
	$(cpp-command)

$(EXT_BC7_OBJS):$(OBJ)/%.o: ext/$(BC7)/%.cpp | print-opts
	$(cpp-command)

$(EXT_SPIRV_OBJS):$(OBJ)/vulkan/%.o: ext/$(SPIRV)/%.cpp | print-opts
	$(cpp-command)

$(EXT_GLSLANG_OBJS):$(OBJ)/vulkan/%.o: ext/$(GLSLANG)/%.cpp | print-opts
	$(cpp-command)

$(EXT_OGLCOMPILERSDLL_OBJS):$(OBJ)/vulkan/%.o: ext/$(OGLCOMPILERSDLL)/%.cpp | print-opts
	$(cpp-command)

$(EXT_VMA_OBJS):$(OBJ)/vulkan/%.o: ext/$(VMA)/%.cpp | print-opts
	$(cpp-command)

$(OPENGL2_RENDERER_LIB_OBJS):$(OBJ)/%.o: $(SRC)/%.cpp | print-opts
	$(cpp-command)

$(OPENGL3CORE_RENDERER_LIB_OBJS):$(OBJ)/%.o: $(SRC)/%.cpp | print-opts
	$(cpp-command)

$(VULKAN_RENDERER_LIB_OBJS):$(OBJ)/%.o: $(SRC)/%.cpp | print-opts
	$(cpp-command)

$(OPENGLES2_RENDERER_LIB_OBJS):$(OBJ)/%.o: $(SRC)/%.cpp | print-opts
	$(cpp-command)

clean-subdirs:
	@mkdir -p lib
	for dir in $(SUBDIRS); do \
		cd ext/$$dir; \
		$(MAKE) clean; \
		cd ../..; \
    done

make-subdirs:
	@mkdir -p lib
	for dir in $(SUBDIRS); do \
		cd ext/$$dir; \
		$(MAKE); \
		cd ../..; \
		cp ext/$$dir/lib/lib$$dir$(LIB_EXT) lib/; \
    done

$(LIB_DIR)/$(EXT_LIB):
	@echo Creating shared library $@
	@mkdir -p $(dir $@)
	@rm -f $@
ifeq ($(OSSHORT), Msys)
	@scripts/windows-mingw-create-library-rc.sh $@ $@.rc
	@windres $@.rc -o coff -o $@.rc.o
	$(CXX) -shared $(patsubst %$(LIB_EXT),,$^) -o $@ $@.rc.o $(LIBS_LDFLAGS) -Wl,--out-implib,$(LIB_DIR)/$(EXT_LIB).a
	@rm $@.rc
	@rm $@.rc.o
else
	$(CXX) -shared $(patsubst %$(LIB_EXT),,$^) -o $@ $(LIBS_LDFLAGS)
endif
	@echo Done $@

$(LIB_DIR)/$(LIB): $(LIB_DIR)/$(EXT_LIB)
	@echo Creating shared library $@
	@mkdir -p $(dir $@)
	@rm -f $@
ifeq ($(OSSHORT), Msys)
	@scripts/windows-mingw-create-library-rc.sh $@ $@.rc
	@windres $@.rc -o coff -o $@.rc.o
	$(CXX) -shared $(patsubst %$(LIB_EXT),,$^) -o $@ $@.rc.o $(LIBS_LDFLAGS) -Llib -l$(LDFLAG_EXT_LIB) -l$(LDFLAG_YANNET_LIB) -l$(LDFLAG_MINITSCRIPT_LIB) -Wl,--out-implib,$(LIB_DIR)/$(LIB).a
	@rm $@.rc
	@rm $@.rc.o
else
	$(CXX) -shared $(patsubst %$(LIB_EXT),,$^) -o $@ $(LIBS_LDFLAGS) -Llib -l$(LDFLAG_EXT_LIB) -l$(LDFLAG_YANNET_LIB) -l$(LDFLAG_MINITSCRIPT_LIB)
endif
	@echo Done $@

$(LIB_DIR)/$(OPENGL2_RENDERER_LIB): $(LIB_DIR)/$(EXT_LIB) $(LIB_DIR)/$(LIB)
	@echo Creating OpenGL2 renderer library $@
	@mkdir -p $(dir $@)
	@rm -f $@
ifeq ($(OSSHORT), Msys)
	@scripts/windows-mingw-create-library-rc.sh $@ $@.rc
	@windres $@.rc -o coff -o $@.rc.o
	$(CXX) -shared $(patsubst %$(LIB_EXT),,$^) -o $@ $@.rc.o $(OPENGL_RENDERER_LDFLAGS) -L$(LIB_DIR) -l$(LDFLAG_EXT_LIB) -l$(LDFLAG_LIB)
	@rm $@.rc
	@rm $@.rc.o
else
	$(CXX) -shared $(patsubst %$(LIB_EXT),,$^) -o $@ $(OPENGL_RENDERER_LDFLAGS) -L$(LIB_DIR) -l$(LDFLAG_EXT_LIB) -l$(LDFLAG_LIB)
endif
	@echo Done $@

$(LIB_DIR)/$(OPENGL3CORE_RENDERER_LIB): $(LIB_DIR)/$(EXT_LIB) $(LIB_DIR)/$(LIB)
	@echo Creating OpenGL3/CORE renderer library $@
	@mkdir -p $(dir $@)
	@rm -f $@
ifeq ($(OSSHORT), Msys)
	@scripts/windows-mingw-create-library-rc.sh $@ $@.rc
	@windres $@.rc -o coff -o $@.rc.o
	$(CXX) -shared $(patsubst %$(LIB_EXT),,$^) -o $@ $@.rc.o $(OPENGL_RENDERER_LDFLAGS) -L$(LIB_DIR) -l$(LDFLAG_EXT_LIB) -l$(LDFLAG_LIB)
	@rm $@.rc
	@rm $@.rc.o
else
	$(CXX) -shared $(patsubst %$(LIB_EXT),,$^) -o $@ $(OPENGL_RENDERER_LDFLAGS) -L$(LIB_DIR) -l$(LDFLAG_EXT_LIB) -l$(LDFLAG_LIB)
endif
	@echo Done $@

$(LIB_DIR)/$(VULKAN_RENDERER_LIB): $(LIB_DIR)/$(EXT_LIB) $(LIB_DIR)/$(LIB)
	@echo Creating Vulkan renderer library $@
	@mkdir -p $(dir $@)
	@rm -f $@
ifeq ($(OSSHORT), Msys)
	@scripts/windows-mingw-create-library-rc.sh $@ $@.rc
	@windres $@.rc -o coff -o $@.rc.o
	$(CXX) -shared $(patsubst %$(LIB_EXT),,$^) -o $@ $@.rc.o $(VULKAN_RENDERER_LDFLAGS) -L$(LIB_DIR) -l$(LDFLAG_EXT_LIB) -l$(LDFLAG_LIB)
	@rm $@.rc
	@rm $@.rc.o
else
	$(CXX) -shared $(patsubst %$(LIB_EXT),,$^) -o $@ $(VULKAN_RENDERER_LDFLAGS) -L$(LIB_DIR) -l$(LDFLAG_EXT_LIB) -l$(LDFLAG_LIB)
endif
	@echo Done $@

$(LIB_DIR)/$(OPENGLES2_RENDERER_LIB): $(LIB_DIR)/$(EXT_LIB) $(LIB_DIR)/$(LIB)
	@echo Creating OpenGLES2 renderer library $@
	@mkdir -p $(dir $@)
	@rm -f $@
ifeq ($(OSSHORT), Msys)
	@scripts/windows-mingw-create-library-rc.sh $@ $@.rc
	@windres $@.rc -o coff -o $@.rc.o
	$(CXX) -shared $(patsubst %$(LIB_EXT),,$^) -o $@ $@.rc.o $(OPENGLES2_RENDERER_LDFLAGS) -L$(LIB_DIR) -l$(LDFLAG_EXT_LIB) -l$(LDFLAG_LIB)
	@rm $@.rc
	@rm $@.rc.o
else
	$(CXX) -shared $(patsubst %$(LIB_EXT),,$^) -o $@ $(OPENGLES2_RENDERER_LDFLAGS) -L$(LIB_DIR) -l$(LDFLAG_EXT_LIB) -l$(LDFLAG_LIB)
endif
	@echo Done $@

ifeq ($(OSSHORT), Msys)
$(MAINS):$(BIN)/%:$(SRC)/%-main.cpp
	@mkdir -p $(dir $@);
	@scripts/windows-mingw-create-executable-rc.sh "$<" $@.rc
	@windres $@.rc -o coff -o $@.rc.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $@.rc.o $< -L$(LIB_DIR) -l$(LDFLAG_EXT_LIB) -l$(LDFLAG_YANNET_LIB) -l$(LDFLAG_MINITSCRIPT_LIB) -l$(LDFLAG_LIB) $(MAIN_LDFLAGS)
	@rm $@.rc
	@rm $@.rc.o
else
$(MAINS):$(BIN)/%:$(SRC)/%-main.cpp $(LIBS)
	@mkdir -p $(dir $@);
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $< -L$(LIB_DIR) -l$(LDFLAG_EXT_LIB) -l$(LDFLAG_YANNET_LIB) -l$(LDFLAG_MINITSCRIPT_LIB) -l$(LDFLAG_LIB) $(MAIN_LDFLAGS)
endif

mains: $(MAINS)

all: mains

clean: clean-subdirs
	rm -rf obj obj-debug $(LIB_DIR) $(BIN)

print-opts:
	@echo Building with \"$(CXX) $(CPPFLAGS) $(CXXFLAGS)\"
	
.PHONY: all $(LIBS) mains clean print-opts

-include $(OBJS:%.o=%.d)
-include $(OBJS_DEBUG:%.o=%.d)
