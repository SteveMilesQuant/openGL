
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtx/transform.hpp>
using namespace glm;

namespace glm {
	class timedMat4 {
	public:
		timedMat4() { setMatrix(mat4(1.0f)); }
		timedMat4(mat4 inMatrix) { setMatrix(inMatrix); }

		void setMatrix(mat4 inMatrix) { matrix = inMatrix; noteTime(); }
		const mat4 & getMatrix() { return matrix; }
		double timeUpdated() { return timeWasUpdated; }

	private:
		mat4 matrix;
		double timeWasUpdated;

		void noteTime() { timeWasUpdated = glfwGetTime(); }
	};

	class lightSource {
	public:
		lightSource() {
			position = vec3(0, 0, 0);
			power = 50.0f;
			color = vec3(1, 1, 1);
		}
		lightSource(const lightSource &inLightSource) {
			position = inLightSource.position;
			power = inLightSource.power;
			color = inLightSource.color;
		}
		vec3 position;
		GLfloat power;
		vec3 color;
	};
};

void screenPosToWorldRay(
	int mouseX, int mouseY,             // Mouse position, in pixels, from bottom-left corner of the window
	int screenWidth, int screenHeight,  // Window size, in pixels
	mat4 ViewMatrix,               // Camera position and orientation
	mat4 ProjectionMatrix,         // Camera parameters (ratio, field of view, near and far planes)
	vec3& out_origin,              // Ouput : Origin of the ray. /!\ Starts at the near plane, so if you want the ray to start at the camera's position instead, ignore this.
	vec3& out_direction            // Ouput : Direction, in world space, of the ray that goes "through" the mouse.
);

bool testRayOBBIntersection(
	vec3 ray_origin,        // Ray origin, in world space
	vec3 ray_direction,     // Ray direction (NOT target position!), in world space. Must be normalize()'d.
	vec3 aabb_min,          // Minimum X,Y,Z coords of the mesh when not transformed at all.
	vec3 aabb_max,          // Maximum X,Y,Z coords. Often aabb_min*-1 if your mesh is centered, but it's not always the case.
	mat4 ModelMatrix,       // Transformation applied to the mesh (which will thus be also applied to its bounding box)
	float& intersection_distance // Output : distance between ray_origin and the intersection with the OBB
);

vec2 screenPosTo2DCoord(GLFWwindow* window);
vec2 screenPosTo2DCoord(GLFWwindow* window, double x, double y);

GLboolean testPointInBox(vec2 testPoint, vec2 boxUpperLeftCornerLocation, vec2 boxDimensions);
