#include <span>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/CryptographyMethods.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/utilities/Base64.h>
#include <minitscript/utilities/Console.h>
#include <minitscript/utilities/SHA256.h>
#include <minitscript/utilities/StringTools.h>

using std::span;

using minitscript::minitscript::CryptographyMethods;

using minitscript::minitscript::MinitScript;

using _Base64 = minitscript::utilities::Base64;
using _Console = minitscript::utilities::Console;
using _SHA256 = minitscript::utilities::SHA256;
using _StringTools = minitscript::utilities::StringTools;

void CryptographyMethods::registerConstants(MinitScript* minitScript) {
}

void CryptographyMethods::registerMethods(MinitScript* minitScript) {
	// base64
	{
		//
		class MethodCryptographyBase64Encode: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodCryptographyBase64Encode(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "value", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "cryptography.base64.encode";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string value;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, value) == true) {
					returnValue.setValue(_Base64::encode(value));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodCryptographyBase64Encode(minitScript));
	}
	{
		//
		class MethodCryptographyBase64Decode: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodCryptographyBase64Decode(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "value", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "cryptography.base64.decode";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string value;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, value) == true) {
					returnValue.setValue(_Base64::decode(value));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodCryptographyBase64Decode(minitScript));
	}
	// sha256
	{
		//
		class MethodCryptographySHA256Encode: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodCryptographySHA256Encode(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "value", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "cryptography.sha256.encode";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string value;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, value) == true) {
					returnValue.setValue(_SHA256::encode(value));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodCryptographySHA256Encode(minitScript));
	}
}
