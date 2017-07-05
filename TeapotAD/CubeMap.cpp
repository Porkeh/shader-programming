#include "CubeMap.h"



CubeMap::CubeMap()
{

}

CubeMap::~CubeMap()
{

}

GLuint CubeMap::GetTexID()
{
	return cm_texID;
}

void CubeMap::Initialize()
{
	gl::ActiveTexture(gl::TEXTURE0);
	gl::GenTextures(1, &cm_texID);
	gl::BindTexture(gl::TEXTURE_CUBE_MAP, cm_texID);


	for (int i = 0; i < 6; i++) {
		
		std::string textureFile = std::string("images/TowerHousepano_") + std::to_string(i + 1) + ".jpg";
		Bitmap bmp = Bitmap::bitmapFromFile(textureFile);
		gl::TexImage2D(gl::TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0, gl::RGB,
			bmp.width(), bmp.height(), 0,
			gl::RGB, gl::UNSIGNED_BYTE,
			bmp.pixelBuffer());
	}

	gl::TexParameteri(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
	gl::TexParameteri(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
	gl::TexParameteri(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_WRAP_S, gl::CLAMP_TO_EDGE);
	gl::TexParameteri(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_WRAP_T, gl::CLAMP_TO_EDGE);
	gl::TexParameteri(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_WRAP_R, gl::CLAMP_TO_EDGE);



}


void CubeMap::Render()
{

}