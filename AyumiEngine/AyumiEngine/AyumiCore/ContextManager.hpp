/**
 * File contains declaraion of ContextManager class.
 * @file    ContextManager.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-04-10
 */

#ifndef CONTEXTMANAGER_HPP
#define CONTEXTMANAGER_HPP

#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <string>

#include "Configuration.hpp"
#include "../Logger.hpp"

namespace AyumiEngine
{
	namespace AyumiCore
	{
		/**
		 * Class represents main Engine Core class - ContextManager which is used
		 * to create window and OpenGL context. Class is also used to initialize OpenGL
		 * state mashine. Use Configuration class to get resolution and other data.
		 * ContextManager use SFML library to create multi-platform code.
		 */
		class ContextManager
		{
		private:
			sf::Window* contextWindow; 
			sf::ContextSettings contextSettings;
			sf::VideoMode contextVideoMode;
			int resolutionHeight;
			int resolutionWidth;
			int colorDepth;
			int msaaLevel;
			std::string windowCaption;
			bool fullScreenEnabled;

			void initializeContext();
			void initializeOpenGL();

		public:
			ContextManager();
			~ContextManager();

			void initializeContextManager();
			void resizeWindow(int windowWidth, int windowHeight);

			sf::Window* getContextWindow() const;
			int getResolutionHeight() const;
			int getResolutionWidth() const;
		};
	}
}
#endif
