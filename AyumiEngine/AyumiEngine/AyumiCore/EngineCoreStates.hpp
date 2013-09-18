/**
 * File contains declaration of EngineCoreStates class.
 * @file    EngineCoreStates.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-06
 */

#ifndef ENGINECORESTATES_HPP
#define ENGINECORESTATES_HPP

#include <GL/glew.h>

#include "../AyumiUtils/State.hpp"

namespace AyumiEngine
{
	namespace AyumiCore
	{
		/**
		 * Class represents depth testing on/off state. It is implementaion of binary State design pattern.
		 */
		class Depth : public AyumiUtils::State
		{
		public:
			void on();
			void off();
		};

		/**
		 * Class represents blending on/off state. It is implementaion of binary State design pattern.
		 */
		class Blend : public AyumiUtils::State
		{
		public:
			void on();
			void off();
		};

		/**
		 * Class represents wireframe rendering on/off state. It is implementaion of binary State design pattern.
		 */
		class Wireframe : public AyumiUtils::State
		{
		public:
			void on();
			void off();
		};
		
		/**
		 * Class represents back face culling on/off state. It is implementaion of binary State design pattern.
		 */
		class BackCulling : public AyumiUtils::State
		{
		public:
			void on();
			void off();
		};
	}
}
#endif
