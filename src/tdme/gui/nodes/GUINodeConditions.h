#pragma once

#include <string>
#include <vector>

#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::vector;
using std::string;

using tdme::gui::nodes::GUIElementNode;

/** 
 * GUI node conditions
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUINodeConditions final
{
	friend class GUINode;

private:
	GUIElementNode* elementNode {  };
	vector<string> conditions {  };

public:

	/** 
	 * @return conditions
	 */
	vector<string>& getConditions();

	/** 
	 * Add a condition
	 * @param condition
	 * @return condition changed
	 */
	bool add(const string& condition);

	/** 
	 * Remove a condition
	 * @param condition
	 * @return condition changed
	 */
	bool remove(const string& condition);

	/** 
	 * Remove all
	 * @return condition changed
	 */
	bool removeAll();

	/**
	 * Public constructor
	 * @param node
	 */
	GUINodeConditions(GUIElementNode* node = nullptr);
};
