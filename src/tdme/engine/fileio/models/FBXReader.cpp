#include <tdme/engine/fileio/models/FBXReader.h>

#include <fbxsdk.h>

#include <string>
#include <vector>

#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Material.h>
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
using tdme::engine::model::Material;
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
	// import the scene
	fbxImportStatus = fbxImporter->Import(fbxScene);
	if (fbxImportStatus == false) {
		throw ModelFileIOException("FBXReader::read(): Error: Unable to import FBX scene from '" + pathName + "/" + fileName + " into scene");
	}

	// triangulate
	FbxGeometryConverter fbxGeometryConverter(fbxManager);
	fbxGeometryConverter.Triangulate(fbxScene, true);

	// create model
	auto model = new Model(
		FileSystem::getInstance()->getCanonicalPath(pathName, fileName),
		fileName,
		getSceneUpVector(fbxScene),
		getSceneRotationOrder(fbxScene),
		nullptr
	);

	// set up model import matrix
	setupModelImportRotationMatrix(model);
	setupModelScaleRotationMatrix(fbxScene, model);

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

RotationOrder* FBXReader::getSceneRotationOrder(FbxScene* fbxScene) throw (ModelFileIOException) {
	auto upVector = getSceneUpVector(fbxScene);

	// take rotation order from root node now
	FbxNode* fbxNode = fbxScene->GetRootNode();
	EFbxRotationOrder fbxRotationOrder;
	fbxNode->GetRotationOrder(FbxNode::eSourcePivot, fbxRotationOrder);
	if (fbxRotationOrder == eEulerXYZ) {
		if (upVector == Model_UpVector::Y_UP) {
			return RotationOrder::ZYX;
		} else
		if (upVector == Model_UpVector::Z_UP) {
			return RotationOrder::YZX;
		} else {
			throw ModelFileIOException("Unknown Up vector");
		}
	} else {
		throw ModelFileIOException("Not supported rotation order(" + to_string(fbxRotationOrder) + ")");
	}
}

Model_UpVector* FBXReader::getSceneUpVector(FbxScene* fbxScene) throw (ModelFileIOException) {
	int fbxUpVectorSign;
	auto fbxUpVector = fbxScene->GetGlobalSettings().GetAxisSystem().GetUpVector(fbxUpVectorSign);
	switch (fbxUpVector) {
		case FbxAxisSystem::eXAxis:
			throw ModelFileIOException("X-Up is not supported");
		case FbxAxisSystem::eYAxis:
			return Model_UpVector::Y_UP;
		case FbxAxisSystem::eZAxis:
			return Model_UpVector::Z_UP;
		default:
			throw ModelFileIOException("Unknown Up vector");
	}
	return Model_UpVector::Y_UP;
}

void FBXReader::setupModelImportRotationMatrix(Model* model) {
	if (model->getUpVector() == Model_UpVector::Y_UP) {
		// no op
	} else
	if (model->getUpVector() == Model_UpVector::Z_UP) {
		model->getImportTransformationsMatrix().rotate(-90.0f, Vector3(1.0f, 0.0f, 0.0f));
	}
}

void FBXReader::setupModelScaleRotationMatrix(FbxScene* fbxScene, Model* model) {
	FbxSystemUnit fbxSceneSystemUnit = fbxScene->GetGlobalSettings().GetSystemUnit();
	model->getImportTransformationsMatrix().scale(
		static_cast<float>(fbxSceneSystemUnit.GetConversionFactorTo(FbxSystemUnit::m))
	);
}

void FBXReader::processScene(FbxScene* fbxScene, Model* model) {
	FbxNode* fbxNode = fbxScene->GetRootNode();
	if (fbxNode == nullptr) return;
	for(auto i = 0; i < fbxNode->GetChildCount(); i++) {
		processNode(fbxNode->GetChild(i), model, nullptr);
	}
}

