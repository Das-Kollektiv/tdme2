#include <tdme/engine/fileio/models/TMWriter.h>

#include <array>
#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fileio/textures/BC7TextureWriter.h>
#include <tdme/engine/fileio/textures/PNGTextureWriter.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/model/Animation.h>
#include <tdme/engine/model/AnimationSetup.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Joint.h>
#include <tdme/engine/model/JointWeight.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/model/PBRMaterialProperties.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/model/ShaderModel.h>
#include <tdme/engine/model/Skinning.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/engine/model/UpVector.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::array;
using std::map;
using std::string;
using std::to_string;
using std::vector;

using tdme::application::Application;
using tdme::engine::fileio::models::TMWriter;
using tdme::engine::fileio::models::TMWriterOutputStream;
using tdme::engine::fileio::textures::BC7TextureWriter;
using tdme::engine::fileio::textures::PNGTextureWriter;
using tdme::engine::Texture;
using tdme::engine::model::Animation;
using tdme::engine::model::AnimationSetup;
using tdme::engine::model::Color4;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Joint;
using tdme::engine::model::JointWeight;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::model::PBRMaterialProperties;
using tdme::engine::model::RotationOrder;
using tdme::engine::model::ShaderModel;
using tdme::engine::model::Skinning;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::model::TextureCoordinate;
using tdme::engine::model::UpVector;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::Prototype_Type;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::misc::Tools;
using tdme::utilities::Console;
using tdme::utilities::Exception;

void TMWriter::write(Model* model, const string& pathName, const string& fileName)
{
	vector<uint8_t> data;
	write(model, data);
	FileSystem::getInstance()->setContent(pathName, fileName, data);
}

void TMWriter::write(Model* model, vector<uint8_t>& data) {
	TMWriterOutputStream os(&data);
	os.writeString("TDME Model");
	os.writeByte(static_cast<uint8_t>(1));
	os.writeByte(static_cast<uint8_t>(9));
	os.writeByte(static_cast<uint8_t>(19));
	os.writeString(model->getName());
	os.writeString(model->getUpVector()->getName());
	os.writeString(model->getRotationOrder()->getName());
	os.writeString(model->getShaderModel()->getName());
	os.writeBoolean(model->hasEmbeddedSpecularTextures());
	os.writeBoolean(model->hasEmbeddedPBRTextures());
	os.writeFloatArray(model->getBoundingBox()->getMin().getArray());
	os.writeFloatArray(model->getBoundingBox()->getMax().getArray());
	os.writeFloat(model->getFPS());
	os.writeFloatArray(model->getImportTransformMatrix().getArray());
	writeEmbeddedTextures(&os, model);
	os.writeInt(model->getMaterials().size());
	for (auto it: model->getMaterials()) {
		Material* material = it.second;
		writeMaterial(&os, material);
	}
	writeSubNodes(&os, model->getSubNodes());
	os.writeInt(model->getAnimationSetups().size());
	for (auto it: model->getAnimationSetups()) {
		AnimationSetup* animationSetup = it.second;
		writeAnimationSetup(&os, animationSetup);
	}
	if (Application::hasApplication() == true && os.getData()->size() < 10 * 1024 * 1024) writeThumbnail(&os, model);
}

