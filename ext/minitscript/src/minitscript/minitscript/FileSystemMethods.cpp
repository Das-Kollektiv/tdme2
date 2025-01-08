#include <span>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/FileSystemMethods.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/os/filesystem/FileSystem.h>
#include <minitscript/utilities/Console.h>
#include <minitscript/utilities/Exception.h>
#include <minitscript/utilities/ExceptionBase.h>

using std::span;

using minitscript::minitscript::FileSystemMethods;

using minitscript::minitscript::MinitScript;

using _FileSystem = minitscript::os::filesystem::FileSystem;
using _Console = minitscript::utilities::Console;
using _Exception = minitscript::utilities::Exception;
using _ExceptionBase = minitscript::utilities::ExceptionBase;

void FileSystemMethods::registerConstants(MinitScript* minitScript) {
}

void FileSystemMethods::registerMethods(MinitScript* minitScript) {
	// file system methods
	{
		//
		class ScriptFileSystemComposeFileName: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			ScriptFileSystemComposeFileName(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_STRING,
					false
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.composeURI";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string pathName;
				string fileName;
				if (arguments.size() == 2 &&
					MinitScript::getStringValue(arguments, 0, pathName) == true &&
					MinitScript::getStringValue(arguments, 1, fileName) == true) {
					returnValue.setValue(_FileSystem::composeURI(pathName, fileName));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new ScriptFileSystemComposeFileName(minitScript));
	}
	{
		//
		class ScriptFileSystemGetFileSize: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			ScriptFileSystemGetFileSize(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_INTEGER,
					false,
					true
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.getFileSize";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string pathName;
				string fileName;
				if (arguments.size() == 2 &&
					MinitScript::getStringValue(arguments, 0, pathName) == true &&
					MinitScript::getStringValue(arguments, 1, fileName) == true) {
					try {
						returnValue.setValue(static_cast<int64_t>(_FileSystem::getFileSize(pathName, fileName)));
					} catch (_Exception& exception) {
						minitScript->_throw(string(exception.what()));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new ScriptFileSystemGetFileSize(minitScript));
	}
	{
		//
		class ScriptFileSystemGetFileTimeStamp: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			ScriptFileSystemGetFileTimeStamp(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_INTEGER,
					false,
					true
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.getFileTimeStamp";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string pathName;
				string fileName;
				if (arguments.size() == 2 &&
					MinitScript::getStringValue(arguments, 0, pathName) == true &&
					MinitScript::getStringValue(arguments, 1, fileName) == true) {
					try {
						returnValue.setValue(static_cast<int64_t>(_FileSystem::getFileTimeStamp(pathName, fileName)));
					} catch (_Exception& exception) {
						minitScript->_throw(string(exception.what()));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new ScriptFileSystemGetFileTimeStamp(minitScript));
	}
	{
		//
		class ScriptFileSystemGetContentAsString: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			ScriptFileSystemGetContentAsString(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_STRING,
					false,
					true
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.getContentAsString";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string pathName;
				string fileName;
				if (arguments.size() == 2 &&
					MinitScript::getStringValue(arguments, 0, pathName) == true &&
					MinitScript::getStringValue(arguments, 1, fileName) == true) {
					try {
						returnValue.setValue(_FileSystem::getContentAsString(pathName, fileName));
					} catch (_Exception& exception) {
						minitScript->_throw(string(exception.what()));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new ScriptFileSystemGetContentAsString(minitScript));
	}
	{
		//
		class ScriptFileSystemSetContentFromString: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			ScriptFileSystemSetContentFromString(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "content", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_NULL,
					false,
					true
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.setContentFromString";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string pathName;
				string fileName;
				string content;
				if (arguments.size() == 3 &&
					MinitScript::getStringValue(arguments, 0, pathName) == true &&
					MinitScript::getStringValue(arguments, 1, fileName) == true &&
					MinitScript::getStringValue(arguments, 2, content) == true) {
					try {
						_FileSystem::setContentFromString(pathName, fileName, content);
					} catch (_Exception& exception) {
						minitScript->_throw(string(exception.what()));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new ScriptFileSystemSetContentFromString(minitScript));
	}
	{
		//
		class ScriptFileSystemGetContent: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			ScriptFileSystemGetContent(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_BYTEARRAY,
					false,
					true
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.getContent";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string pathName;
				string fileName;
				if (arguments.size() == 2 &&
					MinitScript::getStringValue(arguments, 0, pathName) == true &&
					MinitScript::getStringValue(arguments, 1, fileName) == true) {
					try {
						vector<uint8_t> content;
						_FileSystem::getContent(pathName, fileName, content);
						returnValue.setValue(content);
					} catch (_Exception& exception) {
						minitScript->_throw(string(exception.what()));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new ScriptFileSystemGetContent(minitScript));
	}
	{
		//
		class ScriptFileSystemSetContent: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			ScriptFileSystemSetContent(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_BYTEARRAY, .name = "content", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_NULL,
					false,
					true
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.setContent";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string pathName;
				string fileName;
				if (arguments.size() == 3 &&
					MinitScript::getStringValue(arguments, 0, pathName, false) == true &&
					MinitScript::getStringValue(arguments, 1, fileName, false) == true) {
					try {
						auto contentPtr = arguments[2].getByteArrayPointer();
						if (contentPtr == nullptr) throw _ExceptionBase("Empty content byte array provided");
						_FileSystem::setContent(pathName, fileName, *contentPtr);
					} catch (_Exception& exception) {
						minitScript->_throw(string(exception.what()));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new ScriptFileSystemSetContent(minitScript));
	}
	{
		//
		class ScriptFileSystemGetContentAsStringArray: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			ScriptFileSystemGetContentAsStringArray(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_ARRAY,
					false,
					true
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.getContentAsStringArray";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string pathName;
				string fileName;
				if (arguments.size() == 2 &&
					MinitScript::getStringValue(arguments, 0, pathName) == true &&
					MinitScript::getStringValue(arguments, 1, fileName) == true) {
					vector<string> contentAsStringArray;
					try {
						_FileSystem::getContentAsStringArray(pathName, fileName, contentAsStringArray);
						//
						returnValue.setType(MinitScript::TYPE_ARRAY);
						for (const auto& contentAsStringArrayEntry: contentAsStringArray) {
							returnValue.pushArrayEntry(contentAsStringArrayEntry);
						}
					} catch (_Exception& exception) {
						minitScript->_throw(string(exception.what()));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new ScriptFileSystemGetContentAsStringArray(minitScript));
	}
	{
		//
		class ScriptFileSystemSetContentFromStringArray: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			ScriptFileSystemSetContentFromStringArray(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_ARRAY, .name = "content", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_NULL,
					false,
					true
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.setContentFromStringArray";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string pathName;
				string fileName;
				if (arguments.size() == 3 &&
					MinitScript::getStringValue(arguments, 0, pathName) == true &&
					MinitScript::getStringValue(arguments, 1, fileName) == true &&
					arguments[2].getType() == MinitScript::TYPE_ARRAY) {
					vector<string> contentAsStringArray;
					auto arrayPointer = arguments[2].getArrayPointer();
					if (arrayPointer != nullptr) for (const auto arrayEntry: *arrayPointer) contentAsStringArray.push_back(arrayEntry->getValueAsString());
					try {
						_FileSystem::setContentFromStringArray(pathName, fileName, contentAsStringArray);
					} catch (_Exception& exception) {
						minitScript->_throw(string(exception.what()));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new ScriptFileSystemSetContentFromStringArray(minitScript));
	}
	{
		//
		class ScriptFileSystemIsPath: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			ScriptFileSystemIsPath(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "uri", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_BOOLEAN,
					false,
					true
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.isPath";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string uri;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, uri, false) == true) {
					try {
						returnValue.setValue(_FileSystem::isPath(uri));
					} catch (_Exception& exception) {
						minitScript->_throw(string(exception.what()));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new ScriptFileSystemIsPath(minitScript));
	}
	{
		//
		class ScriptFileSystemIsDrive: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			ScriptFileSystemIsDrive(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "uri", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_BOOLEAN
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.isDrive";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string uri;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, uri) == true) {
					returnValue.setValue(_FileSystem::isDrive(uri));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new ScriptFileSystemIsDrive(minitScript));
	}
	{
		class ScriptFileSystemFileExists: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			ScriptFileSystemFileExists(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "uri", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_BOOLEAN,
					false,
					true
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.exists";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string uri;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, uri) == true) {
					try {
						returnValue.setValue(_FileSystem::exists(uri));
					} catch (_Exception& exception) {
						minitScript->_throw(string(exception.what()));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new ScriptFileSystemFileExists(minitScript));
	}
	{
		//
		class ScriptFileSystemGetCanonicalPath: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			ScriptFileSystemGetCanonicalPath(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.getCanonicalURI";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string pathName;
				string fileName;
				if (arguments.size() == 2 &&
					MinitScript::getStringValue(arguments, 0, pathName) == true &&
					MinitScript::getStringValue(arguments, 1, fileName) == true) {
					try {
						returnValue.setValue(_FileSystem::getCanonicalURI(pathName, fileName));
					} catch (_Exception& exception) {
						minitScript->_throw(string(exception.what()));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new ScriptFileSystemGetCanonicalPath(minitScript));
	}
	{
		//
		class ScriptFileSystemGetCurrentWorkingPathName: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			ScriptFileSystemGetCurrentWorkingPathName(MinitScript* minitScript):
				MinitScript::Method(
					{},
					MinitScript::TYPE_STRING,
					false,
					true
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.getCurrentWorkingPathName";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 0) {
					try {
						returnValue.setValue(_FileSystem::getCurrentWorkingPathName());
					} catch (_Exception& exception) {
						minitScript->_throw(string(exception.what()));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new ScriptFileSystemGetCurrentWorkingPathName(minitScript));
	}
	{
		//
		class ScriptFileSystemChangePath: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			ScriptFileSystemChangePath(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_NULL,
					false,
					true
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.changePath";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string pathName;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, pathName) == true) {
					try {
						_FileSystem::changePath(pathName);
					} catch (_Exception& exception) {
						minitScript->_throw(string(exception.what()));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new ScriptFileSystemChangePath(minitScript));
	}
	{
		//
		class ScriptFileSystemGetFileName: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			ScriptFileSystemGetFileName(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "uri", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.getFileName";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string uri;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, uri) == true) {
					returnValue.setValue(_FileSystem::getFileName(uri));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new ScriptFileSystemGetFileName(minitScript));
	}
	{
		//
		class ScriptFileSystemGetPathName: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			ScriptFileSystemGetPathName(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "uri", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.getPathName";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string uri;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, uri) == true) {
					returnValue.setValue(_FileSystem::getPathName(uri));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new ScriptFileSystemGetPathName(minitScript));
	}
	{
		//
		class ScriptFileSystemRemoveFileExtension: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			ScriptFileSystemRemoveFileExtension(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.removeFileExtension";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string fileName;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, fileName) == true) {
					returnValue.setValue(_FileSystem::removeFileExtension(fileName));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new ScriptFileSystemRemoveFileExtension(minitScript));
	}
	{
		//
		class ScriptFileSystemRemoveFile: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			ScriptFileSystemRemoveFile(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_NULL,
					false,
					true
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.removeFile";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string pathName;
				string fileName;
				if (arguments.size() == 2 &&
					MinitScript::getStringValue(arguments, 0, pathName) == true &&
					MinitScript::getStringValue(arguments, 1, fileName) == true) {
					try {
						_FileSystem::removeFile(pathName, fileName);
					} catch (_Exception& exception) {
						minitScript->_throw(string(exception.what()));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new ScriptFileSystemRemoveFile(minitScript));
	}
	{
		//
		class ScriptFileSystemCreatePath: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			ScriptFileSystemCreatePath(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_NULL,
					false,
					true
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.createPath";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string pathName;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, pathName) == true) {
					try {
						_FileSystem::createPath(pathName);
					} catch (_Exception& exception) {
						minitScript->_throw(string(exception.what()));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new ScriptFileSystemCreatePath(minitScript));
	}
	{
		//
		class ScriptFileSystemRemovePath: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			ScriptFileSystemRemovePath(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_BOOLEAN, .name = "recursive", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_NULL,
					false,
					true
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.removePath";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string pathName;
				bool recursive;
				if (arguments.size() == 2 &&
					MinitScript::getStringValue(arguments, 0, pathName) == true &&
					MinitScript::getBooleanValue(arguments, 1, recursive) == true) {
					try {
						_FileSystem::removePath(pathName, recursive);
					} catch (_Exception& exception) {
						minitScript->_throw(string(exception.what()));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new ScriptFileSystemRemovePath(minitScript));
	}
	{
		//
		class ScriptFileSystemRename: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			ScriptFileSystemRename(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "fileNameFrom", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "fileNameTo", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_NULL,
					false,
					true
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.rename";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string fileNameFrom;
				string fileNameTo;
				if (arguments.size() == 2 &&
					MinitScript::getStringValue(arguments, 0, fileNameFrom) == true &&
					MinitScript::getStringValue(arguments, 1, fileNameTo) == true) {
					try {
						_FileSystem::rename(fileNameFrom, fileNameTo);
					} catch (_Exception& exception) {
						minitScript->_throw(string(exception.what()));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new ScriptFileSystemRename(minitScript));
	}
	{
		//
		class ScriptFileSystemMove: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			ScriptFileSystemMove(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "uriFrom", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "uriTo", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_NULL,
					false,
					true
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.move";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string fileNameFrom;
				string fileNameTo;
				if (arguments.size() == 2 &&
					MinitScript::getStringValue(arguments, 0, fileNameFrom) == true &&
					MinitScript::getStringValue(arguments, 1, fileNameTo) == true) {
					try {
						_FileSystem::rename(fileNameFrom, fileNameTo);
					} catch (_Exception& exception) {
						minitScript->_throw(string(exception.what()));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new ScriptFileSystemMove(minitScript));
	}
	{
		//
		class ScriptFileSystemList: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			ScriptFileSystemList(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_ARRAY,
					false,
					true
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "filesystem.list";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string pathName;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, pathName, false) == true) {
					try {
						vector<string> files;
						_FileSystem::list(pathName, files);
						//
						returnValue.setType(MinitScript::TYPE_ARRAY);
						for (const auto& file: files) {
							returnValue.pushArrayEntry(file);
						}
					} catch (_Exception& exception) {
						minitScript->_throw(string(exception.what()));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new ScriptFileSystemList(minitScript));
	}
}
