#include <tdme/engine/subsystems/decals/DecalInternal.h>

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/Transform.h>

using std::string;
using std::vector;

using tdme::engine::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::Color4;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::subsystems::decals::DecalInternal;
using tdme::engine::Transform;

DecalInternal::DecalInternal(const string& id, OrientedBoundingBox* obb, Texture* texture, int32_t textureHorizontalSprites, int32_t textureVerticalSprites, float fps)
{
	this->id = id;
	this->enabled = true;
	this->effectColorMul.set(1.0f, 1.0f, 1.0f, 1.0f);
	this->effectColorAdd.set(0.0f, 0.0f, 0.0f, 0.0f);
	this->pickable = false;
	this->contributesShadows = false;
	this->receivesShadows = false;
	this->obb = obb;
	this->entityTransformMatrix.identity();
	boundingBox = BoundingBox(obb);
	obbMatrix.identity();
	obbMatrix.setTranslation(obb->getCenter());
	obbMatrix.setAxes(
		obb->getAxes()[0] * obb->getHalfExtension()[0] * 2.0f,
		obb->getAxes()[1] * obb->getHalfExtension()[1] * 2.0f,
		obb->getAxes()[2] * obb->getHalfExtension()[2] * 2.0f
	);
	updateInternal();
	this->texture = texture != nullptr?texture:TextureReader::read("resources/engine/textures", "point.png");
	this->textureHorizontalSprites = textureHorizontalSprites;
	this->textureVerticalSprites = textureVerticalSprites;
	this->fps = fps;
}

DecalInternal::~DecalInternal() {
	if (texture != nullptr) texture->releaseReference();
}

void DecalInternal::update()
{
	Transform::update();
	//
	auto entityTransform = parentTransform * (*this);
	entityTransformMatrix = entityTransform.getTransformMatrix();
	//
	updateInternal();
}

void DecalInternal::setTransform(const Transform& transform)
{
	Transform::setTransform(transform);
	//
	auto entityTransform = parentTransform * (*this);
	entityTransformMatrix = entityTransform.getTransformMatrix();
	//
	updateInternal();
}

void DecalInternal::initialize() {
}

void DecalInternal::dispose()
{
}
