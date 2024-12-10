#ifndef HELPER_WINDOW_HPP
#define HELPER_WINDOW_HPP

#include <string>

namespace helper::window
{
	/**
	 * @brief Obtém o PID do processo da janela que está em foco.
	 *
	 * @return O PID do processo associado à janela em foco. Retorna 0 se nenhuma janela estiver em foco ou em caso de erro.
	 */
	uint32_t get_foreground_window_pid();
}

#endif // HELPER_WINDOW_HPP
