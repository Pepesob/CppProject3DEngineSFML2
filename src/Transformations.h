#pragma once
#include <Eigen/Dense>
#include <iostream>


enum RotationAround {X,Y,Z};


class Transformations
{
public:
	static Eigen::Matrix4f getTranslationMatrix(float x, float y, float z) {
		Eigen::Matrix4f m;
		m.setIdentity();
		m.col(3) << x, y, z, 1;
		return m;
	}

	static Eigen::Matrix4f getScaleMatrix(float s) {
		Eigen::Matrix4f m;
		m.setIdentity();
		m << s, 0, 0, 0,
			0, s, 0, 0,
			0, 0, s, 0,
			0, 0, 0, 1;
		return m;
	}

	static Eigen::Matrix4f getRotationMatrix(float degrees, RotationAround axis) {
		Eigen::Matrix4f m;
		switch (axis)
		{
		case X:
			m << 1, 0, 0, 0,
				0, std::cos(degrees), -std::sin(degrees), 0,
				0, std::sin(degrees), std::cos(degrees), 0,
				0, 0, 0, 1;
			break;
		case Y:
			m << std::cos(degrees), 0, std::sin(degrees), 0,
				0, 1, 0, 0,
				-std::sin(degrees), 0, std::cos(degrees), 0,
				0, 0, 0, 1;
			break;
		case Z:
			m << std::cos(degrees), -std::sin(degrees), 0, 0,
				std::sin(degrees), std::cos(degrees), 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1;
			break;
		default:
			m.setIdentity();
			std::cout << "Did not recognise rotation" << std::endl;
			break;
		}
		return m;
	}
	

private:

};

