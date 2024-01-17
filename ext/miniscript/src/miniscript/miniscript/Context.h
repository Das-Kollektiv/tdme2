#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/fwd-miniscript.h>

using std::string;
using std::unordered_map;
using std::vector;

using miniscript::miniscript::MiniScript;

/** 
 * Scripts context
 * @author Andreas Drewke
 */
class miniscript::miniscript::Context
{
private:
	unordered_map<string, MiniScript*> scriptsById;
	vector<MiniScript*> scriptCallStack;
	vector<string> argumentValues;
	int exitCode { 0 };

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
	 * Set argument values
	 * @param argumentValues argument values
	 */
	inline void setArgumentValues(const vector<string>& argumentValues) {
		this->argumentValues = argumentValues;
	}

	/**
	 * @return argument values
	 */
	inline const vector<string>& getArgumentValues() {
		return argumentValues;
	}

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

	/**
	 * Add to script call stack
	 * @param script script
	 */
	inline void push(MiniScript* script) {
		scriptCallStack.push_back(script);
	}

	/**
	 * Remove from script call stack
	 */
	inline void pop() {
		scriptCallStack.erase(scriptCallStack.begin() + scriptCallStack.size() - 1);
	}

	/**
	 * Set exit code
	 * @param exitCode exit code
	 */
	inline void setExitCode(int exitCode) {
		this->exitCode = exitCode;
	}

	/**
	 * @return exit code
	 */
	inline int getExitCode() {
		return exitCode;
	}

};
