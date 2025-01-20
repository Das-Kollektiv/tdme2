#include <tdme/engine/prototype/PrototypeImposterLOD.h>

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/Color4.h>

using tdme::engine::prototype::PrototypeImposterLOD;

using std::string;
using std::vector;

using tdme::engine::model::Model;
using tdme::engine::Color4;

PrototypeImposterLOD::PrototypeImposterLOD(
	const vector<string>& fileNames,
	const vector<Model*>& models,
	float minDistance
) :
	fileNames(fileNames),
	models(models),
	minDistance(minDistance) {
	colorMul.set(1.0f, 1.0f, 1.0f, 1.0f);
	colorAdd.set(0.0f, 0.0f, 0.0f, 0.0f);
}

PrototypeImposterLOD::~PrototypeImposterLOD() {
	for (auto model: models) delete model;
}
