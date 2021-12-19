#pragma once

#include <array>
#include <map>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/EntityShaderParameters.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix2D3x3.h>
#include <tdme/math/Matrix4x4.h>

using std::array;
using std::map;
using std::string;

using tdme::engine::subsystems::renderer::Renderer;

using tdme::engine::EntityShaderParameters;
using tdme::math::Matrix2D3x3;
using tdme::math::Matrix4x4;

/**
 * Single threaded renderer
 * @author Andreas Drewke
 * @ersion $Id$
 */
class tdme::engine::subsystems::renderer::SingleThreadedRenderer: public Renderer
{
private:
	array<float, 4> effectColorMul {{ 1.0f, 1.0f, 1.0f, 1.0f }};
	array<float, 4> effectColorAdd {{ 0.0f, 0.0f, 0.0f, 0.0f }};
	Renderer_SpecularMaterial specularMaterial;
	Renderer_PBRMaterial pbrMaterial;
	array<Renderer_Light, 8> lights;
	Matrix2D3x3 textureMatrix;
	float maskMaxValue { 1.0f };
	int32_t lighting { 0 };
	array<float, 3> environmentMappingCubeMapPosition;
protected:
	string shader;
	EntityShaderParameters shaderParameters;

public:
	/**
	 * Public constructor
	 */
	SingleThreadedRenderer();

	/**
	 * Destructor
	 */
	virtual ~SingleThreadedRenderer();

	// overridden methods
	virtual int32_t getLighting(int contextIdx) override;
	virtual void setLighting(int contextIdx, int32_t lighting) override;
	virtual Matrix2D3x3& getTextureMatrix(int contextIdx) override;
	virtual Renderer_Light& getLight(int contextIdx, int32_t lightId) override;
	virtual array<float, 4>& getEffectColorMul(int contextIdx) override;
	virtual array<float, 4>& getEffectColorAdd(int contextIdx) override;
	virtual Renderer_SpecularMaterial& getSpecularMaterial(int contextIdx) override;
	virtual Renderer_PBRMaterial& getPBRMaterial(int contextIdx) override;
	virtual const string& getShader(int contextIdx) override;
	virtual void setShader(int contextIdx, const string& id) override;
	virtual const EntityShaderParameters& getShaderParameters(int contextIdx) override;
	virtual void setShaderParameters(int contextIdx, const EntityShaderParameters& parameters) override;
	virtual float getMaskMaxValue(int contextIdx) override;
	virtual void setMaskMaxValue(int contextIdx, float maskMaxValue) override;
	virtual array<float, 3>& getEnvironmentMappingCubeMapPosition(int contextIdx) override;
	virtual void setEnvironmentMappingCubeMapPosition(int contextIdx, array<float, 3>& position) override;
	virtual const Renderer_Statistics getStatistics() override;

};
