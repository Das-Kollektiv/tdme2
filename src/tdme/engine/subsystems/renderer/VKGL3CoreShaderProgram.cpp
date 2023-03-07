#include <tdme/engine/subsystems/renderer/VKGL3CoreShaderProgram.h>

#if defined(_MSC_VER)
	// this suppresses a warning redefinition of APIENTRY macro
	#define NOMINMAX
	#include <windows.h>
#endif
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <ext/vulkan/glslang/Public/ShaderLang.h>
#include <ext/vulkan/spirv/GlslangToSpv.h>
#include <ext/vulkan/OGLCompilersDLL/InitializeDll.h>

#include <map>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/VKRenderer.h>
#include <tdme/math/Math.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/Properties.h>
#include <tdme/utilities/StringTokenizer.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/SHA256.h>

using std::to_string;

using std::map;
using std::stack;
using std::string;
using std::to_string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::engine::subsystems::renderer::VKGL3CoreShaderProgram;

using tdme::math::Math;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;
using tdme::utilities::Integer;
using tdme::utilities::Properties;
using tdme::utilities::StringTokenizer;
using tdme::utilities::StringTools;
using tdme::utilities::SHA256;

void VKGL3CoreShaderProgram::shaderInitResources(TBuiltInResource &resources) {
    resources.maxLights = 32;
    resources.maxClipPlanes = 6;
    resources.maxTextureUnits = 32;
    resources.maxTextureCoords = 32;
    resources.maxVertexAttribs = 64;
    resources.maxVertexUniformComponents = 4096;
    resources.maxVaryingFloats = 64;
    resources.maxVertexTextureImageUnits = 32;
    resources.maxCombinedTextureImageUnits = 80;
    resources.maxTextureImageUnits = 32;
    resources.maxFragmentUniformComponents = 4096;
    resources.maxDrawBuffers = 32;
    resources.maxVertexUniformVectors = 128;
    resources.maxVaryingVectors = 8;
    resources.maxFragmentUniformVectors = 16;
    resources.maxVertexOutputVectors = 16;
    resources.maxFragmentInputVectors = 15;
    resources.minProgramTexelOffset = -8;
    resources.maxProgramTexelOffset = 7;
    resources.maxClipDistances = 8;
    resources.maxComputeWorkGroupCountX = 65535;
    resources.maxComputeWorkGroupCountY = 65535;
    resources.maxComputeWorkGroupCountZ = 65535;
    resources.maxComputeWorkGroupSizeX = 1024;
    resources.maxComputeWorkGroupSizeY = 1024;
    resources.maxComputeWorkGroupSizeZ = 64;
    resources.maxComputeUniformComponents = 1024;
    resources.maxComputeTextureImageUnits = 16;
    resources.maxComputeImageUniforms = 8;
    resources.maxComputeAtomicCounters = 8;
    resources.maxComputeAtomicCounterBuffers = 1;
    resources.maxVaryingComponents = 60;
    resources.maxVertexOutputComponents = 64;
    resources.maxGeometryInputComponents = 64;
    resources.maxGeometryOutputComponents = 128;
    resources.maxFragmentInputComponents = 128;
    resources.maxImageUnits = 8;
    resources.maxCombinedImageUnitsAndFragmentOutputs = 8;
    resources.maxCombinedShaderOutputResources = 8;
    resources.maxImageSamples = 0;
    resources.maxVertexImageUniforms = 0;
    resources.maxTessControlImageUniforms = 0;
    resources.maxTessEvaluationImageUniforms = 0;
    resources.maxGeometryImageUniforms = 0;
    resources.maxFragmentImageUniforms = 8;
    resources.maxCombinedImageUniforms = 8;
    resources.maxGeometryTextureImageUnits = 16;
    resources.maxGeometryOutputVertices = 256;
    resources.maxGeometryTotalOutputComponents = 1024;
    resources.maxGeometryUniformComponents = 1024;
    resources.maxGeometryVaryingComponents = 64;
    resources.maxTessControlInputComponents = 128;
    resources.maxTessControlOutputComponents = 128;
    resources.maxTessControlTextureImageUnits = 16;
    resources.maxTessControlUniformComponents = 1024;
    resources.maxTessControlTotalOutputComponents = 4096;
    resources.maxTessEvaluationInputComponents = 128;
    resources.maxTessEvaluationOutputComponents = 128;
    resources.maxTessEvaluationTextureImageUnits = 16;
    resources.maxTessEvaluationUniformComponents = 1024;
    resources.maxTessPatchComponents = 120;
    resources.maxPatchVertices = 32;
    resources.maxTessGenLevel = 64;
    resources.maxViewports = 16;
    resources.maxVertexAtomicCounters = 0;
    resources.maxTessControlAtomicCounters = 0;
    resources.maxTessEvaluationAtomicCounters = 0;
    resources.maxGeometryAtomicCounters = 0;
    resources.maxFragmentAtomicCounters = 8;
    resources.maxCombinedAtomicCounters = 8;
    resources.maxAtomicCounterBindings = 1;
    resources.maxVertexAtomicCounterBuffers = 0;
    resources.maxTessControlAtomicCounterBuffers = 0;
    resources.maxTessEvaluationAtomicCounterBuffers = 0;
    resources.maxGeometryAtomicCounterBuffers = 0;
    resources.maxFragmentAtomicCounterBuffers = 1;
    resources.maxCombinedAtomicCounterBuffers = 1;
    resources.maxAtomicCounterBufferSize = 16384;
    resources.maxTransformFeedbackBuffers = 4;
    resources.maxTransformFeedbackInterleavedComponents = 64;
    resources.maxCullDistances = 8;
    resources.maxCombinedClipAndCullDistances = 8;
    resources.maxSamples = 4;
    resources.maxMeshOutputVerticesNV = 256;
    resources.maxMeshOutputPrimitivesNV = 512;
    resources.maxMeshWorkGroupSizeX_NV = 32;
    resources.maxMeshWorkGroupSizeY_NV = 1;
    resources.maxMeshWorkGroupSizeZ_NV = 1;
    resources.maxTaskWorkGroupSizeX_NV = 32;
    resources.maxTaskWorkGroupSizeY_NV = 1;
    resources.maxTaskWorkGroupSizeZ_NV = 1;
    resources.maxMeshViewCountNV = 4;
    resources.limits.nonInductiveForLoops = 1;
    resources.limits.whileLoops = 1;
    resources.limits.doWhileLoops = 1;
    resources.limits.generalUniformIndexing = 1;
    resources.limits.generalAttributeMatrixVectorIndexing = 1;
    resources.limits.generalVaryingIndexing = 1;
    resources.limits.generalSamplerIndexing = 1;
    resources.limits.generalVariableIndexing = 1;
    resources.limits.generalConstantMatrixVectorIndexing = 1;
}

