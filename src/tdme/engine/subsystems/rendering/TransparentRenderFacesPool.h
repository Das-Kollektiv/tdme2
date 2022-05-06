#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/ObjectNode.h>
#include <tdme/engine/subsystems/rendering/ObjectNodeMesh.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderFace.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderFacesPool_TransparentRenderFacesPool.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Pool.h>

using std::string;
using std::vector;

using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Node;
using tdme::engine::subsystems::rendering::ObjectNode;
using tdme::engine::subsystems::rendering::ObjectNodeMesh;
using tdme::engine::subsystems::rendering::TransparentRenderFace;
using tdme::engine::subsystems::rendering::TransparentRenderFacesPool;
using tdme::engine::subsystems::rendering::TransparentRenderFacesPool_TransparentRenderFacesPool;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utilities::Console;
using tdme::utilities::Pool;

/**
 * Transparent render faces pool
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::subsystems::rendering::TransparentRenderFacesPool final
{
	friend class EntityRenderer;
	friend class tdme::engine::Engine;

private:
	static constexpr int32_t FACES_MAX { 16384 };
	vector<TransparentRenderFace*> transparentRenderFaces;
	TransparentRenderFacesPool_TransparentRenderFacesPool transparentRenderFacesPool;

	/**
	 * Public constructor
	 */
	TransparentRenderFacesPool();

	/**
	 * Creates an array of transparent render faces from
	 * @param modelViewMatrix model view matrix
	 * @param object3DNode object3D node
	 * @param facesEntityIdx faces entity index
	 * @param faceIdx face index
	 */
	inline void createTransparentRenderFaces(Matrix4x4& modelViewMatrix, ObjectNode* object3DNode, int32_t facesEntityIdx, int32_t faceIdx) {
		// retrieve objects we need
		auto& facesEntities = object3DNode->node->getFacesEntities();
		auto& facesEntity = facesEntities[facesEntityIdx];
		auto& faces = facesEntity.getFaces();
		auto nodeTransformedVertices = object3DNode->mesh->vertices;
		// objects we will use for calculations
		float distanceFromCamera;
		Vector3 faceCenter;
		// create transparent render faces
		for (auto i = 0; i < faces.size(); i++) {
			// check for pool overflow
			if (transparentRenderFacesPool.size() >= FACES_MAX) {
				Console::println(string("TransparentRenderFacesPool::createTransparentRenderFaces(): Too many transparent render faces"));
				break;
			}
			// set up face
			auto faceVertexIndices = faces[i].getVertexIndices();
			faceCenter.set(0.0f, 0.0f, 0.0f);
			faceCenter.add((*nodeTransformedVertices)[faceVertexIndices[0]]);
			faceCenter.add((*nodeTransformedVertices)[faceVertexIndices[1]]);
			faceCenter.add((*nodeTransformedVertices)[faceVertexIndices[2]]);
			faceCenter.scale(1.0f / 3.0f);
			faceCenter = modelViewMatrix.multiply(faceCenter);
			distanceFromCamera = -faceCenter.getZ();
			// create transparent render face
			auto transparentRenderFace = transparentRenderFacesPool.allocate();
			transparentRenderFace->object3DNode = object3DNode;
			transparentRenderFace->facesEntityIdx = facesEntityIdx;
			transparentRenderFace->faceIdx = faceIdx;
			transparentRenderFace->distanceFromCamera = distanceFromCamera;
			transparentRenderFaces.push_back(transparentRenderFace);
			faceIdx++;
		}
	}

	/**
	 * Merges given transparent render faces pool into this pool
	 * @param srcTransparentRenderFacesPool transparent render faces pool
	 */
	inline void merge(TransparentRenderFacesPool* srcTransparentRenderFacesPool) {
		for (auto srcTransparentRenderFace: srcTransparentRenderFacesPool->transparentRenderFaces) {
			auto transparentRenderFace = transparentRenderFacesPool.allocate();
			*transparentRenderFace = *srcTransparentRenderFace;
			transparentRenderFaces.push_back(transparentRenderFace);
		}
	}

	/**
	 * Reset
	 */
	void reset();

	/**
	 * @return transparent render faces vector
	 */
	vector<TransparentRenderFace*>& getTransparentRenderFaces();

public:

	/**
	 * @return allocated faces
	 */
	int32_t size();
};
