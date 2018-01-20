//Name: Jonathan Hassel
//Date: 2/23/17
//Class: cop4530 - Duan
#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "Queue.h"


//QUEUE CLASS--------------------------------------------------------------------------------------------------------
template <typename T, class Container>
Queue<T,Container>::Queue()
{	//default constructor

}

template <typename T, class Container>
Queue<T,Container>::~Queue()
{	//destructor

}


template <typename T, class Container>
Queue<T,Container>::Queue(const Queue& rhs): c{rhs.c}
{	//copy constructor

}

template <typename T, class Container>
Queue<T,Container>::Queue(Queue&& rhs)
{	//move constructor
	c = std::move(rhs.c);
}

template <typename T, class Container>
typename Queue<T,Container>::Queue& Queue<T,Container>::operator=(const Queue& rhs)
{	//copy assignment operator
	Queue<T, Container>	copy = rhs;
	std::swap(*this, copy);
	return *this;
}

template <typename T, class Container>
typename Queue<T,Container>::Queue& Queue<T,Container>::operator=(Queue&& rhs)
{	//move assignment operator
	std::swap(c, rhs.c);
}

template <typename T, class Container>
T& Queue<T,Container>::back()
{	//returns reference to the last element in the queue
	return c.back();
}

template <typename T, class Container>
const T& Queue<T,Container>::back() const
{	//returns const reference to the last element in the queue
	return c.back();
}

template <typename T, class Container>
T& Queue<T,Container>::front()
{	//returns reference to the first element in the queue
	return c.front();
}

template <typename T, class Container>
const T& Queue<T,Container>::front() const
{	//returns const reference to the first element in the queue
	return c.front();
}

template <typename T, class Container>
void Queue<T,Container>::pop()
{	//removes the first element in the queue
	c.pop_front();
}

template <typename T, class Container>
void Queue<T,Container>::push(const T& val)
{	//adds a value at the end of the queue
	c.push_back(val);
}

template <typename T, class Container>
void Queue<T,Container>::push(T&& val)
{	//adds a value at the end of the queue(with the move function)
	c.push_back(val);
}

template <typename T, class Container>
bool Queue<T,Container>::empty() const
{	//returns true if the queue is empty, false otherwise
	return c.empty();
}

template <typename T, class Container>
int Queue<T,Container>::size()
{	//returns the size of the queue
	return c.size();
}


#endif
