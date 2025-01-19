#include <tdme/tools/editor/misc/GenerateConvexMeshes.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <VHACD.h>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/models/TMWriter.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/model/UpVector.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/PrototypeBoundingVolume.h>
#include <tdme/engine/ObjectModel.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIParentNode.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/StandardFileSystem.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/controllers/ProgressBarScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>
#include <tdme/utilities/ModelTools.h>
#include <agui/utilities/MutableString.h>

using tdme::tools::editor::misc::GenerateConvexMeshes;

using std::make_unique;
using std::string;
using std::to_string;
using std::unordered_map;
using std::unique_ptr;
using std::vector;

using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::models::TMWriter;
using tdme::engine::Color4;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::model::RotationOrder;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::model::UpVector;
using tdme::engine::primitives::Triangle;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeBoundingVolume;
using tdme::engine::ObjectModel;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::StandardFileSystem;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::controllers::ProgressBarScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;
using tdme::utilities::ModelTools;
using agui::utilities::MutableString;

void GenerateConvexMeshes::removeConvexMeshes(Prototype* prototype)
{
	// delete old convex meshes
	for (int i = 0; i < prototype->getBoundingVolumeCount(); i++) {
		auto boundingVolume = prototype->getBoundingVolume(i);
		if (boundingVolume->isGenerated() == false) {
			continue;
		} else {
			if (boundingVolume->getConvexMeshFile().empty() == false &&
				FileSystem::getInstance()->exists(boundingVolume->getConvexMeshFile()) == true) {
				FileSystem::getInstance()->removeFile(
					FileSystem::getInstance()->getPathName(boundingVolume->getConvexMeshFile()),
					FileSystem::getInstance()->getFileName(boundingVolume->getConvexMeshFile())
				);
				prototype->removeBoundingVolume(i);
				i--;
			} else
			if (boundingVolume->getConvexMeshData().empty() == false) {
				prototype->removeBoundingVolume(i);
				i--;
			}
		}
	}
}

