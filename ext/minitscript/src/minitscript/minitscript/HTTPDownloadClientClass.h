#pragma once

#include <memory>
#include <span>
#include <vector>

#include <minitscript/minitscript/MinitScript.h>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/fwd-minitscript.h>
#include <minitscript/network/httpclient/HTTPDownloadClient.h>

using std::shared_ptr;
using std::span;
using std::vector;

// namespaces
namespace minitscript {
namespace minitscript {
	using ::minitscript::network::httpclient::HTTPDownloadClient;
}
}

/**
 * HTTP download client
 * @author Andreas Drewke
 */
class minitscript::minitscript::HTTPDownloadClientClass final: public MinitScript::DataType {
private:
	MINITSCRIPT_STATIC_DLL_IMPEXT static const string TYPE_NAME;

	// overridden methods
	void registerConstants(MinitScript* minitScript) const override;
	void registerMethods(MinitScript* minitScript) const override;
	void unsetVariableValue(MinitScript::Variable& variable) const override;
	void setVariableValue(MinitScript::Variable& variable) const override;
	void setVariableValue(MinitScript::Variable& variable, const void* value) const override;
	void copyVariable(MinitScript::Variable& to, const MinitScript::Variable& from) const override;
	bool mul(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const override;
	bool div(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const override;
	bool add(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const override;
	bool sub(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const override;
	DataType::ScriptContext* createScriptContext() const override;
	void deleteScriptContext(DataType::ScriptContext* context) const override;
	void garbageCollection(DataType::ScriptContext* context) const override;

public:
	/**
	 * Script context
	 */
	class HTTPDownloadClientClassScriptContext final: public ScriptContext {
		public:
			/**
			 * Constructor
			 */
			HTTPDownloadClientClassScriptContext() {}

			/**
			 * @return instances
			 */
			inline vector<shared_ptr<HTTPDownloadClient>>& getInstances() {
				return instances;
			}
		private:
			vector<shared_ptr<HTTPDownloadClient>> instances;
	};

	// forbid class copy
	_FORBID_CLASS_COPY(HTTPDownloadClientClass)

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
	static inline bool getHTTPDownloadClientValue(const span<MinitScript::Variable>& arguments, int idx, shared_ptr<HTTPDownloadClient>& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		const auto& argument = arguments[idx];
		if (argument.getType() == MinitScript::TYPE_HTTPDOWNLOADCLIENT) {
			value = *static_cast<shared_ptr<HTTPDownloadClient>*>(argument.getValuePtr());
			return true;
		}
		return optional;

	}

	/**
	 * MinitScript HTTP download client class
	 */
	HTTPDownloadClientClass(): MinitScript::DataType(false, true) {
		//
	}

	// overridden methods
	const string& getTypeAsString() const override;
	const string getValueAsString(const MinitScript::Variable& variable) const override;

};
