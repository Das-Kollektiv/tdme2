#include <tdme/engine/fileio/models/DAEReader.h>

#include <map>
#include <map>
#include <string>
#include <unordered_set>
#include <vector>

#include <java/lang/fwd-tdme.h>
#include <tdme/math/Math.h>
#include <tdme/engine/ModelUtilities.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Rotations.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/fileio/models/DAEReader_determineDisplacementFilename_1.h>
#include <tdme/engine/fileio/models/DAEReader_AuthoringTool.h>
#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/engine/fileio/models/TMWriter.h>
#include <tdme/engine/model/Animation.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Color4Base.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Joint.h>
#include <tdme/engine/model/JointWeight.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model_UpVector.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/ModelHelper.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/model/Skinning.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemException.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/tools/shared/files/LevelFileExport.h>
#include <tdme/tools/shared/model/LevelEditorEntity_EntityType.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityLibrary.h>
#include <tdme/tools/shared/model/LevelEditorLevel.h>
#include <tdme/tools/shared/model/LevelEditorObject.h>
#include <tdme/tools/shared/model/LevelPropertyPresets.h>
#include <tdme/utils/Float.h>
#include <tdme/utils/Integer.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/StringTokenizer.h>
#include <tdme/utils/StringUtils.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_Exception.h>
#include <Array.h>
#include <SubArray.h>
#include <ObjectArray.h>

#include <ext/tinyxml/tinyxml.h>
#include "../../subsystems/object/ModelStatistics.h"

#define AVOID_NULLPTR_STRING(arg) (arg == nullptr?"":arg)

using std::array;
using std::vector;
using std::map;
using std::unordered_set;
using std::to_wstring;
using std::wstring;

using tdme::engine::fileio::models::DAEReader;
using tdme::math::Math;
using tdme::engine::ModelUtilities;
using tdme::engine::Rotation;
using tdme::engine::Rotations;
using tdme::engine::Transformations;
using tdme::engine::fileio::models::DAEReader_determineDisplacementFilename_1;
using tdme::engine::fileio::models::DAEReader_AuthoringTool;
using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::fileio::models::TMWriter;
using tdme::engine::model::Animation;
using tdme::engine::model::Color4;
using tdme::engine::model::Color4Base;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::model::Joint;
using tdme::engine::model::JointWeight;
using tdme::engine::model::Material;
using tdme::engine::model::Model_UpVector;
using tdme::engine::model::Model;
using tdme::engine::model::ModelHelper;
using tdme::engine::model::RotationOrder;
using tdme::engine::model::Skinning;
using tdme::engine::model::TextureCoordinate;
using tdme::engine::subsystems::object::ModelStatistics;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemException;
using tdme::os::_FileSystemInterface;
using tdme::tools::shared::files::LevelFileExport;
using tdme::tools::shared::model::LevelEditorEntity_EntityType;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityLibrary;
using tdme::tools::shared::model::LevelEditorLevel;
using tdme::tools::shared::model::LevelEditorObject;
using tdme::tools::shared::model::LevelPropertyPresets;
using tdme::utils::Float;
using tdme::utils::Integer;
using tdme::utils::StringConverter;
using tdme::utils::StringTokenizer;
using tdme::utils::StringUtils;
using tdme::utils::_Console;
using tdme::utils::_Exception;

using tdme::ext::tinyxml::TiXmlDocument;
using tdme::ext::tinyxml::TiXmlElement;
using tdme::ext::tinyxml::TiXmlAttribute;

Color4* DAEReader::BLENDER_AMBIENT_NONE = new Color4(0.0f, 0.0f, 0.0f, 1.0f);

float DAEReader::BLENDER_AMBIENT_FROM_DIFFUSE_SCALE = 0.7f;

float DAEReader::BLENDER_DIFFUSE_SCALE = 0.8f;

Model* DAEReader::read(const wstring& pathName, const wstring& fileName) throw (ModelFileIOException, _FileSystemException)
{
	auto xmlContent = _FileSystem::getInstance()->getContentAsString(pathName, fileName);
	TiXmlDocument xmlDocument;
	xmlDocument.Parse(StringConverter::toString(xmlContent).c_str());
	if (xmlDocument.Error() == true) {
		throw ModelFileIOException(
			string("Could not parse XML. Error='") + string(xmlDocument.ErrorDesc()) + string("'")
		);
	}
	TiXmlElement* xmlRoot = xmlDocument.RootElement();
	auto authoringTool = getAuthoringTool(xmlRoot);
	auto upVector = getUpVector(xmlRoot);
	RotationOrder* rotationOrder = nullptr;
	{
		auto v = upVector;
		if (v == Model_UpVector::Y_UP) {
			rotationOrder = RotationOrder::ZYX;
		} else
		if (v == Model_UpVector::Z_UP) {
			rotationOrder = RotationOrder::YZX;
		}
	}

	auto model = new Model(
		_FileSystem::getInstance()->getCanonicalPath(pathName, fileName),
		fileName,
		upVector,
		rotationOrder,
		nullptr
	);
	setupModelImportRotationMatrix(xmlRoot, model);
	setupModelImportScaleMatrix(xmlRoot, model);
	wstring xmlSceneId;
	auto xmlScene = getChildrenByTagName(xmlRoot, "scene").at(0);
	for (auto xmlInstanceVisualscene: getChildrenByTagName(xmlScene, "instance_visual_scene")) {
		xmlSceneId = StringUtils::substring(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlInstanceVisualscene->Attribute("url"))), 1);
	}
	auto xmlLibraryVisualScenes = getChildrenByTagName(xmlRoot, "library_visual_scenes").at(0);
	for (auto xmlLibraryVisualScene: getChildrenByTagName(xmlLibraryVisualScenes, "visual_scene")) {
		auto xmlVisualSceneId = StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlLibraryVisualScene->Attribute("id")));
		if (xmlVisualSceneId == xmlSceneId) {
			auto fps = 30.0f;
			auto xmlExtraNodes = getChildrenByTagName(xmlLibraryVisualScene, "extra");
			if (xmlExtraNodes.empty() == false) {
				auto xmlExtraNode = xmlExtraNodes.at(0);
				for (auto xmlTechnique: getChildrenByTagName(xmlExtraNode, "technique")) {
					auto xmlFrameRateNodes = getChildrenByTagName(xmlTechnique, "frame_rate");
					if (xmlFrameRateNodes.empty() == false) {
						fps = Float::parseFloat(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlFrameRateNodes.at(0)->GetText())));
						break;
					}
				}
			}
			model->setFPS(fps);
			for (auto xmlNode: getChildrenByTagName(xmlLibraryVisualScene, "node")) {
				auto group = readVisualSceneNode(authoringTool, pathName, model, nullptr, xmlRoot, xmlNode, fps);
				if (group != nullptr) {
					(*model->getSubGroups())[group->getId()] = group;
					(*model->getGroups())[group->getId()] = group;
				}
			}
		}
	}
	ModelHelper::setupJoints(model);
	ModelHelper::fixAnimationLength(model);
	ModelHelper::prepareForIndexedRendering(model);
	return model;
}

