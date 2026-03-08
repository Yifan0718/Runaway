#include "runaway/Framework/SpriteManager.hpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

#include <SOIL/SOIL.h>

#include "runaway/utils.hpp"

SpriteManager::SpriteManager()
: m_spriteInfos()
{
	m_spriteInfos.insert({
		EncodeAnim(ImageID::BACKGROUND, AnimID::NO_ANIMATION),
		SpriteInfo{
			"game_bg.png",
			2 * WINDOW_WIDTH,
			WINDOW_HEIGHT,
			2 * WINDOW_WIDTH,
			WINDOW_HEIGHT
		}
	});
	
	m_spriteInfos.insert({
		EncodeAnim(ImageID::PLAYER, AnimID::IDLE),
		SpriteInfo{
			"Punk_run_gun_24f_remake.png",
			100 * 6,
			100 * 4,
			100,
			100,
			6,
			24
		}
	});
	m_spriteInfos.insert({
		EncodeAnim(ImageID::PLAYER, AnimID::BOOST),
		SpriteInfo{
			"Punk_run_gun_24f_remake.png",
			500 * 6,
			500 * 4,
			500,
			500,
			6,
			24
		}
	});
	m_spriteInfos.insert({
		EncodeAnim(ImageID::BULLET, AnimID::NO_ANIMATION),
		SpriteInfo{
			"player_bullet.png",
			10,
			10,
			10,
			10
		}
	});
	m_spriteInfos.insert({
		EncodeAnim(ImageID::PLAYER, AnimID::JUMP),
		SpriteInfo{
			"Punk_jump_24f_remake.png",
			100 * 6,
			100 * 4,
			100,
			100,
			6,
			24
		}
	});
	m_spriteInfos.insert({
		EncodeAnim(ImageID::GOBLIN, AnimID::IDLE),
		SpriteInfo{
			"goblin_Idle_24f_remake.png",
			100 * 6,
			100 * 4,
			100,
			100,
			6,
			24
		}
	});
	m_spriteInfos.insert({
		EncodeAnim(ImageID::GOBLIN, AnimID::THROW),
		SpriteInfo{
			"goblin_throw_24f_remake.png",
			100 * 6,
			100 * 4,
			100,
			100,
			6,
			24
		}
	});
	m_spriteInfos.insert({
		EncodeAnim(ImageID::GOBLIN, AnimID::HURT),
		SpriteInfo{
			"goblin_hurt_24f_remake.png",
			100 * 6,
			100 * 4,
			100,
			100,
			6,
			24
		}
	});
	m_spriteInfos.insert({
		EncodeAnim(ImageID::AXE, AnimID::NO_ANIMATION),
		SpriteInfo{
			"axe_rotation_grid.png",
			6 * 25,
			4 * 25,
			25,
			25,
			6,
			24
		}
	});
}

bool SpriteManager::LoadSprites()
{
	if (m_loaded)
	{
		return true;
	}
	
	glEnable(GL_DEPTH_TEST);
	for (auto &asset : m_spriteInfos)
	{
		int width, height;
		unsigned char *image = SOIL_load_image(
			asset.second.filename.c_str(),
			&width,
			&height,
			0,
			SOIL_LOAD_RGBA
			);
		
		// GLuint texture;
		// glGenTextures(1, &texture);
		// glBindTexture(GL_TEXTURE_2D, texture);
		// glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		////glGenerateMipmaps(GL_TEXTURE_2D);
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		// gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, image);
		// SOIL_free_image_data(image);
		
		GLuint texture = SOIL_load_OGL_texture(
			asset.second.filename.c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT
			);
		if (0 == texture)
		{
			std::cout << "Error loading " << asset.second.filename << std::endl
			<< "-- SOIL loading error : " << SOIL_last_result() << std::endl;
			return false;
		}
		
		asset.second.texture = texture;
	}
	
	m_loaded = true;
	return true;
}

// GLuint SpriteManager::GetTexture(ImageID imageID) const {
//	auto it = m_textureMap.find(imageID);
//	if (it == m_textureMap.end()) {
//		return 0;
//	}
//	else {
//		return it->second;
//	}
// }

SpriteInfo SpriteManager::GetSpriteInfo(ImageID imageID, AnimID animID) const
{
	auto it = m_spriteInfos.find(EncodeAnim(imageID, animID));
	if (it == m_spriteInfos.end())
	{
		return SpriteInfo("", 0, 0, 0, 0);
	}
	else
	{
		return it->second;
	}
}

