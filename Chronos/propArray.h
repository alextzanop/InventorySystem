#ifndef PROP_ARRAY_H
#define PROP_ARRAY_H
#include "Prop.h"


//An array of props

class propArray
{
private:
	Prop** matrix;
	int size;
	int index;

public:
	//constructor
	propArray(int size);

	int getSize();
	bool isEmpty();
	bool isFull();

	//methods
	//append Prop to array
	void append(Prop* newProp);
	
	//remove Prop in given position
	void removeProp(int index);

	//remove given Prop
	void removeProp(Prop* prop);

	//get Prop in given position
	Prop* getElement(int index);

	//true if array contains given prop, false otherwise
	bool contains(Prop* prop);



};

#endif /* PROP_ARRAY_H */