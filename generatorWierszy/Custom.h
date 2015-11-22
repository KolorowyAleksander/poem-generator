#ifndef _CUSTOM
#define _CUSTOM
#include "Poem.h"
class Custom : public  Poem {
public:
	Custom(int lines_number,bool rhymed,int syll_per_verse, SentencePattern &pattern, Dictionary &dictionary);
	~Custom();

private:

};

#endif