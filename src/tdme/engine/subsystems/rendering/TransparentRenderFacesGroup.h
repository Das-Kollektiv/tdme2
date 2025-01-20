#pragma once

#include <string>
#include <tuple>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/BatchRendererTriangles.h>
#include <tdme/engine/subsystems/rendering/EntityRenderer.h>
#include <tdme/engine/Color4.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/Console.h>

using std::string;
using std::tuple;
using std::vector;

using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::subsystems::rendering::BatchRendererTriangles;
using tdme::engine::subsystems::rendering::EntityRenderer;
using tdme::engine::subsystems::rendering::ObjectNode;
using tdme::engine::Color4;
using tdme::math::Matrix4x4;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::utilities::Console;

/**
 * Transparent render faces group
 * @author andreas.drewke
 */
class tdme::engine::subsystems::rendering::TransparentRenderFacesGroup final
{
	friend class ObjectNodeMesh;
	friend class EntityRenderer;
	friend class EntityRenderer_TransparentRenderFacesGroupPool;

private:
	EntityRenderer* entityRenderer { nullptr };
	vector<BatchRendererTriangles*> batchRenderers;
	Model* model { nullptr };
	ObjectNode* objectNode { nullptr };
	int32_t facesEntityIdx;

	Color4 effectColorAdd;
	Color4 effectColorMul;

	const Material* material { nullptr };
	bool textureCoordinates;

	string shader;

	// forbid class copy
	FORBID_CLASS_COPY(TransparentRenderFacesGroup)

	/**
	 * Public constructor
	 */
	TransparentRenderFacesGroup();

	/**
	 * Set transparent render faces group
	 * @param entityRenderer entity renderer
	 * @param model model
	 * @param objectNode object node
	 * @param facesEntityIdx faces entity idx
	 * @param effectColorAdd effect color add
	 * @param effectColorMul effect color mul
	 * @param material material
	 * @param textureCoordinates texture coordinates
	 * @param shader shader
	 */
	void set(EntityRenderer* entityRenderer, Model* model, ObjectNode* objectNode, int32_t facesEntityIdx, const Color4& effectColorAdd, const Color4& effectColorMul, const Material* material, bool textureCoordinates, const string& shader);

	/**
	 * Creates a key for given transparent render faces group attributes
	 * @param model model
	 * @param objectNode object node
	 * @param facesEntityIdx faces entity idx
	 * @param effectColorAdd effect color add
	 * @param effectColorMul effect color mul
	 * @param material material
	 * @param textureCoordinates texture coordinates
	 * @param unique shader id
	 * @returns key
	 */
	inline static const tuple<Model*, ObjectNode*, int32_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, int32_t, const Material*, bool, uint8_t> createKey(Model* model, ObjectNode* objectNode, int32_t facesEntityIdx, const Color4& effectColorAdd, const Color4& effectColorMul, const Material* material, bool textureCoordinates, uint8_t uniqueShaderId) {
		return {
			model,
			objectNode,
			facesEntityIdx,
			static_cast<uint8_t>(effectColorAdd.getRed() * 255.0f),
			static_cast<uint8_t>(effectColorAdd.getGreen() * 255.0f),
			static_cast<uint8_t>(effectColorAdd.getBlue() * 255.0f),
			static_cast<uint8_t>(effectColorAdd.getAlpha() * 255.0f),
			static_cast<uint8_t>(effectColorMul.getRed() * 255.0f),
			static_cast<uint8_t>(effectColorMul.getGreen() * 255.0f),
			static_cast<uint8_t>(effectColorMul.getBlue() * 255.0f),
			static_cast<uint8_t>(effectColorMul.getAlpha() * 255.0f),
			material,
			textureCoordinates,
			uniqueShaderId
		};
	}

	/**
	 * Adds a vertex to this transparent render faces group
	 * @param vertex vertex
	 * @param normal normal
	 * @param textureCoordinate texture coordinate
	 */
	inline void addVertex(const Vector3& vertex, const Vector3& normal, const Vector2& textureCoordinate) {
		// check if we have a batch renderer already?
		if (batchRenderers.size() == 0) {
			// nope, add first one
			auto batchRendererTriangles = entityRenderer->acquireTrianglesBatchRenderer();
			if (batchRendererTriangles == nullptr) {
				Console::printLine(string("TransparentRenderFacesGroup::addVertex(): could not acquire triangles batch rendererBackend"));
				return;
			}
			batchRenderers.push_back(batchRendererTriangles);
		}
		// try to add vertex
		auto batchRendererTriangles = batchRenderers[batchRenderers.size() - 1];
		if (batchRendererTriangles->addVertex(vertex, normal, textureCoordinate) == true)
			return;
		// failed, acquire additionally one
		batchRendererTriangles = entityRenderer->acquireTrianglesBatchRenderer();
		if (batchRendererTriangles == nullptr) {
			Console::printLine(string("TransparentRenderFacesGroup::addVertex(): could not acquire triangles batch rendererBackend"));
			return;
		}
		// 	add it
		batchRenderers.push_back(batchRendererTriangles);
		// 	add vertex
		batchRendererTriangles->addVertex(vertex, normal, textureCoordinate);
	}

	/**
	 * Render this transparent render faces node
	 * @param engine engine
	 * @param rendererBackend renderer backend
	 * @param contextIdx context index
	 */
	void render(Engine* engine, RendererBackend* rendererBackend, int contextIdx);

};
