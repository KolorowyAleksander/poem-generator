#include "Haiku.h"

Haiku::Haiku(SentencePattern &pattern,Dictionary &dictionary) : Poem(3,0, pattern,dictionary) {
	this->make_poem();
}

Haiku :: ~Haiku(){

}

char** Haiku::choose_patterns(){
	srand(time(NULL));
	int rand_word;
	char ** patterns_table = new char*[lines_number];
	for (int i = 0; i < lines_number; i++){
		int size = (rand() % 4) +2;
		char * verse = new char[size];
			for (int n = 0; n < size; n++){
				rand_word = rand() % 5 +1;
				char ch_rand_word[2];
				sprintf_s(ch_rand_word, 2, "%d", rand_word); // change int to char;
				verse[n] = *ch_rand_word;
			}
			patterns_table[i] = verse;
	}
	return patterns_table;
}

char** Haiku::choose_words(char **patterns_table){
	int i = 0;
	char **poem = new char*[lines_number];
	//choosing words until get right size of verse
	poem[0] = get_text(5, patterns_table[0], 0);
	while (!poem[0]){
		poem[0] = get_text(5, patterns_table[0], 0);
	}
	
	poem[1]=get_text(7, patterns_table[1], 0);
	while (!poem[1]){
		poem[1] = get_text(7, patterns_table[1], 0);
	}

	poem[2]=get_text(5, patterns_table[2], 0);
	while (!poem[2]){
		poem[2] = get_text(5, patterns_table[2], 0);
	}

	return patterns_table;
}