LevelEditorLevel* DAEReader::readLevel(const wstring& pathName, const wstring& fileName) throw (ModelFileIOException, _FileSystemException)
{
	wstring modelPathName = pathName + L"/" + fileName + L"-models";
	if (_FileSystem::getInstance()->fileExists(modelPathName)) {
		_FileSystem::getInstance()->removePath(modelPathName);
	}
	_FileSystem::getInstance()->createPath(modelPathName);

	auto levelEditorLevel = new LevelEditorLevel();
	auto xmlContent = _FileSystem::getInstance()->getContentAsString(pathName, fileName);
	TiXmlDocument xmlDocument;
	xmlDocument.Parse(StringConverter::toString(xmlContent).c_str());
	if (xmlDocument.Error() == true) {
		throw ModelFileIOException(
			string("Could not parse XML. Error='") + string(xmlDocument.ErrorDesc()) + string("'")
		);
	}
	TiXmlElement* xmlRoot = xmlDocument.RootElement();

	auto authoringTool = getAuthoringTool(xmlRoot);
	auto upVector = getUpVector(xmlRoot);
	RotationOrder* rotationOrder = nullptr;
	{
		auto v = upVector;
		if (v == Model_UpVector::Y_UP) {
			rotationOrder = RotationOrder::ZYX;
		} else
		if (v == Model_UpVector::Z_UP) {
			rotationOrder = RotationOrder::YZX;
		}
	}

	levelEditorLevel->setRotationOrder(rotationOrder);

	wstring xmlSceneId;
	auto xmlScene = getChildrenByTagName(xmlRoot, "scene").at(0);
	for (auto xmlInstanceVisualscene: getChildrenByTagName(xmlScene, "instance_visual_scene")) {
		xmlSceneId = StringUtils::substring(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlInstanceVisualscene->Attribute("url"))), 1);
	}
	auto xmlLibraryVisualScenes = getChildrenByTagName(xmlRoot, "library_visual_scenes").at(0);
	for (auto xmlLibraryVisualScene: getChildrenByTagName(xmlLibraryVisualScenes, "visual_scene")) {
		auto xmlVisualSceneId = StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlLibraryVisualScene->Attribute("id")));
		if (xmlVisualSceneId == xmlSceneId) {
			auto fps = 30.0f;
			auto xmlExtraNodes = getChildrenByTagName(xmlLibraryVisualScene,"extra");
			if (xmlExtraNodes.empty() == false) {
				auto xmlExtraNode = xmlExtraNodes.at(0);
				for (auto xmlTechnique: getChildrenByTagName(xmlExtraNode, "technique")) {
					auto xmlFrameRateNodes = getChildrenByTagName(xmlTechnique, "frame_rate");
					if (xmlFrameRateNodes.empty() == false) {
						fps = Float::parseFloat(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlFrameRateNodes.at(0)->GetText())));
						break;
					}
				}
			}
			auto entityLibrary = levelEditorLevel->getEntityLibrary();
			LevelEditorEntity* emptyEntity = nullptr;
			auto nodeIdx = 0;
			for (auto xmlNode: getChildrenByTagName(xmlLibraryVisualScene, "node")) {
				auto nodeId = StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlNode->Attribute("id")));
				auto modelName = nodeId;
				modelName = StringUtils::replaceAll(modelName, L"[-_]{1}[0-9]+$", L"");
				modelName = StringUtils::replaceAll(modelName, L"[0-9]+$", L"");
				auto haveName = entityLibrary->getEntityCount() == 0;
				if (haveName == false) {
					for (auto i = 0; i < 10000; i++) {
						haveName = true;
						auto modelNameTry = modelName;
						if (i > 0) modelNameTry+= to_wstring(i);
						for (auto entityIdx = 0; entityIdx < entityLibrary->getEntityCount(); entityIdx++) {
							auto entity = entityLibrary->getEntityAt(entityIdx);
							if (entity->getName() == modelNameTry) {
								haveName = false;
								break;
							}
						}
						if (haveName == true) {
							modelName = modelNameTry;
							break;
						}
					}
				}
				if (haveName == false) {
					_Console::println(
						wstring(
							L"DAEReader::readLevel(): Skipping model '" +
							modelName +
							L"' as no name could be created for it."
						)
					 );
					continue;
				}
				// FIXME: use canonical path
				auto model = new Model(
					modelPathName,
					fileName + L"-" + modelName,
					upVector,
					rotationOrder,
					nullptr
				);
				setupModelImportRotationMatrix(xmlRoot, model);
				Matrix4x4 modelImportRotationMatrix;
				modelImportRotationMatrix.set(model->getImportTransformationsMatrix());
				setupModelImportScaleMatrix(xmlRoot, model);
				Vector3 translation;
				Vector3 scale;
				Vector3 rotation;
				Vector3 xAxis;
				Vector3 yAxis;
				Vector3 zAxis;
				Vector3 tmpAxis;
				Matrix4x4 nodeTransformationsMatrix;
				auto xmlMatrixElements = getChildrenByTagName(xmlNode, "matrix");
				if (xmlMatrixElements.empty() == false) {
					auto xmlMatrix = StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlMatrixElements.at(0)->GetText()));
					StringTokenizer t;
					t.tokenize(xmlMatrix, L" \n\r");
					array<float, 16> nodeTransformationsMatrixArray;
					for (auto i = 0; i < nodeTransformationsMatrixArray.size(); i++) {
						nodeTransformationsMatrixArray[i] = Float::parseFloat(t.nextToken());
					}
					nodeTransformationsMatrix.set(nodeTransformationsMatrixArray).transpose();
				} else {
					throw ModelFileIOException(
						"missing node transformations matrix for node '" +
						StringConverter::toString(nodeId) +
						"'"
					);
				}
				nodeTransformationsMatrix.getAxes(xAxis, yAxis, zAxis);
				nodeTransformationsMatrix.getTranslation(translation);
				nodeTransformationsMatrix.getScale(scale);
				xAxis.normalize();
				yAxis.normalize();
				zAxis.normalize();
				nodeTransformationsMatrix.setAxes(xAxis, yAxis, zAxis);
				if ((upVector == Model_UpVector::Y_UP && Vector3::computeDotProduct(Vector3::computeCrossProduct(&xAxis, &yAxis, &tmpAxis), &zAxis) < 0.0f) ||
					(upVector == Model_UpVector::Z_UP && Vector3::computeDotProduct(Vector3::computeCrossProduct(&xAxis, &zAxis, &tmpAxis), &yAxis) < 0.0f)) {
					xAxis.scale(-1.0f);
					yAxis.scale(-1.0f);
					zAxis.scale(-1.0f);
					nodeTransformationsMatrix.setAxes(xAxis, yAxis, zAxis);
					scale.scale(-1.0f);
				}
				nodeTransformationsMatrix.computeEulerAngles(rotation);
				modelImportRotationMatrix.multiply(scale, scale);
				modelImportRotationMatrix.multiply(rotation, rotation);
				model->getImportTransformationsMatrix().multiply(translation, translation);
				model->setFPS(fps);
				auto group = readVisualSceneNode(authoringTool, pathName, model, nullptr, xmlRoot, xmlNode, fps);
				if (group != nullptr) {
					group->getTransformationsMatrix().identity();
					(*model->getSubGroups())[group->getId()] = group;
					(*model->getGroups())[group->getId()] = group;
				}
				ModelHelper::setupJoints(model);
				ModelHelper::fixAnimationLength(model);
				ModelHelper::prepareForIndexedRendering(model);
				auto entityType = LevelEditorEntity_EntityType::MODEL;
				ModelStatistics modelStatistics;
				ModelUtilities::computeModelStatistics(model, &modelStatistics);
				if (modelStatistics.opaqueFaceCount == 0 && modelStatistics.transparentFaceCount == 0) {
					entityType = LevelEditorEntity_EntityType::EMPTY;
				}
				LevelEditorEntity* levelEditorEntity = nullptr;
				if (entityType == LevelEditorEntity_EntityType::MODEL) {
					for (auto i = 0; i < levelEditorLevel->getEntityLibrary()->getEntityCount(); i++) {
						auto levelEditorEntityCompare = levelEditorLevel->getEntityLibrary()->getEntityAt(i);
						if (levelEditorEntityCompare->getType() != LevelEditorEntity_EntityType::MODEL)
							continue;

						if (ModelUtilities::equals(model, levelEditorEntityCompare->getModel()) == true) {
							levelEditorEntity = levelEditorEntityCompare;
							break;
						}
					}
					if (levelEditorEntity == nullptr) {
						auto modelFileName = modelName + L".tm";
						TMWriter::write(
							model,
							modelPathName,
							modelFileName
						  );
						levelEditorEntity = entityLibrary->addModel(
							nodeIdx++,
							modelName,
							modelName,
							modelPathName,
							modelFileName,
							new Vector3()
						);
					}
				} else
				if (entityType == LevelEditorEntity_EntityType::EMPTY) {
					if (emptyEntity == nullptr) {
						emptyEntity = entityLibrary->addEmpty(nodeIdx++, L"Default Empty", L"");
					}
					levelEditorEntity = emptyEntity;
				} else {
					_Console::println(wstring(L"DAEReader::readLevel(): unknown entity type. Skipping"));
					continue;
				}
				auto levelEditorObjectTransformations = new Transformations();
				levelEditorObjectTransformations->getTranslation()->set(&translation);
				levelEditorObjectTransformations->getRotations()->add(new Rotation((*rotation.getArray())[rotationOrder->getAxis0VectorIndex()], rotationOrder->getAxis0()));
				levelEditorObjectTransformations->getRotations()->add(new Rotation((*rotation.getArray())[rotationOrder->getAxis1VectorIndex()], rotationOrder->getAxis1()));
				levelEditorObjectTransformations->getRotations()->add(new Rotation((*rotation.getArray())[rotationOrder->getAxis2VectorIndex()], rotationOrder->getAxis2()));
				levelEditorObjectTransformations->getScale()->set(&scale);
				levelEditorObjectTransformations->update();
				auto object = new LevelEditorObject(
					nodeId,
					nodeId,
					levelEditorObjectTransformations,
					levelEditorEntity
				);
				levelEditorLevel->addObject(object);
			}
		}
	}
	LevelFileExport::export_(
		pathName,
		fileName + L".tl",
		levelEditorLevel
	);
	return levelEditorLevel;
}