void TMWriter::writeEmbeddedTextures(TMWriterOutputStream* os, Model* m) {
	map<string, Texture*> embeddedTextures;
	for (auto it: m->getMaterials()) {
		Material* material = it.second;
		auto smp = material->getSpecularMaterialProperties();
		if (smp != nullptr && m->hasEmbeddedSpecularTextures() == true) {
			if (smp->getDiffuseTexture() != nullptr) embeddedTextures[smp->getDiffuseTexture()->getId()] = smp->getDiffuseTexture();
			if (smp->getSpecularTexture() != nullptr) embeddedTextures[smp->getSpecularTexture()->getId()] = smp->getSpecularTexture();
			if (smp->getNormalTexture() != nullptr) embeddedTextures[smp->getNormalTexture()->getId()] = smp->getNormalTexture();
		}
		auto pmp = material->getPBRMaterialProperties();
		if (pmp != nullptr && m->hasEmbeddedPBRTextures() == true) {
			if (pmp->getBaseColorTexture() != nullptr) embeddedTextures[pmp->getBaseColorTexture()->getId()] = pmp->getBaseColorTexture();
			if (pmp->getMetallicRoughnessTexture() != nullptr) embeddedTextures[pmp->getMetallicRoughnessTexture()->getId()] = pmp->getMetallicRoughnessTexture();
			if (pmp->getNormalTexture() != nullptr) embeddedTextures[pmp->getNormalTexture()->getId()] = pmp->getNormalTexture();
		}
	}
	os->writeInt(embeddedTextures.size());
	for (auto it: embeddedTextures) {
		auto texture = it.second;
		os->writeString(texture->getId());
		// optional PNG
		/*
		vector<uint8_t> pngData;
		PNGTextureWriter::write(texture, pngData, false, false);
		os->writeByte(1); // PNG
		os->writeByte(texture->getMinFilter());
		os->writeByte(texture->getMagFilter());
		os->writeInt(pngData.size());
		os->writeUInt8tArray(pngData);
		*/
		//
		/*
		os->writeByte(2); // BC7
		vector<uint8_t> bc7Data;
		os->writeInt(texture->getWidth());
		os->writeInt(texture->getHeight());
		os->writeInt(texture->getTextureWidth());
		os->writeInt(texture->getTextureHeight());
		os->writeByte(texture->getRGBDepthBitsPerPixel());
		os->writeByte(texture->getMinFilter());
		os->writeByte(texture->getMagFilter());
		BC7TextureWriter::write(texture->getTextureWidth(), texture->getTextureHeight(), texture->getRGBDepthBitsPerPixel() / 8, texture->getRGBTextureData(), bc7Data);
		os->writeInt(bc7Data.size());
		os->writeUInt8tArray(bc7Data);
		*/
		os->writeByte(3); // BC7 with mip maps
		vector<uint8_t> bc7Data;
		os->writeInt(texture->getWidth());
		os->writeInt(texture->getHeight());
		os->writeInt(texture->getTextureWidth());
		os->writeInt(texture->getTextureHeight());
		os->writeByte(texture->getRGBDepthBitsPerPixel());
		os->writeByte(texture->getMinFilter());
		os->writeByte(texture->getMagFilter());
		BC7TextureWriter::write(texture->getTextureWidth(), texture->getTextureHeight(), texture->getRGBDepthBitsPerPixel() / 8, texture->getRGBTextureData(), bc7Data);
		os->writeInt(bc7Data.size());
		os->writeUInt8tArray(bc7Data);
		if (texture->isUseMipMap() == false) {
			os->writeByte(0);
		} else {
			auto mipMapTextures = texture->getMipMapTextures(true);
			os->writeByte(mipMapTextures.size());
			for (auto& mipMapTexture: mipMapTextures) {
				os->writeByte(mipMapTexture.format);
				os->writeInt(mipMapTexture.width);
				os->writeInt(mipMapTexture.height);
				os->writeInt(mipMapTexture.textureData.getBufferVector()->size());
				os->writeUInt8tArray(*mipMapTexture.textureData.getBufferVector());
			}
		}
	}
}

