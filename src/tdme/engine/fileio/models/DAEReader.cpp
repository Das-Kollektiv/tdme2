// Generated from /tdme/src/tdme/engine/fileio/models/DAEReader.java
#include <tdme/engine/fileio/models/DAEReader.h>

#include <java/io/File.h>
#include <java/io/IOException.h>
#include <java/io/Serializable.h>
#include <java/lang/ArrayStoreException.h>
#include <java/lang/CharSequence.h>
#include <java/lang/ClassCastException.h>
#include <java/lang/Comparable.h>
#include <java/lang/Float.h>
#include <java/lang/Integer.h>
#include <java/lang/Math.h>
#include <java/lang/NullPointerException.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/HashSet.h>
#include <java/util/Iterator.h>
#include <java/util/StringTokenizer.h>
#include <javax/xml/parsers/DocumentBuilder.h>
#include <javax/xml/parsers/DocumentBuilderFactory.h>
#include <org/w3c/dom/Document.h>
#include <org/w3c/dom/Element.h>
#include <org/w3c/dom/NamedNodeMap.h>
#include <org/w3c/dom/Node.h>
#include <org/w3c/dom/NodeList.h>
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
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/tools/shared/files/LevelFileExport.h>
#include <tdme/tools/shared/model/LevelEditorEntity_EntityType.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityLibrary.h>
#include <tdme/tools/shared/model/LevelEditorLevel.h>
#include <tdme/tools/shared/model/LevelEditorObject.h>
#include <tdme/tools/shared/model/LevelPropertyPresets.h>
#include <tdme/utils/_ArrayList.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_HashMap.h>
#include <Array.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::engine::fileio::models::DAEReader;
using java::io::File;
using java::io::IOException;
using java::io::Serializable;
using java::lang::ArrayStoreException;
using java::lang::CharSequence;
using java::lang::ClassCastException;
using java::lang::Comparable;
using java::lang::Float;
using java::lang::Integer;
using java::lang::Math;
using java::lang::NullPointerException;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::HashSet;
using java::util::Iterator;
using java::util::StringTokenizer;
using javax::xml::parsers::DocumentBuilder;
using javax::xml::parsers::DocumentBuilderFactory;
using org::w3c::dom::Document;
using org::w3c::dom::Element;
using org::w3c::dom::NamedNodeMap;
using org::w3c::dom::Node;
using org::w3c::dom::NodeList;
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
using tdme::os::_FileSystemInterface;
using tdme::tools::shared::files::LevelFileExport;
using tdme::tools::shared::model::LevelEditorEntity_EntityType;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityLibrary;
using tdme::tools::shared::model::LevelEditorLevel;
using tdme::tools::shared::model::LevelEditorObject;
using tdme::tools::shared::model::LevelPropertyPresets;
using tdme::utils::_ArrayList;
using tdme::utils::_Console;
using tdme::utils::_HashMap;

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
    if (!t) throw new ::java::lang::ClassCastException();
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

Model* DAEReader::read(String* pathName, String* fileName) /* throws(Exception) */
{
	clinit();
	auto builder = DocumentBuilderFactory::newInstance()->newDocumentBuilder();
	auto document = builder->parse(_FileSystem::getInstance()->getInputStream(pathName, fileName));
	auto xmlRoot = document->getDocumentElement();
	auto authoringTool = getAuthoringTool(xmlRoot);
	auto upVector = getUpVector(xmlRoot);
	RotationOrder* rotationOrder = nullptr;
	{
		auto v = upVector;
		if ((v == Model_UpVector::Y_UP)) {
			rotationOrder = RotationOrder::ZYX;
		}
		if ((v == Model_UpVector::Y_UP) || (v == Model_UpVector::Z_UP)) {
			rotationOrder = RotationOrder::YZX;
		}
		end_switch0:;
	}

	auto model = new Model(::java::lang::StringBuilder().append(pathName)->append(File::separator)
		->append(fileName)->toString(), fileName, upVector, rotationOrder, nullptr);
	setupModelImportRotationMatrix(xmlRoot, model);
	setupModelImportScaleMatrix(xmlRoot, model);
	String* xmlSceneId = nullptr;
	auto xmlScene = java_cast< Element* >(getChildrenByTagName(xmlRoot, u"scene"_j)->get(0));
	for (auto _i = getChildrenByTagName(xmlScene, u"instance_visual_scene"_j)->iterator(); _i->hasNext(); ) {
		Element* xmlInstanceVisualscene = java_cast< Element* >(_i->next());
		{
			xmlSceneId = xmlInstanceVisualscene->getAttribute(u"url"_j)->substring(1);
		}
	}
	if (xmlSceneId == nullptr) {
		throw new ModelFileIOException(u"No scene id found"_j);
	}
	auto xmlLibraryVisualScenes = java_cast< Element* >(getChildrenByTagName(xmlRoot, u"library_visual_scenes"_j)->get(0));
	for (auto _i = getChildrenByTagName(xmlLibraryVisualScenes, u"visual_scene"_j)->iterator(); _i->hasNext(); ) {
		Element* xmlLibraryVisualScene = java_cast< Element* >(_i->next());
		{
			auto xmlVisualSceneId = xmlLibraryVisualScene->getAttribute(u"id"_j);
			if (xmlVisualSceneId->equals(xmlSceneId)) {
				auto fps = 30.0f;
				auto xmlExtraNodes = getChildrenByTagName(xmlLibraryVisualScene, u"extra"_j);
				if (xmlExtraNodes->isEmpty() == false) {
					auto xmlExtraNode = java_cast< Element* >(xmlExtraNodes->get(0));
					for (auto _i = getChildrenByTagName(xmlExtraNode, u"technique"_j)->iterator(); _i->hasNext(); ) {
						Element* xmlTechnique = java_cast< Element* >(_i->next());
						{
							auto xmlFrameRateNodes = getChildrenByTagName(xmlTechnique, u"frame_rate"_j);
							if (xmlFrameRateNodes->isEmpty() == false) {
								fps = Float::parseFloat(java_cast< Element* >(xmlFrameRateNodes->get(0))->getTextContent());
								break;
							}
						}
					}
				}
				model->setFPS(fps);
				for (auto _i = getChildrenByTagName(xmlLibraryVisualScene, u"node"_j)->iterator(); _i->hasNext(); ) {
					Element* xmlNode = java_cast< Element* >(_i->next());
					{
						auto group = readVisualSceneNode(authoringTool, pathName, model, nullptr, xmlRoot, xmlNode, fps);
						if (group != nullptr) {
							model->getSubGroups()->put(group->getId(), group);
							model->getGroups()->put(group->getId(), group);
						}
					}
				}
			}
		}
	}
	ModelHelper::setupJoints(model);
	ModelHelper::fixAnimationLength(model);
	ModelHelper::prepareForIndexedRendering(model);
	return model;
}

