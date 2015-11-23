#include "Haiku.h"

Haiku::Haiku(SentencePattern &pattern, Dictionary &dictionary) : Poem(3, 0, pattern, dictionary) {
}

Haiku :: ~Haiku(){

}

char** Haiku::choose_patterns(){
	//initial
	int rand_word; // contains int type of word
	char ** patterns_table = new char*[lines_number];

	for (int i = 0; i < lines_number; i++){
		int size = (rand() % 4) + 2; // random number of words in verse
		char * verse = new char[size + size - 1]; //size = number of words, size-1  = number of spaces between words
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

string Haiku::choose_words(char **patterns_table){
	//initial
	int i = 0;
	string *poem = new string[lines_number];
	string final_poem = "";

	//choosing words until get right size of verse
	this->syll_per_verse = 5;
	poem[0] = get_text(patterns_table[0]);
	while (poem[0]==""){
		poem[0] = get_text(patterns_table[0]);
	}
	final_poem = final_poem + poem[0] + '\n';
	this->syll_per_verse = 7;
	poem[1] = get_text(patterns_table[1]);
	while (poem[1]==""){
		poem[1] = get_text(patterns_table[1]);
	}
	final_poem = final_poem + poem[1] + '\n';
	this->syll_per_verse = 5;
	poem[2] = get_text(patterns_table[2]);
	while (poem[2]==""){
		poem[2] = get_text(patterns_table[2]);
	}
	final_poem = final_poem + poem[2] + '\n';
	this->poem = final_poem;
	return final_poem;
}
