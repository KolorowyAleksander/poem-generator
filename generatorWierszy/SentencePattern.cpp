#include "SentencePattern.h"


SentencePattern::SentencePattern(){
	SentencePattern::read_patterns();
}
SentencePattern:: ~SentencePattern(){
	save_patterns();
}



bool SentencePattern::read_patterns(){
	patterns_list.clear();
	string pattern;
	fstream fd;
	fd.open(filename, ios::in);
	while (getline(fd, pattern)){
		SentencePattern::add(pattern);
	}
	fd.close();
	return 0;
}
bool SentencePattern::save_patterns(){
	fstream fd(filename);
	fd.open(filename, ios::out);
	fd.clear();
	for (list<string>::iterator iter = patterns_list.begin(); iter != patterns_list.end(); iter++){
		fd << *iter << endl;
	}
	fd.close();
	patterns_list.clear();
	return 0;
}
bool SentencePattern::add(string pattern){
	patterns_list.push_back(pattern);
	return 0;
}
bool SentencePattern::change(string new_pattern, string old_pattern){
	patterns_list.remove(old_pattern);
	patterns_list.push_back(new_pattern);
	return 0;
}
bool SentencePattern::remove(string pattern){
	patterns_list.remove(pattern);
	return 0;
}

char* SentencePattern::get_pattern(){
	int size = patterns_list.size();
	list<string>::iterator iter;

	iter = patterns_list.begin();
	int n = rand() % size-1;
	while (n > 0){
			n--;
			iter++;
	}
	char * pattern = new char[(*iter).length() + 1];
	strcpy_s(pattern,(*iter).length()+1, (*iter).c_str());
	//cout << pattern << endl;
return pattern;
}
	