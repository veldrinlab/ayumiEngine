/**
 * File contains declaration of Cloneable pattern interface class.
 * @file    Cloneable.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-04-10
 */

#ifndef CLONEABLE_HPP
#define CLONEABLE_HPP

#include "Noncopyable.hpp"

namespace AyumiEngine
{
	namespace AyumiUtils
	{
		/**
		 * Class represents abstract interface of Cloneable pattern class.
		 * Derived class must implement clone method. Cloneable extends Noncopyable
		 * interface in order to make clone() method only way to copy object.
		 */
		class Cloneable : private Noncopyable
		{
		public:
			virtual Cloneable* clone() const = 0;
			virtual ~Cloneable(){};
		};
	}
}
#endif
