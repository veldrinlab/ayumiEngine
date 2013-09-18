/**
 * File contains declaraion of Configuration class.
 * @file    Configuration.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-06
 */

#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include "StateMachine.hpp"

#include "..\AyumiScript.hpp"
#include "..\AyumiUtils\Singleton.hpp"

namespace AyumiEngine
{
	namespace AyumiCore
	{
		/**
		 * Class represents Ayumi Engine Configuration. It implements singleton interface
		 * pattern for global, thread-safe scope. Configuration is initialize by AyumiScript Data script.
		 */
		class Configuration : public AyumiUtils::Singleton<Configuration>
		{
			friend AyumiUtils::Singleton<Configuration>;

		private:
			AyumiScript* configurationScript;
			StateMachine* coreState;
			int resolutionHeight;
			int resolutionWidth;
			int colorDepth;
			int msaaLevel;
			bool fullscreenEnabled;
			bool vSyncEnabled;
			std::string* windowCaption;
			std::string* textureScriptName;
			std::string* meshScriptName;
			std::string* shaderScriptName;
			std::string* materialScriptName;
			std::string* lightScriptName;
			std::string* soundScriptName;
			std::string* effectScriptName;

			Configuration();
			Configuration(const Configuration& engineConfig);
			virtual ~Configuration();

			void prepareConfigScript();

		public:
			void configureEngine(const std::string& scriptPath);

			StateMachine* getCoreState() const;
			int getResolutionHeight() const;
			int getResolutionWidth() const;
			int getColorDepth() const;
			int getMSAALevel() const;
			bool isFullscreenEnabled() const;
			bool isVSyncEnabled() const;
			std::string* getWindowCaption() const;
			std::string* getTextureScriptName() const;
			std::string* getMeshScriptName() const;
			std::string* getShaderScriptName() const;
			std::string* getMaterialScriptName() const;
			std::string* getLightScriptName() const;
			std::string* getSoundScriptName() const;
			std::string* getEffectScriptName() const;

			void setResolutionHeight(const int height);
			void setResolutionWidth(const int width);
			void setColorDepth(const int depth);
			void setMSAALevel(const int msaaLevel);
			void setFullscreenEnabled(const bool enabled);
			void setVSyncEnabled(const bool enabled);
			void setWindowCaption(const std::string& caption);
			void setTextureScriptName(const std::string& name);
			void setMeshScriptName(const std::string& name);
			void setShaderScriptName(const std::string& name);
			void setMaterialScriptName(const std::string& name);
			void setLightScriptName(const std::string& name);
			void setSoundScriptName(const std::string& name);
			void setEffectScriptName(const std::string& name);
		};
	}
}
#endif
