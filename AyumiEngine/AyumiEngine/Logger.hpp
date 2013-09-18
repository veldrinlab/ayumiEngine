/**
 * File contains declaraion of Logger class.
 * @file    Logger.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-04-10
 */

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>

#include "Log.hpp"
#include "AyumiUtils/Singleton.hpp"

namespace AyumiEngine
{
	/**
	 * Class represents Ayumi Engine Logger. It implements singleton interface pattern for global,
	 * thread-safe scope. Logger is used to save templated message logs to file. Name of file
	 * is "log.log" and it is pure plain text file with messages and messages times. Log class is templated
	 * so user can use int/float/string messeges.
	 */
	class Logger: public AyumiUtils::Singleton<Logger>
	{
	private:
		friend class AyumiUtils::Singleton<Logger>;

		Logger();
		Logger(const Logger& logger);
		virtual ~Logger();

	public:
		void saveLog(const Log<int>& log);
		void saveLog(const Log<float>& log);
		void saveLog(const Log<std::string>& log);
	};
}
#endif
