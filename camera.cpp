#include "stdafx.h"
#include "camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>
#include <math.h>

double lrx = 0;

bool rdown = false;
double lastx, lasty, xs, ys, xe, ye;
double rx = 0;
double ry = 0;
double mydiff = 0.000001;
extern engine eng;
glm::quat currot(1.0, 0, 0, 0);

arcball_camera::arcball_camera()
{
	cdist = 5;
}
arcball_camera::~arcball_camera()
{
}
glm::mat4 arcball_camera::getview()
{ 
	cdist += mydiff / 5;
	mydiff = 0;

	glm::mat4 v = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -cdist) );
	
	v = glm::rotate( v, (float)ry / 100, glm::vec3(-1.0f, 0.0f, 0.0f));
	
	v = glm::rotate(v, (float)rx / 100, glm::vec3(0.0f, 1.0f, 0.0f));

	return v;
}

glm::vec3 arcball_camera::getpos()
{
	return inverse(getview())[3];
}

void arcball_camera::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		rdown = true;
		glfwGetCursorPos(window, &lastx, &lasty);
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
	{
		rdown = false;
		currot = glm::angleAxis(glm::radians((float)ry / 100), glm::vec3(1.0f, 0.0f, 0.0f));
	}
}
void arcball_camera::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (rdown)
	{
		ry += lasty - ypos;

		bool n = ry < 0 ? true : false;
		ry = abs(ry);

		rx -= lastx - xpos;
	
		ry = n ? -ry : ry;

		lastx = xpos;
		lasty = ypos;
	}
}
void arcball_camera::mouse_wheel_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	mydiff = -yoffset;
}
qball_camera::qball_camera()
{
	cdist = 5;
}
qball_camera::~qball_camera()
{
}

int ct = 0;
glm::quat oldrot = glm::quat(1,0,0,0);

glm::mat4 qball_camera::getview()
{
	cdist += mydiff / 5;
	mydiff = 0;


	glm::mat4 viewm = glm::translate(glm::mat4(1.0f), glm::vec3(0, -3, -cdist));
	glm::vec3 mouseaxis = glm::normalize(glm::vec3(xe - xs, ye - ys, 0));
	glm::vec3 rightaxis = glm::normalize(glm::cross(mouseaxis, glm::vec3(0, 1, 0)));
	glm::vec3 rotaxis = glm::normalize(glm::cross(mouseaxis, rightaxis));


	if (ct > 1000)
	{
		ct = 0;
		cout << "x:" << rotaxis.x << " y:" << rotaxis.y << " z:" << rotaxis.z << endl;
	}
	else ct++;


	glm::quat xrot = glm::angleAxis( glm::radians( glm::length(glm::vec3(xe - xs, ye - ys, 0))/ 10 ) , rotaxis);

	viewm = glm::mat4_cast(xrot);
	return viewm;
}

glm::vec3 qball_camera::getpos()
{
	return inverse(getview())[3];
}


void qball_camera::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		rdown = true;
		glfwGetCursorPos(window, &xs, &ys);

	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
	{
		rdown = false;
	}
}
void qball_camera::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (rdown)
	{
		glfwGetCursorPos(window, &xe, &ye);
	}
}
void qball_camera::mouse_wheel_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	mydiff = -yoffset;
}