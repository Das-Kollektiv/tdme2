// Generated from /tdme/src/tdme/engine/physics/DynamicVector.java
#include <tdme/engine/physics/DynamicVector.h>

#include <vector>

using std::vector;

using tdme::engine::physics::DynamicVector;

DynamicVector::DynamicVector()
{
}

DynamicVector::DynamicVector(int32_t size) 
{
	data.resize(size);
}

void DynamicVector::setSize(int32_t size)
{
	data.resize(size);
}

void DynamicVector::setValue(int32_t idx, float value)
{
	data[idx] = value;
}

float DynamicVector::getValue(int32_t idx)
{
	return data[idx];
}

void DynamicVector::scale(float value, DynamicVector* dest)
{
	if (data.size() != dest->data.size()) {
		dest->setSize(data.size());
	}
	for (auto i = 0; i < data.size(); i++) {
		dest->data[i] = data[i] * value;
	}
}
