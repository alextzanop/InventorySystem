#ifndef INV_CELLS_H
#define INV_CELLS_H

#include "allegro5/allegro.h"



//Node of the inventory linked list
class InvCell
{
private:
	ALLEGRO_BITMAP* icon;
	const char* name; 
	int quantitiy;
	InvCell* prev; //previous node
	InvCell* next; //next node
	bool selected; //true if cell selected, false otherwise

public:
	InvCell(ALLEGRO_BITMAP* icon, const char* name, int quantity);

	//getters
	ALLEGRO_BITMAP* getIcon();
	const char* getName();
	int getQuantity();
	InvCell* getPrev();
	InvCell* getNext();
	bool isSelected();


	//setters
	void setQuantity(int q);
	void setPrev(InvCell* prev);
	void setNext(InvCell* next);
	void setSelected(bool val);

};

#endif /* INV_CELLS_H */