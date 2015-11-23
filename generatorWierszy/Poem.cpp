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


void Poem::make_poem(){
	char ** patterns_table = this->choose_patterns();
	this->choose_words(patterns_table);
	
}

void Poem::print_poem(){
	cout << this->poem << endl;
}

char** Poem::choose_patterns(){
	char ** patterns_table = new char*[lines_number];
	srand(time(NULL));
	for (int i = 0; i < lines_number; i++){
		patterns_table[i] = pattern.get_pattern();
	}
	return patterns_table;
}

string Poem::last_syllable_of_verse(string verse){
	/*int i = strlen(verse) -1;
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
	start = i+1;*/
	string last_word = verse.substr(verse.find_last_of(" ") + 1,verse.find_last_of("#")-1);
	/*for (i = start; i <= end; i++){
		last_word = last_word + verse[i];
	}*/
	Word word(last_word);
	return word.last_syllable;
}

int Poem::stat_num_syllables(char*verse){
	int i = 0;
	while (verse[i] != '#'){
		i++;
	}
	i++;
	return verse[i]-'0';
}

string Poem::get_text(char*verse){
	int num_words = this->count_words(verse);
	int medium;
	int last;
	int i = 0;
	string string_verse;
	Word *word;
	int type_word;
	int syllab_to_div = this->syll_per_verse - stat_num_syllables(verse);
	if (syllab_to_div % num_words == 0){ // jezeli rowno sie dziel¹
		medium = syllab_to_div / num_words;
		last = medium;
	}
	else{
		medium = syllab_to_div / (num_words - 1);
		last = syllab_to_div - medium*(num_words - 1);
	}
	char next_char = verse[i];
	while (next_char != '#'){
		if (next_char <'9' && next_char>'0'){ //change to word
			type_word = next_char - '0';
			if (verse[i + 2] == '#'){ //jezeli to ostatnie slowo
				if (this->rhymed && this->rhyme_syllable != ""){
					word = dictionary.get_word(type_word, last, this->rhyme_syllable);
					if (!word){
						return "";
					}
				}
				else{
					word = dictionary.get_word(type_word, last);
					if (!word){
						return "";
					}
				}
			}
			else{
				if (this->rhymed && this->rhyme_syllable != ""){
					word = dictionary.get_word(type_word, medium, this->rhyme_syllable);
					if (!word){
						return "";
					}
				}
				word = dictionary.get_word(type_word, medium);
				if (!word){
					return "";
				}
			}
			string_verse = string_verse + word->word;
		}
		else{
			string_verse = string_verse + verse[i];
		}
		i++;
		next_char = verse[i];

	}
	 
	return string_verse;
	 
}


char** Poem::choose_words_old(char **patterns_table){
	//char **poem = new char*[lines_number];
	//this->rhyme_syllable = "";
	//for (int i = 0; i < lines_number; i++){
	//	if (this->rhymed && i>0){ // if it's rhymed poem and it's not first line
	//		this->rhyme_syllable = last_syllable_of_verse(poem[i - 1]);// find syllable that will rhyme with the next verse
	//	}
	//	poem[i] = get_text(patterns_table[i]);
	//	while (!poem[i]){//choosing words until get right size of verse
	//		poem[i] = get_text(patterns_table[i]);
	//	}
	//	cout << poem[i];
	//	this->rhyme_syllable = "";
	//}

	//return poem;
	return NULL;
}
string  Poem::choose_words(char **patterns_table){
	this->rhyme_syllable = "";
	string final_poem = "";
	string *poem = new string[lines_number];
	for (int i = 0; i < lines_number; i++){
		if (rhymed && i>0){ // if it's rhymed poem and it's not first line
				rhyme_syllable = last_syllable_of_verse(poem[i - 1]);// find syllable that will rhyme with the next verse
			}
		poem[i] = get_text(patterns_table[i]);
		while (poem[i] == ""){
			poem[i] = get_text(patterns_table[i]);
		}
		cout << poem[i] << endl;
		final_poem = final_poem + poem[i] + '\n';
	}

	return final_poem;
}

int Poem::count_words(char*verse){
	int i = 0;
	int how_many = 0;
	char next_char = verse[i];
	while (next_char != '#'){
		if (next_char <'9' && next_char >'0'){
			how_many++;
		}
		i++;
		next_char = verse[i];
	}
	return how_many;
}