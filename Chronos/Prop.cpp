#include "Prop.h"
#include <iostream>
#include "Macros.h"


//constructors
Prop::Prop(const char* name, const char* type, ALLEGRO_BITMAP* bitmap, int width, int heigth, int xPos, int yPos) {
	this->name = name;
	this->type = type;
	this->bitmap = bitmap;
	this->width = width;
	this->heigth = heigth;
	this->xPos = xPos;
	this->yPos = yPos;
	this->interactable = false;
	this->collidable = true;
	this->active = true;

}

//getters
const char* Prop::getName() {
	return this->name;
}
const char* Prop::getType() {
	return this->type;
}


ALLEGRO_BITMAP* Prop::getBitmap() {
	return this->bitmap;
}
int Prop::getWidth() {
	return this->width;
}
int Prop::getHeigth() {
	return this->heigth;
}
int Prop::getX() {
	return this->xPos;
}
int Prop::getY() {
	return this->yPos;
}

bool Prop::isInteractable() {
	return this->interactable;
}

bool Prop::isCollidable() {
	return this->collidable;
}

bool Prop::isActive() {
	return this->active;
}

void Prop::transform(int dx, int dy){
	this->xPos += dx;
	this->yPos += dy;
}


//setters

void Prop::setInteractable(bool val) {
	this->interactable = val;
}

void Prop::setCollidable(bool val) {
	this->collidable = val;
}

void Prop::setActive(bool val) {
	this->active = val;
}

/*
bool Prop::collidePlayer(Character* player) {

	int collideOffset = 3;

	int pRx = player->getX();
	int pRy = player->getY();
	int pLx = player->getX() + player->getWidth();
	int pLy = player->getY() + player->getHeigth();

	bool clx = false; //char left x
	bool crx = false; //char right x
	bool cly = false; //char left y
	bool cry = false; //char right y

	bool plx = false;
	bool prx = false;
	bool ply = false;
	bool pry = false;

	bool ccol = false;
	bool pcol = false;

	//Player in prop
	clx = ((this->getX() < player->getX() - player->getWidth()/2) && (player->getX() - player->getWidth()/2 < this->getX() + this->getWidth()));
	crx = ((this->getX() < player->getX() + player->getWidth()/2 ) && (player->getX() + player->getWidth()/2 < this->getX() + this->getWidth()));
	cly = ((this->getY() < player->getY() - player->getHeigth()/2) && (player->getY() - player->getHeigth()/2 < this->getY() + this->getHeigth()));
	cry = ((this->getY() < player->getY() + player->getHeigth()/2) && (player->getY() + player->getHeigth()/2 < this->getY() + this->getHeigth()));


	//prop in player
	plx = ((player->getX() - player->getWidth()/2 < this->getX()) && (this->getX() < player->getX() + player->getWidth()/2));
	prx = ((player->getX() - player->getWidth()/2 < this->getX() + this->getWidth()) && (this->getX() + this->getWidth() < player->getX() + player->getWidth()/2));
	ply = ((player->getY() - player->getHeigth()/2 < this->getY()) && (this->getY() < player->getY() + player->getHeigth()/2));
	pry = ((player->getY() - player->getHeigth()/2 < this->getY() + this->getHeigth()) && (this->getY() + this->getHeigth() < player->getY() + player->getHeigth()/2));


	ccol = (clx && cly || crx && cry || clx && cry || crx && cly);
	pcol = (plx && ply || prx && pry || plx && pry || prx && ply);

	//ccol = (clx || crx || cly || cry);
	//pcol = (plx || prx || ply || pry);

	//reset player collides
	if (!(ccol || pcol)) {
		for (int i = 0; i < 4; i++) {
			player->getCollides()[i] = false;
			player->removeCollideProp(this);
		}
	}

	//set player collides
	else {
		//player touches right
		if (crx && (ply || pry))
			player->setCollides(COLL_RIGHT, true);
		//player touches left
		if (clx && (ply || pry))
			player->setCollides(COLL_LEFT, true);
		//player touces up
		if (cly && (plx || prx))
			player->setCollides(COLL_UP, true);
		//player touches down
		if (cry && (plx || prx))
			player->setCollides(COLL_DOWN, true);
	}
	if (ccol || pcol)
		player->addCollideProp(this);

	return (ccol || pcol);
}
*/

void Prop::interact() {
	if (this->type == "pickUp") {
		this->setActive(false);
	}
	std::cout << "Interacted with: " << this->getName()<<std::endl;
}

void Prop::collide() {
	std::cout << "Collided with: " << this->getName() << std::endl;
}