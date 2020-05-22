#include "Inventory.h"

//A linked list of InvCells

//constructor
Inventory::Inventory(ALLEGRO_BITMAP* bitmap, InvCell* head) {
	this->bitmap = bitmap;
	this->head = head;
	this->size = 0;
}

//getters
ALLEGRO_BITMAP* Inventory::getBitmap() {
	return this->bitmap;
}


InvCell* Inventory::getHead() {
	return this->head;
}

int Inventory::getSize() {
	return this->size;
}

//add node to list
void Inventory::add(InvCell* newCell) {
	InvCell* tmpCell = this->head;
	InvCell* prev = this->head;
	InvCell* next = tmpCell->getNext();
	while (tmpCell) {
		next = tmpCell->getNext();
		//increase quantity and end
		if (tmpCell->getName() == newCell->getName()){
			tmpCell->setQuantity(tmpCell->getQuantity() + newCell->getQuantity());
			return;
			}
		prev = tmpCell;
		tmpCell = next;
		
	}
	prev->setNext(newCell);
	newCell->setPrev(prev);
	newCell->setNext(NULL);
	this->size++;

}

//remove node from list
void Inventory::remove(InvCell* remCell) {
	if (remCell->getName() == this->head->getName()) {
		InvCell* next = this->head->getNext();
		delete this->head;
		this->head = next;
		this->size--;
		return;
	}


	InvCell* tmpCell = this->head;
	InvCell* next = tmpCell->getNext();
	InvCell* prev = NULL;
	while (tmpCell) {
		next = tmpCell->getNext();
		if (tmpCell->getName() == remCell->getName())
			break;
		tmpCell = next;

	}
	if (!tmpCell)
		return;
	prev = tmpCell->getPrev();
	delete tmpCell;
	prev->setNext(next);
	if (next)
		next->setPrev(prev);
	this->size--;
}