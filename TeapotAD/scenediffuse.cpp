
#include "scenediffuse.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
using std::cerr;
using std::endl;

#include "defines.h"

using glm::vec3;


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>


namespace imat3111
{
/////////////////////////////////////////////////////////////////////////////////////////////
// Default constructor
/////////////////////////////////////////////////////////////////////////////////////////////
SceneDiffuse::SceneDiffuse()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////
//Initialise the scene
/////////////////////////////////////////////////////////////////////////////////////////////
void SceneDiffuse::initScene(QuatCamera camera)
{
    //|Compile and link the shader  
	compileAndLinkShader();
	boxProg.use();
    gl::Enable(gl::DEPTH_TEST);

 	//Set up the lighting
	

	cubeMap = new CubeMap();
	cubeMap->Initialize();

	
	skyBox = new VBOCube();
	skyBox->Initialize();
	//Create the plane to represent the ground
	plane = new VBOPlane(100.0,100.0,100,100);



	//A matrix to move the teapot lid upwards
	glm::mat4 lid = glm::mat4(1.0);
	//lid *= glm::translate(vec3(0.0,1.0,0.0));

	reflectProg.use();
	//Create the teapot with translated lid
	teapot = new VBOTeapot(16,lid);
	teapot2 = new VBOTeapot(16, lid);




}

/////////////////////////////////////////////////////////////////////////////////////////////
//Update not used at present
/////////////////////////////////////////////////////////////////////////////////////////////
void SceneDiffuse::update( float t )
{

}

/////////////////////////////////////////////////////////////////////////////////////////////
// Set up the lighting variables in the shader
/////////////////////////////////////////////////////////////////////////////////////////////
void SceneDiffuse::setLightParams(QuatCamera camera)
{

	//vec3 worldLight = vec3(10.0f,10.0f,10.0f);
   	//
	//prog.setUniform("La", vec3(0.1f, 0.1f, 0.1f));
    //prog.setUniform("Ld", 1.0f, 1.0f, 1.0f);
  ////  prog.setUniform("LightPosition", camera.view() * vec4(worldLight,1.0) );
	//prog.setUniform("LightPosition", worldLight );
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Render the scene
/////////////////////////////////////////////////////////////////////////////////////////////
void SceneDiffuse::render(QuatCamera camera)
{
    gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

	boxProg.use();

	model = mat4(1.0f);
	boxProg.setUniform("M", model);
	boxProg.setUniform("V", camera.view());
	boxProg.setUniform("P", camera.projection());
	

	skyBox->render();
	//First deal with the plane to represent the ground

	//Initialise the model matrix for the plane
	//Set the plane's material properties in the shader and render
	
	
	
	reflectProg.use();
	//Now set up the teapot 
	 model = mat4(1.0f);
	 model[3] = vec4(vec3(-5, 0, 0), 1.0f);
;

	 reflectProg.setUniform("M", model);
	 reflectProg.setUniform("V", camera.view());
	 reflectProg.setUniform("P", camera.projection());
	
	 //Set the Teapot material properties in the shader and render
	 teapot->render();

	 refractProg.use();
	 model = mat4(1.0f);
	 model[3] = vec4(vec3(5, 0, 0), 1.0f);
	 reflectProg.setUniform("M", model);
	 reflectProg.setUniform("V", camera.view());
	 reflectProg.setUniform("P", camera.projection());
	 teapot2->render();
	 
}


/////////////////////////////////////////////////////////////////////////////////////////////
//Send the MVP matrices to the GPU
/////////////////////////////////////////////////////////////////////////////////////////////
void SceneDiffuse::setMatrices(QuatCamera camera)
{

    mat4 mv = camera.view() * model;
    reflectProg.setUniform("ModelViewMatrix", mv);
   
    reflectProg.setUniform("MVP", camera.projection() * mv);
	// the correct matrix to transform the normal is the transpose of the inverse of the M matrix
	 mat3 normMat = glm::transpose(glm::inverse(mat3(model)));
	
}

/////////////////////////////////////////////////////////////////////////////////////////////
// resize the viewport
/////////////////////////////////////////////////////////////////////////////////////////////
void SceneDiffuse::resize(QuatCamera camera,int w, int h)
{
    gl::Viewport(0,0,w,h);
    width = w;
    height = h;
	camera.setAspectRatio((float)w/h);

}

/////////////////////////////////////////////////////////////////////////////////////////////
// Compile and link the shader
/////////////////////////////////////////////////////////////////////////////////////////////
void SceneDiffuse::compileAndLinkShader()
{
   
	try {
    	reflectProg.compileShader("Shaders/reflection.vert");
    	reflectProg.compileShader("Shaders/reflection.frag");
    	reflectProg.link();
    	reflectProg.validate();
    	
    } catch(GLSLProgramException & e) {
 		cerr << e.what() << endl;
 		exit( EXIT_FAILURE );
    }


	try {
		boxProg.compileShader("Shaders/skybox.vert");
		boxProg.compileShader("Shaders/skybox.frag");
		boxProg.link();
		boxProg.validate();

	}
	catch (GLSLProgramException & e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}

	try {
		refractProg.compileShader("Shaders/refraction.vert");
		refractProg.compileShader("Shaders/refraction.frag");
		refractProg.link();
		refractProg.validate();

	}
	catch (GLSLProgramException & e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

}
