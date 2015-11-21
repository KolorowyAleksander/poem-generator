#include "Poem.h"


Poem::Poem(int lines_number, bool rhymed, SentencePattern &pattern, Dictionary &dictionary)
{
	this->lines_number = lines_number;
	this->pattern = pattern;
	this->dictionary = dictionary;
	this->rhymed = rhymed;
}
Poem::Poem()
{
}

Poem::~Poem()
{
}


string* Poem::make_poem(){
	char ** patterns_table = this->choose_patterns();
	//char** char_poem = this->choose_words(patterns_table);
	return NULL;
}


char** Poem::choose_patterns(){
	char ** patterns_table = new char*[lines_number];
	for (int i = 0; i < lines_number; i++){
		patterns_table[i] = pattern.get_pattern();
	}
	return patterns_table;
}

char* Poem::last_word_of_verse(char* verse){
	//int i = sizeof(verse) / sizeof(char);
	int i = strlen(verse) -1;
	int start;
	int end;
	int j =0;
	while (verse[i] > 'z' || verse[i] < 'a'){
		i--;
	}
	end = i;
	while (verse[i] != ' ' || i<0){
		i--;
	}
	start = i+1;
	char * last_word = new char[start-end+1];
	for (i = start; i <= end; i++){
		last_word[j] = verse[i];
		j++;
	}

	return last_word;
}

char * Poem::get_text(char* verse){
	int i = 0;
	char next_char = verse[i];
	int already_syllabes = 0;
	Word *word;
	string string_verse = "";
	char *char_verse;
	int type_word;
	while (next_char != '#'){
		if (next_char <= 57 && next_char>48){ // transformate to word
			if (this->rhym_word){
				if ((((verse[i + 1] > 57 || verse[i + 1] < 48) && (verse[i + 2] = '#')) || (verse[i + 1] = '#')) && this->rhymed) { // jezeli to ostatnie s³owo i wiersz jest rymowany
					type_word = next_char - '0';
					word = dictionary.get_word(type_word); //znajdz slowo rymowane z rhym_word;
					//already_syllabes = +word->syllables;
					//string_verse = string_verse + word->word;
				}
			}

			else
			{
				type_word = next_char - '0';
				word = dictionary.get_word(type_word);
				//already_syllabes = +word->syllables;
				//string_verse = string_verse + word->word;
			}

		}
		else{ //rewrite to output table
		//	string_verse = string_verse + verse[i];
		}
		i++;
		next_char = verse[i];
	}
	already_syllabes = +verse[++i];
	if (already_syllabes != this->syll_per_verse){
		return NULL;
	}
	else

		char_verse = new char[string_verse.length() + 1];
	strcpy_s(char_verse, string_verse.length() + 1, string_verse.c_str());
	return char_verse;
}

char** Poem::choose_words(char **patterns_table){
	char **poem = new char*[lines_number];
	this->rhym_word = NULL;
	for (int i = 0; i < lines_number; i++){
		if (this->rhymed && i>0){
			this->rhym_word = last_word_of_verse(poem[i - 1]);// znajdz slowo rymowane ze slowem rhym_word
		}
		poem[i] = get_text(patterns_table[i]);
		while (!poem[i]){//choosing words until get right size of verse
			poem[i] = get_text(patterns_table[i]);
		}
		this->rhym_word = NULL;
	}

	return poem;
}

