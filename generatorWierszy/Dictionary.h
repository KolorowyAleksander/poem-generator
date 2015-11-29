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
	Word* get_word(int type, int syllables); //Find random word of exact type and exact syllabes number
	Word* get_word(int type, int syllables, std::string last_syllable); //Find random word of exact type and exact syllabes number and exact last syllable
	void print_list();
	void read_from_file();
	void save_to_file();
	friend std::ostream& operator<<(std::ostream &os, const Word &a); //overloaded ostream operator for proper serialization
private:
	std::list<Word> *words; //A container to keep the words in
	std::string filename = "dictionary.txt";

};

