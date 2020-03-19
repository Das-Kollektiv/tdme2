#pragma once

#include <array>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/subsystems/renderer/Renderer_Light.h>
#include <tdme/engine/subsystems/renderer/Renderer_SpecularMaterial.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix2D3x3.h>
#include <tdme/math/Matrix4x4.h>

using std::array;
using std::string;

using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::renderer::Renderer_Light;
using tdme::engine::subsystems::renderer::Renderer_SpecularMaterial;
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
	array<Renderer_Light, 8> lights;
	Matrix2D3x3 textureMatrix;
	float maskMaxValue { 1.0f };
	int32_t lighting { 0 };

protected:
	string shader;

public:
	// overriden methods
	virtual int32_t getLighting(void* context) override;
	virtual void setLighting(void* context, int32_t lighting) override;
	virtual Matrix2D3x3& getTextureMatrix(void* context) override;
	virtual Renderer_Light& getLight(void* context, int32_t lightId) override;
	virtual array<float, 4>& getEffectColorMul(void* context) override;
	virtual array<float, 4>& getEffectColorAdd(void* context) override;
	virtual Renderer_SpecularMaterial& getSpecularMaterial(void* context) override;
	virtual const string getShader(void* context) override;
	virtual void setShader(void* context, const string& id) override;
	virtual float getMaskMaxValue(void* context) override;
	virtual void setMaskMaxValue(void* context, float maskMaxValue) override;

	/**
	 * Public constructor
	 */
	SingleThreadedRenderer();

	/**
	 * Destructor
	 */
	virtual ~SingleThreadedRenderer();

private:

	//
	friend class Renderer_SpecularMaterial;
	friend class Renderer_Light;
};
