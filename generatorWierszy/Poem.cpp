#include "Poem.h"


Poem::Poem(int lines_number, bool rhymed, SentencePattern &pattern, Dictionary &dictionary)
{
	this->lines_number = lines_number;
	this->pattern = pattern;
	this->dictionary = dictionary;
	this->rhymed = rhymed;
	this->syll_per_verse = 8;
	this->patterns_table = new char*[lines_number];
}
Poem::Poem()
{
}

Poem::~Poem()
{
}


void Poem::make_poem(){
	patterns_table = this->choose_patterns();
	this->choose_words();
}

void Poem::print_poem(){
	cout << this->poem << endl;
}

char** Poem::choose_patterns(){
	char ** patterns_table = new char*[lines_number];
	for (int i = 0; i < lines_number; i++){
		patterns_table[i] = pattern.get_pattern();
	}
	return patterns_table;
}

string Poem::last_syllable_of_verse(string verse){
	
	string last_word = verse.substr(verse.find_last_of(" ") + 1);
	string last_word2 = last_word.substr(0, last_word.length() - 1);
	Word word(last_word2);
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

int * Poem::div_syllables(int num_words,int stat_num_syllables){
	//division of syllables per words
	int temp;
	int syllab_to_div = this->syll_per_verse - num_words - stat_num_syllables;
	if (syllab_to_div < 0){
		return NULL;
	}
	int *tab = new int[num_words];
	for (int i = 0; i < num_words; i++){
		tab[i] = 1;
	}
	int impossible = 0;
	while (syllab_to_div>0){
		temp = rand() %num_words;
		if (tab[temp] < 5){
			tab[temp] = tab[temp] + 1;
			syllab_to_div--;
		}
		if (impossible == 100){
			return NULL;
		}
		impossible++;
	}


	return tab;
}
string Poem::get_text(char*verse){

	// assigns to each word the number of syllables
	int num_words = count_words(verse);
	int stat_syll = stat_num_syllables(verse);
	int *tab = div_syllables(num_words, stat_syll); 
	if (tab == NULL){
		return "";
	}

	//transformate patterns into text
	int n  = 0;
	int num_syll = 0;
	string string_verse;
	Word *word;
	int type_word;
	char next_char = verse[n];
	while (next_char != '#'){


		if (next_char <'9' && next_char>'0'){ //need to change into word
			type_word = next_char - '0';

			if (verse[n + 2] == '#'&&this->rhymed && this->rhyme_syllable != ""){ // if it's the last word and we need to find rhyme
					word = dictionary.get_word(type_word, tab[num_syll], this->rhyme_syllable);
					num_syll++;
					if (!word){
						return "";
					}
				}
				
			
			else{ //if it's not the last word or it's not rhyme

					word = dictionary.get_word(type_word, tab[num_syll]);
					num_syll++;
					if (!word){
						return "";
					}
			}


			string_verse = string_verse + word->word; // add text to final content of verse
		}



		else{ // next_char is a punctuation mark,articel or space
			string_verse = string_verse + verse[n];
		}


		n++;
		next_char = verse[n]; // go to next char

	}
	 
	return string_verse;
	 
}



string  Poem::choose_words(){
	//initial 
	this->rhyme_syllable = "";
	string final_poem = "";
	string *poem = new string[lines_number];

	for (int i = 0; i < lines_number; i++){
		if (rhymed && i>0 && i%2==1){ // if it's rhymed poem and it's not first line
				rhyme_syllable = last_syllable_of_verse(poem[i - 1]);// find syllable that will rhyme with the next verse
			}
		poem[i] = get_text(patterns_table[i]);
		while (poem[i] == ""){ //get new pattern until find sth with appropriate number of words
			patterns_table[i] = pattern.get_pattern();
			poem[i] = get_text(patterns_table[i]);
		}
		final_poem = final_poem + poem[i] + '\n';
	}
	this->poem = final_poem;
	this->rhyme_syllable = "";
	return final_poem;
}

void Poem::save_poem(){
	ofstream NewPoem;
	NewPoem.open("poem.txt");
	NewPoem << this->poem << endl;
	NewPoem.close();
}