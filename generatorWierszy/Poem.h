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
	Poem(SentencePattern &pattern, Dictionary &dictionary);
	//Poem();
	virtual ~Poem();
	Poem();
	void make_poem();
	void print_poem();

protected:
	int lines_number; // number of verse
	int syll_per_verse; // number of syllables for each verse
	bool rhymed; // TRUE if poem is rhymed, FALSE else
	string poem; // final text of poem
	string rhyme_syllable; // last syllable of verse to find rhyme, NULL if unnecessary
	char ** patterns_table;
	//list<Word> *word; // list of words from which arises a poem
	Dictionary &dictionary;
	SentencePattern &pattern;
	
	virtual char ** choose_patterns(); // for each line choose patterns from pattern_list 
	char * get_text_old(char* verse); // change pattern to property words creating one single verse
	string get_text(char* verse);
	string last_syllable_of_verse(string verse); // finding last word of verse
	int count_words(char*verse); // count words in verse
	int stat_num_syllables(char*verse); // ile ma wbudowanych sylab
	virtual string choose_words();// with function get_text finding a words with property number of syllabes
	int * div_syllables(int num_words); // 

private:
	
};


#endif