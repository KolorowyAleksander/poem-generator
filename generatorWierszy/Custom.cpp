#include "Custom.h"

Custom::Custom(int lines_number,bool rhymed,SentencePattern &pattern, Dictionary &dictionary) 
	: Poem(lines_number,rhymed, pattern, dictionary) {
}

Custom :: ~Custom(){

}

char** Custom::choose_patterns(){
	char ** patterns_table = new char*[lines_number];
	for (int i = 0; i < lines_number; i++){
		patterns_table[i] = pattern.get_pattern();
	}
	return patterns_table;
}