void FBXReader::processNode(FbxNode* fbxNode, Model* model, Group* parentGroup) {
	Group* group = nullptr;
	if (fbxNode->GetNodeAttribute() != nullptr) {
		auto fbxAttributeType = fbxNode->GetNodeAttribute()->GetAttributeType();
		switch (fbxAttributeType) {
			case FbxNodeAttribute::eMesh:
				{
					group = processMeshNode(fbxNode, model, parentGroup);
					break;
				}
		}
	}
	if (group == nullptr) {
		auto fbxGroupName = fbxNode->GetName();
		group = new Group(model, parentGroup, fbxGroupName, fbxGroupName);
	}
	FbxAMatrix& fbxNodeLocalTransform = fbxNode->EvaluateLocalTransform();
	group->getTransformationsMatrix().set(
		fbxNodeLocalTransform.Get(0,0),
		fbxNodeLocalTransform.Get(0,1),
		fbxNodeLocalTransform.Get(0,2),
		fbxNodeLocalTransform.Get(0,3),
		fbxNodeLocalTransform.Get(1,0),
		fbxNodeLocalTransform.Get(1,1),
		fbxNodeLocalTransform.Get(1,2),
		fbxNodeLocalTransform.Get(1,3),
		fbxNodeLocalTransform.Get(2,0),
		fbxNodeLocalTransform.Get(2,1),
		fbxNodeLocalTransform.Get(2,2),
		fbxNodeLocalTransform.Get(2,3),
		fbxNodeLocalTransform.Get(3,0),
		fbxNodeLocalTransform.Get(3,1),
		fbxNodeLocalTransform.Get(3,2),
		fbxNodeLocalTransform.Get(3,3)
	);
	if (parentGroup == nullptr) {
		(*model->getSubGroups())[group->getId()] = group;
	} else {
		(*parentGroup->getSubGroups())[group->getId()] = group;
	}
	(*model->getGroups())[group->getId()] = group;
	parentGroup = group;
	for(auto i = 0; i < fbxNode->GetChildCount(); i++) {
		processNode(fbxNode->GetChild(i), model, parentGroup);
	}
}