void TMWriter::writeMaterial(TMWriterOutputStream* os, Material* m)
{
	// TODO: minFilter, magFilter for non embedded textures
	auto smp = m->getSpecularMaterialProperties();
	auto pmp = m->getPBRMaterialProperties();
	os->writeString(m->getId());
	os->writeFloatArray(smp->getAmbientColor().getArray());
	os->writeFloatArray(smp->getDiffuseColor().getArray());
	os->writeFloatArray(smp->getSpecularColor().getArray());
	os->writeFloatArray(smp->getEmissionColor().getArray());
	os->writeFloat(smp->getShininess());
	os->writeInt(smp->getTextureAtlasSize());
	os->writeString(smp->getDiffuseTexturePathName());
	os->writeString(smp->getDiffuseTextureFileName());
	os->writeString(smp->getDiffuseTransparencyTexturePathName());
	os->writeString(smp->getDiffuseTransparencyTextureFileName());
	os->writeString(smp->getSpecularTexturePathName());
	os->writeString(smp->getSpecularTextureFileName());
	os->writeString(smp->getNormalTexturePathName());
	os->writeString(smp->getNormalTextureFileName());
	os->writeBoolean(smp->hasDiffuseTextureTransparency());
	os->writeBoolean(smp->hasDiffuseTextureMaskedTransparency());
	os->writeFloat(smp->getDiffuseTextureMaskedTransparencyThreshold());
	os->writeBoolean(m->isDoubleSided());
	os->writeFloatArray(m->getTextureMatrix().getArray());
	if (pmp == nullptr) {
		os->writeBoolean(false);
	} else {
		os->writeBoolean(true);
		os->writeFloatArray(pmp->getBaseColorFactor().getArray());
		os->writeString(pmp->getBaseColorTexturePathName());
		os->writeString(pmp->getBaseColorTextureFileName());
		os->writeBoolean(pmp->hasBaseColorTextureMaskedTransparency());
		os->writeFloat(pmp->getBaseColorTextureMaskedTransparencyThreshold());
		os->writeFloat(pmp->getMetallicFactor());
		os->writeFloat(pmp->getRoughnessFactor());
		os->writeString(pmp->getMetallicRoughnessTexturePathName());
		os->writeString(pmp->getMetallicRoughnessTextureFileName());
		os->writeFloat(pmp->getNormalScale());
		os->writeString(pmp->getNormalTexturePathName());
		os->writeString(pmp->getNormalTextureFileName());
		os->writeFloat(pmp->getExposure());
	}
}

void TMWriter::writeAnimationSetup(TMWriterOutputStream* os, AnimationSetup* animationSetup) {
	os->writeString(animationSetup->getId());
	os->writeString(animationSetup->getOverlayFromNodeId());
	os->writeInt(animationSetup->getStartFrame());
	os->writeInt(animationSetup->getEndFrame());
	os->writeBoolean(animationSetup->isLoop());
	os->writeFloat(animationSetup->getSpeed());
}

void TMWriter::writeVertices(TMWriterOutputStream* os, const vector<Vector3>& v)
{
	if (v.size() == 0) {
		os->writeBoolean(false);
	} else {
		os->writeBoolean(true);
		os->writeInt(v.size());
		for (auto i = 0; i < v.size(); i++) {
			os->writeFloatArray(v[i].getArray());
		}
	}
}

void TMWriter::writeTextureCoordinates(TMWriterOutputStream* os, const vector<TextureCoordinate>& tc) // TODO: change std::vector* argument to std::vector& ?
{
	if (tc.size() == 0) {
		os->writeBoolean(false);
	} else {
		os->writeBoolean(true);
		os->writeInt(tc.size());
		for (auto i = 0; i < tc.size(); i++) {
			os->writeFloatArray(tc[i].getArray());
		}
	}
}

void TMWriter::writeIndices(TMWriterOutputStream* os, const array<int32_t, 3>& indices)
{
	os->writeBoolean(true);
	os->writeInt(indices.size());
	for (auto i = 0; i < indices.size(); i++) {
		os->writeInt(indices[i]);
	}
}

void TMWriter::writeAnimation(TMWriterOutputStream* os, Animation* a)
{
	if (a == nullptr) {
		os->writeBoolean(false);
	} else {
		os->writeBoolean(true);
		os->writeInt(a->getTransformMatrices().size());
		for (auto i = 0; i < a->getTransformMatrices().size(); i++) {
			os->writeFloatArray(a->getTransformMatrices()[i].getArray());
		}
	}
}

