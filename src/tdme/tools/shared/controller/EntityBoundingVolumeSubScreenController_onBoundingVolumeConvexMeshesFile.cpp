#include <tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshesFile.h>

#include <string>

#include <ext/v-hacd/src/VHACD_Lib/public/VHACD.h>

#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/models/TMWriter.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/ModelHelper.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/model/UpVector.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/engine/Object3DModel.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController.h>
#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/views/EntityBoundingVolumeView.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/MutableString.h>

using std::string;
using std::to_string;

using namespace VHACD;

using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshesFile;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::models::TMWriter;
using tdme::engine::model::Color4;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::model::Material;
using tdme::engine::model::ModelHelper;
using tdme::engine::model::Model;
using tdme::engine::model::RotationOrder;
using tdme::engine::model::UpVector;
using tdme::engine::primitives::Triangle;
using tdme::engine::Object3DModel;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::views::EntityBoundingVolumeView;
using tdme::tools::shared::views::PopUps;
using tdme::utils::Console;
using tdme::utils::Exception;
using tdme::utils::MutableString;

class VHACDCallback : public IVHACD::IUserCallback {
public:
	VHACDCallback() {}
    ~VHACDCallback() {};
    void Update(
    	const double overallProgress,
		const double stageProgress,
		const double operationProgress,
        const char* const stage,
		const char* const operation)
    {
    	Console::println(to_string((int)(overallProgress + 0.5)));
    };
};

class VHACDLogger : public IVHACD::IUserLogger {
public:
	VHACDLogger() {}
    ~VHACDLogger() {};
    void Log(const char* const msg)
    {
    	Console::println(msg);
    }
};

EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshesFile::EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshesFile(EntityBoundingVolumeSubScreenController* entityBoundingVolumeSubScreenController, LevelEditorEntity* entityFinal)
	: entityBoundingVolumeSubScreenController(entityBoundingVolumeSubScreenController)
	, entityFinal(entityFinal)
{
}

void EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshesFile::performAction()
{
	entityBoundingVolumeSubScreenController->convexMeshesFile->getController()->setValue(
		entityBoundingVolumeSubScreenController->value->set(
			entityBoundingVolumeSubScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getPathName() +
			"/" +
			entityBoundingVolumeSubScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getFileName()
		)
	);

	for (auto i = 0; i < EntityBoundingVolumeSubScreenController::MODEL_BOUNDINGVOLUME_COUNT; i++) {
		entityBoundingVolumeSubScreenController->onBoundingVolumeNoneApply(entityFinal, i);
	}
	IVHACD* vhacd = CreateVHACD();
	vector<string> convexMeshFileNames;
	try {
		IVHACD::Parameters vhacdParams;
		VHACDCallback vhacdCallback;
		VHACDLogger vhacdLogger;
		vhacdParams.m_logger = &vhacdLogger;
		vhacdParams.m_callback = &vhacdCallback;
		vector<float> meshPoints;
		vector<int> meshTriangles;
		string meshPathName = entityBoundingVolumeSubScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getPathName();
		string meshFileName = entityBoundingVolumeSubScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getFileName();
		auto meshModel = ModelReader::read(
			meshPathName,
			meshFileName
		);
		Object3DModel meshObject3DModel(meshModel);
		vector<Triangle> meshFaceTriangles;
		meshObject3DModel.getFaceTriangles(&meshFaceTriangles);
		for (auto& triangle: meshFaceTriangles) {
			meshTriangles.push_back(meshPoints.size() / 3 + 0);
			meshTriangles.push_back(meshPoints.size() / 3 + 1);
			meshTriangles.push_back(meshPoints.size() / 3 + 2);
			for (auto i = 0; i < triangle.getVertices()->size(); i++) {
				meshPoints.push_back((*triangle.getVertices())[i].getX());
				meshPoints.push_back((*triangle.getVertices())[i].getY());
				meshPoints.push_back((*triangle.getVertices())[i].getZ());
			}
		}
		delete meshModel;
		bool vhacdResult =
			vhacd->Compute(
				&meshPoints[0],
				(unsigned int)meshPoints.size() / 3,
				(const uint32_t *)&meshTriangles[0],
				(unsigned int)meshTriangles.size() / 3,
				vhacdParams
			);
		if (vhacdResult == true) {
			auto convexHulls = vhacd->GetNConvexHulls();
			IVHACD::ConvexHull convexHull;
			for (auto i = 0; i < convexHulls; i++) {
				vhacd->GetConvexHull(i, convexHull);
				auto convexHullFileName = meshFileName + ".cm." + to_string(i) + ".tm";
				Console::println(
					"Saving convex hull@" +
					to_string(i) +
					": " + convexHullFileName +
					", points = " + to_string(convexHull.m_nPoints) +
					", triangles = " + to_string(convexHull.m_nTriangles)
				);
				auto convexHullModel = createModel(
					meshPathName + "/" + convexHullFileName,
					convexHull.m_points,
					convexHull.m_triangles,
					convexHull.m_nPoints,
					convexHull.m_nTriangles
				);
				TMWriter::write(convexHullModel, meshPathName, convexHullFileName);
				delete convexHullModel;
				convexMeshFileNames.push_back(meshPathName + "/" + convexHullFileName);
			}
		}
	} catch (Exception &exception) {
		Console::println(string("Could not create convex hulls: ") + exception.what());
	}
	vhacd->Clean();
	vhacd->Release();
	for (auto i = 0; i < EntityBoundingVolumeSubScreenController::MODEL_BOUNDINGVOLUME_COUNT && i < convexMeshFileNames.size(); i++) {
		entityBoundingVolumeSubScreenController->boundingvolumeConvexMeshFile[i]->getController()->setValue(
			entityBoundingVolumeSubScreenController->value->set(convexMeshFileNames[i])
		);
		entityBoundingVolumeSubScreenController->onBoundingVolumeConvexMeshApply(entityFinal, i);
		entityBoundingVolumeSubScreenController->setupModelBoundingVolumeType(entityFinal, i);
	}
	entityBoundingVolumeSubScreenController->modelPath->setPath(entityBoundingVolumeSubScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getPathName());
	entityBoundingVolumeSubScreenController->view->getPopUpsViews()->getFileDialogScreenController()->close();
}

