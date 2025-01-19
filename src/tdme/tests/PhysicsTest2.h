#pragma once

#include <memory>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/tests/fwd-tdme.h>
#include <tdme/utilities/ObjectDeleter.h>

using std::unique_ptr;

using tdme::application::Application;
using tdme::engine::model::Model;
using tdme::engine::physics::World;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::Engine;
using tdme::utilities::ObjectDeleter;

/**
 * Engine with physics test 2
 * @author andreas.drewke
 */
class tdme::tests::PhysicsTest2 final
	: public virtual Application
{
private:
	static constexpr int32_t RIGID_TYPEID_STANDARD { 1 };
	static constexpr int32_t BOX_COUNT { 4 };
	Engine* engine { nullptr };
	unique_ptr<World> world;
	ObjectDeleter<Model> modelDeleter;
	ObjectDeleter<BoundingVolume> bvDeleter;

public:

	/**
	 * Main
	 * @param argc argument count
	 * @param argv argument values
	 * @returns exit code
	 */
	static int main(int argc, char** argv);

	// forbid class copy
	FORBID_CLASS_COPY(PhysicsTest2)

	/**
	 * Public constructor
	 */
	PhysicsTest2();

	/**
	 * Destructor
	 */
	~PhysicsTest2();

	// overridden methods
	void display() override;
	void dispose() override;
	void initialize() override;
	void reshape(int32_t width, int32_t height) override;

};
