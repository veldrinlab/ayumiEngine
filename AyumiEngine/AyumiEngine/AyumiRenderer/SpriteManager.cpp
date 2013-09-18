/**
 * File contains definition of SpriteManager class.
 * @file    SpriteManager.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-10-25
 */

#include "SpriteManager.hpp"

using namespace std;
using namespace AyumiEngine::AyumiResource;
using namespace AyumiEngine::AyumiMath;

namespace AyumiEngine
{
	namespace AyumiRenderer
	{
		/**
		 * Class default constructor. Create Sprite rendering shader object.
		 */
		SpriteManager::SpriteManager()
		{
			spriteShader = new Shader("Sprite");
			fontCharset = nullptr;
		}

		/**
		 * Class destructor, free allocated memory. Clear sprite/text collecion, delete font charset and sprite shader.
		 */
		SpriteManager::~SpriteManager()
		{
			clearSpriteCollection();
			clearTextCollection();
			if(fontCharset != nullptr)
				delete [] fontCharset;
			delete spriteShader;
		}

		/**
		 * Method is used to initialize SpriteManager. Init sprites rendering shader.
		 */
		void SpriteManager::initializeSpriteManager()
		{
			initializeSpriteShader();
		}

		/**
		 * Method is used to initialize bitmap font charset and store it in SpriteManager.
		 * @param	fontTexture is pointer to bitmap font texture resource.
		 * @param	size is font size in px.
		 */
		void SpriteManager::initializeFont(Texture* fontTexture, const int size)
		{		
			fontCharset = new Sprite[256];
			
			float x = 0.0f;
			float y = 0.0f;

			for(int i = 0; i < 256; ++i)
			{
				x = (static_cast<float>(i%16)/16)*size*16.0f;
				y = (static_cast<float>(i/16)/16)*size*16.0f;

				fontCharset[i].setTexture(fontTexture);
				fontCharset[i].setShader(spriteShader);
				fontCharset[i].setSize(static_cast<float>(size),static_cast<float>(size));
				fontCharset[i].initializeSprite(x,y);

			}
		}

		/**
		 * Method is used to create sprite for post-processing full-screen quad. It is used by RenderPass rendering task.
		 * Result of off-screen rendering is used as a Sprite texture.
		 * @param	spriteTexture is pointer to off-screen rendering render buffer.
		 * @param	spriteShader is pointer to fullscreen rendering shader.
		 * @param	position is sprite postion vector.
		 * @param	size is sprite scale vector.
		 * @return	return pointer to created sprite object.
		 */
		Sprite* SpriteManager::createSprite(Texture* spriteTexture, Shader* spriteShader, const Vector3D& position, const Vector3D& size)
		{
			Sprite* sprite = new Sprite(spriteTexture,position,size,1.0f);
			sprite->setShader(spriteShader);
			sprite->initializeSprite();
			return sprite;
		}

		/**
		 * Method is used to add new Sprite object to sprite collection.
		 * @param	name is sprite name.
		 * @param	spriteTexture is pointer to sprite texture resource.
		 * @param	position is sprite postion vector.
		 * @param	size is sprite scale vector.
		 * @param	alpha is sprite alpha channel.
		 */
		void SpriteManager::addSprite(const string& name, Texture* spriteTexture, const Vector3D& position, const Vector3D& size, const float alpha)
		{
			Sprite* sprite = new Sprite(spriteTexture,position,size,alpha);
			sprite->setShader(spriteShader);
			sprite->initializeSprite();
			sprite->setName(name);
			spriteCollection.push_back(sprite);
		}

		/**
		 * Method is used to update Sprite Sprite object from sprite collection.
		 * @param	name is sprite name id.
		 * @param	position is sprite new postion vector.
		 * @param	size is sprite new scale vector.
		 * @param	alpha is sprite new alpha channel.
		 */
		void SpriteManager::updateSprite(const string& name, const Vector3D& position, const Vector3D& size, const float alpha)
		{
			SpriteBatch::const_iterator it = spriteCollection.begin();
			for(; it != spriteCollection.end(); ++it)
				if((*it)->getName() == name)
					break;
			if(it != spriteCollection.end())
			{
				(*it)->setPosition(position[0],position[1]);
				(*it)->setSize(size[0],size[1]);
				(*it)->setAlpha(alpha);
			}
		}
		
