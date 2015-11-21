#ifndef _SONET
#define _SONET
#include "Poem.h"
#include "SentencePattern.h"
#include "stdlib.h"
#include "time.h"

class Sonet : public  Poem {
public:
	Sonet(SentencePattern &pattern,Dictionary &dictionary);
	~Sonet();

private:
	char** choose_words(char** patterns_table); // choose prperty rhyme in verse
};

#endif