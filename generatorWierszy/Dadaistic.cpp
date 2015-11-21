#include "Dadaistic.h"

Dadaistic::Dadaistic(Dictionary &dictionary){
	srand(time(NULL));
	this->lines_number = (rand() % 20) +1;
	this->rhymed = rand() % 1;
	this->syll_per_verse = (rand() % 10) +4;

}


char** Dadaistic::choose_patterns(){
	char ** patterns_table = new char*[lines_number];
	for (int i = 0; i < lines_number; i++){
		patterns_table[i] = pattern.get_pattern();
	}
	return patterns_table;
}
