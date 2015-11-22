#pragma once
namespace Word_type{

	enum word_type{
		Concrete_Noun = 1,
		Abstract_Noun = 2,
		Transitive_Verb = 3,
		Intransitive_Verb = 4,
		Adjectives = 5,
		Adverb = 6
	}; // enum for word types for simplicity and laziness

	inline const char* intToString(int a){
		switch (a){
		case 1:		return "Concrete Noun";
		case 2:		return "Abstract Noun";
		case 3:		return "Transitive Verb";
		case 4:		return "Intransitive Verb";
		case 5:		return "Adjectives";
		case 6:		return "Adverb";
		default:	return "Oh noes! Something went horriberly wrong!";
		} // converting to string for proper file management
	}

	inline int strToInt(std::string a){
		if (a == "Concrete Noun"){
			return 1;
		}
		if (a == "Abstract Noun"){
			return 2;
		}
		if (a == "Transitive Verb"){
			return 3;
		}
		if (a == "Intransitive Verb"){
			return 4;
		}
		if (a == "Adjectives"){
			return 5;
		}
		if (a == "Adverb"){
			return 6;
		}
		return 0;
	}
}