bool GenerateConvexMeshes::generateConvexMeshes(Prototype* prototype, Mode mode, PopUps* popUps, const string& pathName, const string& fileName, vector<vector<uint8_t>>& convexMeshTMsData, VHACD::IVHACD::Parameters parameters)
{
	auto success = true;
	if (mode == MODE_GENERATE) {
		class VHACDCallback : public VHACD::IVHACD::IUserCallback {
			private:
				ProgressBarScreenController* progressBarScreenController;
			public:
				VHACDCallback(ProgressBarScreenController* progressBarScreenController): progressBarScreenController(progressBarScreenController) {}
				~VHACDCallback() {};
				void Update(
					const double overallProgress,
					const double stageProgress,
					const double operationProgress,
					const char* const stage,
					const char* const operation)
				{
					// progressBarScreenController->progress((int)(overallProgress + 0.5) / 100.0f);
				};
		};

		class VHACDLogger : public VHACD::IVHACD::IUserLogger {
			public:
				VHACDLogger() {}
				~VHACDLogger() {};
				void Log(const char* const msg)
				{
					Console::printLine(msg);
				}
		};

		//
		// if (popUps != nullptr) popUps->getProgressBarScreenController()->show("Generate convex meshes ...");
		auto vhacd = VHACD::CreateVHACD();
		try {
			//
			parameters.m_maxRecursionDepth = 15;
			//
			if (parameters.m_resolution < 10000 || parameters.m_resolution > 64000000) {
				throw ExceptionBase("Resolution must be between 10000 and 64000000");
			}
			if (parameters.m_minimumVolumePercentErrorAllowed < 0.0f || parameters.m_minimumVolumePercentErrorAllowed > 100.0f) {
				throw ExceptionBase("Concavity must be between 0.0 and 100.0");
			}
			if (parameters.m_maxNumVerticesPerCH < 4 || parameters.m_maxNumVerticesPerCH > 1024) {
				throw ExceptionBase("Max number of vertices per convex hull must be between 4 and 1024");
			}
			if (parameters.m_maxConvexHulls < 1 || parameters.m_maxConvexHulls > 64) {
				throw ExceptionBase("Max number of convex hulls must be between 1 and 64");
			}
			//
			VHACDLogger vhacdLogger;
			parameters.m_logger = &vhacdLogger;
			/*
			if (popUps != nullptr) {
				VHACDCallback vhacdCallback(popUps->getProgressBarScreenController());
				parameters.m_callback = &vhacdCallback;
			}
			*/
			vector<float> meshPoints;
			vector<int> meshTriangles;
			//
			{
				auto meshModel = unique_ptr<Model>(
					ModelReader::read(
						pathName,
						fileName
					)
				);
				{
					ObjectModel meshObjectModel(meshModel.get());
					vector<Triangle> meshFaceTriangles;
					meshObjectModel.getTriangles(meshFaceTriangles);
					for (const auto& triangle: meshFaceTriangles) {
						meshTriangles.push_back(meshPoints.size() / 3 + 0);
						meshTriangles.push_back(meshPoints.size() / 3 + 1);
						meshTriangles.push_back(meshPoints.size() / 3 + 2);
						for (auto i = 0; i < triangle.getVertices().size(); i++) {
							meshPoints.push_back(triangle.getVertices()[i].getX());
							meshPoints.push_back(triangle.getVertices()[i].getY());
							meshPoints.push_back(triangle.getVertices()[i].getZ());
						}
					}
				}
			}
			//
			bool vhacdResult =
				vhacd->Compute(
					&meshPoints[0],
					(unsigned int)meshPoints.size() / 3,
					(const unsigned int *)&meshTriangles[0],
					(unsigned int)meshTriangles.size() / 3,
					parameters
				);
			if (vhacdResult == true) {
				auto convexHulls = vhacd->GetNConvexHulls();
				VHACD::IVHACD::ConvexHull convexHull;
				for (auto i = 0; i < convexHulls; i++) {
					vhacd->GetConvexHull(i, convexHull);
					auto convexHullModel = unique_ptr<Model>(
						createModel(
							fileName + ".cm." + to_string(i) + ".tm",
							convexHull.m_points,
							convexHull.m_triangles
						)
					);
					convexMeshTMsData.push_back(vector<uint8_t>());
					TMWriter::write(convexHullModel.get(), convexMeshTMsData[convexMeshTMsData.size() - 1]);
				}
			}
		} catch (Exception &exception) {
			/*
			if (popUps != nullptr) {
				popUps->getInfoDialogScreenController()->show(
					"Warning: Could not create convex hulls",
					exception.what()
				);
			}
			*/
			Console::printLine("Could not create convex hulls: " + string(exception.what()));
			convexMeshTMsData.clear();
			success = false;
		}
		vhacd->Clean();
		vhacd->Release();
		// if (popUps != nullptr) popUps->getProgressBarScreenController()->close();
	} else
	if (mode == MODE_IMPORT) {
		try {
			//
			auto meshModel = unique_ptr<Model>(
				ModelReader::read(
					pathName,
					fileName
				)
			);
			//
			{
				ObjectModel meshObjectModel(meshModel.get());
				for (auto i = 0; i < meshObjectModel.getNodeCount(); i++) {
					vector<Triangle> nodeTriangles;
					meshObjectModel.getTriangles(nodeTriangles, i);
					auto convexHullModel = unique_ptr<Model>(
						createModel(
							fileName + ".cm." + to_string(i) + ".tm",
							nodeTriangles
						)
					);
					convexMeshTMsData.push_back(vector<uint8_t>());
					TMWriter::write(convexHullModel.get(), convexMeshTMsData[convexMeshTMsData.size() - 1]);
				}
			}
		} catch (Exception &exception) {
			/*
			if (popUps != nullptr) {
				popUps->getInfoDialogScreenController()->show(
					"Warning: Could not create convex hulls",
					exception.what()
				);
			}
			*/
			Console::printLine("Could not create convex hulls: " + string(exception.what()));
			convexMeshTMsData.clear();
			success = false;
		}
	}
	return success;
}