EShLanguage VKGL3CoreShaderProgram::shaderFindLanguage(const VkShaderStageFlagBits shaderType) {
    switch (shaderType) {
        case VK_SHADER_STAGE_VERTEX_BIT:
            return EShLangVertex;
        case VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT:
            return EShLangTessControl;
        case VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT:
            return EShLangTessEvaluation;
        case VK_SHADER_STAGE_GEOMETRY_BIT:
            return EShLangGeometry;
        case VK_SHADER_STAGE_FRAGMENT_BIT:
            return EShLangFragment;
        case VK_SHADER_STAGE_COMPUTE_BIT:
            return EShLangCompute;
        default:
            return EShLangVertex;
    }
}

int VKGL3CoreShaderProgram::determineAlignment(const unordered_map<string, vector<string>>& structs, const vector<string>& uniforms) {
	StringTokenizer t;
	auto alignmentMax = 0;
	for (auto uniform: uniforms) {
		t.tokenize(uniform, "\t ;");
		string uniformType;
		string uniformName;
		auto isArray = false;
		auto arraySize = 1;
		if (t.hasMoreTokens() == true) uniformType = t.nextToken();
		while (t.hasMoreTokens() == true) uniformName = t.nextToken();
		if (uniformName.find('[') != -1 && uniformName.find(']') != -1) {
			uniformName = StringTools::substring(uniformName, 0, uniformName.find('['));
		}
		if (uniformType == "int") {
			uint32_t size = sizeof(int32_t);
			alignmentMax = Math::max(alignmentMax, size);
		} else
		if (uniformType == "float") {
			uint32_t size = sizeof(float);
			alignmentMax = Math::max(alignmentMax, size);
		} else
		if (uniformType == "vec2") {
			uint32_t size = sizeof(float) * 2;
			alignmentMax = Math::max(alignmentMax, size);
		} else
		if (uniformType == "vec3") {
			uint32_t size = sizeof(float) * 4;
			alignmentMax = Math::max(alignmentMax, size);
		} else
		if (uniformType == "vec4") {
			uint32_t size = sizeof(float) * 4;
			alignmentMax = Math::max(alignmentMax, size);
		} else
		if (uniformType == "mat3") {
			uint32_t size = sizeof(float) * 4;
			alignmentMax = Math::max(alignmentMax, size);
		} else
		if (uniformType == "mat4") {
			uint32_t size = sizeof(float) * 4;
			alignmentMax = Math::max(alignmentMax, size);
		} else
		if (uniformType == "sampler2D") {
			// no op
		} else
		if (uniformType == "samplerCube") {
			// no op
		} else {
			if (structs.find(uniformType) != structs.end()) {
				uint32_t size = determineAlignment(structs, structs.find(uniformType)->second);
				alignmentMax = Math::max(alignmentMax, size);
			} else {
				return false;
			}
		}
	}
	return alignmentMax;
}

