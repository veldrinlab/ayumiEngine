/**
 * File contains definition of TextureFactory class.
 * @file    TextureFactory.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-02
 */

#include "TextureFactory.hpp"

using namespace std;

namespace AyumiEngine
{
	namespace AyumiResource
	{
		/**
		 * Class default constructor. Nothing to do.
		 */
		TextureFactory::TextureFactory()
		{

		}

		/**
		 * Class destructor, free allocated memory. Nothing to delete.
		 */
		TextureFactory::~TextureFactory()
		{

		}

		/**
		 * Method is used to create texture resource. It implement Factory Method, depends on resource name
		 * factory choose creating method.
		 * @param	name is resource name.
		 * @param	path is resource file path.
		 * @param	path2 is resource file layer path.
		 * @param	path3 is resource file layer path.
		 * @param	path4 is resource file layer path.
		 * @param	path5 is resource file layer path.
		 * @param	path6 is resource file layer path.
		 * @param	type is name of resource type.
		 * @return	loaded and created texture resource, or nullptr when and logger error type is
		 *			not supported.
		 */
		Texture* TextureFactory::createTextureResource(const string& name, const string& path, const string& path2, const string& path3,const string& path4, const string& path5, const string& path6, const string& type)
		{
			Texture* textureResource = nullptr;

			if(type == "TEXTURE1D")
				textureResource = createTexture1D(name,path);
			else if(type == "TEXTURE2D")
				textureResource = createTexture2D(name,path);
			else if(type == "TEXTURE3D")
				textureResource = createTexture3D(name,path);
			else if(type == "TEXTURE_RECT")
				textureResource = createRectangleTexture(name,path);
			else if(type == "CUBEMAP")
				textureResource = createCubeMapTexture(name,path,path2,path3,path4,path5,path6);
			else
			{
				Logger::getInstance()->saveLog(Log<string>("Undefined texture type requested!"));
				textureResource = nullptr;
			}

			return textureResource;
		}

