// Generated from /tdme/src/tdme/engine/fileio/models/DAEReader.java
#include <tdme/engine/fileio/models/DAEReader.h>

#include <unordered_set>
#include <vector>

#include <java/io/Serializable.h>
#include <java/lang/CharSequence.h>
#include <java/lang/Comparable.h>
#include <java/lang/Float.h>
#include <java/lang/Integer.h>
#include <java/lang/Math.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Iterator.h>
#include <java/util/StringTokenizer.h>
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
#include <tdme/engine/subsystems/object/ModelUtilitiesInternal_ModelStatistics.h>
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
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/_ArrayList.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_Exception.h>
#include <tdme/utils/_HashMap.h>
#include <Array.h>
#include <SubArray.h>
#include <ObjectArray.h>

#include <ext/tinyxml/tinyxml.h>

#define AVOID_NULLPTR_STRING(arg) (arg == nullptr?"":arg)

using std::vector;
using std::unordered_set;

using tdme::engine::fileio::models::DAEReader;
using java::io::Serializable;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::Float;
using java::lang::Integer;
using java::lang::Math;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Iterator;
using java::util::StringTokenizer;
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
using tdme::engine::subsystems::object::ModelUtilitiesInternal_ModelStatistics;
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
using tdme::utils::StringConverter;
using tdme::utils::_ArrayList;
using tdme::utils::_Console;
using tdme::utils::_Exception;
using tdme::utils::_HashMap;

using tdme::ext::tinyxml::TiXmlDocument;
using tdme::ext::tinyxml::TiXmlElement;
using tdme::ext::tinyxml::TiXmlAttribute;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::String, ObjectArray, ::java::io::SerializableArray, ComparableArray, CharSequenceArray > StringArray;
}  // namespace lang
}  // namespace java

namespace tdme {
namespace engine {
namespace model {
typedef ::SubArray< ::tdme::engine::model::FacesEntity, ::java::lang::ObjectArray > FacesEntityArray;
typedef ::SubArray< ::tdme::engine::model::Joint, ::java::lang::ObjectArray > JointArray;
typedef ::SubArray< ::tdme::engine::model::TextureCoordinate, ::java::lang::ObjectArray > TextureCoordinateArray;
}  // namespace model
}  // namespace engine

namespace math {
typedef ::SubArray< ::tdme::math::Matrix4x4, ::java::lang::ObjectArray > Matrix4x4Array;
typedef ::SubArray< ::tdme::math::Vector3, ::java::lang::ObjectArray > Vector3Array;
}  // namespace math
}  // namespace tdme

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

DAEReader::DAEReader(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

DAEReader::DAEReader()
	: DAEReader(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

Color4* DAEReader::BLENDER_AMBIENT_NONE;

float DAEReader::BLENDER_AMBIENT_FROM_DIFFUSE_SCALE;

float DAEReader::BLENDER_DIFFUSE_SCALE;

Model* DAEReader::read(String* pathName, String* fileName) throw (ModelFileIOException, _FileSystemException)
{
	clinit();
	auto xmlContent = new String(_FileSystem::getInstance()->getContent(pathName, fileName));
	TiXmlDocument xmlDocument;
	xmlDocument.Parse(StringConverter::toString(xmlContent->getCPPWString()).c_str());
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

	String* tmpString = nullptr;
	auto model = new Model(
		_FileSystem::getInstance()->getCanonicalPath(pathName, fileName),
		fileName,
		upVector,
		rotationOrder,
		nullptr
	);
	setupModelImportRotationMatrix(xmlRoot, model);
	setupModelImportScaleMatrix(xmlRoot, model);
	String* xmlSceneId = nullptr;
	auto xmlScene = getChildrenByTagName(xmlRoot, "scene").at(0);
	for (auto xmlInstanceVisualscene: getChildrenByTagName(xmlScene, "instance_visual_scene")) {
		xmlSceneId = (tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlInstanceVisualscene->Attribute("url")))))->substring(1);
	}
	if (xmlSceneId == nullptr) {
		throw ModelFileIOException("No scene id found");
	}
	auto xmlLibraryVisualScenes = getChildrenByTagName(xmlRoot, "library_visual_scenes").at(0);
	for (auto xmlLibraryVisualScene: getChildrenByTagName(xmlLibraryVisualScenes, "visual_scene")) {
		auto xmlVisualSceneId = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlLibraryVisualScene->Attribute("id"))));
		if (xmlVisualSceneId->equals(xmlSceneId)) {
			auto fps = 30.0f;
			auto xmlExtraNodes = getChildrenByTagName(xmlLibraryVisualScene, "extra");
			if (xmlExtraNodes.empty() == false) {
				auto xmlExtraNode = xmlExtraNodes.at(0);
				for (auto xmlTechnique: getChildrenByTagName(xmlExtraNode, "technique")) {
					auto xmlFrameRateNodes = getChildrenByTagName(xmlTechnique, "frame_rate");
					if (xmlFrameRateNodes.empty() == false) {
						fps = Float::parseFloat(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlFrameRateNodes.at(0)->GetText()))));
						break;
					}
				}
			}
			model->setFPS(fps);
			for (auto xmlNode: getChildrenByTagName(xmlLibraryVisualScene, "node")) {
				auto group = readVisualSceneNode(authoringTool, pathName, model, nullptr, xmlRoot, xmlNode, fps);
				if (group != nullptr) {
					model->getSubGroups()->put(group->getId(), group);
					model->getGroups()->put(group->getId(), group);
				}
			}
		}
	}
	ModelHelper::setupJoints(model);
	ModelHelper::fixAnimationLength(model);
	ModelHelper::prepareForIndexedRendering(model);
	return model;
}

