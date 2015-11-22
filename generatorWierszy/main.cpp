#include <SFML/Graphics.hpp>
#include <iostream>
#include "Dictionary.h"
#include "SentencePattern.h"
#include "Poem.h"
#include "Custom.h"
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
	//dict.get_word(1);
	Custom cust(5, 0, 6, pattern, dict);
	cust.make_poem();
	cout << cust.poem;

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
