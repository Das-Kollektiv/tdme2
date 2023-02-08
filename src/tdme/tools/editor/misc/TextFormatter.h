#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>

#include <ext/tinyxml/tinyxml.h>

using std::string;
using std::vector;

using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIStyledTextNode;

using tinyxml::TiXmlElement;

/**
 * Text formatter
 * @author Andreas Drewke
 */
class tdme::tools::editor::misc::TextFormatter final
{
private:
	// these were grabbed from gedit, yaaaa, not sure about License
	GUIColor commentLineColor;
	GUIColor commentInlineColor;
	GUIColor literalColor;
	GUIColor keyword1Color;
	GUIColor keyword2Color;
	GUIColor preprocessorColor;

	struct Language {
		string name;
		vector<string> extensions;
		string commentLine;
		string commentInlineStart;
		string commentInlineEnd;
		string preprocessorLineKeywords;
		string keywordDelimiters;
		string keywordQuotes;
		string keywords1;
	    string keywords2;
	    string datatypeLiteralSuffixes;
	    string statementDelimiter;
	    vector<string> preprocessorLineKeywordsTokenized;
	    vector<string> keywords1Tokenized;
	    vector<string> keywords2Tokenized;
	    vector<string> datatypeLiteralSuffixesTokenized;
	};

	Language cpp = {
		// I have taken CPP keywords1+2 from NotePad++, not sure about license
		.name = "C++",
		.extensions = {"cpp", "hpp", "h", "c"},
		.commentLine = "//",
		.commentInlineStart = "/*",
		.commentInlineEnd = "*/",
		.preprocessorLineKeywords = "#if #ifdef #ifndef #elif #else #endif #define #include #pragma #undef #error",
		.keywordDelimiters = " \t\n:;=-+*/%&|!~<>{}()[],?",
		.keywordQuotes = "\"\'",
		.keywords1 = "alignof and and_eq bitand bitor break case catch compl const_cast continue default delete do dynamic_cast else false for goto if namespace new not not_eq nullptr operator or or_eq reinterpret_cast return sizeof static_assert static_cast switch this throw true try typedef typeid using while xor xor_eq NULL",
	    .keywords2 = "alignas asm auto bool char char16_t char32_t class clock_t concept const consteval constexpr constinit decltype double enum explicit export extern final float friend inline int int8_t int16_t int32_t int64_t int_fast8_t int_fast16_t int_fast32_t int_fast64_t intmax_t intptr_t long mutable noexcept override private protected ptrdiff_t public register requires short signed size_t ssize_t static struct template thread_local time_t typename uint8_t uint16_t uint32_t uint64_t uint_fast8_t uint_fast16_t uint_fast32_t uint_fast64_t uintmax_t uintptr_t union unsigned virtual void volatile wchar_t",
	    .datatypeLiteralSuffixes = "u U l L ul uL Ul UL lu lU Lu LU ll LL ull uLL Ull ULL llu llU LLu LLU f F l L",
	    .statementDelimiter = ";"
	};

