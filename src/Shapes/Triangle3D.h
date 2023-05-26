#pragma once
#include <Eigen/Dense>
#include "Object3D.h"


class Triangle3D : public Object3D
{
public:
	Triangle3D(const Eigen::Vector4f& v1, const Eigen::Vector4f& v2, const Eigen::Vector4f& v3, sf::Color color = sf::Color::White) {
		this->v1 = v1;
		this->v2 = v2;
		this->v3 = v3;

		this->color = color;
	}

	Triangle3D(sf::Color color = sf::Color::White) {
		this->v1 = Eigen::Vector4f(0, 0, 0, 1);
		this->v2 = Eigen::Vector4f(0, 1, 0, 1);
		this->v3 = Eigen::Vector4f(0, 0, 1, 1);

		this->color = color;
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

	void setVertexes(const Eigen::Vector4f& v1, const Eigen::Vector4f& v2, const Eigen::Vector4f& v3) {
		this->v1 = v1;
		this->v2 = v2;
		this->v3 = v3;
	}

	void setColor(sf::Color color) {
		this->color = color;
	}

private:
	sf::VertexArray getVertexArray(const Eigen::Matrix4f& transforMatrix) const {
		sf::VertexArray triangle(sf::LineStrip, 3);
		Eigen::Vector4f v = transforMatrix * v1;

		float scrW = Screen::getScreenWidth();
		float scrH = Screen::getScreenHeight();

		if (v(3) < 0.01) {
			throw std::out_of_range("");
		}
		v /= v(3);

		if (!(v(0) >= 0 && v(0) <= scrW && v(1) >= 0 && v(1) <= scrH)) {
			throw std::out_of_range("");
		}

		triangle[0].position = sf::Vector2f(v(0), v(1));
		triangle[0].color = color;


		v = transforMatrix * v2;
		if (v(3) < 0.01) {
			throw std::out_of_range("");
		}
		v /= v(3);

		if (!(v(0) >= 0 && v(0) <= scrW && v(1) >= 0 && v(1) <= scrH)) {
			throw std::out_of_range("");
		}

		triangle[1].position = sf::Vector2f(v(0), v(1));
		triangle[1].color = color;


		v = transforMatrix * v3;
		if (v(3) < 0.01) {
			throw std::out_of_range("");
		}

		v /= v(3);

		if (!(v(0) >= 0 && v(0) <= scrW && v(1) >= 0 && v(1) <= scrH)) {
			throw std::out_of_range("");
		}

		triangle[2].position = sf::Vector2f(v(0), v(1));
		triangle[2].color = color;
		return triangle;
	}


	Eigen::Vector4f v1;
	Eigen::Vector4f v2;
	Eigen::Vector4f v3;

	sf::Color color;
};

