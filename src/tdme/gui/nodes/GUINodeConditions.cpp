#include <tdme/gui/nodes/GUINodeConditions.h>

#include <algorithm>
#include <vector>

#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/utils/Console.h>

using std::find;
using std::vector;

using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUIScreenNode;
using tdme::utils::Console;

GUINodeConditions::GUINodeConditions(GUIElementNode* elementNode): elementNode(elementNode)
{
}

const vector<string>& GUINodeConditions::getConditions( ) const
{
	return conditions;
}

bool GUINodeConditions::has(const string& condition) const {
	return find(conditions.begin(), conditions.end(), condition) != conditions.end();
}

bool GUINodeConditions::add(const string& condition)
{
	auto conditionsChanged = has(condition) == false;
	if (conditionsChanged == true) conditions.push_back(condition);
	if (conditionsChanged == true) updateElementNode();
	return conditionsChanged;
}

bool GUINodeConditions::remove(const string& condition)
{
	auto conditionsChanged = has(condition);
	conditions.erase(std::remove(conditions.begin(), conditions.end(), condition), conditions.end());
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

void GUINodeConditions::updateNode(GUINode* node) const {
	node->conditionsMet = node->checkConditions(elementNode);
	if (node->conditionsMet == false) {
		node->parentNode->layouted = false;
		return;
	}

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

void GUINodeConditions::updateElementNode() const {
	if (elementNode == nullptr) return;
	for (auto i = 0; i < elementNode->subNodes.size(); i++) {
		auto guiSubNode = elementNode->subNodes[i];
		updateNode(guiSubNode);
	}
}
