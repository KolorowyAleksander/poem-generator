#include "Dadaistic.h"

Dadaistic::Dadaistic(SentencePattern &pattern, Dictionary &dictionary){
	this->lines_number = (rand() % 20) + 1;
	this->rhymed = rand() % 1;
	this->syll_per_verse = (rand() % 10) + 4;
	this->dictionary = dictionary;
	this->pattern = pattern;
	this->make_poem();

}

Dadaistic::~Dadaistic(){

}
char** Dadaistic::choose_patterns(){
	char ** patterns_table = new char*[lines_number];
	char * char_pattern = pattern.get_pattern();
	for (int i = 0; i < lines_number; i++){
		char_pattern = pattern.get_pattern();
		patterns_table[i] = new char[sizeof(char_pattern)];
		*patterns_table[i] = *char_pattern;
		cout << char_pattern << endl;
	}
	return patterns_table;
}