bool VKGL3CoreShaderProgram::addToShaderUniformBufferObject(VKRenderer::VKRenderer::shader_type& shader, const unordered_map<string, string>& definitionValues, const unordered_map<string, vector<string>>& structs, const vector<string>& uniforms, const string& prefix, unordered_set<string>& uniformStructsArrays, string& uniformsBlock) {
	StringTokenizer t;
	for (auto uniform: uniforms) {
		t.tokenize(uniform, "\t ;");
		string uniformType;
		string uniformName;
		auto isArray = false;
		auto arraySize = 1;
		if (t.hasMoreTokens() == true) uniformType = t.nextToken();
		while (t.hasMoreTokens() == true) uniformName = t.nextToken();
		if (uniformName.find('[') != -1 && uniformName.find(']') != string::npos) {
			isArray = true;
			auto arraySizeString = StringTools::substring(uniformName, uniformName.find('[') + 1, uniformName.find(']'));
			for (auto definitionValueIt: definitionValues) arraySizeString = StringTools::replace(arraySizeString, definitionValueIt.first, definitionValueIt.second);
			if (Integer::is(arraySizeString) == false) {
				Console::println("VKGL3CoreShaderProgram::" + string(__FUNCTION__) + "(): Unknown array size: " + uniform);
			}
			arraySize = Integer::parse(arraySizeString);
			uniformName = StringTools::substring(uniformName, 0, uniformName.find('['));
			if (uniformType != "sampler2D" && uniformType != "samplerCube") uniformStructsArrays.insert(uniformName);
		}
		if (uniformType == "int") {
			for (auto i = 0; i < arraySize; i++) {
				auto suffix = isArray == true?"[" + to_string(i) + "]":"";
				uint32_t size = sizeof(int32_t);
				uint32_t alignment = Math::max(isArray == true?16:0, sizeof(int32_t));
				auto position = align(alignment, shader.uboSize);
				shader.uniforms[prefix + uniformName + suffix] = new VKRenderer::shader_type::uniform_type
					{
						.name = prefix + uniformName + suffix,
						.newName = prefix + uniformName + suffix,
						.type = VKRenderer::shader_type::uniform_type::TYPE_UNIFORM,
						.position = position,
						.size = size,
						.textureUnit = -1
					};
				shader.uboSize = position + size;
			}
		} else
		if (uniformType == "float") {
			for (auto i = 0; i < arraySize; i++) {
				auto suffix = isArray == true?"[" + to_string(i) + "]":"";
				uint32_t size = sizeof(float);
				uint32_t alignment = Math::max(isArray == true?16:0, sizeof(float));
				auto position = align(alignment, shader.uboSize);
				shader.uniforms[prefix + uniformName + suffix] = new VKRenderer::shader_type::uniform_type
					{
						.name = prefix + uniformName + suffix,
						.newName = prefix + uniformName + suffix,
						.type = VKRenderer::shader_type::uniform_type::TYPE_UNIFORM,
						.position = position,
						.size = size,
						.textureUnit = -1
					};
				shader.uboSize = position + size;
			}
		} else
		if (uniformType == "vec2") {
			for (auto i = 0; i < arraySize; i++) {
				auto suffix = isArray == true?"[" + to_string(i) + "]":"";
				uint32_t size = sizeof(float) * 2;
				uint32_t alignment = Math::max(isArray == true?16:0, sizeof(float) * 2);
				auto position = align(alignment, shader.uboSize);
				shader.uniforms[prefix + uniformName + suffix] = new VKRenderer::shader_type::uniform_type
					{
						.name = prefix + uniformName + suffix,
						.newName = prefix + uniformName + suffix,
						.type = VKRenderer::shader_type::uniform_type::TYPE_UNIFORM,
						.position = position,
						.size = size,
						.textureUnit = -1
					};
				shader.uboSize = position + size;
			}
		} else
		if (uniformType == "vec3") {
			for (auto i = 0; i < arraySize; i++) {
				auto suffix = isArray == true?"[" + to_string(i) + "]":"";
				uint32_t size = sizeof(float) * 3;
				uint32_t alignment = Math::max(isArray == true?16:0, sizeof(float) * 4);
				auto position = align(alignment, shader.uboSize);
				shader.uniforms[prefix + uniformName + suffix] = new VKRenderer::shader_type::uniform_type
					{
						.name = prefix + uniformName + suffix,
						.newName = prefix + uniformName + suffix,
						.type = VKRenderer::shader_type::uniform_type::TYPE_UNIFORM,
						.position = position,
						.size = size,
						.textureUnit = -1
					};
				shader.uboSize = position + size;
			}
		} else
		if (uniformType == "vec4") {
			for (auto i = 0; i < arraySize; i++) {
				auto suffix = isArray == true?"[" + to_string(i) + "]":"";
				uint32_t size = sizeof(float) * 4;
				uint32_t alignment = Math::max(isArray == true?16:0, sizeof(float) * 4);
				auto position = align(alignment, shader.uboSize);
				shader.uniforms[prefix + uniformName + suffix] = new VKRenderer::shader_type::uniform_type
					{
						.name = prefix + uniformName + suffix,
						.newName = prefix + uniformName + suffix,
						.type = VKRenderer::shader_type::uniform_type::TYPE_UNIFORM,
						.position = position,
						.size = size,
						.textureUnit = -1
					};
				shader.uboSize = position + size;
			}
		} else
		if (uniformType == "mat3") {
			for (auto i = 0; i < arraySize; i++) {
				auto suffix = isArray == true?"[" + to_string(i) + "]":"";
				uint32_t size = sizeof(float) * 12;
				uint32_t alignment = Math::max(isArray == true?16:0, sizeof(float) * 4);
				auto position = align(alignment, shader.uboSize);
				shader.uniforms[prefix + uniformName + suffix] = new VKRenderer::shader_type::uniform_type
					{
						.name = prefix + uniformName + suffix,
						.newName = prefix + uniformName + suffix,
						.type = VKRenderer::shader_type::uniform_type::TYPE_UNIFORM,
						.position = position,
						.size = size,
						.textureUnit = -1
					};
				shader.uboSize = position + size;
			}
		} else
		if (uniformType == "mat4") {
			for (auto i = 0; i < arraySize; i++) {
				auto suffix = isArray == true?"[" + to_string(i) + "]":"";
				uint32_t size = sizeof(float) * 16;
				uint32_t alignment = Math::max(isArray == true?16:0, sizeof(float) * 4);
				auto position = align(alignment, shader.uboSize);
				shader.uniforms[prefix + uniformName + suffix] = new VKRenderer::shader_type::uniform_type
					{
						.name = prefix + uniformName + suffix,
						.newName = prefix + uniformName + suffix,
						.type = VKRenderer::shader_type::uniform_type::TYPE_UNIFORM,
						.position = position,
						.size = size,
						.textureUnit = -1
					};
				shader.uboSize = position + size;
			}
		} else
		if (uniformType == "sampler2D") {
			for (auto i = 0; i < arraySize; i++) {
				auto suffix = isArray == true?"[" + to_string(i) + "]":"";
				auto newSuffix = isArray == true?"_" + to_string(i):"";
				shader.uniforms[prefix + uniformName + suffix] = new VKRenderer::shader_type::uniform_type
					{
						.name = prefix + uniformName + suffix,
						.newName = prefix + uniformName + newSuffix,
						.type = VKRenderer::shader_type::uniform_type::TYPE_SAMPLER2D,
						.position = -1,
						.size = 0,
						.textureUnit = -1
					};
			}
			continue;
		} else
		if (uniformType == "samplerCube") {
			for (auto i = 0; i < arraySize; i++) {
				auto suffix = isArray == true?"[" + to_string(i) + "]":"";
				auto newSuffix = isArray == true?"_" + to_string(i):"";
				shader.uniforms[prefix + uniformName + suffix] = new VKRenderer::shader_type::uniform_type
					{
						.name = prefix + uniformName + suffix,
						.newName = prefix + uniformName + newSuffix,
						.type = VKRenderer::shader_type::uniform_type::TYPE_SAMPLERCUBE,
						.position = -1,
						.size = 0,
						.textureUnit = -1
					};
			}
			continue;
		} else {
			if (structs.find(uniformType) != structs.end()) {
				for (auto i = 0; i < arraySize; i++) {
					auto structPrefix = prefix + uniformName + (isArray == true?"[" + to_string(i) + "]":"") + ".";
					string uniformsBlockIgnore;
					auto alignment = Math::max(16, determineAlignment(structs, structs.find(uniformType)->second));
					shader.uboSize = align(alignment, shader.uboSize);
					auto success = addToShaderUniformBufferObject(shader, definitionValues, structs, structs.find(uniformType)->second, structPrefix, uniformStructsArrays, uniformsBlockIgnore);
					shader.uboSize = align(alignment, shader.uboSize);
					if (success == false) return false;
					if (isArray == false) uniformStructsArrays.insert(uniformName);
				}
			} else {
				Console::println("VKGL3CoreShaderProgram::" + string(__FUNCTION__) + "(): Unknown uniform type: " + uniformType + "@" + prefix + uniform);
				return false;
			}
		}
		uniformsBlock+= uniform + "\n";
	}
	return true;
}

