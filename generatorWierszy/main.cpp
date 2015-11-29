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
	string output_text;
	int syllables = 1;
	int verses = 1;
	bool rhymed = false;
	while (window.isOpen()){
		sf::Event event;

		sf::Text text(input_text, font, 20);	//thats for input text
		text.setColor(sf::Color(130, 119, 23, 255)); //color
		text.setPosition(225, 415);
		
		sf::Text syll_output(to_string(syllables), font, 25); //thats for syllables number
		syll_output.setColor(sf::Color(130, 119, 23, 255));
		syll_output.setPosition(182, 350);

		sf::Text verses_output(to_string(verses), font, 25);
		verses_output.setColor(sf::Color(130, 119, 23, 255));
		verses_output.setPosition(83, 350);
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
					if (position.x >= 15 && position.x <= 215 && position.y >= 15 && position.y <= 65){
						cout << "Haiku\n";
						Haiku haiku(pattern,dict);
						haiku.make_poem();
						haiku.print_poem();
					}
					if (position.x >= 15 && position.x <= 215 && position.y >= 80 && position.y <= 130) {
						cout << "Sonet\n";
						Sonet sonet(pattern, dict);
						sonet.make_poem();
						sonet.print_poem();
					}

					if (position.x >= 15 && position.x <= 215 && position.y >= 145 && position.y <= 195){
						cout << "Dadaistic\n";
						Dadaistic dadaistic(pattern, dict);
						dadaistic.make_poem();
						dadaistic.print_poem();
					}
					if (position.x >= 15 && position.x <= 215 && position.y >= 210 && position.y <= 260){
						cout << "Custom\n";
						Custom custom(verses, rhymed, syllables, pattern, dict);
						custom.make_poem();
						custom.print_poem();
					}
					if (position.x >= 15 && position.x <= 215 && position.y >= 275 && position.y <= 325)
						cout << "Rhymed";
					if (position.x >= 15 && position.x <= 65 && position.y >= 340 && position.y <= 364){
						if (verses >= 1 && verses < 9)
							verses++;
					}
					if (position.x >= 15 && position.x <= 65 && position.y >= 365 && position.y <= 390){
						if (verses >1 && verses <= 9)
							verses--;
					}
					if (position.x >= 115 && position.x <= 165 && position.y >= 340 && position.y <= 364){
						if (syllables >= 1 && syllables < 9)
							syllables++;
					}
					if (position.x >= 115 && position.x <= 165 && position.y >= 365 && position.y <= 390){
						if (syllables > 1 && syllables <= 9)
							syllables--;
					}
					if (position.x >= 15 && position.x <= 65 && position.y >= 405 && position.y <= 455){ //editing words
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
						if (input_text.empty()){
							size_t found = input_text.find_first_of(" ");
							if (Word_type::strToInt(input_text.substr(found + 1)) != 0)
								dict.add(input_text.substr(0, found), Word_type::strToInt(input_text.substr(found + 1)));
							dict.save_to_file();
							dict.read_from_file();
						}
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
		window.draw(verses_output);
		window.draw(syll_output);
		window.draw(text);
		window.display();
	}
	//here go every de-initialization methods we need / also saving them to file and stuff
	return 0;
}
#endif
