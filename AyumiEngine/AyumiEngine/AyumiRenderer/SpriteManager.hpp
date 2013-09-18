/**
 * File contains declaration of SpriteManager class.
 * @file    SpriteManager.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-10-25
 */

#ifndef SPRITEMANAGER_HPP
#define SPRITEMANAGER_HPP

#include <vector>
#include <string>

#include "Sprite.hpp"
#include "DefinedShader.hpp"
#include "../Logger.hpp"

namespace AyumiEngine
{
	namespace AyumiRenderer
	{
		typedef std::pair<Sprite*, AyumiMath::Vector3D> TextElement;
		typedef std::pair<std::string,std::vector<TextElement>> Text;
		typedef std::vector<Text> TextBatch;
		typedef std::vector<Sprite*> SpriteBatch;
	
		/**
		 * Class represents SpriteManager which is one Renderer managers used to create, store and update
		 * 2D images like Sprites, Text and fullscreen quads for post-process effects. They are used to create
		 * Engine GUI, games Head Up Display etc. SpriteManager can also create empty Sprite for post-processing
		 * RenderPassem and create bitmap font charset and create texts on screen.
		 */
		class SpriteManager
		{
		private:
			SpriteBatch spriteCollection;
			TextBatch textCollection;
			Sprite* fontCharset;
			AyumiResource::Shader* spriteShader;

			void initializeSpriteShader();

		public:
			SpriteManager();
			~SpriteManager();

			void initializeSpriteManager();
			void initializeFont(AyumiResource::Texture* fontTexturem, const int size);
			Sprite* createSprite(AyumiResource::Texture* spriteTexture, AyumiResource::Shader* spriteShader, const AyumiMath::Vector3D& position, const AyumiMath::Vector3D& size);		

			void addSprite(const std::string& name, AyumiResource::Texture* spriteTexture, const AyumiMath::Vector3D& position, const AyumiMath::Vector3D& size, const float alpha);	
			void updateSprite(const std::string& name, const AyumiMath::Vector3D& position, const AyumiMath::Vector3D& size, const float alpha);
			void createText(const std::string& name, const std::string& text, const AyumiMath::Vector3D position);
			void updateText(const std::string& name, const std::string& text);
			void deleteSprite(const std::string name);
			void deleteText(const std::string& name);
			
			void clearSpriteCollection();
			void clearTextCollection();
		
			SpriteBatch* getSpriteCollection();
			TextBatch* getTextCollection();
		};
	}
}
#endif
