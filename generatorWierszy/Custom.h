#ifndef _CUSTOM
#define _CUSTOM
#include "Poem.h"
#include "SentencePattern.h"
#include "stdlib.h"
#include "time.h"

class Custom : public  Poem {
public:
	Custom(int lines_number,bool rhymed,SentencePattern &pattern, Dictionary &dictionary);
	~Custom();
	char** choose_patterns() override; // generates random patterns

private:

};

#endif