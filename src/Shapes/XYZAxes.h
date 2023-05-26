#pragma once
#include "Line3D.h"


class XYZAxes: public Object3D
{
public:
	XYZAxes(const Eigen::Matrix4f& transforMat=Eigen::Matrix4f::Identity()) {
		xAxis = Line3D(Eigen::Vector4f(0, 0, 0, 1), Eigen::Vector4f(25, 0, 0, 1), sf::Color::Red);
		yAxis = Line3D(Eigen::Vector4f(0, 0, 0, 1), Eigen::Vector4f(0, 25, 0, 1), sf::Color::Green);
		zAxis = Line3D(Eigen::Vector4f(0, 0, 0, 1), Eigen::Vector4f(0, 0, 25, 1), sf::Color::Blue);
		
		wordCoordMat = transforMat;
	}

	// Odziedziczono za poœrednictwem elementu Object3D
	virtual void drawTransformed(Screen* scrn, const Eigen::Matrix4f& transforMatrix) const override {
		xAxis.drawTransformed(scrn, transforMatrix);
		yAxis.drawTransformed(scrn, transforMatrix);
		zAxis.drawTransformed(scrn, transforMatrix);
	}

	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
private:

	Eigen::Matrix4f wordCoordMat;

	Line3D xAxis;
	Line3D yAxis;
	Line3D zAxis;

};

