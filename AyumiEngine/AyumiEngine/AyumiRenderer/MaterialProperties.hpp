/**
 * File contains declaration of MaterialProperties structure.
 * @file    MaterialProperties.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-10
 */

#ifndef MATERIALPROPERTIES_HPP
#define MATERIALPROPERTIES_HPP

#include <string>
#include <map>

#include "../AyumiMath/CommonMath.hpp"

namespace AyumiEngine
{
	typedef std::map<std::string,int> IntegerUniforms;
	typedef std::map<std::string,float> FloatUniforms;
	typedef std::map<std::string,unsigned int> TextureUniforms;
	typedef std::map<std::string,AyumiMath::Vector3D> VectorUniforms;

	namespace AyumiRenderer
	{
		/**
		 * Structure represents entity material properties for phong lighting model: material ambinet,
		 * diffuse, specular and shininess.
		 */
		struct MaterialProperties
		{ 
			AyumiMath::Vector4D ambient;
			AyumiMath::Vector4D diffuse;
			AyumiMath::Vector4D specular;
			float shininess;
		};
	}
}
#endif
