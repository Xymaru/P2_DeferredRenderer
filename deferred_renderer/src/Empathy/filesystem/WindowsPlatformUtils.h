#pragma once
#include <string>

namespace EM
{
	class FileDialogs
	{
	public:
		/* Opens a file dialog in open mode
		* returns the file path that's opened, empty when cancelled
		*/
		static std::string OpenFile(const char* filter);

		/* Opens a file dialog in save mode
		* returns the file path that's opened, empty when cancelled
		*/
		static std::string SaveFile(const char* filter);

		/* Opens a directory dialog to select a directory
		* returns the directory path selected, empty when cancelled
		*/
		static std::string SelectFolder();

		/*
		* Gets the documents folder for the current machine
		*/
		static std::string GetDocumentsFolder();

		/*
		* Get the default location for projects
		*/
		static std::string GetDefaultProjectPath();

		/*
		 *Opens a file using the default application of the system
		 */
		static void OpenDefaultFile(const char* path);
	};
}