#include"Sonet.h"

Sonet::Sonet(SentencePattern &pattern,Dictionary &dictionary) 
	: Poem(14,1,pattern, dictionary)  {
}

Sonet::~Sonet(){

}

char** Sonet :: choose_words(char** patterns_table){
	char **poem = new char*[lines_number];
	this->rhym_word = NULL;
	for (int i = 0; i < 4; i++){
		if (i % 4 == 0 || (i - 1) % 4 == 0){
			poem[i] = get_text(patterns_table[i]);
		}
		else if (i % 2 == 0|| (i-1) % 2 == 0){
			this->rhym_word = last_word_of_verse(poem[i - 2]);
			poem[i] = get_text(patterns_table[i]);
			this->rhym_word = NULL;
		}
	}
	poem[12] = get_text(patterns_table[12]);
	this->rhym_word = last_word_of_verse(poem[12]);
	poem[13] = get_text(patterns_table[1]);
	this->rhym_word = NULL;
	return poem;
}
