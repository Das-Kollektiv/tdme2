#pragma once

#include <memory>

using std::unique_ptr;

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>

using tdme::engine::model::Model;

/**
 * Editor tools
 * @author Andreas Drewke
 */
class tdme::tools::editor::misc::Tools final
{
private:
	STATIC_DLL_IMPEXT static unique_ptr<Model> gizmoAll;
	STATIC_DLL_IMPEXT static unique_ptr<Model> gizmoTranslationScale;
	STATIC_DLL_IMPEXT static unique_ptr<Model> gizmoTranslation;
	STATIC_DLL_IMPEXT static unique_ptr<Model> gizmoScale;
	STATIC_DLL_IMPEXT static unique_ptr<Model> gizmoRotations;
	STATIC_DLL_IMPEXT static unique_ptr<Model> defaultOBB;

public:
	/**
	 * @returns GIZMO translation/rotations/scale
	 */
	static Model* getGizmoAll();

	/**
	 * @returns GIZMO translation/rotations/scale
	 */
	static Model* getGizmoTranslationScale();

	/**
	 * @returns GIZMO for translation
	 */
	static Model* getGizmoTranslation();

	/**
	 * @returns GIZMO for scale
	 */
	static Model* getGizmoScale();

	/**
	 * @returns GIZMO for rotations
	 */
	static Model* getGizmoRotations();

	/**
	 * @returns default obb
	 */
	static Model* getDefaultObb();

};
