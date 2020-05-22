#ifndef CHARACTER_H
#define CHARACTER_H
#include <allegro5/allegro.h>
#include "Prop.h"
#include "propArray.h"


class Character
{
private:
	const char* name;
	int height;
	int width;
	int xPos;
	int yPos;
	int xSpeed; //horizontal velocity
	int ySpeed; //vertical velocity
	int xDirection; //1 for right, -1 for left, 0 for nothing
	int yDirection; //1 for up, -1 for down, 0 for nothing
	ALLEGRO_BITMAP* bitmap;
	propArray* collideProps; //array of props colliding with player

	//collision checks
	
	bool collides[4] = { false, false, false, false }; //up,left,down,right


public:
	//constructors
	Character(const char* name, ALLEGRO_BITMAP* bitmap, int heigth, int width);
	Character(const char* name, ALLEGRO_BITMAP* bitmap, int heigth, int width, int xPos, int yPos);
	Character(const char* name, ALLEGRO_BITMAP* bitmap, int heigth, int width, int xPos, int yPos, int xSpeed, int ySpeed);
	


	//getters
	const char* getName();
	int getHeigth();
	int getWidth();
	int getX();
	int getY();
	int getDirectionX();
	int getDirectionY();
	int getSpeedX();
	int getSpeedY();
	ALLEGRO_BITMAP* getBitmap();
	bool* getCollides();
	
	//setters
	void setX(int x);
	void setY(int y);
	void setDirectionX(int dirX);
	void setDirectionY(int dirY);
	void setSpeedX(int xSpeed);
	void setSpeedY(int ySpeed);
	void setCollides(int i, bool val);

	//add prop to collide array
	void addCollideProp(Prop* prop);
	
	//remove prop from collide array
	void removeCollideProp(Prop* prop);

	//other methods
	void move(int x, int y);
	void transform(int dx, int dy);
	void transform();

	//get props that are colliding with player
	propArray* getCollideProps();

	//true if player is near to a given prop, false otherwise
	bool nearTo(Prop*);

	//true if player collides with given prop, false otherwise
	bool collideProp(Prop*);
	
	


};

#endif /* CHARACTER_H */