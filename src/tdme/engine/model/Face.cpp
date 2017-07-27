// Generated from /tdme/src/tdme/engine/model/Face.java
#include <tdme/engine/model/Face.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Arrays.h>
#include <tdme/engine/model/Group.h>
#include <Array.h>

using tdme::engine::model::Face;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Arrays;
using tdme::engine::model::Group;

Face::Face()
{
	init();
}

Face::Face(Group* group, int32_t vi0, int32_t vi1, int32_t vi2, int32_t ni0, int32_t ni1, int32_t ni2) 
{
	init();
	this->group = group;
	vertexIndices = new int32_tArray(3);
	(*vertexIndices)[0] = vi0;
	(*vertexIndices)[1] = vi1;
	(*vertexIndices)[2] = vi2;
	normalIndices = new int32_tArray(3);
	(*normalIndices)[0] = ni0;
	(*normalIndices)[1] = ni1;
	(*normalIndices)[2] = ni2;
}

Face::Face(Group* group, int32_t vi0, int32_t vi1, int32_t vi2, int32_t ni0, int32_t ni1, int32_t ni2, int32_t vt0, int32_t vt1, int32_t vt2) 
{
	init();
	this->group = group;
	vertexIndices = new int32_tArray(3);
	(*vertexIndices)[0] = vi0;
	(*vertexIndices)[1] = vi1;
	(*vertexIndices)[2] = vi2;
	normalIndices = new int32_tArray(3);
	(*normalIndices)[0] = ni0;
	(*normalIndices)[1] = ni1;
	(*normalIndices)[2] = ni2;
	textureCoordinateIndices = new int32_tArray(3);
	(*textureCoordinateIndices)[0] = vt0;
	(*textureCoordinateIndices)[1] = vt1;
	(*textureCoordinateIndices)[2] = vt2;
}

void Face::init()
{
	vertexIndices = nullptr;
	normalIndices = nullptr;
	textureCoordinateIndices = nullptr;
	tangentIndices = nullptr;
	bitangentIndices = nullptr;
}

Group* Face::getGroup()
{
	return group;
}

int32_tArray* Face::getVertexIndices()
{
	return vertexIndices;
}

int32_tArray* Face::getNormalIndices()
{
	return normalIndices;
}

void Face::setTextureCoordinateIndices(int32_t vt0, int32_t vt1, int32_t vt2)
{
	textureCoordinateIndices = new int32_tArray(3);
	(*textureCoordinateIndices)[0] = vt0;
	(*textureCoordinateIndices)[1] = vt1;
	(*textureCoordinateIndices)[2] = vt2;
}

int32_tArray* Face::getTextureCoordinateIndices()
{
	return textureCoordinateIndices;
}

void Face::setTangentIndices(int32_t ti0, int32_t ti1, int32_t ti2)
{
	tangentIndices = new int32_tArray(3);
	(*tangentIndices)[0] = ti0;
	(*tangentIndices)[1] = ti1;
	(*tangentIndices)[2] = ti2;
}

int32_tArray* Face::getTangentIndices()
{
	return tangentIndices;
}

void Face::setBitangentIndices(int32_t bi0, int32_t bi1, int32_t bi2)
{
	bitangentIndices = new int32_tArray(3);
	(*bitangentIndices)[0] = bi0;
	(*bitangentIndices)[1] = bi1;
	(*bitangentIndices)[2] = bi2;
}

int32_tArray* Face::getBitangentIndices()
{
	return bitangentIndices;
}

void Face::setIndexedRenderingIndices(int32_tArray* faceVertexIndices)
{
	vertexIndices = faceVertexIndices;
	normalIndices = faceVertexIndices;
	if (textureCoordinateIndices != nullptr)
		textureCoordinateIndices = faceVertexIndices;
	if (tangentIndices != nullptr && bitangentIndices != nullptr) {
		tangentIndices = faceVertexIndices;
		bitangentIndices = faceVertexIndices;
	} else {
		tangentIndices = nullptr;
		bitangentIndices = nullptr;
	}
}

