#include <tdme/tools/editor/misc/Tools.h>

#include <memory>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/ShaderModel.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/ModelTools.h>
#include <tdme/utilities/Primitives.h>

using std::unique_ptr;

using tdme::tools::editor::misc::Tools;

using tdme::application::Application;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::model::Model;
using tdme::engine::model::ShaderModel;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::math::Vector3;
using tdme::utilities::ModelTools;
using tdme::utilities::Primitives;

unique_ptr<Model> Tools::gizmoAll = nullptr;
unique_ptr<Model> Tools::gizmoTranslationScale = nullptr;
unique_ptr<Model> Tools::gizmoTranslation = nullptr;
unique_ptr<Model> Tools::gizmoScale = nullptr;
unique_ptr<Model> Tools::gizmoRotations = nullptr;
unique_ptr<Model> Tools::defaultOBB = nullptr;

Model* Tools::getGizmoAll() {
	if (gizmoAll == nullptr) {
		gizmoAll = unique_ptr<Model>(ModelReader::read("resources/engine/models", "gizmo_all.tm"));
		ModelTools::prepareForShader(gizmoAll.get());
		ModelTools::changeFrontFace(gizmoAll.get()); // TODO: why is this needed currently
		gizmoAll->setShaderModel(ShaderModel::SPECULAR);
	}
	return gizmoAll.get();
}

Model* Tools::getGizmoTranslationScale() {
	if (gizmoTranslationScale == nullptr) {
		gizmoTranslationScale = unique_ptr<Model>(ModelReader::read("resources/engine/models", "gizmo_transscale.tm"));
		ModelTools::prepareForShader(gizmoTranslationScale.get());
		ModelTools::changeFrontFace(gizmoTranslationScale.get()); // TODO: why is this needed currently
		gizmoTranslationScale->setShaderModel(ShaderModel::SPECULAR);
	}
	return gizmoTranslationScale.get();
}

Model* Tools::getGizmoTranslation() {
	if (gizmoTranslation == nullptr) {
		gizmoTranslation = unique_ptr<Model>(ModelReader::read("resources/engine/models", "gizmo_translate.tm"));
		ModelTools::prepareForShader(gizmoTranslation.get());
		ModelTools::changeFrontFace(gizmoTranslation.get()); // TODO: why is this needed currently
		gizmoTranslation->setShaderModel(ShaderModel::SPECULAR);
	}
	return gizmoTranslation.get();
}

Model* Tools::getGizmoScale() {
	if (gizmoScale == nullptr) {
		gizmoScale = unique_ptr<Model>(ModelReader::read("resources/engine/models", "gizmo_scale.tm"));
		ModelTools::prepareForShader(gizmoScale.get());
		ModelTools::changeFrontFace(gizmoScale.get()); // TODO: why is this needed currently
		gizmoScale->setShaderModel(ShaderModel::SPECULAR);
	}
	return gizmoScale.get();
}

Model* Tools::getGizmoRotations() {
	if (gizmoRotations == nullptr) {
		gizmoRotations = unique_ptr<Model>(ModelReader::read("resources/engine/models", "gizmo_rotate.tm"));
		ModelTools::prepareForShader(gizmoRotations.get());
		ModelTools::changeFrontFace(gizmoRotations.get()); // TODO: why is this needed currently
		gizmoRotations->setShaderModel(ShaderModel::SPECULAR);
	}
	return gizmoRotations.get();
}

Model* Tools::getDefaultObb() {
	if (defaultOBB == nullptr) {
		OrientedBoundingBox obb(
			Vector3(),
			OrientedBoundingBox::AABB_AXIS_X,
			OrientedBoundingBox::AABB_AXIS_Y,
			OrientedBoundingBox::AABB_AXIS_Z,
			Vector3(0.5f, 0.5f, 0.5f)
		);
		defaultOBB = unique_ptr<Model>(Primitives::createModel(&obb, "tdme.obb.default"));
	}
	return defaultOBB.get();
}
