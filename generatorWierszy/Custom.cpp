#include "Custom.h"

Custom::Custom(int lines_number,bool rhymed,int syll_per_verse ,SentencePattern &pattern, Dictionary &dictionary) 
	: Poem(lines_number,rhymed, pattern, dictionary) {
	this->syll_per_verse = syll_per_verse;
}

Custom :: ~Custom(){

}


