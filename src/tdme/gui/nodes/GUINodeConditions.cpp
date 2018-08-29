#include <tdme/gui/nodes/GUINodeConditions.h>

#include <algorithm>
#include <vector>

#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/utils/Console.h>

using std::vector;

using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::utils::Console;

GUINodeConditions::GUINodeConditions(GUIElementNode* elementNode): elementNode(elementNode)
{
}

vector<string>& GUINodeConditions::getConditions()
{
	return conditions;
}

bool GUINodeConditions::has(const string& condition) {
	for (vector<string>::iterator it = conditions.begin(); it != conditions.end(); ++it) {
		if (condition == *it) return true;
	}
	return false;
}

bool GUINodeConditions::add(const string& condition)
{
	auto conditionsChanged = true;
	for (vector<string>::iterator it = conditions.begin(); it != conditions.end(); ++it) {
		if (condition == *it) {
			conditionsChanged = false;
			break;
		}
	}
	if (conditionsChanged == true) conditions.push_back(condition);
	if (conditionsChanged == true) updateElementNode();
	return conditionsChanged;
}

bool GUINodeConditions::remove(const string& condition)
{
	auto conditionsChanged = false;
	for (vector<string>::iterator it = conditions.begin(); it != conditions.end(); ++it) {
		if (condition == *it) {
			conditions.erase(it);
			conditionsChanged = true;
			break;
		}
	}
	if (conditionsChanged == true) updateElementNode();
	return conditionsChanged;
}

bool GUINodeConditions::removeAll()
{
	auto conditionsChanged = conditions.empty() == false;
	conditions.clear();
	if (conditionsChanged == true) updateElementNode();
	return conditionsChanged;
}

void GUINodeConditions::updateNode(GUINode* node) {
	node->conditionsMet = node->checkConditions(elementNode);
	if (node->conditionsMet == false) return;

	auto asElementNode = dynamic_cast<GUIElementNode*>(node);
	if (asElementNode != nullptr) return;

	auto parentNode = dynamic_cast<GUIParentNode*>(node);
	if (parentNode != nullptr) {
		for (auto i = 0; i < parentNode->subNodes.size(); i++) {
			auto guiSubNode = parentNode->subNodes[i];
			updateNode(guiSubNode);
		}
	}
}

void GUINodeConditions::updateElementNode() {
	if (elementNode == nullptr) return;
	for (auto i = 0; i < elementNode->subNodes.size(); i++) {
		auto guiSubNode = elementNode->subNodes[i];
		updateNode(guiSubNode);
	}
}
