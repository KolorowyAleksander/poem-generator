#ifndef _POEM
#define _POEM
#include <string>
#include <list>
#include <iostream>
#include "SentencePattern.h"
#include "Dictionary.h"
#include "Word.h"
using namespace std;
class Poem
{
public:
	Poem(int lines_number, bool rhymed, SentencePattern &pattern, Dictionary &dictionary);
	Poem();
	~Poem();
	string *make_poem();
	string *poem; // final text of poem
	void print_poem();
protected:
	int lines_number; // number of verse
	int syll_per_verse; // number of syllables for each verse
	bool rhymed; // TRUE if poem is rhymed, FALSE else
	list<Word> *word; // list of words from which arises a poem
	Dictionary dictionary;
	SentencePattern pattern;
	char* rhyme_syllable; // last syllable of verse to find rhyme, NULL if unnecessary
	virtual char ** choose_patterns(); // for each line choose patterns from pattern_list 
	char * get_text(char* verse); // change pattern to property words creating one single verse
	virtual char** choose_words(char **patterns_table);  // with function get_text finding a words with property number of syllabes
	char * last_syllable_of_verse(char* verse); // finding last word of verse

private:

};


#endif