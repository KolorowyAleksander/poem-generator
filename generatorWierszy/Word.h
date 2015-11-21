#pragma once
#include <string>
#include "Hyphenator.h"
using namespace Hyphenate;

class Word{
public:
	friend class Poem;
	std::string word; //text of the word
	int type; // throws errors on other than 1 -6
	void test() const;
	Word(std::string word); // create empty word for comparison
	Word(std::string word, int type);
	bool operator==(const Word &a) const;
private:
	std::string last_syllable; //last syllable for rhyming
	int syllables; // number of syllables in the word
	static Hyphenator hyph;
};

