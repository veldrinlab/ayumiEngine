/**
 * File contains declaraion of StateMachine structure.
 * @file    StateMachine.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-06
 */

#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include "EngineCoreStates.hpp"

namespace AyumiEngine
{
	namespace AyumiCore
	{
		/**
		 * Structure represents group of Engine inner state machine. Each state implements
		 * Binary State desgin pattern and represents some OpenGL API state machine effects
		 * like depth testing, blending and culling operations.
		 */
		struct StateMachine
		{
			Depth depthState;
			Blend blendState;
			Wireframe wireframeState;
			BackCulling backCullingState;
		};
	}
}
#endif
