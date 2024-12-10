/* THIS PROJECT INCLUDES */
#include "../includes/helper_process.hpp"
#include "../includes/helper_filesystem.hpp"

/* C++ INCLUDES */
#include <vector>

/* WINDOWS INCLUDES */
#include <windows.h>
#include <psapi.h>

#pragma comment(lib, "psapi.lib")

namespace helper::process
{
	std::string execute_command(const std::string& executable, const std::initializer_list<std::string>& arguments,
	                            const uint32_t timeout, const bool wait_exit)
	{
		std::string output;

		try
		{
			// Configurações de segurança para os pipes
			SECURITY_ATTRIBUTES sa;
			sa.nLength = sizeof(SECURITY_ATTRIBUTES);
			sa.lpSecurityDescriptor = nullptr;
			sa.bInheritHandle = TRUE;

			// Criação dos pipes para capturar a saída do processo
			HANDLE hStdOutRead = nullptr;
			HANDLE hStdOutWrite = nullptr;
			if (!CreatePipe(&hStdOutRead, &hStdOutWrite, &sa, 0))
			{
				// Falha ao criar os pipes
				return "";
			}

			// Garante que o handle de leitura não seja herdado
			SetHandleInformation(hStdOutRead, HANDLE_FLAG_INHERIT, 0);

			STARTUPINFOA si;
			PROCESS_INFORMATION pi;
			ZeroMemory(&si, sizeof(si));
			si.cb = sizeof(si);
			si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
			si.wShowWindow = SW_HIDE; // Oculta a janela
			si.hStdOutput = hStdOutWrite;
			si.hStdError = hStdOutWrite; // Redireciona STDERR também

			ZeroMemory(&pi, sizeof(pi));

			// Monta a linha de comando
			std::string cmd = executable;
			for (const auto& arg : arguments)
			{
				cmd += " " + arg;
			}

			// Cria uma cópia modificável da linha de comando
			std::vector<char> cmdline(cmd.begin(), cmd.end());
			cmdline.push_back('\0');

			// Inicia o processo
			if (!CreateProcessA(nullptr, cmdline.data(), nullptr, nullptr, TRUE, CREATE_NO_WINDOW, nullptr, nullptr,
			                    &si, &pi))
			{
				// Falha ao iniciar o processo
				CloseHandle(hStdOutWrite);
				CloseHandle(hStdOutRead);
				return "";
			}
			// Fecha o handle de escrita no processo pai
			CloseHandle(hStdOutWrite);

			if (wait_exit)
			{
				// Aguarda o processo finalizar
				DWORD waitResult = WaitForSingleObject(pi.hProcess, timeout);

				if (waitResult == WAIT_OBJECT_0)
				{
					// Processo finalizado antes do timeout
				}
				else if (waitResult == WAIT_TIMEOUT)
				{
					// Timeout expirado, processo ainda está em execução
					// Opcionalmente, pode encerrar o processo
					TerminateProcess(pi.hProcess, 1);
				}
				else
				{
					// Ocorreu um erro
				}

				// Lê a saída do processo
				constexpr DWORD BUFSIZE = 4096;
				char buffer[BUFSIZE];
				DWORD bytesRead;

				while (ReadFile(hStdOutRead, buffer, BUFSIZE, &bytesRead, nullptr) && bytesRead != 0)
				{
					output.append(buffer, bytesRead);
				}
			}

			// Fecha os handles do processo e thread
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);

			// Fecha o handle de leitura
			CloseHandle(hStdOutRead);

			return output;
		}
		catch (...)
		{
			// Trate exceções se necessário
			return "";
		}
	}

	std::string get_process_name(const uint32_t process_id)
	{
		const std::string process_path = get_process_path(process_id);
		if (!process_path.empty())
		{
			return filesystem::get_binary_name(process_path);
		}
		return "";
	}

	std::string get_process_path(const uint32_t process_id)
	{
		const HANDLE h_process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, process_id);
		if (h_process == nullptr)
		{
			return "";
		}

		char process_path[MAX_PATH];
		if (GetModuleFileNameExA(h_process, nullptr, process_path, MAX_PATH))
		{
			CloseHandle(h_process);
			return std::string(process_path);
		}

		CloseHandle(h_process);
		return "";
	}
}
