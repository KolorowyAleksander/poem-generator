#ifndef _HAIKU
#define _HAIKU
#include "Poem.h"
#include "SentencePattern.h"
#include "stdlib.h"
#include "time.h"

class Haiku : public  Poem {
public:
	Haiku(Dictionary &dictionary);
	~Haiku();
   
protected:
	

private:
	char** choose_patterns(); // generates random patterns without any grammar
	string choose_words(); // choose property verse : 5,7,5 syllables per line
};

#endif