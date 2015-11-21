#include "Dictionary.h"
#include <iostream>
#include <algorithm>
#include <fstream>

Dictionary::Dictionary(){
	this->words = new std::list<Word>; //make a list for words from file
	//read from file to list
	std::fstream file(this->filename);
	file.open(this->filename, std::ios::in);
	file.clear();
	
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
	os << a.word << " " << a.type << "\n";
	return os;
}
