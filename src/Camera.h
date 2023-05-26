#pragma once
#include <Eigen/Dense>

class Camera
{
public:
	Camera(int sWidth, int sHeight, float projNear=100, float projRight=50, float projFar=10000, float projTop=50) {
		scrWidth = sWidth;
		scrHeight = sHeight;

		near = projNear;
		far = projFar;
		right = projRight;
		top = projTop;

		targetChange = true;

		cameraPosition << 50, 50, 50; // where camera is
		cameraTarget << 0, 0, 0; //where camera points to

		cameraVectorX << 1, 0, 0;
		cameraVectorY << 0, 1, 0;
		cameraVectorZ << 0, 0, 1;


		originCameraPosition = cameraPosition;
		originCameraTarget = cameraTarget;


		projectionMatrix << near / right, 0, 0, 0,
							0, near / top, 0, 0,
							0, 0, (far + near) / (near - far), -2 * far * near / (far - near),
							0, 0, -1, 0;



		makeCameraVectors();


	}

	void makeCameraVectors() {
		if (targetChange) {
			cameraVectorZ = cameraPosition - cameraTarget;
			cameraVectorZ /= cameraVectorZ.norm();

			cameraVectorX = Eigen::Vector3f(0, 1, 0).cross(cameraVectorZ);
			cameraVectorX /= cameraVectorX.norm();

			cameraVectorY = cameraVectorZ.cross(cameraVectorX);
			cameraVectorY /= cameraVectorY.norm();
		}
	}

	Eigen::Matrix4f getCameraCordsSystemMatrix() {

		Eigen::Matrix4f cameraMatrix;
		Eigen::Matrix4f translationMatrix;
		translationMatrix.setIdentity();

		cameraMatrix.row(0) << cameraVectorX.transpose(), 0;
		cameraMatrix.row(1) << cameraVectorY.transpose(), 0;
		cameraMatrix.row(2) << cameraVectorZ.transpose(), 0;
		cameraMatrix.row(3) << 0, 0, 0, 1;

		translationMatrix.col(3) << -cameraPosition, 1;

		return cameraMatrix * translationMatrix;
	}

	Eigen::Matrix4f getProjectionMatrix() {
		return projectionMatrix;
	}


	void moveRight(float x) {
		cameraPosition += x * cameraVectorX;
	}

	void moveLeft(float x) {
		cameraPosition += -x * cameraVectorX;
	}

	void moveForward(float x) {
		cameraPosition += -x * cameraVectorZ;
	}

	void moveBackward(float x) {
		cameraPosition += x * cameraVectorZ;
	}

	void lookUpDown(float x) {
		Eigen::Vector3f newZ = rotationAroundVector(cameraVectorZ, cameraVectorX, x);
		Eigen::Vector3f newY = newZ.cross(cameraVectorX);

		if (newY(1) <= 0.0001) {
			return;
		}

		cameraVectorY = newY;
		cameraVectorZ = newZ;
	}

	void lookLeftRight(float x) {
		Eigen::Vector3f vectY(0, 1, 0);

		Eigen::Vector3f newX = rotationAroundVector(cameraVectorX, vectY, x);
		Eigen::Vector3f newZ = rotationAroundVector(cameraVectorZ, vectY, x);
		Eigen::Vector3f newY = newZ.cross(newX);

		cameraVectorX = newX;
		cameraVectorY = newY;
		cameraVectorZ = newZ;
	}

	void backToOrigin() {
		cameraPosition = originCameraPosition;
		cameraTarget = originCameraTarget;

		makeCameraVectors();
	}


	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
private:
	Eigen::Vector3f rotationAroundVector(const Eigen::Vector3f& oldV, const Eigen::Vector3f& rotationOn, float x) {
		return oldV * std::cos(x) + rotationOn.cross(oldV) * std::sin(x) + rotationOn * rotationOn.dot(oldV) * (1 - std::cos(x));
	}

	int scrWidth;
	int scrHeight;

	float near;
	float far;
	float right;
	float top;

	bool targetChange;

	Eigen::Vector3f cameraPosition;
	Eigen::Vector3f cameraTarget;

	Eigen::Vector3f cameraVectorX;
	Eigen::Vector3f cameraVectorY;
	Eigen::Vector3f cameraVectorZ;


	Eigen::Vector3f originCameraPosition;
	Eigen::Vector3f originCameraTarget;

	
	Eigen::Matrix4f projectionMatrix;
};

