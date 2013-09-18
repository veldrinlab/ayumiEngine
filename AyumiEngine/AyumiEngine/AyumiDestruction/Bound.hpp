/**
 * File contains declaraion of Bound class.
 * @file    Bound.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-15
 */

#ifndef BOUND_HPP
#define BOUND_HPP

#include "Vector.hpp"

namespace AyumiEngine
{
	namespace AyumiDestruction
	{
		/**
		 * Class represents face boudning volume.
		 */
		class Bound
		{
		private:
			void checkVertex(const Vector& vertex);

		public:
			float xMax;
			float xMin;
			float yMax;
			float yMin;
			float zMax;
			float zMin;
	
			Bound(const Vector& p1, const Vector& p2, const Vector& p3);
			Bound(VectorSet* vertices);
			virtual ~Bound();
	
			bool overlap(Bound& bound);
		};
	}
}
#endif