LevelEditorLevel* DAEReader::readLevel(String* pathName, String* fileName) throw (ModelFileIOException, _FileSystemException)
{
	String* tmpString = nullptr;

	clinit();

	auto modelPathName =
		::java::lang::StringBuilder().
			append(pathName)->
			append(u"/"_j)->
			append(fileName)->
			append(u"-models"_j)->
			toString();
	if (_FileSystem::getInstance()->fileExists(modelPathName)) {
		_FileSystem::getInstance()->removePath(modelPathName);
	}
	_FileSystem::getInstance()->createPath(
		modelPathName
	);

	auto levelEditorLevel = new LevelEditorLevel();
	auto xmlContent = new String(_FileSystem::getInstance()->getContent(pathName, fileName));
	TiXmlDocument xmlDocument;
	xmlDocument.Parse(StringConverter::toString(xmlContent->getCPPWString()).c_str());
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
	String* xmlSceneId = nullptr;
	auto xmlScene = getChildrenByTagName(xmlRoot, "scene").at(0);
	for (auto xmlInstanceVisualscene: getChildrenByTagName(xmlScene, "instance_visual_scene")) {
		xmlSceneId = (tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlInstanceVisualscene->Attribute("url")))))->substring(1);
	}
	if (xmlSceneId == nullptr) {
		throw ModelFileIOException("No scene id found");
	}
	auto xmlLibraryVisualScenes = getChildrenByTagName(xmlRoot, "library_visual_scenes").at(0);
	for (auto xmlLibraryVisualScene: getChildrenByTagName(xmlLibraryVisualScenes, "visual_scene")) {
		auto xmlVisualSceneId = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlLibraryVisualScene->Attribute("id"))));
		if (xmlVisualSceneId->equals(xmlSceneId)) {
			auto fps = 30.0f;
			auto xmlExtraNodes = getChildrenByTagName(xmlLibraryVisualScene,"extra");
			if (xmlExtraNodes.empty() == false) {
				auto xmlExtraNode = xmlExtraNodes.at(0);
				for (auto xmlTechnique: getChildrenByTagName(xmlExtraNode, "technique")) {
					auto xmlFrameRateNodes = getChildrenByTagName(xmlTechnique, "frame_rate");
					if (xmlFrameRateNodes.empty() == false) {
						fps = Float::parseFloat(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlFrameRateNodes.at(0)->GetText()))));
						break;
					}
				}
			}
			auto entityLibrary = levelEditorLevel->getEntityLibrary();
			LevelEditorEntity* emptyEntity = nullptr;
			auto nodeIdx = 0;
			for (auto xmlNode: getChildrenByTagName(xmlLibraryVisualScene, "node")) {
				auto nodeId = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlNode->Attribute("id"))));
				auto modelName = new String(nodeId->getCPPWString());
				modelName = modelName->replaceAll(u"[-_]{1}[0-9]+$"_j, u""_j);
				modelName = modelName->replaceAll(u"[0-9]+$"_j, u""_j);
				auto haveName = entityLibrary->getEntityCount() == 0;
				if (haveName == false) {
					for (auto i = 0; i < 10000; i++) {
						haveName = true;
						auto modelNameTry =
							::java::lang::StringBuilder().
							 	 append(modelName)->
								 append((i == 0 ? u""_j : String::valueOf(i)))->
								 toString();
						for (auto entityIdx = 0; entityIdx < entityLibrary->getEntityCount(); entityIdx++) {
							auto entity = entityLibrary->getEntityAt(entityIdx);
							if (entity->getName()->equals(modelNameTry) == true) {
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
						static_cast< Object* >(
							::java::lang::StringBuilder().
							 	 append(u"DAEReader::readLevel(): Skipping model '"_j)->
								 append(modelName)->
								 append(u"' as no name could be created for it."_j)->
								 toString()
							 )
					 );
					continue;
				}
				// FIXME: use canonical path
				auto model = new Model(
					modelPathName,
					::java::lang::StringBuilder().
					 append(fileName)->
					 append(u'-')->
					 append(modelName)->
					 toString(),
					 upVector,
					 rotationOrder,
					 nullptr
				);
				setupModelImportRotationMatrix(xmlRoot, model);
				auto modelImportRotationMatrix = new Matrix4x4(model->getImportTransformationsMatrix());
				setupModelImportScaleMatrix(xmlRoot, model);
				auto translation = new Vector3();
				auto scale = new Vector3();
				auto rotation = new Vector3();
				auto xAxis = new Vector3();
				auto yAxis = new Vector3();
				auto zAxis = new Vector3();
				Matrix4x4* nodeTransformationsMatrix = nullptr;
				auto xmlMatrixElements = getChildrenByTagName(xmlNode, "matrix");
				if (xmlMatrixElements.empty() == false) {
					auto xmlMatrix = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlMatrixElements.at(0)->GetText())));
					auto t = new StringTokenizer(xmlMatrix, u" \n\r"_j);
					nodeTransformationsMatrix = (
						new Matrix4x4(
							Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
							Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
							Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
							Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
							Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
							Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
							Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
							Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken())
						)
					)->transpose();
				}
				if (nodeTransformationsMatrix == nullptr) {
					throw ModelFileIOException(
						 "missing node transformations matrix for node '" +
						 StringConverter::toString(nodeId->getCPPWString()) +
						 "'"
					);
				}
				nodeTransformationsMatrix->getAxes(xAxis, yAxis, zAxis);
				nodeTransformationsMatrix->getTranslation(translation);
				nodeTransformationsMatrix->getScale(scale);
				xAxis->normalize();
				yAxis->normalize();
				zAxis->normalize();
				nodeTransformationsMatrix->setAxes(xAxis, yAxis, zAxis);
				if ((upVector == Model_UpVector::Y_UP && Vector3::computeDotProduct(Vector3::computeCrossProduct(xAxis, yAxis), zAxis) < 0.0f) || (upVector == Model_UpVector::Z_UP && Vector3::computeDotProduct(Vector3::computeCrossProduct(xAxis, zAxis), yAxis) < 0.0f)) {
					xAxis->scale(-1.0f);
					yAxis->scale(-1.0f);
					zAxis->scale(-1.0f);
					nodeTransformationsMatrix->setAxes(xAxis, yAxis, zAxis);
					scale->scale(-1.0f);
				}
				nodeTransformationsMatrix->computeEulerAngles(rotation);
				modelImportRotationMatrix->multiply(scale, scale);
				modelImportRotationMatrix->multiply(rotation, rotation);
				model->getImportTransformationsMatrix()->multiply(translation, translation);
				model->setFPS(fps);
				auto group = readVisualSceneNode(authoringTool, pathName, model, nullptr, xmlRoot, xmlNode, fps);
				if (group != nullptr) {
					group->getTransformationsMatrix()->identity();
					model->getSubGroups()->put(group->getId(), group);
					model->getGroups()->put(group->getId(), group);
				}
				ModelHelper::setupJoints(model);
				ModelHelper::fixAnimationLength(model);
				ModelHelper::prepareForIndexedRendering(model);
				auto entityType = LevelEditorEntity_EntityType::MODEL;
				auto modelStatistics = ModelUtilities::computeModelStatistics(model);
				if (modelStatistics->getOpaqueFaceCount() == 0 && modelStatistics->getTransparentFaceCount() == 0) {
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
						auto modelFileName =
							::java::lang::StringBuilder().
							 	 append(modelName)->
								 append(u".tm"_j)->
								 toString();
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
						emptyEntity = entityLibrary->addEmpty(nodeIdx++, u"Default Empty"_j, u""_j);
					}
					levelEditorEntity = emptyEntity;
				} else {
					_Console::println(static_cast< Object* >(u"DAEReader::readLevel(): unknown entity type. Skipping"_j));
					continue;
				}
				auto levelEditorObjectTransformations = new Transformations();
				levelEditorObjectTransformations->getTranslation()->set(translation);
				levelEditorObjectTransformations->getRotations()->add(new Rotation((*rotation->getArray())[rotationOrder->getAxis0VectorIndex()], rotationOrder->getAxis0()));
				levelEditorObjectTransformations->getRotations()->add(new Rotation((*rotation->getArray())[rotationOrder->getAxis1VectorIndex()], rotationOrder->getAxis1()));
				levelEditorObjectTransformations->getRotations()->add(new Rotation((*rotation->getArray())[rotationOrder->getAxis2VectorIndex()], rotationOrder->getAxis2()));
				levelEditorObjectTransformations->getScale()->set(scale);
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
		::java::lang::StringBuilder().
			 append(fileName)->
			 append(u".tl"_j)->
			 toString(),
		 levelEditorLevel
	);
	return levelEditorLevel;
}

DAEReader_AuthoringTool* DAEReader::getAuthoringTool(TiXmlElement* xmlRoot)
{
	clinit();
	String* tmpString = nullptr;
	for (auto xmlAsset: getChildrenByTagName(xmlRoot, "asset")) {
		for (auto xmlContributer: getChildrenByTagName(xmlAsset, "contributor")) {
			for (auto xmlAuthoringTool: getChildrenByTagName(xmlContributer, "authoring_tool")) {
				if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlAuthoringTool->GetText()))))->indexOf(u"Blender"_j) != -1) {
					return DAEReader_AuthoringTool::BLENDER;
				}
			}
		}
	}
	return DAEReader_AuthoringTool::UNKNOWN;
}

