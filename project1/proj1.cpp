//Name: Jonathan Hassel
//Date: 1/20/17

//THIS PROGRAM TAKES 35-40 SECONDS TO RUN THROUGH THE 10,000 LINE FILE
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//FUNCTION PROTOTYPES-----------------------------------------------------------------------------------------------
void stringToUniqueVec(string str, vector<int>& myVector, vector<int>::iterator& it);
void stringToVec(string str, vector<int>& myVector);
void removeDuplicates(vector<int>& myVector);
void ignore(int n);
bool finalSort(vector<int> a, vector<int> b);


//MAIN PROGRAM------------------------------------------------------------------------------------------------------
int main()
{
	string temp, finalList;
	vector<int> asNumbers, myVec;
	vector<vector<int> > asList;
	vector<int>::iterator it;

	while(getline(cin, temp, 'T'))
	{
		//ignoring first 6 fields
		ignore(6);

		//gets all the numbers in the 7th field
		getline(cin, temp, '|');

		//string stream to look for assets
		stringstream tin(temp);

		//removes the ASSETS
		while(getline(tin, temp, '['))
		{
			//removes ASSETS
			tin.ignore(128, ']');
		}

		//makes large list of all AS numbers
		finalList.append(temp);
		finalList.append("\n");

		//ignoring last 7 fields
		ignore(7);
	}

	//gets each unique AS number, and populates a vector with them
	stringToUniqueVec(finalList, asNumbers, it);

	//for loop to find neighbors------------------------------------------------------------------------------------
	for(it = asNumbers.begin(); it != asNumbers.end(); it++)
	{
		//string stream for finalList
		stringstream sin(finalList);

		//initializing the temp vector with the unique AS number, then pushing it into asList
		vector<int> tempVec;

		//makes first element of the vector the AS number(move this down)
		tempVec.push_back(*it);

		//while loop sorts though each line in finalList, getting neighbors of *it
		while(getline(sin, temp, '\n'))
		{
			vector<int> myVec;

			stringToVec(temp, myVec);

			for(int i = 0; i < myVec.size(); i++)
			{
				if(myVec[i] == *it)
				{
					if(i == 0)
					{
						if(myVec.size() > 1)
							tempVec.push_back(myVec[i + 1]);
					}
					else if(i > 0)
					{
						if(myVec.size() == i + 1)
							tempVec.push_back(myVec[i - 1]);
						else
						{
							tempVec.push_back(myVec[i + 1]);
							tempVec.push_back(myVec[i - 1]);
						}
					}
				}
			}
		}
		//removing duplicates from tempVec
		removeDuplicates(tempVec);

		//pushing vector into asList
		asList.push_back(tempVec);
	}
//-------------------------------------------------------------------------------------------------------------------
	sort(asList.begin(), asList.end(), finalSort);

	//printing all the data
	for(int i = 0; i < asList.size(); i++)
	{
		cout << asList[i][0] << ' ' << asList[i].size() - 1 << ' ' << asList[i][1];
		for(int j = 2; j < asList[i].size(); j++)
		{
			cout << '|' << asList[i][j];
		}
		cout << '\n';
	}

	return 0;
}


//FUNCTION DEFINITIONS---------------------------------------------------------------------------------------------
void stringToUniqueVec(string str, vector<int>& myVector, vector<int>::iterator& it)
{
	//stream for string input
	stringstream sin(str);
	int number;

	//populating vector with all the AS numbers
	while(sin >> number)
		myVector.push_back(number);

	//sorts vector in ascending order, eliminating duplicates, and resizing the vector
	sort(myVector.begin(), myVector.end());
	it =  unique(myVector.begin(), myVector.end());
	myVector.resize(distance(myVector.begin(), it));
}

void stringToVec(string str, vector<int>& myVector)
{
	//stream for string input
	stringstream sin(str);
	int number;

	//populating vector with all the AS numbers
	while(sin >> number)
		myVector.push_back(number);
}

void removeDuplicates(vector<int>& myVector)
{
	//sorts vector in ascending order, eliminating duplicates, and resizing the vector: excludes first element.
	sort(myVector.begin() + 1, myVector.end());
	myVector.erase(unique(myVector.begin() + 1,myVector.end()), myVector.end());

	for(int i = 1; i < myVector.size(); i++)
	{
		if(myVector[i] == myVector[0])
			myVector.erase(myVector.begin() + i);
	}
}

void ignore(int n)
{
	for(int i = 0; i < n; i++)
		cin.ignore(128, '|');
}

bool finalSort(vector<int> a, vector<int> b)
{
	if(a.size() > b.size())
		return true;
	if(a.size() == b.size())
		return (a[0] < b[0]);
	return false;
}
