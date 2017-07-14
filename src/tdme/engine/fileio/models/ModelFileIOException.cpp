#include <tdme/engine/fileio/models/ModelFileIOException.h>

#include <tdme/utils/_ExceptionBase.h>

using tdme::engine::fileio::models::ModelFileIOException;

using tdme::utils::_ExceptionBase;

ModelFileIOException::ModelFileIOException(const string& message) throw() : _ExceptionBase(message) {
}