Model_UpVector* DAEReader::getUpVector(TiXmlElement* xmlRoot) throw (ModelFileIOException)
{
	clinit();
	for (auto xmlAsset: getChildrenByTagName(xmlRoot, "asset")) {
		for (auto xmlAssetUpAxis: getChildrenByTagName(xmlAsset, "up_axis")) {
			auto upAxis = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlAssetUpAxis->GetText())));
			if (upAxis->equalsIgnoreCase(u"Y_UP"_j)) {
				return Model_UpVector::Y_UP;
			} else
			if (upAxis->equalsIgnoreCase(u"Z_UP"_j)) {
				return Model_UpVector::Z_UP;
			} else
			if (upAxis->equalsIgnoreCase(u"X_UP"_j)) {
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
	clinit();
	for (auto xmlAsset: getChildrenByTagName(xmlRoot, "asset")) {
		for (auto xmlAssetUpAxis: getChildrenByTagName(xmlAsset, "up_axis")) {
			auto upAxis = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlAssetUpAxis->GetText())));
			if (upAxis->equalsIgnoreCase(u"Y_UP"_j)) {
			} else if (upAxis->equalsIgnoreCase(u"Z_UP"_j)) {
				model->getImportTransformationsMatrix()->rotate(-90.0f, new Vector3(1.0f, 0.0f, 0.0f));
			} else if (upAxis->equalsIgnoreCase(u"X_UP"_j)) {
				model->getImportTransformationsMatrix()->rotate(-90.0f, new Vector3(0.0f, 1.0f, 0.0f));
			} else {
				_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Warning: Unknown up axis: "_j)->append(upAxis)->toString()));
			}
		}
	}
}

void DAEReader::setupModelImportScaleMatrix(TiXmlElement* xmlRoot, Model* model)
{
	clinit();
	for (auto xmlAsset: getChildrenByTagName(xmlRoot, "asset")) {
		for (auto xmlAssetUnit: getChildrenByTagName(xmlAsset, "unit")) {
			String* tmp = nullptr;
			if ((tmp = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlAssetUnit->Attribute("meter"))))) != nullptr) {
				model->getImportTransformationsMatrix()->scale(Float::parseFloat(tmp));
			}
		}
	}
}

Group* DAEReader::readVisualSceneNode(DAEReader_AuthoringTool* authoringTool, String* pathName, Model* model, Group* parentGroup, TiXmlElement* xmlRoot, TiXmlElement* xmlNode, float fps)
{
	clinit();
	auto xmlInstanceControllers = getChildrenByTagName(xmlNode, "instance_controller");
	if (xmlInstanceControllers.empty() == false) {
		return readVisualSceneInstanceController(authoringTool, pathName, model, parentGroup, xmlRoot, xmlNode);
	} else {
		return readNode(authoringTool, pathName, model, parentGroup, xmlRoot, xmlNode, fps);
	}
}

Group* DAEReader::readNode(DAEReader_AuthoringTool* authoringTool, String* pathName, Model* model, Group* parentGroup, TiXmlElement* xmlRoot, TiXmlElement* xmlNode, float fps) throw (ModelFileIOException)
{
	clinit();
	String* tmpString = nullptr;

	auto xmlNodeId = AVOID_NULLPTR_STRING(xmlNode->Attribute("id")) != nullptr?new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlNode->Attribute("id")))):nullptr;
	auto xmlNodeName = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlNode->Attribute("name"))));
	if (xmlNodeId == nullptr) xmlNodeId = xmlNodeName;

	StringTokenizer* t = nullptr;
	Matrix4x4* transformationsMatrix = nullptr;
	auto xmlMatrixElements = getChildrenByTagName(xmlNode, "matrix");
	if (xmlMatrixElements.empty() == false) {
		auto xmlMatrix = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlMatrixElements.at(0)->GetText())));
		t = new StringTokenizer(xmlMatrix, u" \n\r"_j);
		transformationsMatrix = (new Matrix4x4(
			Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
			Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
			Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
			Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
			Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
			Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
			Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
			Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken())
		))->transpose();
	}

	auto group = new Group(model, parentGroup, xmlNodeId, xmlNodeName);
	if (transformationsMatrix != nullptr) {
		group->getTransformationsMatrix()->multiply(transformationsMatrix);
	}

	auto xmlAnimationsLibrary = getChildrenByTagName(xmlRoot, "library_animations");
	if (xmlAnimationsLibrary.empty() == false) {
		for (auto xmlAnimation: getChildrenByTagName(xmlAnimationsLibrary.at(0), "animation")) {
			auto _xmlAnimation = getChildrenByTagName(xmlAnimation, "animation");
			if (_xmlAnimation.empty() == false) {
				xmlAnimation = _xmlAnimation.at(0);
			}
			String* xmlSamplerSource = nullptr;
			auto xmlChannel = getChildrenByTagName(xmlAnimation, "channel").at(0);
			if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlChannel->Attribute("target")))))->startsWith(::java::lang::StringBuilder().append(xmlNodeId)->append(u"/"_j)->toString())) {
				xmlSamplerSource = (tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlChannel->Attribute("source")))))->substring(1);
			}
			if (xmlSamplerSource == nullptr) {
				continue;
			}
			String* xmlSamplerOutputSource = nullptr;
			String* xmlSamplerInputSource = nullptr;
			auto xmlSampler = getChildrenByTagName(xmlAnimation, "sampler").at(0);
			for (auto xmlSamplerInput: getChildrenByTagName(xmlSampler, "input")) {
				if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlSamplerInput->Attribute("semantic")))))->equals(u"OUTPUT"_j)) {
					xmlSamplerOutputSource = (tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlSamplerInput->Attribute("source")))))->substring(1);
				} else
				if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlSamplerInput->Attribute("semantic")))))->equals(u"INPUT"_j)) {
					xmlSamplerInputSource = (tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlSamplerInput->Attribute("source")))))->substring(1);
				}
			}
			if (xmlSamplerOutputSource == nullptr) {
				throw ModelFileIOException(
					"Could not find xml sampler output source for animation for '" +
					StringConverter::toString(xmlNodeId->getCPPWString()) +
					"'"
				);
			}
			floatArray* keyFrameTimes = nullptr;
			for (auto xmlAnimationSource: getChildrenByTagName(xmlAnimation, "source")) {
				if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlAnimationSource->Attribute("id")))))->equals(xmlSamplerInputSource)) {
					auto xmlFloatArray = getChildrenByTagName(xmlAnimationSource, "float_array").at(0);
					auto frames = Integer::parseInt(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlFloatArray->Attribute("count")))));
					auto valueString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlFloatArray->GetText())));
					auto keyFrameIdx = 0;
					keyFrameTimes = new floatArray(frames);
					t = new StringTokenizer(valueString, u" \n\r"_j);
					while (t->hasMoreTokens()) {
						(*keyFrameTimes)[keyFrameIdx++] = Float::parseFloat(t->nextToken());
					}
				}
			}
			Matrix4x4Array* keyFrameMatrices = nullptr;
			for (auto xmlAnimationSource: getChildrenByTagName(xmlAnimation, "source")) {
				if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlAnimationSource->Attribute("id")))))->equals(xmlSamplerOutputSource)) {
					auto xmlFloatArray = getChildrenByTagName(xmlAnimationSource, "float_array").at(0);
					auto keyFrames = Integer::parseInt(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlFloatArray->Attribute("count"))))) / 16;
					if (keyFrames > 0) {
						auto valueString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlFloatArray->GetText())));
						t = new StringTokenizer(valueString, u" \n\r"_j);
						auto keyFrameIdx = 0;
						keyFrameMatrices = new Matrix4x4Array(keyFrames);
						while (t->hasMoreTokens()) {
							keyFrameMatrices->set(
								keyFrameIdx,
								(new Matrix4x4(
									Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
									Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
									Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
									Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
									Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
									Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
									Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
									Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken())
								)
							)->transpose());
							keyFrameIdx++;
						}
					}
				}
			}
			if (keyFrameTimes != nullptr && keyFrameMatrices != nullptr) {
				auto frames = static_cast< int32_t >(Math::ceil((*keyFrameTimes)[keyFrameTimes->length - 1] * fps));
				ModelHelper::createDefaultAnimation(model, frames);
				auto animation = group->createAnimation(frames);
				auto transformationsMatrices = animation->getTransformationsMatrices();
				auto tansformationsMatrixLast = (*keyFrameMatrices)[0];
				auto keyFrameIdx = 0;
				auto frameIdx = 0;
				auto timeStampLast = 0.0f;
				for (auto keyFrameTime : *keyFrameTimes) {
					auto transformationsMatrixCurrent = (*keyFrameMatrices)[(keyFrameIdx) % keyFrameMatrices->length];
					float timeStamp;
					for (timeStamp = timeStampLast; timeStamp < keyFrameTime; timeStamp += 1.0f / fps) {
						if (frameIdx >= frames) {
							_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Warning: skipping frame: "_j)->append(frameIdx)->toString()));
							frameIdx++;
							continue;
						}
						Matrix4x4::interpolateLinear(tansformationsMatrixLast, transformationsMatrixCurrent, (timeStamp - timeStampLast) / (keyFrameTime - timeStampLast), (*transformationsMatrices)[frameIdx]);
						frameIdx++;
					}
					timeStampLast = timeStamp;
					tansformationsMatrixLast = transformationsMatrixCurrent;
					keyFrameIdx++;
				}
			}
		}
	}

	for (auto _xmlNode: getChildrenByTagName(xmlNode, "node")) {
		auto _group = readVisualSceneNode(authoringTool, pathName, model, group, xmlRoot, _xmlNode, fps);
		if (_group != nullptr) {
			group->getSubGroups()->put(_group->getId(), _group);
			model->getGroups()->put(_group->getId(), _group);
		}
	}

	String* xmlInstanceGeometryId = nullptr;
	auto xmlInstanceGeometryElements = getChildrenByTagName(xmlNode, "instance_geometry");
	if (xmlInstanceGeometryElements.empty() == false) {
		auto xmlInstanceGeometryElement = xmlInstanceGeometryElements.at(0);
		xmlInstanceGeometryId = (tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlInstanceGeometryElement->Attribute("url")))))->substring(1);
		auto materialSymbols = new _HashMap();
		for (auto xmlBindMaterial: getChildrenByTagName(xmlInstanceGeometryElement, "bind_material"))
		for (auto xmlTechniqueCommon: getChildrenByTagName(xmlBindMaterial, "technique_common"))
		for (auto xmlInstanceMaterial: getChildrenByTagName(xmlTechniqueCommon, "instance_material")) {
			materialSymbols->put(
				new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlInstanceMaterial->Attribute("symbol")))),
				new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlInstanceMaterial->Attribute("target"))))
			);
		}
		readGeometry(authoringTool, pathName, model, group, xmlRoot, xmlInstanceGeometryId, materialSymbols);
		return group;
	}

	String* xmlInstanceNodeId = nullptr;
	for (auto xmlInstanceNodeElement: getChildrenByTagName(xmlNode, "instance_node")) {
		xmlInstanceNodeId = (tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlInstanceNodeElement->Attribute("url")))))->substring(1);
	}
	if (xmlInstanceNodeId != nullptr) {
		for (auto xmlLibraryNodes: getChildrenByTagName(xmlRoot, "library_nodes"))
		for (auto xmlLibraryNode: getChildrenByTagName(xmlLibraryNodes, "node"))
		if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlLibraryNode->Attribute("id")))))->equals(xmlInstanceNodeId)) {
			for (auto _xmlNode: getChildrenByTagName(xmlLibraryNode, "node")) {
				auto _group = readVisualSceneNode(authoringTool, pathName, model, parentGroup, xmlRoot, _xmlNode, fps);
				if (_group != nullptr) {
					group->getSubGroups()->put(_group->getId(), _group);
					model->getGroups()->put(_group->getId(), _group);
				}
			}
			for (auto xmlInstanceGeometry: getChildrenByTagName(xmlLibraryNode, "instance_geometry")) {
				auto xmlGeometryId = (tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlInstanceGeometry->Attribute("url")))))->substring(1);
				auto materialSymbols = new _HashMap();
				for (auto xmlBindMaterial: getChildrenByTagName(xmlInstanceGeometry, "bind_material"))
				for (auto xmlTechniqueCommon: getChildrenByTagName(xmlBindMaterial, "technique_common"))
				for (auto xmlInstanceMaterial: getChildrenByTagName(xmlTechniqueCommon, "instance_material")) {
					materialSymbols->put(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlInstanceMaterial->Attribute("symbol")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlInstanceMaterial->Attribute("target"))))
					);
				}
				readGeometry(authoringTool, pathName, model, group, xmlRoot, xmlGeometryId, materialSymbols);
			}
		}
	}
	return group;
}

