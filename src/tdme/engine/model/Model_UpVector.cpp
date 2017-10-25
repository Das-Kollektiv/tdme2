#include <tdme/engine/model/Model_UpVector.h>

#include <string>

#include <tdme/utils/Enum.h>

using std::string;

using tdme::engine::model::Model_UpVector;
using tdme::utils::Enum;

Model_UpVector::Model_UpVector(const string& name, int ordinal): Enum(name, ordinal)
{
}

Model_UpVector* tdme::engine::model::Model_UpVector::Y_UP = new Model_UpVector("Y_UP", 0);
Model_UpVector* tdme::engine::model::Model_UpVector::Z_UP = new Model_UpVector("Z_UP", 1);

Model_UpVector* Model_UpVector::valueOf(const string& a0)
{
	if (Y_UP->getName() == a0) return Y_UP;
	if (Z_UP->getName() == a0) return Z_UP;
	// TODO: throw exception here maybe
	return nullptr;
}
