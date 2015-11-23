#include "Word.h"
#include <iostream>

Hyphenate::Hyphenator Word::hyph(RFC_3066::Language("en"));

Word::Word(std::string word){
	this->word = word;
};

Word::Word(std::string word, int type){
	this->word = word;
	this->type = type;
	std::string tmp = hyph.hyphenate(word);
	this->syllables = 0;
	for (auto i : tmp)
		if (i == '-') this->syllables++;
	this->syllables++;
	if(size_t found = tmp.find_last_of('-'))
		this->last_syllable = tmp.substr(found + 1);
}

bool Word::operator==(const Word &a) const{
	return this->word == a.word;
	}
