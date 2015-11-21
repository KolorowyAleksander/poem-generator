#ifndef _HAIKU
#define _HAIKU
#include "Poem.h"
#include "SentencePattern.h"
#include "stdlib.h"
#include "time.h"

class Haiku : public  Poem {
public:
	Haiku(SentencePattern &pattern,Dictionary &dictionary);
	~Haiku();
    char** choose_patterns(); // generates random patterns
	char** choose_words(char** patterns_table); // choose property verse : 5,7,5 syllabes per line
private:
	
};

#endif