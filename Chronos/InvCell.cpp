#include "InvCell.h"

//Node of the inventory linked list

InvCell::InvCell(ALLEGRO_BITMAP* icon, const char* name, int quantity) {
	this->icon = icon;
	this->name = name;
	this->quantitiy = quantity;
	this->next = NULL;
	this->prev = NULL;
}

//getters
ALLEGRO_BITMAP* InvCell::getIcon() {
	return this->icon;
}
const char* InvCell::getName() {
	return this->name;
}
int InvCell::getQuantity() {
	return this->quantitiy;
}
InvCell* InvCell::getPrev() {
	return this->prev;
}
InvCell* InvCell::getNext() {
	return this->next;
}
bool InvCell::isSelected() {
	return this->selected;
}


//setters
void InvCell::setQuantity(int q) {
	this->quantitiy = q;
}
void InvCell::setPrev(InvCell* prev) {
	this->prev = prev;
}
void InvCell::setNext(InvCell* next) {
	this->next = next;
}
void InvCell::setSelected(bool val) {
	this->selected = val;
}