		/**
		 * Method is used to initialize tetxure facotry by initializing DevIL library.
		 */
		void TextureFactory::initializeFactory()
		{
			if(ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
				Logger::getInstance()->saveLog(Log<string>("Wrong DevIL version detected!"));
			
			ilInit();
			glPixelStorei(GL_UNPACK_ALIGNMENT,1);
		}

		/**
		 * Method is used to load and create texture 1d which can be used in Toon/Cartoon mapping.
		 * @param	name is resource name.
		 * @param	path is resource file path.
		 * @return	pointer to loaded and created TEXTURE1D resource.
		 */
		Texture* TextureFactory::createTexture1D(const string& name, const string& path)
		{
			Texture* texture1D = new Texture(name.c_str(),path.c_str());
			texture1D->setTextureType(TEXTURE1D);

			ifstream textureFile;
			textureFile.open(path);

			if(textureFile.is_open())
			{
				int sampleAmount = 0;
				int colorComponentAmount = 0;
				int inputData = 0;

				GLubyte* textureData = nullptr;

				textureFile >> sampleAmount;
				textureFile >> colorComponentAmount; 

				textureData = new GLubyte[sampleAmount*colorComponentAmount];

				for(int i = 0; i < sampleAmount*colorComponentAmount; ++i)
				{
					textureFile >> inputData;
					textureData[i] = inputData % 256;
				}

				glPixelStorei(GL_UNPACK_ALIGNMENT,1);					
				glGenTextures(1,texture1D->getTexture());
				glBindTexture(GL_TEXTURE_1D,*texture1D->getTexture());

				glTexImage1D(GL_TEXTURE_1D,0,GL_RGB, sampleAmount,0,GL_RGB,GL_UNSIGNED_BYTE,textureData);
				glTexParameteri(GL_TEXTURE_1D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
				glTexParameteri(GL_TEXTURE_1D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
				glTexParameteri(GL_TEXTURE_1D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);

				delete [] textureData;
			}
			else
				Logger::getInstance()->saveLog(Log<string>("Texture1D file opening error occurred!!"));
			
			textureFile.close();

			return texture1D;
		}

		/**
		 * Method is used to load and create texture 2d which can be used in all kind of materials.
		 * @param	name is resource name.
		 * @param	path is resource file path.
		 * @return	pointer to loaded and created TEXTURE2D resource.
		 */
		Texture* TextureFactory::createTexture2D(const string& name, const string& path)
		{
			Texture* texture2D = new Texture(name.c_str(),path.c_str());
			texture2D->setTextureType(TEXTURE2D);

			ILuint texID;
			ilGenImages(1,&texID);
			ilBindImage(texID);
			
			if(!ilLoadImage((const ILstring)path.c_str()))
			{
				Logger::getInstance()->saveLog(Log<string>("Texture2D loading error occurred!"));
				Logger::getInstance()->saveLog(Log<string>(name));
			}

			if(!ilConvertImage(IL_RGBA,IL_UNSIGNED_BYTE))
			{
				Logger::getInstance()->saveLog(Log<string>("Texture2D converting error occurred!"));
				Logger::getInstance()->saveLog(Log<string>(name));
			}

			glGenTextures(1,texture2D->getTexture());
			glBindTexture(GL_TEXTURE_2D,*texture2D->getTexture());

			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

			float maximumAnisotropy;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT,&maximumAnisotropy);

			glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAX_ANISOTROPY_EXT,maximumAnisotropy);

			glTexImage2D(GL_TEXTURE_2D,0,ilGetInteger(IL_IMAGE_BPP),ilGetInteger(IL_IMAGE_WIDTH),
				  ilGetInteger(IL_IMAGE_HEIGHT),0,ilGetInteger(IL_IMAGE_FORMAT),GL_UNSIGNED_BYTE,ilGetData());
			
			ilDeleteImages(1,&texID);

			return texture2D;
		}

		/**
		 * Method is used to load and create texture 3d which can be used in terrain mapping, volumetri
		 * effects etc.
		 * @param	name is resource name.
		 * @param	path is resource file path.
		 * @return	pointer to loaded and created TEXTURE3D resource.
		 */
		Texture* TextureFactory::createTexture3D(const string& name, const string& path)
		{
			Texture* texture3D = new Texture(name.c_str(),path.c_str());
			texture3D->setTextureType(TEXTURE3D);

			ILuint texID;
			ilGenImages(1,&texID);
			ilBindImage(texID);
			
			if(!ilLoadImage((const ILstring)path.c_str()))
			{
				Logger::getInstance()->saveLog(Log<string>("Texture3D loading error occurred!"));
				Logger::getInstance()->saveLog(Log<string>(name));
			}

			if(!ilConvertImage(IL_RGB,IL_UNSIGNED_BYTE))
			{
				Logger::getInstance()->saveLog(Log<string>("Texture3D converting error occurred!"));
				Logger::getInstance()->saveLog(Log<string>(name));
			}

			glGenTextures(1,texture3D->getTexture());
			glBindTexture(GL_TEXTURE_3D,*texture3D->getTexture());
			glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

			glTexImage3D(GL_TEXTURE_3D,0,ilGetInteger(IL_IMAGE_BPP),ilGetInteger(IL_IMAGE_WIDTH),
				  ilGetInteger(IL_IMAGE_HEIGHT),ilGetInteger(IL_IMAGE_DEPTH),0,ilGetInteger(IL_IMAGE_FORMAT),GL_UNSIGNED_BYTE,ilGetData());
			
			ilDeleteImages(1,&texID);

			return texture3D;
		}

		/**
		 * Method is used to load and create texture rect which can be used in Sprite and text rendering.
		 * @param	name is resource name.
		 * @param	path is resource file path.
		 * @return	pointer to loaded and created RECTANGLE resource.
		 */
		Texture* TextureFactory::createRectangleTexture(const string& name, const string& path)
		{
			Texture* textureRect = new Texture(name.c_str(),path.c_str());
			textureRect->setTextureType(RECTANGLE);

			ILuint texID;
			ilGenImages(1,&texID);
			ilBindImage(texID);
			
			if(!ilLoadImage((const ILstring)path.c_str()))
			{
				Logger::getInstance()->saveLog(Log<string>("Texture Rectangle loading error occurred!"));
				Logger::getInstance()->saveLog(Log<string>(name));
			}

			if(!ilConvertImage(IL_RGBA,IL_UNSIGNED_BYTE))
			{
				Logger::getInstance()->saveLog(Log<string>("Texture Rectangle converting error occurred!"));
				Logger::getInstance()->saveLog(Log<string>(name));
			}

			glGenTextures(1,textureRect->getTexture());
			glBindTexture(GL_TEXTURE_RECTANGLE,*textureRect->getTexture());

			glTexParameteri(GL_TEXTURE_RECTANGLE,GL_TEXTURE_WRAP_S,GL_CLAMP);
			glTexParameteri(GL_TEXTURE_RECTANGLE,GL_TEXTURE_WRAP_T,GL_CLAMP);
			glTexParameteri(GL_TEXTURE_RECTANGLE,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_RECTANGLE,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

			glTexImage2D(GL_TEXTURE_RECTANGLE,0,ilGetInteger(IL_IMAGE_BPP),ilGetInteger(IL_IMAGE_WIDTH),
				  ilGetInteger(IL_IMAGE_HEIGHT),0,ilGetInteger(IL_IMAGE_FORMAT),GL_UNSIGNED_BYTE,ilGetData());
		
			ilDeleteImages(1, &texID);

			return textureRect;
		}

		/**
		 * Method is used to load and create cube map texture which can be used in sky mapping and cube mapping
		 * @param	name is resource name.
		 * @param	path is resource file path.
		 * @param	path2 is resource file path2.
		 * @param	path3 is resource file path3.
		 * @param	path4 is resource file path4.
		 * @param	path5 is resource file path5.
		 * @param	path6 is resource file path6.
		 * @return	pointer to loaded and created CUBE_MAP resource.
		 */
		Texture* TextureFactory::createCubeMapTexture(const string& name, const string& path, const string& path2, const string& path3, const string& path4, const string& path5, const string& path6)
		{
			Texture* cubeMap = new Texture(name.c_str(), path.c_str());
			cubeMap->setTextureType(CUBE_MAP);

			string filePath; 
			ILuint texID;

			glGenTextures(1,cubeMap->getTexture());
			glBindTexture(GL_TEXTURE_CUBE_MAP,*cubeMap->getTexture());
			ilGenImages(1,&texID);
			ilBindImage(texID);
			
			if(!ilLoadImage((const ILstring)path.c_str()))
			{
				Logger::getInstance()->saveLog(Log<string>("Texture Cubemap loading error occurred!"));
				Logger::getInstance()->saveLog(Log<string>(name));
			}

			if(!ilConvertImage(IL_RGB,IL_UNSIGNED_BYTE))
			{
				Logger::getInstance()->saveLog(Log<string>("Texture Cubemap converting error occurred!"));
				Logger::getInstance()->saveLog(Log<string>(name));
			}

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,0,ilGetInteger(IL_IMAGE_BPP),ilGetInteger(IL_IMAGE_WIDTH),
				ilGetInteger(IL_IMAGE_HEIGHT),0,ilGetInteger(IL_IMAGE_FORMAT),GL_UNSIGNED_BYTE,ilGetData());

			ilDeleteImages(1, &texID);

			ilGenImages(1,&texID);
			ilBindImage(texID);
			
			if(!ilLoadImage((const ILstring)path2.c_str()))
			{
				Logger::getInstance()->saveLog(Log<string>("Texture Cubemap loading error occurred!"));
				Logger::getInstance()->saveLog(Log<string>(name));
			}

			if(!ilConvertImage(IL_RGB,IL_UNSIGNED_BYTE))
			{
				Logger::getInstance()->saveLog(Log<string>("Texture Cubemap converting error occurred!"));
				Logger::getInstance()->saveLog(Log<string>(name));
			}

			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,0,ilGetInteger(IL_IMAGE_BPP),ilGetInteger(IL_IMAGE_WIDTH),
				ilGetInteger(IL_IMAGE_HEIGHT),0,ilGetInteger(IL_IMAGE_FORMAT),GL_UNSIGNED_BYTE,ilGetData());

			ilDeleteImages(1,&texID);

			ilGenImages(1,&texID);
			ilBindImage(texID);
			
			if(!ilLoadImage((const ILstring)path3.c_str()))
			{
				Logger::getInstance()->saveLog(Log<string>("Texture Cubemap loading error occurred!"));
				Logger::getInstance()->saveLog(Log<string>(name));
			}

			if(!ilConvertImage(IL_RGB,IL_UNSIGNED_BYTE))
			{
				Logger::getInstance()->saveLog(Log<string>("Texture Cubemap converting error occurred!"));
				Logger::getInstance()->saveLog(Log<string>(name));
			}

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,0,ilGetInteger(IL_IMAGE_BPP),ilGetInteger(IL_IMAGE_WIDTH),
				ilGetInteger(IL_IMAGE_HEIGHT),0,ilGetInteger(IL_IMAGE_FORMAT),GL_UNSIGNED_BYTE,ilGetData());