Group* DAEReader::readVisualSceneInstanceController(DAEReader_AuthoringTool* authoringTool, String* pathName, Model* model, Group* parentGroup, TiXmlElement* xmlRoot, TiXmlElement* xmlNode) throw (ModelFileIOException)
{
	clinit();

	String* tmpString = nullptr;

	StringTokenizer* t;
	auto xmlNodeId = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlNode->Attribute("id"))));
	auto xmlNodeName = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlNode->Attribute("name"))));
	auto materialSymbols = new _HashMap();
	String* xmlGeometryId = nullptr;
	auto xmlInstanceControllers = getChildrenByTagName(xmlNode, "instance_controller");
	TiXmlElement* xmlSkin = nullptr;
	auto xmlInstanceController = xmlInstanceControllers.at(0);

	for (auto xmlBindMaterial: getChildrenByTagName(xmlInstanceController, "bind_material"))
	for (auto xmlTechniqueCommon: getChildrenByTagName(xmlBindMaterial, "technique_common"))
	for (auto xmlInstanceMaterial: getChildrenByTagName(xmlTechniqueCommon, "instance_material")) {
		materialSymbols->put(
			new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlInstanceMaterial->Attribute("symbol")))),
			new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlInstanceMaterial->Attribute("target"))))
		);
	}

	auto xmlInstanceControllerId = (tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlInstanceController->Attribute("url")))))->substring(1);
	auto xmlLibraryControllers = getChildrenByTagName(xmlRoot, "library_controllers").at(0);
	for (auto xmlLibraryController: getChildrenByTagName(xmlLibraryControllers, "controller")) {
		if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlLibraryController->Attribute("id")))))->equals(xmlInstanceControllerId)) {
			auto xmlSkins = getChildrenByTagName(xmlLibraryController, "skin");
			if (xmlSkins.empty() == false) {
				xmlSkin = xmlSkins.at(0);
			}
		}
	}
	if (xmlSkin == nullptr) {
		throw ModelFileIOException(
			"skin not found for instance controller '" +
			StringConverter::toString(xmlNodeId->getCPPWString()) +
			"'"
		);
	}

	xmlGeometryId = (tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlSkin->Attribute("source")))))->substring(1);
	auto xmlMatrix = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(getChildrenByTagName(xmlSkin, "bind_shape_matrix").at(0)->GetText())));
	t = new StringTokenizer(xmlMatrix, u" \n\r"_j);
	auto bindShapeMatrix =
		(new Matrix4x4(
			Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
			Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
			Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
			Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
			Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
			Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
			Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
			Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken())
		))->transpose();

	auto group = new Group(model, parentGroup, xmlNodeId, xmlNodeName);
	auto skinning = group->createSkinning();
	readGeometry(authoringTool, pathName, model, group, xmlRoot, xmlGeometryId, materialSymbols);

	String* xmlJointsSource = nullptr;
	String* xmlJointsInverseBindMatricesSource = nullptr;
	auto xmlJoints = getChildrenByTagName(xmlSkin, "joints").at(0);
	for (auto xmlJointsInput: getChildrenByTagName(xmlJoints, "input")) {
		if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlJointsInput->Attribute("semantic")))))->equals(u"JOINT"_j)) {
			xmlJointsSource = (tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlJointsInput->Attribute("source")))))->substring(1);
		} else
		if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlJointsInput->Attribute("semantic")))))->equals(u"INV_BIND_MATRIX"_j)) {
			xmlJointsInverseBindMatricesSource = (tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlJointsInput->Attribute("source")))))->substring(1);
		}
	}
	if (xmlJointsSource == nullptr) {
		throw ModelFileIOException(
			"joint source not found for instance controller '" +
			StringConverter::toString(xmlNodeId->getCPPWString()) +
			"'"
		);
	}

	vector<Joint*> joints;
	for (auto xmlSkinSource: getChildrenByTagName(xmlSkin, "source")) {
		if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlSkinSource->Attribute("id")))))->equals(xmlJointsSource)) {
			t = new StringTokenizer(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(getChildrenByTagName(xmlSkinSource, "Name_array").at(0)->GetText()))), u" \n\r"_j);
			while (t->hasMoreTokens()) {
				joints.push_back(new Joint(t->nextToken()));
			}
		}
	}
	skinning->setJoints(joints);

	if (xmlJointsInverseBindMatricesSource == nullptr) {
		throw ModelFileIOException(
			"inverse bind matrices source not found for instance controller '" +
			StringConverter::toString(xmlNodeId->getCPPWString()) +
			"'"
		);
	}

	for (auto xmlSkinSource: getChildrenByTagName(xmlSkin, "source")) {
		if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlSkinSource->Attribute("id")))))->equals(xmlJointsInverseBindMatricesSource)) {
			t = new StringTokenizer((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(getChildrenByTagName(xmlSkinSource, "float_array").at(0)->GetText())))), u" \n\r"_j);
			auto _joints = skinning->getJoints();
			for (auto i = 0; i < _joints->length; i++) {
				(*_joints)[i]->getBindMatrix()->multiply(bindShapeMatrix);
				(*_joints)[i]->getBindMatrix()->multiply(
					(new Matrix4x4(
						Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
						Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
						Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
						Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
						Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
						Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
						Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()),
						Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken())
					))->transpose());
			}
		}
	}

	vector<float> weights;
	auto xmlJointOffset = -1;
	auto xmlWeightOffset = -1;
	String* xmlWeightsSource = nullptr;
	auto xmlVertexWeights = getChildrenByTagName(xmlSkin, "vertex_weights").at(0);
	auto xmlVertexWeightInputs = getChildrenByTagName(xmlVertexWeights, "input");
	for (auto xmlVertexWeightInput: xmlVertexWeightInputs) {
		if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlVertexWeightInput->Attribute("semantic")))))->equals(u"JOINT"_j)) {
			if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlVertexWeightInput->Attribute("source")))))->substring(1)->equals(xmlJointsSource) == false) {
				throw ModelFileIOException("joint inverse bind matrices source do not match");
			}
			xmlJointOffset = Integer::parseInt(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlVertexWeightInput->Attribute("offset")))));
		} else
		if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlVertexWeightInput->Attribute("semantic")))))->equals(u"WEIGHT"_j)) {
			xmlWeightOffset = Integer::parseInt(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlVertexWeightInput->Attribute("offset")))));
			xmlWeightsSource = (tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlVertexWeightInput->Attribute("source")))))->substring(1);
		}
	}
	if (xmlJointOffset == -1) {
		throw ModelFileIOException(
			"xml vertex weight joint offset missing for node '" +
			StringConverter::toString(xmlNodeId->getCPPWString()) +
			"'"
		);
	}
	if (xmlWeightOffset == -1) {
		throw ModelFileIOException(
			"xml vertex weight weight offset missing for node " +
			StringConverter::toString(xmlNodeId->getCPPWString()) +
			"'"
		);
	}
	if (xmlWeightsSource == nullptr) {
		throw ModelFileIOException(
			"xml vertex weight weight source missing for node '" +
			StringConverter::toString(xmlNodeId->getCPPWString()) +
			"'"
		);
	}
	for (auto xmlSkinSource: getChildrenByTagName(xmlSkin, "source")) {
		if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlSkinSource->Attribute("id")))))->equals(xmlWeightsSource)) {
			t = new StringTokenizer(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(getChildrenByTagName(xmlSkinSource, "float_array").at(0)->GetText()))), u" \n\r"_j);
			while (t->hasMoreTokens()) {
				weights.push_back(Float::parseFloat(t->nextToken()));
			}
		}
	}
	skinning->setWeights(weights);
	auto xmlVertexWeightInputCount = xmlVertexWeightInputs.size();
	auto vertexJointsInfluenceCountString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(getChildrenByTagName(xmlVertexWeights, "vcount").at(0)->GetText())));
	auto vertexJointsInfluencesString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(getChildrenByTagName(xmlVertexWeights, "v").at(0)->GetText())));
	t = new StringTokenizer(vertexJointsInfluenceCountString, u" \n\r"_j);
	auto t2 = new StringTokenizer(vertexJointsInfluencesString, u" \n\r"_j);
	auto offset = 0;
	vector<vector<JointWeight*>> verticesJointsWeights;
	while (t->hasMoreTokens()) {
		auto vertexJointsInfluencesCount = Integer::parseInt(t->nextToken());
		vector<JointWeight*>vertexJointsWeights;
		for (auto i = 0; i < vertexJointsInfluencesCount; i++) {
			auto vertexJoint = -1;
			auto vertexWeight = -1;
			while (vertexJoint == -1 || vertexWeight == -1) {
				auto value = Integer::parseInt(t2->nextToken());
				if (offset % xmlVertexWeightInputCount == xmlJointOffset) {
					vertexJoint = value;
				} else if (offset % xmlVertexWeightInputCount == xmlWeightOffset) {
					vertexWeight = value;
				}
				offset++;
			}
			vertexJointsWeights.push_back(new JointWeight(vertexJoint, vertexWeight));
		}
		verticesJointsWeights.push_back(vertexJointsWeights);
	}
	skinning->setVerticesJointsWeights(verticesJointsWeights);

	return group;
}

