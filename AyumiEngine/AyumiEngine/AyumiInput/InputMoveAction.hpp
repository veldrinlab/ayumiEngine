/**
 * File contains declaraion of InputMoveAction class.
 * @file    InputMoveAction.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-07-13
 */

#ifndef INPUTMOVEACTION_HPP
#define INPUTMOVEACTION_HPP

#include <boost/signal.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp> 

namespace AyumiEngine
{
	namespace AyumiInput
	{
		/**
		 * Structure represents InputMoveAction class which is wrapper of boost::signal with arguments class.
		 * User must wrap signal class in order to store signlas in std::map structure. Class is used to 
		 * connect Mouse move signlas with user defined functions.
		 */
		struct InputMoveAction
		{
			boost::signal<void (int,int)> signal;
		};

		/**
		 * Structure represents InputMoveWheelAction class which is wrapper of boost::signal with arguments class.
		 * User must wrap signal class in order to store signlas in std::map structure. Class is used to 
		 * connect Mouse wheel move signlas with user defined functions.
		 */
		struct InputMoveWheelAction
		{
			boost::signal<void (int)> signal;
		};

		/**
		 * Structure represents InputAxisAction class which is wrapper of boost::signal with arguments class.
		 * User must wrap signal class in order to store signlas in std::map structure. Class is used to 
		 * connect GamePad axis move signlas with user defined functions.
		 */
		struct InputAxisAction
		{
			boost::signal<void (float)> signal;
		};	
	}
}
#endif
