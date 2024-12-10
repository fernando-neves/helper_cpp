/* THIS PROJECT INCLUDES */
#include "../includes/helper_filesystem.hpp"

namespace helper::filesystem
{
	std::string get_binary_name(const std::string& full_path)
	{
		// Find the last occurrence of the path separator
		const size_t pos = full_path.find_last_of("/\\");
		if (pos == std::string::npos)
		{
			// If no path separator is found, return the full path as the process name
			return full_path;
		}
		// Return the substring after the last path separator
		return full_path.substr(pos + 1);
	}
}
