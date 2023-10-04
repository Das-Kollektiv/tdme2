#include <tdme/engine/subsystems/lighting/LightingShaderTerrainEditorImplementation.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/lighting/LightingShaderConstants.h>
#include <tdme/engine/subsystems/lighting/LightingShaderTerrainImplementation.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Engine.h>
#include <tdme/math/Matrix3x3.h>
#include <tdme/math/Vector2.h>

using std::string;
using std::to_string;

using tdme::engine::subsystems::lighting::LightingShaderConstants;
using tdme::engine::subsystems::lighting::LightingShaderTerrainEditorImplementation;
using tdme::engine::subsystems::lighting::LightingShaderTerrainImplementation;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;
using tdme::math::Matrix3x3;
using tdme::math::Vector2;

LightingShaderTerrainEditorImplementation::LightingShaderTerrainEditorImplementation(Renderer* renderer): LightingShaderTerrainImplementation(renderer)
{
	additionalDefinitions = "\n#define HAVE_TERRAIN_SHADER_EDITOR";
}

const string LightingShaderTerrainEditorImplementation::getId() {
	return "terraineditor";
}

void LightingShaderTerrainEditorImplementation::initialize()
{
	LightingShaderTerrainImplementation::initialize();

	if (initialized == false) return;

	//
	initialized = false;

	uniformBrushEnabled = renderer->getProgramUniformLocation(programId, "brushEnabled");
	if (uniformBrushEnabled == -1) return;

	uniformBrushTextureMatrix = renderer->getProgramUniformLocation(programId, "brushTextureMatrix");
	if (uniformBrushTextureMatrix == -1) return;

	uniformBrushTextureUnit = renderer->getProgramUniformLocation(programId, "brushTextureUnit");
	if (uniformBrushTextureUnit == -1) return;

	uniformBrushPosition = renderer->getProgramUniformLocation(programId, "brushPosition");
	if (uniformBrushPosition == -1) return;

	uniformBrushTextureDimension = renderer->getProgramUniformLocation(programId, "brushTextureDimension");
	if (uniformBrushTextureDimension == -1) return;

	//
	initialized = true;
}

void LightingShaderTerrainEditorImplementation::registerShader() {
	Engine::registerShader(
		Engine::ShaderType::SHADERTYPE_OBJECT,
		getId(),
		{} // no public parameters
	);
}

void LightingShaderTerrainEditorImplementation::useProgram(Engine* engine, int contextIdx) {
	LightingShaderTerrainImplementation::useProgram(engine, contextIdx);

	//
	auto currentTextureUnit = renderer->getTextureUnit(contextIdx);
	renderer->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_TERRAIN_BRUSH);
	renderer->bindTexture(contextIdx, engine->getShaderParameter(getId(), "brushTexture").getIntegerValue());
	renderer->setTextureUnit(contextIdx, currentTextureUnit);

	//
	Matrix3x3 brushTextureMatrix;
	brushTextureMatrix.identity();
	brushTextureMatrix.multiply((Matrix3x3()).identity().setTranslation(Vector2(0.5f, 0.5f)));
	brushTextureMatrix.multiply((Matrix3x3()).identity().scale(
		Vector2(
			1.0f / engine->getShaderParameter(getId(), "brushScale").getVector2Value().getX(),
			1.0f / engine->getShaderParameter(getId(), "brushScale").getVector2Value().getY()
		)
	));
	brushTextureMatrix.multiply((Matrix3x3()).identity().setAxes(engine->getShaderParameter(getId(), "brushRotation").getFloatValue()));

	//
	renderer->setProgramUniformInteger(contextIdx, uniformBrushEnabled, engine->getShaderParameter(getId(), "brushEnabled").getBooleanValue() == true?1:0);
	renderer->setProgramUniformInteger(contextIdx, uniformBrushTextureUnit, LightingShaderConstants::SPECULAR_TEXTUREUNIT_TERRAIN_BRUSH);
	renderer->setProgramUniformFloatMatrix3x3(contextIdx, uniformBrushTextureMatrix, brushTextureMatrix.getArray());
	renderer->setProgramUniformFloatVec2(contextIdx, uniformBrushTextureDimension, engine->getShaderParameter(getId(), "brushDimension").getVector2Value().getArray());
	renderer->setProgramUniformFloatVec2(contextIdx, uniformBrushPosition, engine->getShaderParameter(getId(), "brushPosition").getVector2Value().getArray());
}
