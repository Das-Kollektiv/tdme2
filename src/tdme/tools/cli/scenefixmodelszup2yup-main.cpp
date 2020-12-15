#include <string>
#include <cstdlib>

#include <tdme/application/Application.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/engine/fileio/scenes/SceneReader.h>
#include <tdme/engine/fileio/scenes/SceneWriter.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/scene/SceneLibrary.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/engine/scene/SceneEntity.h>
#include <tdme/engine/scene/SceneLibrary.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using tdme::application::Application;
using tdme::engine::Transformations;
using tdme::engine::model::RotationOrder;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::engine::fileio::scenes::SceneReader;
using tdme::engine::fileio::scenes::SceneWriter;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::Prototype_Type;
using tdme::engine::scene::Scene;
using tdme::engine::scene::SceneEntity;
using tdme::engine::scene::SceneLibrary;
using tdme::utilities::Console;
using tdme::utilities::Exception;

int main(int argc, char** argv)
{
	Console::println(string("scenefixmodelszup2yup 1.9.9"));
	Console::println(string("Programmed 2018 by Andreas Drewke, drewke.net."));
	Console::println();
	if (argc != 2) {
		Console::println("Usage: scenefixmodelszup2yup scene.tl");
		Application::exit(1);
	}
	string sceneFileName = string(argv[1]);
	try {
		Console::println("Loading scene: " + sceneFileName);
		Scene scene;
		SceneReader::read(
			FileSystem::getInstance()->getPathName(sceneFileName),
			FileSystem::getInstance()->getFileName(sceneFileName),
			scene
		);
		Console::println("Fixing scene models up axis from Z-Up to Y-Up");
		Matrix4x4 z2yUpMatrix;
		z2yUpMatrix.identity().rotate(Vector3(1.0f, 0.0f, 0.0f), -90.0f);
		// scene prototype library
		auto sceneLibray = scene.getLibrary();
		for (auto i = 0; i < sceneLibray->getPrototypeCount(); i++) {
			auto entity = sceneLibray->getPrototypeAt(i);
			if (entity->getType() != Prototype_Type::MODEL) continue;
			entity->getModel()->setImportTransformationsMatrix(entity->getModel()->getImportTransformationsMatrix().clone().multiply(z2yUpMatrix));
			z2yUpMatrix.multiply(
				entity->getModel()->getBoundingBox()->getMin(),
				entity->getModel()->getBoundingBox()->getMin()
			);
			z2yUpMatrix.multiply(
				entity->getModel()->getBoundingBox()->getMax(),
				entity->getModel()->getBoundingBox()->getMax()
			);
			entity->getModel()->getBoundingBox()->update();
		}
		// scene entities
		for (auto i = 0; i < scene.getEntityCount(); i++) {
			auto entity = scene.getEntityAt(i);
			if (entity->getPrototype()->getType() != Prototype_Type::MODEL) continue;
			auto scale = entity->getTransformations().getScale();
			entity->getTransformations().setScale(Vector3(scale.getX(), scale.getZ(), scale.getY()));
			auto rotationX = entity->getTransformations().getRotationAngle(scene.getRotationOrder()->getAxisXIndex());
			entity->getTransformations().setRotationAngle(scene.getRotationOrder()->getAxisXIndex(), rotationX + 90);
			entity->getTransformations().update();
		}
		// TODO: bvs
		Console::println("Saving scene: " + sceneFileName);
		SceneWriter::write(
			FileSystem::getInstance()->getPathName(sceneFileName),
			FileSystem::getInstance()->getFileName(sceneFileName),
			scene
		);
	} catch (Exception& exception) {
		Console::println("An error occurred: " + string(exception.what()));
	}
}