void DAEReader::readGeometry(DAEReader_AuthoringTool* authoringTool, String* pathName, Model* model, Group* group, TiXmlElement* xmlRoot, String* xmlNodeId, _HashMap* materialSymbols) throw (ModelFileIOException)
{
	clinit();
	StringTokenizer* t;
	String* tmpString = nullptr;
	FacesEntity* facesEntity = nullptr;
	vector<FacesEntity*> facesEntities;
	for (int i = 0; i < group->getFacesEntities()->length; i++) {
		facesEntities.push_back(group->getFacesEntities()->get(i));
	}
	auto verticesOffset = group->getVertices()->length;
	auto vertices = new _ArrayList(group->getVertices());
	auto normalsOffset = group->getNormals()->length;
	auto normals = new _ArrayList(group->getNormals());
	auto textureCoordinatesOffset = group->getTextureCoordinates() != nullptr ? group->getTextureCoordinates()->length : 0;
	auto textureCoordinates = group->getTextureCoordinates() != nullptr ? new _ArrayList(group->getTextureCoordinates()) : new _ArrayList();
	auto xmlLibraryGeometries = getChildrenByTagName(xmlRoot, "library_geometries").at(0);
	for (auto xmlGeometry: getChildrenByTagName(xmlLibraryGeometries, "geometry")) {
		if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlGeometry->Attribute("id")))))->equals(xmlNodeId)) {
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
				vector<Face*> faces;
				facesEntity = new FacesEntity(group, xmlNodeId);
				if ((tmpString = new String(StringConverter::toWideString(xmlPolygons->Value())))->toLowerCase()->equals(u"polylist"_j)) {
					t = new StringTokenizer(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(getChildrenByTagName(xmlPolygons, "vcount").at(0)->GetText()))));
					while (t->hasMoreTokens()) {
						auto vertexCount = Integer::parseInt(t->nextToken());
						if (vertexCount != 3) {
							throw ModelFileIOException(
								 "we only support triangles in '" +
								 StringConverter::toString(xmlNodeId->getCPPWString()) +
								 "'"
							);
						}
					}
				}
				auto xmlInputs = -1;
				auto xmlVerticesOffset = -1;
				String* xmlVerticesSource = nullptr;
				auto xmlNormalsOffset = -1;
				String* xmlNormalsSource = nullptr;
				auto xmlTexCoordOffset = -1;
				String* xmlTexCoordSource = nullptr;
				auto xmlColorOffset = -1;
				String* xmlColorSource = nullptr;
				auto xmlMaterialId = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlPolygons->Attribute("material"))));
				auto materialSymbol = java_cast< String* >(materialSymbols->get(xmlMaterialId));
				if (materialSymbol != nullptr)
					xmlMaterialId = materialSymbol->substring(1);

				if (xmlMaterialId != nullptr && xmlMaterialId->length() > 0) {
					auto material = java_cast< Material* >(model->getMaterials()->get(xmlMaterialId));
					if (material == nullptr) {
						material = readMaterial(authoringTool, pathName, model, xmlRoot, xmlMaterialId);
					}
					facesEntity->setMaterial(material);
				}
				unordered_set<Integer*> xmlInputSet;
				for (auto xmlTrianglesInput: getChildrenByTagName(xmlPolygons, "input")) {
					if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlTrianglesInput->Attribute("semantic")))))->equals(u"VERTEX"_j)) {
						xmlVerticesOffset = Integer::parseInt(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlTrianglesInput->Attribute("offset")))));
						xmlVerticesSource = (tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlTrianglesInput->Attribute("source")))))->substring(1);
						xmlInputSet.insert(Integer::valueOf(xmlVerticesOffset));
					} else
					if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlTrianglesInput->Attribute("semantic")))))->equals(u"NORMAL"_j)) {
						xmlNormalsOffset = Integer::parseInt(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlTrianglesInput->Attribute("offset")))));
						xmlNormalsSource = (tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlTrianglesInput->Attribute("source")))))->substring(1);
						xmlInputSet.insert(Integer::valueOf(xmlNormalsOffset));
					} else
					if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlTrianglesInput->Attribute("semantic")))))->equals(u"TEXCOORD"_j)) {
						xmlTexCoordOffset = Integer::parseInt(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlTrianglesInput->Attribute("offset")))));
						xmlTexCoordSource = (tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlTrianglesInput->Attribute("source")))))->substring(1);
						xmlInputSet.insert(Integer::valueOf(xmlTexCoordOffset));
					} else
					if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlTrianglesInput->Attribute("semantic")))))->equals(u"COLOR"_j)) {
						xmlColorOffset = Integer::parseInt(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlTrianglesInput->Attribute("offset")))));
						xmlColorSource = (tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlTrianglesInput->Attribute("source")))))->substring(1);
						xmlInputSet.insert(Integer::valueOf(xmlColorOffset));
					}
				}
				xmlInputs = xmlInputSet.size();
				for (auto xmlVertices: getChildrenByTagName(xmlMesh, "vertices")) {
					if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlVertices->Attribute("id")))))->equals(xmlVerticesSource)) {
						for (auto xmlVerticesInput: getChildrenByTagName(xmlVertices, "input")) {
							if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlVerticesInput->Attribute("semantic")))))->equalsIgnoreCase(u"position"_j)) {
								xmlVerticesSource = (tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlVerticesInput->Attribute("source")))))->substring(1);
							} else
							if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlVerticesInput->Attribute("semantic")))))->equalsIgnoreCase(u"normal"_j)) {
								xmlNormalsSource = (tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlVerticesInput->Attribute("source")))))->substring(1);
							}
						}
					}
				}
				if (xmlVerticesSource == nullptr) {
					throw ModelFileIOException(
						"Could not determine triangles vertices source for '" +
						StringConverter::toString(xmlNodeId->getCPPWString()) +
						"'"
					);
				}
				if (xmlNormalsSource == nullptr) {
					throw ModelFileIOException(
						"Could not determine triangles normal source for '" +
						StringConverter::toString(xmlNodeId->getCPPWString()) +
						"'"
					);
				}
				for (auto xmlMeshSource: getChildrenByTagName(xmlMesh, "source")) {
					if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlMeshSource->Attribute("id")))))->equals(xmlVerticesSource)) {
						auto xmlFloatArray = getChildrenByTagName(xmlMeshSource, "float_array").at(0);
						auto valueString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlFloatArray->GetText())));
						t = new StringTokenizer(valueString, u" \n\r"_j);
						while (t->hasMoreTokens()) {
							auto v = new Vector3(Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()));
							vertices->add(v);
						}
					} else
					if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlMeshSource->Attribute("id")))))->equals(xmlNormalsSource)) {
						auto xmlFloatArray = getChildrenByTagName(xmlMeshSource, "float_array").at(0);
						auto valueString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlFloatArray->GetText())));
						t = new StringTokenizer(valueString, u" \n\r"_j);
						while (t->hasMoreTokens()) {
							auto v = new Vector3(Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()));
							normals->add(v);
						}
					}
					if (xmlTexCoordSource != nullptr) {
						if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlMeshSource->Attribute("id")))))->equals(xmlTexCoordSource)) {
							auto xmlFloatArray = getChildrenByTagName(xmlMeshSource, "float_array").at(0);
							auto valueString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlFloatArray->GetText())));
							t = new StringTokenizer(valueString, u" \n\r"_j);
							while (t->hasMoreTokens()) {
								auto tc = new TextureCoordinate(Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()));
								textureCoordinates->add(tc);
							}
						}
					}
				}
				for (auto xmlPolygon: getChildrenByTagName(xmlPolygons, "p")) {
					auto valueString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlPolygon->GetText())));
					t = new StringTokenizer(valueString, u" \n\r"_j);
					auto vi = new int32_tArray(3);
					auto viIdx = 0;
					auto ni = new int32_tArray(3);
					auto niIdx = 0;
					auto ti = xmlTexCoordSource == nullptr ? static_cast< int32_tArray* >(nullptr) : new int32_tArray(3);
					auto tiIdx = 0;
					auto valueIdx = 0;
					auto valid = true;
					while (t->hasMoreTokens()) {
						auto value = Integer::parseInt(t->nextToken());
						if (valueIdx % xmlInputs == xmlVerticesOffset) {
							(*vi)[viIdx++] = value;
							if (value < 0 || value >= vertices->size() - verticesOffset) {
								valid = false;
							}
							if (xmlNormalsSource != nullptr && xmlNormalsOffset == -1) {
								(*ni)[niIdx++] = value;
								if (value < 0 || value >= normals->size() - normalsOffset) {
									valid = false;
								}
							}
						}
						if (xmlNormalsOffset != -1 && valueIdx % xmlInputs == xmlNormalsOffset) {
							(*ni)[niIdx++] = value;
							if (value < 0 || value >= normals->size() - normalsOffset) {
								valid = false;
							}
						}
						if (xmlTexCoordOffset != -1 && valueIdx % xmlInputs == xmlTexCoordOffset) {
							(*ti)[tiIdx++] = value;
							if (value < 0 || value >= textureCoordinates->size() - textureCoordinatesOffset) {
								valid = false;
							}
						}
						if (viIdx == 3 && niIdx == 3 && (ti == nullptr || tiIdx == 3)) {
							if (valid == true) {
								auto f = new Face(
									group,
									(*vi)[0] + verticesOffset,
									(*vi)[1] + verticesOffset,
									(*vi)[2] + verticesOffset,
									(*ni)[0] + normalsOffset,
									(*ni)[1] + normalsOffset,
									(*ni)[2] + normalsOffset
								);
								if (ti != nullptr) {
									f->setTextureCoordinateIndices(
										(*ti)[0] + textureCoordinatesOffset,
										(*ti)[1] + textureCoordinatesOffset,
										(*ti)[2] + textureCoordinatesOffset
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
					facesEntity->setFaces(faces);
					facesEntities.push_back(facesEntity);
				}
			}
		}
	}

	group->setVertices(vertices);
	group->setNormals(normals);
	if (textureCoordinates->size() > 0)
		group->setTextureCoordinates(textureCoordinates);

	group->setFacesEntities(facesEntities);
	ModelHelper::createNormalTangentsAndBitangents(group);
	group->determineFeatures();
}

