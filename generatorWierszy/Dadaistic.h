#ifndef _DADAISTIC
#define _DADAISTIC
#include "Poem.h"


class Dadaistic : public  Poem {
public:
	Dadaistic(Dictionary &dictionary);
	~Dadaistic();
protected:
	char** choose_patterns(); // generates random patterns without any grammar
	string Dadaistic::choose_words();
private:
	char* get_pattern();

};

#endif