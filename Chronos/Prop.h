#ifndef PROP_H
#define PROP_H

#include "allegro5/allegro.h"


class Prop
{
private:
	const char* name;
	const char* type;
	ALLEGRO_BITMAP* bitmap;
	int width;
	int heigth;
	int xPos;
	int yPos;
	bool interactable;
	bool collidable;
	bool active;

public:
	
	//constructors
	Prop(const char* name,const char* type, ALLEGRO_BITMAP* bitmap, int width, int heigth, int xPos, int yPos);

	//getters
	const char* getName();
	const char* getType();
	ALLEGRO_BITMAP* getBitmap();
	int getWidth();
	int getHeigth();
	int getX();
	int getY();
	bool isInteractable();
	bool isCollidable();
	bool isActive();
	
	//setters
	void setInteractable(bool val);
	void setCollidable(bool val);
	void setActive(bool val);
	

	//others
	//bool collidePlayer(Character* player);
	void transform(int dx, int dy);
	void interact();
	void collide();


};


#endif /* PROP_H */