Material* DAEReader::readMaterial(DAEReader_AuthoringTool* authoringTool, String* pathName, Model* model, TiXmlElement* xmlRoot, String* xmlNodeId)
{
	clinit();
	String* tmpString = nullptr;
	String* xmlEffectId = nullptr;
	auto xmlLibraryMaterials = getChildrenByTagName(xmlRoot, "library_materials").at(0);
	for (auto xmlMaterial: getChildrenByTagName(xmlLibraryMaterials, "material")) {
		if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlMaterial->Attribute("id")))))->equals(xmlNodeId)) {
			auto xmlInstanceEffect = getChildrenByTagName(xmlMaterial, "instance_effect").at(0);
			xmlEffectId = (tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlInstanceEffect->Attribute("url")))))->substring(1);
		}
	}
	if (xmlEffectId == nullptr) {
		_Console::println(
			static_cast< Object* >(
				::java::lang::StringBuilder().
				 	 append(u"Could not determine effect id for '"_j)->
					 append(xmlNodeId)->
					 append(u"'"_j)->
					 toString()
			 )
		 );
		return nullptr;
	}
	auto material = new Material(xmlNodeId);
	String* xmlDiffuseTextureId = nullptr;
	String* xmlSpecularTextureId = nullptr;
	String* xmlBumpTextureId = nullptr;
	auto xmlLibraryEffects = getChildrenByTagName(xmlRoot, "library_effects").at(0);
	for (auto xmlEffect: getChildrenByTagName(xmlLibraryEffects, "effect")) {
		if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlEffect->Attribute("id")))))->equals(xmlEffectId)) {
			auto xmlProfile = getChildrenByTagName(xmlEffect, "profile_COMMON").at(0);
			auto samplerSurfaceMapping = new _HashMap();
			auto surfaceImageMapping = new _HashMap();
			for (auto xmlNewParam: getChildrenByTagName(xmlProfile, "newparam")) {
				auto xmlNewParamSID = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlNewParam->Attribute("sid"))));
				for (auto xmlSurface: getChildrenByTagName(xmlNewParam, "surface"))
				for (auto xmlSurfaceInitFrom: getChildrenByTagName(xmlSurface, "init_from")) {
					surfaceImageMapping->put(
						xmlNewParamSID,
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlSurfaceInitFrom->GetText())))
					);
				}
				for (auto xmlSampler2D: getChildrenByTagName(xmlNewParam, "sampler2D"))
				for (auto xmlSampler2DSource: getChildrenByTagName(xmlSampler2D, "source")) {
					samplerSurfaceMapping->put(
						xmlNewParamSID,
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlSampler2DSource->GetText())))
					);
				}
			}
			for (auto xmlTechnique: getChildrenByTagName(xmlProfile, "technique")) {
				for (auto xmlTechniqueNode: getChildren(xmlTechnique)) {
					for (auto xmlDiffuse: getChildrenByTagName(xmlTechniqueNode, "diffuse")) {
						for (auto xmlTexture: getChildrenByTagName(xmlDiffuse, "texture")) {
							xmlDiffuseTextureId = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlTexture->Attribute("texture"))));
							auto sample2Surface = java_cast< String* >(samplerSurfaceMapping->get(xmlDiffuseTextureId));
							String* surface2Image = nullptr;
							if (sample2Surface != nullptr)
								surface2Image = java_cast< String* >(surfaceImageMapping->get(sample2Surface));
							if (surface2Image != nullptr)
								xmlDiffuseTextureId = surface2Image;
						}
						for (auto xmlColor: getChildrenByTagName(xmlDiffuse, "color")) {
							auto t = new StringTokenizer(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlColor->GetText()))), u" "_j);
							material->getDiffuseColor()->set(
								Float::parseFloat(t->nextToken()),
								Float::parseFloat(t->nextToken()),
								Float::parseFloat(t->nextToken()),
								Float::parseFloat(t->nextToken())
							);
						}
					}
					for (auto xmlAmbient: getChildrenByTagName(xmlTechniqueNode, "ambient")) {
						for (auto xmlColor: getChildrenByTagName(xmlAmbient, "color")) {
							auto t = new StringTokenizer(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlColor->GetText()))), u" "_j);
							material->getAmbientColor()->set(
								Float::parseFloat(t->nextToken()),
								Float::parseFloat(t->nextToken()),
								Float::parseFloat(t->nextToken()),
								Float::parseFloat(t->nextToken())
							);
						}
					}
					for (auto xmlEmission: getChildrenByTagName(xmlTechniqueNode, "emission")) {
						for (auto xmlColor: getChildrenByTagName(xmlEmission, "color")) {
							auto t = new StringTokenizer(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlColor->GetText()))), u" "_j);
							material->getEmissionColor()->set(
								Float::parseFloat(t->nextToken()),
								Float::parseFloat(t->nextToken()),
								Float::parseFloat(t->nextToken()),
								Float::parseFloat(t->nextToken())
							);
						}
					}
					auto hasSpecularMap = false;
					auto hasSpecularColor = false;
					for (auto xmlSpecular: getChildrenByTagName(xmlTechniqueNode, "specular")) {
						for (auto xmlTexture: getChildrenByTagName(xmlSpecular, "texture")) {
							xmlSpecularTextureId = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlTexture->Attribute("texture"))));
							auto sample2Surface = samplerSurfaceMapping->get(xmlSpecularTextureId);
							String* surface2Image = nullptr;
							if (sample2Surface != nullptr) surface2Image = java_cast< String* >(surfaceImageMapping->get(sample2Surface));
							if (surface2Image != nullptr) xmlSpecularTextureId = surface2Image;
							hasSpecularMap = true;
						}
						for (auto xmlColor: getChildrenByTagName(xmlSpecular, "color")) {
							auto t = new StringTokenizer(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlColor->GetText()))), u" "_j);
							material->getSpecularColor()->set(
								Float::parseFloat(t->nextToken()),
								Float::parseFloat(t->nextToken()),
								Float::parseFloat(t->nextToken()),
								Float::parseFloat(t->nextToken())
							);
							hasSpecularColor = true;
						}
					}
					if (hasSpecularMap == true && hasSpecularColor == false) {
						material->getSpecularColor()->set(1.0f, 1.0f, 1.0f, 1.0f);
					}
					for (auto xmlShininess: getChildrenByTagName(xmlTechniqueNode, "shininess"))
					for (auto xmlFloat: getChildrenByTagName(xmlShininess, "float")) {
							material->setShininess(Float::parseFloat(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlFloat->GetText())))));
					}
				}
				for (auto xmlBumpExtra: getChildrenByTagName(xmlTechnique, "extra"))
				for (auto xmlBumpTechnique: getChildrenByTagName(xmlBumpExtra, "technique"))
				for (auto xmlBumpTechniqueBump: getChildrenByTagName(xmlBumpTechnique, "bump"))
				for (auto xmlBumpTexture: getChildrenByTagName(xmlBumpTechniqueBump, "texture")) {
					xmlBumpTextureId = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlBumpTexture->Attribute("texture"))));
					auto sample2Surface = java_cast< String* >(samplerSurfaceMapping->get(xmlBumpTextureId));
					String* surface2Image = nullptr;
					if (sample2Surface != nullptr) surface2Image = java_cast< String* >(surfaceImageMapping->get(sample2Surface));
					if (surface2Image != nullptr) xmlBumpTextureId = surface2Image;
				}
			}
		}
	}

	String* xmlDiffuseTextureFilename = nullptr;
	if (xmlDiffuseTextureId != nullptr) {
		xmlDiffuseTextureFilename = getTextureFileNameById(xmlRoot, xmlDiffuseTextureId);
		if (xmlDiffuseTextureFilename != nullptr) {
			xmlDiffuseTextureFilename = makeFileNameRelative(xmlDiffuseTextureFilename);
			material->setDiffuseTexture(pathName, xmlDiffuseTextureFilename);
		}
	}

	String* xmlSpecularTextureFilename = nullptr;
	if (xmlSpecularTextureId != nullptr) {
		xmlSpecularTextureFilename = getTextureFileNameById(xmlRoot, xmlSpecularTextureId);
		if (xmlSpecularTextureFilename != nullptr) {
			xmlSpecularTextureFilename = makeFileNameRelative(xmlSpecularTextureFilename);
			material->setSpecularTexture(pathName, xmlSpecularTextureFilename);
		}
	}

	String* xmlBumpTextureFilename = nullptr;
	if (xmlBumpTextureId != nullptr) {
		xmlBumpTextureFilename = getTextureFileNameById(xmlRoot, xmlBumpTextureId);
		if (xmlBumpTextureFilename != nullptr) {
			xmlBumpTextureFilename = makeFileNameRelative(xmlBumpTextureFilename);
			material->setNormalTexture(pathName, xmlBumpTextureFilename);
		}
	}

	String* xmlDisplacementFilename = nullptr;
	if (xmlDiffuseTextureFilename != nullptr) {
		xmlDisplacementFilename = determineDisplacementFilename(pathName, u"diffuse"_j, xmlDiffuseTextureFilename);
	}
	if (xmlDisplacementFilename == nullptr && xmlBumpTextureFilename != nullptr) {
		xmlDisplacementFilename = determineDisplacementFilename(pathName, u"normal"_j, xmlBumpTextureFilename);
	}
	if (xmlDisplacementFilename != nullptr) {
		material->setDisplacementTexture(pathName, xmlDisplacementFilename);
	}

	if (authoringTool == DAEReader_AuthoringTool::BLENDER && material->getAmbientColor()->equals(static_cast< Color4Base* >(BLENDER_AMBIENT_NONE))) {
		material->getAmbientColor()->set(material->getDiffuseColor()->getRed() * BLENDER_AMBIENT_FROM_DIFFUSE_SCALE, material->getDiffuseColor()->getGreen() * BLENDER_AMBIENT_FROM_DIFFUSE_SCALE, material->getDiffuseColor()->getBlue() * BLENDER_AMBIENT_FROM_DIFFUSE_SCALE, 1.0f);
		material->getDiffuseColor()->set(material->getDiffuseColor()->getRed() * BLENDER_DIFFUSE_SCALE, material->getDiffuseColor()->getGreen() * BLENDER_DIFFUSE_SCALE, material->getDiffuseColor()->getBlue() * BLENDER_DIFFUSE_SCALE, material->getDiffuseColor()->getAlpha());
	}

	model->getMaterials()->put(material->getId(), material);

	return material;
}

