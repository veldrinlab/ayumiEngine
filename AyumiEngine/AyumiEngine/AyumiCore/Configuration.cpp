/**
 * File contains definition of Configuration class.
 * @file    Configuraton.cpp
 * @author  Szymon "Veldrin" Jab³oñski.
 * @date    2011-08-06
 */

#include "Configuration.hpp"

using namespace std;
using namespace boost;

namespace AyumiEngine
{
	namespace AyumiCore
	{
		/**
		 * Class default constructor. Initialize and prepares configuration script and
		 * set all class variables to default. Name of configuration script MUST be config.lua.
		 */
		Configuration::Configuration()
		{
			configurationScript = new AyumiScript("null");
			coreState = new StateMachine();
			resolutionHeight = 0;
			resolutionWidth = 0;
			colorDepth = 0;
			msaaLevel = 0;
			fullscreenEnabled = false;
			vSyncEnabled = false;
			prepareConfigScript();
		}

		/**
		 * Class destructor, free allocated memory for configurationScript and StateMachine state objects.
		 */
		Configuration::~Configuration()
		{
			delete configurationScript;
			delete coreState;
			delete windowCaption;
			delete textureScriptName;
			delete meshScriptName;
			delete shaderScriptName;
			delete materialScriptName;
			delete lightScriptName;
			delete soundScriptName;
			delete effectScriptName;
		}

		/**
		 * Private method which is used to prepare configuration script. By using Luabind engine register Configuration class
		 * to Lua namespace and bind global pointer to engine configuration object.
		 */
		void Configuration::prepareConfigScript()
		{
			luabind::module(configurationScript->getVirtualMachine())
			[
				luabind::class_<Configuration>("Configuration")
				.def("setResolutionWidth",&Configuration::setResolutionWidth)
				.def("setResolutionHeight",&Configuration::setResolutionHeight)
				.def("setColorDepth",&Configuration::setColorDepth)
				.def("setMSAALevel",&Configuration::setMSAALevel)
				.def("setFullscreenEnabled",&Configuration::setFullscreenEnabled)
				.def("setVSyncEnabled",&Configuration::setVSyncEnabled)
				.def("setWindowCaption",&Configuration::setWindowCaption)
				.def("setTextureScriptName",&Configuration::setTextureScriptName)
				.def("setMeshScriptName",&Configuration::setMeshScriptName)
				.def("setShaderScriptName",&Configuration::setShaderScriptName)
				.def("setMaterialScriptName",&Configuration::setMaterialScriptName)
				.def("setLightScriptName",&Configuration::setLightScriptName)
				.def("setSoundScriptName",&Configuration::setSoundScriptName)
				.def("setEffectScriptName",&Configuration::setEffectScriptName)
			];

			luabind::globals(configurationScript->getVirtualMachine())["Config"] = this;
		}

		/**
		 * Method is used to execute configuration script. Need to be called only once. After that user can configure engine
		 * by seeter methods from game code, for example Options menu.
		 * @param	name is 
		 */
		void Configuration::configureEngine(const string& scriptPath)
		{
			configurationScript->setScriptFile(scriptPath.c_str());
			configurationScript->executeScript();
		}

		/**
		 * Accessor to core state pointer private member.
		 * @return	pointer to core state object.
		 */
		StateMachine* Configuration::getCoreState() const
		{
			return coreState;
		}

		/**
		 * Accessor to resolution height private member.
		 * @return	resolution height value.
		 */
		int Configuration::getResolutionHeight() const
		{
			return resolutionHeight;
		}

		/**
		 * Accessor to resolution width private member.
		 * @return	resolution width value.
		 */
		int Configuration::getResolutionWidth() const
		{
			return resolutionWidth;
		}

		/**
		 * Accessor to color depth private member.
		 * @return	color depth value.
		 */
		int Configuration::getColorDepth() const
		{
			return colorDepth;
		}
		
		/**
		 * Accessor to MSAA level private member.
		 * @return	MSAA level value.
		 */
		int Configuration::getMSAALevel() const
		{
			return msaaLevel;
		}

		/**
		 * Accessor to fullscreen enabled private flag member.
		 * @return	true if it is enabled, false otherwise.
		 */
		bool Configuration::isFullscreenEnabled() const
		{
			return fullscreenEnabled;
		}

		/**
		 * Accessor to VSync enabled private flag member.
		 * @return	true if it is enabled, false otherwise.
		 */
		bool Configuration::isVSyncEnabled() const
		{
			return vSyncEnabled;
		}

