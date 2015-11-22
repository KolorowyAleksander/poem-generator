#include "Dadaistic.h"

Dadaistic::Dadaistic(SentencePattern &pattern, Dictionary &dictionary){
	this->lines_number = (rand() % 20) + 1; // min 1 verse, max 20 verse
	this->rhymed = rand() % 2;
	this->syll_per_verse = NULL;
	this->dictionary = dictionary;
	this->pattern = pattern;

}

Dadaistic::~Dadaistic(){

}

char** Dadaistic::choose_patterns(){
	int rand_word; // contains int type of word
	char ** patterns_table = new char*[lines_number];
	for (int i = 0; i < lines_number; i++){
		int size = (rand() % 4) + 2; // random number of words in verse
		char * verse = new char[size +size-1]; //size = number of words, size-1  = number of spaces between words
		for (int n = 0; n < size; n++){
			if (n % 2 == 0){ // if it's word turn
				rand_word = (rand() % 6) + 1; // generates random type of word
				char ch_rand_word[2];
				sprintf_s(ch_rand_word, 2, "%d", rand_word); // change int to char;
				verse[n] = *ch_rand_word;
			}
			else{//if it's space turn
				verse[n] = 32;
			}	
		}
		patterns_table[i] = verse;
	}
	return patterns_table;
}