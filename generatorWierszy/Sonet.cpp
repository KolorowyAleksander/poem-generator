#include"Sonet.h"

Sonet::Sonet(SentencePattern &pattern,Dictionary &dictionary) 
	: Poem(14,1,pattern, dictionary)  {
}

Sonet::~Sonet(){

}


char** Sonet::choose_patterns(){
	char ** patterns_table = new char*[lines_number];
	for (int i = 0; i < lines_number; i++){
		patterns_table[i] = pattern.get_pattern();
	}
	return patterns_table;
}