			ilDeleteImages(1, &texID);

			ilGenImages(1,&texID);
			ilBindImage(texID);
			
			if(!ilLoadImage((const ILstring)path4.c_str()))
			{
				Logger::getInstance()->saveLog(Log<string>("Texture Cubemap loading error occurred!"));
				Logger::getInstance()->saveLog(Log<string>(name));
			}

			if(!ilConvertImage(IL_RGB,IL_UNSIGNED_BYTE))
			{
				Logger::getInstance()->saveLog(Log<string>("Texture Cubemap converting error occurred!"));
				Logger::getInstance()->saveLog(Log<string>(name));
			}

			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,0,ilGetInteger(IL_IMAGE_BPP),ilGetInteger(IL_IMAGE_WIDTH),
				ilGetInteger(IL_IMAGE_HEIGHT),0,ilGetInteger(IL_IMAGE_FORMAT),GL_UNSIGNED_BYTE,ilGetData());

			ilDeleteImages(1, &texID);

			ilGenImages(1,&texID);
			ilBindImage(texID);
			
			if(!ilLoadImage((const ILstring)path5.c_str()))
			{
				Logger::getInstance()->saveLog(Log<string>("Texture Cubemap loading error occurred!"));
				Logger::getInstance()->saveLog(Log<string>(name));
			}

