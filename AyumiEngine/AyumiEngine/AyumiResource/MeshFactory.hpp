/**
 * File contains declaration of MeshFactory class.
 * @file    MeshFactory.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-10
 */

#ifndef MESHFACTORY_HPP
#define MESHFACTORY_HPP

#include <fstream>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>

#include "Mesh.hpp"
#include "FileMD2.hpp"

#include "../Logger.hpp"
#include "../AyumiMath/CommonMath.hpp"

namespace AyumiEngine
{
	namespace AyumiResource
	{
		/**
		 * Struct represents RAW mesh creation parameters.
		 */
		struct RawParameters
		{
			int size;
			float rowScale;
			float columnScale;
			float heightScale;
			float maxCoord;
		};

		/**
		 * Class represents one of Engine ResourceManager/MeshManager subclass - MeshFactory
		 * which is used by MeshManager to load create all supported 3d model formats. Class has
		 * methods to load and create all kind of mesh resources and store it in MeshManager class.
		 * It is implementation of simple Factory design pattern.
		 */
		class MeshFactory
		{
		private:
			RawParameters rawParams;

			Mesh* createVelMesh(const std::string& name, const std::string& path);
			Mesh* createObjMesh(const std::string& name, const std::string& path);
			Mesh* create3dsMesh(const std::string& name, const std::string& path);
			Mesh* createMD2Mesh(const std::string& name, const std::string& path);
			Mesh* createMD3Mesh(const std::string& name, const std::string& path); // TODO
			Mesh* createMD5Mesh(const std::string& name, const std::string& path); // TODO
			Mesh* createRawMesh(const std::string& name, const std::string& path);
			Mesh* createProceduralMesh(const std::string& name, const float roughnes);

		public:
			MeshFactory();
			~MeshFactory();

			Mesh* createMeshResource(const std::string& name, const std::string& type, const std::string& path);
			void initRawParameters(const int size, const float rowScale, const float columnScale, const float heightScale, const float maxCoord);
		};
	}
}
#endif
