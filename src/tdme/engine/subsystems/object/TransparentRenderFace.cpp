// Generated from /tdme/src/tdme/engine/subsystems/object/TransparentRenderFace.java
#include <tdme/engine/subsystems/object/TransparentRenderFace.h>

#include <tdme/engine/subsystems/object/TransparentRenderFace.h>

using tdme::engine::subsystems::object::TransparentRenderFace;

bool TransparentRenderFace::compare(TransparentRenderFace* face1, TransparentRenderFace* face2)
{
	return face1->distanceFromCamera > face2->distanceFromCamera;
}
