#include "propArray.h"
#include <iostream>

propArray::propArray(int size) {
	this->size = size;
	this->matrix = (Prop **)malloc(this->size * sizeof(Prop*));
	this->index = 0;

	//init matrix
	for (int i = 0; i < this->size; i++) {
		this->matrix[i] = NULL;
	}

}

int propArray::getSize() {
	return this->size;
}

bool propArray::isEmpty() {
	return (this->size == 0);
}

bool propArray::isFull() {
	return (this->size == this->index);
}

//append Prop to array
void propArray::append(Prop* newProp) {
	std::cout << this->index;
	if (this->index < this->size)
		this->matrix[this->index++] = newProp;
}

//remove Prop afrom given position
void propArray::removeProp(int index) {
	if (index < this->size)
		this->matrix[index] = NULL;
	else
		std::cout << "Wrong index\n";
}

//remove given Prop
void propArray::removeProp(Prop* prop) {
	for (int i = 0; i < this->size; i++) {
		if (this->matrix[i] == prop) {
			this->matrix[i] = NULL;
			break;
		}
	}
}

//get Prop in given position
Prop* propArray::getElement(int index) {
	return this->matrix[index];
}

//true if array contains given Prop, false otherwise
bool propArray::contains(Prop* prop) {
	for (int i = 0; i < this->size; i++) {
		if (this->matrix[i] == prop)
			return true;
	}
	return false;
}

