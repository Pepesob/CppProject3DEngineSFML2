#pragma once
#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include "../Screen.h"
#include "../Camera.h"


class Object3D
{
public:
	virtual void drawTransformed(Screen* scrn, const Eigen::Matrix4f& transforMatrix) const = 0;
};

