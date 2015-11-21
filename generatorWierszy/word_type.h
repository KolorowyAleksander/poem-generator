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
	/*
	inline int StrToEnum(const char *a){
		switch (a){
		case "Concrete Noun":		return Concrete_Noun;
		case "Abstract Noun":		return Abstract_Noun;
		case "Transitive Verb":		return Transitive_Verb;
		case "Intransitive Verb":	return Intransitive_Verb;
		case "Adjectives":			return Adjectives;
		case "Adverb":				return Adverb;
		default:					return;
		}
	} //converting back to int
	
	inline const char* ToString(word_type a){
		switch (a){
		case Concrete_Noun:		return "Concrete Noun";
		case Abstract_Noun:		return "Abstract Noun";
		case Transitive_Verb:	return "Transitive Verb";
		case Intransitive_Verb: return "Intransitive Verb";
		case Adjectives:		return "Adjectives";
		case Adverb:			return "Adverb";
		default:				return "Oh noes! Something went horriberly wrong!";
		} // converting to string for proper file management
	}
	*/
}