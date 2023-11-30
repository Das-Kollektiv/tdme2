#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/fwd-miniscript.h>

using std::string;
using std::unordered_map;
using std::vector;

/** 
 * Scripts context
 * @author Andreas Drewke
 */
class miniscript::miniscript::Context
{
public:
	static constexpr bool VERBOSE { false };

private:
	unordered_map<string, MiniScript*> scriptsById;

public:
	// forbid class copy
	FORBID_CLASS_COPY(Context)

	/**
	 * Public constructor
	 */
	Context();

	/**
	 * Destructor
	 */
	virtual ~Context();

	/**
	 * Add script
	 * @param id id
	 * @param script script
	 */
	void addScript(const string& id, MiniScript* script);

	/**
	 * Remove script
	 * @param id id
	 */
	void removeScript(const string& id);

	/**
	 * Get script
	 * @param id id
	 * @return script or nullptr
	 */
	inline MiniScript* getScript(const string& id) {
		auto scriptsIt = scriptsById.find(id);
		return scriptsIt != scriptsById.end()?scriptsIt->second:nullptr;
	}

	/**
	 * Get script ids
	 * @return script ids
	 */
	inline const vector<string> getScriptIds() {
		vector<string> result;
		for (const auto& [scriptId, script]: scriptsById) {
			result.push_back(scriptId);
		}
		return result;
	}

};
