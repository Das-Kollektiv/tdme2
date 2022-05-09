#include <tdme/engine/subsystems/decals/DecalInternal.h>

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/Transform.h>

using std::string;
using std::vector;

using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::model::Color4;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::subsystems::decals::DecalInternal;
using tdme::engine::Transform;

DecalInternal::DecalInternal(const string& id, OrientedBoundingBox* obb, Texture* texture)
{
	this->id = id;
	this->enabled = true;
	this->effectColorMul.set(1.0f, 1.0f, 1.0f, 1.0f);
	this->effectColorAdd.set(0.0f, 0.0f, 0.0f, 0.0f);
	this->pickable = false;
	this->contributesShadows = false;
	this->receivesShadows = false;
	this->obb = obb;
	this->texture = texture != nullptr?texture:TextureReader::read("resources/engine/textures", "point.png");
	boundingBox = BoundingBox(obb);
	obbMatrix.identity();
	obbMatrix.translate(obb->getCenter());
	obbMatrix.setAxes(
		obb->getAxes()[0] * obb->getHalfExtension()[0] * 2.0f,
		obb->getAxes()[1] * obb->getHalfExtension()[1] * 2.0f,
		obb->getAxes()[2] * obb->getHalfExtension()[2] * 2.0f
	);
	updateInternal();
}

DecalInternal::~DecalInternal() {
	if (texture != nullptr) {
		texture->releaseReference();
		texture = nullptr;
	}
}

void DecalInternal::update()
{
	Transform::update();
	updateInternal();
}

void DecalInternal::setTransform(const Transform& transform)
{
	Transform::setTransform(transform);
	updateInternal();
}

void DecalInternal::initialize() {
}

void DecalInternal::dispose()
{
}
