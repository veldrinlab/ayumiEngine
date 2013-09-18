/**
 * File contains declaraion of InputAction class.
 * @file    InputAction.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-04-10
 */

#ifndef INPUTACTION_HPP
#define INPUTACTION_HPP

#include <boost/signal.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp> 

namespace AyumiEngine
{
	namespace AyumiInput
	{
		/**
		 * Structure represents InputAction class which is wrapper of boost::signal class. User must wrap signal class
		 * in order to store signlas in std::map structure. Class is used to connect Keyboard key and mouse button 
		 * signals with user defined functions.
		 */
		struct InputAction
		{
			boost::signal<void()> signal;
		};
	}
}
#endif