LevelEditorLevel* DAEReader::readLevel(String* pathName, String* fileName) /* throws(Exception) */
{
	clinit();
	auto tmFilesFolder = new File(::java::lang::StringBuilder().append(pathName)->append(u"/"_j)
		->append(fileName)
		->append(u"-models"_j)->toString());
	if (tmFilesFolder->exists()) {
		tmFilesFolder->delete_();
	}
	tmFilesFolder->mkdir();
	auto levelEditorLevel = new LevelEditorLevel();
	LevelPropertyPresets::getInstance()->setDefaultLevelProperties(levelEditorLevel);
	auto builder = DocumentBuilderFactory::newInstance()->newDocumentBuilder();
	auto document = builder->parse(_FileSystem::getInstance()->getInputStream(pathName, fileName));
	auto xmlRoot = document->getDocumentElement();
	auto authoringTool = getAuthoringTool(xmlRoot);
	auto upVector = getUpVector(xmlRoot);
	RotationOrder* rotationOrder = nullptr;
	{
		auto v = upVector;
		if ((v == Model_UpVector::Y_UP)) {
			rotationOrder = RotationOrder::ZYX;
		}
		if ((v == Model_UpVector::Y_UP) || (v == Model_UpVector::Z_UP)) {
			rotationOrder = RotationOrder::YZX;
		}
end_switch1:;
	}

	levelEditorLevel->setRotationOrder(rotationOrder);
	String* xmlSceneId = nullptr;
	auto xmlScene = java_cast< Element* >(getChildrenByTagName(xmlRoot, u"scene"_j)->get(0));
	for (auto _i = getChildrenByTagName(xmlScene, u"instance_visual_scene"_j)->iterator(); _i->hasNext(); ) {
		Element* xmlInstanceVisualscene = java_cast< Element* >(_i->next());
		{
			xmlSceneId = xmlInstanceVisualscene->getAttribute(u"url"_j)->substring(1);
		}
	}
	if (xmlSceneId == nullptr) {
		throw new ModelFileIOException(u"No scene id found"_j);
	}
	auto xmlLibraryVisualScenes = java_cast< Element* >(getChildrenByTagName(xmlRoot, u"library_visual_scenes"_j)->get(0));
	for (auto _i = getChildrenByTagName(xmlLibraryVisualScenes, u"visual_scene"_j)->iterator(); _i->hasNext(); ) {
		Element* xmlLibraryVisualScene = java_cast< Element* >(_i->next());
		{
			auto xmlVisualSceneId = xmlLibraryVisualScene->getAttribute(u"id"_j);
			if (xmlVisualSceneId->equals(xmlSceneId)) {
				auto fps = 30.0f;
				auto xmlExtraNodes = getChildrenByTagName(xmlLibraryVisualScene, u"extra"_j);
				if (xmlExtraNodes->isEmpty() == false) {
					auto xmlExtraNode = java_cast< Element* >(xmlExtraNodes->get(0));
					for (auto _i = getChildrenByTagName(xmlExtraNode, u"technique"_j)->iterator(); _i->hasNext(); ) {
						Element* xmlTechnique = java_cast< Element* >(_i->next());
						{
							auto xmlFrameRateNodes = getChildrenByTagName(xmlTechnique, u"frame_rate"_j);
							if (xmlFrameRateNodes->isEmpty() == false) {
								fps = Float::parseFloat(java_cast< Element* >(xmlFrameRateNodes->get(0))->getTextContent());
								break;
							}
						}
					}
				}
				auto entityLibrary = levelEditorLevel->getEntityLibrary();
				LevelEditorEntity* emptyEntity = nullptr;
				auto nodeIdx = 0;
				for (auto _i = getChildrenByTagName(xmlLibraryVisualScene, u"node"_j)->iterator(); _i->hasNext(); ) {
					Element* xmlNode = java_cast< Element* >(_i->next());
					{
						auto modelName = xmlNode->getAttribute(u"id"_j);
						modelName = modelName->replaceAll(u"[\\-\\_]{1}+[0-9]+$"_j, u""_j);
						modelName = modelName->replaceAll(u"[0-9]+$"_j, u""_j);
						auto haveName = entityLibrary->getEntityCount() == 0;
						if (haveName == false) {
							for (auto i = 0; i < 10000; i++) {
								haveName = true;
								auto modelNameTry = ::java::lang::StringBuilder().append(modelName)->append((i == 0 ? u""_j : String::valueOf(i)))->toString();
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
							_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"DAEReader::readLevel(): Skipping model '"_j)->append(modelName)
								->append(u"' as no name could be created for it."_j)->toString()));
							continue;
						}
						auto model = new Model(::java::lang::StringBuilder().append(pathName)->append(File::separator)
							->append(fileName)
							->append(u'-')
							->append(modelName)->toString(), ::java::lang::StringBuilder().append(fileName)->append(u'-')
							->append(modelName)->toString(), upVector, rotationOrder, nullptr);
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
						auto xmlMatrixElements = getChildrenByTagName(xmlNode, u"matrix"_j);
						if (xmlMatrixElements->size() == 1) {
							auto xmlMatrix = java_cast< Element* >(xmlMatrixElements->get(0))->getTextContent();
							auto t = new StringTokenizer(xmlMatrix, u" \n\r"_j);
							nodeTransformationsMatrix = (new Matrix4x4(Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken())))->transpose();
						}
						if (nodeTransformationsMatrix == nullptr) {
							throw new ModelFileIOException(::java::lang::StringBuilder().append(u"missing node transformations matrix for node "_j)->append(xmlNode->getAttribute(u"id"_j))->toString());
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
								TMWriter::write(model, ::java::lang::StringBuilder().append(pathName)->append(u"/"_j)
									->append(fileName)
									->append(u"-models"_j)->toString(), ::java::lang::StringBuilder().append(modelName)->append(u".tm"_j)->toString());
								levelEditorEntity = entityLibrary->addModel(nodeIdx++, modelName, modelName, ::java::lang::StringBuilder().append(pathName)->append(u"/"_j)
									->append(fileName)
									->append(u"-models"_j)->toString(), ::java::lang::StringBuilder().append(modelName)->append(u".tm"_j)->toString(), new Vector3());
							}
						} else if (entityType == LevelEditorEntity_EntityType::EMPTY) {
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
						auto object = new LevelEditorObject(xmlNode->getAttribute(u"id"_j), xmlNode->getAttribute(u"id"_j), levelEditorObjectTransformations, levelEditorEntity);
						levelEditorLevel->addObject(object);
					}
				}
			}
		}
	}
	LevelFileExport::export_(::java::lang::StringBuilder().append(pathName)->append(u"/"_j)
		->append(fileName)
		->append(u".tl"_j)->toString(), levelEditorLevel);
	return levelEditorLevel;
}

DAEReader_AuthoringTool* DAEReader::getAuthoringTool(Element* xmlRoot)
{
	clinit();
	for (auto _i = getChildrenByTagName(xmlRoot, u"asset"_j)->iterator(); _i->hasNext(); ) {
		Element* xmlAsset = java_cast< Element* >(_i->next());
		{
			for (auto _i = getChildrenByTagName(xmlAsset, u"contributor"_j)->iterator(); _i->hasNext(); ) {
				Element* xmlContributer = java_cast< Element* >(_i->next());
				{
					for (auto _i = getChildrenByTagName(xmlContributer, u"authoring_tool"_j)->iterator(); _i->hasNext(); ) {
						Element* xmlAuthoringTool = java_cast< Element* >(_i->next());
						{
							if (xmlAuthoringTool->getTextContent()->indexOf(u"Blender"_j) != -1) {
								return DAEReader_AuthoringTool::BLENDER;
							}
						}
					}
				}
			}
		}
	}
	return DAEReader_AuthoringTool::UNKNOWN;
}

