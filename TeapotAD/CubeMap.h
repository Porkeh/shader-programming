#pragma once


#include "gl_core_4_3.hpp"
#include <string>
#include <stdlib.h>
#include"Bitmap.h"
#include"Texture.h"


class CubeMap
{
private:

	unsigned int cm_VAOHandle;
	GLuint cm_texID;



public:

	CubeMap();
	~CubeMap();
	GLuint GetTexID();
	void Initialize();
	void Render();






};

