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
	unsigned int width = 1000; // width of the window

	/*initializing patterns and dictionary*/
	SentencePattern pattern; // class for managing sentence patterns
	Dictionary dict; //class for mamgings words
	sf::Font font;	//instance of font class
	if (!font.loadFromFile("NotoSans-Bold.ttf")){} //loading font from file
	sf::RenderWindow window(sf::VideoMode(width, height), "Generator", sf::Style::None); //create a sfml renderwindow

	vector<sf::Vector2f> rectangle_position{ sf::Vector2f(15, 15), sf::Vector2f(15, 80), sf::Vector2f(15, 145),
		sf::Vector2f(15, 210), sf::Vector2f(15, 275) };/*a vector of rectangle positions inside window*/
	vector <sf::RectangleShape> wektor_kwadratow; //vector of rectangles for buttons
	vector<sf::Vector2f> text_position{ sf::Vector2f(75, 25), sf::Vector2f(75, 90), sf::Vector2f(53, 154), sf::Vector2f(65, 218) };
	vector<sf::Text> texts; //texts

	for (auto i = rectangle_position.begin(); i != rectangle_position.end();i++){
		sf::RectangleShape rectangle(sf::Vector2f(200,50));
		rectangle.setPosition(*i);
		rectangle.setFillColor(sf::Color(175, 180, 43, 255));
		wektor_kwadratow.emplace_back(rectangle);
	} //initializing a vector of rectangles for buttons
	
	vector<string> names{ "Haiku", "Sonet", "Dadaistic", "Custom" };
	{
		int a = 0;
		for (auto i = text_position.begin(); i != text_position.end(); i++){
			sf::Text textss(names[a], font, 25);
			textss.setColor(sf::Color(130, 119, 23, 255));
			textss.setPosition(*i);
			texts.push_back(textss);
			a++;
		}
	}
	//loading icons
	sf::Texture texture;
	sf::Sprite edit;
	if (texture.loadFromFile("wszystko.png")) {
		edit.setTexture(texture);
		edit.setPosition(sf::Vector2f(15, 340));
	}


	//variables for the programm to work
	string input_text;
	string output_text = "welcome, welcome";
	int syllables = 1;
	int verses = 1;
	bool rhymed = false;
	string rhymed_text;
	while (window.isOpen()){
		sf::Event event;
		if (rhymed) rhymed_text = "rhymed: yes"; 
		else rhymed_text = "rhymed: not";
		sf::Text text(input_text, font, 20);	//thats for input text
		text.setColor(sf::Color(130, 119, 23, 255)); //color
		text.setPosition(225, 415);
		
		sf::Text syll_output(to_string(syllables), font, 25); //thats for syllables number
		syll_output.setColor(sf::Color(130, 119, 23, 255));
		syll_output.setPosition(182, 350);

		sf::Text verses_output(to_string(verses), font, 25); //for output number
		verses_output.setColor(sf::Color(130, 119, 23, 255));
		verses_output.setPosition(83, 350);

		sf::Text if_rhymed(rhymed_text, font, 25); //thats if text is rhymed or not
		if_rhymed.setColor(sf::Color(130, 119, 23, 255));
		if_rhymed.setPosition(38, 283);

		sf::Text onscreen_text(output_text, font, 20); //finally the output text
		onscreen_text.setColor(sf::Color(130, 119, 23, 255));
		onscreen_text.setPosition(223, 25);

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
						output_text = haiku.get_text();
					}
					if (position.x >= 15 && position.x <= 215 && position.y >= 80 && position.y <= 130) {
						cout << "Sonet\n";
						Sonet sonet(pattern, dict);
						sonet.make_poem();
						output_text = sonet.get_text();
					}

					if (position.x >= 15 && position.x <= 215 && position.y >= 145 && position.y <= 195){
						cout << "Dadaistic\n";
						Dadaistic dadaistic(pattern, dict);
						dadaistic.make_poem();
						output_text = dadaistic.get_text();
					}
					if (position.x >= 15 && position.x <= 215 && position.y >= 210 && position.y <= 260){
						cout << "Custom\n";
						Custom custom(verses, rhymed, syllables, pattern, dict);
						custom.make_poem();
						output_text = custom.get_text();
					}
					if (position.x >= 15 && position.x <= 215 && position.y >= 275 && position.y <= 325){
						if (rhymed)
							rhymed = false;
						else
							rhymed = true;
					}
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
		for (auto i = texts.begin(); i != texts.end(); i++){
			sf::Text textsss = *i;
			window.draw(textsss);
		}
		window.draw(edit);
		window.draw(verses_output);
		window.draw(syll_output);
		window.draw(if_rhymed);
		window.draw(text);
		window.draw(onscreen_text);
		window.display();
	}
	//here go every de-initialization methods we need / also saving them to file and stuff
	return 0;
}
#endif
