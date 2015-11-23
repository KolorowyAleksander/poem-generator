#include"Sonet.h"

Sonet::Sonet(SentencePattern &pattern,Dictionary &dictionary) 
	: Poem(14,0,pattern, dictionary)  {
	this->syll_per_verse = 13;
}

Sonet::~Sonet(){

}

string Sonet :: choose_words(char** patterns_table){
	//initial
	string *poem = new string[lines_number];
	this->rhyme_syllable = "";
	string final_poem = "";
	for (int j = 0; j < 3; j++){
		for (int i = 0; i < 4; i++){ // the first and second verse of stanzas
			if (i % 4 == 0 || (i - 1) % 4 == 0){
				poem[i] = get_text(patterns_table[i]);
				while (poem[i] == ""){ //get new pattern until find sth with appropriate number of words
					patterns_table[i] = pattern.get_pattern();
					poem[i] = get_text(patterns_table[i]);
				}
				final_poem = final_poem + poem[i] + '\n';
			}
			else if (i % 2 == 0 || (i - 1) % 2 == 0){ // the third and fourth verse of stanzas
				this->rhyme_syllable = last_syllable_of_verse(poem[i - 2]);
				poem[i] = get_text(patterns_table[i]);
				while (poem[i] == ""){ //get new pattern until find sth with appropriate number of words
					patterns_table[i] = pattern.get_pattern();
					poem[i] = get_text(patterns_table[i]);
				}
				final_poem = final_poem + poem[i] + '\n';
				this->rhyme_syllable = "";
			}
		}
	}
	
	//and the couplet
	poem[12] = get_text(patterns_table[12]);
	while (poem[12] == ""){ //get new pattern until find sth with appropriate number of words
		patterns_table[12] = pattern.get_pattern();
		poem[12] = get_text(patterns_table[12]);
	}
	final_poem = final_poem + poem[12] + '\n';
	this->rhyme_syllable = last_syllable_of_verse(poem[12]);
	poem[13] = get_text(patterns_table[1]);
	while (poem[13] == ""){ //get new pattern until find sth with appropriate number of words
		patterns_table[13] = pattern.get_pattern();
		poem[13] = get_text(patterns_table[13]);
	}
	final_poem = final_poem + poem[13] + '\n';
	this->rhyme_syllable = "";
	this->poem = final_poem;
	return final_poem;
}
