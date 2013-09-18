/**
 * File contains declaration of templated Singleton pattern interface class.
 * @file    Singleton.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-04-10
 */

#ifndef SINGLETON_HPP
#define SINGLETON_HPP

namespace AyumiEngine
{
	namespace AyumiUtils
	{
		/**
		 * Class represents implementaion of Singleton pattern. Is is templated in order to
		 * implement singleton pattern classes which will extend Singleton base class and 
		 * became singletons.
		 */
		template <typename T> class Singleton
		{
		protected:
			static T* instance;

			/**
			 * Class default constructor. Must be private and empty because of singleton pattern.
			 */
			Singleton(){}
			
			/**
			 * Class copy constructor. Must be private and empty because of singleton pattern.
			 * @param	s is copy source object.
			 */
			Singleton(const Singleton<T>& s){}
			
			/**
			 * Class destructor
			 */
			virtual ~Singleton(){}

			/**
			 * Class assignment operator. Must be private and empty because of singleton pattern.
			 * @param	s is copy source object.
			 */  
			Singleton& operator=(const Singleton<T>& s){}
		public:

			/**
			 * Method is used to get singleton class instance. It use lazy evaluation.
			 * @return	instance of singleton object.
			 */
			static inline T* getInstance()
			{
				if (instance == nullptr)
					instance = new T;
				return instance;
			}

			/**
			 * Method is sused to delete allocated memory in lazy evaluation - if object was
			 * created.
			 */
			static inline void killInstance()
			{
				if (instance != nullptr)
					delete instance;
				instance = nullptr;
			}
		};
		
		/**
		 * Initialization of class static member to null pointer.
		 */
		template<typename T> T* Singleton<T>::instance = nullptr;
	}
}
#endif
