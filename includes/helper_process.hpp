#ifndef HELPER_PROCESS_HPP
#define HELPER_PROCESS_HPP

/* C++ INCLUDES */
#include <string>
#include <initializer_list>
#include <cstdint>

namespace helper::process
{
    /**
     * @brief Executes a command in the background, optionally capturing the output.
     *
     * This function executes a command specified by the executable and list of arguments, hiding the console window.
     * It is possible to specify a timeout and whether the function should wait for the process to exit.
     *
     * @param executable The path to the executable to be run.
     * @param arguments List of arguments for the executable.
     * @param timeout Maximum time (in milliseconds) to wait for the process to finish. Default value is INFINITE.
     * @param wait_exit If true, the function will wait for the process to finish. If false, it will return immediately. Default is true.
     * @return The captured output of the command as a std::string. If not capturing or an error occurs, returns an empty string.
     */
	std::string execute_command(const std::string& executable, const std::initializer_list<std::string>& arguments,
	                            uint32_t timeout = -1, bool wait_exit = true);


    /**
     * @brief Retrieves the full path of the executable of a process based on its PID.
     *
     * @param process_id The PID of the process.
     * @return A string containing the full path of the executable. Returns an empty string in case of an error.
     */
    std::string get_process_path(uint32_t process_id);

    /**
     * @brief Retrieves the name of the executable of a process based on its PID.
     *
     * This function uses the get_binary_name function from the filesystem module to extract the executable name from the full path.
     *
     * @param process_id The PID of the process.
     * @return A string containing the name of the executable. Returns an empty string in case of an error.
     */
    std::string get_process_name(uint32_t process_id);
}

#endif // HELPER_PROCESS_HPP
