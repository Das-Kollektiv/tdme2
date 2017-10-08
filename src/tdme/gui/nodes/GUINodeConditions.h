#pragma once

#include <string>
#include <vector>

#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::vector;
using std::wstring;

/** 
 * GUI node conditions
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUINodeConditions final
{

public: /* protected */
	vector<wstring> conditions {  };

public:

	/** 
	 * @return conditions
	 */
	vector<wstring>* getConditions();

	/** 
	 * Add a condition
	 * @param condition
	 */
	void add(const wstring& condition);

	/** 
	 * Remove a condition
	 * @param condition
	 */
	void remove(const wstring& condition);

	/** 
	 * Remove all
	 */
	void removeAll();

	GUINodeConditions();
};
