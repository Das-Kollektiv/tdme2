#include <tdme/engine/subsystems/decals/DecalObjectInternal.h>

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/subsystems/rendering/ObjectBuffer.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Transformations.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/FloatBuffer.h>

using std::string;
using std::vector;

using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::model::Color4;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::decals::DecalObjectInternal;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::rendering::ObjectBuffer;
using tdme::engine::Engine;
using tdme::engine::Transformations;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utilities::ByteBuffer;
using tdme::utilities::FloatBuffer;

DecalObjectInternal::DecalObjectInternal(const string& id, Texture* texture)
{
	this->id = id;
	this->enabled = true;
	this->effectColorMul.set(1.0f, 1.0f, 1.0f, 1.0f);
	this->effectColorAdd.set(0.0f, 0.0f, 0.0f, 0.0f);
	this->pickable = false;
	this->contributesShadows = false;
	this->receivesShadows = false;
	this->texture = texture;
	// TODO: set up bounding box
	updateBoundingBox();
}

DecalObjectInternal::~DecalObjectInternal() {
}

void DecalObjectInternal::update()
{
	Transformations::update();
	updateBoundingBox();
}

void DecalObjectInternal::fromTransformations(const Transformations& transformations)
{
	Transformations::fromTransformations(transformations);
	updateBoundingBox();
}

void DecalObjectInternal::initialize() {
	texture = TextureReader::read("resources/engine/textures", "point.png");
}

void DecalObjectInternal::dispose()
{
	if (texture != nullptr) {
		texture->releaseReference();
		texture = nullptr;
	}
}