Model* EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshesFile::createModel(const string& id, double* points, uint32_t* triangles, uint32_t pointCount, uint32_t triangleCount) {
	auto model = new Model(id, id, UpVector::Y_UP, RotationOrder::XYZ, nullptr);
	auto material = new Material("tdme.primitive.material");
	material->getAmbientColor().set(0.5f, 0.5f, 0.5f, 1.0f);
	material->getDiffuseColor().set(1.0f, 0.5f, 0.5f, 0.5f);
	material->getSpecularColor().set(0.0f, 0.0f, 0.0f, 1.0f);
	(*model->getMaterials())[material->getId()] = material;
	auto group = new Group(model, nullptr, "group", "group");
	vector<Vector3> vertices;
	vector<Vector3> normals;
	vector<Face> faces;
	int normalIndex = -1;
	for (auto i = 0; i < pointCount; i++) {
		vertices.push_back(
			Vector3(
				static_cast<float>(points[i * 3 + 0]),
				static_cast<float>(points[i * 3 + 1]),
				static_cast<float>(points[i * 3 + 2])
			)
		);
	}
	for (auto i = 0; i < triangleCount; i++) {
		normalIndex = normals.size();
		{
			array<Vector3, 3> faceVertices = {
				vertices.at(triangles[i * 3 + 0]),
				vertices.at(triangles[i * 3 + 1]),
				vertices.at(triangles[i * 3 + 2])
			};
			array<Vector3, 3> faceNormals;
			ModelHelper::computeNormals(&faceVertices, &faceNormals);
			for (auto& normal : faceNormals) {
				normals.push_back(normal);
			}
		}
		faces.push_back(
			Face(
				group,
				triangles[i * 3 + 0],
				triangles[i * 3 + 1],
				triangles[i * 3 + 2],
				normalIndex + 0,
				normalIndex + 1,
				normalIndex + 2
			)
		);
	}
	FacesEntity groupFacesEntity(group, "faces entity");
	groupFacesEntity.setMaterial(material);
	groupFacesEntity.setFaces(&faces);
	vector<FacesEntity> groupFacesEntities;
	groupFacesEntities.push_back(groupFacesEntity);
	group->setVertices(&vertices);
	group->setNormals(&normals);
	group->setFacesEntities(&groupFacesEntities);
	group->determineFeatures();
	(*model->getGroups())["group"] = group;
	(*model->getSubGroups())["group"] = group;
	ModelHelper::prepareForIndexedRendering(model);
	return model;
}
