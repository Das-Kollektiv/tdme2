#include <tdme/engine/fileio/models/FBXReader.h>

#include <fbxsdk.h>

#include <string>
#include <vector>

#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/ModelHelper.h>
#include <tdme/engine/model/Model_UpVector.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utils/Console.h>

using std::string;
using std::to_string;
using std::vector;

using tdme::engine::fileio::models::FBXReader;
using tdme::engine::model::Group;
using tdme::engine::model::Model;
using tdme::engine::model::ModelHelper;
using tdme::engine::model::Model_UpVector;
using tdme::engine::model::RotationOrder;
using tdme::engine::model::TextureCoordinate;
using tdme::math::Vector3;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utils::Console;

Model* FBXReader::read(const string& pathName, const string& fileName) throw (ModelFileIOException, FileSystemException) {
	// init fbx sdk
	FbxManager* fbxManager = NULL;
	FbxScene* fbxScene = NULL;
	fbxManager = FbxManager::Create();
	if (fbxManager == nullptr) {
		Console::println("FBXReader::read(): Unable to create FBX manager.");
		return nullptr;
	} else {
		Console::println(string("FBXReader::read(): Autodesk FBX SDK version ") + string(fbxManager->GetVersion()));
	}
	FbxIOSettings* ios = FbxIOSettings::Create(fbxManager, IOSROOT);
	fbxManager->SetIOSettings(ios);
	FbxString lPath = FbxGetApplicationDirectory();
	fbxManager->LoadPluginsDirectory(lPath.Buffer());
	fbxScene = FbxScene::Create(fbxManager, "My Scene");
	if (fbxScene == nullptr) {
		throw ModelFileIOException("FBXReader::read(): Error: Unable to create FBX scene");
	}

	// create import and import scene
	FbxImporter* fbxImporter = FbxImporter::Create(fbxManager, "");
	bool fbxImportStatus = fbxImporter->Initialize((pathName + "/" + fileName).c_str(), -1, fbxManager->GetIOSettings());
	if (fbxImportStatus == false) {
		throw ModelFileIOException("FBXReader::read(): Error: Unable to import FBX scene from '" + pathName + "/" + fileName);
	}
	if (fbxImporter->IsFBX() == false) {
		throw ModelFileIOException("FBXReader::read(): Error: This is not a FBX file '" + pathName + "/" + fileName);
	}
	// import the scene
	fbxImportStatus = fbxImporter->Import(fbxScene);
	if (fbxImportStatus == false) {
		throw ModelFileIOException("FBXReader::read(): Error: Unable to import FBX scene from '" + pathName + "/" + fileName + " into scene");
	}

	// create model
	auto model = new Model(
		FileSystem::getInstance()->getCanonicalPath(pathName, fileName),
		fileName,
		Model_UpVector::Y_UP,
		RotationOrder::ZYX,
		nullptr
	);

	// process nodes
	processScene(fbxScene, model);

	// destroy the importer
	if (fbxImporter != nullptr) fbxImporter->Destroy();

	// destroy fbx manager
	if (fbxManager != nullptr) fbxManager->Destroy();

	//
	ModelHelper::setupJoints(model);
	ModelHelper::fixAnimationLength(model);
	ModelHelper::prepareForIndexedRendering(model);

	//
	return model;
}

void FBXReader::processScene(FbxScene* fbxScene, Model* model) {
	Console::println("FBXReader::processScene()");
	FbxNode* fbxNode = fbxScene->GetRootNode();
	if (fbxNode == nullptr) return;
	for(auto i = 0; i < fbxNode->GetChildCount(); i++) {
		processNode(fbxNode->GetChild(i), model, nullptr);
	}
}

void FBXReader::processNode(FbxNode* fbxNode, Model* model, Group* parentGroup) {
	Console::println("FBXReader::processNode()");
	Group* group = nullptr;
	if (fbxNode->GetNodeAttribute() != nullptr) {
		auto fbxAttributeType = fbxNode->GetNodeAttribute()->GetAttributeType();
		switch (fbxAttributeType) {
			case FbxNodeAttribute::eMesh:
				{
					auto group = processMeshNode(fbxNode, model, parentGroup);
					if (parentGroup == nullptr) {
						(*model->getSubGroups())[group->getId()] = group;
					} else {
						(*parentGroup->getSubGroups())[group->getId()] = group;
					}
					(*model->getGroups())[group->getId()] = group;
					parentGroup = group;
					break;
				}
			default:
				{
					Console::println("FBXReader::processNode(): unsupported node with attribute type " + to_string(fbxAttributeType));
					break;
				}
		}
	}
	for(auto i = 0; i < fbxNode->GetChildCount(); i++) {
		processNode(fbxNode->GetChild(i), model, parentGroup);
	}
}


