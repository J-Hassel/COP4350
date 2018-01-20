//Name: Jonathan Hassel
//Date: 4/20/17
//Class: cop4530 - Duan

#include <cstring>
#include <iostream>
#include <sstream>
#include "hashtable.h"

using namespace cop4530;
using namespace std;

void menu();
void printWithCapitalizedWord(const string& word, const vector<string>& vector);

int main(int argc, char* argv[])
{
	if(argc == 1)	//program is given no command line arguments
	{
		int capacity;
		char choice, filename[40];
		string input;

		cout << "Enter preferred capacity: ";
		cin >> capacity;

		//creating a hashtable of size prime_below(capacity)
		HashTable<string> table(capacity);

		//clearing cin from bad input/overflow
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		do
		{	//menu loop with choice selection
			menu();
			cin >> choice;

			switch(choice)
			{
				case 'l':	//gets filename, loads dictionary into hashtable
					cout << "Enter dictionary filename to load from: ";
					cin >> input;
					strcpy(filename,  input.c_str());

					if(table.load(filename))
						cout << "\nDictionary loaded successfully.\n";
					else
						cout << "\nCannot open file " << input << ".\n";
					break;

				case 'a':	//gets word, inserts it into hashtable if it does not exist
					cout << "Enter word: ";
					cin >> input;

					if(table.insert(input))
						cout << "\nWord " << input << " added.\n";
					else
						cout << "\nError: Word alread exists. Could not add.\n";
					break;

				case 'r':	//gets word, removes it from hashtable if it exists
					cout << "Enter word: ";
					cin >> input;

					if(table.remove(input))
						cout << "\nWord " << input << " deleted.\n";
					else
						cout << "\nError: Word not found. Could not delete.\n";
					break;

				case 'c':	//clears the hashtable
					table.clear();
					break;

				case 'f':	//gets word, searches for it in hashtable, prints whether or not it was found
					cout << "Enter word: ";
					cin >> input;

					if(table.contains(input))
						cout << "\nWord " << input << " found.\n";
					else
						cout << "\nWord " << input << " not found.\n";
					break;

				case 'd':	//prints the hashtable
					table.dump();
					break;

				case 's':	//prints out the current size of the hashtable(how many elements are stored)
					cout << "Size of hashtable: " << table.getCurrentSize() << ".\n";;
					break;

				case 'w':	//gets a filename, writes hashtable to file
					cout << "Enter dictionary file name to write to: ";
					cin >> input;
					strcpy(filename,  input.c_str());

					if(table.write_to_file(filename))
						cout << "\nWritten successfully.\n";
					else
						cout << "\nCould not write to file.\n";
					break;
			}
		}while(choice != 'x');	//x == exit
	}
	else if(argc == 4)		//if there are 3 command line arguments(outside of the programs name)
	{
		HashTable<string> table;
		string line, word;
		char *dictionary = argv[1], *inFile = argv[2], *outFile = argv[3];
		ifstream din, fin;
		ofstream fout;

		//opening all the files
		din.open(dictionary);
		fin.open(inFile);
		fout.open(outFile);

		if(!din)		//if file is not open program ends
		{
			cout << "Cannot open file " << dictionary << "\nGlobal dictionary cannot be loaded\n";
			return 0;
		}

		if(!fin)		//if file is not open program ends
		{
			cout << "Word file cannot be opened\n";
			return 0;
		}

		table.load(dictionary);		//loading dictionary words into hashtable

		while(getline(fin, line))	//gets a sentence from input file
		{
			stringstream sin(line);
			vector<string> sentence;

			while(sin >> word)		//gets a word from sentence and pushes it into a vector
				sentence.push_back(word);

			for(int i = 0; i < sentence.size(); ++i)	//looping through each word in the sentence
			{	//creating a temporary lowercase version of sentence[i]
				string lcWord = sentence[i];
				for(auto& c : lcWord)
					c = tolower(c);

				if(!table.contains(lcWord))		//if word is not in dictionary
				{
					int count = 0;
					char choice;
					string candidates[10];

					printWithCapitalizedWord(sentence[i], sentence);	//prints sentence with word capitalized

					cout << "\n====================================\n";

					for(int j = 0; j < lcWord.size(); ++j)	//for loop to similar words in dictionary to suggest
					{
						string temp = lcWord;
						for(int k = 97; k < 123; ++k)
						{	//replaces each letter of the word with 'a' - 'z' and checks for a match in hashtable
							temp[j] = k;
							if(table.contains(temp))
							{	//getting the original word(case sensitive) and replacing the single character
								string originalWord = sentence[i];
								originalWord[j] = k;

								if(count > 9)		//if count > 10, stop looking for candidates
									goto done;	//to break out of 2 loops

								//prints out the candidate and adds it to the array
								cout << count << "): " << temp << '\n';
								candidates[count] = originalWord;
								count++;
							}
						}
					}

					done:
					cout << "n (no change):";
					cout << "\n====================================\n";
					cout << "Your choice: ";
					cin >> choice;

					if(choice >= '0' && choice <= '9' && candidates[choice - 48] != "")
							sentence[i] = candidates[choice - 48];		//48 is the ascii code for '0'
				}
				fout << sentence[i] << ' ';		//printing word if it is unchanged
			}
			fout << '\n';	//newline after every sentence
		}

		//closing all the files
		din.close();
		fin.close();
		fout.close();
	}
	else	//incorrect usage message
		cout << "proj5.x dictionary file_to_check output_file\n";

	return 0;
}

void menu()
{
	cout << "\n\n";
	cout << "l - Load Dictionary From File" << endl;
	cout << "a - Add Word" << endl;
	cout << "r - Remove Word" << endl;
	cout << "c - Clear HashTable" << endl;
	cout << "f - Find Word" << endl;
	cout << "d - Dump HashTable" << endl;
	cout << "s - HashTable Size" << endl;
	cout << "w - Write to File" << endl;
	cout << "x - Exit program" << endl;
	cout << "\nEnter choice : ";
}

void printWithCapitalizedWord(const string& word, const vector<string>& vector)
{
	string temp = word;

	//capitalizing the word not in hashtable
	for(auto& c : temp)
		c = toupper(c);

	//printing sentence
	for(int i = 0; i < vector.size(); ++i)
	{
		if(vector[i] != word)
			cout << vector[i] << ' ';
		else
			cout << temp << ' ';
	}
}
