#pragma once

#include <memory>
#include <span>
#include <vector>

#include <miniscript/miniscript/MiniScript.h>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/fwd-miniscript.h>
#include <miniscript/network/httpclient/HTTPDownloadClient.h>

using std::shared_ptr;
using std::span;
using std::vector;

using miniscript::miniscript::MiniScript;
using _HTTPDownloadClient = miniscript::network::httpclient::HTTPDownloadClient;

/**
 * HTTP download client
 * @author Andreas Drewke
 */
class miniscript::miniscript::HTTPDownloadClientClass final: public MiniScript::DataType {
private:
	MINISCRIPT_STATIC_DLL_IMPEXT static const string TYPE_NAME;
	MINISCRIPT_STATIC_DLL_IMPEXT static vector<shared_ptr<_HTTPDownloadClient>> instances;

	// overridden methods
	void registerConstants(MiniScript* miniScript) const override;
	void registerMethods(MiniScript* miniScript) const override;
	void unsetVariableValue(MiniScript::Variable& variable) const override;
	void setVariableValue(MiniScript::Variable& variable) const override;
	void setVariableValue(MiniScript::Variable& variable, const void* value) const override;
	void copyVariable(MiniScript::Variable& to, const MiniScript::Variable& from) const override;
	bool mul(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const override;
	bool div(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const override;
	bool add(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const override;
	bool sub(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const override;

public:
	// forbid class copy
	FORBID_CLASS_COPY(HTTPDownloadClientClass)

	/**
	 * Initialize
	 */
	static void initialize();

	/**
	 * Get HTTPDownloadClient value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	static inline bool getHTTPDownloadClientValue(const span<MiniScript::Variable>& arguments, int idx, shared_ptr<_HTTPDownloadClient>& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		const auto& argument = arguments[idx];
		if (argument.getType() == MiniScript::TYPE_HTTPDOWNLOADCLIENT) {
			value = *static_cast<shared_ptr<_HTTPDownloadClient>*>(argument.getValuePtr());
			return true;
		}
		return optional;

	}

	/**
	 * MiniScript Vector2 data type
	 */
	HTTPDownloadClientClass(): MiniScript::DataType(false) {
		//
	}

	// overridden methods
	const string& getTypeAsString() const override;
	const string getValueAsString(const MiniScript::Variable& variable) const override;

};
