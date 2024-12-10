/* THIS PROJECT INCLUDES */
#include "../includes/helper_string.hpp"

/* C++ INCLUDES */
#include <algorithm>

/* WINDOWS INCLUDES */
#ifdef _WIN32
	#include <windows.h>
	#include <stringapiset.h>
#endif

namespace helper::string
{
	std::string to_string(const std::wstring& wide_string)
	{
		const int required_size =
			WideCharToMultiByte(CP_UTF8, 0, wide_string.c_str(), -1, nullptr, 0, nullptr, nullptr);
		if (required_size == 0)
		{
			// Handle error
			return "";
		}

		std::string str(required_size - 1, '\0');
		if (const int result = WideCharToMultiByte(CP_UTF8, 0, wide_string.c_str(), -1, str.data(), required_size,
		                                           nullptr, nullptr); result == 0)
		{
			// Handle error
			return "";
		}

		return str;
	}

	std::string to_lower(const std::string& input)
	{
		std::string output = input;
		std::ranges::transform(output, output.begin(),
		                       [](const unsigned char c) { return std::tolower(c); });
		return output;
	}
}
