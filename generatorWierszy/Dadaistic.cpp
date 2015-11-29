#include "Dadaistic.h"

Dadaistic::Dadaistic( SentencePattern &pattern,Dictionary &dictionary): Poem(pattern,dictionary){
	this->lines_number = (rand() % 20) + 1; // min 1 verse, max 20 verse
	this->rhymed = rand() % 2;
	this->syll_per_verse = NULL;
	this->dictionary = dictionary;
	this->patterns_table = new char*[lines_number];


}

Dadaistic::~Dadaistic(){

}
char* Dadaistic::get_pattern(){
	//initial
	int rand_word; // contains int type of word
	int i = rand() % lines_number;
	int size = (rand() % 4) + 3; // random number of words in verse
	string verse = "";


	for (int n = 0; n < size; n++){
		if (n % 2 == 0){ // if it's word turn
			rand_word = (rand() % 6) + 1; // generates random type of word
			char ch_rand_word[2];
			sprintf_s(ch_rand_word, 2, "%d", rand_word); // change int to char;
			verse = verse + *ch_rand_word;
		}
		else if (n == size - 1){
		}
		else{//if it's space turn
			verse = verse + ' ';
		}
	}
	if (i % 7 == 0){
		verse = verse + "!#0";
	}
	else if (i % 5 == 0){
		verse = verse + "?#0";
	}
	else if (i % 2 == 0){
		verse = verse + ".#0";
	}
	else {
		verse = verse + ",#0";
	}
	char * pattern = new char[verse.length() + 1];
	strcpy_s(pattern, verse.length() + 1, verse.c_str());
	return pattern;
}

char** Dadaistic::choose_patterns(){
	char ** patterns_table = new char*[lines_number];
	for (int i = 0; i < lines_number; i++){
		patterns_table[i] = get_pattern();
	}
	return patterns_table;
}

string Dadaistic::choose_words(){
	//initial
	int i = 0;
	string *poem = new string[lines_number];
	string final_poem = "";

	//choosing words until get right size of verse
	
	for (int i = 0; i < lines_number; i++){
		this->syll_per_verse = rand() % 8 + 4;
		poem[i] = get_text(patterns_table[i]);
			while (poem[i] == ""){
				patterns_table[i] = get_pattern();
			poem[i] = get_text(patterns_table[i]);
			}
		final_poem = final_poem + poem[i] + '\n';
	}
	this->poem = final_poem;
	return final_poem;
}