Model_UpVector* DAEReader::getUpVector(Element* xmlRoot) /* throws(ModelFileIOException) */
{
	clinit();
	for (auto _i = getChildrenByTagName(xmlRoot, u"asset"_j)->iterator(); _i->hasNext(); ) {
		Element* xmlAsset = java_cast< Element* >(_i->next());
		{
			for (auto _i = getChildrenByTagName(xmlAsset, u"up_axis"_j)->iterator(); _i->hasNext(); ) {
				Element* xmlAssetUpAxis = java_cast< Element* >(_i->next());
				{
					auto upAxis = xmlAssetUpAxis->getTextContent();
					if (upAxis->equalsIgnoreCase(u"Y_UP"_j)) {
						return Model_UpVector::Y_UP;
					} else if (upAxis->equalsIgnoreCase(u"Z_UP"_j)) {
						return Model_UpVector::Z_UP;
					} else if (upAxis->equalsIgnoreCase(u"X_UP"_j)) {
						throw new ModelFileIOException(u"X-Up is not supported"_j);
					} else {
						throw new ModelFileIOException(u"Unknown Up vector"_j);
					}
				}
			}
		}
	}
	throw new ModelFileIOException(u"Unknown Up vector"_j);
}

void DAEReader::setupModelImportRotationMatrix(Element* xmlRoot, Model* model)
{
	clinit();
	for (auto _i = getChildrenByTagName(xmlRoot, u"asset"_j)->iterator(); _i->hasNext(); ) {
		Element* xmlAsset = java_cast< Element* >(_i->next());
		{
			for (auto _i = getChildrenByTagName(xmlAsset, u"up_axis"_j)->iterator(); _i->hasNext(); ) {
				Element* xmlAssetUpAxis = java_cast< Element* >(_i->next());
				{
					auto upAxis = xmlAssetUpAxis->getTextContent();
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
	}
}

void DAEReader::setupModelImportScaleMatrix(Element* xmlRoot, Model* model)
{
	clinit();
	for (auto _i = getChildrenByTagName(xmlRoot, u"asset"_j)->iterator(); _i->hasNext(); ) {
		Element* xmlAsset = java_cast< Element* >(_i->next());
		{
			for (auto _i = getChildrenByTagName(xmlAsset, u"unit"_j)->iterator(); _i->hasNext(); ) {
				Element* xmlAssetUnit = java_cast< Element* >(_i->next());
				{
					String* tmp = nullptr;
					if ((tmp = xmlAssetUnit->getAttribute(u"meter"_j)) != nullptr) {
						model->getImportTransformationsMatrix()->scale(Float::parseFloat(tmp));
					}
				}
			}
		}
	}
}

Group* DAEReader::readVisualSceneNode(DAEReader_AuthoringTool* authoringTool, String* pathName, Model* model, Group* parentGroup, Element* xmlRoot, Element* xmlNode, float fps) /* throws(Exception) */
{
	clinit();
	auto xmlInstanceControllers = getChildrenByTagName(xmlNode, u"instance_controller"_j);
	if (xmlInstanceControllers->isEmpty() == false) {
		return readVisualSceneInstanceController(authoringTool, pathName, model, parentGroup, xmlRoot, xmlNode);
	} else {
		return readNode(authoringTool, pathName, model, parentGroup, xmlRoot, xmlNode, fps);
	}
}

Group* DAEReader::readNode(DAEReader_AuthoringTool* authoringTool, String* pathName, Model* model, Group* parentGroup, Element* xmlRoot, Element* xmlNode, float fps) /* throws(Exception) */
{
	clinit();
	auto xmlNodeId = xmlNode->getAttribute(u"id"_j);
	auto xmlNodeName = xmlNode->getAttribute(u"name"_j);
	if (xmlNodeId->length() == 0)
		xmlNodeId = xmlNodeName;

	StringTokenizer* t = nullptr;
	Matrix4x4* transformationsMatrix = nullptr;
	auto xmlMatrixElements = getChildrenByTagName(xmlNode, u"matrix"_j);
	if (xmlMatrixElements->size() == 1) {
		auto xmlMatrix = java_cast< Element* >(getChildrenByTagName(xmlNode, u"matrix"_j)->get(0))->getTextContent();
		t = new StringTokenizer(xmlMatrix, u" \n\r"_j);
		transformationsMatrix = (new Matrix4x4(Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken())))->transpose();
	}
	auto group = new Group(model, parentGroup, xmlNodeId, xmlNodeName);
	if (transformationsMatrix != nullptr) {
		group->getTransformationsMatrix()->multiply(transformationsMatrix);
	}
	auto xmlAnimationsLibrary = getChildrenByTagName(xmlRoot, u"library_animations"_j);
	if (xmlAnimationsLibrary->isEmpty() == false) {
		auto xmlAnimations = getChildrenByTagName(java_cast< Element* >(xmlAnimationsLibrary->get(0)), u"animation"_j);
		for (auto _i = xmlAnimations->iterator(); _i->hasNext(); ) {
			Element* xmlAnimation = java_cast< Element* >(_i->next());
			{
				auto _xmlAnimation = getChildrenByTagName(xmlAnimation, u"animation"_j);
				if (_xmlAnimation->isEmpty() == false) {
					xmlAnimation = java_cast< Element* >(_xmlAnimation->get(0));
				}
				String* xmlSamplerSource = nullptr;
				auto xmlChannel = java_cast< Element* >(getChildrenByTagName(xmlAnimation, u"channel"_j)->get(0));
				if (xmlChannel->getAttribute(u"target"_j)->startsWith(::java::lang::StringBuilder().append(xmlNodeId)->append(u"/"_j)->toString())) {
					xmlSamplerSource = xmlChannel->getAttribute(u"source"_j)->substring(1);
				}
				if (xmlSamplerSource == nullptr) {
					continue;
				}
				String* xmlSamplerOutputSource = nullptr;
				String* xmlSamplerInputSource = nullptr;
				auto xmlSampler = java_cast< Element* >(getChildrenByTagName(xmlAnimation, u"sampler"_j)->get(0));
				for (auto _i = getChildrenByTagName(xmlSampler, u"input"_j)->iterator(); _i->hasNext(); ) {
					Element* xmlSamplerInput = java_cast< Element* >(_i->next());
					{
						if (xmlSamplerInput->getAttribute(u"semantic"_j)->equals(u"OUTPUT"_j)) {
							xmlSamplerOutputSource = xmlSamplerInput->getAttribute(u"source"_j)->substring(1);
						} else if (xmlSamplerInput->getAttribute(u"semantic"_j)->equals(u"INPUT"_j)) {
							xmlSamplerInputSource = xmlSamplerInput->getAttribute(u"source"_j)->substring(1);
						}
					}
				}
				if (xmlSamplerOutputSource == nullptr) {
					throw new ModelFileIOException(::java::lang::StringBuilder().append(u"Could not find xml sampler output source for animation for "_j)->append(xmlNodeId)->toString());
				}
				floatArray* keyFrameTimes = nullptr;
				for (auto _i = getChildrenByTagName(xmlAnimation, u"source"_j)->iterator(); _i->hasNext(); ) {
					Element* xmlAnimationSource = java_cast< Element* >(_i->next());
					{
						if (xmlAnimationSource->getAttribute(u"id"_j)->equals(xmlSamplerInputSource)) {
							auto xmlFloatArray = java_cast< Element* >(getChildrenByTagName(xmlAnimationSource, u"float_array"_j)->get(0));
							auto frames = Integer::parseInt(xmlFloatArray->getAttribute(u"count"_j));
							auto valueString = xmlFloatArray->getTextContent();
							auto keyFrameIdx = 0;
							keyFrameTimes = new floatArray(frames);
							t = new StringTokenizer(valueString, u" \n\r"_j);
							while (t->hasMoreTokens()) {
								(*keyFrameTimes)[keyFrameIdx++] = Float::parseFloat(t->nextToken());
							}
						}
					}
				}
				Matrix4x4Array* keyFrameMatrices = nullptr;
				for (auto _i = getChildrenByTagName(xmlAnimation, u"source"_j)->iterator(); _i->hasNext(); ) {
					Element* xmlAnimationSource = java_cast< Element* >(_i->next());
					{
						if (xmlAnimationSource->getAttribute(u"id"_j)->equals(xmlSamplerOutputSource)) {
							auto xmlFloatArray = java_cast< Element* >(getChildrenByTagName(xmlAnimationSource, u"float_array"_j)->get(0));
							auto keyFrames = Integer::parseInt(xmlFloatArray->getAttribute(u"count"_j)) / 16;
							if (keyFrames > 0) {
								auto valueString = xmlFloatArray->getTextContent();
								t = new StringTokenizer(valueString, u" \n\r"_j);
								auto keyFrameIdx = 0;
								keyFrameMatrices = new Matrix4x4Array(keyFrames);
								while (t->hasMoreTokens()) {
									keyFrameMatrices->set(keyFrameIdx, (new Matrix4x4(Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken())))->transpose());
									keyFrameIdx++;
								}
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
	}
	for (auto _i = getChildrenByTagName(xmlNode, u"node"_j)->iterator(); _i->hasNext(); ) {
		Element* _xmlNode = java_cast< Element* >(_i->next());
		{
			auto _group = readVisualSceneNode(authoringTool, pathName, model, group, xmlRoot, _xmlNode, fps);
			if (_group != nullptr) {
				group->getSubGroups()->put(_group->getId(), _group);
				model->getGroups()->put(_group->getId(), _group);
			}
		}
	}
	String* xmlInstanceGeometryId = nullptr;
	auto xmlInstanceGeometryElements = getChildrenByTagName(xmlNode, u"instance_geometry"_j);
	if (xmlInstanceGeometryElements->isEmpty() == false) {
		auto xmlInstanceGeometryElement = java_cast< Element* >(xmlInstanceGeometryElements->get(0));
		xmlInstanceGeometryId = xmlInstanceGeometryElement->getAttribute(u"url"_j)->substring(1);
		auto materialSymbols = new _HashMap();
		for (auto _i = getChildrenByTagName(xmlInstanceGeometryElement, u"bind_material"_j)->iterator(); _i->hasNext(); ) {
			Element* xmlBindMaterial = java_cast< Element* >(_i->next());
			
								for (auto _i = getChildrenByTagName(xmlBindMaterial, u"technique_common"_j)->iterator(); _i->hasNext(); ) {
					Element* xmlTechniqueCommon = java_cast< Element* >(_i->next());
					
												for (auto _i = getChildrenByTagName(xmlTechniqueCommon, u"instance_material"_j)->iterator(); _i->hasNext(); ) {
							Element* xmlInstanceMaterial = java_cast< Element* >(_i->next());
							{
								materialSymbols->put(xmlInstanceMaterial->getAttribute(u"symbol"_j), xmlInstanceMaterial->getAttribute(u"target"_j));
							}
						}

				}

		}
		readGeometry(authoringTool, pathName, model, group, xmlRoot, xmlInstanceGeometryId, materialSymbols);
		return group;
	}
	String* xmlInstanceNodeId = nullptr;
	for (auto _i = getChildrenByTagName(xmlNode, u"instance_node"_j)->iterator(); _i->hasNext(); ) {
		Element* xmlInstanceNodeElement = java_cast< Element* >(_i->next());
		{
			xmlInstanceNodeId = xmlInstanceNodeElement->getAttribute(u"url"_j)->substring(1);
		}
	}
	if (xmlInstanceNodeId != nullptr) {
		for (auto _i = getChildrenByTagName(xmlRoot, u"library_nodes"_j)->iterator(); _i->hasNext(); ) {
			Element* xmlLibraryNodes = java_cast< Element* >(_i->next());
			
								for (auto _i = getChildrenByTagName(xmlLibraryNodes, u"node"_j)->iterator(); _i->hasNext(); ) {
					Element* xmlLibraryNode = java_cast< Element* >(_i->next());
					
												if (xmlLibraryNode->getAttribute(u"id"_j)->equals(xmlInstanceNodeId)) {
							for (auto _i = getChildrenByTagName(xmlLibraryNode, u"node"_j)->iterator(); _i->hasNext(); ) {
								Element* _xmlNode = java_cast< Element* >(_i->next());
								{
									auto _group = readVisualSceneNode(authoringTool, pathName, model, parentGroup, xmlRoot, _xmlNode, fps);
									if (_group != nullptr) {
										group->getSubGroups()->put(_group->getId(), _group);
										model->getGroups()->put(_group->getId(), _group);
									}
								}
							}
							for (auto _i = getChildrenByTagName(xmlLibraryNode, u"instance_geometry"_j)->iterator(); _i->hasNext(); ) {
								Element* xmlInstanceGeometry = java_cast< Element* >(_i->next());
								{
									auto xmlGeometryId = xmlInstanceGeometry->getAttribute(u"url"_j)->substring(1);
									auto materialSymbols = new _HashMap();
									for (auto _i = getChildrenByTagName(xmlInstanceGeometry, u"bind_material"_j)->iterator(); _i->hasNext(); ) {
										Element* xmlBindMaterial = java_cast< Element* >(_i->next());
										
																						for (auto _i = getChildrenByTagName(xmlBindMaterial, u"technique_common"_j)->iterator(); _i->hasNext(); ) {
												Element* xmlTechniqueCommon = java_cast< Element* >(_i->next());
												
																										for (auto _i = getChildrenByTagName(xmlTechniqueCommon, u"instance_material"_j)->iterator(); _i->hasNext(); ) {
														Element* xmlInstanceMaterial = java_cast< Element* >(_i->next());
														{
															materialSymbols->put(xmlInstanceMaterial->getAttribute(u"symbol"_j), xmlInstanceMaterial->getAttribute(u"target"_j));
														}
													}

											}

									}
									readGeometry(authoringTool, pathName, model, group, xmlRoot, xmlGeometryId, materialSymbols);
								}
							}
						}

				}

		}
	}
	return group;
}

Group* DAEReader::readVisualSceneInstanceController(DAEReader_AuthoringTool* authoringTool, String* pathName, Model* model, Group* parentGroup, Element* xmlRoot, Element* xmlNode) /* throws(Exception) */
{
	clinit();
	StringTokenizer* t;
	auto xmlNodeId = xmlNode->getAttribute(u"id"_j);
	auto xmlNodeName = xmlNode->getAttribute(u"name"_j);
	auto materialSymbols = new _HashMap();
	String* xmlGeometryId = nullptr;
	auto xmlInstanceControllers = getChildrenByTagName(xmlNode, u"instance_controller"_j);
	Element* xmlSkin = nullptr;
	auto xmlInstanceController = java_cast< Element* >(xmlInstanceControllers->get(0));
	for (auto _i = getChildrenByTagName(xmlInstanceController, u"bind_material"_j)->iterator(); _i->hasNext(); ) {
		Element* xmlBindMaterial = java_cast< Element* >(_i->next());
		
						for (auto _i = getChildrenByTagName(xmlBindMaterial, u"technique_common"_j)->iterator(); _i->hasNext(); ) {
				Element* xmlTechniqueCommon = java_cast< Element* >(_i->next());
				
										for (auto _i = getChildrenByTagName(xmlTechniqueCommon, u"instance_material"_j)->iterator(); _i->hasNext(); ) {
						Element* xmlInstanceMaterial = java_cast< Element* >(_i->next());
						{
							materialSymbols->put(xmlInstanceMaterial->getAttribute(u"symbol"_j), xmlInstanceMaterial->getAttribute(u"target"_j));
						}
					}

			}

	}
	auto xmlInstanceControllerId = xmlInstanceController->getAttribute(u"url"_j)->substring(1);
	auto xmlLibraryControllers = java_cast< Element* >(getChildrenByTagName(xmlRoot, u"library_controllers"_j)->get(0));
	for (auto _i = getChildrenByTagName(xmlLibraryControllers, u"controller"_j)->iterator(); _i->hasNext(); ) {
		Element* xmlLibraryController = java_cast< Element* >(_i->next());
		{
			if (xmlLibraryController->getAttribute(u"id"_j)->equals(xmlInstanceControllerId)) {
				auto xmlSkins = getChildrenByTagName(xmlLibraryController, u"skin"_j);
				if (xmlSkins->isEmpty() == false) {
					xmlSkin = java_cast< Element* >(xmlSkins->get(0));
				}
			}
		}
	}
	if (xmlSkin == nullptr) {
		throw new ModelFileIOException(::java::lang::StringBuilder().append(u"skin not found for instance controller "_j)->append(xmlNodeId)->toString());
	}
	xmlGeometryId = xmlSkin->getAttribute(u"source"_j)->substring(1);
	auto xmlMatrix = java_cast< Element* >(getChildrenByTagName(xmlSkin, u"bind_shape_matrix"_j)->get(0))->getTextContent();
	t = new StringTokenizer(xmlMatrix, u" \n\r"_j);
	auto bindShapeMatrix = (new Matrix4x4(Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken())))->transpose();
	auto group = new Group(model, parentGroup, xmlNodeId, xmlNodeName);
	auto skinning = group->createSkinning();
	readGeometry(authoringTool, pathName, model, group, xmlRoot, xmlGeometryId, materialSymbols);
	String* xmlJointsSource = nullptr;
	String* xmlJointsInverseBindMatricesSource = nullptr;
	auto xmlJoints = java_cast< Element* >(getChildrenByTagName(xmlSkin, u"joints"_j)->get(0));
	for (auto _i = getChildrenByTagName(xmlJoints, u"input"_j)->iterator(); _i->hasNext(); ) {
		Element* xmlJointsInput = java_cast< Element* >(_i->next());
		{
			if (xmlJointsInput->getAttribute(u"semantic"_j)->equals(u"JOINT"_j)) {
				xmlJointsSource = xmlJointsInput->getAttribute(u"source"_j)->substring(1);
			} else if (xmlJointsInput->getAttribute(u"semantic"_j)->equals(u"INV_BIND_MATRIX"_j)) {
				xmlJointsInverseBindMatricesSource = xmlJointsInput->getAttribute(u"source"_j)->substring(1);
			}
		}
	}
	if (xmlJointsSource == nullptr) {
		throw new ModelFileIOException(::java::lang::StringBuilder().append(u"joint source not found for instance controller "_j)->append(xmlNodeId)->toString());
	}
	auto joints = new _ArrayList();
	for (auto _i = getChildrenByTagName(xmlSkin, u"source"_j)->iterator(); _i->hasNext(); ) {
		Element* xmlSkinSource = java_cast< Element* >(_i->next());
		{
			if (xmlSkinSource->getAttribute(u"id"_j)->equals(xmlJointsSource)) {
				t = new StringTokenizer(java_cast< Element* >(getChildrenByTagName(xmlSkinSource, u"Name_array"_j)->get(0))->getTextContent(), u" \n\r"_j);
				while (t->hasMoreTokens()) {
					joints->add(new Joint(t->nextToken()));
				}
			}
		}
	}
	skinning->setJoints(joints);
	if (xmlJointsInverseBindMatricesSource == nullptr) {
		throw new ModelFileIOException(::java::lang::StringBuilder().append(u"inverse bind matrices source not found for instance controller "_j)->append(xmlNodeId)->toString());
	}
	for (auto _i = getChildrenByTagName(xmlSkin, u"source"_j)->iterator(); _i->hasNext(); ) {
		Element* xmlSkinSource = java_cast< Element* >(_i->next());
		{
			if (xmlSkinSource->getAttribute(u"id"_j)->equals(xmlJointsInverseBindMatricesSource)) {
				t = new StringTokenizer(java_cast< Element* >(getChildrenByTagName(xmlSkinSource, u"float_array"_j)->get(0))->getTextContent(), u" \n\r"_j);
				auto _joints = skinning->getJoints();
				for (auto i = 0; i < _joints->length; i++) {
					(*_joints)[i]->getBindMatrix()->multiply(bindShapeMatrix);
					(*_joints)[i]->getBindMatrix()->multiply((new Matrix4x4(Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken())))->transpose());
				}
			}
		}
	}
	auto weights = new _ArrayList();
	auto xmlJointOffset = -1;
	auto xmlWeightOffset = -1;
	String* xmlWeightsSource = nullptr;
	auto xmlVertexWeights = java_cast< Element* >(getChildrenByTagName(xmlSkin, u"vertex_weights"_j)->get(0));
	auto xmlVertexWeightInputs = getChildrenByTagName(xmlVertexWeights, u"input"_j);
	for (auto _i = xmlVertexWeightInputs->iterator(); _i->hasNext(); ) {
		Element* xmlVertexWeightInput = java_cast< Element* >(_i->next());
		{
			if (xmlVertexWeightInput->getAttribute(u"semantic"_j)->equals(u"JOINT"_j)) {
				if (xmlVertexWeightInput->getAttribute(u"source"_j)->substring(1)->equals(xmlJointsSource) == false) {
					throw new ModelFileIOException(u"joint inverse bind matrices source do not match"_j);
				}
				xmlJointOffset = Integer::parseInt(xmlVertexWeightInput->getAttribute(u"offset"_j));
			} else if (xmlVertexWeightInput->getAttribute(u"semantic"_j)->equals(u"WEIGHT"_j)) {
				xmlWeightOffset = Integer::parseInt(xmlVertexWeightInput->getAttribute(u"offset"_j));
				xmlWeightsSource = xmlVertexWeightInput->getAttribute(u"source"_j)->substring(1);
			}
		}
	}
	if (xmlJointOffset == -1) {
		throw new ModelFileIOException(::java::lang::StringBuilder().append(u"xml vertex weight joint offset missing for node "_j)->append(xmlNodeId)->toString());
	}
	if (xmlWeightOffset == -1) {
		throw new ModelFileIOException(::java::lang::StringBuilder().append(u"xml vertex weight weight offset missing for node "_j)->append(xmlNodeId)->toString());
	}
	if (xmlWeightsSource == nullptr) {
		throw new ModelFileIOException(::java::lang::StringBuilder().append(u"xml vertex weight weight source missing for node "_j)->append(xmlNodeId)->toString());
	}
	for (auto _i = getChildrenByTagName(xmlSkin, u"source"_j)->iterator(); _i->hasNext(); ) {
		Element* xmlSkinSource = java_cast< Element* >(_i->next());
		{
			if (xmlSkinSource->getAttribute(u"id"_j)->equals(xmlWeightsSource)) {
				t = new StringTokenizer(java_cast< Element* >(getChildrenByTagName(xmlSkinSource, u"float_array"_j)->get(0))->getTextContent(), u" \n\r"_j);
				while (t->hasMoreTokens()) {
					weights->add(new Float(Float::parseFloat(t->nextToken())));
				}
			}
		}
	}
	skinning->setWeights(weights);
	auto xmlVertexWeightInputCount = xmlVertexWeightInputs->size();
	auto vertexJointsInfluenceCountString = java_cast< Element* >(getChildrenByTagName(xmlVertexWeights, u"vcount"_j)->get(0))->getTextContent();
	auto vertexJointsInfluencesString = java_cast< Element* >(getChildrenByTagName(xmlVertexWeights, u"v"_j)->get(0))->getTextContent();
	t = new StringTokenizer(vertexJointsInfluenceCountString, u" \n\r"_j);
	auto t2 = new StringTokenizer(vertexJointsInfluencesString, u" \n\r"_j);
	auto offset = 0;
	auto verticesJointsWeights = new _ArrayList();
	while (t->hasMoreTokens()) {
		auto vertexJointsInfluencesCount = Integer::parseInt(t->nextToken());
		auto vertexJointsWeights = new _ArrayList();
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
			vertexJointsWeights->add(new JointWeight(vertexJoint, vertexWeight));
		}
		verticesJointsWeights->add(vertexJointsWeights);
	}
	skinning->setVerticesJointsWeights(verticesJointsWeights);
	return group;
}

void DAEReader::readGeometry(DAEReader_AuthoringTool* authoringTool, String* pathName, Model* model, Group* group, Element* xmlRoot, String* xmlNodeId, _HashMap* materialSymbols) /* throws(Exception) */
{
	clinit();
	StringTokenizer* t;
	FacesEntity* facesEntity = nullptr;
	auto facesEntities = new _ArrayList(group->getFacesEntities());
	auto verticesOffset = group->getVertices()->length;
	auto vertices = new _ArrayList(group->getVertices());
	auto normalsOffset = group->getNormals()->length;
	auto normals = new _ArrayList(group->getNormals());
	auto textureCoordinatesOffset = group->getTextureCoordinates() != nullptr ? group->getTextureCoordinates()->length : 0;
	auto textureCoordinates = group->getTextureCoordinates() != nullptr ? new _ArrayList(group->getTextureCoordinates()) : new _ArrayList();
	auto xmlLibraryGeometries = java_cast< Element* >(getChildrenByTagName(xmlRoot, u"library_geometries"_j)->get(0));
	for (auto _i = getChildrenByTagName(xmlLibraryGeometries, u"geometry"_j)->iterator(); _i->hasNext(); ) {
		Element* xmlGeometry = java_cast< Element* >(_i->next());
		{
			if (xmlGeometry->getAttribute(u"id"_j)->equals(xmlNodeId)) {
				auto xmlMesh = java_cast< Element* >(getChildrenByTagName(xmlGeometry, u"mesh"_j)->get(0));
				auto xmlPolygonsList = new _ArrayList();
				for (auto _i = getChildrenByTagName(xmlMesh, u"triangles"_j)->iterator(); _i->hasNext(); ) {
					Element* xmlTriangesElement = java_cast< Element* >(_i->next());
					{
						xmlPolygonsList->add(xmlTriangesElement);
					}
				}
				for (auto _i = getChildrenByTagName(xmlMesh, u"polylist"_j)->iterator(); _i->hasNext(); ) {
					Element* xmlPolyListElement = java_cast< Element* >(_i->next());
					{
						xmlPolygonsList->add(xmlPolyListElement);
					}
				}
				for (auto _i = getChildrenByTagName(xmlMesh, u"polygons"_j)->iterator(); _i->hasNext(); ) {
					Element* xmlPolygonsElement = java_cast< Element* >(_i->next());
					{
						xmlPolygonsList->add(xmlPolygonsElement);
					}
				}
				for (auto _i = xmlPolygonsList->iterator(); _i->hasNext(); ) {
					Element* xmlPolygons = java_cast< Element* >(_i->next());
					{
						auto faces = new _ArrayList();
						facesEntity = new FacesEntity(group, xmlNodeId);
						if (xmlPolygons->getNodeName()->toLowerCase()->equals(u"polylist"_j)) {
							t = new StringTokenizer(java_cast< Element* >(getChildrenByTagName(xmlPolygons, u"vcount"_j)->get(0))->getTextContent());
							while (t->hasMoreTokens()) {
								auto vertexCount = Integer::parseInt(t->nextToken());
								if (vertexCount != 3) {
									throw new ModelFileIOException(::java::lang::StringBuilder().append(u"we only support triangles in "_j)->append(xmlNodeId)->toString());
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
						auto xmlMaterialId = xmlPolygons->getAttribute(u"material"_j);
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
						auto xmlInputSet = new HashSet();
						for (auto _i = getChildrenByTagName(xmlPolygons, u"input"_j)->iterator(); _i->hasNext(); ) {
							Element* xmlTrianglesInput = java_cast< Element* >(_i->next());
							{
								if (xmlTrianglesInput->getAttribute(u"semantic"_j)->equals(u"VERTEX"_j)) {
									xmlVerticesOffset = Integer::parseInt(xmlTrianglesInput->getAttribute(u"offset"_j));
									xmlVerticesSource = xmlTrianglesInput->getAttribute(u"source"_j)->substring(1);
									xmlInputSet->add(Integer::valueOf(xmlVerticesOffset));
								} else if (xmlTrianglesInput->getAttribute(u"semantic"_j)->equals(u"NORMAL"_j)) {
									xmlNormalsOffset = Integer::parseInt(xmlTrianglesInput->getAttribute(u"offset"_j));
									xmlNormalsSource = xmlTrianglesInput->getAttribute(u"source"_j)->substring(1);
									xmlInputSet->add(Integer::valueOf(xmlNormalsOffset));
								}
								if (xmlTrianglesInput->getAttribute(u"semantic"_j)->equals(u"TEXCOORD"_j)) {
									xmlTexCoordOffset = Integer::parseInt(xmlTrianglesInput->getAttribute(u"offset"_j));
									xmlTexCoordSource = xmlTrianglesInput->getAttribute(u"source"_j)->substring(1);
									xmlInputSet->add(Integer::valueOf(xmlTexCoordOffset));
								}
								if (xmlTrianglesInput->getAttribute(u"semantic"_j)->equals(u"COLOR"_j)) {
									xmlColorOffset = Integer::parseInt(xmlTrianglesInput->getAttribute(u"offset"_j));
									xmlColorSource = xmlTrianglesInput->getAttribute(u"source"_j)->substring(1);
									xmlInputSet->add(Integer::valueOf(xmlColorOffset));
								}
							}
						}
						xmlInputs = xmlInputSet->size();
						for (auto _i = getChildrenByTagName(xmlMesh, u"vertices"_j)->iterator(); _i->hasNext(); ) {
							Element* xmlVertices = java_cast< Element* >(_i->next());
							{
								if (xmlVertices->getAttribute(u"id"_j)->equals(xmlVerticesSource)) {
									for (auto _i = getChildrenByTagName(xmlVertices, u"input"_j)->iterator(); _i->hasNext(); ) {
										Element* xmlVerticesInput = java_cast< Element* >(_i->next());
										{
											if (xmlVerticesInput->getAttribute(u"semantic"_j)->equalsIgnoreCase(u"position"_j)) {
												xmlVerticesSource = xmlVerticesInput->getAttribute(u"source"_j)->substring(1);
											} else if (xmlVerticesInput->getAttribute(u"semantic"_j)->equalsIgnoreCase(u"normal"_j)) {
												xmlNormalsSource = xmlVerticesInput->getAttribute(u"source"_j)->substring(1);
											}
										}
									}
								}
							}
						}
						if (xmlVerticesSource == nullptr) {
							throw new ModelFileIOException(::java::lang::StringBuilder().append(u"Could not determine triangles vertices source for '"_j)->append(xmlNodeId)
								->append(u"'"_j)->toString());
						}
						if (xmlNormalsSource == nullptr) {
							throw new ModelFileIOException(::java::lang::StringBuilder().append(u"Could not determine triangles normal source for '"_j)->append(xmlNodeId)
								->append(u"'"_j)->toString());
						}
						for (auto _i = getChildrenByTagName(xmlMesh, u"source"_j)->iterator(); _i->hasNext(); ) {
							Element* xmlMeshSource = java_cast< Element* >(_i->next());
							{
								if (xmlMeshSource->getAttribute(u"id"_j)->equals(xmlVerticesSource)) {
									auto xmlFloatArray = java_cast< Element* >(getChildrenByTagName(xmlMeshSource, u"float_array"_j)->get(0));
									auto valueString = xmlFloatArray->getTextContent();
									t = new StringTokenizer(valueString, u" \n\r"_j);
									while (t->hasMoreTokens()) {
										auto v = new Vector3(Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()));
										vertices->add(v);
									}
								} else if (xmlMeshSource->getAttribute(u"id"_j)->equals(xmlNormalsSource)) {
									auto xmlFloatArray = java_cast< Element* >(getChildrenByTagName(xmlMeshSource, u"float_array"_j)->get(0));
									auto valueString = xmlFloatArray->getTextContent();
									t = new StringTokenizer(valueString, u" \n\r"_j);
									while (t->hasMoreTokens()) {
										auto v = new Vector3(Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()));
										normals->add(v);
									}
								}
								if (xmlTexCoordSource != nullptr) {
									if (xmlMeshSource->getAttribute(u"id"_j)->equals(xmlTexCoordSource)) {
										auto xmlFloatArray = java_cast< Element* >(getChildrenByTagName(xmlMeshSource, u"float_array"_j)->get(0));
										auto valueString = xmlFloatArray->getTextContent();
										t = new StringTokenizer(valueString, u" \n\r"_j);
										while (t->hasMoreTokens()) {
											auto tc = new TextureCoordinate(Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()));
											textureCoordinates->add(tc);
										}
									}
								}
							}
						}
						for (auto _i = getChildrenByTagName(xmlPolygons, u"p"_j)->iterator(); _i->hasNext(); ) {
							Element* xmlPolygon = java_cast< Element* >(_i->next());
							{
								auto valueString = xmlPolygon->getTextContent();
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
										if (valid) {
											auto f = new Face(group, (*vi)[0] + verticesOffset, (*vi)[1] + verticesOffset, (*vi)[2] + verticesOffset, (*ni)[0] + normalsOffset, (*ni)[1] + normalsOffset, (*ni)[2] + normalsOffset);
											if (ti != nullptr) {
												f->setTextureCoordinateIndices((*ti)[0] + textureCoordinatesOffset, (*ti)[1] + textureCoordinatesOffset, (*ti)[2] + textureCoordinatesOffset);
											}
											faces->add(f);
										}
										viIdx = 0;
										niIdx = 0;
										tiIdx = 0;
										valid = true;
									}
									valueIdx++;
								}
							}
						}
						if (faces->isEmpty() == false) {
							facesEntity->setFaces(faces);
							facesEntities->add(facesEntity);
						}
					}
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

Material* DAEReader::readMaterial(DAEReader_AuthoringTool* authoringTool, String* pathName, Model* model, Element* xmlRoot, String* xmlNodeId) /* throws(Exception) */
{
	clinit();
	String* xmlEffectId = nullptr;
	auto xmlLibraryMaterials = java_cast< Element* >(getChildrenByTagName(xmlRoot, u"library_materials"_j)->get(0));
	for (auto _i = getChildrenByTagName(xmlLibraryMaterials, u"material"_j)->iterator(); _i->hasNext(); ) {
		Element* xmlMaterial = java_cast< Element* >(_i->next());
		{
			if (xmlMaterial->getAttribute(u"id"_j)->equals(xmlNodeId)) {
				auto xmlInstanceEffect = java_cast< Element* >(getChildrenByTagName(xmlMaterial, u"instance_effect"_j)->get(0));
				xmlEffectId = xmlInstanceEffect->getAttribute(u"url"_j)->substring(1);
			}
		}
	}
	if (xmlEffectId == nullptr) {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Could not determine effect id for '"_j)->append(xmlNodeId)
			->append(u"'"_j)->toString()));
		return nullptr;
	}
	auto material = new Material(xmlNodeId);
	String* xmlDiffuseTextureId = nullptr;
	String* xmlSpecularTextureId = nullptr;
	String* xmlBumpTextureId = nullptr;
	auto xmlLibraryEffects = java_cast< Element* >(getChildrenByTagName(xmlRoot, u"library_effects"_j)->get(0));
	for (auto _i = getChildrenByTagName(xmlLibraryEffects, u"effect"_j)->iterator(); _i->hasNext(); ) {
		Element* xmlEffect = java_cast< Element* >(_i->next());
		{
			if (xmlEffect->getAttribute(u"id"_j)->equals(xmlEffectId)) {
				auto xmlProfile = java_cast< Element* >(getChildrenByTagName(xmlEffect, u"profile_COMMON"_j)->get(0));
				auto samplerSurfaceMapping = new _HashMap();
				auto surfaceImageMapping = new _HashMap();
				for (auto _i = getChildrenByTagName(xmlProfile, u"newparam"_j)->iterator(); _i->hasNext(); ) {
					Element* xmlNewParam = java_cast< Element* >(_i->next());
					{
						auto xmlNewParamSID = xmlNewParam->getAttribute(u"sid"_j);
						for (auto _i = getChildrenByTagName(xmlNewParam, u"surface"_j)->iterator(); _i->hasNext(); ) {
							Element* xmlSurface = java_cast< Element* >(_i->next());
							
																for (auto _i = getChildrenByTagName(xmlSurface, u"init_from"_j)->iterator(); _i->hasNext(); ) {
									Element* xmlSurfaceInitFrom = java_cast< Element* >(_i->next());
									{
										surfaceImageMapping->put(xmlNewParamSID, xmlSurfaceInitFrom->getTextContent());
									}
								}

						}
						for (auto _i = getChildrenByTagName(xmlNewParam, u"sampler2D"_j)->iterator(); _i->hasNext(); ) {
							Element* xmlSampler2D = java_cast< Element* >(_i->next());
							
																for (auto _i = getChildrenByTagName(xmlSampler2D, u"source"_j)->iterator(); _i->hasNext(); ) {
									Element* xmlSampler2DSource = java_cast< Element* >(_i->next());
									{
										samplerSurfaceMapping->put(xmlNewParamSID, xmlSampler2DSource->getTextContent());
									}
								}

						}
					}
				}
				for (auto _i = getChildrenByTagName(xmlProfile, u"technique"_j)->iterator(); _i->hasNext(); ) {
					Element* xmlTechnique = java_cast< Element* >(_i->next());
					{
						auto xmlTechniqueNodes = xmlTechnique->getChildNodes();
						for (auto i = 0; i < xmlTechniqueNodes->getLength(); i++) {
							auto xmlTechniqueNode = xmlTechniqueNodes->item(i);
							if (xmlTechniqueNode->getNodeType() != Node::ELEMENT_NODE)
								continue;

							for (auto _i = getChildrenByTagName(java_cast< Element* >(xmlTechniqueNode), u"diffuse"_j)->iterator(); _i->hasNext(); ) {
								Element* xmlDiffuse = java_cast< Element* >(_i->next());
								{
									for (auto _i = getChildrenByTagName(xmlDiffuse, u"texture"_j)->iterator(); _i->hasNext(); ) {
										Element* xmlTexture = java_cast< Element* >(_i->next());
										{
											xmlDiffuseTextureId = xmlTexture->getAttribute(u"texture"_j);
											auto sample2Surface = java_cast< String* >(samplerSurfaceMapping->get(xmlDiffuseTextureId));
											String* surface2Image = nullptr;
											if (sample2Surface != nullptr)
												surface2Image = java_cast< String* >(surfaceImageMapping->get(sample2Surface));

											if (surface2Image != nullptr)
												xmlDiffuseTextureId = surface2Image;

										}
									}
									for (auto _i = getChildrenByTagName(xmlDiffuse, u"color"_j)->iterator(); _i->hasNext(); ) {
										Element* xmlColor = java_cast< Element* >(_i->next());
										{
											auto t = new StringTokenizer(xmlColor->getTextContent(), u" "_j);
											material->getDiffuseColor()->set(Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()));
										}
									}
								}
							}
							for (auto _i = getChildrenByTagName(java_cast< Element* >(xmlTechniqueNode), u"ambient"_j)->iterator(); _i->hasNext(); ) {
								Element* xmlAmbient = java_cast< Element* >(_i->next());
								{
									for (auto _i = getChildrenByTagName(xmlAmbient, u"color"_j)->iterator(); _i->hasNext(); ) {
										Element* xmlColor = java_cast< Element* >(_i->next());
										{
											auto t = new StringTokenizer(xmlColor->getTextContent(), u" "_j);
											material->getAmbientColor()->set(Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()));
										}
									}
								}
							}
							for (auto _i = getChildrenByTagName(java_cast< Element* >(xmlTechniqueNode), u"emission"_j)->iterator(); _i->hasNext(); ) {
								Element* xmlEmission = java_cast< Element* >(_i->next());
								{
									for (auto _i = getChildrenByTagName(xmlEmission, u"color"_j)->iterator(); _i->hasNext(); ) {
										Element* xmlColor = java_cast< Element* >(_i->next());
										{
											auto t = new StringTokenizer(xmlColor->getTextContent(), u" "_j);
											material->getEmissionColor()->set(Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()));
										}
									}
								}
							}
							auto hasSpecularMap = false;
							auto hasSpecularColor = false;
							for (auto _i = getChildrenByTagName(java_cast< Element* >(xmlTechniqueNode), u"specular"_j)->iterator(); _i->hasNext(); ) {
								Element* xmlSpecular = java_cast< Element* >(_i->next());
								{
									for (auto _i = getChildrenByTagName(xmlSpecular, u"texture"_j)->iterator(); _i->hasNext(); ) {
										Element* xmlTexture = java_cast< Element* >(_i->next());
										{
											xmlSpecularTextureId = xmlTexture->getAttribute(u"texture"_j);
											auto sample2Surface = java_cast< String* >(samplerSurfaceMapping->get(xmlSpecularTextureId));
											String* surface2Image = nullptr;
											if (sample2Surface != nullptr)
												surface2Image = java_cast< String* >(surfaceImageMapping->get(sample2Surface));

											if (surface2Image != nullptr)
												xmlSpecularTextureId = surface2Image;

											hasSpecularMap = true;
										}
									}
									for (auto _i = getChildrenByTagName(xmlSpecular, u"color"_j)->iterator(); _i->hasNext(); ) {
										Element* xmlColor = java_cast< Element* >(_i->next());
										{
											auto t = new StringTokenizer(xmlColor->getTextContent(), u" "_j);
											material->getSpecularColor()->set(Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()));
											hasSpecularColor = true;
										}
									}
								}
							}
							if (hasSpecularMap == true && hasSpecularColor == false) {
								material->getSpecularColor()->set(1.0f, 1.0f, 1.0f, 1.0f);
							}
							for (auto _i = getChildrenByTagName(java_cast< Element* >(xmlTechniqueNode), u"shininess"_j)->iterator(); _i->hasNext(); ) {
								Element* xmlShininess = java_cast< Element* >(_i->next());
								{
									for (auto _i = getChildrenByTagName(xmlShininess, u"float"_j)->iterator(); _i->hasNext(); ) {
										Element* xmlFloat = java_cast< Element* >(_i->next());
										{
											material->setShininess(Float::parseFloat(xmlFloat->getTextContent()));
										}
									}
								}
							}
						}
						for (auto _i = getChildrenByTagName(xmlTechnique, u"extra"_j)->iterator(); _i->hasNext(); ) {
							Element* xmlBumpExtra = java_cast< Element* >(_i->next());
							
																for (auto _i = getChildrenByTagName(xmlBumpExtra, u"technique"_j)->iterator(); _i->hasNext(); ) {
									Element* xmlBumpTechnique = java_cast< Element* >(_i->next());
									
																				for (auto _i = getChildrenByTagName(xmlBumpTechnique, u"bump"_j)->iterator(); _i->hasNext(); ) {
											Element* xmlBumpTechniqueBump = java_cast< Element* >(_i->next());
											
																								for (auto _i = getChildrenByTagName(xmlBumpTechniqueBump, u"texture"_j)->iterator(); _i->hasNext(); ) {
													Element* xmlBumpTexture = java_cast< Element* >(_i->next());
													{
														xmlBumpTextureId = xmlBumpTexture->getAttribute(u"texture"_j);
														auto sample2Surface = java_cast< String* >(samplerSurfaceMapping->get(xmlBumpTextureId));
														String* surface2Image = nullptr;
														if (sample2Surface != nullptr)
															surface2Image = java_cast< String* >(surfaceImageMapping->get(sample2Surface));

														if (surface2Image != nullptr)
															xmlBumpTextureId = surface2Image;

													}
												}

										}

								}

						}
					}
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
	} catch (IOException* ioe) {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"DAEReader::makeDisplacementFilenameCandidate::"_j)->append(static_cast< Object* >(ioe))->toString()));
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

String* DAEReader::getTextureFileNameById(Element* xmlRoot, String* xmlTextureId)
{
	clinit();
	String* xmlTextureFilename = nullptr;
	auto xmlLibraryImages = java_cast< Element* >(getChildrenByTagName(xmlRoot, u"library_images"_j)->get(0));
	for (auto _i = getChildrenByTagName(xmlLibraryImages, u"image"_j)->iterator(); _i->hasNext(); ) {
		Element* xmlImage = java_cast< Element* >(_i->next());
		{
			if (xmlImage->getAttribute(u"id"_j)->equals(xmlTextureId)) {
				xmlTextureFilename = java_cast< Element* >(getChildrenByTagName(xmlImage, u"init_from"_j)->get(0))->getTextContent();
				if (xmlTextureFilename->startsWith(u"file://"_j)) {
					xmlTextureFilename = xmlTextureFilename->substring(7);
				}
				break;
			}
		}
	}
	return xmlTextureFilename;
}

_ArrayList* DAEReader::getChildrenByTagName(Element* parent, String* name)
{
	clinit();
	auto nodeList = new _ArrayList();
	for (auto *child = parent->getFirstChild(); child != nullptr; child = child->getNextSibling()) {
		if (child->getNodeType() == Node::ELEMENT_NODE && name->equals(child->getNodeName())) {
			nodeList->add(java_cast< Element* >(child));
		}
	}
	return nodeList;
}

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

