#include <span>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/FileSystemMethods.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/os/filesystem/FileSystem.h>
#include <miniscript/utilities/Console.h>
#include <miniscript/utilities/Exception.h>

using std::span;

using miniscript::miniscript::FileSystemMethods;

using miniscript::miniscript::MiniScript;
using miniscript::os::filesystem::FileSystem;
using miniscript::utilities::Console;
using miniscript::utilities::Exception;

void FileSystemMethods::registerMethods(MiniScript* miniScript) {
	// file system methods
	{
		//
		class ScriptFileSystemComposeFileName: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptFileSystemComposeFileName(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.composeURI";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string pathName;
				string fileName;
				if (MiniScript::getStringValue(arguments, 0, pathName, false) == true &&
					MiniScript::getStringValue(arguments, 1, fileName, false) == true) {
					returnValue.setValue(FileSystem::composeURI(pathName, fileName));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptFileSystemComposeFileName(miniScript));
	}
	{
		//
		class ScriptFileSystemGetFileSize: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptFileSystemGetFileSize(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_INTEGER,
					true
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.getFileSize";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string pathName;
				string fileName;
				if (MiniScript::getStringValue(arguments, 0, pathName, false) == true &&
					MiniScript::getStringValue(arguments, 1, fileName, false) == true) {
					try {
						returnValue.setValue(static_cast<int64_t>(FileSystem::getFileSize(pathName, fileName)));
					} catch (Exception& exception) {
						Console::println("An error occurred: " + string(exception.what()));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptFileSystemGetFileSize(miniScript));
	}
	{
		//
		class ScriptFileSystemGetContentAsString: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptFileSystemGetContentAsString(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_STRING,
					true
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.getContentAsString";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string pathName;
				string fileName;
				if (MiniScript::getStringValue(arguments, 0, pathName, false) == true &&
					MiniScript::getStringValue(arguments, 1, fileName, false) == true) {
					try {
						returnValue.setValue(FileSystem::getContentAsString(pathName, fileName));
					} catch (Exception& exception) {
						Console::println("An error occurred: " + string(exception.what()));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptFileSystemGetContentAsString(miniScript));
	}
	{
		//
		class ScriptFileSystemSetContentFromString: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptFileSystemSetContentFromString(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "content", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.setContentFromString";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string pathName;
				string fileName;
				string content;
				if (MiniScript::getStringValue(arguments, 0, pathName, false) == true &&
					MiniScript::getStringValue(arguments, 1, fileName, false) == true &&
					MiniScript::getStringValue(arguments, 2, content, false) == true) {
					try {
						FileSystem::setContentFromString(pathName, fileName, content);
						returnValue.setValue(true);
					} catch (Exception& exception) {
						returnValue.setValue(false);
						Console::println("An error occurred: " + string(exception.what()));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptFileSystemSetContentFromString(miniScript));
	}
	{
		//
		class ScriptFileSystemGetContent: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptFileSystemGetContent(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_BYTEARRAY,
					true
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.getContent";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string pathName;
				string fileName;
				if (MiniScript::getStringValue(arguments, 0, pathName, false) == true &&
					MiniScript::getStringValue(arguments, 1, fileName, false) == true) {
					try {
						vector<uint8_t> content;
						FileSystem::getContent(pathName, fileName, content);
						returnValue.setValue(content);
					} catch (Exception& exception) {
						Console::println("An error occurred: " + string(exception.what()));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptFileSystemGetContent(miniScript));
	}
	{
		//
		class ScriptFileSystemSetContent: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptFileSystemSetContent(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "content", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.setContent";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string pathName;
				string fileName;
				if (arguments.size() == 3 &&
					MiniScript::getStringValue(arguments, 0, pathName, false) == true &&
					MiniScript::getStringValue(arguments, 1, fileName, false) == true) {
					try {
						auto contentPtr = arguments[2].getByteArrayPointer();
						if (contentPtr == nullptr) throw ExceptionBase("Empty content byte array provided");
						FileSystem::setContent(pathName, fileName, *contentPtr);
						returnValue.setValue(true);
					} catch (Exception& exception) {
						returnValue.setValue(false);
						Console::println("An error occurred: " + string(exception.what()));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptFileSystemSetContent(miniScript));
	}
	{
		//
		class ScriptFileSystemGetContentAsStringArray: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptFileSystemGetContentAsStringArray(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_ARRAY,
					true
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.getContentAsStringArray";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string pathName;
				string fileName;
				if (MiniScript::getStringValue(arguments, 0, pathName, false) == true &&
					MiniScript::getStringValue(arguments, 1, fileName, false) == true) {
					vector<string> contentAsStringArray;
					try {
						FileSystem::getContentAsStringArray(pathName, fileName, contentAsStringArray);
						//
						returnValue.setType(MiniScript::TYPE_ARRAY);
						for (const auto& contentAsStringArrayEntry: contentAsStringArray) {
							returnValue.pushArrayEntry(contentAsStringArrayEntry);
						}
					} catch (Exception& exception) {
						Console::println("An error occurred: " + string(exception.what()));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptFileSystemGetContentAsStringArray(miniScript));
	}
	{
		//
		class ScriptFileSystemSetContentFromStringArray: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptFileSystemSetContentFromStringArray(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_ARRAY, .name = "content", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.setContentFromStringArray";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string pathName;
				string fileName;
				if (arguments.size() == 3 &&
					MiniScript::getStringValue(arguments, 0, pathName, false) == true &&
					MiniScript::getStringValue(arguments, 1, fileName, false) == true &&
					arguments[2].getType() == MiniScript::TYPE_ARRAY) {
					vector<string> contentAsStringArray;
					auto arrayPointer = arguments[2].getArrayPointer();
					if (arrayPointer != nullptr) for (const auto arrayEntry: *arrayPointer) contentAsStringArray.push_back(arrayEntry->getValueAsString());
					try {
						FileSystem::setContentFromStringArray(pathName, fileName, contentAsStringArray);
						returnValue.setValue(true);
					} catch (Exception& exception) {
						returnValue.setValue(false);
						Console::println("An error occurred: " + string(exception.what()));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptFileSystemSetContentFromStringArray(miniScript));
	}
	{
		//
		class ScriptFileSystemIsPath: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptFileSystemIsPath(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "uri", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_BOOLEAN,
					true
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.isPath";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string uri;
				if (MiniScript::getStringValue(arguments, 0, uri, false) == true) {
					try {
						returnValue.setValue(FileSystem::isPath(uri));
					} catch (Exception& exception) {
						Console::println("An error occurred: " + string(exception.what()));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptFileSystemIsPath(miniScript));
	}
	{
		//
		class ScriptFileSystemIsDrive: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptFileSystemIsDrive(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "uri", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.isDrive";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string uri;
				if (MiniScript::getStringValue(arguments, 0, uri, false) == true) {
					returnValue.setValue(FileSystem::isDrive(uri));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptFileSystemIsDrive(miniScript));
	}
	{
		class ScriptFileSystemFileExists: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptFileSystemFileExists(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "uri", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_BOOLEAN,
					true
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.exists";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string uri;
				if (MiniScript::getStringValue(arguments, 0, uri, false) == true) {
					try {
						returnValue.setValue(FileSystem::exists(uri));
					} catch (Exception& exception) {
						Console::println("An error occurred: " + string(exception.what()));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptFileSystemFileExists(miniScript));
	}
	{
		//
		class ScriptFileSystemGetCanonicalPath: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptFileSystemGetCanonicalPath(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_STRING,
					true
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.getCanonicalURI";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string pathName;
				string fileName;
				if (MiniScript::getStringValue(arguments, 0, pathName, false) == true &&
					MiniScript::getStringValue(arguments, 1, fileName, false) == true) {
					try {
						returnValue.setValue(FileSystem::getCanonicalURI(pathName, fileName));
					} catch (Exception& exception) {
						Console::println("An error occurred: " + string(exception.what()));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptFileSystemGetCanonicalPath(miniScript));
	}
	{
		//
		class ScriptFileSystemGetCurrentWorkingPathName: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptFileSystemGetCurrentWorkingPathName(MiniScript* miniScript):
				MiniScript::Method(
					{},
					MiniScript::TYPE_STRING,
					true
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.getCurrentWorkingPathName";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				try {
					returnValue.setValue(FileSystem::getCurrentWorkingPathName());
				} catch (Exception& exception) {
					Console::println("An error occurred: " + string(exception.what()));
				}
			}
		};
		miniScript->registerMethod(new ScriptFileSystemGetCurrentWorkingPathName(miniScript));
	}
	{
		//
		class ScriptFileSystemChangePath: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptFileSystemChangePath(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.changePath";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string pathName;
				if (MiniScript::getStringValue(arguments, 0, pathName, false) == true) {
					try {
						FileSystem::changePath(pathName);
						returnValue.setValue(true);
					} catch (Exception& exception) {
						returnValue.setValue(false);
						Console::println("An error occurred: " + string(exception.what()));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptFileSystemChangePath(miniScript));
	}
	{
		//
		class ScriptFileSystemGetFileName: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptFileSystemGetFileName(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "uri", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.getFileName";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string uri;
				if (MiniScript::getStringValue(arguments, 0, uri, false) == true) {
					returnValue.setValue(FileSystem::getFileName(uri));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptFileSystemGetFileName(miniScript));
	}
	{
		//
		class ScriptFileSystemGetPathName: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptFileSystemGetPathName(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "uri", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.getPathName";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string uri;
				if (MiniScript::getStringValue(arguments, 0, uri, false) == true) {
					returnValue.setValue(FileSystem::getPathName(uri));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptFileSystemGetPathName(miniScript));
	}
	{
		//
		class ScriptFileSystemRemoveFileExtension: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptFileSystemRemoveFileExtension(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.removeFileExtension";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string fileName;
				if (MiniScript::getStringValue(arguments, 0, fileName, false) == true) {
					returnValue.setValue(FileSystem::removeFileExtension(fileName));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptFileSystemRemoveFileExtension(miniScript));
	}
	{
		//
		class ScriptFileSystemRemoveFile: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptFileSystemRemoveFile(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.removeFile";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string pathName;
				string fileName;
				if (MiniScript::getStringValue(arguments, 0, pathName, false) == true &&
					MiniScript::getStringValue(arguments, 1, fileName, false) == true) {
					try {
						FileSystem::removeFile(pathName, fileName);
						returnValue.setValue(true);
					} catch (Exception& exception) {
						returnValue.setValue(false);
						Console::println("An error occurred: " + string(exception.what()));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptFileSystemRemoveFile(miniScript));
	}
	{
		//
		class ScriptFileSystemCreatePath: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptFileSystemCreatePath(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.createPath";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string pathName;
				if (MiniScript::getStringValue(arguments, 0, pathName, false) == true) {
					try {
						FileSystem::createPath(pathName);
						returnValue.setValue(true);
					} catch (Exception& exception) {
						returnValue.setValue(false);
						Console::println("An error occurred: " + string(exception.what()));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptFileSystemCreatePath(miniScript));
	}
	{
		//
		class ScriptFileSystemRemovePath: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptFileSystemRemovePath(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "recursive", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.removePath";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string pathName;
				bool recursive;
				if (MiniScript::getStringValue(arguments, 0, pathName, false) == true &&
					MiniScript::getBooleanValue(arguments, 1, recursive, false) == true) {
					try {
						FileSystem::removePath(pathName, recursive);
						returnValue.setValue(true);
					} catch (Exception& exception) {
						returnValue.setValue(false);
						Console::println("An error occurred: " + string(exception.what()));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptFileSystemRemovePath(miniScript));
	}
	{
		//
		class ScriptFileSystemRename: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptFileSystemRename(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "fileNameFrom", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "fileNameTo", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.rename";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string fileNameFrom;
				string fileNameTo;
				if (MiniScript::getStringValue(arguments, 0, fileNameFrom, false) == true &&
					MiniScript::getStringValue(arguments, 1, fileNameTo, false) == true) {
					try {
						FileSystem::rename(fileNameFrom, fileNameTo);
						returnValue.setValue(true);
					} catch (Exception& exception) {
						returnValue.setValue(false);
						Console::println("An error occurred: " + string(exception.what()));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptFileSystemRename(miniScript));
	}
	{
		//
		class ScriptFileSystemMove: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptFileSystemMove(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "uriFrom", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "uriTo", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.move";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string fileNameFrom;
				string fileNameTo;
				if (MiniScript::getStringValue(arguments, 0, fileNameFrom, false) == true &&
					MiniScript::getStringValue(arguments, 1, fileNameTo, false) == true) {
					try {
						FileSystem::rename(fileNameFrom, fileNameTo);
						returnValue.setValue(true);
					} catch (Exception& exception) {
						returnValue.setValue(false);
						Console::println("An error occurred: " + string(exception.what()));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptFileSystemMove(miniScript));
	}
	{
		//
		class ScriptFileSystemList: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptFileSystemList(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_ARRAY,
					true
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.list";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string pathName;
				if (MiniScript::getStringValue(arguments, 0, pathName, false) == true) {
					try {
						vector<string> files;
						FileSystem::list(pathName, files);
						//
						returnValue.setType(MiniScript::TYPE_ARRAY);
						for (const auto& file: files) {
							returnValue.pushArrayEntry(file);
						}
					} catch (Exception& exception) {
						Console::println("An error occurred: " + string(exception.what()));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptFileSystemList(miniScript));
	}
}