DAEReader_AuthoringTool* DAEReader::getAuthoringTool(TiXmlElement* xmlRoot)
{
	for (auto xmlAsset: getChildrenByTagName(xmlRoot, "asset")) {
		for (auto xmlContributer: getChildrenByTagName(xmlAsset, "contributor")) {
			for (auto xmlAuthoringTool: getChildrenByTagName(xmlContributer, "authoring_tool")) {
				if (StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlAuthoringTool->GetText())).find(L"Blender") != -1) {
					return DAEReader_AuthoringTool::BLENDER;
				}
			}
		}
	}
	return DAEReader_AuthoringTool::UNKNOWN;
}

Model_UpVector* DAEReader::getUpVector(TiXmlElement* xmlRoot) throw (ModelFileIOException)
{
	for (auto xmlAsset: getChildrenByTagName(xmlRoot, "asset")) {
		for (auto xmlAssetUpAxis: getChildrenByTagName(xmlAsset, "up_axis")) {
			auto upAxis = StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlAssetUpAxis->GetText()));
			if (StringUtils::equalsIgnoreCase(upAxis, L"Y_UP") == true) {
				return Model_UpVector::Y_UP;
			} else
			if (StringUtils::equalsIgnoreCase(upAxis, L"Z_UP") == true) {
				return Model_UpVector::Z_UP;
			} else
			if (StringUtils::equalsIgnoreCase(upAxis, L"X_UP") == true) {
				throw ModelFileIOException("X-Up is not supported");
			} else {
				throw ModelFileIOException("Unknown Up vector");
			}
		}
	}
	throw ModelFileIOException("Unknown Up vector");
}

void DAEReader::setupModelImportRotationMatrix(TiXmlElement* xmlRoot, Model* model)
{
	for (auto xmlAsset: getChildrenByTagName(xmlRoot, "asset")) {
		for (auto xmlAssetUpAxis: getChildrenByTagName(xmlAsset, "up_axis")) {
			auto upAxis = StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlAssetUpAxis->GetText()));
			if (StringUtils::equalsIgnoreCase(upAxis, L"Y_UP") == true) {
			} else
			if (StringUtils::equalsIgnoreCase(upAxis, L"Z_UP") == true) {
				model->getImportTransformationsMatrix().rotate(-90.0f, Vector3(1.0f, 0.0f, 0.0f));
			} else
			if (StringUtils::equalsIgnoreCase(upAxis, L"X_UP") == true) {
				model->getImportTransformationsMatrix().rotate(-90.0f, Vector3(0.0f, 1.0f, 0.0f));
			} else {
				_Console::println(wstring(L"Warning: Unknown up axis: " + upAxis));
			}
		}
	}
}

void DAEReader::setupModelImportScaleMatrix(TiXmlElement* xmlRoot, Model* model)
{
	for (auto xmlAsset: getChildrenByTagName(xmlRoot, "asset")) {
		for (auto xmlAssetUnit: getChildrenByTagName(xmlAsset, "unit")) {
			wstring tmp;
			if ((tmp = StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlAssetUnit->Attribute("meter")))).length() > 0) {
				model->getImportTransformationsMatrix().scale(Float::parseFloat(tmp));
			}
		}
	}
}

Group* DAEReader::readVisualSceneNode(DAEReader_AuthoringTool* authoringTool, const wstring& pathName, Model* model, Group* parentGroup, TiXmlElement* xmlRoot, TiXmlElement* xmlNode, float fps)
{
	auto xmlInstanceControllers = getChildrenByTagName(xmlNode, "instance_controller");
	if (xmlInstanceControllers.empty() == false) {
		return readVisualSceneInstanceController(authoringTool, pathName, model, parentGroup, xmlRoot, xmlNode);
	} else {
		return readNode(authoringTool, pathName, model, parentGroup, xmlRoot, xmlNode, fps);
	}
}

