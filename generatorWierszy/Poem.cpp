#include "Poem.h"


Poem::Poem(int lines_number,bool rhymed, SentencePattern &pattern, Dictionary &dictionary)
{
	this->lines_number = lines_number;
	this->pattern= pattern;
	this->dictionary = dictionary;
	this->rhymed = rhymed;
}
Poem::Poem()
{
}

Poem::~Poem()
{
}


string* Poem::make_poem(){
	char ** paterns_table = this->choose_patterns();
	string string_jakis= "lalal";
	return &string_jakis;
}


char** Poem::choose_patterns(){
	char ** patterns_table = new char*[lines_number];
	for (int i = 0; i < lines_number; i++){
		patterns_table[i] = pattern.get_pattern();
	}
	return patterns_table;
}

char * Poem:: get_text(int syllabes, char* verse, bool rhymed){
	int i = 0;
	char next_char = verse[i];
	int already_syllabes=0;
	Word *word;
	char * concrate_verse = new char[sizeof(verse)];
	while (next_char != '#'){
		if (next_char < 9){ // transformate to word
			word =  dictionary.get_word(next_char); // zamienic next_char na int
			already_syllabes = +word->syllables;
		}
		else{ //rewrite to output table
			concrate_verse[i] = next_char;
		}
		i++;
		next_char = verse[i];
	}
	already_syllabes =+ verse[++i];
	if (already_syllabes != syllabes){
		return NULL; 
	}
	else
		return concrate_verse;
}

char** Poem::choose_words(char **patterns_table){
	char **poem = new char*[lines_number];
	//choosing words until get right size of verse
	for (int i = 0; i < lines_number; i++){
		poem[i] = get_text(syll_per_verse, patterns_table[i], rhymed);
		while (!poem[i]){
			poem[i] = get_text(syll_per_verse, patterns_table[i], rhymed);
		}
	}
	
	return poem;
}