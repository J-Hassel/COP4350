//Name: Jonathan /hassel
//Date: 2/23/17
//Class: cop4530 - Duan
#include <algorithm>
#include <iostream>
#include <deque>
#include <fstream>
#include <string>
#include <vector>
#include "Queue.h"

using namespace cop4530;
using namespace std;

int getIndex(string city, string* cities);

int main(int argc, char* argv[])
{
	if(argc == 2)				//only time program runs is when 2 arguments are passed
	{
		ifstream fin;			//file input stream
		fin.open(argv[1]);		//opens the file

		if(fin.is_open())		//if file is open, run program. Else file is invalid
		{
			int numDest, temp;
			fin >> numDest >> ws;		//gets the first line in the input file, the number of destinations

			int matrix[numDest][numDest];		//creates a 2D matrix of size numDest
			string cities[numDest], source, destination, tempInput;		//string array to hold city names

			//gets all city names and puts them in array
			for(int i = 0; i < numDest; ++i)
				getline(fin, cities[i]);

			//fills matrix according to input file matrix
			for(int i = 0; i < numDest; ++i)
			{
				for(int j = 0; j < numDest; ++j)
				{
					fin >> temp;
					matrix[i][j] = temp;
				}
			}

			fin.close();		//closes input file stream

			//printing cities
			cout << numDest << " cities:" << endl;
			for(int i = 0; i < numDest; ++i)
				cout << "    " << cities[i] << endl;

			//printing connections between cities
			cout << "\ndirect flights between cities" << endl << "-------------------------" << endl;
			for(int i = 0; i < numDest; ++i)
			{
				cout << cities[i] << ":" << endl;
				for(int j = 0; j < numDest; ++j)
				{
					if(matrix[i][j] > 0)
						cout << "    " << cities[j] << ", $" << matrix[i][j] << endl;
				}
			}
			cout << "------------------------" << "\n\n";

			//for finding the least amount of hops between source and destination cities
			do
			{
				int s = 0, d = 0;		//used later to check if user inputs valid cities

				cout << "Source city: ";
				getline(cin, source);

				cout << "Destination city: ";
				getline(cin, destination);

				cout << "finding min_hop route...." << endl;

				//checks if cities are valid // dont need this if I implement failure and success functions
				for(int i = 0; i < numDest; ++i)
				{
					if(source == cities[i])
						s++;

					if(destination == cities[i])
						d++;
				}

				//if cities are invalid, print error, else find path with least amount of hops between cities
				if(s == 0)
					cout << "   path not found, source city, " << source << ", not on the map" << endl;
				else if(d == 0)
					cout << "   path not found, destination city, " << destination << ", not on the map" << endl;
				else		//breadth first search to find path with least hops
				{

					//BFS----------------------------------------------------------------------------------------------------------------

					Queue<string, deque<string> > path;
					vector <string> shortestPath;
					bool visited[numDest];
					int parent[numDest], price = 0;
					string neighbor, temp;

					//initializing boolean array to all false
					for(int i = 0; i < numDest; ++i)
						visited[i] = false;

					path.push(source);
					visited[getIndex(source, cities)] = true; 	//mark the start location as visited
					parent[getIndex(source, cities)] = -1;		//source has no parent

					while(!path.empty())
					{
						temp = path.front();
						vector <int> neighbors;

						for(int i = 0; i < numDest; ++i)
						{	//finding the neighbors of temp
							if(matrix[getIndex(temp, cities)][i] > 0 && visited[i] == false)
							{
								neighbors.push_back(i);					//pushes the neighbors index into neighbors vector
								parent[i] = getIndex(temp, cities);		//sets temp as the parent of neighbors
							}
						}

						for(int i = 0; i < neighbors.size(); ++i)
						{	//pushing the neighbor into path and checking if it is the destination
							neighbor = cities[neighbors[i]];
							path.push(neighbor);
							if(neighbor == destination)
								goto success;		//jumps to success label(out of both loop

							visited[neighbors[i]] = true;		//marks neighbor as visited
						}
						path.pop();
					}
					//END BFS------------------------------------------------------------------------------------------------------------

					//jumps here when success is reached
					success:

					//pushes the parent of the last thing in the vector into the back of the vector, until -1 is reached
					shortestPath.push_back(destination);
					while(true)
					{
						if(parent[getIndex(shortestPath.back(), cities)] == -1)
							break;

						//pushing parent of back()
						shortestPath.push_back(cities[parent[getIndex(shortestPath.back(), cities)]]);

						//adding the price between the two cities to the sum(price)
						price += matrix[getIndex(shortestPath.end()[-2], cities)][getIndex(shortestPath.back(), cities)];
					}

					//reverse the vector to get path in the correct direction
					reverse(shortestPath.begin(), shortestPath.end());

					if(shortestPath.size() > 1)
					{	//if path > 1, then print with arrows, else dont
						cout << "   " << shortestPath[0];
						for(int i = 1; i < shortestPath.size(); ++i)
							cout << " -> " << shortestPath[i];

						cout << ", $" << price << endl;
					}
					else
						cout << "   " << shortestPath[0] << ", $" << price << endl;

				}

				do		//asks user if they want to search another route. Loops until input is valid
				{
					cout << "\nSearch another route? (Y/N)";
					getline(cin, tempInput);

				}while(tempInput != "Y" && tempInput != "y" && tempInput != "N" && tempInput != "n");

			}while(tempInput == "Y" || tempInput == "y");		//if user input is 'n' ot 'N', exit program
		}
		else		//prints error if file is not valid
			cout << "Error: \"" << argv[1] << "\" is not a valid file." << endl;
	}
	else		//prints usage when command line arguments are not == 2
		cout << "Usage: proj3.x airline_file" << endl;

	return 0;
}



int getIndex(string city, string* cities)
{
	for(int i = 0; i < cities->size() + 1; ++i)
		if(city == cities[i])
			return i;
}