String* DAEReader::determineDisplacementFilename(String* path, String* mapType, String* fileName)
{
	clinit();
	auto tmpFileNameCandidate = fileName->toLowerCase();
	tmpFileNameCandidate = tmpFileNameCandidate->substring(0, tmpFileNameCandidate->lastIndexOf(static_cast< int32_t >(u'.')));
	if (tmpFileNameCandidate->endsWith(mapType))
		tmpFileNameCandidate = tmpFileNameCandidate->substring(0, tmpFileNameCandidate->length() - mapType->length());

	tmpFileNameCandidate = ::java::lang::StringBuilder(tmpFileNameCandidate).append(u"displacement"_j)->toString();
	auto const finalFilenameCandidate = tmpFileNameCandidate;
	try {
		auto fileNameCandidates = _FileSystem::getInstance()->list(path, new DAEReader_determineDisplacementFilename_1(finalFilenameCandidate));
		tmpFileNameCandidate = fileNameCandidates->length > 0 ? (*fileNameCandidates)[0] : static_cast< String* >(nullptr);
	} catch (_Exception& exception) {
		_Console::print(string("DAEReader::determineDisplacementFilename(): An exception occurred: "));
		_Console::println(string(exception.what()));
	}
	return tmpFileNameCandidate;
}

String* DAEReader::makeFileNameRelative(String* fileName)
{
	clinit();
	if (fileName->startsWith(u"/"_j) == true || fileName->matches(u"^[A-Z]\\:\\\\.*$"_j) == true) {
		auto indexSlash = fileName->lastIndexOf(u"/"_j);
		auto indexBackslash = fileName->lastIndexOf(u"\\"_j);
		if (indexSlash != -1 || indexBackslash != -1) {
			if (indexSlash > indexBackslash) {
				fileName = fileName->substring(indexSlash + 1);
			} else {
				fileName = fileName->substring(indexBackslash + 1);
			}
		}
	}
	return fileName;
}

