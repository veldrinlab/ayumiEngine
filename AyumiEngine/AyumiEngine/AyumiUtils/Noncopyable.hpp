/**
 * File contains declaration of Noncopyable pattern interface class.
 * @file    Noncopyable.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-04-10
 */

#ifndef NONCOPYABLE_HPP
#define NONCOPYABLE_HPP

namespace AyumiEngine
{
	namespace AyumiUtils
	{
		/**
		 * Class represents abstract interface of Nincopyable pattern class.
		 * Derived class cannot use assignment operator and copy constructor.
		 * The only way to copy object is to implement Cloneable interface.
		 */
		class Noncopyable
		{
		private:

			/**
			 * Class copy constructor.
			 * @param	sourceObject is copy source object.
			 */
			Noncopyable(const Noncopyable& sourceObject){}
			
			/**
			 * Class assignment operator.
			 * @param	sourceObject is copy source object.
			 */
			Noncopyable& operator=(const Noncopyable& sourceObject){}
		
		public:

			/**
			 * Class default constructor.
			 */
			Noncopyable(){}
		};
	}
}
#endif
