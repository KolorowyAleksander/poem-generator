#include "Poem.h"


Poem::Poem(int lines_number, bool rhymed, SentencePattern &pattern, Dictionary &dictionary) :
dictionary(dictionary), pattern(pattern), lines_number(lines_number), rhymed(rhymed)
{
	patterns_table = new char*[lines_number];
}


Poem::~Poem(){
	delete[] patterns_table;
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
string Poem::get_text(char*verse){

	int num_words = this->count_words(verse); // number of words to transform in verse
	
	//division of syllables per words
	int temp;
	int syllab_to_div = this->syll_per_verse - stat_num_syllables(verse) - num_words;
	int *tab = new int[num_words];
	for (int i = 0; i < num_words; i++){
		tab[i] = 1;
	}
	int n = 0;
	while (syllab_to_div){
		if (n >= num_words){
			n = 0;
		}
		if (syllab_to_div < 5){
			temp= rand() % syllab_to_div + 1 ; // jezeli syllab_t_dic jest jeden to temp zawsze bedzie rowne 1
			if (tab[n] + temp < 5){
				tab[n] =tab[n] +temp;
				syllab_to_div =syllab_to_div -temp;
			}
			
		}
		else {
			temp = rand() % 5;
			if (tab[n] + temp < 5){
				tab[n] = tab[n] + temp;
				syllab_to_div = syllab_to_div - temp;
			}
		}
		
		n++;
	}
	
	//int medium;
	//int last;
	//if (syllab_to_div % num_words == 0){ // 
	//	medium = syllab_to_div / num_words;
	//	last = medium;
	//}
	//else{
	//	medium = syllab_to_div / (num_words - 1);
	//	last = syllab_to_div - medium*(num_words - 1);
	//}
	//if (last < 1 || last>4 || medium < 1 || medium>4){
	//	return "";
	//}

	//transformate patterns into text
	n  = 0;
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
		if (rhymed && i>0){ // if it's rhymed poem and it's not first line
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

