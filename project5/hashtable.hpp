#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
//Name: Jonathan Hassel
//Date: 4/10/17
//Class: cop4530 - Duan

#include "hashtable.h"

//HASH TABLE CLASS---------------------------------------------------------------------------------------------------

//PUBLIC MEMBER FUNCTIONS--------------------------------------------------------------------------------------------
template <typename T>
HashTable<T>::HashTable(size_t size): table{prime_below(size)}, currentSize{0}
{	//single parameter constructor: initializes the hashtable
	makeEmpty();
	std::cout << table.size() << '\n';
}

template <typename T>
HashTable<T>::~HashTable()
{	//destructor
	makeEmpty();
}

template <typename T>
bool HashTable<T>::contains(const T& x)
{	//uses myhash() to find correct index of a value, then searches the list for it
	auto& whichList = table[myhash(x)];
	return std::find(begin(whichList), end(whichList), x) != end(whichList);
}

template <typename T>
bool HashTable<T>::insert(const T& x)
{	//checks to see if value already exists
	auto& whichList = table[myhash(x)];
	if(std::find(begin(whichList), end(whichList), x) != end(whichList))
		return false;

	//if value does not exist, the list is added to the vector and current size is incremented
	whichList.push_back(x);

	//if current size > table size then rehash is called
	if(++currentSize > table.size())
		rehash();

	return true;
}

template <typename T>
bool HashTable<T>::insert(T&& x)
{	//same as above, just the move version
	auto& whichList = table[myhash(std::move(x))];
	if(std::find(begin(whichList), end(whichList), std::move(x)) != end(whichList))
		return false;

	whichList.push_back(std::move(x));

	if(++currentSize > table.size())
		rehash();

	return true;
}

template <typename T>
bool HashTable<T>::remove(const T& x)
{	//finds the index in which the value should be, then erases it and decrements the currentSize
	auto& whichList = table[myhash(x)];
	auto itr = std::find(begin(whichList), end(whichList), x);

	if(itr == end(whichList))
		return false;

	whichList.erase(itr);
	--currentSize;
	return true;
}

template <typename T>
void HashTable<T>::clear()
{	//calls makeEmpty() function to clear entire table
	makeEmpty();
}

template <typename T>
bool HashTable<T>::load(const char* filename)
{	//input stream to read from file
	std::ifstream fin;
	std::string word;

	//clearing input stream and opening file
	fin.clear();
	fin.open(filename);
	if(!fin)
		return false;		//file not opened: failure

	//while getline still gets a word, insert it into table
	while(getline(fin, word))
		insert(word);

	fin.close();		//closing file: success
	return true;

}

template <typename T>
void HashTable<T>::dump()
{	//prints the entire hash table by index
	for(int i = 0; i < table.size(); ++i)
	{
		std::cout << "v[" << i << "]: ";

		for(auto itr = table[i].begin(); itr != table[i].end(); ++itr)
			std::cout << *itr << '\t';

		std::cout << '\n';
	}
}

template <typename T>
bool HashTable<T>::write_to_file(const char* filename)
{	//output stream to write to a file
	std::ofstream fout;

	//clearing output stream and opening file
	fout.clear();
	fout.open(filename);
	if(!fout)
		return false;		//file not opened: failure

	//writes all the elements of the table to a file, each element seperated by a newline
	for(int i = 0; i < table.size(); ++i)
		for(auto itr = table[i].begin(); itr != table[i].end(); ++itr)
			fout << *itr << '\n';

	fout.close();		//closing file: success
	return true;
}

template <typename T>
int HashTable<T>::getCurrentSize()
{
	return currentSize;
}

//PRIVATE MEMBER FUNCTIONS-------------------------------------------------------------------------------------------
template <typename T>
void HashTable<T>::makeEmpty()
{	//deletes every element in the table
	currentSize = 0;
	for(auto& element : table)
		element.clear();
}

template <typename T>
void HashTable<T>::rehash()
{	//creating a temporary hashtable to save old data before resizing
	std::vector<std::list <T> > temp = table;

	//resizing, then clearing table
	table.resize(prime_below(2 * temp.size()));
	for(auto& element : table)
		element.clear();

	//setting currentSize to 0, then moving old data back to newly resized table
	currentSize = 0;
	for(auto& element : temp)
		for(auto& x : element)
			insert(std::move(x));
}

template <typename T>
size_t HashTable<T>::myhash(const T& x)
{	//hash function to get index
	size_t hash = 0;
	for(auto element : x)
		hash = 23 * hash + element;

	return hash % table.size();		//% by table.size() to get a range from 0 - table size
}

//returns largest prime number <= n or zero if input is too large
//this is likely to be more efficient than prime_above(), because
//it only needs a vector of size n
template <typename T>
unsigned long HashTable<T>::prime_below (unsigned long n)
{
	if (n > max_prime)
	{
		std::cerr << "** input too large for prime_below()\nset to default capacity\n";
		return default_capacity;
	}

	if (n == max_prime)
		return max_prime;
	if (n <= 1)
	{
		std::cerr << "** input too small\nset to default capacity\n";
		return default_capacity;
	}

	// now: 2 <= n < max_prime
	std::vector <unsigned long> v (n+1);
	setPrimes(v);
	while (n > 2)
	{
		if (v[n] == 1)
			return n;
		--n;
	}

	return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n)
template <typename T>
void HashTable<T>::setPrimes(std::vector<unsigned long>& vprimes)
{
	int i = 0;
	int j = 0;

	vprimes[0] = 0;
	vprimes[1] = 0;
	int n = vprimes.capacity();

	for (i = 2; i < n; ++i)
		vprimes[i] = 1;

	for( i = 2; i*i < n; ++i)
	{
		if (vprimes[i] == 1)
		{
			for(j = i + i ; j < n; j += i)
				vprimes[j] = 0;
		}
	}
}



#endif
