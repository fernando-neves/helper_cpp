#include "../includes/helper_window.hpp"

#include <windows.h>

namespace helper::window
{
	uint32_t get_foreground_window_pid()
	{
		const HWND hwnd = GetForegroundWindow();
		if (hwnd == nullptr)
		{
			return -1;
		}

		DWORD process_id = 0;
		GetWindowThreadProcessId(hwnd, &process_id);
		return process_id;
	}
}