	Language glsl = {
		// see: https://www.lighthouse3d.com/2013/01/notepad-glsl-4-3-syntax-highlight/
		.name = "GLSL",
		.extensions = {"glsl", "frag", "vert"},
		.commentLine = "//",
		.commentInlineStart = "/*",
		.commentInlineEnd = "*/",
		.preprocessorLineKeywords = "#if #ifdef #ifndef #elif #else #endif #define #include #pragma #undef #error #extension #version #line",
		.keywordDelimiters = " \t\n:;=-+*/%&|!~<>{}()[],?",
		.keywordQuotes = "\"\'",
		.keywords1 = "radians degrees sin cos tan asin acos atan sinh cosh tanh asinh acosh atanh pow exp log exp2 log2 sqrt inversqrt abs sign floor trunc round roundEven ceil fract mod modf min max clamp mix step smoothstep isnan isinf floatBitsToInt floatBitsToUInt intBitsToFloat uintBitsToFloat fma frexp ldexp packUnorm2x16 packSnorm2x16 packUnorm4x8 packSnorm4x8 unpackUnorm2x16 unpackSnorm2x16 unpackUnorm4x8 unpackSnorm4x8 packDouble2x32 unpackDouble2x32 packHalf2x16 unpackHalf2x16 length distance dot cross normalize faceforward reflect refract matrixCompMult outerProduct transpose determinant inverse lessThan lessThanEqual greaterThan greaterThanEqual equal notEqual any all not uaddCarry usubBorrow umulExtended imulExtended bitfieldExtract bitfieldInsert bitfieldReverse findLSB bitCount findMSB textureSize textureQueryLod textureQueryLevels texture textureProj textureLod textureOffset texelFetch texelFetchOffset textureProjOffset textureLodOffset textureProjLod textureProjLodOffset textureGrad textureGradOffset textureProjGrad textureProjGradOffset textureGather textureGatherOffset textureGatherOffsets texture1D texture1DProj texture1DLod texture1DProjLod texture2D texture2DProj texture2DLod texture2DProjLod texture3D texture3DProj texture3DLod texture3DProjLod textureCube textureCubeLod shadow1D shadow2D shadow1DProj shadow2DProj shadow1DLod shadow2DLod shadow1DProjLod shadow2DProjLod atomicCounterIncrement atomicCounterDecrement atomicCounter atomicAdd atomicMin atomicMax atomicAnd atomicOr atomicXor atomicExchange atomicCompSwap imageSize imageLoad imageStore imageAtomicAdd imageAtomicMin imageAtomicMax imageAtomicAnd imageAtomicOr imageAtomicXor imageAtomicExchange imageAtomicCompSwap dFdx dFdy fwidth interpolateAtCentroid interpolateAtSample interpolateAtOffset noise1 noise2 noise3 noise4 EmitStreamVertex EndStreamPrimitive EmitVertex EndPrimitive barrier memoryBarrier memoryBarrierAtomicCounter memoryBarrierBuffer memoryBarrierShared memoryBarrierImage groupMemoryBarrier",
	    .keywords2 = "attribute const uniform varying buffer shared coherent volatile restrict readonly writeonly struct layout centroid flat smooth noperspective patch sample break continue do for while switch case default if else subroutine in out inout true false invariant discard return lowp mediump highp precision sampler1D sampler2D sampler3D samplerCube sampler1DShadow sampler2DShadow samplerCubeShadow sampler1DArray sampler2DArray sampler1DArrayShadow sampler2DArrayShadow isampler1D isampler2D isampler3D isamplerCube isampler1DArray isampler2DArray usampler1D usampler2D usampler3D usamplerCube usampler1DArray usampler2DArray sampler2DRect sampler2DRectShadow isampler2DRect usampler2DRect samplerBuffer isamplerBuffer usamplerBuffer sampler2DMS isampler2DMS usampler2DMS sampler2DMSArray isampler2DMSArray usampler2DMSArray samplerCubeArray samplerCubeArrayShadow isamplerCubeArray usamplerCubeArray image1D iimage1D uimage1D image2D iimage2D uimage2D image3D iimage3D uimage3D image2DRect iimage2DRect uimage2DRect imageCube iimageCube uimageCube imageBuffer iimageBuffer uimageBuffer image1DArray iimage1DArray uimage1DArray image2DArray iimage2DArray uimage2DArray imageCubeArray iimageCubeArray uimageCubeArray image2DMS iimage2DMS uimage2DMS image2DMSArray iimage2DMSArray uimage2DMSArray atomic_uint mat2 mat3 mat4 dmat2 dmat3 dmat4 mat2x2 mat2x3 mat2x4 dmat2x2 dmat2x3 dmat2x4 mat3x2 mat3x3 mat3x4 dmat3x2 dmat3x3 dmat3x4 mat4x2 mat4x3 mat4x4 dmat4x2 dmat4x3 dmat4x4 vec2 vec3 vec4 ivec2 ivec3 ivec4 bvec2 bvec3 bvec4 dvec2 dvec3 dvec4 float double int void bool uint uvec2 uvec3 uvec4",
	    .datatypeLiteralSuffixes = "",
	    .statementDelimiter = ";"
	    // TODO: global variables: gl_NumWorkGroups gl_WorkGroupSize gl_WorkGroupID gl_LocalInvocationID gl_GlobalInvocationID gl_LocalInvocationIndex gl_VertexID gl_InstanceID gl_PerVertex gl_Position gl_PointSize gl_ClipDistance gl_in gl_PrimitiveIDIn gl_InvocationID gl_Layer gl_ViewportIndex gl_PatchVerticesIn gl_InvocationID gl_out gl_TessLevelOuter gl_TessLevelInner gl_PatchVerticesIn gl_PrimitiveID gl_TessCoord gl_FragCoord gl_FrontFacing gl_ClipDistance gl_PointCoord gl_PrimitiveID gl_SampleID gl_SamplePosition gl_SampleMaskIn gl_Layer gl_ViewportIndex gl_FragDepth gl_SampleMask
	    // TODO: constraints: gl_MaxComputeWorkGroupCount gl_MaxComputeWorkGroupSize gl_MaxComputeUniformComponents gl_MaxComputeTextureImageUnits gl_MaxComputeImageUniforms gl_MaxComputeAtomicCounters gl_MaxComputeAtomicCounterBuffers gl_MaxVertexAttribs gl_MaxVertexUniformComponents gl_MaxVaryingComponents gl_MaxVertexOutputComponents gl_MaxGeometryInputComponents gl_MaxGeometryOutputComponents gl_MaxFragmentInputComponents gl_MaxVertexTextureImageUnits gl_MaxCombinedTextureImageUnits gl_MaxTextureImageUnits gl_MaxImageUnits gl_MaxCombinedImageUnitsAndFragmentOutputs gl_MaxImageSamples gl_MaxVertexImageUniforms gl_MaxTessControlImageUniforms gl_MaxTessEvaluationImageUniforms gl_MaxGeometryImageUniforms gl_MaxFragmentImageUniforms gl_MaxCombinedImageUniforms gl_MaxFragmentUniformComponents gl_MaxDrawBuffers gl_MaxClipDistances gl_MaxGeometryTextureImageUnits gl_MaxGeometryOutputVertices gl_MaxGeometryTotalOutputComponents gl_MaxGeometryUniformComponents gl_MaxGeometryVaryingComponents gl_MaxTessControlInputComponents gl_MaxTessControlOutputComponents gl_MaxTessControlTextureImageUnits gl_MaxTessControlUniformComponents gl_MaxTessControlTotalOutputComponents gl_MaxTessEvaluationInputComponents gl_MaxTessEvaluationOutputComponents gl_MaxTessEvaluationTextureImageUnits gl_MaxTessEvaluationUniformComponents gl_MaxTessPatchComponents gl_MaxPatchVertices gl_MaxTessGenLevel gl_MaxViewports gl_MaxVertexUniformVectors gl_MaxFragmentUniformVectors gl_MaxVaryingVectors gl_MaxVertexAtomicCounters gl_MaxTessControlAtomicCounters gl_MaxTessEvaluationAtomicCounters gl_MaxGeometryAtomicCounters gl_MaxFragmentAtomicCounters gl_MaxCombinedAtomicCounters gl_MaxAtomicCounterBindings gl_MaxVertexAtomicCounterBuffers gl_MaxTessControlAtomicCounterBuffers gl_MaxTessEvaluationAtomicCounterBuffers gl_MaxGeometryAtomicCounterBuffers gl_MaxFragmentAtomicCounterBuffers gl_MaxCombinedAtomicCounterBuffers gl_MaxAtomicCounterBufferSize gl_MinProgramTexelOffset gl_MaxProgramTexelOffset
	};

