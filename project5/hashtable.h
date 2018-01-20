#ifndef HASHTABLE_H
#define HASHTABLE_H
//Name: Jonathan Hassel
//Date: 4/10/17
//Class: cop4530 - Duan

#include <algorithm>
#include <fstream>
#include <list>
#include <string>
#include <vector>

namespace cop4530
{

template <typename T>
class HashTable
{
	public:
		HashTable(size_t size = 101);
		~HashTable();

		bool contains(const T& x);
		bool insert(const T& x);
		bool insert(T&& x);
		bool remove(const T& x);
		void clear();
		bool load(const char* filename);
		void dump();
		bool write_to_file(const char* filename);
		int getCurrentSize();

	private:
		//used when improper size is given (for example
		//size is 0 or negatiave)
		static const unsigned int default_capacity = 11;
		static const unsigned int max_prime = 1301081;
		std::vector< std::list<T> > table;
		int currentSize;

		void makeEmpty();
		void rehash();
		size_t myhash(const T& x);
		unsigned long prime_below(unsigned long x);
		void setPrimes(std::vector<unsigned long>& x);
};

#include "hashtable.hpp"

}//end namespace cop4530
#endif
