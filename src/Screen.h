#pragma once
#include <SFML/Graphics.hpp>
#include <Eigen/Dense>


class Screen
{
public:
	Screen(int w = 720, int h = 720) {
		window = new sf::RenderWindow(sf::VideoMode(w, h), "3DEngine", sf::Style::Titlebar | sf::Style::Close);
		window->setFramerateLimit(60);

		screenMatrix << 0.5f * w, 0, 0, 0.5f * w,
						0, -0.5f * h, 0, 0.5f * h,
						0, 0, 1.0f, 0,
						0, 0, 0, 1.0f;
		width = w;
		height = h;
	}

	~Screen() {
		delete window;
	}

	void gameLoop();

	Eigen::Matrix4f screenMatrix;
	sf::RenderWindow* window;

	static int getScreenWidth() {
		return width;
	}

	static int getScreenHeight() {
		return height;
	}

	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
private:
	static int width;
	static int height;
};


