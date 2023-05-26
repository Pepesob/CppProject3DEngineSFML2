#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include "src/Screen.h"
#include <iostream>
#include "src/Camera.h"

int main() {
	
	Screen s(1080,720);

	s.gameLoop();

	
	return 0;
}