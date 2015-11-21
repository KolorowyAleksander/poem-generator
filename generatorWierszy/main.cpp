#include <SFML/Graphics.hpp>
#include <iostream>
#include "Dictionary.h"
#include "SentencePattern.h"
#include "Poem.h"
#include "Sonet.h"
#include "Haiku.h"
#include "Word.h"
#include "word_type.h"
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS


int main(){
	
	//testy testy
	SentencePattern pattern;
	Dictionary dict;
	dict.add("Enlightment", Word_type::Concrete_Noun);
	dict.add("Cowboy", Word_type::Concrete_Noun);
	dict.add("Frogification", Word_type::Adverb);
	dict.add("Lele", Word_type::Concrete_Noun);
	dict.add("Bazinga", Word_type::Intransitive_Verb);
	dict.add("Intensify", Word_type::Transitive_Verb);
	Poem poem(6,1,pattern,dict);
	//poem.make_poem();

	sf::RenderWindow window(sf::VideoMode(500, 500), "Generator",sf::Style::None); //create a sfml renderwindow
	while (window.isOpen()){
		sf::Event event;
		sf::Font font;	//instance of font class
		if (!font.loadFromFile("Paper Banner-Regular.ttf")){} //loading font from file
		sf::Text text("Hello world", font, 36);	//instance of text class
		text.setColor(sf::Color::Red); //color
		while (window.pollEvent(event)){
			// ReSharper disable once CppIncompleteSwitchStatement
			switch (event.type){
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					window.close();
				break;
			}
		}

		window.clear();
		window.draw(text);
		window.display();
	}
	//here go every de-initialization methods we need / also saving them to file and stuff
	return 0;
}
#endif