Group* DAEReader::readNode(DAEReader_AuthoringTool* authoringTool, const wstring& pathName, Model* model, Group* parentGroup, TiXmlElement* xmlRoot, TiXmlElement* xmlNode, float fps) throw (ModelFileIOException)
{
	auto xmlNodeId = StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlNode->Attribute("id")));
	auto xmlNodeName = StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlNode->Attribute("name")));
	if (xmlNodeId.length() == 0) xmlNodeId = xmlNodeName;

	auto group = new Group(model, parentGroup, xmlNodeId, xmlNodeName);

	auto xmlMatrixElements = getChildrenByTagName(xmlNode, "matrix");
	if (xmlMatrixElements.empty() == false) {
		StringTokenizer t;
		Matrix4x4 transformationsMatrix;
		auto xmlMatrix = StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlMatrixElements.at(0)->GetText()));
		t.tokenize(xmlMatrix, L" \n\r");
		array<float, 16> transformationsMatrixArray;
		for (auto i = 0; i < transformationsMatrixArray.size(); i++) {
			transformationsMatrixArray[i] = Float::parseFloat(t.nextToken());
		}
		transformationsMatrix.set(transformationsMatrixArray).transpose();
		group->getTransformationsMatrix().multiply(transformationsMatrix);
	}

	auto xmlAnimationsLibrary = getChildrenByTagName(xmlRoot, "library_animations");
	if (xmlAnimationsLibrary.empty() == false) {
		for (auto xmlAnimation: getChildrenByTagName(xmlAnimationsLibrary.at(0), "animation")) {
			auto _xmlAnimation = getChildrenByTagName(xmlAnimation, "animation");
			if (_xmlAnimation.empty() == false) {
				xmlAnimation = _xmlAnimation.at(0);
			}
			wstring xmlSamplerSource;
			auto xmlChannel = getChildrenByTagName(xmlAnimation, "channel").at(0);
			if (StringUtils::startsWith(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlChannel->Attribute("target"))), xmlNodeId + L"/") == true) {
				xmlSamplerSource = StringUtils::substring(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlChannel->Attribute("source"))), 1);
			}
			if (xmlSamplerSource.length() == 0) {
				continue;
			}
			wstring xmlSamplerOutputSource;
			wstring xmlSamplerInputSource;
			auto xmlSampler = getChildrenByTagName(xmlAnimation, "sampler").at(0);
			for (auto xmlSamplerInput: getChildrenByTagName(xmlSampler, "input")) {
				if (StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlSamplerInput->Attribute("semantic"))) == L"OUTPUT") {
					xmlSamplerOutputSource = StringUtils::substring(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlSamplerInput->Attribute("source"))), 1);
				} else
				if (StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlSamplerInput->Attribute("semantic"))) == L"INPUT") {
					xmlSamplerInputSource = StringUtils::substring(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlSamplerInput->Attribute("source"))), 1);
				}
			}
			if (xmlSamplerOutputSource.length() == 0) {
				throw ModelFileIOException(
					"Could not find xml sampler output source for animation for '" +
					StringConverter::toString(xmlNodeId) +
					"'"
				);
			}
			vector<float> keyFrameTimes;
			for (auto xmlAnimationSource: getChildrenByTagName(xmlAnimation, "source")) {
				if (StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlAnimationSource->Attribute("id"))) == xmlSamplerInputSource) {
					auto xmlFloatArray = getChildrenByTagName(xmlAnimationSource, "float_array").at(0);
					auto frames = Integer::parseInt(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlFloatArray->Attribute("count"))));
					auto valueString = StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlFloatArray->GetText()));
					auto keyFrameIdx = 0;
					keyFrameTimes.resize(frames);
					StringTokenizer t;
					t.tokenize(valueString, L" \n\r");
					while (t.hasMoreTokens()) {
						keyFrameTimes[keyFrameIdx++] = Float::parseFloat(t.nextToken());
					}
				}
			}
			if (keyFrameTimes.size() > 0) {
				for (auto xmlAnimationSource: getChildrenByTagName(xmlAnimation, "source")) {
					if (StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlAnimationSource->Attribute("id"))) == xmlSamplerOutputSource) {
						auto xmlFloatArray = getChildrenByTagName(xmlAnimationSource, "float_array").at(0);
						auto keyFrames = Integer::parseInt(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlFloatArray->Attribute("count")))) / 16;
						if (keyFrames > 0) {
							auto valueString = StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlFloatArray->GetText()));
							StringTokenizer t;
							t.tokenize(valueString, L" \n\r");
							int32_t keyFrameIdx = 0;
							vector<Matrix4x4> keyFrameMatrices;
							keyFrameMatrices.resize(keyFrames);
							while (t.hasMoreTokens()) {
								array<float, 16> keyFrameMatricesArray;
								for (auto i = 0; i < keyFrameMatricesArray.size() ;i++) {
									keyFrameMatricesArray[i] = Float::parseFloat(t.nextToken());
								}
								keyFrameMatrices[keyFrameIdx].set(keyFrameMatricesArray);
								keyFrameMatrices[keyFrameIdx].transpose();
								keyFrameIdx++;
							}

							auto frames = static_cast< int32_t >(Math::ceil(keyFrameTimes[keyFrameTimes.size() - 1] * fps));
							if (frames > 0) {
								ModelHelper::createDefaultAnimation(model, frames);
								auto animation = group->createAnimation(frames);
								auto transformationsMatrices = animation->getTransformationsMatrices();
								auto tansformationsMatrixLast = &keyFrameMatrices[0];
								keyFrameIdx = 0;
								auto frameIdx = 0;
								auto timeStampLast = 0.0f;
								for (auto keyFrameTime : keyFrameTimes) {
									auto transformationsMatrixCurrent = &keyFrameMatrices[(keyFrameIdx) % keyFrameMatrices.size()];
									float timeStamp;
									for (timeStamp = timeStampLast; timeStamp < keyFrameTime; timeStamp += 1.0f / fps) {
										if (frameIdx >= frames) {
											_Console::println(wstring(L"Warning: skipping frame: ") + to_wstring(frameIdx));
											frameIdx++;
											continue;
										}
										Matrix4x4::interpolateLinear(*tansformationsMatrixLast, *transformationsMatrixCurrent, (timeStamp - timeStampLast) / (keyFrameTime - timeStampLast), (*transformationsMatrices)[frameIdx]);
										frameIdx++;
									}
									timeStampLast = timeStamp;
									tansformationsMatrixLast = transformationsMatrixCurrent;
									keyFrameIdx++;
								}
							}
						}
					}
				}
			}
		}
	}

	for (auto _xmlNode: getChildrenByTagName(xmlNode, "node")) {
		auto _group = readVisualSceneNode(authoringTool, pathName, model, group, xmlRoot, _xmlNode, fps);
		if (_group != nullptr) {
			(*group->getSubGroups())[_group->getId()] = _group;
			(*model->getGroups())[_group->getId()] = _group;
		}
	}

	wstring xmlInstanceGeometryId;
	auto xmlInstanceGeometryElements = getChildrenByTagName(xmlNode, "instance_geometry");
	if (xmlInstanceGeometryElements.empty() == false) {
		auto xmlInstanceGeometryElement = xmlInstanceGeometryElements.at(0);
		xmlInstanceGeometryId = StringUtils::substring(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlInstanceGeometryElement->Attribute("url"))), 1);
		map<wstring, wstring> materialSymbols;
		for (auto xmlBindMaterial: getChildrenByTagName(xmlInstanceGeometryElement, "bind_material"))
		for (auto xmlTechniqueCommon: getChildrenByTagName(xmlBindMaterial, "technique_common"))
		for (auto xmlInstanceMaterial: getChildrenByTagName(xmlTechniqueCommon, "instance_material")) {
			materialSymbols[StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlInstanceMaterial->Attribute("symbol")))] =
				StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlInstanceMaterial->Attribute("target")));
		}
		readGeometry(authoringTool, pathName, model, group, xmlRoot, xmlInstanceGeometryId, &materialSymbols);
		return group;
	}

	wstring xmlInstanceNodeId;
	for (auto xmlInstanceNodeElement: getChildrenByTagName(xmlNode, "instance_node")) {
		xmlInstanceNodeId = StringUtils::substring(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlInstanceNodeElement->Attribute("url"))), 1);
	}
	if (xmlInstanceNodeId.length() > 0) {
		for (auto xmlLibraryNodes: getChildrenByTagName(xmlRoot, "library_nodes"))
		for (auto xmlLibraryNode: getChildrenByTagName(xmlLibraryNodes, "node"))
		if (StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlLibraryNode->Attribute("id"))) == xmlInstanceNodeId) {
			for (auto _xmlNode: getChildrenByTagName(xmlLibraryNode, "node")) {
				auto _group = readVisualSceneNode(authoringTool, pathName, model, parentGroup, xmlRoot, _xmlNode, fps);
				if (_group != nullptr) {
					(*group->getSubGroups())[_group->getId()] = _group;
					(*model->getGroups())[_group->getId()] = _group;
				}
			}
			for (auto xmlInstanceGeometry: getChildrenByTagName(xmlLibraryNode, "instance_geometry")) {
				auto xmlGeometryId = StringUtils::substring(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlInstanceGeometry->Attribute("url"))), 1);
				map<wstring, wstring> materialSymbols;
				for (auto xmlBindMaterial: getChildrenByTagName(xmlInstanceGeometry, "bind_material"))
				for (auto xmlTechniqueCommon: getChildrenByTagName(xmlBindMaterial, "technique_common"))
				for (auto xmlInstanceMaterial: getChildrenByTagName(xmlTechniqueCommon, "instance_material")) {
					materialSymbols[StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlInstanceMaterial->Attribute("symbol")))] =
						StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlInstanceMaterial->Attribute("target")));
				}
				readGeometry(authoringTool, pathName, model, group, xmlRoot, xmlGeometryId, &materialSymbols);
			}
		}
	}
	return group;
}

