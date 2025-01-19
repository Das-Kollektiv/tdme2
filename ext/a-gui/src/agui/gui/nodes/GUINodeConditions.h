#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include <agui/agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/utilities/fwd-agui.h>

using std::find;
using std::string;
using std::vector;

/**
 * GUI element node conditions
 * @author Andreas Drewke
 */
class agui::gui::nodes::GUINodeConditions final
{
	friend class GUINode;

private:
	GUIElementNode* elementNode { nullptr };
	vector<string> conditions;

	/**
	 * Update node
	 * @param node node
	 * @param conditions conditions that have been set
	 */
	void updateNode(GUINode* node, const vector<string>& conditions) const;

	/**
	 * Update element node
	 * @param conditions conditions that have been set
	 */
	void updateElementNode(const vector<string>& conditions) const;

public:
	/**
	 * Public constructor
	 * @param node node
	 */
	GUINodeConditions(GUIElementNode* node = nullptr);

	/**
	 * @return conditions
	 */
	inline const vector<string>& getConditions() const {
		return conditions;
	}

	/**
	 * Returns if condition is set
	 * @param condition condition name
	 * @return if condition is set
	 */
	inline bool has(const string& condition) const {
		return find(conditions.begin(), conditions.end(), condition) != conditions.end();
	}

	/**
	 * Set condition
	 * @param condition condition
	 */
	inline void set(const string& condition) {
		this->conditions = {{ condition }};
		updateElementNode(conditions);
	}

	/**
	 * Set multiple conditions
	 * @param conditions conditions
	 */
	inline void set(const vector<string>& conditions) {
		this->conditions = conditions;
		updateElementNode(conditions);
	}

	/**
	 * Add a condition
	 * @param condition condition
	 * @return condition changed
	 */
	inline bool add(const string& condition) {
		auto conditionsChanged = has(condition) == false;
		if (conditionsChanged == true) {
			conditions.push_back(condition);
			updateElementNode({condition});
		}
		return conditionsChanged;
	}

	/**
	 * Remove a condition
	 * @param condition condition
	 * @return condition changed
	 */
	inline bool remove(const string& condition) {
		auto conditionsChanged = has(condition);
		if (conditionsChanged == true) {
			conditions.erase(std::remove(conditions.begin(), conditions.end(), condition), conditions.end());
			updateElementNode({});
		}
		return conditionsChanged;
	}

	/**
	 * Remove all
	 * @return condition changed
	 */
	inline bool removeAll() {
		auto conditionsChanged = conditions.empty() == false;
		if (conditionsChanged == true) {
			conditions.clear();
			updateElementNode({});
		}
		return conditionsChanged;
	}

};
