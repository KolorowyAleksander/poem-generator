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
	char** choose_patterns() override; // generates random patterns

private:
};

#endif