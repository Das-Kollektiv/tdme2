#include <tdme/engine/fileio/models/ModelFileIOException.h>

#include <tdme/utils/ExceptionBase.h>

using tdme::engine::fileio::models::ModelFileIOException;

using tdme::utils::ExceptionBase;

ModelFileIOException::ModelFileIOException(const string& message) throw() : ExceptionBase(message) {
}
