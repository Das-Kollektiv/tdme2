#include <tdme/engine/model/Face.h>

#include <tdme/engine/model/Group.h>

using tdme::engine::model::Face;
using tdme::engine::model::Group;

Face::Face()
{
	init();
}

Face::Face(Group* group, int32_t vi0, int32_t vi1, int32_t vi2, int32_t ni0, int32_t ni1, int32_t ni2) 
{
	init();
	this->group = group;
	vertexIndices[0] = vi0;
	vertexIndices[1] = vi1;
	vertexIndices[2] = vi2;
	normalIndices[0] = ni0;
	normalIndices[1] = ni1;
	normalIndices[2] = ni2;
}

Face::Face(Group* group, int32_t vi0, int32_t vi1, int32_t vi2, int32_t ni0, int32_t ni1, int32_t ni2, int32_t vt0, int32_t vt1, int32_t vt2) 
{
	init();
	this->group = group;
	vertexIndices[0] = vi0;
	vertexIndices[1] = vi1;
	vertexIndices[2] = vi2;
	normalIndices[0] = ni0;
	normalIndices[1] = ni1;
	normalIndices[2] = ni2;
	textureCoordinateIndices[0] = vt0;
	textureCoordinateIndices[1] = vt1;
	textureCoordinateIndices[2] = vt2;
}

void Face::init()
{
}

Group* Face::getGroup()
{
	return group;
}

array<int32_t, 3>* Face::getVertexIndices()
{
	return &vertexIndices;
}

array<int32_t, 3>* Face::getNormalIndices()
{
	return &normalIndices;
}

void Face::setTextureCoordinateIndices(int32_t vt0, int32_t vt1, int32_t vt2)
{
	textureCoordinateIndices[0] = vt0;
	textureCoordinateIndices[1] = vt1;
	textureCoordinateIndices[2] = vt2;
}

array<int32_t, 3>* Face::getTextureCoordinateIndices()
{
	return &textureCoordinateIndices;
}

void Face::setTangentIndices(int32_t ti0, int32_t ti1, int32_t ti2)
{
	tangentIndices[0] = ti0;
	tangentIndices[1] = ti1;
	tangentIndices[2] = ti2;
}

array<int32_t, 3>* Face::getTangentIndices()
{
	return &tangentIndices;
}

void Face::setBitangentIndices(int32_t bi0, int32_t bi1, int32_t bi2)
{
	bitangentIndices[0] = bi0;
	bitangentIndices[1] = bi1;
	bitangentIndices[2] = bi2;
}

array<int32_t, 3>* Face::getBitangentIndices()
{
	return &bitangentIndices;
}

void Face::setIndexedRenderingIndices(const array<int32_t, 3>& indices)
{
	vertexIndices = indices;
	normalIndices = indices;
	textureCoordinateIndices = indices;
	tangentIndices = indices;
	bitangentIndices = indices;
}

