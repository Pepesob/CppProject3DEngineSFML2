#include <SFML/Graphics.hpp>
#include "Object3D.h"
#include "../Camera.h"
#include "../Screen.h"



#pragma once
class Cube : public Object3D
{
public:
	Cube(const Eigen::Matrix4f& wordCoordMatrix=Eigen::Matrix4f::Identity()) {
		ownCoordMat = wordCoordMatrix;
	}

	// Odziedziczono za poœrednictwem elementu Object3D
	virtual void drawTransformed(Screen* scrn, const Eigen::Matrix4f& transforMatrix) const override {
		Eigen::Matrix4f finalMatrix = transforMatrix * ownCoordMat;
		try {
			scrn->window->draw(getVertexArray(finalMatrix));
		}
		catch (std::out_of_range& e) {
			return;
		}
	}

	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
private:
	Eigen::Vector4f verticies[8] = { Eigen::Vector4f(0,0,5,1), Eigen::Vector4f(5,0,5,1), Eigen::Vector4f(5,5,5,1), Eigen::Vector4f(0,5,5,1),
								Eigen::Vector4f(0,0,0,1), Eigen::Vector4f(5,0,0,1), Eigen::Vector4f(5,5,0,1), Eigen::Vector4f(0,5,0,1) };

	const int connections[12][2] = { {1,2}, {2,3}, {3,4}, {4,1}, {1,5}, {5,6}, {6,2}, {6,7}, {7,8}, {8,5}, {3,7}, {4,8} };

	Eigen::Matrix4f ownCoordMat;
	

	sf::VertexArray getVertexArray(const Eigen::Matrix4f& finalMatrix) const {
		float scrW = Screen::getScreenWidth();
		float scrH = Screen::getScreenHeight();
		Eigen::Vector4f verT[8];
		sf::VertexArray vArray(sf::Lines);
		for (int i = 0; i < 8; i++) {
			verT[i] = finalMatrix * verticies[i];
			if (verT[i](3) < 0.01) { // jeœli obiekt jest za kamer¹ to siê dziej¹ dziwne rzeczy, nie pozwalam na to
				throw std::out_of_range("");
			}
			verT[i] /= verT[i](3);
			if (!(verT[i](0) >= 0 && verT[i](0) <= scrW && verT[i](1) >= 0 && verT[i](1) <= scrH)) {
				throw std::out_of_range("");
			}
		}
		for (int i = 0; i < 12; i++) {
			float x1 = verT[connections[i][0] - 1](0);
			float y1 = verT[connections[i][0] - 1](1);
			float x2 = verT[connections[i][1] - 1](0);
			float y2 = verT[connections[i][1] - 1](1);
			vArray.append(sf::Vertex(sf::Vector2f(x1, y1), sf::Color::Cyan));
			vArray.append(sf::Vertex(sf::Vector2f(x2, y2), sf::Color::Cyan));
		}
		return vArray;
	}


};