Group* FBXReader::processMeshNode(FbxNode* fbxNode, Model* model, Group* parentGroup) {
	auto fbxGroupName = fbxNode->GetName();
	FbxMesh* fbxMesh = (FbxMesh*)fbxNode->GetNodeAttribute();

	auto group = new Group(model, parentGroup, fbxGroupName, fbxGroupName);
	vector<Vector3> vertices;
	vector<Vector3> normals;
	vector<TextureCoordinate> textureCoordinates;
	vector<Vector3> tangents;
	vector<Vector3> bitangents;
	vector<FacesEntity> facesEntities;
	vector<Face> faces;

	int fbxVertexId = 0;
	int fbxPolygonCount = fbxMesh->GetPolygonCount();

	FacesEntity* facesEntity = nullptr;

	FbxVector4* fbxControlPoints = fbxMesh->GetControlPoints();
	for (auto i = 0; i < fbxPolygonCount; i++) {
		FbxSurfaceMaterial* fbxMaterial = nullptr;
		int fbxMaterialId = -1;
		for (auto l = 0; l < fbxMesh->GetElementMaterialCount() & l < 1; l++) {
			FbxGeometryElementMaterial* fbxMaterialElement = fbxMesh->GetElementMaterial(l);
			if (fbxMaterialElement->GetMappingMode() == FbxGeometryElement::eAllSame) {
				fbxMaterial = fbxMesh->GetNode()->GetMaterial(fbxMaterialElement->GetIndexArray().GetAt(0));
				fbxMaterialId = fbxMaterialElement->GetIndexArray().GetAt(0);
			} else {
				fbxMaterial = fbxMesh->GetNode()->GetMaterial(fbxMaterialElement->GetIndexArray().GetAt(i));
				fbxMaterialId = fbxMaterialElement->GetIndexArray().GetAt(i);
			}
		}
		Material* material = nullptr;
		if (fbxMaterial == nullptr) {
			material = (*model->getMaterials())["tdme.nomaterial"];
			if (material == nullptr) {
				material = new Material("tdme.nomaterial");
				(*model->getMaterials())[material->getId()] = material;
			}
		} else {
			string fbxMaterialName = fbxMaterial->GetName();
			material = (*model->getMaterials())[fbxMaterialName];
			if (material == nullptr) {
				material = new Material(fbxMaterialName);
				if (fbxMaterial->GetClassId().Is(FbxSurfacePhong::ClassId)) {
					FbxPropertyT<FbxDouble3> fbxDouble3;
					FbxPropertyT<FbxDouble> fbxDouble;
					fbxDouble3 = ((FbxSurfacePhong*)fbxMaterial)->Ambient;
					material->getAmbientColor().set(
						static_cast<float>(fbxDouble3.Get()[0]),
						static_cast<float>(fbxDouble3.Get()[1]),
						static_cast<float>(fbxDouble3.Get()[2]),
						1.0f
					);
					fbxDouble = ((FbxSurfacePhong*)fbxMaterial)->TransparencyFactor;
					fbxDouble3 = ((FbxSurfacePhong*)fbxMaterial)->Diffuse;
					material->getDiffuseColor().set(
						static_cast<float>(fbxDouble3.Get()[0]),
						static_cast<float>(fbxDouble3.Get()[1]),
						static_cast<float>(fbxDouble3.Get()[2]),
						1.0f - static_cast<float>(fbxDouble)
					);
					fbxDouble3 = ((FbxSurfacePhong*)fbxMaterial)->Specular;
					material->getSpecularColor().set(
						static_cast<float>(fbxDouble3.Get()[0]),
						static_cast<float>(fbxDouble3.Get()[1]),
						static_cast<float>(fbxDouble3.Get()[2]),
						1.0f
					);
					fbxDouble3 = ((FbxSurfacePhong*)fbxMaterial)->Emissive;
					material->getEmissionColor().set(
						static_cast<float>(fbxDouble3.Get()[0]),
						static_cast<float>(fbxDouble3.Get()[1]),
						static_cast<float>(fbxDouble3.Get()[2]),
						1.0f
					);
					fbxDouble = ((FbxSurfacePhong*)fbxMaterial)->Shininess;
					material->setShininess(
						static_cast<float>(fbxDouble)
					);
					fbxDouble = ((FbxSurfacePhong*)fbxMaterial)->ReflectionFactor;
				} else
				if (fbxMaterial->GetClassId().Is(FbxSurfaceLambert::ClassId)) {
					FbxPropertyT<FbxDouble3> fbxDouble3;
					FbxPropertyT<FbxDouble> fbxDouble;
					fbxDouble3 = ((FbxSurfaceLambert*)fbxMaterial)->Ambient;
					material->getAmbientColor().set(
						static_cast<float>(fbxDouble3.Get()[0]),
						static_cast<float>(fbxDouble3.Get()[1]),
						static_cast<float>(fbxDouble3.Get()[2]),
						1.0f
					);
					fbxDouble3 = ((FbxSurfaceLambert*)fbxMaterial)->Diffuse;
					fbxDouble = ((FbxSurfaceLambert*)fbxMaterial)->TransparencyFactor;
					material->getDiffuseColor().set(
						static_cast<float>(fbxDouble3.Get()[0]),
						static_cast<float>(fbxDouble3.Get()[1]),
						static_cast<float>(fbxDouble3.Get()[2]),
						1.0f - static_cast<float>(fbxDouble)
					);
					fbxDouble3 = ((FbxSurfaceLambert*)fbxMaterial)->Emissive;
					material->getEmissionColor().set(
						static_cast<float>(fbxDouble3.Get()[0]),
						static_cast<float>(fbxDouble3.Get()[1]),
						static_cast<float>(fbxDouble3.Get()[2]),
						1.0f
					);
				}
				FbxProperty fbxProperty;
				fbxProperty = fbxMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);
				string diffuseTextureFileName =
					fbxProperty.GetSrcObjectCount<FbxLayeredTexture>() == 0?
						(fbxProperty.GetSrcObjectCount<FbxTexture>() > 0?
							FbxCast<FbxFileTexture>(fbxProperty.GetSrcObject<FbxTexture>(0))->GetFileName():
							""
						):
						FbxCast<FbxFileTexture>(fbxProperty.GetSrcObject<FbxLayeredTexture>(0))->GetFileName();
				fbxProperty = fbxMaterial->FindProperty(FbxSurfaceMaterial::sTransparentColor);
				string diffuseTransparencyTextureFileName =
					fbxProperty.GetSrcObjectCount<FbxLayeredTexture>() == 0?
						(fbxProperty.GetSrcObjectCount<FbxTexture>() > 0?
							FbxCast<FbxFileTexture>(fbxProperty.GetSrcObject<FbxTexture>(0))->GetFileName():
							""
						):
						FbxCast<FbxFileTexture>(fbxProperty.GetSrcObject<FbxLayeredTexture>(0))->GetFileName();
				if (diffuseTextureFileName.length() > 0) {
					material->setDiffuseTexture(
						FileSystem::getInstance()->getPathName(diffuseTextureFileName),
						FileSystem::getInstance()->getFileName(diffuseTextureFileName),
						FileSystem::getInstance()->getPathName(diffuseTransparencyTextureFileName),
						FileSystem::getInstance()->getFileName(diffuseTransparencyTextureFileName)
					);
				}
				fbxProperty = fbxMaterial->FindProperty(FbxSurfaceMaterial::sNormalMap);
				string normalTextureFileName =
					fbxProperty.GetSrcObjectCount<FbxLayeredTexture>() == 0?
						(fbxProperty.GetSrcObjectCount<FbxTexture>() > 0?
							FbxCast<FbxFileTexture>(fbxProperty.GetSrcObject<FbxTexture>(0))->GetFileName():
							""
						):
						FbxCast<FbxFileTexture>(fbxProperty.GetSrcObject<FbxLayeredTexture>(0))->GetFileName();
				if (normalTextureFileName.length() > 0) {
					material->setNormalTexture(
						FileSystem::getInstance()->getPathName(normalTextureFileName),
						FileSystem::getInstance()->getFileName(normalTextureFileName)
					);
				}
				fbxProperty = fbxMaterial->FindProperty(FbxSurfaceMaterial::sSpecular);
				string specularTextureFileName =
					fbxProperty.GetSrcObjectCount<FbxLayeredTexture>() == 0?
						(fbxProperty.GetSrcObjectCount<FbxTexture>() > 0?
							FbxCast<FbxFileTexture>(fbxProperty.GetSrcObject<FbxTexture>(0))->GetFileName():
							""
						):
						FbxCast<FbxFileTexture>(fbxProperty.GetSrcObject<FbxLayeredTexture>(0))->GetFileName();
				if (specularTextureFileName.length() > 0) {
					material->setSpecularTexture(
						FileSystem::getInstance()->getPathName(specularTextureFileName),
						FileSystem::getInstance()->getFileName(specularTextureFileName)
					);
				}
				(*model->getMaterials())[material->getId()] = material;
			}
		}
		auto foundFacesEntity = false;
		string facesEntityName = "facesentity-" + material->getId();
		for (auto& facesEntityLookUp: facesEntities) {
			if (facesEntityLookUp.getId() == facesEntityName) {
				if (&facesEntityLookUp != facesEntity) {
					if (facesEntity != nullptr) {
						facesEntity->setFaces(&faces);
					}
					faces = *facesEntityLookUp.getFaces();
					facesEntity = &facesEntityLookUp;
				}
				foundFacesEntity = true;
				break;
			}
		}
		if (foundFacesEntity == false) {
			if (facesEntity != nullptr) {
				facesEntity->setFaces(&faces);
				faces.clear();
			}
			facesEntities.push_back(FacesEntity(group, facesEntityName));
			facesEntity = &facesEntities[facesEntities.size() - 1];
			facesEntity->setMaterial(material);
		}
		auto fbxPolygonSize = fbxMesh->GetPolygonSize(i);
		auto verticesOffset = vertices.size();
		auto normalsOffset = normals.size();
		auto textureCoordinatesOffset = textureCoordinates.size();
		auto tangentsOffset = tangents.size();
		auto bitangentsOffset = bitangents.size();
		auto haveUV = true;
		auto haveNormal = true;
		auto haveTangent = true;
		auto haveBitangent = true;
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
		if (haveTangent == true && haveBitangent == true) {
			f.setTangentIndices(
				tangentsOffset + 0,
				tangentsOffset + 1,
				tangentsOffset + 2
			);
			f.setBitangentIndices(
				bitangentsOffset + 0,
				bitangentsOffset + 1,
				bitangentsOffset + 2
			);
		}
		faces.push_back(f);
	}
	if (facesEntity != nullptr) {
		facesEntity->setFaces(&faces);
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
