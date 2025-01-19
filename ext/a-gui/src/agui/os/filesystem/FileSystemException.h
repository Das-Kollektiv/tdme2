#pragma once

#include <agui/agui.h>
#include <agui/os/filesystem/fwd-agui.h>
#include <agui/utilities/fwd-agui.h>
#include <agui/utilities/ExceptionBase.h>

/**
 * File system exception
 * @author Andreas Drewke
 */
class agui::os::filesystem::FileSystemException: public agui::utilities::ExceptionBase
{
public:

	/**
	 * @brief Public constructor
	 * @param message message Exception message
	 */
	FileSystemException(const string& message) throw();

};
