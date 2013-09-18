/**
 * File contains definition of ContextManager class.
 * @file    ContextManager.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-04-10
 */

#include "ContextManager.hpp"

using namespace sf;
using namespace std;

namespace AyumiEngine
{
	namespace AyumiCore
	{
		/**
		 * Class default constructor. Create and configure window and OpenGL context.
		 */
		ContextManager::ContextManager()
		{
			resolutionHeight = Configuration::getInstance()->getResolutionHeight();
			resolutionWidth = Configuration::getInstance()->getResolutionWidth();
			colorDepth = Configuration::getInstance()->getColorDepth();
			msaaLevel = Configuration::getInstance()->getMSAALevel();
			windowCaption = *Configuration::getInstance()->getWindowCaption();
			fullScreenEnabled =  Configuration::getInstance()->isFullscreenEnabled();
		}

		/**
		 * Class destructor, free allocated memory for context window.
		 */
		ContextManager::~ContextManager()
		{

		}

		/**
		 * Method is used to initialize and configure engine context.
		 */
		void ContextManager::initializeContextManager()
		{
			initializeContext();
			resizeWindow(resolutionWidth, resolutionHeight);
			initializeOpenGL();

			contextWindow->setActive();
			sf::Mouse::setPosition(sf::Vector2i(resolutionWidth/2,resolutionHeight/2),*contextWindow);
			contextWindow->setMouseCursorVisible(false);
		}

		/**
		 * Method is used to initialize OpenGL window context settings such as OpenGL context
		 * version depth/stencil bits and context video mode settings like resolution.
		 */
		void ContextManager::initializeContext()
		{
			contextSettings.depthBits = 32;
			contextSettings.stencilBits = 8;
			contextSettings.antialiasingLevel = msaaLevel;
			contextSettings.majorVersion = 3;
			contextSettings.minorVersion = 3;
		
			contextVideoMode.height = resolutionHeight;
			contextVideoMode.width = resolutionWidth;
			contextVideoMode.bitsPerPixel = colorDepth;

			if(fullScreenEnabled)
				contextWindow = new Window(contextVideoMode,windowCaption,sf::Style::Fullscreen,contextSettings);
			else
				contextWindow = new Window(contextVideoMode,windowCaption,sf::Style::Close,contextSettings);

			contextWindow->setVerticalSyncEnabled(Configuration::getInstance()->isVSyncEnabled());
		}

		/**
		 * Method is used to initialize OpenGL extensions. Engine use GLEW library
		 * to manage all posible extensions for OpenGL 3.3.
		 */
		void ContextManager::initializeOpenGL()
		{
			GLenum glewError = 0;
			glewExperimental = GL_TRUE;
		
			if ((glewError = glewInit()) != GLEW_OK)
			{
				Logger::getInstance()->saveLog(Log<string>("GLEW error occurred!"));
				Logger::getInstance()->saveLog(Log<string>("Application close - critical error!"));
				exit(0);
			}

			if (!GLEW_VERSION_3_3)
			{
				Logger::getInstance()->saveLog(Log<string>("OpenGL 3.3 not supporterd!"));
				Logger::getInstance()->saveLog(Log<string>("Application close - critical error!"));
				exit(0);
			}
		}

		/**
		 * Method is used to resize application window and set OpenGL viewport.
		 * @param	windowWidth is application window resolution width.
		 * @param	windowHeight is application window resolution height.
		 */
		void ContextManager::resizeWindow(int windowWidth, int windowHeight)
		{
			if(windowWidth == 0)
				windowWidth = 1;
			if(windowHeight == 0)
				windowHeight = 1;
	
			glViewport(0, 0,static_cast<GLsizei>(windowWidth), static_cast<GLsizei>(windowHeight));
		}

		/**
		 * Accessor to context window private pointer.
		 * @return	pointer to context window.
		 */
		Window* ContextManager::getContextWindow() const
		{
			return contextWindow;
		}

		/**
		 * Accessor to context resolution height private member.
		 * @reutrn	resolution height value.
		 */
		int ContextManager::getResolutionHeight() const
		{
			return resolutionHeight;
		}

		/**
		 * Accessor to context resolution width private member.
		 * @return	resolution width value.
		 */
		int ContextManager::getResolutionWidth() const
		{
			return resolutionWidth;
		}
	}
}
