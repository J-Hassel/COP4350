#ifndef QUEUE_H
#define QUEUE_H
//Name: Jonathan Hassel
//Date: 2/23/17
//Class: cop4530 - Duan

namespace cop4530
{

template <typename T, class Container>
class Queue
{
	public:
		//CONSTRUCTORS-------------------------------------------
		Queue();						//default constructor	|
		~Queue();						//destructor			|
		Queue(const Queue& rhs);		//copy constructor		|
		Queue(Queue&& rhs);				//move constructor		|
		//-------------------------------------------------------

		//ASSIGNMENT OPERATORS-----------------------------------------------
		Queue& operator=(const Queue& rhs);		//copy assignment operator	|
		Queue& operator=(Queue&& rhs);			//move assignment operator	|
		//-------------------------------------------------------------------

		//MEMBER FUNCTIONS------
		T& back();
		const T& back() const;
		T& front();
		const T& front() const;
		void pop();
		void push(const T& val);
		void push(T&& val);
		bool empty() const;
		int size();

	protected:
		Container c;

};



#include "Queue.hpp"

}//end of namespace cop4530
#endif
