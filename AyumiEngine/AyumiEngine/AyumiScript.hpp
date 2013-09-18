/**
 * File contains declaration of AyumiScript class.
 * @file    AyumiScript.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-07-10
 */

#ifndef AYUMISCRIPT_HPP
#define AYUMISCRIPT_HPP

#include "VirtualMachine.hpp"
#include "Logger.hpp"

namespace AyumiEngine
{
	/**
	 * Class represents simple adapter of Lua script. It is use to store and execute scripts in Engine
	 * source code. Each Lua script objects store name of script file and pointer to Lua state which is 
	 * Lua virtual machine. User can load and execute any Lua scripts. Class do not use luabind.
	 */
	class AyumiScript
	{
	private:
		const char* scriptFile;
		lua_State* virtualMachine;

	public:
		AyumiScript();
		AyumiScript(const char* scriptFile);
		~AyumiScript();

		void executeScript();
		lua_State* getVirtualMachine() const;
		void setScriptFile(const char* name);
		void setVirtualMachine(lua_State* machine);
	};
}
#endif
