#include <tdme/engine/prototype/PrototypeBoundingVolume.h>

#include <string>

#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/models/TMReader.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Capsule.h>
#include <tdme/engine/primitives/ConvexMesh.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/engine/Object3DModel.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/os/threading/AtomicOperations.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Primitives.h>
#include <tdme/utilities/StringTools.h>

using std::string;
using std::to_string;

using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::models::TMReader;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::ConvexMesh;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::Sphere;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::Prototype_Type;
using tdme::engine::prototype::PrototypeBoundingVolume;
using tdme::engine::Object3DModel;
using tdme::math::Matrix4x4;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::os::threading::AtomicOperations;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Primitives;
using tdme::utilities::StringTools;

volatile unsigned int PrototypeBoundingVolume::modelIdx = 0;

PrototypeBoundingVolume::PrototypeBoundingVolume(int id, Prototype* prototype)
{
	this->id = id;
	this->prototype = prototype;
	convexMeshFile.clear();
	model = nullptr;
	boundingVolume = nullptr;
	generated = false;
}

PrototypeBoundingVolume::~PrototypeBoundingVolume() {
	if (model != nullptr) delete model;
	if (boundingVolume != nullptr) delete boundingVolume;
}

void PrototypeBoundingVolume::setupNone()
{
	boundingVolume = nullptr;
	model = nullptr;
	convexMeshFile.clear();
	convexMeshData.clear();
	generated = false;
}

int PrototypeBoundingVolume::allocateModelIdx() {
	return AtomicOperations::increment(modelIdx);
}

void PrototypeBoundingVolume::setupSphere(const Vector3& center, float radius)
{
	if (boundingVolume != nullptr) delete boundingVolume;
	boundingVolume = new Sphere(center, radius);
	if (model != nullptr) delete model;
	model = Primitives::createModel(
		boundingVolume,
		string(prototype->getModel() != nullptr ? prototype->getModel()->getId() : "none") +
			string(",") +
			to_string(prototype->getId()) +
			string("_model_bv.") +
			to_string(id) +
			string(".") +
			to_string(allocateModelIdx())
	);
	convexMeshFile.clear();
	convexMeshData.clear();
	generated = false;
}

void PrototypeBoundingVolume::setupCapsule(const Vector3& a, const Vector3& b, float radius)
{
	if (boundingVolume != nullptr) delete boundingVolume;
	boundingVolume = new Capsule(a, b, radius);
	if (model != nullptr) delete model;
	model = Primitives::createModel(
		boundingVolume,
		string(prototype->getModel() != nullptr ? prototype->getModel()->getId() : "none") +
			string(",") +
			to_string(prototype->getId()) +
			string("_model_bv.") +
			to_string(id) +
			string(".") +
			to_string(allocateModelIdx())
	);
	convexMeshFile.clear();
	convexMeshData.clear();
	generated = false;
}

void PrototypeBoundingVolume::setupObb(const Vector3& center, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2, const Vector3& halfExtension)
{
	if (boundingVolume != nullptr) delete boundingVolume;
	boundingVolume = new OrientedBoundingBox(center, axis0, axis1, axis2, halfExtension);
	if (model != nullptr) delete model;
	model = Primitives::createModel(
		boundingVolume,
		string(prototype->getModel() != nullptr ? prototype->getModel()->getId() : "none") +
			string(",") +
			to_string(prototype->getId()) +
			string("_model_bv.") +
			to_string(id) +
			string(".") +
			to_string(allocateModelIdx())
	);
	convexMeshFile.clear();
	convexMeshData.clear();
	generated = false;
}

void PrototypeBoundingVolume::setupAabb(const Vector3& min, const Vector3& max)
{
	if (boundingVolume != nullptr) delete boundingVolume;
	BoundingBox aabb(min, max);
	boundingVolume = new OrientedBoundingBox(&aabb);
	if (model != nullptr) delete model;
	model = Primitives::createModel(
		boundingVolume,
		string(prototype->getModel() != nullptr ? prototype->getModel()->getId() : "none") +
			string(",") +
			to_string(prototype->getId()) +
			string("_model_bv.") +
			to_string(id) +
			string(".") +
			to_string(allocateModelIdx())
	);
	convexMeshFile.clear();
	convexMeshData.clear();
	generated = false;
}

void PrototypeBoundingVolume::clearConvexMesh()
{
	if (boundingVolume != nullptr) delete boundingVolume;
	if (model != nullptr) delete model;
	boundingVolume = nullptr;
	model = nullptr;
	convexMeshFile.clear();
	convexMeshData.clear();
	generated = false;
}

void PrototypeBoundingVolume::setupConvexMesh(const string& pathName, const string& fileName)
{
	if (boundingVolume != nullptr) delete boundingVolume;
	if (model != nullptr) delete model;
	boundingVolume = nullptr;
	model = nullptr;
	convexMeshFile = pathName + "/" + fileName;
	convexMeshData.clear();
	generated = false;
	try {
		auto convexMeshModel = ModelReader::read(
			pathName,
			fileName
		);
		auto convexMeshObject3DModel = new Object3DModel(convexMeshModel);
		boundingVolume = new ConvexMesh(convexMeshObject3DModel);
		delete convexMeshObject3DModel;
		Primitives::setupConvexMeshModel(convexMeshModel);
		model = convexMeshModel;
	} catch (Exception& exception) {
		Console::print(string("PrototypeBoundingVolume::setupConvexMesh(): An error occurred: " + convexMeshFile + ": "));
		Console::println(string(exception.what()));
		setupNone();
	}
}

void PrototypeBoundingVolume::setupConvexMesh(const vector<uint8_t>& data) {
	convexMeshData = data;
	if (boundingVolume != nullptr) delete boundingVolume;
	if (model != nullptr) delete model;
	boundingVolume = nullptr;
	model = nullptr;
	convexMeshFile = string();
	generated = true;
	try {
		auto convexMeshModel = TMReader::read(
			convexMeshData,
			FileSystem::getInstance()->getPathName(prototype->getFileName()),
			FileSystem::getInstance()->getFileName(prototype->getFileName()) + "." + to_string(id)
		);
		auto convexMeshObject3DModel = new Object3DModel(convexMeshModel);
		boundingVolume = new ConvexMesh(convexMeshObject3DModel);
		delete convexMeshObject3DModel;
		Primitives::setupConvexMeshModel(convexMeshModel);
		model = convexMeshModel;
	} catch (Exception& exception) {
		Console::print(string("PrototypeBoundingVolume::setupConvexMesh(): An error occurred: "));
		Console::println(string(exception.what()));
		setupNone();
	}
}
