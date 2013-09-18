/**
 * File contains declaration of State pattern interface class.
 * @file    State.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-06
 */

#ifndef STATE_HPP
#define STATE_HPP

namespace AyumiEngine
{
	namespace AyumiUtils
	{
		/**
		 * Class represents abstract State design pattern interface class. In will be used
		 * to define engine binary state machine class.
		 */
		class State
		{
		public:
			virtual ~State() {};
			virtual void on() = 0;
			virtual void off() = 0;
		};
	}
}
#endif
