#pragma once
#include <list>
#include <Eigen/Dense>
#include "Object3D.h"
#include "Triangle3D.h"
#include "../OBJParser.h"


class CustomShape3D : public Object3D
{
public:

	CustomShape3D(std::string filePath, const Eigen::Matrix4f& transforMatrix=Eigen::Matrix4f::Identity()) {
		OBJParser::getVertexesFromOBJFile(vertexesList, connectionsList, filePath);

		worldCoordMatrix = transforMatrix;
	}

	// Odziedziczono za poœrednictwem elementu Object3D
	virtual void drawTransformed(Screen* scrn, const Eigen::Matrix4f& transforMatrix) const override {
		Eigen::Matrix4f finalMatrix = transforMatrix * worldCoordMatrix;
		Triangle3D triange;
		Eigen::Vector4f vec;
		for (const auto& i : connectionsList) {
			triange.setVertexes(vertexesList[i(0)-1], vertexesList[i(1)-1], vertexesList[i(2)-1]);
			triange.drawTransformed(scrn, finalMatrix);
		}
	}

	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
private:
	std::vector<Eigen::Vector4f> vertexesList;
	std::list<Eigen::Vector3i> connectionsList;

	Eigen::Matrix4f worldCoordMatrix;
};

