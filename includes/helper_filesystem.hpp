#ifndef HELPER_FILESYSTEM_H
#define HELPER_FILESYSTEM_H

/* C++ INCLUDES */
#include <string>

namespace helper::filesystem
{
	/**
	 * Extracts the binary name from a full file path.
	 *
	 * This function takes a full file path as input and extracts the binary name (i.e., the file name) from it.
	 * It searches for the last occurrence of a path separator ('/' or '\\') and returns the substring that follows it.
	 * If no path separator is found, the function returns the full path as the binary name.
	 *
	 * @param full_path The full file path from which to extract the binary name.
	 * @return A string containing the binary name extracted from the full file path. If no path separator is found,
	 *         the full path is returned as the binary name.
	 */
	std::string get_binary_name(const std::string& full_path);
}

#endif // !HELPER_FILESYSTEM_H
