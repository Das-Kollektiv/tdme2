#include <iostream>
#include <string>

#include <java/lang/String.h>

#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/_Console.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Animation.h>
#include <tdme/engine/fileio/models/DAEReader.h>

using std::wcout;
using std::cout;
using std::endl;
using std::find;

using java::lang::String;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::engine::fileio::models::DAEReader;
using tdme::engine::model::Model;
using tdme::engine::model::Group;
using tdme::engine::model::Animation;
using tdme::utils::_Console;
using tdme::utils::Key;

void printMatrix(Matrix4x4* matrix) {
	for (auto value: *matrix->getArray()) {
		cout << value;
		cout << " ";
	}
	cout << endl;
}

void printVector(Vector3* vector) {
	for (auto value: *vector->getArray()) {
		cout << value;
		cout << " ";
	}
	cout << endl;
}

int main(int argc, char** argv)
{
    cout << "DAETest" << endl;
    Model* model = DAEReader::read(u"./resources/tests/models/test"_j, u"cube.dae"_j);
    for (auto it: *model->getSubGroups()) {
    		Group* group = it.second;
    		wcout << it.first << endl;
    		wcout << "--" << endl;
    		for (auto& vector: *group->getVertices()) {
    			printVector(&vector);
    		}
    		wcout << "--" << endl;
    		printMatrix(group->getTransformationsMatrix());
    		wcout << "--" << endl;
    		Animation* animation = group->getAnimation();
    		for (auto& matrix: *animation->getTransformationsMatrices()) {
    			printMatrix(&matrix);
    		}
    }
}