Model* GenerateConvexMeshes::createModel(const string& id, const vector<VHACD::Vertex>& points, const vector<VHACD::Triangle>& triangles) {
	//
	auto model = make_unique<Model>(id, id, UpVector::Y_UP, RotationOrder::XYZ, nullptr);
	//
	auto material = make_unique<Material>("primitive");
	material->setSpecularMaterialProperties(make_unique<SpecularMaterialProperties>().release());
	material->getSpecularMaterialProperties()->setAmbientColor(Color4(0.5f, 0.5f, 0.5f, 1.0f));
	material->getSpecularMaterialProperties()->setDiffuseColor(Color4(1.0f, 0.5f, 0.5f, 0.5f));
	material->getSpecularMaterialProperties()->setSpecularColor(Color4(0.0f, 0.0f, 0.0f, 1.0f));
	//
	auto node = make_unique<Node>(model.get(), nullptr, "node", "node");
	vector<Vector3> vertices;
	vector<Vector3> normals;
	vector<Face> faces;
	int normalIndex = -1;
	for (const auto& vertex: points) {
		vertices.emplace_back(
			static_cast<float>(vertex.mX),
			static_cast<float>(vertex.mY),
			static_cast<float>(vertex.mZ)
		);
	}
	for (const auto& triangle: triangles) {
		normalIndex = normals.size();
		{
			array<Vector3, 3> faceVertices = {
				vertices[triangle.mI0],
				vertices[triangle.mI1],
				vertices[triangle.mI2]
			};
			for (const auto& normal: ModelTools::computeNormals(faceVertices)) {
				normals.push_back(normal);
			}
		}
		faces.emplace_back(
			node.get(),
			triangle.mI0,
			triangle.mI1,
			triangle.mI2,
			normalIndex + 0,
			normalIndex + 1,
			normalIndex + 2
		);
	}
	FacesEntity nodeFacesEntity(node.get(), "faces entity");
	nodeFacesEntity.setMaterial(material.get());
	nodeFacesEntity.setFaces(faces);
	vector<FacesEntity> nodeFacesEntities;
	nodeFacesEntities.push_back(nodeFacesEntity);
	node->setVertices(vertices);
	node->setNormals(normals);
	node->setFacesEntities(nodeFacesEntities);
	model->getNodes()["node"] = node.get();
	model->getSubNodes()["node"] = node.get();
	node.release();
	//
	model->getMaterials()[material->getId()] = material.get();
	material.release();
	//
	ModelTools::prepareForIndexedRendering(model.get());
	//
	return model.release();
}

Model* GenerateConvexMeshes::createModel(const string& id, vector<Triangle>& triangles) {
	auto model = make_unique<Model>(id, id, UpVector::Y_UP, RotationOrder::XYZ, nullptr);
	//
	auto material = make_unique<Material>("primitive");
	material->setSpecularMaterialProperties(make_unique<SpecularMaterialProperties>().release());
	material->getSpecularMaterialProperties()->setAmbientColor(Color4(0.5f, 0.5f, 0.5f, 1.0f));
	material->getSpecularMaterialProperties()->setDiffuseColor(Color4(1.0f, 0.5f, 0.5f, 0.5f));
	material->getSpecularMaterialProperties()->setSpecularColor(Color4(0.0f, 0.0f, 0.0f, 1.0f));
	//
	auto node = make_unique<Node>(model.get(), nullptr, "node", "node");
	vector<Vector3> vertices;
	vector<Vector3> normals;
	vector<Face> faces;
	auto index = 0;
	for (const auto& triangle: triangles) {
		for (const auto& vertex: triangle.getVertices()) {
			vertices.push_back(vertex);
		}
		{
			array<Vector3, 3> faceVertices = {
				triangle.getVertices()[0],
				triangle.getVertices()[1],
				triangle.getVertices()[2],
			};
			for (const auto& normal: ModelTools::computeNormals(faceVertices)) {
				normals.push_back(normal);
			}
		}
		faces.emplace_back(
			node.get(),
			index + 0,
			index + 1,
			index + 2,
			index + 0,
			index + 1,
			index + 2
		);
		index+= 3;
	}
	FacesEntity nodeFacesEntity(node.get(), "faces entity");
	nodeFacesEntity.setMaterial(material.get());
	nodeFacesEntity.setFaces(faces);
	vector<FacesEntity> nodeFacesEntities;
	nodeFacesEntities.push_back(nodeFacesEntity);
	node->setVertices(vertices);
	node->setNormals(normals);
	node->setFacesEntities(nodeFacesEntities);
	//
	model->getNodes()["node"] = node.get();
	model->getSubNodes()["node"] = node.get();
	node.release();
	//
	model->getMaterials()[material->getId()] = material.get();
	material.release();
	//
	ModelTools::prepareForIndexedRendering(model.get());
	//
	return model.release();
}