Group* DAEReader::readVisualSceneInstanceController(DAEReader_AuthoringTool* authoringTool, const wstring& pathName, Model* model, Group* parentGroup, TiXmlElement* xmlRoot, TiXmlElement* xmlNode) throw (ModelFileIOException)
{
	auto xmlNodeId = StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlNode->Attribute("id")));
	auto xmlNodeName = StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlNode->Attribute("name")));
	map<wstring, wstring> materialSymbols;
	wstring xmlGeometryId;
	auto xmlInstanceControllers = getChildrenByTagName(xmlNode, "instance_controller");
	TiXmlElement* xmlSkin = nullptr;
	auto xmlInstanceController = xmlInstanceControllers.at(0);

	for (auto xmlBindMaterial: getChildrenByTagName(xmlInstanceController, "bind_material"))
	for (auto xmlTechniqueCommon: getChildrenByTagName(xmlBindMaterial, "technique_common"))
	for (auto xmlInstanceMaterial: getChildrenByTagName(xmlTechniqueCommon, "instance_material")) {
		materialSymbols[StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlInstanceMaterial->Attribute("symbol")))] =
			StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlInstanceMaterial->Attribute("target")));
	}

	auto xmlInstanceControllerId = StringUtils::substring(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlInstanceController->Attribute("url"))), 1);
	auto xmlLibraryControllers = getChildrenByTagName(xmlRoot, "library_controllers").at(0);
	for (auto xmlLibraryController: getChildrenByTagName(xmlLibraryControllers, "controller")) {
		if (StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlLibraryController->Attribute("id"))) == xmlInstanceControllerId) {
			auto xmlSkins = getChildrenByTagName(xmlLibraryController, "skin");
			if (xmlSkins.empty() == false) {
				xmlSkin = xmlSkins.at(0);
			}
		}
	}
	if (xmlSkin == nullptr) {
		throw ModelFileIOException(
			"skin not found for instance controller '" +
			StringConverter::toString(xmlNodeId) +
			"'"
		);
	}

	xmlGeometryId = StringUtils::substring(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlSkin->Attribute("source"))), 1);
	auto xmlMatrix = StringConverter::toWideString(AVOID_NULLPTR_STRING(getChildrenByTagName(xmlSkin, "bind_shape_matrix").at(0)->GetText()));
	StringTokenizer t;;
	t.tokenize(xmlMatrix, L" \n\r");
	array<float, 16> bindShapeMatrixArray;
	for (auto i = 0; i < bindShapeMatrixArray.size(); i++) {
		bindShapeMatrixArray[i] = Float::parseFloat(t.nextToken());
	}
	Matrix4x4 bindShapeMatrix;
	bindShapeMatrix.set(bindShapeMatrixArray).transpose();

	auto group = new Group(model, parentGroup, xmlNodeId, xmlNodeName);
	auto skinning = group->createSkinning();
	readGeometry(authoringTool, pathName, model, group, xmlRoot, xmlGeometryId, &materialSymbols);

	wstring xmlJointsSource;
	wstring xmlJointsInverseBindMatricesSource;
	auto xmlJoints = getChildrenByTagName(xmlSkin, "joints").at(0);
	for (auto xmlJointsInput: getChildrenByTagName(xmlJoints, "input")) {
		if (StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlJointsInput->Attribute("semantic"))) == L"JOINT") {
			xmlJointsSource = StringUtils::substring(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlJointsInput->Attribute("source"))), 1);
		} else
		if (StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlJointsInput->Attribute("semantic"))) == L"INV_BIND_MATRIX") {
			xmlJointsInverseBindMatricesSource = StringUtils::substring(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlJointsInput->Attribute("source"))), 1);
		}
	}
	if (xmlJointsSource.length() == 0) {
		throw ModelFileIOException(
			"joint source not found for instance controller '" +
			StringConverter::toString(xmlNodeId) +
			"'"
		);
	}

	vector<Joint> joints;
	for (auto xmlSkinSource: getChildrenByTagName(xmlSkin, "source")) {
		if (StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlSkinSource->Attribute("id"))) == xmlJointsSource) {
			t.tokenize(StringConverter::toWideString(AVOID_NULLPTR_STRING(getChildrenByTagName(xmlSkinSource, "Name_array").at(0)->GetText())), L" \n\r");
			while (t.hasMoreTokens()) {
				joints.push_back(Joint(t.nextToken()));
			}
		}
	}
	skinning->setJoints(&joints);

	if (xmlJointsInverseBindMatricesSource.length() == 0) {
		throw ModelFileIOException(
			"inverse bind matrices source not found for instance controller '" +
			StringConverter::toString(xmlNodeId) +
			"'"
		);
	}

	for (auto xmlSkinSource: getChildrenByTagName(xmlSkin, "source")) {
		if (StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlSkinSource->Attribute("id"))) == xmlJointsInverseBindMatricesSource) {
			t.tokenize(StringConverter::toWideString(AVOID_NULLPTR_STRING(getChildrenByTagName(xmlSkinSource, "float_array").at(0)->GetText())), L" \n\r");
			auto _joints = skinning->getJoints();
			for (auto i = 0; i < _joints->size(); i++) {
				array<float, 16> bindMatrixArray;
				for (auto i = 0; i < bindMatrixArray.size(); i++) {
					bindMatrixArray[i] = Float::parseFloat(t.nextToken());
				}
				(*_joints)[i].getBindMatrix().multiply(bindShapeMatrix);
				(*_joints)[i].getBindMatrix().multiply((Matrix4x4(bindMatrixArray)).transpose());
			}
		}
	}

	vector<float> weights;
	auto xmlJointOffset = -1;
	auto xmlWeightOffset = -1;
	wstring xmlWeightsSource;
	auto xmlVertexWeights = getChildrenByTagName(xmlSkin, "vertex_weights").at(0);
	auto xmlVertexWeightInputs = getChildrenByTagName(xmlVertexWeights, "input");
	for (auto xmlVertexWeightInput: xmlVertexWeightInputs) {
		if (StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlVertexWeightInput->Attribute("semantic"))) == L"JOINT") {
			if ((StringUtils::substring(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlVertexWeightInput->Attribute("source"))), 1) == xmlJointsSource) == false) {
				throw ModelFileIOException("joint inverse bind matrices source do not match");
			}
			xmlJointOffset = Integer::parseInt(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlVertexWeightInput->Attribute("offset"))));
		} else
		if (StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlVertexWeightInput->Attribute("semantic"))) == L"WEIGHT") {
			xmlWeightOffset = Integer::parseInt(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlVertexWeightInput->Attribute("offset"))));
			xmlWeightsSource = StringUtils::substring(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlVertexWeightInput->Attribute("source"))), 1);
		}
	}
	if (xmlJointOffset == -1) {
		throw ModelFileIOException(
			"xml vertex weight joint offset missing for node '" +
			StringConverter::toString(xmlNodeId) +
			"'"
		);
	}
	if (xmlWeightOffset == -1) {
		throw ModelFileIOException(
			"xml vertex weight weight offset missing for node " +
			StringConverter::toString(xmlNodeId) +
			"'"
		);
	}
	if (xmlWeightsSource.length() == 0) {
		throw ModelFileIOException(
			"xml vertex weight weight source missing for node '" +
			StringConverter::toString(xmlNodeId) +
			"'"
		);
	}
	for (auto xmlSkinSource: getChildrenByTagName(xmlSkin, "source")) {
		if (StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlSkinSource->Attribute("id"))) == xmlWeightsSource) {
			t.tokenize(StringConverter::toWideString(AVOID_NULLPTR_STRING(getChildrenByTagName(xmlSkinSource, "float_array").at(0)->GetText())), L" \n\r");
			while (t.hasMoreTokens()) {
				weights.push_back(Float::parseFloat(t.nextToken()));
			}
		}
	}
	skinning->setWeights(weights);
	auto xmlVertexWeightInputCount = xmlVertexWeightInputs.size();
	auto vertexJointsInfluenceCountString = StringConverter::toWideString(AVOID_NULLPTR_STRING(getChildrenByTagName(xmlVertexWeights, "vcount").at(0)->GetText()));
	auto vertexJointsInfluencesString = StringConverter::toWideString(AVOID_NULLPTR_STRING(getChildrenByTagName(xmlVertexWeights, "v").at(0)->GetText()));
	t.tokenize(vertexJointsInfluenceCountString, L" \n\r");
	StringTokenizer t2;
	t2.tokenize(vertexJointsInfluencesString, L" \n\r");
	auto offset = 0;
	vector<vector<JointWeight>> verticesJointsWeights;
	while (t.hasMoreTokens()) {
		auto vertexJointsInfluencesCount = Integer::parseInt(t.nextToken());
		vector<JointWeight>vertexJointsWeights;
		for (auto i = 0; i < vertexJointsInfluencesCount; i++) {
			auto vertexJoint = -1;
			auto vertexWeight = -1;
			while (vertexJoint == -1 || vertexWeight == -1) {
				auto value = Integer::parseInt(t2.nextToken());
				if (offset % xmlVertexWeightInputCount == xmlJointOffset) {
					vertexJoint = value;
				} else if (offset % xmlVertexWeightInputCount == xmlWeightOffset) {
					vertexWeight = value;
				}
				offset++;
			}
			vertexJointsWeights.push_back(JointWeight(vertexJoint, vertexWeight));
		}
		verticesJointsWeights.push_back(vertexJointsWeights);
	}
	skinning->setVerticesJointsWeights(&verticesJointsWeights);

	return group;
}

