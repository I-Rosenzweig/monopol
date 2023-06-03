#define  _CRTDBG_MAP_ALLOC
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include "Slot.h"
#include "Board.h"
#include "Player.h"
#include "Queue.h"
using namespace std;
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
int Queue::q_counter(0);

//default constractor + initialization list:
//service time is random number between 50 and 69
Queue::Queue(unsigned max_capacity) :max_capacity(max_capacity),Queue_Number(q_counter + 1), head(0), tail(0), q_size(0)
{
	//srand(time(NULL));
	q_counter++;//every time an object is created the counter is rising 
	q_data = nullptr;
	q_data = new Asset * [max_capacity];
	//q_data = new Asset[max_capacity];//create a Queue 
	////for (int i = 0; i < max_capacity; i++)
	////	q_data[i] = NULL;//initialize the Queue with null
}


//member function:
bool Queue::full()//check if the Queue is full or not
{
	if (q_size == max_capacity)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Queue::empty()//check if the Queue is empty or not
{
	if (q_size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
unsigned Queue::get_size()const//return the number of item currentlu in the Queue.
{
	return q_size;
}
unsigned Queue::get_queue_number()const//return the Queue number of times it appeared.
{
	return Queue_Number;
}
Asset* Queue::get_data(int index)const//return the value in a specific index.
{
	return q_data[(head + index) % max_capacity];
}
unsigned Queue::get_max_capacity()const
{
	return max_capacity;
}
Asset* Queue::front()//return the value of the Queue at index head.
{
	return q_data[head];
}
void Queue::push(Asset* s)//puse a new value
{
	if (this->full())//check if the Queue is fuell
		cout << "the Queue is full" << endl;
	else {
		q_size++;
		q_data[tail] = s;//insert the new value a the end of the Queue.
						 //notice the Queue is cyclical
		tail = (tail + 1) % max_capacity;//moving forward tail.
	}
}
void Queue::pop()
{
	if (this->empty())//check if the Queue is empty
		cout << "the Queue is empty" << endl;
	else {
		q_size--;
		q_data[head] = nullptr;//erase the value at index head.
							//notice the Queue is cyclical
		head = (head + 1) % max_capacity;//moving forward tail.
	}
}

Asset* Queue::operator[](int idx) const
{
		return q_data[idx];
}
ostream& operator<<(ostream& os, const Queue& q)
{
	for (int i = 0; i < q.get_size(); i++)
		if (q.q_data)
		{
			os << i+1<< ")City name: " << q.q_data[(q.head + i) % q.get_max_capacity()]->get_city_name()<<endl;
			os << " Asset name: " << q.q_data[(q.head + i) % q.get_max_capacity()]->get_ass_name() << endl;
			os << " Asset index: " << q.q_data[(q.head + i) % q.get_max_capacity()]->get_index()<< endl;
			os <<" Asset value: " << q.q_data[(q.head + i) % q.get_max_capacity()]->get_price()<<endl;
			os << " Asset rent: " << q.q_data[(q.head + i) % q.get_max_capacity()]->get_rent()<<endl;
		}
	return os;
}
//distructor:
Queue::~Queue()
{
	delete[] q_data;
	q_counter--;
}


