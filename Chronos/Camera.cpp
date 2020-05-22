#include "Camera.h"

//constructors
Camera::Camera(int x, int y) {
	this->xPos = x;
	this->yPos = y;
}
Camera::Camera(int x, int y, int zoom) {
	this->xPos = x;
	this->yPos = y;
	this->zoom = zoom;
}

//getters
int Camera::getX() {
	return this->xPos;
}
int Camera::getY() {
	return this->yPos;
}
int Camera::getZoom() {
	return this->zoom;
}

//setters
void Camera::setX(int x) {
	this->xPos = x;
}
void Camera::setY(int y) {
	this->yPos = y;
}
void Camera::setZoom(int zoom) {
	this->zoom = zoom;
}

//movers
void Camera::transform(int dx, int dy) {
	this->xPos += dx;
	this->yPos += dy;
}

void Camera::move(int x, int y) {
	this->xPos = x;
	this->yPos = y;
}