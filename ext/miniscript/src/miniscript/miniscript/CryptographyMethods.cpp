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

using _Base64 = miniscript::utilities::Base64;
using _Console = miniscript::utilities::Console;
using _SHA256 = miniscript::utilities::SHA256;
using _StringTools = miniscript::utilities::StringTools;

void CryptographyMethods::registerConstants(MiniScript* miniScript) {
}

void CryptographyMethods::registerMethods(MiniScript* miniScript) {
	// base64
	{
		//
		class MethodCryptographyBase64Encode: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodCryptographyBase64Encode(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "value", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "cryptography.base64.encode";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string value;
				if (MiniScript::getStringValue(arguments, 0, value, false) == true) {
					returnValue.setValue(_Base64::encode(value));
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodCryptographyBase64Encode(miniScript));
	}
	{
		//
		class MethodCryptographyBase64Decode: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodCryptographyBase64Decode(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "value", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "cryptography.base64.decode";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string value;
				if (MiniScript::getStringValue(arguments, 0, value, false) == true) {
					returnValue.setValue(_Base64::decode(value));
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodCryptographyBase64Decode(miniScript));
	}
	// sha256
	{
		//
		class MethodCryptographySHA256Encode: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodCryptographySHA256Encode(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "value", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "cryptography.sha256.encode";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string value;
				if (MiniScript::getStringValue(arguments, 0, value, false) == true) {
					returnValue.setValue(_SHA256::encode(value));
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodCryptographySHA256Encode(miniScript));
	}
}