	Language tscript = {
		// see: https://www.lighthouse3d.com/2013/01/notepad-glsl-4-3-syntax-highlight/
		.name = "TSCRIPT",
		.extensions = {"tscript"},
		.commentLine = "#",
		.commentInlineStart = "",
		.commentInlineEnd = "",
		.preprocessorLineKeywords = "",
		.keywordDelimiters = " \t\n;=-+*/%&|!~<>()[],",
		.keywordQuotes = "\"",
		.keywords1 = "add and array array.get array.indexOf array.length array.push array.remove array.removeOf array.set bool concatenate console.log div else elseif end equals float forCondition forTime getVariable greater greaterequals if int lesser lesserequals map map.get map.getKeys map.getValues map.has map.remove map.set mat3.identity mat3.multiply mat3.rotate mat3.rotateAroundPoint mat3.rotateAroundTextureCenter mat3.scale mat3.translate mat4.computeEulerAngles mat4.identity mat4.invert mat4.multiply mat4.rotate mat4.scale mat4.translate math.DEG2RAD math.EPSILON math.G math.PI math.abs math.absmod math.acos math.asin math.atan math.atan2 math.ceil math.clamp math.cos math.exp math.floor math.log math.max math.min math.mod math.pow math.random math.round math.sign math.sin math.sqrt math.square math.tan mul not notequal or quaternion.computeMatrix quaternion.identity quaternion.invert quaternion.multiply quaternion.normalize quaternion.rotate return script.call script.disableNamedCondition script.emit script.enableNamedCondition script.evaluate script.getNamedConditions script.getVariables script.stop script.wait script.waitForCondition set set.getKeys set.has set.insert set.remove setVariable space string sub time.getCurrentMillis toLowerCase toUpperCase transform transform.getRotationAngle transform.getRotationAxis transform.getRotationsQuaternion transform.getScale transform.getTransformMatrix transform.getTranslation transform.multiply transform.rotate transform.setRotationAngle transform.setScale transform.setTranslation unsetVariable vec2 vec2.computeDotProduct vec2.computeLength vec2.computeLengthSquared vec2.getX vec2.getY vec2.normalize vec3 vec3.computeAngle vec3.computeCrossProduct vec3.computeDotProduct vec3.computeLength vec3.computeLengthSquared vec3.getX vec3.getY vec3.getZ vec3.normalize vec4 vec4.computeDotProduct vec4.computeLength vec4.computeLengthSquared vec4.getW vec4.getX vec4.getY vec4.getZ vec4.normalize",
	    .keywords2 = "function: on: on-enabled:",
	    .datatypeLiteralSuffixes = "",
	    .statementDelimiter = "\n"
	};