void TMWriter::writeFacesEntities(TMWriterOutputStream* os, const vector<FacesEntity>& facesEntities)
{
	os->writeInt(facesEntities.size());
	for (auto i = 0; i < facesEntities.size(); i++) {
		auto& fe = facesEntities[i];
		os->writeString(fe.getId());
		if (fe.getMaterial() == nullptr) {
			os->writeBoolean(false);
		} else {
			os->writeBoolean(true);
			os->writeString(fe.getMaterial()->getId());
		}
		os->writeInt(fe.getFaces().size());
		for (auto j = 0; j < fe.getFaces().size(); j++) {
			auto& f = fe.getFaces()[j];
			writeIndices(os, f.getVertexIndices());
			writeIndices(os, f.getNormalIndices());
			writeIndices(os, f.getTextureCoordinateIndices());
			writeIndices(os, f.getTangentIndices());
			writeIndices(os, f.getBitangentIndices());
		}
	}
}

void TMWriter::writeSkinningJoint(TMWriterOutputStream* os, const Joint& joint)
{
	os->writeString(joint.getNodeId());
	os->writeFloatArray(joint.getBindMatrix().getArray());
}

void TMWriter::writeSkinningJointWeight(TMWriterOutputStream* os, const JointWeight& jointWeight)
{
	os->writeInt(jointWeight.getJointIndex());
	os->writeInt(jointWeight.getWeightIndex());
}

void TMWriter::writeSkinning(TMWriterOutputStream* os, Skinning* skinning)
{
	if (skinning == nullptr) {
		os->writeBoolean(false);
	} else {
		os->writeBoolean(true);
		os->writeFloatArray(skinning->getWeights());
		os->writeInt(skinning->getJoints().size());
		for (auto i = 0; i < skinning->getJoints().size(); i++) {
			writeSkinningJoint(os, skinning->getJoints()[i]);
		}
		os->writeInt(skinning->getVerticesJointsWeights().size());
		for (auto i = 0; i < skinning->getVerticesJointsWeights().size(); i++) {
			os->writeInt(skinning->getVerticesJointsWeights()[i].size());
			for (auto j = 0; j < skinning->getVerticesJointsWeights()[i].size(); j++) {
				writeSkinningJointWeight(os, skinning->getVerticesJointsWeights()[i][j]);
			}
		}
	}
}

void TMWriter::writeSubNodes(TMWriterOutputStream* os, const map<string, Node*>& subNodes)
{
	os->writeInt(subNodes.size());
	for (auto it: subNodes) {
		Node* subNode = it.second;
		writeNode(os, subNode);
	}
}

void TMWriter::writeNode(TMWriterOutputStream* os, Node* g)
{
	os->writeString(g->getId());
	os->writeString(g->getName());
	os->writeBoolean(g->isJoint());
	os->writeFloatArray(g->getTransformMatrix().getArray());
	writeVertices(os, g->getVertices());
	writeVertices(os, g->getNormals());
	writeTextureCoordinates(os, g->getTextureCoordinates());
	writeVertices(os, g->getTangents());
	writeVertices(os, g->getBitangents());
	writeAnimation(os, g->getAnimation());
	writeSkinning(os, g->getSkinning());
	writeFacesEntities(os, g->getFacesEntities());
	writeSubNodes(os, g->getSubNodes());
}

void TMWriter::writeThumbnail(TMWriterOutputStream* os, Model* model) {
	// generate thumbnail
	auto prototype = new Prototype(
		Prototype::ID_NONE,
		Prototype_Type::MODEL,
		model->getId(),
		model->getId(),
		"",
		model->getId(),
		string(),
		model,
		Vector3(0.0f, 0.0f, 0.0f)
	);
	vector<uint8_t> pngData;
	string base64PNGData;
	Tools::oseThumbnail(prototype, pngData);
	prototype->unsetModel();
	delete prototype;

	// write as attachment
	os->writeUInt8tArray(pngData);
	os->writeInt(pngData.size()); // png size
	os->writeUInt8tArray({'T', 'M', 'B', 'N'}); // attachment type id
	os->writeUInt8tArray({'A', 'T', 'M', 'T'}); // attachment id
}
