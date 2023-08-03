#include <tdme/engine/prototype/PrototypeBoundingVolume.h>

#include <memory>
#include <string>
#include <vector>

#include <tdme/tdme.h>
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
#include <tdme/engine/ObjectModel.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Primitives.h>
#include <tdme/utilities/StringTools.h>

using std::make_unique;
using std::move;
using std::string;
using std::to_string;
using std::unique_ptr;
using std::vector;

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
using tdme::engine::ObjectModel;
using tdme::math::Matrix4x4;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Primitives;
using tdme::utilities::StringTools;

PrototypeBoundingVolume::PrototypeBoundingVolume(int id, Prototype* prototype)
{
	this->id = id;
	this->prototype = prototype;
	convexMeshFile.clear();
	generated = false;
}

PrototypeBoundingVolume::~PrototypeBoundingVolume() {
}

void PrototypeBoundingVolume::setupNone()
{
	boundingVolume = nullptr;
	model = nullptr;
	convexMeshFile.clear();
	convexMeshData.clear();
	generated = false;
}

void PrototypeBoundingVolume::setupSphere(const Vector3& center, float radius)
{
	boundingVolume = make_unique<Sphere>(center, radius);
	model = unique_ptr<Model>(
		Primitives::createModel(
			boundingVolume.get(),
			string(prototype->getModel() != nullptr ? prototype->getModel()->getId() : "none") +
				string(",") +
				to_string(prototype->getId()) +
				string("_model_bv.") +
				to_string(id)
		)
	);
	convexMeshFile.clear();
	convexMeshData.clear();
	generated = false;
}

void PrototypeBoundingVolume::setupCapsule(const Vector3& a, const Vector3& b, float radius)
{
	boundingVolume = make_unique<Capsule>(a, b, radius);
	model = unique_ptr<Model>(
		Primitives::createModel(
			boundingVolume.get(),
			string(prototype->getModel() != nullptr ? prototype->getModel()->getId() : "none") +
				string(",") +
				to_string(prototype->getId()) +
				string("_model_bv.") +
				to_string(id) +
				string(".")
		)
	);
	convexMeshFile.clear();
	convexMeshData.clear();
	generated = false;
}

void PrototypeBoundingVolume::setupObb(const Vector3& center, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2, const Vector3& halfExtension)
{
	boundingVolume = make_unique<OrientedBoundingBox>(center, axis0, axis1, axis2, halfExtension);
	model = unique_ptr<Model>(
		Primitives::createModel(
			boundingVolume.get(),
			string(prototype->getModel() != nullptr ? prototype->getModel()->getId() : "none") +
				string(",") +
				to_string(prototype->getId()) +
				string("_model_bv.") +
				to_string(id)
		)
	);
	convexMeshFile.clear();
	convexMeshData.clear();
	generated = false;
}

void PrototypeBoundingVolume::setupAabb(const Vector3& min, const Vector3& max)
{
	BoundingBox aabb(min, max);
	boundingVolume = make_unique<OrientedBoundingBox>(&aabb);
	model = unique_ptr<Model>(
		Primitives::createModel(
			boundingVolume.get(),
			string(prototype->getModel() != nullptr ? prototype->getModel()->getId() : "none") +
				string(",") +
				to_string(prototype->getId()) +
				string("_model_bv.") +
				to_string(id)
		)
	);
	convexMeshFile.clear();
	convexMeshData.clear();
	generated = false;
}

void PrototypeBoundingVolume::clearConvexMesh()
{
	boundingVolume = nullptr;
	model = nullptr;
	convexMeshFile.clear();
	convexMeshData.clear();
	generated = false;
}

void PrototypeBoundingVolume::setupConvexMesh(const string& pathName, const string& fileName)
{
	boundingVolume = nullptr;
	model = nullptr;
	convexMeshFile = pathName + "/" + fileName;
	convexMeshData.clear();
	generated = false;
	try {
		auto convexMeshModel = unique_ptr<Model>(
			ModelReader::read(
				pathName,
				fileName
			)
		);
		auto convexMeshObjectModel = make_unique<ObjectModel>(convexMeshModel.get());
		boundingVolume = make_unique<ConvexMesh>(convexMeshObjectModel.get());
		Primitives::setupConvexMeshModel(convexMeshModel.get());
		model = move(convexMeshModel);
	} catch (Exception& exception) {
		Console::print(string("PrototypeBoundingVolume::setupConvexMesh(): An error occurred: " + convexMeshFile + ": "));
		Console::println(string(exception.what()));
		setupNone();
	}
}

void PrototypeBoundingVolume::setupConvexMesh(const vector<uint8_t>& data) {
	convexMeshData = data;
	boundingVolume = nullptr;
	model = nullptr;
	convexMeshFile = string();
	generated = true;
	try {
		auto convexMeshModel = unique_ptr<Model>(
			TMReader::read(
				convexMeshData,
				FileSystem::getInstance()->getPathName(prototype->getFileName()),
				FileSystem::getInstance()->getFileName(prototype->getFileName()) + "." + to_string(id)
			)
		);
		auto convexMeshObjectModel = make_unique<ObjectModel>(convexMeshModel.get());
		boundingVolume = make_unique<ConvexMesh>(convexMeshObjectModel.get());
		Primitives::setupConvexMeshModel(convexMeshModel.get());
		model = move(convexMeshModel);
	} catch (Exception& exception) {
		Console::print(string("PrototypeBoundingVolume::setupConvexMesh(): An error occurred: "));
		Console::println(string(exception.what()));
		setupNone();
	}
}
