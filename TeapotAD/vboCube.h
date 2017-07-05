#pragma once


#include "drawable.h"
#include "gl_core_4_3.hpp"

class VBOCube : public Drawable
{
private:
	GLuint vaoHandle;
public:
	VBOCube();
	void Initialize();
	void render() const;


};