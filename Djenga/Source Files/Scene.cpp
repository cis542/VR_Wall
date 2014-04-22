/*
 * Scene.cpp
 *
 *  Created on: Mar 30, 2014
 *      Author: vrwall
 */

#include "../Header Files/Scene.h"
#include <map>
#include <GL/glut.h>

Scene::Scene()
{
;
}

Scene::~Scene()
{
//TODO
}

void Scene::Draw(int width, int depth)
{
	double half_width = 0.5f*width;
	double half_height = 0.00001f;
	double half_depth = 0.5f*depth;

	double x=0,y=-1,z=0;

	glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(x-half_width, y-half_height, z-half_depth);
		glVertex3f(x+half_width, y-half_height, z-half_depth);
		glVertex3f(x+half_width, y+half_height, z-half_depth);
		glVertex3f(x-half_width, y+half_height, z-half_depth);


		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(x+half_width, y+half_height, z-half_depth);
		glVertex3f(x-half_width, y+half_height, z-half_depth);
		glVertex3f(x-half_width, y+half_height, z+half_depth);
		glVertex3f(x+half_width, y+half_height, z+half_depth);

		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(x-half_width, y+half_height, z+half_depth);
		glVertex3f(x-half_width, y-half_height, z+half_depth);
		glVertex3f(x+half_width, y-half_height, z+half_depth);
		glVertex3f(x+half_width, y+half_height, z+half_depth);

		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(x+half_width, y-half_height, z-half_depth);
		glVertex3f(x-half_width, y-half_height, z-half_depth);
		glVertex3f(x-half_width, y-half_height, z+half_depth);
		glVertex3f(x+half_width, y-half_height, z+half_depth);

		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(x-half_width, y+half_height, z-half_depth);
		glVertex3f(x-half_width, y-half_height, z-half_depth);
		glVertex3f(x-half_width, y-half_height, z+half_depth);
		glVertex3f(x-half_width, y+half_height, z+half_depth);

		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(x+half_width, y+half_height, z-half_depth);
		glVertex3f(x+half_width, y-half_height, z-half_depth);
		glVertex3f(x+half_width, y-half_height, z+half_depth);
		glVertex3f(x+half_width, y+half_height, z+half_depth);

		glEnd();


}
