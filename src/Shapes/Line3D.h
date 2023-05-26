#pragma once
#include <SFML/Graphics.hpp>
#include <Eigen/Dense>
#include "../Camera.h"
#include "../Screen.h"
#include "iostream"
#include "Object3D.h"

class Line3D : public Object3D
{
public:

	Line3D(const Eigen::Vector4f LStart, const Eigen::Vector4f LEnd, sf::Color lineColor = sf::Color::White) {
		start = LStart;
		end = LEnd;
		lColor = lineColor;
	}
	
	Line3D() {
		start = Eigen::Vector4f(0, 0, 0, 1);
		end = Eigen::Vector4f(0, 10, 0, 1);
		lColor = sf::Color::White;
	}


	// Odziedziczono za poœrednictwem elementu Object3D
	virtual void drawTransformed(Screen* scrn, const Eigen::Matrix4f& transforMatrix) const override {
		try {
			scrn->window->draw(getVertexArray(transforMatrix));
		}
		catch (std::out_of_range& e) {
			return;
		}
	}

	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
private:
	Eigen::Vector4f start;
	Eigen::Vector4f end;

	sf::Color lColor;



	virtual sf::VertexArray getVertexArray(const Eigen::Matrix4f& finalMatrix) const {
		sf::VertexArray line(sf::Lines, 2);
		int scrW = Screen::getScreenWidth();
		int scrH = Screen::getScreenHeight();

		Eigen::Vector4f screenStart = finalMatrix * start;

		if (screenStart(3) < 0.01) {
			throw std::out_of_range("");
		}

		screenStart /= screenStart(3);

		if (!(screenStart(0) >= 0 && screenStart(0) <= scrW && screenStart(1) >= 0 && screenStart(1) <= scrH)) {
			throw std::out_of_range("");
		}

		Eigen::Vector4f screenEnd = finalMatrix * end;
		if (screenEnd(3) < 0.01) {
			throw std::out_of_range("");
		}
		screenEnd /= screenEnd(3);

		if (!(screenEnd(0) >= 0 && screenEnd(0) <= scrW && screenEnd(1) >= 0 && screenEnd(1) <= scrH)) {
			throw std::out_of_range("");
		}

		line[0].position = sf::Vector2f(screenStart(0), screenStart(1));
		line[0].color = lColor;
		line[1].position = sf::Vector2f(screenEnd(0), screenEnd(1));
		line[1].color = lColor;
		return line;
	}
};

