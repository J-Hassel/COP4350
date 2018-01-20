//Name: Jonathan Hassel
//Date: 2/6/17
//Class: COP4530 - Duan
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "Vector.h"


//VECTOR CLASS------------------------------------------------------------------------------------------------------
template <typename T>
Vector<T>::Vector(): theSize{0}, theCapacity{0}, array{nullptr}
{
	//default constructor
}



template <typename T>
Vector<T>::Vector(const Vector& rhs): theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, array{nullptr}
{	//copy constructor
	array = new T[theCapacity];
	for(int i = 0; i < theSize; i++)
		array[i] = rhs.array[i];
}

template <typename T>
Vector<T>::Vector(Vector&& rhs): theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, array{rhs.array}
{	//move constructor
	rhs.array = nullptr;
	rhs.theSize = 0;
	rhs.theCapacity = 0;
}

template <typename T>
Vector<T>::Vector(int num, const T& val): theSize{num}, theCapacity{num}, array{nullptr}
{	//constructs vector of size num, with all elements being val
	array = new T[theCapacity];
	for(int i = 0; i < theSize; i++)
		array[i] = val;
}

template <typename T>
Vector<T>::Vector(const_iterator start, const_iterator end): theSize{0}, theCapacity{0}, array{nullptr}
{	//constructor, sets elements to the elements in the range of another vector
	theSize = std::distance(start, end);
	theCapacity = theSize + 10;

	array = new T[theCapacity];
	for(int i = 0; i < theSize; i++)
		array[i] = *(start + i);
}

template <typename T>
Vector<T>::~Vector()
{	//destructor
	delete [] array;
}

template <typename T>
T& Vector<T>::operator[](int index)
{
	return array[index];
}

template <typename T>
const T& Vector<T>::operator[](int index) const
{
	return array[index];
}

template <typename T>
const typename Vector<T>::Vector& Vector<T>::operator=(const Vector& rhs)
{	//copy assignment operator=
	Vector copy = rhs;
	std::swap(*this, copy);
	return *this;
}

template <typename T>
typename Vector<T>::Vector& Vector<T>::operator=(Vector&& rhs)
{	//move assignment operator=
	std::swap(theSize, rhs.theSize);
	std::swap(theCapacity, rhs.theCapacity);
	std::swap(array, rhs.array);
}

template <typename T>
T& Vector<T>::at(int loc)
{	//returns reference to element at loc, throws exception if index is out of bounds
	if(loc < 0 || loc >= theSize)
		throw std::out_of_range("Error, index is not in the valid range of [0,theSize)");

	return array[loc];
}

template <typename T>
const T& Vector<T>::at(int loc) const
{	//returns const reference to element at loc, throws exception if index is out of bounds
	if(loc < 0 || loc >= theSize)
		throw std::out_of_range("Error, index is not in the valid range of [0,theSize)");

	return array[loc];
}

template <typename T>
T& Vector<T>::front()
{	//retuens reference to first element in array
	return array[0];
}

template <typename T>
const T& Vector<T>::front() const
{	//returns const reference to first element in array
	return array[0];
}

template <typename T>
T& Vector<T>::back()
{	//returns reference to last element in array
	return array[theSize - 1];
}

template <typename T>
const T& Vector<T>::back() const
{	//returns const reference to last element in array
	return array[theSize - 1];
}

template <typename T>
int Vector<T>::size() const
{	//returns size
	return theSize;
}

template <typename T>
int Vector<T>::capacity() const
{	//returns capacity
	return theCapacity + 1;
}

template <typename T>
bool Vector<T>::empty() const
{	//returns true if array is empty, false otherwise
	return (size() == 0);
}

template <typename T>
void Vector<T>::clear()
{	//sets size to 0, for an empty array
	theSize = 0;
}

template <typename T>
void Vector<T>::push_back(const T& val)
{	//if size == capacity, double capacity
	if(theSize == theCapacity)
		reserve((2 * theCapacity + 1));

	array[theSize++] = val;		//increases size and sets last element of array to val
}


template <typename T>
void Vector<T>::pop_back()
{	//reduces size by 1
	theSize--;
}

template <typename T> void Vector<T>::resize(int num, T val)
{	//resizes array to size num, if num > theSize then the new elements added are set to val
	int tempSize = theSize;

	if(num > theSize)
	{
		theSize = num;
		reserve((2 * num) + 1);
		for(int i = tempSize; i < theSize; i++)
			array[i] = val;
	}
	else
		theSize = num;
}

template <typename T> void Vector<T>::reserve(int size)
{	//if size < theSize, do nothing
	if(size < theSize)
		return;

	//creates a new array of size [size] and moves all elements into this array
	T *newArray = new T[size];
	for(int i = 0; i < theSize; i++)
		newArray[i] = std::move(array[i]);

	//changes capacity to size, then swap newArray into array and delete newArray
	theCapacity = size;
	std::swap(array, newArray);
	delete [] newArray;
}

template <typename T>
void Vector<T>::print(std::ostream& os, char ofc) const
{	//prints vector, element by element
	for(int i = 0; i < theSize; i++)
		os << array[i] << ofc;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::begin()
{	//returns address of first element in the array
	return &array[0];
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const
{	//returns address as const_iterator of the first element in the array
	return &array[0];
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end()
{	//returns address of element after the last one in the array
	return &array[size()];
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::end() const
{	//returns address as const_iterator of element after the last one
	return &array[size()];
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator itr, const T& val)
{	//if the size == the capacity, double capacity
	if(theSize == theCapacity)
		reserve((2 * theCapacity) + 1);

	//increases the size by 1, then shifts all elements between itr and end() to the right
	theSize++;
	for(iterator it = end() - 1; it != itr - 1; it--)
		*(it + 1) = *it;

	*itr = val;		//inserting val into itr
	return itr;		//returning iterator to the inserted value
}

template <typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator itr)
{	//erases the value pointed to by the given iterator by shifting everything after it to the left
	for(iterator it = itr; it != end() - 1; it++)
		*it = *(it + 1);

	theSize--;

	return itr++;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator start, iterator end)
{	//moves elements starting at end all the way left to start
	int dist = std::distance(start, end);

	for(iterator it = start; it != end; it++)
		*it = *(it + dist);

/*	//causes segmentation fault in erase(itr) function
	for(iterator itr = start; itr != end;)
		itr = erase(itr);
*/
	theSize -= dist;

	return end;
}

template <typename T>
void Vector<T>::doubleCapacity()
{	//doubles capacity
	if(theCapacity == 0)
		theCapacity = 1;
	else
		theCapacity *= 2;
}


//OVERLOADS--------------------------------------------------------------------------------------------------------
template <typename T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs)
{	//if the size is different: return false, if it is the same, check element by element
	if(lhs.size() == rhs.size())
	{
		for(int i = 0; i < lhs.size(); i++)
		{
			if(lhs[i] != rhs[i])
				return false;
		}
		return true;
	}

	return false;
}

template <typename T>
bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs)
{
	return !(lhs == rhs);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v)
{	//prints all of the elements in the vector
	for(int i = 0; i < v.size(); i++)
	{
		os << v[i] << ' ';
	}

	return os;
}

#endif