		/**
		 * Accessor to window caption private member.
		 * @return	window caption value.
		 */
		string* Configuration::getWindowCaption() const
		{
			return windowCaption;
		}
		/**
		 * Accessor to textures load script name private member.
		 * @return	texture load script name.
		 */
		string* Configuration::getTextureScriptName() const
		{
			return textureScriptName;
		}

		/**
		 * Accessor to meshes load script name private member.
		 * @return	meshes load script name.
		 */
		string* Configuration::getMeshScriptName() const
		{
			return meshScriptName;
		}

		/**
		 * Accessor to shaders load script name private member.
		 * @return	shaders load script name.
		 */
		string* Configuration::getShaderScriptName() const
		{
			return shaderScriptName;
		}

		/**
		 * Accessor to materials load script name private member.
		 * @return	materials load script name.
		 */
		string* Configuration::getMaterialScriptName() const
		{
			return materialScriptName;
		}

		/**
		 * Accessor to lights load script name private member.
		 * @return	lights load script name.
		 */
		string* Configuration::getLightScriptName() const
		{
			return lightScriptName;
		}

		/**
		 * Accessor to sounds load script name private member.
		 * @return	sounds load script name.
		 */
		string* Configuration::getSoundScriptName() const
		{
			return soundScriptName;
		}

		/**
		 * Accessor to effects load script name private member.
		 * @return	effects load script name.
		 */
		string* Configuration::getEffectScriptName() const
		{
			return effectScriptName;
		}

		/**
		 * Setter for private resolution height member.
		 * @param	height is new constant resolution height value.
		 */
		void Configuration::setResolutionHeight(const int height)
		{
			this->resolutionHeight = height;
		}

		/**
		 * Setter for private resolution width member.
		 * @param	width is new constant resolution width value.
		 */
		void Configuration::setResolutionWidth(const int width)
		{
			this->resolutionWidth = width;
		}

		/**
		 * Setter for private color depth member.
		 * @param	depth is new constant color depth value.
		 */
		void Configuration::setColorDepth(const int depth)
		{
			this->colorDepth = depth;
		}

		/**
		 * Setter for private MSAA level member.
		 * @param	msaaLevel is new constant MSAA level value.
		 */
		void Configuration::setMSAALevel(const int msaaLevel)
		{
			this->msaaLevel = msaaLevel;
		}

		/**
		 * Setter for private fullscreen enabled flag member.
		 * @param	enabled is flag bool value.
		 */
		void Configuration::setFullscreenEnabled(const bool enabled)
		{
			this->fullscreenEnabled = enabled;
		}

		/**
		 * Setter for private VSync enabled flag member.
		 * @param	enabled is flag bool value.
		 */
		void Configuration::setVSyncEnabled(const bool enabled)
		{
			this->vSyncEnabled = enabled;
		}

		/**
		 * Setter for private window caption member.
		 * @param	caption is new constant window caption value.
		 */
		void Configuration::setWindowCaption(const string& caption)
		{
			this->windowCaption  = new string(caption);
		}

		/**
		 * Setter for private textures load script name member.
		 * @param	name is new textures load script name.
		 */
		void Configuration::setTextureScriptName(const string& name)
		{
			this->textureScriptName = new string(name);
		}

		/**
		 * Setter for private meshes load script name member.
		 * @param	name is new meshes load script name.
		 */
		void Configuration::setMeshScriptName(const string& name)
		{
			this->meshScriptName = new string(name);
		}

		/**
		 * Setter for private shaders load script name member.
		 * @param	name is new shaders load script name.
		 */
		void Configuration::setShaderScriptName(const string& name)
		{
			this->shaderScriptName = new string(name);
		}

		/**
		 * Setter for private materials load script name member.
		 * @param	name is new materials load script name.
		 */
		void Configuration::setMaterialScriptName(const string& name)
		{
			this->materialScriptName = new string(name);
		}

		/**
		 * Setter for private lights load script name member.
		 * @param	name is new lights load script name.
		 */
		void Configuration::setLightScriptName(const string& name)
		{
			this->lightScriptName = new string(name);
		}

		/**
		 * Setter for private sounds load script name member.
		 * @param	name is new sounds load script name.
		 */
		void Configuration::setSoundScriptName(const string& name)
		{
			this->soundScriptName = new string(name);
		}

		/**
		 * Setter for private effects load script name member.
		 * @param	name is new sounds load script name.
		 */
		void Configuration::setEffectScriptName(const string& name)
		{
			this->effectScriptName = new string(name);
		}
	}
}