String* DAEReader::getTextureFileNameById(TiXmlElement* xmlRoot, String* xmlTextureId)
{
	clinit();
	String* tmpString = nullptr;
	String* xmlTextureFilename = nullptr;
	auto xmlLibraryImages = getChildrenByTagName(xmlRoot, "library_images").at(0);
	for (auto xmlImage: getChildrenByTagName(xmlLibraryImages, "image")) {
		if ((tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlImage->Attribute("id")))))->equals(xmlTextureId)) {
			xmlTextureFilename = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(getChildrenByTagName(xmlImage, "init_from").at(0)->GetText())));
			if (xmlTextureFilename->startsWith(u"file://"_j)) {
				xmlTextureFilename = xmlTextureFilename->substring(7);
			}
			break;
		}
	}
	return xmlTextureFilename;
}

const vector<TiXmlElement*> DAEReader::getChildrenByTagName(TiXmlElement* parent, const char* name)
{
	clinit();
	vector<TiXmlElement*> elementList;
	for (auto *child = parent->FirstChildElement(name); child != nullptr; child = child->NextSiblingElement(name)) {
		elementList.push_back(child);
	}
	return elementList;
}

const vector<TiXmlElement*> DAEReader::getChildren(TiXmlElement* parent)
{
	clinit();
	vector<TiXmlElement*> elementList;
	for (auto *child = parent->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
		elementList.push_back(child);
	}
	return elementList;
}

/*
String* DAEReader::nodeToString(Node* node)
{
	clinit();
	auto attributes = node->getAttributes();
	auto attributesString = u""_j;
	for (auto i = 0; i < attributes->getLength(); i++) {
		if (i > 0) {
			attributesString = ::java::lang::StringBuilder(attributesString).append(u", "_j)->toString();
		}
		attributesString = ::java::lang::StringBuilder(attributesString).append(attributes->item(i)->getNodeName())->toString();
		attributesString = ::java::lang::StringBuilder(attributesString).append(u"="_j)->toString();
		attributesString = ::java::lang::StringBuilder(attributesString).append(attributes->item(i)->getNodeValue())->toString();
	}
	return ::java::lang::StringBuilder().append(::java::lang::StringBuilder().append(u"["_j)->append(u"name="_j)->toString())->append(node->getNodeName())
		->append(u", attributes=["_j)
		->append(attributesString)
		->append(u"]"_j)
		->append(u"]"_j)->toString();
}
*/

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* DAEReader::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.fileio.models.DAEReader", 35);
    return c;
}

void DAEReader::clinit()
{
	super::clinit();
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
		BLENDER_AMBIENT_NONE = new Color4(0.0f, 0.0f, 0.0f, 1.0f);
		BLENDER_AMBIENT_FROM_DIFFUSE_SCALE = 0.7f;
		BLENDER_DIFFUSE_SCALE = 0.8f;
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

java::lang::Class* DAEReader::getClass0()
{
	return class_();
}

