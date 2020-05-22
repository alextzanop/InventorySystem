#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
private:
	int xPos;
	int yPos;
	int zoom;


public:
	//constructors
	Camera(int x, int y);
	Camera(int x, int y, int zoom);

	//getters
	int getX();
	int getY();
	int getZoom();

	//setters
	void setX(int x);
	void setY(int y);
	void setZoom(int zoom);

	//movers
	void transform(int dx, int dy);
	void move(int x, int y);

};

#endif /* CAMERA_H */

