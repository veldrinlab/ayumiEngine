/**
 * File contains declaraion of VirtualMachine class.
 * @file    VirtualMachine.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-07-10
 */

#ifndef VIRTUALMACHINE_HPP
#define VIRTUALMACHINE_HPP

extern "C"
{
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
}

#include <fstream>

#include "luabind/luabind.hpp"
#include "AyumiUtils/Singleton.hpp"

namespace AyumiEngine
{
	/**
	 * Class represents adapter of Lua virtual machine. It implements singleton interface pattern for global,
	 * thread-safe scope. It is use to store lua global state. We use Lua script with luabind library to 
	 * register and use c++ code in Lua scripts. Class represents only Lua global state - user can define
	 * unlimited Lua states which will can use different C++ classes and globals.
	 */
	class VirtualMachine : public AyumiUtils::Singleton<VirtualMachine>
	{
	private:
		friend AyumiUtils::Singleton<VirtualMachine>;
		lua_State* globalState;

		VirtualMachine();
		VirtualMachine(const VirtualMachine& notPossibleHehehe);
		virtual ~VirtualMachine();
	
	public:
		lua_State* getGlobalState() const;
	};
}
#endif
