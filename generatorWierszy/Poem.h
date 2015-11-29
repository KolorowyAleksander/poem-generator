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
	Poem(SentencePattern& pattern, Dictionary& dictionary);
	virtual	~Poem();
	void make_poem();
	void print_poem();
	string get_text();
	void save_poem(); //save text of poem to file poem.txt
protected:
	int lines_number; // number of verse
	int syll_per_verse; // number of syllables for each verse
	bool rhymed; // TRUE if poem is rhymed, FALSE else
	string poem; // final text of poem
	string rhyme_syllable; // last syllable of verse to find rhyme, NULL if unnecessary
	char ** patterns_table;

	Dictionary &dictionary;
	SentencePattern &pattern;
	
	virtual char ** choose_patterns(); // for each line choose patterns from pattern_list 
	string get_text(char* verse);
	string last_syllable_of_verse(string verse); // finding last word of verse
	virtual string choose_words();// with function get_text finding a words with property number of syllabes
	int count_words(char*verse); // count words in verse
	int stat_num_syllables(char*verse); // ile ma wbudowanych sylab
	int * div_syllables(int num_words, int stat_num_syllables); // assigns to each word the number of syllables
	

private:
	
};


#endif