#include "Character.h"
#include "Macros.h"
#include "myMath.h"

Character::Character(const char* name, ALLEGRO_BITMAP* bitmap, int heigth, int width){
	this->name = name;
	this->bitmap = bitmap;
	this->height = heigth;
	this->width = width;
	this->xPos = 0;
	this->yPos = 0;
}


Character::Character(const char* name, ALLEGRO_BITMAP* bitmap, int heigth, int width, int xPos, int yPos) {
	this->name = name;
	this->height = heigth;
	this->bitmap = bitmap;
	this->width = width;
	this->xPos = xPos;
	this->yPos = yPos;
}

Character::Character(const char* name, ALLEGRO_BITMAP* bitmap, int heigth, int width, int xPos, int yPos, int xSpeed, int ySpeed) {
	this->name = name;
	this->height = heigth;
	this->bitmap = bitmap;
	this->width = width;
	this->xPos = xPos;
	this->yPos = yPos;
	this->xSpeed = xSpeed;
	this->ySpeed = ySpeed;
	this->collideProps = new propArray(6); //at max 6 props collide(too bored to make it dynamic... bad, lazy code, I know)
}



//getters

const char* Character::getName() {
	return this->name;
}

int Character::getHeigth() {
	return this->height;
}

int Character::getWidth() {
	return this->width;
}

int Character::getX() {
	return this->xPos;
}

int Character::getY() {
	return this->yPos;
}

int Character::getDirectionX() {
	return this->xDirection;
}

int Character::getDirectionY() {
	return this->yDirection;
}

int Character::getSpeedX() {
	return this->xSpeed;
}

int Character::getSpeedY() {
	return this->ySpeed;
}

ALLEGRO_BITMAP* Character::getBitmap() {
	return this->bitmap;
}

bool* Character::getCollides() {
	return this->collides;
}

propArray* Character::getCollideProps() {
	return this->collideProps;
}

//setters
void Character::setX(int x) {
	this->xPos = x;
}
void Character::setY(int y) {
	this->yPos = y;
}

void Character::setDirectionX(int dirX) {
	this->xDirection = dirX;
}

void Character::setDirectionY(int dirY) {
	this->yDirection = dirY;
}

void Character::setSpeedX(int xSpeed) {
	this->xSpeed = xSpeed;
}

void Character::setSpeedY(int ySpeed) {
	this->ySpeed = ySpeed;
}

void Character::setCollides(int i, bool val) {
	this->collides[i] = val;
}

//other methods
void Character::move(int x, int y) {
	this->xPos = x;
	this->yPos = y;
}

void Character::transform(int dx, int dy) {
	this->xPos += dx;
	this->yPos += dy;
}

void Character::transform() {
	this->xPos += xSpeed;
	this->yPos += ySpeed;
}

//add prop to collide array
void Character::addCollideProp(Prop* prop) {
	if(!this->collideProps->isFull())
		this->collideProps->append(prop);
}

//remove prop from collide array
void Character::removeCollideProp(Prop* prop) {
	if(!this->collideProps->isEmpty())
		this->collideProps->removeProp(prop);
}

//true if player is near to a given prop, false otherwise
bool Character::nearTo(Prop* prop) {
	
	bool a = (myMath::myEucDist(this->xPos, this->yPos, prop->getX()+prop->getWidth()/2, prop->getY()+prop->getHeigth()/2) < this->getWidth()/2 + prop->getWidth()/2 + 12);
	//bool b = (myMath::myEucDist(this->xPos+this->getWidth()/2, this->yPos+this->getHeigth()/2, prop->getX()+prop->getWidth()/2, prop->getY()+prop->getHeigth()/2) < this->getHeigth()/2 + prop->getHeigth()/2 + 8);
	return (a);
}

//true if player collides with given prop, false otherwise
bool Character::collideProp(Prop* prop) {
	if (!prop->isCollidable())
		return false;

	int collideOffset = 3;

	int pRx = this->getX();
	int pRy = this->getY();
	int pLx = this->getX() + this->getWidth();
	int pLy = this->getY() + this->getHeigth();

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
	clx = ((prop->getX() < this->getX() - this->getWidth() / 2) && (this->getX() - this->getWidth() / 2 < prop->getX() + prop->getWidth()));
	crx = ((prop->getX() < this->getX() + this->getWidth() / 2) && (this->getX() + this->getWidth() / 2 < prop->getX() + prop->getWidth()));
	cly = ((prop->getY() < this->getY() - this->getHeigth() / 2) && (this->getY() - this->getHeigth() / 2 < prop->getY() + prop->getHeigth()));
	cry = ((prop->getY() < this->getY() + this->getHeigth() / 2) && (this->getY() + this->getHeigth() / 2 < prop->getY() + prop->getHeigth()));


	//prop in player
	plx = ((this->getX() - this->getWidth() / 2 < prop->getX()) && (prop->getX() < this->getX() + this->getWidth() / 2));
	prx = ((this->getX() - this->getWidth() / 2 < prop->getX() + prop->getWidth()) && (prop->getX() + prop->getWidth() < this->getX() + this->getWidth() / 2));
	ply = ((this->getY() - this->getHeigth() / 2 < prop->getY()) && (prop->getY() < this->getY() + this->getHeigth() / 2));
	pry = ((this->getY() - this->getHeigth() / 2 < prop->getY() + prop->getHeigth()) && (prop->getY() + prop->getHeigth() < this->getY() + this->getHeigth() / 2));


	ccol = (clx && cly || crx && cry || clx && cry || crx && cly);
	pcol = (plx && ply || prx && pry || plx && pry || prx && ply);

	//ccol = (clx || crx || cly || cry);
	//pcol = (plx || prx || ply || pry);

	//reset player collides
	if (!(ccol || pcol)) {
		for (int i = 0; i < 4; i++) {
			this->getCollides()[i] = false;
			//this->removeCollideProp(prop);
		}
	}

	//set player collides
	else {
		//player touches right
		if (crx && (ply || pry))
			this->setCollides(COLL_RIGHT, true);
		//player touches left
		if (clx && (ply || pry))
			this->setCollides(COLL_LEFT, true);
		//player touces up
		if (cly && (plx || prx))
			this->setCollides(COLL_UP, true);
		//player touches down
		if (cry && (plx || prx))
			this->setCollides(COLL_DOWN, true);
	}
	//if (ccol || pcol)
		//this->addCollideProp(prop);

	return (ccol || pcol);
}