void VKGL3CoreShaderProgram::loadShader(VKRenderer::shader_type& shader, int32_t type, const string& pathName, const string& fileName, const string& definitions, const string& functions)
{
	if (VERBOSE == true) Console::println("VKGL3CoreShaderProgram::" + string(__FUNCTION__) + "(): INIT: " + pathName + "/" + fileName + ": " + definitions);

	shader.valid = true;
	shader.type = (VkShaderStageFlagBits)type;
	shader.file = pathName + "/" + fileName;

	// cache + hash
	shader.cacheId = "shader-" + to_string(shader.id) + "-" + StringTools::replace(shader.file, "/", "_");
	shader.hash = SHA256::encode(shader.cacheId + "." + to_string(type) + definitions + functions);

	// do we have a cached shader already?
	if (FileSystem::getInstance()->fileExists("shader/vk/" + shader.cacheId + ".properties") == true) {
		Properties vkShaderCache;
		vkShaderCache.load("shader/vk", shader.cacheId + ".properties");
		if (shader.hash != vkShaderCache.get("shader.hash", "")) {
			Console::println("VKGL3CoreShaderProgram::" + string(__FUNCTION__) + "(): Invalid hash id");
			shader.valid = false;
		}
		return;
	}

	// shader source
	auto shaderSource = StringTools::replace(
		StringTools::replace(
			FileSystem::getInstance()->getContentAsString(pathName, fileName),
			"{$DEFINITIONS}",
			"#define HAVE_VULKAN\n\n" + definitions + "\n\n"
		),
		"{$FUNCTIONS}",
		functions + "\n\n"
	);

	// do some shader adjustments
	{
		// pre parse shader code
		vector<string> newShaderSourceLines;
		vector<string> uniforms;
		shaderSource = StringTools::replace(shaderSource, "\r", "");
		shaderSource = StringTools::replace(shaderSource, "\t", " ");
		shaderSource = StringTools::replace(shaderSource, "#version 430 core", "#version 430 core\n#extension GL_EXT_scalar_block_layout: require\n\n");
		shaderSource = StringTools::replace(shaderSource, "#version 330 core", "#version 430 core\n#extension GL_EXT_scalar_block_layout: require\n\n");
		StringTokenizer t;
		t.tokenize(shaderSource, "\n");
		StringTokenizer t2;
		vector<string> definitions;
		unordered_map<string, string> definitionValues;
		unordered_map<string, vector<string>> structs;
		string currentStruct;
		stack<string> testedDefinitions;
		vector<bool> matchedDefinitions;
		vector<bool> hadMatchedDefinitions;
		auto uboUniformCount = 0;
		auto multiLineComment = false;
		while (t.hasMoreTokens() == true) {
			auto matchedAllDefinitions = true;
			for (auto matchedDefinition: matchedDefinitions) matchedAllDefinitions&= matchedDefinition;
			auto line = StringTools::trim(t.nextToken());
			if (StringTools::startsWith(line, "//") == true) continue;
			auto position = string::npos;
			if (StringTools::startsWith(line, "/*") == true) {
				multiLineComment = true;
			} else
			if (multiLineComment == true) {
				if (StringTools::endsWith(line, "*/") == true) multiLineComment = false;
			} else
			if (StringTools::startsWith(line, "#if defined(") == true ||
				StringTools::startsWith(line, "#if !defined(") == true ||
				StringTools::startsWith(line, "#ifdef ") == true ||
				StringTools::startsWith(line, "#ifndef ") == true) {
				auto inverted = StringTools::startsWith(line, "#if !defined(") == true || StringTools::startsWith(line, "#ifndef ") == true;
				string definition;
				if (StringTools::startsWith(line, "#if ") == true) {
					definition = StringTools::trim(StringTools::substring(line, string(inverted == false?"#if defined(":"#if !defined(").size(), (position = line.find(")")) != string::npos?position:line.size()));
				} else {
					definition = StringTools::trim(StringTools::substring(line, string(inverted == false?"#ifdef ":"#ifndef ").size()));
				}
				if (VERBOSE == true) Console::println("VKGL3CoreShaderProgram::" + string(__FUNCTION__) + "(): Have preprocessor test begin: " + definition);
				testedDefinitions.push(definition);
				bool matched = false;
				for (auto availableDefinition: definitions) {
					if (definition == availableDefinition) {
						matched = true;
						break;
					}
				}
				if (inverted == true) matched = !matched;
				if (VERBOSE == true) Console::println("VKGL3CoreShaderProgram::" + string(__FUNCTION__) + "(): Have preprocessor test begin: " + definition + ": " + to_string(matched));
				matchedDefinitions.push_back(matched);
				hadMatchedDefinitions.push_back(matched);
				newShaderSourceLines.push_back("// " + line);
			} else
			if (StringTools::startsWith(line, "#elif defined(") == true ||
				StringTools::startsWith(line, "#elif !defined(") == true) {
				auto inverted = StringTools::startsWith(line, "#elif !defined(") == true;
				// remove old test from stack
				if (testedDefinitions.size() == 0) Console::println("VKGL3CoreShaderProgram::" + string(__FUNCTION__) + "(): Have preprocessor else end: invalid depth"); else {
					testedDefinitions.pop();
					matchedDefinitions.pop_back();
				}
				newShaderSourceLines.push_back("// " + line);
				// do new test
				auto definition = StringTools::trim(StringTools::substring(line, string(inverted == false?"#elif defined(":"#elif !defined(").size(), (position = line.find(")")) != string::npos?position:line.size()));
				if (VERBOSE == true) Console::println("VKGL3CoreShaderProgram::" + string(__FUNCTION__) + "(): Have preprocessor test else if: " + definition);
				testedDefinitions.push(definition);
				bool matched = false;
				for (auto availableDefinition: definitions) {
					if (definition == availableDefinition) {
						matched = true;
						break;
					}
				}
				if (inverted == true) matched = !matched;
				if (VERBOSE == true) Console::println("VKGL3CoreShaderProgram::" + string(__FUNCTION__) + "(): Have preprocessor else test begin: " + definition + ": " + to_string(matched));
				matchedDefinitions.push_back(matched);
				if (matched == true) hadMatchedDefinitions[hadMatchedDefinitions.size() - 1] = matched;
			} else
			if (StringTools::startsWith(line, "#define ") == true) {
				auto definition = StringTools::trim(StringTools::substring(line, string("#define ").size()));
				if (definition.find(' ') != string::npos) {
					t2.tokenize(definition, " ");
					definition = t2.nextToken();
					string value;
					while (t2.hasMoreTokens() == true) value+= t2.nextToken();
					definitionValues[definition] = value;
					newShaderSourceLines.push_back((matchedAllDefinitions == true?"":"// ") + line);
					if (VERBOSE == true) Console::println("VKGL3CoreShaderProgram::" + string(__FUNCTION__) + "(): Have define with value: " + definition + " --> " + value);
				} else {
					definitions.push_back(definition);
					newShaderSourceLines.push_back((matchedAllDefinitions == true?"":"// ") + line);
					if (VERBOSE == true) Console::println("VKGL3CoreShaderProgram::" + string(__FUNCTION__) + "(): Have define: " + definition);
				}
			} else
			if (StringTools::startsWith(line, "#else") == true) {
				if (VERBOSE == true) Console::println("VKGL3CoreShaderProgram::" + string(__FUNCTION__) + "(): Have preprocessor else: " + line);
				matchedDefinitions[matchedDefinitions.size() - 1] = !matchedDefinitions[matchedDefinitions.size() - 1] && hadMatchedDefinitions[matchedDefinitions.size() - 1] == false;
				newShaderSourceLines.push_back("// " + line);
				matchedAllDefinitions = true;
				for (auto matchedDefinition: matchedDefinitions) matchedAllDefinitions&= matchedDefinition;
			} else
			if (StringTools::startsWith(line, "#endif") == true) {
				if (VERBOSE == true) Console::println("VKGL3CoreShaderProgram::" + string(__FUNCTION__) + "(): Have preprocessor test end: " + line);
				if (testedDefinitions.size() == 0) Console::println("VKGL3CoreShaderProgram::" + string(__FUNCTION__) + "(): Have preprocessor test end: invalid depth"); else {
					testedDefinitions.pop();
					matchedDefinitions.pop_back();
					hadMatchedDefinitions.pop_back();
				}
				newShaderSourceLines.push_back("// " + line);
			} else
			if (matchedAllDefinitions == true) {
				if (StringTools::startsWith(line, "struct ") == true) {
					currentStruct = StringTools::trim(StringTools::substring(line, string("struct ").size(), line.find('{')));
				} else
				if (currentStruct.size() > 0) {
					if (line == "};") {
						currentStruct.clear();
					} else {
						structs[currentStruct].push_back(line);
					}
				} else
				if (currentStruct.size() > 0) {

				}
				if ((StringTools::startsWith(line, "uniform ")) == true) {
					string uniform;
					if (line.find("sampler2D") != string::npos) {
						uniform = StringTools::substring(line, string("uniform").size() + 1);
						t2.tokenize(uniform, " ;");
						string uniformType;
						string uniformName;
						if (t2.hasMoreTokens() == true) uniformType = t2.nextToken();
						while (t2.hasMoreTokens() == true) uniformName = t2.nextToken();
						auto isArray = false;
						auto arraySize = 1;
						if (uniformName.find('[') != string::npos && uniformName.find(']') != string::npos) {
							isArray = true;
							auto arraySizeString = StringTools::substring(uniformName, uniformName.find('[') + 1, uniformName.find(']'));
							for (auto definitionValueIt: definitionValues) arraySizeString = StringTools::replace(arraySizeString, definitionValueIt.first, definitionValueIt.second);
							arraySize = Integer::parse(arraySizeString);
							uniformName = StringTools::substring(uniformName, 0, uniformName.find('['));
						}
						for (auto i = 0; i < arraySize; i++) {
							auto suffix = isArray == true?"_" + to_string(i):"";
							newShaderSourceLines.push_back("layout(set = 1, binding = {$SAMPLER2D_BINDING_" + uniformName + suffix + "_IDX}) uniform sampler2D " + uniformName + suffix + ";");
						}
						shader.samplers++;
					} else
					if (line.find("samplerCube") != string::npos) {
						uniform = StringTools::substring(line, string("uniform").size() + 1);
						t2.tokenize(uniform, " ;");
						string uniformType;
						string uniformName;
						if (t2.hasMoreTokens() == true) uniformType = t2.nextToken();
						while (t2.hasMoreTokens() == true) uniformName = t2.nextToken();
						auto isArray = false;
						auto arraySize = 1;
						if (uniformName.find('[') != string::npos && uniformName.find(']') != string::npos) {
							isArray = true;
							auto arraySizeString = StringTools::substring(uniformName, uniformName.find('[') + 1, uniformName.find(']'));
							for (auto definitionValueIt: definitionValues) arraySizeString = StringTools::replace(arraySizeString, definitionValueIt.first, definitionValueIt.second);
							arraySize = Integer::parse(arraySizeString);
							uniformName = StringTools::substring(uniformName, 0, uniformName.find('['));
						}
						for (auto i = 0; i < arraySize; i++) {
							auto suffix = isArray == true?"_" + to_string(i):"";
							newShaderSourceLines.push_back("layout(set = 1, binding = {$SAMPLERCUBE_BINDING_" + uniformName + suffix + "_IDX}) uniform samplerCube " + uniformName + suffix + ";");
						}
						shader.samplers++;
					} else {
						uniform = StringTools::substring(line, string("uniform").size() + 1);
						uboUniformCount++;
					}
					uniforms.push_back(uniform);
					newShaderSourceLines.push_back("// " + line);
					if (VERBOSE == true) Console::println("VKGL3CoreShaderProgram::" + string(__FUNCTION__) + "(): Have uniform: " + uniform);
				} else
				if (StringTools::startsWith(line, "out ") == true || StringTools::startsWith(line, "flat out ") == true) {
					if (shader.type == SHADER_VERTEX_SHADER) {
						t2.tokenize(line, " ;");
						bool flat = false;
						auto inOutType = t2.hasMoreTokens() == true?t2.nextToken():string();
						if (inOutType == "flat") {
							flat = true;
							auto inOutType = t2.hasMoreTokens() == true?t2.nextToken():string();
						}
						auto outType = t2.hasMoreTokens() == true?t2.nextToken():string();
						auto outName = t2.hasMoreTokens() == true?t2.nextToken():string();
						auto outLocation = 0;
						for (auto& attributeLayout: shader.attributeLayouts) {
							if (attributeLayout.type == "mat3") {
								outLocation+= 3;
							} else
							if (attributeLayout.type == "mat4") {
								outLocation+= 4;
							} else {
								outLocation++;
							}
						}
						shader.attributeLayouts.emplace_back(
							outName,
							outType,
							static_cast<uint8_t>(outLocation)
						);
						if (VERBOSE == true) {
							Console::println(
								"inOutType: " + inOutType + " / " +
								"outType: " + outType + " / " +
								"outName: " + outName + " / " +
								"location: " + to_string(outLocation)
							);
						}
						newShaderSourceLines.push_back("layout (location = " + to_string(outLocation) + ") " + line);
					} else
					if (shader.type == SHADER_FRAGMENT_SHADER) {
						newShaderSourceLines.push_back("layout (location = 0) " + line);
					}
				} else
				if (StringTools::startsWith(line, "in ") == true || StringTools::startsWith(line, "flat in ") == true) {
					if (shader.type == SHADER_FRAGMENT_SHADER) {
						t2.tokenize(line, " ;");
						bool flat = false;
						auto inOutType = t2.hasMoreTokens() == true?t2.nextToken():string();
						if (inOutType == "flat") {
							flat = true;
							auto inOutType = t2.hasMoreTokens() == true?t2.nextToken():string();
						}
						auto inType = t2.hasMoreTokens() == true?t2.nextToken():string();
						auto inName = t2.hasMoreTokens() == true?t2.nextToken():string();
						if (VERBOSE == true) {
							Console::println("layout (location = {$IN_ATTRIBUTE_LOCATION_" + inName + "_IDX}) " + line);
						}
						newShaderSourceLines.push_back("layout (location = {$IN_ATTRIBUTE_LOCATION_" + inName + "_IDX}) " + line);
					}
				} else
				if (StringTools::startsWith(line, "layout") == true && line.find("binding=") != string::npos) {
					if (VERBOSE == true) Console::println("VKGL3CoreShaderProgram::" + string(__FUNCTION__) + "(): Have layout with binding: " + line);
					t2.tokenize(line, "(,)= \t");
					while (t2.hasMoreTokens() == true) {
						auto token = t2.nextToken();
						if (token == "binding" && t2.hasMoreTokens() == true) {
							auto nextToken = t2.nextToken();
							shader.maxBindings = Math::max(Integer::parse(nextToken), shader.maxBindings);
							break;
						}
					}
					newShaderSourceLines.push_back(line);
				} else {
					newShaderSourceLines.push_back(line);
				}
			} else {
				newShaderSourceLines.push_back("// " + line);
			}
		}

		// generate new uniform block
		unordered_set<string> uniformStructsArrays;
		string uniformsBlock = "";

		// replace uniforms to use ubo
		if (uniforms.size() > 0) {
			if (uboUniformCount > 0) {
				uniformsBlock+= "layout(set = 0, std140, column_major, binding={$UBO_BINDING_IDX}) uniform UniformBufferObject\n";
				uniformsBlock+= "{\n";
			}
			string uniformsBlockIgnore;
			addToShaderUniformBufferObject(shader, definitionValues, structs, uniforms, "", uniformStructsArrays, uboUniformCount > 0?uniformsBlock:uniformsBlockIgnore);
			if (uboUniformCount > 0) uniformsBlock+= "} ubo_generated;\n";
			if (VERBOSE == true) Console::println("Shader UBO size: " + to_string(shader.uboSize));
		}

		// root ubo uniform names
		unordered_set<string> uboUniformNames;
		for (auto& uniform: shader.uniforms) {
			auto uniformName = uniform.second->name;
			auto uniformDotIdx = uniformName.find('.');
			auto uniformOpenBracketIdx = uniformName.find('[');
			if (uniformDotIdx != string::npos && uniformOpenBracketIdx == string::npos) {
				uniformName = StringTools::substring(uniformName, 0, uniformDotIdx);
			} else
			if (uniformDotIdx == string::npos && uniformOpenBracketIdx != string::npos) {
				uniformName = StringTools::substring(uniformName, 0, uniformOpenBracketIdx);
			} else
			if (uniformDotIdx != string::npos && uniformOpenBracketIdx != string::npos) {
				uniformName = StringTools::substring(uniformName, 0, Math::min(static_cast<int>(uniformDotIdx), static_cast<int>(uniformOpenBracketIdx)));
			}
			uboUniformNames.insert(uniformName);
		}

		// construct new shader from vector and flip y, also inject uniforms
		shaderSource.clear();
		auto injectedUniformsAt = -1;
		auto injectedYFlip = false;
		auto inStruct = false;
		// inject uniform before first method
		for (auto i = 0; i < newShaderSourceLines.size(); i++) {
			auto line = newShaderSourceLines[i];
			if (StringTools::startsWith(line, "//") == true) continue;
			//
			if (inStruct == false && StringTools::startsWith(line, "struct ") == true) {
				inStruct = true;
			} else
			if (inStruct == true && StringTools::startsWith(line, "};") == true) {
				inStruct = false;
			} else
			if (injectedUniformsAt == -1 &&
				line.find('(') != string::npos &&
				line.find(')') != string::npos &&
				StringTools::startsWith(line, "struct ") == false &&
				StringTools::startsWith(line, "layout ") == false &&
				StringTools::startsWith(line, "layout(") == false &&
				StringTools::startsWith(line, "#") == false) {
				injectedUniformsAt = i - 1;
			} else
			if (inStruct == false) {
				// rename arrays and structs to ubo uniforms
				for (auto& uniformStructArrayName: uniformStructsArrays) {
					// is struct/array a first level uniform
					auto isUniform = uboUniformNames.find(uniformStructArrayName) != uboUniformNames.end();
					if (isUniform == false) continue;
					//
					line = StringTools::regexReplace(
						line,
						"(\\b)" + uniformStructArrayName + "(\\b)([\\s]*[\\[\\.;\\)]{1})",
						"$1ubo_generated." + uniformStructArrayName + "$2$3"
					);
					// TODO: this is a workaround until we have a better shader parser/adapt code
					line = StringTools::replace(line, "ubo_generated.ubo_generated.", "ubo_generated.");
					//
					newShaderSourceLines[i] = line;
				}
			}
		}
		for (int i = newShaderSourceLines.size() - 1; i >= 0; i--) {
			auto line = newShaderSourceLines[i] + "\n";
			if (i == injectedUniformsAt) {
				shaderSource = uniformsBlock + line + shaderSource;
			} else
			if (StringTools::startsWith(line, "//") == true) {
				shaderSource = line + shaderSource;
				// rename uniforms to ubo uniforms
			} else {
				for (auto& uniformIt: shader.uniforms) {
					if (uniformIt.second->type == VKRenderer::shader_type::uniform_type::TYPE_SAMPLER2D) {
						if (uniformIt.second->name != uniformIt.second->newName) {
							line = StringTools::replace(
								line,
								uniformIt.second->name,
								uniformIt.second->newName
							);
						}
					} else
					if (uniformIt.second->type == VKRenderer::shader_type::uniform_type::TYPE_SAMPLERCUBE) {
						if (uniformIt.second->name != uniformIt.second->newName) {
							line = StringTools::replace(
								line,
								uniformIt.second->name,
								uniformIt.second->newName
							);
						}
					} else {
						auto uniformName = uniformIt.second->name;
						line = StringTools::regexReplace(
							line,
							"(\\b)" + uniformName + "(\\b)",
							"$1ubo_generated." + uniformName + "$2"
						);
						// TODO: this is a workaround until we have a better shader parser/adapt code
						line = StringTools::replace(line, "ubo_generated.ubo_generated.", "ubo_generated.");
					}
				}
				// inject gl_Position flip before last } from main
				if (type == SHADER_VERTEX_SHADER && injectedYFlip == false && StringTools::startsWith(line, "}") == true) {
					shaderSource =
						"gl_Position.y*= -1.0;\ngl_Position.z = (gl_Position.z + gl_Position.w) / 2.0;\n" +
						line +
						shaderSource;
					injectedYFlip = true;
				} else  {
					shaderSource = line + shaderSource;
				}
			}
		}
		if (type == SHADER_VERTEX_SHADER && injectedYFlip == false) {
			Console::println("VKGL3CoreShaderProgram::" + string(__FUNCTION__) + "(): Could not inject OpenGL GL like Y and Z correction math");
		}

		// debug uniforms
		for (auto& uniformIt: shader.uniforms) {
			if (VERBOSE == true) Console::println("VKGL3CoreShaderProgram::" + string(__FUNCTION__) + "(): Uniform: " + uniformIt.second->name + ": " + to_string(uniformIt.second->position) + " / " + to_string(uniformIt.second->size));
		}
	}

	shader.definitions = definitions;
	shader.source = shaderSource;
}

