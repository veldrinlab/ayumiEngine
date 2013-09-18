/**
 * File contains declaraion of Timer class.
 * @file    Timer.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-04-10
 */

#ifndef TIMER_HPP
#define TIMER_HPP

#include <SFML/Window.hpp>

namespace AyumiEngine
{
	namespace AyumiCore
	{
		/**
		 * Class represents simple Timer class which is used in engine real-time loop
		 * for controlling and calculating time between frames. It is use to get delta time mode.
		 */
		class Timer
		{
		private:
			sf::Clock* timerClock;
			float actualTime;
			float previousTime;
			float elapsedTime;
			float timeAccumulator;
			float timeStep;
		public:
			Timer();
			~Timer();

			void updateTimerData();
			bool checkTimerAccumulator() const;
			void eatAccumulatorTime();
			
			float getTimeStep() const;
		};
	}
}
#endif
