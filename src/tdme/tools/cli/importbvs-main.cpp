#include <string>
#include <cstdlib>

#include <tdme/application/Application.h>
#include <tdme/engine/Object3DModel.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/models/TMWriter.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/model/UpVector.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/shared/files/ModelMetaDataFileImport.h>
#include <tdme/tools/shared/files/ModelMetaDataFileExport.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityBoundingVolume.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ModelTools.h>
#include <tdme/utilities/StringTools.h>

using tdme::application::Application;
using tdme::engine::Object3DModel;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::models::TMWriter;
using tdme::engine::model::Group;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::RotationOrder;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::model::UpVector;
using tdme::engine::primitives::Triangle;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::shared::files::ModelMetaDataFileImport;
using tdme::tools::shared::files::ModelMetaDataFileExport;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityBoundingVolume;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ModelTools;
using tdme::utilities::StringTools;

static Model* createModel(const string& id, vector<Triangle>& triangles) {
	auto model = new Model(id, id, UpVector::Y_UP, RotationOrder::XYZ, nullptr);
	auto material = new Material("tdme.primitive.material");
	material->setSpecularMaterialProperties(new SpecularMaterialProperties());
	material->getSpecularMaterialProperties()->setAmbientColor(Color4(0.5f, 0.5f, 0.5f, 1.0f));
	material->getSpecularMaterialProperties()->setDiffuseColor(Color4(1.0f, 0.5f, 0.5f, 0.5f));
	material->getSpecularMaterialProperties()->setSpecularColor(Color4(0.0f, 0.0f, 0.0f, 1.0f));
	model->getMaterials()[material->getId()] = material;
	auto group = new Group(model, nullptr, "group", "group");
	vector<Vector3> vertices;
	vector<Vector3> normals;
	vector<Face> faces;
	auto index = 0;
	for (auto& triangle: triangles) {
		for (auto& vertex: triangle.getVertices()) {
			vertices.push_back(vertex);
		}
		{
			array<Vector3, 3> faceVertices = {
				triangle.getVertices()[0],
				triangle.getVertices()[1],
				triangle.getVertices()[2],
			};
			array<Vector3, 3> faceNormals;
			ModelTools::computeNormals(faceVertices, faceNormals);
			for (auto& normal : faceNormals) {
				normals.push_back(normal);
			}
		}
		faces.push_back(
			Face(
				group,
				index + 0,
				index + 1,
				index + 2,
				index + 0,
				index + 1,
				index + 2
			)
		);
		index+= 3;
	}
	FacesEntity groupFacesEntity(group, "faces entity");
	groupFacesEntity.setMaterial(material);
	groupFacesEntity.setFaces(faces);
	vector<FacesEntity> groupFacesEntities;
	groupFacesEntities.push_back(groupFacesEntity);
	group->setVertices(vertices);
	group->setNormals(normals);
	group->setFacesEntities(groupFacesEntities);
	model->getGroups()["group"] = group;
	model->getSubGroups()["group"] = group;
	ModelTools::prepareForIndexedRendering(model);
	return model;
}

int main(int argc, char** argv)
{
	Console::println(string("importbvs 1.9.9"));
	Console::println(string("Programmed 2018 by Andreas Drewke, drewke.net."));
	Console::println();
	if (argc < 3) {
		Console::println("Usage: importbvs inputfile.tmm bvs-model.tm");
		Application::exit(1);
	}
	//
	string tmmFileName = argv[1];
	string bvsModelFileName = argv[2];
	try {
		Console::println("Loading tmm: " + tmmFileName);
		auto tmm = ModelMetaDataFileImport::doImport(
			FileSystem::getInstance()->getPathName(tmmFileName),
			FileSystem::getInstance()->getFileName(tmmFileName)
		);
		Console::println("Loading convex mesh bounding volumes model: " + bvsModelFileName);
		auto bvsModel = ModelReader::read(
			FileSystem::getInstance()->getPathName(bvsModelFileName),
			FileSystem::getInstance()->getFileName(bvsModelFileName)
		);
		vector<string> convexMeshFileNames;
		{
			auto meshFileName = FileSystem::getInstance()->getFileName(bvsModelFileName);
			auto meshPathName = FileSystem::getInstance()->getPathName(bvsModelFileName);
			Object3DModel meshObject3DModel(bvsModel);
			for (auto i = 0; i < meshObject3DModel.getGroupCount(); i++) {
				vector<Triangle> groupTriangles;
				meshObject3DModel.getTriangles(groupTriangles, i);
				auto convexMeshFileName = StringTools::substring(meshFileName, 0, meshFileName.rfind('.')) + "_cm" + to_string(i) + ".tm";
				Console::println(
					"Saving convex mesh model file@" +
					to_string(i) +
					": " + convexMeshFileName +
					", triangles = " + to_string(groupTriangles.size())
				);
				auto convexHullModel = createModel(
					meshPathName + "/" + convexMeshFileName,
					groupTriangles
				);
				TMWriter::write(convexHullModel, meshPathName, convexMeshFileName);
				delete convexHullModel;
				convexMeshFileNames.push_back(meshPathName + "/" + convexMeshFileName);

			}
		}
		for (auto i = 0; i < tmm->getBoundingVolumeCount(); i++) {
			auto bv = tmm->getBoundingVolume(i);
			auto bvModelMesh = bv->getModelMeshFile();
			if (bvModelMesh.empty() == false && FileSystem::getInstance()->fileExists(bvModelMesh) == true) {
				try {
					Console::println(
						"Removing old convex mesh model file@" +
						to_string(i) +
						": " + bvModelMesh
					);
					FileSystem::getInstance()->removeFile(
						FileSystem::getInstance()->getPathName(bvModelMesh),
						FileSystem::getInstance()->getFileName(bvModelMesh)
					);
				} catch (Exception& exception) {
					Console::println("An error occurred: " + string(exception.what()));
				}
			}
		}
		Console::println("Removing old bounding volumes");
		while (tmm->getBoundingVolumeCount() > 0) tmm->removeBoundingVolume(0);
		for (auto& convexMeshFileName: convexMeshFileNames) {
			Console::println(
				"Adding convex mesh bounding volume@" +
				to_string(tmm->getBoundingVolumeCount()) +
				": " + convexMeshFileName
			);
			tmm->addBoundingVolume(tmm->getBoundingVolumeCount(), new LevelEditorEntityBoundingVolume(tmm->getBoundingVolumeCount(), tmm));
			tmm->getBoundingVolume(tmm->getBoundingVolumeCount() - 1)->setupConvexMesh(
				FileSystem::getInstance()->getPathName(convexMeshFileName),
				FileSystem::getInstance()->getFileName(convexMeshFileName)
			);
		}
		Console::println("Saving tmm: " + tmmFileName);
		ModelMetaDataFileExport::doExport(
			FileSystem::getInstance()->getPathName(tmmFileName),
			FileSystem::getInstance()->getFileName(tmmFileName),
			tmm
		);
	} catch (Exception& exception) {
		Console::println("An error occurred: " + string(exception.what()));
	}

}
