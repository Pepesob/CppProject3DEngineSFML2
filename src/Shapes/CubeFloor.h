#pragma once
#include "Cube.h"
#include <iostream>
#include <list>

class CubeFloor: public Object3D
{
public:
	CubeFloor(unsigned int size1) {
		size = size1;

		wordCoordMat.setIdentity();

		Eigen::Matrix4f translation;
		translation.setIdentity();
		

		for (unsigned int i = 0; i < size*size; i++) {
			translation.col(3) = Eigen::Vector4f(5 * (i / size), 0, 5 * (i % size), 1);
			translationMatrixes.push_back(translation);
		}
	}

	// Odziedziczono za poœrednictwem elementu Object3D
	virtual void drawTransformed(Screen* scrn, const Eigen::Matrix4f& transforMatrix) const override {
		for (const auto& mat : translationMatrixes) {
			cube.drawTransformed(scrn, transforMatrix * mat);
		}
	}

	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
private:
	unsigned int size;
	Eigen::Matrix4f wordCoordMat;
	std::list<Eigen::Matrix4f> translationMatrixes;

	Cube cube;
};

