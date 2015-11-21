#ifndef _DADAISTIC
#define _DADAISTIC
#include "Poem.h"
#include "stdlib.h"
#include "time.h"

class Dadaistic : public  Poem {
public:
	Dadaistic(SentencePattern &pattern, Dictionary &dictionary);
	~Dadaistic();
	char** choose_patterns() override; // generates random patterns
private:

};

#endif