	Language makefile = {
		.name = "MAKEFILE",
		.extensions = {"makefile", "nmake"},
		.commentLine = "#",
		.commentInlineStart = "",
		.commentInlineEnd = "",
		.preprocessorLineKeywords = "",
		.keywordDelimiters = "",
		.keywordQuotes = "\"",
		.keywords1 = "",
	    .keywords2 = "",
	    .datatypeLiteralSuffixes = "",
	    .statementDelimiter = ""
	};

	vector<Language> languages { cpp, glsl, tscript, makefile };

	struct XMLLanguage {
		vector<string> extensions = { "xml" };
		string commentInlineStart = "<!--";
		string commentInlineEnd = "-->";
		string delimiters = " \t\n=";
		string quotes = "\"\'";
	} xmlLanguage;

	struct PropertiesLanguage {
		vector<string> extensions = { "properties" };
		char comment = '#';
		char delimiter = '=';
		string whitespaces = " \t";
	} propertiesLanguage;

	STATIC_DLL_IMPEXT static TextFormatter* instance;

	/**
	 * Returns immediate children tags by tag name
	 * @param parent parent
	 * @param name name
	 * @return matching elements
	 */
	static const vector<TiXmlElement*> getChildrenByTagName(TiXmlElement* parent, const char* name);

	/**
	 * Returns immediate children tags
	 * @param parent parent
	 * @return elements
	 */
	static const vector<TiXmlElement*> getChildren(TiXmlElement* parent);

public:
	struct CodeCompletion {
		struct CodeCompletionSymbol {
			struct CodeCompletionMethodOverload {
				vector<string> parameters;
				string returnValue;
			};
			string name;
			vector<CodeCompletionMethodOverload> overloadList;
		};
		string name;
		vector<CodeCompletionSymbol> symbols;
		string delimiters;
	    string statementDelimiter;
	};

	/**
	 * @return instance
	 */
	inline static TextFormatter* getInstance() {
		if (instance == nullptr) {
			instance = new TextFormatter();
		}
		return instance;
	}

	/**
	 * Public constructor
	 */
	TextFormatter();

	/**
	 * Format given styled text node according to extension
	 * @param extension extension
	 * @param textNode text node
	 * @param charStartIdx character start index
	 * @param charEndIdx character end index
	 */
	void format(const string& extension, GUIStyledTextNode* textNode, int charStartIdx = -1, int charEndIdx = -1);

	/**
	 * Parse code completion
	 */
	const CodeCompletion* loadCodeCompletion(const string& extension);
};
