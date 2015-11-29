#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Dictionary.h"
#include "SentencePattern.h"
#include "Word.h"
#include "Poem.h"
#include "Custom.h"
#include "Sonet.h"
#include "Haiku.h"
#include "Dadaistic.h"
#include "word_type.h"
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS

int main(){

	srand(time(nullptr)); //for random number generators
	unsigned int height = 475; //height of the window
	unsigned int width = 800; // width of the window

	/*initializing patterns and dictionary*/
	SentencePattern pattern; // class for managing sentence patterns
	Dictionary dict; //class for mamgings words
	sf::Font font;	//instance of font class
	if (!font.loadFromFile("NotoSans-Bold.ttf")){} //loading font from file
	sf::RenderWindow window(sf::VideoMode(width, height), "Generator", sf::Style::None); //create a sfml renderwindow

	vector<sf::Vector2f> rectangle_position{ sf::Vector2f(15, 15), sf::Vector2f(15, 80), sf::Vector2f(15, 145),
		sf::Vector2f(15, 210), sf::Vector2f(15, 275) };/*a vector of rectangle positions inside window*/
	vector <sf::RectangleShape> wektor_kwadratow; //vector of rectangles for buttons
	vector<sf::Vector2f> text_position{/*texts position*/};
	vector<sf::Text> texts; //texts

	for (auto i = rectangle_position.begin(); i != rectangle_position.end();i++){
		sf::RectangleShape rectangle(sf::Vector2f(200,50));
		rectangle.setPosition(*i);
		rectangle.setFillColor(sf::Color(175, 180, 43, 255));
		wektor_kwadratow.emplace_back(rectangle);
	} //initializing a vector of rectangles for buttons
	
	
	//loading icons
	sf::Texture texture;
	sf::Sprite edit;
	if (texture.loadFromFile("wszystko.png")) {
		edit.setTexture(texture);
		edit.setPosition(sf::Vector2f(15, 340));
	}



	string input_text;

	while (window.isOpen()){
		sf::Event event;

		sf::Text text(input_text, font, 20);	//instance of text class
		text.setColor(sf::Color(220, 231, 117, 255)); //color
		text.setPosition(220, 405);
		
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
			case sf::Event::MouseButtonPressed:
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					sf::Vector2i position = sf::Mouse::getPosition(window);
					if ( position.x >= 15 &&position.x <= 215 && position.y >=15 && position.y <= 65)
						cout << "Haiku";
					if (position.x >= 15 && position.x <= 215 && position.y >= 80 && position.y <= 130)
						cout << "Sonet";
					if (position.x >= 15 && position.x <= 215 && position.y >= 145 && position.y <= 195)
						cout << "Dadaistic";
					if (position.x >= 15 && position.x <= 215 && position.y >= 210 && position.y <= 260)
						cout << "Custom";
					if (position.x >= 15 && position.x <= 215 && position.y >= 275 && position.y <= 325)
						cout << "Rhymed";
					if (position.x >= 15 && position.x <= 65 && position.y >= 340 && position.y <= 364)
						cout << "Verses plus";
					if (position.x >= 15 && position.x <= 65 && position.y >= 365 && position.y <= 390)
						cout << "Verses minus";
					if (position.x >= 115 && position.x <= 165 && position.y >= 340 && position.y <= 364)
						cout << "Syllabs plus";
					if (position.x >= 115 && position.x <= 165 && position.y >= 365 && position.y <= 390)
						cout << "Syllabs minus";
					if (position.x >= 15 && position.x <= 65 && position.y >= 405 && position.y <= 455){ //editing words
						cout << "Edit";
						dict.save_to_file();
						system("notepad.exe dictionary.txt");
						dict.read_from_file();
					}
					if (position.x >= 90 && position.x <= 140 && position.y >= 405 && position.y <= 455){ //editing patterns
						pattern.save_patterns();
						system("notepad.exe patterns_file.txt");
						pattern.read_patterns();
					}
					if (position.x >= 165 && position.x <= 215 && position.y >= 405 && position.y <= 455){ //add word to input
						cout << input_text;
					}
				}
			}
		}

		window.clear(sf::Color(205, 220, 57,255));
		for (auto i = wektor_kwadratow.begin(); i != wektor_kwadratow.end(); i++){
			sf::RectangleShape rectangle = *i;
			window.draw(rectangle);
		}
		window.draw(edit);
		window.draw(text);
		window.display();
	}
	//here go every de-initialization methods we need / also saving them to file and stuff
	return 0;
}
#endif