bool VKGL3CoreShaderProgram::linkProgram(VKRenderer::program_type& program) {
	map<string, int32_t> uniformsByName;
	auto useCache = false;

	// check if shaders are valid
	for (auto shader: program.shaders) {
		if (shader->valid == false) {
			Console::println("VKGL3CoreShaderProgram::linkProgram(): Cached shader is invalid. Please recreate VK shader cache or delete VK shader cache files");
			return false;
		}
	}

	// check if we can use a cache
	if (FileSystem::getInstance()->fileExists("shader/vk/program-" + to_string(program.id) + ".properties") == true) {
		// use cache
		useCache = true;

		//
		Properties vkProgramCache;
		vkProgramCache.load("shader/vk", "program-" + to_string(program.id) + ".properties");
		if (Integer::parse(vkProgramCache.get("program.id", "-1")) != program.id) {
			Console::println("VKGL3CoreShaderProgram::linkProgram(): program id mismatch");
			return false;
		}
		program.layoutBindings = Integer::parse(vkProgramCache.get("program.layout_bindings", "-1"));

		// read shaders from cache
		auto shaderIdx = 0;
		for (auto shader: program.shaders) {
			//
			shader->cacheId = vkProgramCache.get("program.shader_" + to_string(shaderIdx) + "_cacheid", "");
			shader->source = FileSystem::getInstance()->getContentAsString("shader/vk", shader->cacheId + ".glsl");
			shader->definitions = FileSystem::getInstance()->getContentAsString("shader/vk", shader->cacheId + ".definitions");
			vector<uint8_t> spirv8;
			FileSystem::getInstance()->getContent("shader/vk", shader->cacheId + ".spirv", spirv8);
			shader->spirv.resize(spirv8.size() / 4);
			for (auto i = 0; i < spirv8.size() / 4; i++) {
				shader->spirv[i] =
					(static_cast<uint32_t>(spirv8[i * 4 + 0])) +
					(static_cast<uint32_t>(spirv8[i * 4 + 1]) << 8) +
					(static_cast<uint32_t>(spirv8[i * 4 + 2]) << 16) +
					(static_cast<uint32_t>(spirv8[i * 4 + 3]) << 24);
			}
			{
				// use shader caches to load shaders
				Properties vkShaderCache;
				vkShaderCache.load("shader/vk", shader->cacheId + ".properties");
				if (Integer::parse(vkShaderCache.get("shader.id", "-1")) != shader->id) {
					Console::println("VKGL3CoreShaderProgram::linkProgram(): shader id mismatch");
					return false;
				}
				shader->type = static_cast<VkShaderStageFlagBits>(Integer::parse(vkShaderCache.get("shader.type", "-1")));
				shader->file = vkShaderCache.get("shader.file", "");
				shader->maxBindings = Integer::parse(vkShaderCache.get("shader.max_bindings", "-1"));

				// vert->frag layout attributes
				{
					auto i = 0;
					while (vkShaderCache.get("shader.attributelayout_name_" + to_string(i), "").empty() == false) {
						auto outName = vkShaderCache.get("shader.attributelayout_name_" + to_string(i), "");
						auto outType = vkShaderCache.get("shader.attributelayout_type_" + to_string(i), "");
						uint8_t outLocation = Integer::parse(vkShaderCache.get("shader.attributelayout_location_" + to_string(i), "-1"));
						shader->attributeLayouts.emplace_back(
							outName,
							outType,
							static_cast<uint8_t>(outLocation)
						);
						i++;
					}
					shader->attributeLayouts.shrink_to_fit();
				}

				// ubo + uniforms
				{
					shader->uboSize = Integer::parse(vkShaderCache.get("shader.ubo_size", "-1"));
					shader->uboBindingIdx = Integer::parse(vkShaderCache.get("shader.ubo_bindingidx", "-1"));
					auto i = 0;
					while (vkShaderCache.get("shader.uniform_name_" + to_string(i), "").empty() == false) {
						auto name = vkShaderCache.get("shader.uniform_name_" + to_string(i), "");
						auto newName = vkShaderCache.get("shader.uniform_newname_" + to_string(i), "");
						auto type = static_cast<VKRenderer::shader_type::uniform_type::uniform_type_enum>(Integer::parse(vkShaderCache.get("shader.uniform_type_" + to_string(i), "-1")));
						int32_t position = Integer::parse(vkShaderCache.get("shader.uniform_position_" + to_string(i), "-1"));
						uint32_t size = Integer::parse(vkShaderCache.get("shader.uniform_size_" + to_string(i), "0"));
						shader->uniforms[name] = new VKRenderer::shader_type::uniform_type
							{
								.name = name,
								.newName = newName,
								.type = type,
								.position = position,
								.size = size,
								.textureUnit = -1
							};
						i++;
					}
				}
			}
			shaderIdx++;
		}

		// uniforms by name
		auto uniformIdx = 1;
		for (auto shader: program.shaders) {
			for (auto& uniformIt: shader->uniforms) {
				auto& uniform = *uniformIt.second;
				uniformsByName[uniform.name] = uniformIdx++;
			}
			// binding idx
		}
	} else {
		// nope, no cache
		auto bindingIdx = 0;
		for (auto shader: program.shaders) {
			//
			bindingIdx = Math::max(shader->maxBindings + 1, bindingIdx);
		}

		//
		for (auto shader: program.shaders) {
			// do we need a uniform buffer object for this shader stage?
			if (shader->uboSize > 0) {
				// yep, inject UBO index
				shader->uboBindingIdx = bindingIdx;
				shader->source = StringTools::replace(shader->source, "{$UBO_BINDING_IDX}", to_string(bindingIdx));
				bindingIdx++;
			}
		}

		// bind samplers, set up ingoing attribute layout indices, compile shaders
		auto uniformIdx = 1;
		VKRenderer::shader_type* shaderLast = nullptr;
		for (auto shader: program.shaders) {
			// set up sampler2D and samplerCube binding indices
			for (auto& uniformIt: shader->uniforms) {
				auto& uniform = *uniformIt.second;
				//
				if (uniform.type == VKRenderer::shader_type::uniform_type::TYPE_SAMPLER2D) {
					shader->source = StringTools::replace(shader->source, "{$SAMPLER2D_BINDING_" + uniform.newName + "_IDX}", to_string(bindingIdx));
					uniform.position = bindingIdx++;
				} else
				if (uniform.type == VKRenderer::shader_type::uniform_type::TYPE_SAMPLERCUBE) {
					shader->source = StringTools::replace(shader->source, "{$SAMPLERCUBE_BINDING_" + uniform.newName + "_IDX}", to_string(bindingIdx));
					uniform.position = bindingIdx++;
				}
				uniformsByName[uniform.name] = uniformIdx++;
			}

			// set up ingoing attributes layout indices
			if (shaderLast != nullptr) {
				for (auto& attributeLayout: shaderLast->attributeLayouts) {
					shader->source = StringTools::replace(shader->source, "{$IN_ATTRIBUTE_LOCATION_" + attributeLayout.name + "_IDX}", to_string(attributeLayout.location));
				}
			}

			// compile shader
			EShLanguage stage = shaderFindLanguage(shader->type);
			glslang::TShader glslShader(stage);
			glslang::TProgram glslProgram;
			const char *shaderStrings[1];
			TBuiltInResource resources;
			shaderInitResources(resources);

			// Enable SPIR-V and Vulkan rules when parsing GLSL
			EShMessages messages = (EShMessages)(EShMsgSpvRules | EShMsgVulkanRules);

			shaderStrings[0] = shader->source.c_str();
			glslShader.setStrings(shaderStrings, 1);

			if (!glslShader.parse(&resources, 100, false, messages)) {
				// be verbose
				Console::println(
					string(
						string("VKGL3CoreShaderProgram::") +
						string(__FUNCTION__) +
						string("[") +
						to_string(shader->id) +
						string("]") +
						string(": parsing failed: ") +
						shader->file + ": " +
						glslShader.getInfoLog() + ": " +
						glslShader.getInfoDebugLog()
					 )
				);
				Console::println(shader->source);
				return false;
			}

			glslProgram.addShader(&glslShader);
			if (glslProgram.link(messages) == false) {
				// be verbose
				Console::println(
					string(
						string("VKGL3CoreShaderProgram::") +
						string(__FUNCTION__) +
						string("[") +
						to_string(shader->id) +
						string("]") +
						string(": linking failed: ") +
						shader->file + ": " +
						glslShader.getInfoLog() + ": " +
						glslShader.getInfoDebugLog()
					)
				);
				Console::println(shader->source);
				return false;
			}

			glslang::GlslangToSpv(*glslProgram.getIntermediate(stage), shader->spirv);

			//
			shaderLast = shader;
		}

		// total bindings of program
		program.layoutBindings = bindingIdx;
	}

	//
	auto uniformMaxId = 0;
	for (auto& uniformIt: uniformsByName) {
		auto uniformName = uniformIt.first;
		auto uniformId = uniformIt.second;
		program.uniforms[uniformId] = uniformName;
		if (uniformId > uniformMaxId) uniformMaxId = uniformId;
	}

	// prepare indexed uniform lists per shader
	for (auto shader: program.shaders) {
		shader->uniformList.resize(uniformMaxId + 1);
	}
	for (auto& it: program.uniforms) {
		auto uniformId = it.first;
		auto uniformName = it.second;

		//
		for (auto shader: program.shaders) {
			auto shaderUniformIt = shader->uniforms.find(uniformName);
			if (shaderUniformIt == shader->uniforms.end()) {
				continue;
			}
			auto uniform = shaderUniformIt->second;
			shader->uniformList[uniformId] = uniform;
			if (uniform->type == VKRenderer::shader_type::uniform_type::TYPE_SAMPLER2D ||
				uniform->type == VKRenderer::shader_type::uniform_type::TYPE_SAMPLERCUBE) shader->samplerUniformList.push_back(uniform);
		}
	}

	// print shaders with more than SAMPLER_HASH_MAX samplers as our hashing depends of 4 samplers max
	if (program.type == 1/*PROGRAM_OBJECTS*/) {
		for (auto shader: program.shaders) {
			if (shader->samplerUniformList.size() > SAMPLER_HASH_MAX) {
				Console::println(
					string("VKGL3CoreShaderProgram::") +
					string(__FUNCTION__) +
					string("[") +
					to_string(shader->id) +
					string("]") +
					string(": warning: more than ") + to_string(SAMPLER_HASH_MAX) + string(" samplers @ ") +
					shader->file
				);
				for (auto samplerUniform: shader->samplerUniformList) {
					Console::println("\t" + samplerUniform->name);
				}
			}
		}
	}

	//
	for (auto shader: program.shaders) {
		shader->samplerUniformList.shrink_to_fit();
	}


	// store if not using cache
	if (useCache == false) {
		// store program properties
		{
			Properties vkProgramCache;
			vkProgramCache.put("program.id", to_string(program.id));
			vkProgramCache.put("program.layout_bindings", to_string(program.layoutBindings));
			auto i = 0;
			for (auto& shader: program.shaders) {
				vkProgramCache.put("program.shader_" + to_string(i) + "_cacheid", shader->cacheId);
				i++;
			}
			vkProgramCache.store("shader/vk", "program-" + to_string(program.id) + ".properties");
		}

		// store shader properties
		for (auto shader: program.shaders) {
			Properties vkShaderCache;
			vkShaderCache.put("shader.type", to_string(shader->type));
			vkShaderCache.put("shader.file", shader->file);
			vkShaderCache.put("shader.id", to_string(shader->id));
			vkShaderCache.put("shader.hash", shader->hash);
			vkShaderCache.put("shader.max_bindings", to_string(shader->maxBindings));
			vkShaderCache.put("shader.ubo_size", to_string(shader->uboSize));
			vkShaderCache.put("shader.ubo_bindingidx", to_string(shader->uboBindingIdx));
			// attribute layouts
			{
				auto i = 0;
				for (auto& attribute: shader->attributeLayouts) {
					vkShaderCache.put("shader.attributelayout_name_" + to_string(i), attribute.name);
					vkShaderCache.put("shader.attributelayout_type_" + to_string(i), attribute.type);
					vkShaderCache.put("shader.attributelayout_location_" + to_string(i), to_string(attribute.location));
					i++;
				}
			}
			// uniforms
			{
				auto i = 0;
				for (auto& uniformIt: shader->uniforms) {
					auto uniform = uniformIt.second;
					vkShaderCache.put("shader.uniform_name_" + to_string(i), uniform->name);
					vkShaderCache.put("shader.uniform_newname_" + to_string(i), uniform->newName);
					vkShaderCache.put("shader.uniform_type_" + to_string(i), to_string(uniform->type));
					vkShaderCache.put("shader.uniform_position_" + to_string(i), to_string(uniform->position));
					vkShaderCache.put("shader.uniform_size_" + to_string(i), to_string(uniform->size));
					i++;
				}
			}

			// store glsl
			FileSystem::getInstance()->setContentFromString("shader/vk", shader->cacheId + ".glsl", shader->source);

			// store SPIRV
			{
				vector<uint8_t> spirv8;
				for (auto v: shader->spirv) {
					spirv8.push_back((static_cast<uint32_t>(v)) & 0xff);
					spirv8.push_back((static_cast<uint32_t>(v) >> 8) & 0xff);
					spirv8.push_back((static_cast<uint32_t>(v) >> 16) & 0xff);
					spirv8.push_back((static_cast<uint32_t>(v) >> 24) & 0xff);
				}
				FileSystem::getInstance()->setContent("shader/vk", shader->cacheId + ".spirv", spirv8);
			}

			// store definitions
			FileSystem::getInstance()->setContentFromString("shader/vk", shader->cacheId + ".definitions", shader->definitions);

			// done
			vkShaderCache.store("shader/vk", shader->cacheId + ".properties");
		}
	}

	//
	return true;
}
