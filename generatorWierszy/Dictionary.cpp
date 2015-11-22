#include "Dictionary.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include "word_type.h"

Dictionary::Dictionary(){
	this->words = new std::list<Word>; //make a list for words from file
	//read from file to list
	std::fstream file(this->filename);
	file.open(this->filename, std::ios::in);
	file.clear();
	std::string a;
	while (getline(file, a)){
		size_t found = a.find_first_of(" ");
		std::cout << "czytam: "<< a.substr(0, found) << " " << a.substr(found + 1) <<"\n";
		if (Word_type::strToInt(a.substr(found + 1)) != 0)
			this->add(a.substr(0, found), Word_type::strToInt(a.substr(found + 1)));
		else
			std::cout << "some kinda error happened\n";
	}
	file.close();
	//stuff
}

Dictionary::~Dictionary(){
	//stuff
	std::fstream file(this->filename);
	file.open(this->filename, std::ios::out);
	file.clear();
	for (auto i : *words)
		file << i;
	file.close();
	delete this->words; //free list from memory
}

void Dictionary::add(std::string word, int type){
	this->words->emplace_back(word, type);
}

void Dictionary::remove(std::string word){
	Word a(word);
	std::remove(words->begin(), words->end(), a);
}

void Dictionary::print_list(){
	std::list<Word>::iterator it;
	for (it = words->begin(); it != words->end(); ++it){
		std::cout << it->word << std::endl;
	}
}

Word *Dictionary::get_word(int type){
	return nullptr;
}

std::ostream& operator<<(std::ostream& os, const Word& a){
	os << a.word << " " << Word_type::intToString(a.type) << "\n";
	return os;
}
