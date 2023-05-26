#pragma once
#include <iostream>
#include <list>
#include "Shapes/Object3D.h"
#include "Camera.h"
#include "Screen.h"
#include "Shapes/XYZAxes.h"
#include "Shapes/CubeFloor.h"


class World
{
public:
	World(Screen* scrn, Camera* cam) {
		camera = cam;
		screen = scrn;

		transforMatrix.setIdentity();
	}



	void makeScreenCamMatrix() {
		screenCamMatrix = screen->screenMatrix * camera->getProjectionMatrix() * camera->getCameraCordsSystemMatrix();
	}



	void drawAll() {
		makeScreenCamMatrix();
		for (auto obj : worldObjects) {
			obj->drawTransformed(screen, screenCamMatrix);
		}
	}

	void push_back(Object3D *obj) {
		for (Object3D* temp : worldObjects) {
			if (temp == obj) {
				return;
			}
		}
		worldObjects.push_back(obj);
	}

	void pop_back() {
		worldObjects.pop_back();
	}

	void remove(Object3D* obj) {
		worldObjects.remove(obj);
	}

	void changeVisibility(Object3D* obj) {
		for (Object3D* temp : worldObjects) {
			if (temp == obj) {
				remove(obj);
				return;
			}
		}
		push_back(obj);
	}

	

	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
private:
	Camera* camera;
	Screen* screen;


	std::list<Object3D*> worldObjects;
	Eigen::Matrix4f screenCamMatrix;

	Eigen::Matrix4f transforMatrix;
};

