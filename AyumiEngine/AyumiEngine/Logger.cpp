/**
 * File contains definition of Logger class.
 * @file    Logger.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-04-10
 */

#include "Logger.hpp"

//using namespace boost::posix_time;
using namespace std;

namespace AyumiEngine
{
	/**
	 * Class default constructor. Nothing to create or initilize.
	 */
	Logger::Logger()
	{
		//ofstream logFile("AyumiLogs.log", ofstream::trunc);
	//	logFile.close();
	}

	/**
	 * Class private copy constructor beacause of singleton pattern.
	 * @param	logger is another looger object.
	 */
	Logger::Logger(const Logger& logger)
	{

	}
	
	/**
	 * Class destructor, free allocated memory. Nothing to delete.
	 */
	Logger::~Logger()
	{

	}

	/**
	 * Method is used to save int log message to log file.
	 * @param	log is message log object.
	 */
	void Logger::saveLog(const Log<int>& log)
	{
		//ofstream logFile("AyumiLogs.log", ofstream::in | ofstream::app);
		//
		//logFile.imbue(locale(logFile.getloc(), log.getFacet()));
		//logFile << second_clock::local_time() << " ";
		//logFile << log.getLogMessage() << endl;
		//logFile.close();
	}

	/**
	 * Method is used to save float log message to log file.
	 * @param	log is message log object.
	 */
	void Logger::saveLog(const Log<float>& log)
	{
		//ofstream logFile("AyumiLogs.log", ofstream::in | ofstream::app);
		//
		//logFile.imbue(locale(logFile.getloc(), log.getFacet()));
		//logFile << second_clock::local_time() << " ";
		//logFile << log.getLogMessage() << endl;
		//logFile.close();
	}

	/**
	 * Method is used to save int string message to log file.
	 * @param	log is message log object.
	 */
	void Logger::saveLog(const Log<string>& log)
	{
		//ofstream logFile("AyumiLogs.log", ofstream::in | ofstream::app);
		//
		//logFile.imbue(locale(logFile.getloc(), log.getFacet()));
		//logFile << second_clock::local_time() << " ";
		//logFile << log.getLogMessage() << endl;
		//logFile.close();
	}
}
