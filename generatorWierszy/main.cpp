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

	//initialization of needed things
	SentencePattern pattern; //patterns
	Dictionary dict; //dictionary
	sf::RenderWindow window(sf::VideoMode(500, 550), "Generator",sf::Style::None); //create a sfml renderwindow


	sf::String Text;
	sf::String Title;
	sf::RectangleShape rectangle(sf::Vector2f(250, 75));
	rectangle.setFillColor(sf::Color(100, 100, 100));
	rectangle.move(sf::Vector2f(10, 10));
	string input_text;
	//the following part of code is based on sfml tutorial foun on sfml site, its common way to handle the window
	
	while (window.isOpen()){
		sf::Event event;
		sf::Font font;	//instance of font class
		if (!font.loadFromFile("Pollito Peligroso.ttf")){} //loading font from file
		sf::Text text(input_text, font, 50);	//instance of text class
		text.move(sf::Vector2f(5, 5));
		text.setColor(sf::Color::White); //color
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
			case sf::Event::TextEntered:
				if (event.text.unicode == '\b' && input_text.size()){
					input_text.pop_back();
					std::cout << input_text << std::endl;
				} else if (event.text.unicode < 128){
					input_text += static_cast<char>(event.text.unicode);
					std::cout << input_text << std::endl;
				}

			}
		}

		window.clear();
		window.draw(rectangle);
		window.draw(text);
		window.display();
	}
	//here go every de-initialization methods we need / also saving them to file and stuff
	return 0;
}
#endif
