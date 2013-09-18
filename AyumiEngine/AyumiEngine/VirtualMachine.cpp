/**
 * File contains definition of VirtualMachine class.
 * @file    VirtualMachine.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-07-10
 */

#include "VirtualMachine.hpp"

namespace AyumiEngine
{
	/**
	 * Class default constuctor. Initialize Lua virtual machine state and luabind connection.
	 */
	VirtualMachine::VirtualMachine()
	{
		globalState = lua_open();
		luabind::open(globalState);
	}

	/**
	 * Class private copy constructor because of singleton pattern implementation.
	 * @param	notPossibleHehehe is just a joke.
	 */
	VirtualMachine::VirtualMachine(const VirtualMachine& notPossibleHehehe)
	{

	}

	/**
	 * Class destructor, free allocated memory. Close Lua virtual machine.
	 */
	VirtualMachine::~VirtualMachine()
	{
		lua_close(globalState);
	}

	/**
	 * Accessor to private lua global state.
	 * @return	pointer to lua global state.
	 */
	lua_State* VirtualMachine::getGlobalState() const
	{
		return globalState;
	}
}
