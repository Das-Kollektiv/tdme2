#pragma once

#include <tdme/engine/subsystems/renderer/VKRenderer.h>

#include <ext/vulkan/spirv/GlslangToSpv.h>

#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::map;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

/**
 * GL3/Core -> Vulkan shader program
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::renderer::VKGL3CoreShaderProgram
{
private:
	static constexpr bool VERBOSE { false };

	static constexpr uint32_t SHADER_VERTEX_SHADER { VK_SHADER_STAGE_VERTEX_BIT };
	static constexpr uint32_t SHADER_FRAGMENT_SHADER { VK_SHADER_STAGE_FRAGMENT_BIT };
	static constexpr uint32_t SHADER_COMPUTE_SHADER { VK_SHADER_STAGE_COMPUTE_BIT };

	/**
	 * Set up shader constraints/resources
	 * @param resources resources
	 */
	static void shaderInitResources(TBuiltInResource &resources);

	/**
	 * Shader VK type to language converter
	 * @param shaderType shader type
	 */
	static EShLanguage shaderFindLanguage(const VkShaderStageFlagBits shaderType);

	/**
	 * Determine alignment
	 * @param structs structs
	 * @param uniforms uniforms
	 */
	static int determineAlignment(const unordered_map<string, vector<string>>& structs, const vector<string>& uniforms);

	/**
	 * Align
	 * @param alignment alignment
	 * @param offset offset
	 */
	inline static int align(int alignment, int offset) {
		auto alignRemainder = offset % alignment;
		return alignRemainder == 0?offset:offset + (alignment - alignRemainder);
	}

	/**
	 * Add shader uniform buffer object
	 * @param shader shader
	 * @param preprocessorDefinitions preprocessor definitions
	 * @param structs parsed structs
	 * @param uniforms parsed uniforms
	 * @param prefix prefix
	 * @param uniformStructsArrays uniforms and structs arrays
	 * @param uniformsBlock uniforms block
	 */
	static bool addToShaderUniformBufferObject(
		VKRenderer::shader_type& shader,
		const unordered_map<string, string>& preprocessorDefinitions,
		const unordered_map<string, vector<string>>& structs,
		const vector<string>& uniforms,
		const string& prefix,
		unordered_set<string>& uniformStructsArrays,
		string& uniformsBlock
	);

public:
	/**
	 * Loads a shader
	 * @param shader shader
	 * @param type type
	 * @param pathName path name
	 * @param fileName file name
	 * @param definitions preprocessor definitions
	 * @param functions included functions
	 * @return shader handle
	 */
	static void loadShader(VKRenderer::shader_type& shader, int32_t type, const string& pathName, const string& fileName, const string& definitions = string(), const string& functions = string());

	/**
	 * Links attached shaders to a program
	 * @param program program
	 * @return success
	 */
	static bool linkProgram(VKRenderer::program_type& program);
};