void DAEReader::readGeometry(DAEReader_AuthoringTool* authoringTool, const wstring& pathName, Model* model, Group* group, TiXmlElement* xmlRoot, const wstring& xmlNodeId, const map<wstring, wstring>* materialSymbols) throw (ModelFileIOException)
{
	vector<FacesEntity> facesEntities = *group->getFacesEntities();
	auto verticesOffset = group->getVertices()->size();
	vector<Vector3> vertices = *group->getVertices();
	auto normalsOffset = group->getNormals()->size();
	vector<Vector3> normals = *group->getNormals();;
	auto textureCoordinatesOffset = group->getTextureCoordinates()->size();
	vector<TextureCoordinate> textureCoordinates = *group->getTextureCoordinates();
	auto xmlLibraryGeometries = getChildrenByTagName(xmlRoot, "library_geometries").at(0);
	for (auto xmlGeometry: getChildrenByTagName(xmlLibraryGeometries, "geometry")) {
		if (StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlGeometry->Attribute("id"))) == xmlNodeId) {
			auto xmlMesh = getChildrenByTagName(xmlGeometry, "mesh").at(0);
			vector<TiXmlElement*> xmlPolygonsList;
			for (auto xmlTriangesElement: getChildrenByTagName(xmlMesh, "triangles")) {
				xmlPolygonsList.push_back(xmlTriangesElement);
			}
			for (auto xmlPolyListElement: getChildrenByTagName(xmlMesh, "polylist")) {
				xmlPolygonsList.push_back(xmlPolyListElement);
			}
			for (auto xmlPolygonsElement: getChildrenByTagName(xmlMesh, "polygons")) {
				xmlPolygonsList.push_back(xmlPolygonsElement);
			}
			for (auto xmlPolygons: xmlPolygonsList) {
				vector<Face> faces;
				FacesEntity facesEntity(group, xmlNodeId);
				if (StringUtils::toLowerCase(StringConverter::toWideString(xmlPolygons->Value())) == L"polylist") {
					StringTokenizer t;
					t.tokenize(StringConverter::toWideString(AVOID_NULLPTR_STRING(getChildrenByTagName(xmlPolygons, "vcount").at(0)->GetText())), L" \t\n\r\f");
					while (t.hasMoreTokens()) {
						auto vertexCount = Integer::parseInt(t.nextToken());
						if (vertexCount != 3) {
							throw ModelFileIOException(
								 "we only support triangles in '" +
								 StringConverter::toString(xmlNodeId) +
								 "'"
							);
						}
					}
				}
				auto xmlInputs = -1;
				auto xmlVerticesOffset = -1;
				wstring xmlVerticesSource;
				auto xmlNormalsOffset = -1;
				wstring xmlNormalsSource;
				auto xmlTexCoordOffset = -1;
				wstring xmlTexCoordSource;
				auto xmlColorOffset = -1;
				wstring xmlColorSource;
				auto xmlMaterialId = StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlPolygons->Attribute("material")));
				auto materialSymbolIt = materialSymbols->find(xmlMaterialId);
				if (materialSymbolIt != materialSymbols->end()) {
					xmlMaterialId = materialSymbolIt->second;
					xmlMaterialId = StringUtils::substring(xmlMaterialId, 1);
				}

				if (xmlMaterialId.length() > 0) {
					Material* material = nullptr;
					auto materialIt = model->getMaterials()->find(xmlMaterialId);
					if (materialIt != model->getMaterials()->end()) {
						material = materialIt->second;
					} else {
						material = readMaterial(authoringTool, pathName, model, xmlRoot, xmlMaterialId);
					}
					facesEntity.setMaterial(material);
				}
				unordered_set<int32_t> xmlInputSet;
				for (auto xmlTrianglesInput: getChildrenByTagName(xmlPolygons, "input")) {
					if (StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlTrianglesInput->Attribute("semantic"))) == L"VERTEX") {
						xmlVerticesOffset = Integer::parseInt(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlTrianglesInput->Attribute("offset"))));
						xmlVerticesSource = StringUtils::substring(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlTrianglesInput->Attribute("source"))), 1);
						xmlInputSet.insert(xmlVerticesOffset);
					} else
					if (StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlTrianglesInput->Attribute("semantic"))) == L"NORMAL") {
						xmlNormalsOffset = Integer::parseInt(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlTrianglesInput->Attribute("offset"))));
						xmlNormalsSource = StringUtils::substring(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlTrianglesInput->Attribute("source"))), 1);
						xmlInputSet.insert(xmlNormalsOffset);
					} else
					if (StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlTrianglesInput->Attribute("semantic"))) == L"TEXCOORD") {
						xmlTexCoordOffset = Integer::parseInt(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlTrianglesInput->Attribute("offset"))));
						xmlTexCoordSource = StringUtils::substring(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlTrianglesInput->Attribute("source"))), 1);
						xmlInputSet.insert(xmlTexCoordOffset);
					} else
					if (StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlTrianglesInput->Attribute("semantic"))) == L"COLOR") {
						xmlColorOffset = Integer::parseInt(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlTrianglesInput->Attribute("offset"))));
						xmlColorSource = StringUtils::substring(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlTrianglesInput->Attribute("source"))), 1);
						xmlInputSet.insert(xmlColorOffset);
					}
				}
				xmlInputs = xmlInputSet.size();
				for (auto xmlVertices: getChildrenByTagName(xmlMesh, "vertices")) {
					if (StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlVertices->Attribute("id"))) == xmlVerticesSource) {
						for (auto xmlVerticesInput: getChildrenByTagName(xmlVertices, "input")) {
							if (StringUtils::equalsIgnoreCase(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlVerticesInput->Attribute("semantic"))), L"position") == true) {
								xmlVerticesSource = StringUtils::substring(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlVerticesInput->Attribute("source"))), 1);
							} else
							if (StringUtils::equalsIgnoreCase(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlVerticesInput->Attribute("semantic"))), L"normal") == true) {
								xmlNormalsSource = StringUtils::substring(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlVerticesInput->Attribute("source"))), 1);
							}
						}
					}
				}
				if (xmlVerticesSource.length() == 0) {
					throw ModelFileIOException(
						"Could not determine triangles vertices source for '" +
						StringConverter::toString(xmlNodeId) +
						"'"
					);
				}
				if (xmlNormalsSource.length() == 0) {
					throw ModelFileIOException(
						"Could not determine triangles normal source for '" +
						StringConverter::toString(xmlNodeId) +
						"'"
					);
				}
				for (auto xmlMeshSource: getChildrenByTagName(xmlMesh, "source")) {
					if (StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlMeshSource->Attribute("id"))) == xmlVerticesSource) {
						auto xmlFloatArray = getChildrenByTagName(xmlMeshSource, "float_array").at(0);
						auto valueString = StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlFloatArray->GetText()));
						StringTokenizer t;
						t.tokenize(valueString, L" \n\r");
						while (t.hasMoreTokens()) {
							float x = Float::parseFloat(t.nextToken());
							float y = Float::parseFloat(t.nextToken());
							float z = Float::parseFloat(t.nextToken());
							vertices.push_back(Vector3(x, y, z));
						}
					} else
					if (StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlMeshSource->Attribute("id"))) == xmlNormalsSource) {
						auto xmlFloatArray = getChildrenByTagName(xmlMeshSource, "float_array").at(0);
						auto valueString = StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlFloatArray->GetText()));
						StringTokenizer t;
						t.tokenize(valueString, L" \n\r");
						while (t.hasMoreTokens()) {
							float x = Float::parseFloat(t.nextToken());
							float y = Float::parseFloat(t.nextToken());
							float z = Float::parseFloat(t.nextToken());
							normals.push_back(Vector3(x, y, z));
						}
					}
					if (xmlTexCoordSource.length() > 0) {
						if (StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlMeshSource->Attribute("id"))) == xmlTexCoordSource) {
							auto xmlFloatArray = getChildrenByTagName(xmlMeshSource, "float_array").at(0);
							auto valueString = StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlFloatArray->GetText()));
							StringTokenizer t;
							t.tokenize(valueString, L" \n\r");
							while (t.hasMoreTokens()) {
								float u = Float::parseFloat(t.nextToken());
								float v = Float::parseFloat(t.nextToken());
								textureCoordinates.push_back(TextureCoordinate(u, v));
							}
						}
					}
				}
				for (auto xmlPolygon: getChildrenByTagName(xmlPolygons, "p")) {
					auto valueString = StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlPolygon->GetText()));
					StringTokenizer t;
					t.tokenize(valueString, L" \n\r");
					array<int32_t, 3> vi;
					auto viIdx = 0;
					array<int32_t, 3> ni;
					auto niIdx = 0;
					array<int32_t, 3> ti;
					auto tiIdx = 0;
					auto valueIdx = 0;
					auto valid = true;
					while (t.hasMoreTokens()) {
						auto value = Integer::parseInt(t.nextToken());
						if (valueIdx % xmlInputs == xmlVerticesOffset) {
							vi[viIdx++] = value;
							if (value < 0 || value >= vertices.size() - verticesOffset) {
								valid = false;
							}
							if (xmlNormalsSource.length() > 0 && xmlNormalsOffset == -1) {
								ni[niIdx++] = value;
								if (value < 0 || value >= normals.size() - normalsOffset) {
									valid = false;
								}
							}
						}
						if (xmlNormalsOffset != -1 && valueIdx % xmlInputs == xmlNormalsOffset) {
							ni[niIdx++] = value;
							if (value < 0 || value >= normals.size() - normalsOffset) {
								valid = false;
							}
						}
						if (xmlTexCoordOffset != -1 && valueIdx % xmlInputs == xmlTexCoordOffset) {
							ti[tiIdx++] = value;
							if (value < 0 || value >= textureCoordinates.size() - textureCoordinatesOffset) {
								valid = false;
							}
						}
						if (viIdx == 3 && niIdx == 3 && (xmlTexCoordSource.length() == 0 || tiIdx == 3)) {
							if (valid == true) {
								Face f(
									group,
									vi[0] + verticesOffset,
									vi[1] + verticesOffset,
									vi[2] + verticesOffset,
									ni[0] + normalsOffset,
									ni[1] + normalsOffset,
									ni[2] + normalsOffset
								);
								if (xmlTexCoordSource.length() != 0) {
									f.setTextureCoordinateIndices(
										ti[0] + textureCoordinatesOffset,
										ti[1] + textureCoordinatesOffset,
										ti[2] + textureCoordinatesOffset
									);
								}
								faces.push_back(f);
							}
							viIdx = 0;
							niIdx = 0;
							tiIdx = 0;
							valid = true;
						}
						valueIdx++;
					}
				}
				if (faces.empty() == false) {
					facesEntity.setFaces(&faces);
					facesEntities.push_back(facesEntity);
				}
			}
		}
	}

	group->setVertices(&vertices);
	group->setNormals(&normals);
	if (textureCoordinates.size() > 0)
		group->setTextureCoordinates(&textureCoordinates);

	group->setFacesEntities(&facesEntities);
	ModelHelper::createNormalTangentsAndBitangents(group);
	group->determineFeatures();
}

