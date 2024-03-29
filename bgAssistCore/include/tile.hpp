
#pragma once

#include <prismTop.hpp>
#include <token.hpp>

#include <list>
using namespace std;

class token;

void setGlobalTileUnitLength(GLfloat inLength);
GLfloat getGlobalTileUnitLength();

class tile {
public:

	// Constructor, desctructor, copy constructor
	tile(ivec2 inDimensions);
	tile(ivec2 inDimensions, GLfloat inRelativeThickness);
	~tile();
	tile(const tile & inTile) { copyTile(inTile); }
	tile(const tile && inTile) { copyTile(inTile); }
	tile & operator = (const tile & inTile) { copyTile(inTile); return *this; }

	void addChildToken(token * inChild);
	void removeChildToken(token * inChild);
	void drawChildTokens();

	// Set location (in xy plane only)
	void setLocation(vec2 location);

	// Accessor functions to underlying prism
	void setProgramId(GLuint inProgramId) { rectPrism.setProgramId(inProgramId); }
	void setCamera(timedMat4 *inCamera) { rectPrism.setCamera(inCamera); }
	void setProjection(timedMat4 *inProjection) { rectPrism.setProjection(inProjection); }
	void setLight(lightSource * inLight) { rectPrism.setLight(inLight); }
	void setAmbientRatio(GLfloat inAmbientRatio) { rectPrism.setAmbientRatio(inAmbientRatio); }
	void setSpecularRatio(GLfloat inSpecularRatio) { rectPrism.setSpecularRatio(inSpecularRatio); }
	timedMat4 & getCamera() { return rectPrism.getCamera(); }
	timedMat4 & getProjection() { return rectPrism.getProjection(); }
	void loadFaceImage(const char * imagepath) { rectPrism.loadFaceImage(imagepath, true); }
	void loadSideImage(const char * imagepath) { rectPrism.loadSideImage(imagepath, true); }
	void draw() { rectPrism.draw(); drawChildTokens(); }
	void setGlfwCursorPosCallback(void(*inFunc)(GLFWwindow* window, double x, double y)) { rectPrism.glfwCursorPosCallback = inFunc; }
	void setGlfwMouseButtonCallback(void(*inFunc)(GLFWwindow* window, int button, int action, int mods)) { rectPrism.glfwMouseButtonCallback = inFunc; }

	// Test ray intersection
	GLboolean testRayOBBIntersection(vec3 ray_origin, vec3 ray_direction);
	token * findChildRayIntersection(vec3 ray_origin, vec3 ray_direction);


private:
	list<token *> tokenList;
	ivec2 tileDimensions;
	GLfloat relativeThickness;
	prismTop rectPrism;

	// Constructor, copy constructor
	void constructTile(ivec2 inDimensions, GLfloat inRelativeThickness);
	void copyTile(const tile & inTile);
};


