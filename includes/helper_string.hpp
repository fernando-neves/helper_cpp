#ifndef HELPER_STRING_H
#define HELPER_STRING_H

/* C++ INCLUDES */
#include <string>

namespace helper::string
{
	/**
	 * Converts a wide string (std::wstring) to a narrow string (std::string) using UTF-8 encoding.
	 *
	 * This function takes a wide string as input and converts it to a narrow string using the UTF-8 encoding.
	 * It first determines the required size for the narrow string buffer by calling WideCharToMultiByte with
	 * a null destination buffer. If the required size is zero, it indicates an error, and the function returns
	 * an empty string.
	 *
	 * The function then allocates a narrow string buffer of the required size and performs the conversion by
	 * calling WideCharToMultiByte again with the allocated buffer. If the conversion fails, the function returns
	 * an empty string.
	 *
	 * @param wide_string The wide string (std::wstring) to be converted.
	 * @return A narrow string (std::string) containing the UTF-8 encoded representation of the input wide string.
	 *         If the conversion fails, an empty string is returned.
	 */
	std::string to_string(const std::wstring& wide_string);

	std::string to_lower(const std::string& input);
}
#endif // !HELPER_STRING_H