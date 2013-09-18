/**
 * File contains declaraion and definition of templated Log class.
 * @file    Log.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-04-10
 */

#ifndef LOG_HPP
#define LOG_HPP

//#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>

namespace AyumiEngine
{
	/**
	 * Class represents templated adapter of Engine Logs. It is used to store message for example
	 * error and time when it occcurred and was saved in log file.
	 */
	template<class T = std::string>
	class Log
	{
	private:
		T messageLog;
		//boost::posix_time::time_facet* facet;

	public:
		/**
		 * Class constructor whih initialize parameters. Create templated message log and initialize
		 * posix time facet.
		 * @param	message is log message.
		 */
		Log(const T& message) : messageLog(message)
		{
		//	facet = new boost::posix_time::time_facet("%d-%b-%Y %H:%M:%S");
		}

		/**
		 * Class destructor, free allocated memory. Nothing to delete.
		 */
		~Log()
		{

		}

		/**
		 * Accessor to private log message member.
		 * @return	log message.
		 */
		T getLogMessage() const
		{
			return messageLog;
		}

		/**
		 * Accessor to private posix time facet member.
		 * @return	pointer to posix time facet.
		 */
		//boost::posix_time::time_facet* getFacet() const
		//{
		//	return facet;
		//}
	};
}
#endif
