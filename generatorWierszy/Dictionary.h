#pragma once

#include <list>
#include "Word.h"

class Dictionary{
public:
	Dictionary(); //default constructor replaced to read from file and dynamically allocate list for bigger memory
	~Dictionary(); //default destructor replaced to save to file and destroy list
	void add(std::string, int type); //Add a word of exact type to the list
	void remove(std::string); //Remove a word from the list
	Word* get_word(int type); //Find random word of exact type
	void print_list();
	friend std::ostream& operator<<(std::ostream &os, const Word &a); //overloaded ostream operator for proper serialization
private:
	std::list<Word> *words; //A container to keep the words in
	std::string filename = "dictionary.txt";

};