			if(!ilConvertImage(IL_RGB,IL_UNSIGNED_BYTE))
			{
				Logger::getInstance()->saveLog(Log<string>("Texture Cubemap converting error occurred!"));
				Logger::getInstance()->saveLog(Log<string>(name));
			}

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,0,ilGetInteger(IL_IMAGE_BPP),ilGetInteger(IL_IMAGE_WIDTH),
				ilGetInteger(IL_IMAGE_HEIGHT),0,ilGetInteger(IL_IMAGE_FORMAT),GL_UNSIGNED_BYTE,ilGetData());

			ilDeleteImages(1, &texID);

			ilGenImages(1,&texID);
			ilBindImage(texID);
			
			if(!ilLoadImage((const ILstring)path6.c_str()))
			{
				Logger::getInstance()->saveLog(Log<string>("Texture Cubemap loading error occurred!"));
				Logger::getInstance()->saveLog(Log<string>(name));
			}

			if(!ilConvertImage(IL_RGB,IL_UNSIGNED_BYTE))
			{
				Logger::getInstance()->saveLog(Log<string>("Texture Cubemap converting error occurred!"));
				Logger::getInstance()->saveLog(Log<string>(name));
			}

			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,0,ilGetInteger(IL_IMAGE_BPP),ilGetInteger(IL_IMAGE_WIDTH),
				ilGetInteger(IL_IMAGE_HEIGHT),0,ilGetInteger(IL_IMAGE_FORMAT),GL_UNSIGNED_BYTE,ilGetData());

			ilDeleteImages(1,&texID);

			glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
			glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

			return cubeMap;
		}
	}
}
