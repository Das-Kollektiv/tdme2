#pragma once

#include <string>
#include <vector>

#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::vector;
using std::string;

/** 
 * GUI node conditions
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUINodeConditions final
{
	friend class GUINode;

private:
	vector<string> conditions {  };

public:

	/** 
	 * @return conditions
	 */
	vector<string>* getConditions();

	/** 
	 * Add a condition
	 * @param condition
	 */
	void add(const string& condition);

	/** 
	 * Remove a condition
	 * @param condition
	 */
	void remove(const string& condition);

	/** 
	 * Remove all
	 */
	void removeAll();

	/**
	 * Public constructor
	 */
	GUINodeConditions();
};
