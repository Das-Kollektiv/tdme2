#pragma once

#include <vector>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/Object3DGroup.h>
#include <tdme/engine/subsystems/rendering/Object3DGroupMesh.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderFace.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderFacesPool_TransparentRenderFacesPool.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Pool.h>

using std::vector;
using std::string;

using tdme::engine::subsystems::rendering::TransparentRenderFacesPool;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::subsystems::rendering::Object3DGroup;
using tdme::engine::subsystems::rendering::Object3DGroupMesh;
using tdme::engine::subsystems::rendering::TransparentRenderFace;
using tdme::engine::subsystems::rendering::TransparentRenderFacesPool_TransparentRenderFacesPool;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utils::Pool;
using tdme::utils::Console;

/** 
 * Transparent render faces pool
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::subsystems::rendering::TransparentRenderFacesPool final
{
	friend class Object3DVBORenderer;
	friend class tdme::engine::Engine;

private:
	static constexpr int32_t FACES_MAX { 16384 };
	vector<TransparentRenderFace*> transparentRenderFaces {  };
	TransparentRenderFacesPool_TransparentRenderFacesPool transparentRenderFacesPool {  };

	/** 
	 * Creates an array of transparent render faces from
	 * @param modelViewMatrix model view matrix
	 * @param object3DGroup object3D group
	 * @param facesEntityIdx faces entity index
	 * @param faceIdx face index
	 */
	inline void createTransparentRenderFaces(Matrix4x4& modelViewMatrix, Object3DGroup* object3DGroup, int32_t facesEntityIdx, int32_t faceIdx) {
		// retrieve objects we need
		auto facesEntities = object3DGroup->group->getFacesEntities();
		auto& facesEntity = (*facesEntities)[facesEntityIdx];
		auto faces = facesEntity.getFaces();
		auto groupTransformedVertices = object3DGroup->mesh->vertices;
		// objects we will use for calculations
		float distanceFromCamera;
		Vector3 tmpVector3;
		// create transparent render faces
		for (auto i = 0; i < faces->size(); i++) {
			// check for pool overflow
			if (transparentRenderFacesPool.size() >= FACES_MAX) {
				Console::println(string("TransparentRenderFacesPool::createTransparentRenderFaces(): Too many transparent render faces"));
				break;
			}
			// set up face
			auto faceVertexIndices = (*faces)[i].getVertexIndices();
			tmpVector3.set(0.0f, 0.0f, 0.0f);
			tmpVector3.add((*groupTransformedVertices)[(*faceVertexIndices)[0]]);
			tmpVector3.add((*groupTransformedVertices)[(*faceVertexIndices)[1]]);
			tmpVector3.add((*groupTransformedVertices)[(*faceVertexIndices)[2]]);
			tmpVector3.scale(1.0f / 3.0f);
			modelViewMatrix.multiply(tmpVector3, tmpVector3);
			distanceFromCamera = -tmpVector3.getZ();
			// create transparent render face
			auto transparentRenderFace = transparentRenderFacesPool.allocate();
			transparentRenderFace->object3DGroup = object3DGroup;
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
	vector<TransparentRenderFace*>* getTransparentRenderFaces();

	/**
	 * Public constructor
	 */
	TransparentRenderFacesPool();

public:

	/**
	 * @return allocated faces
	 */
	int32_t size();
};
