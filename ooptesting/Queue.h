#ifndef __Queue_h_
#define __Queue_h_
#include<iostream>
#include <time.h>
#include "Slot.h"
//#include "Board.h"
//#include "Player.h"
using namespace std;


//FIFO First In First Out:
class Asset;
//class Board;

class Queue {
protected:
	Asset** q_data;
	static int q_counter;
	const int Queue_Number;
	unsigned head;
	unsigned tail;
	unsigned max_capacity;
	unsigned q_size;
public:
	Queue(unsigned max_capacity = 13);//default constractor
	bool full();//check if the Queue is full or not.
	bool empty();//check if the Queue is empty or not.
	unsigned get_size()const;//return  hhow many item are in the Queue in the moment.
	unsigned get_queue_number()const;
	Asset* get_data(int index)const;//return the value in a specific index, used mainly in show function
	unsigned get_max_capacity()const;//return the max capacity in a specific Queue.
	Asset* front();//return the value that head is pointing at.
	void push(Asset* s);//if the the Queue is not full, will add a value to whare the pointer tail point to.
	void pop();//only if the the Queue is not empty will erase the value at index head.
	//void show();//print to the console the parmeters of the Queue
	//used foe debuging only.
	Asset* operator[](int idx) const;
	friend ostream& operator<<(ostream& os, const Queue& q);
	~Queue();//distructor
};
//int Random(int mod, int st);//retun a random number between start to mod
//int Random();//return a rundom number.
#endif 