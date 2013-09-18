/**
 * File contains definition of Timer class.
 * @file    Timer.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-04-10
 */

#include "Timer.hpp"

using namespace sf;

namespace AyumiEngine
{
	namespace AyumiCore
	{
		/**
		 * Class default constructor, set initialize values.
		 */
		Timer::Timer()
		{
			timerClock = new Clock();
			timeAccumulator = 0.0f;
			timeStep = 1.0f/60.0f;
			actualTime = 0.0f;
			previousTime = static_cast<float>(timerClock->getElapsedTime().asSeconds());
			elapsedTime = 0.0f;
		}

		/**
		 * Class default destructor, free allocated memeory. Delete timer object.
		 */
		Timer::~Timer()
		{
			delete timerClock;
		}

		/**
		 * Templated function which is used to clamp some value in defined <min,max> space.
		 * @param	what is value to clamp.
		 * @param	a is clamp min.
		 * @param	b is clamp max.
		 */
		template <typename T>
		T clamp(const T& what, const T& a, const T& b)
		{
			return std::min(b, std::max(what, a));
		}

		/**
		 * Method is used to update actual and previous time and count elapsed time. Use SFML Clock class GetElapsedTime()
		 * method to get actual time from OS API.
		 */
		void Timer::updateTimerData()
		{
			actualTime = static_cast<float>(timerClock->getElapsedTime().asSeconds());
			elapsedTime = actualTime - previousTime;
			previousTime += elapsedTime;
			elapsedTime = std::max(0.0f,elapsedTime);	
			timeAccumulator += elapsedTime;
			timeAccumulator = clamp<float>(timeAccumulator,0.0f,1.0f);
		}

		/**
		 * Method is used to check if there is enough time in accumulator to update scene.
		 * @retun	true if there is, false otherwise.
		 */
		bool Timer::checkTimerAccumulator() const
		{
			return timeAccumulator > timeStep;
		}
		
		/**
		 * Method is used to decrease accumulator time after scene update.
		 */
		void Timer::eatAccumulatorTime()
		{
			timeAccumulator -= timeStep;
		}

		/**
		 * Accessor to time step private member.
		 * @return	time step in seconds.
		 */
		float Timer::getTimeStep() const
		{
			return timeStep;
		}
	}
}
