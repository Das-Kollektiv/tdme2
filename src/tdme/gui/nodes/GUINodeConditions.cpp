#include <tdme/gui/nodes/GUINodeConditions.h>

#include <algorithm>
#include <vector>

using std::vector;

using tdme::gui::nodes::GUINodeConditions;

GUINodeConditions::GUINodeConditions() 
{
}

vector<string>& GUINodeConditions::getConditions()
{
	return conditions;
}

void GUINodeConditions::add(const string& condition)
{
	remove(condition);
	conditions.push_back(condition);
}

void GUINodeConditions::remove(const string& condition)
{
	// TODO: use STL to remove conditions
	for (vector<string>::iterator i = conditions.begin(); i != conditions.end(); ++i) {
		if (condition == *i) {
			conditions.erase(i);
			return;
		}

	}
}

void GUINodeConditions::removeAll()
{
	conditions.clear();
}