		/**
		 * Method is used to create new text and add text sprites to sprite collection.
		 * @param	nam is text name id.
		 * @param	text is new text string.
		 * @param	position is sprite position vector.
		 */
		void SpriteManager::createText(const string& name, const string& text, const Vector3D position)
		{
			vector<TextElement> chars;

			for(unsigned int i = 0; i < text.length(); ++i)
			{
				int asciiNumber = text.at(i);
				Sprite* charSprite = &fontCharset[asciiNumber];
				Vector3D charPosition = position;
				charPosition.setX(charPosition.x() + 32.0f * i);
				chars.push_back(make_pair(charSprite,charPosition));
			}

			textCollection.push_back(make_pair(name,chars));
		}

		/**
		 * Method is used to update text string for example displaying value of debug information, time, scores.
		 * @param	name is text sprite id.
		 * @param	text is new text.
		 */
		void SpriteManager::updateText(const string& name, const string& text)
		{
			TextBatch::iterator it = textCollection.begin();
			for(; it != textCollection.end(); ++it)
				if((*it).first == name)
					break;

			if(it != textCollection.end())
			{
				vector<TextElement> chars;
				
				for(unsigned int i = 0; i < text.length(); ++i)
				{
					int asciiNumber = text.at(i);
					Sprite* charSprite = &fontCharset[asciiNumber];
					Vector3D charPosition = (*it).second.at(0).second;
					charPosition.setX(charPosition.x() + 32.0f * i);
					chars.push_back(make_pair(charSprite,charPosition));
				}
				(*it).second = chars;
			}
		}

		/**
		 * Method is used to delete Sprite object from sprites collection.
		 * @param	name is sprite name.
		 */
		void SpriteManager::deleteSprite(const string name)
		{
			SpriteBatch::const_iterator it = spriteCollection.begin();
			for(; it != spriteCollection.end(); ++it)
				if((*it)->getName() == name)
					break;
			if(it != spriteCollection.end())
			{
				delete (*it);
				spriteCollection.erase(it);
			}
		}

		/**
		 * Method is used to delete text sprites from texts collection.
		 * @param	name is text sprites name.
		 */
		void SpriteManager::deleteText(const string& name)
		{
			TextBatch::const_iterator it = textCollection.begin();
			for(; it != textCollection.end(); ++it)
				if((*it).first == name)
					break;

			if(it != textCollection.end())
				textCollection.erase(it);
		}
		
		/**
		 * Method is used to clear all sprite data.
		 */
		void SpriteManager::clearSpriteCollection()
		{
			for(SpriteBatch::const_iterator it = spriteCollection.begin(); it != spriteCollection.end(); ++it)
				delete (*it);
			spriteCollection.clear();
		}
		
		/**
		 * Method is used to clear all stored text data.
		 */
		void SpriteManager::clearTextCollection()
		{
			textCollection.clear();
		}

		/**
		 * Accessor to private sprite collection memebr.
		 * @return	pointer to sprite collection.
		 */
		SpriteBatch* SpriteManager::getSpriteCollection()
		{
			return &spriteCollection;
		}

		/**
		 * Accessor to private text collection memebr.
		 * @return	pointer to text collection.
		 */
		TextBatch* SpriteManager::getTextCollection()
		{
			return &textCollection;
		}

		/**
		 * Private method which is used to load and compile sprites rendering shader.
		 */
		void SpriteManager::initializeSpriteShader()
		{
			spriteShader->setVertexPath("null");
			spriteShader->setFragmentPath("null");
			spriteShader->createVertexShader();
			spriteShader->createFragmentShader();

			const char* vertexShaderSource = spriteVertexShader;
			const char* fragmentShaderSource = spriteFragmentShader;

			if(vertexShaderSource == nullptr || fragmentShaderSource == nullptr)
				Logger::getInstance()->saveLog(Log<string>("Sprite shader loading error detected: "));
		
			glShaderSource(spriteShader->getShaderVertex(),1,&vertexShaderSource,0);
			glShaderSource(spriteShader->getShaderFragment(),1,&fragmentShaderSource,0);
			glCompileShader(spriteShader->getShaderVertex());
			glCompileShader(spriteShader->getShaderFragment());
			spriteShader->createShaderProgram();
			glAttachShader(spriteShader->getShaderProgram(),spriteShader->getShaderVertex());
			glAttachShader(spriteShader->getShaderProgram(),spriteShader->getShaderFragment());
			glLinkProgram(spriteShader->getShaderProgram());
		}
	}
}