Group* FBXReader::processMeshNode(FbxNode* fbxNode, Model* model, Group* parentGroup) {
	auto fbxGroupName = fbxNode->GetName();
	Console::println(string("FBXReader::processNode(): Have mesh node: ") + string(fbxGroupName));
	FbxMesh* fbxMesh = (FbxMesh*)fbxNode->GetNodeAttribute();

	auto group = new Group(model, parentGroup, fbxGroupName, fbxGroupName);
	vector<Vector3> vertices;
	vector<Vector3> normals;
	vector<TextureCoordinate> textureCoordinates;
	vector<Vector3> tangents;
	vector<Vector3> bitangents;
	vector<FacesEntity> facesEntities;

	int fbxVertexId = 0;
	int fbxPolygonCount = fbxMesh->GetPolygonCount();
	FbxVector4* fbxControlPoints = fbxMesh->GetControlPoints();
	int fbxPolyGroupId = 0;
	for (auto i = 0; i < fbxPolygonCount; i++) {
		for (auto l = 0; l < fbxMesh->GetElementPolygonGroupCount(); l++) {
			FbxGeometryElementPolygonGroup* fbxPolygonGroup = fbxMesh->GetElementPolygonGroup(l);
			switch (fbxPolygonGroup->GetMappingMode()) {
			case FbxGeometryElement::eByPolygon:
				if (fbxPolygonGroup->GetReferenceMode() == FbxGeometryElement::eIndex) {
					fbxPolyGroupId = fbxPolygonGroup->GetIndexArray().GetAt(i);
				}
				break;
			default:
				break;
			}
		}
		if (fbxPolyGroupId >= facesEntities.size()) {
			facesEntities.push_back(FacesEntity(group, "facesentity-" + to_string(fbxPolyGroupId)));
		}
		auto& facesEntity = facesEntities[fbxPolyGroupId];
		vector<Face> faces = *facesEntity.getFaces();
		auto fbxPolygonSize = fbxMesh->GetPolygonSize(i);
		auto verticesOffset = vertices.size();
		auto normalsOffset = normals.size();
		auto textureCoordinatesOffset = textureCoordinates.size();
		auto tangentsOffset = tangents.size();
		auto bitangentsOffset = bitangents.size();
		bool haveUV = true;
		bool haveNormal = true;
		bool haveTangent = true;
		bool haveBitangent = true;
		if (fbxPolygonSize != 3) throw ModelFileIOException("we only support triangles in '" + group->getName() + "'");
		for (auto j = 0; j < fbxPolygonSize; j++) {
			int fbxControlPointIndex = fbxMesh->GetPolygonVertex(i, j);
			auto fbxControlPoint = fbxControlPoints[fbxControlPointIndex];
			vertices.push_back(Vector3(fbxControlPoint[0], fbxControlPoint[1], fbxControlPoint[2]));
			for (auto l = 0; l < fbxMesh->GetElementUVCount() && l < 1; ++l) {
				FbxGeometryElementUV* fbxUV = fbxMesh->GetElementUV(l);
				switch (fbxUV->GetMappingMode()) {
					case FbxGeometryElement::eByControlPoint:
						switch (fbxUV->GetReferenceMode()) {
							case FbxGeometryElement::eDirect:
								{
									auto fbxUVArray = fbxUV->GetDirectArray().GetAt(fbxControlPointIndex);
									textureCoordinates.push_back(TextureCoordinate(fbxUVArray[0], fbxUVArray[1]));
									break;
								}
							case FbxGeometryElement::eIndexToDirect:
								{
									auto fbxUVArray = fbxUV->GetDirectArray().GetAt(fbxUV->GetIndexArray().GetAt(fbxControlPointIndex));
									textureCoordinates.push_back(TextureCoordinate(fbxUVArray[0], fbxUVArray[1]));
									break;
								}
							default:
								haveUV = false;
								break;
						}
						break;
					case FbxGeometryElement::eByPolygonVertex:
						{
							switch (fbxUV->GetReferenceMode()) {
								case FbxGeometryElement::eDirect:
								case FbxGeometryElement::eIndexToDirect:
									{
										auto fbxUVArray = fbxUV->GetDirectArray().GetAt(fbxMesh->GetTextureUVIndex(i, j));
										textureCoordinates.push_back(TextureCoordinate(fbxUVArray[0], fbxUVArray[1]));
										break;
									}
								default:
									haveUV = false;
									break;
							}
							break;
						}
						default:
							haveUV = false;
							break;
				}
			}
			for (auto l = 0; l < fbxMesh->GetElementNormalCount() && l < 1; ++l) {
				FbxGeometryElementNormal* fbxNormal = fbxMesh->GetElementNormal(l);
				if (fbxNormal->GetMappingMode() == FbxGeometryElement::eByPolygonVertex) {
					switch (fbxNormal->GetReferenceMode()) {
						case FbxGeometryElement::eDirect:
							{
								auto fbxNormalArray = fbxNormal->GetDirectArray().GetAt(fbxVertexId);
								normals.push_back(Vector3(fbxNormalArray[0], fbxNormalArray[1], fbxNormalArray[2]));
							}
							break;
						case FbxGeometryElement::eIndexToDirect:
							{
								auto fbxNormalArray = fbxNormal->GetDirectArray().GetAt(fbxNormal->GetIndexArray().GetAt(fbxVertexId));
								normals.push_back(Vector3(fbxNormalArray[0], fbxNormalArray[1], fbxNormalArray[2]));
								break;
							}
						default:
							haveNormal = false;
							break;
					}
				} else {
					haveNormal = false;
				}
			}
			for (auto l = 0; l < fbxMesh->GetElementTangentCount() && l < 1; ++l) {
				FbxGeometryElementTangent* fbxTangent = fbxMesh->GetElementTangent(l);
				if (fbxTangent->GetMappingMode() == FbxGeometryElement::eByPolygonVertex) {
					switch (fbxTangent->GetReferenceMode()) {
						case FbxGeometryElement::eDirect:
							{
								auto fbxTangentArray = fbxTangent->GetDirectArray().GetAt(fbxVertexId);
								tangents.push_back(Vector3(fbxTangentArray[0], fbxTangentArray[1], fbxTangentArray[2]));
							}
							break;
						case FbxGeometryElement::eIndexToDirect:
							{
								auto fbxTangentArray = fbxTangent->GetDirectArray().GetAt(fbxTangent->GetIndexArray().GetAt(fbxVertexId));
								tangents.push_back(Vector3(fbxTangentArray[0], fbxTangentArray[1], fbxTangentArray[2]));
								break;
							}
						default:
							haveTangent = false;
							break;
					}
				} else {
					haveTangent = false;
				}
			}
			for (auto l = 0; l < fbxMesh->GetElementBinormalCount() && l < 1; ++l) {
				FbxGeometryElementBinormal* fbxBinormal = fbxMesh->GetElementBinormal(l);
				if (fbxBinormal->GetMappingMode() == FbxGeometryElement::eByPolygonVertex) {
					switch (fbxBinormal->GetReferenceMode()) {
						case FbxGeometryElement::eDirect:
							{
								auto fbxBinormalArray = fbxBinormal->GetDirectArray().GetAt(fbxVertexId);
								bitangents.push_back(Vector3(fbxBinormalArray[0], fbxBinormalArray[1], fbxBinormalArray[2]));
							}
							break;
						case FbxGeometryElement::eIndexToDirect:
							{
								auto fbxBinormalArray = fbxBinormal->GetDirectArray().GetAt(fbxBinormal->GetIndexArray().GetAt(fbxVertexId));
								bitangents.push_back(Vector3(fbxBinormalArray[0], fbxBinormalArray[1], fbxBinormalArray[2]));
								break;
							}
						default:
							haveBitangent = false;
							break;
					}
				} else {
					haveBitangent = false;
				}
			}
			fbxVertexId++;
		}
		Face f(
			group,
			verticesOffset + 0,
			verticesOffset + 1,
			verticesOffset + 2,
			normalsOffset + 0,
			normalsOffset + 1,
			normalsOffset + 2
		);
		if (haveUV == true) {
			f.setTextureCoordinateIndices(
				textureCoordinatesOffset + 0,
				textureCoordinatesOffset + 1,
				textureCoordinatesOffset + 2
			);
		}
		// TODO: tangents, bitangents
		faces.push_back(f);
		facesEntity.setFaces(&faces);
	}

	group->setVertices(&vertices);
	group->setNormals(&normals);
	if (tangents.size() > 0 && bitangents.size() > 0) {
		group->setTangents(&tangents);
		group->setBitangents(&bitangents);
	}
	if (textureCoordinates.size() > 0) group->setTextureCoordinates(&textureCoordinates);
	group->setFacesEntities(&facesEntities);
	group->determineFeatures();

	return group;
}
