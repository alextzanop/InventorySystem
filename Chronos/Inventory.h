#ifndef INVENTORY_H
#define INVENTORY_H

#include "InvCell.h"
#include "allegro5/allegro.h"


//A linked list of InvCells
class Inventory
{
private:
	ALLEGRO_BITMAP* bitmap;
	InvCell* head;
	int size;

public:
	//constructor
	Inventory(ALLEGRO_BITMAP* bitmap, InvCell* head);

	//getters
	ALLEGRO_BITMAP* getBitmap();
	InvCell* getHead();
	int getSize();

	//add node to list
	void add(InvCell* newCell);

	//remove node from list
	void remove(InvCell* remCell);

};

#endif /* INVENTORY_H */
