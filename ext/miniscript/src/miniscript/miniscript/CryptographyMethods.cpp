#include <span>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/CryptographyMethods.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/utilities/Base64.h>
#include <miniscript/utilities/Console.h>
#include <miniscript/utilities/SHA256.h>
#include <miniscript/utilities/StringTools.h>

using std::span;

using miniscript::miniscript::CryptographyMethods;

using miniscript::miniscript::MiniScript;
using miniscript::utilities::Base64;
using miniscript::utilities::Console;
using miniscript::utilities::SHA256;
using miniscript::utilities::StringTools;

void CryptographyMethods::registerMethods(MiniScript* miniScript) {
	// base64
	{
		//
		class ScriptMethodCryptographyBase64Encode: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodCryptographyBase64Encode(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "value", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "cryptography.base64.encode";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string value;
				if (MiniScript::getStringValue(argumentValues, 0, value, false) == true) {
					returnValue.setValue(Base64::encode(value));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodCryptographyBase64Encode(miniScript));
	}
	{
		//
		class ScriptMethodCryptographyBase64Decode: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodCryptographyBase64Decode(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "value", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "cryptography.base64.decode";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string value;
				if (MiniScript::getStringValue(argumentValues, 0, value, false) == true) {
					returnValue.setValue(Base64::decode(value));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodCryptographyBase64Decode(miniScript));
	}
	// sha256
	{
		//
		class ScriptMethodCryptographySHA256Encode: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodCryptographySHA256Encode(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "value", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "cryptography.sha256.encode";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string value;
				if (MiniScript::getStringValue(argumentValues, 0, value, false) == true) {
					returnValue.setValue(SHA256::encode(value));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodCryptographySHA256Encode(miniScript));
	}
}
