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
	Poem(int lines_number,bool rhymed, SentencePattern &pattern, Dictionary &dictionary);
	Poem();
	~Poem();
	virtual char ** choose_patterns(); // for each line choose patterns from pattern_list 

protected:
	int lines_number; 
	int syll_per_verse; 
	bool rhymed;
	list<Word> *word; // list of words from which arises a poem
	string *poem; // final text of poem
	string *make_poem();
	char * get_text(int syllabes, char* verse, bool rhymed); // change pattern to property words creating one single verse
	char** choose_words(char **patterns_table);  // with function get_text finding a words with property number of syllabes
	Dictionary dictionary;
	SentencePattern pattern;


private:

	
};


#endif