Material* DAEReader::readMaterial(DAEReader_AuthoringTool* authoringTool, const wstring& pathName, Model* model, TiXmlElement* xmlRoot, const wstring& xmlNodeId)
{
	wstring xmlEffectId;
	auto xmlLibraryMaterials = getChildrenByTagName(xmlRoot, "library_materials").at(0);
	for (auto xmlMaterial: getChildrenByTagName(xmlLibraryMaterials, "material")) {
		if (StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlMaterial->Attribute("id"))) == xmlNodeId) {
			auto xmlInstanceEffect = getChildrenByTagName(xmlMaterial, "instance_effect").at(0);
			xmlEffectId = StringUtils::substring(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlInstanceEffect->Attribute("url"))), 1);
		}
	}
	if (xmlEffectId.length() == 0) {
		_Console::println(
			wstring(
				 L"Could not determine effect id for '" +
				 xmlNodeId +
				 L"'"
			 )
		 );
		return nullptr;
	}
	auto material = new Material(xmlNodeId);
	wstring xmlDiffuseTextureId;
	wstring xmlSpecularTextureId;
	wstring xmlBumpTextureId;
	auto xmlLibraryEffects = getChildrenByTagName(xmlRoot, "library_effects").at(0);
	for (auto xmlEffect: getChildrenByTagName(xmlLibraryEffects, "effect")) {
		if (StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlEffect->Attribute("id"))) == xmlEffectId) {
			auto xmlProfile = getChildrenByTagName(xmlEffect, "profile_COMMON").at(0);
			map<wstring, wstring> samplerSurfaceMapping;
			map<wstring, wstring> surfaceImageMapping;
			for (auto xmlNewParam: getChildrenByTagName(xmlProfile, "newparam")) {
				auto xmlNewParamSID = StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlNewParam->Attribute("sid")));
				for (auto xmlSurface: getChildrenByTagName(xmlNewParam, "surface"))
				for (auto xmlSurfaceInitFrom: getChildrenByTagName(xmlSurface, "init_from")) {
					surfaceImageMapping[xmlNewParamSID] =
						StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlSurfaceInitFrom->GetText()));
				}
				for (auto xmlSampler2D: getChildrenByTagName(xmlNewParam, "sampler2D"))
				for (auto xmlSampler2DSource: getChildrenByTagName(xmlSampler2D, "source")) {
					samplerSurfaceMapping[xmlNewParamSID] =
						StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlSampler2DSource->GetText()));
				}
			}
			for (auto xmlTechnique: getChildrenByTagName(xmlProfile, "technique")) {
				for (auto xmlTechniqueNode: getChildren(xmlTechnique)) {
					for (auto xmlDiffuse: getChildrenByTagName(xmlTechniqueNode, "diffuse")) {
						for (auto xmlColor: getChildrenByTagName(xmlDiffuse, "color")) {
							StringTokenizer t;
							t.tokenize(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlColor->GetText())), L" ");
							array<float, 4> colorArray;
							for (auto i = 0; i < colorArray.size(); i++) {
								colorArray[i] = Float::parseFloat(t.nextToken());
							}
							material->getDiffuseColor()->set(&colorArray);
						}
						for (auto xmlTexture: getChildrenByTagName(xmlDiffuse, "texture")) {
							xmlDiffuseTextureId = StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlTexture->Attribute("texture")));

							auto sample2SurfaceIt = samplerSurfaceMapping.find(xmlDiffuseTextureId);
							wstring sample2Surface;
							if (sample2SurfaceIt != samplerSurfaceMapping.end()) {
								sample2Surface = sample2SurfaceIt->second;
							}
							if (sample2Surface.length() == 0) continue;

							wstring surface2Image;
							auto surface2ImageIt = surfaceImageMapping.find(sample2Surface);
							if (sample2SurfaceIt != surfaceImageMapping.end()) {
								surface2Image = surface2ImageIt->second;
							}
							if (surface2Image.length() > 0) {
								xmlDiffuseTextureId = surface2Image;
							}
						}
					}
					for (auto xmlAmbient: getChildrenByTagName(xmlTechniqueNode, "ambient")) {
						for (auto xmlColor: getChildrenByTagName(xmlAmbient, "color")) {
							StringTokenizer t;
							t.tokenize(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlColor->GetText())), L" ");
							array<float, 4> colorArray;
							for (auto i = 0; i < colorArray.size(); i++) {
								colorArray[i] = Float::parseFloat(t.nextToken());
							}
							material->getAmbientColor()->set(&colorArray);
						}
					}
					for (auto xmlEmission: getChildrenByTagName(xmlTechniqueNode, "emission")) {
						for (auto xmlColor: getChildrenByTagName(xmlEmission, "color")) {
							StringTokenizer t;
							t.tokenize(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlColor->GetText())), L" ");
							array<float, 4> colorArray;
							for (auto i = 0; i < colorArray.size(); i++) {
								colorArray[i] = Float::parseFloat(t.nextToken());
							}
							material->getEmissionColor()->set(&colorArray);
						}
					}
					auto hasSpecularMap = false;
					auto hasSpecularColor = false;
					for (auto xmlSpecular: getChildrenByTagName(xmlTechniqueNode, "specular")) {
						for (auto xmlTexture: getChildrenByTagName(xmlSpecular, "texture")) {
							xmlSpecularTextureId = StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlTexture->Attribute("texture")));

							auto sample2SurfaceIt = samplerSurfaceMapping.find(xmlSpecularTextureId);
							wstring sample2Surface;
							if (sample2SurfaceIt != samplerSurfaceMapping.end()) {
								sample2Surface = sample2SurfaceIt->second;
							}
							if (sample2Surface.length() == 0) continue;

							wstring surface2Image;
							auto surface2ImageIt = surfaceImageMapping.find(sample2Surface);
							if (sample2SurfaceIt != surfaceImageMapping.end()) {
								surface2Image = surface2ImageIt->second;
							}

							if (surface2Image.length() > 0) {
								xmlSpecularTextureId = surface2Image;
								hasSpecularMap = true;
							}
						}
						for (auto xmlColor: getChildrenByTagName(xmlSpecular, "color")) {
							StringTokenizer t;
							t.tokenize(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlColor->GetText())), L" ");
							array<float, 4> colorArray;
							for (auto i = 0; i < colorArray.size(); i++) {
								colorArray[i] = Float::parseFloat(t.nextToken());
							}
							material->getSpecularColor()->set(&colorArray);
							hasSpecularColor = true;
						}
					}
					if (hasSpecularMap == true && hasSpecularColor == false) {
						material->getSpecularColor()->set(1.0f, 1.0f, 1.0f, 1.0f);
					}
					for (auto xmlShininess: getChildrenByTagName(xmlTechniqueNode, "shininess"))
					for (auto xmlFloat: getChildrenByTagName(xmlShininess, "float")) {
						material->setShininess(Float::parseFloat(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlFloat->GetText()))));
					}
				}
				for (auto xmlBumpExtra: getChildrenByTagName(xmlTechnique, "extra"))
				for (auto xmlBumpTechnique: getChildrenByTagName(xmlBumpExtra, "technique"))
				for (auto xmlBumpTechniqueBump: getChildrenByTagName(xmlBumpTechnique, "bump"))
				for (auto xmlBumpTexture: getChildrenByTagName(xmlBumpTechniqueBump, "texture")) {
					xmlBumpTextureId = StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlBumpTexture->Attribute("texture")));

					auto sample2SurfaceIt = samplerSurfaceMapping.find(xmlBumpTextureId);
					wstring sample2Surface;
					if (sample2SurfaceIt != samplerSurfaceMapping.end()) {
						sample2Surface = sample2SurfaceIt->second;
					}
					if (sample2Surface.length() == 0) continue;

					wstring surface2Image;
					auto surface2ImageIt = surfaceImageMapping.find(sample2Surface);
					if (sample2SurfaceIt != surfaceImageMapping.end()) {
						surface2Image = surface2ImageIt->second;
					}

					if (surface2Image.length() > 0) xmlBumpTextureId = surface2Image;
				}
			}
		}
	}

	wstring xmlDiffuseTextureFilename;
	if (xmlDiffuseTextureId.length() > 0) {
		xmlDiffuseTextureFilename = getTextureFileNameById(xmlRoot, xmlDiffuseTextureId);
		if (xmlDiffuseTextureFilename.length() > 0) {
			xmlDiffuseTextureFilename = makeFileNameRelative(xmlDiffuseTextureFilename);
			material->setDiffuseTexture(pathName, xmlDiffuseTextureFilename);
		}
	}

	wstring xmlSpecularTextureFilename;
	if (xmlSpecularTextureId.length() > 0) {
		xmlSpecularTextureFilename = getTextureFileNameById(xmlRoot, xmlSpecularTextureId);
		if (xmlSpecularTextureFilename.length() > 0) {
			xmlSpecularTextureFilename = makeFileNameRelative(xmlSpecularTextureFilename);
			material->setSpecularTexture(pathName, xmlSpecularTextureFilename);
		}
	}

	wstring xmlBumpTextureFilename;
	if (xmlBumpTextureId.length() > 0) {
		xmlBumpTextureFilename = getTextureFileNameById(xmlRoot, xmlBumpTextureId);
		if (xmlBumpTextureFilename.length() > 0) {
			xmlBumpTextureFilename = makeFileNameRelative(xmlBumpTextureFilename);
			material->setNormalTexture(pathName, xmlBumpTextureFilename);
		}
	}

	wstring xmlDisplacementFilename;
	if (xmlDiffuseTextureFilename.length() > 0) {
		xmlDisplacementFilename = determineDisplacementFilename(pathName, L"diffuse", xmlDiffuseTextureFilename);
	}
	if (xmlDisplacementFilename.length() == 0 && xmlBumpTextureFilename.length() > 0) {
		xmlDisplacementFilename = determineDisplacementFilename(pathName, L"normal", xmlBumpTextureFilename);
	}
	if (xmlDisplacementFilename.length() > 0) {
		material->setDisplacementTexture(pathName, xmlDisplacementFilename);
	}

	if (authoringTool == DAEReader_AuthoringTool::BLENDER && material->getAmbientColor()->equals(BLENDER_AMBIENT_NONE)) {
		material->getAmbientColor()->set(
			material->getDiffuseColor()->getRed() * BLENDER_AMBIENT_FROM_DIFFUSE_SCALE,
			material->getDiffuseColor()->getGreen() * BLENDER_AMBIENT_FROM_DIFFUSE_SCALE,
			material->getDiffuseColor()->getBlue() * BLENDER_AMBIENT_FROM_DIFFUSE_SCALE,
			1.0f
		);
		material->getDiffuseColor()->set(
			material->getDiffuseColor()->getRed() * BLENDER_DIFFUSE_SCALE,
			material->getDiffuseColor()->getGreen() * BLENDER_DIFFUSE_SCALE,
			material->getDiffuseColor()->getBlue() * BLENDER_DIFFUSE_SCALE,
			material->getDiffuseColor()->getAlpha()
		);
	}

	(*model->getMaterials())[material->getId()] = material;

	return material;
}

const wstring DAEReader::determineDisplacementFilename(const wstring& path, const wstring& mapType, const wstring& fileName)
{
	auto tmpFileNameCandidate = StringUtils::toLowerCase(fileName);
	tmpFileNameCandidate = StringUtils::substring(tmpFileNameCandidate, 0, tmpFileNameCandidate.find_last_of(L'.'));
	if (StringUtils::endsWith(tmpFileNameCandidate, mapType) == true) {
		tmpFileNameCandidate = StringUtils::substring(tmpFileNameCandidate, 0, tmpFileNameCandidate.length() - mapType.length());
	}
	tmpFileNameCandidate = tmpFileNameCandidate + L"displacement";
	try {
		vector<wstring> fileNameCandidates;
		_FileSystem::getInstance()->list(path, &fileNameCandidates, new DAEReader_determineDisplacementFilename_1(tmpFileNameCandidate));
		if (fileNameCandidates.size() > 0) {
			return fileNameCandidates[0];
		}
	} catch (_Exception& exception) {
		_Console::print(wstring(L"DAEReader::determineDisplacementFilename(): An exception occurred: "));
		_Console::println(string(exception.what()));
	}
	return L"";
}

const wstring DAEReader::makeFileNameRelative(const wstring& fileName)
{
	if (StringUtils::startsWith(fileName, L"/") == true ||
		StringUtils::matches(fileName, L"^[A-Z]\\:\\\\.*$") == true) {
		int indexSlash = fileName.find_last_of(L'/');
		int indexBackslash = fileName.find_last_of(L'\\');
		if (indexSlash != -1 || indexBackslash != -1) {
			if (indexSlash > indexBackslash) {
				return StringUtils::substring(fileName, indexSlash + 1);
			} else {
				return StringUtils::substring(fileName, indexBackslash + 1);
			}
		}
	}
	return fileName;
}

const wstring DAEReader::getTextureFileNameById(TiXmlElement* xmlRoot, const wstring& xmlTextureId)
{
	wstring xmlTextureFilename;
	auto xmlLibraryImages = getChildrenByTagName(xmlRoot, "library_images").at(0);
	for (auto xmlImage: getChildrenByTagName(xmlLibraryImages, "image")) {
		if (StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlImage->Attribute("id"))) == xmlTextureId) {
			xmlTextureFilename = StringConverter::toWideString(AVOID_NULLPTR_STRING(getChildrenByTagName(xmlImage, "init_from").at(0)->GetText()));
			if (StringUtils::startsWith(xmlTextureFilename, L"file://") == true) {
				xmlTextureFilename = StringUtils::substring(xmlTextureFilename, 7);
			}
			break;
		}
	}
	return xmlTextureFilename;
}

const vector<TiXmlElement*> DAEReader::getChildrenByTagName(TiXmlElement* parent, const char* name)
{
	vector<TiXmlElement*> elementList;
	for (auto *child = parent->FirstChildElement(name); child != nullptr; child = child->NextSiblingElement(name)) {
		elementList.push_back(child);
	}
	return elementList;
}

const vector<TiXmlElement*> DAEReader::getChildren(TiXmlElement* parent)
{
	vector<TiXmlElement*> elementList;
	for (auto *child = parent->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
		elementList.push_back(child);
	}
	return elementList;
}
