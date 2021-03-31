#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<array> // std::array
#include<chrono> // std::chrono
#include<algorithm> // std::shuffle
#include<random> // std::default random engine


// Height and width of window 
const int WIDTH = 500;
const int HEIGHT = 500;

// Variables to hold the numbers and the rectangles 
std::array<int, WIDTH> numbers;
std::array<sf::RectangleShape, WIDTH> rects;

// Defines the window 
sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Quick sort", sf::Style::Titlebar | sf::Style::Close);


// Variable to store window events 
sf::Event event;

// Function that adds the numbers 1 - WIDTH to the array, and then shuffles them 
void initNumbers() {

	// Adds the numbers 1 - width to the numbers array
	for (int i = 0; i < WIDTH; i++) {
		numbers[i] = i + 1;
	}

	// Seed for default_random_engine function
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	// Shuffling the numbers so that the algorithm can sort them
	std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(seed));
}

// Initializes the rectangles 
// Adds a height based on the corresponding value in the numbers array
void initRects() {
	for (int i = 0; i < WIDTH; i++) {
		float y = HEIGHT - numbers[i];
		float x = i;
		float height = numbers[i];
		float width = 1;
		rects[i].setPosition(x, y);
		rects[i].setSize(sf::Vector2f(width, height));
		rects[i].setFillColor(sf::Color::White);
	}
}


// Updats the rectangles based on the current state of the numbers array
void updateRects() {
	for (int j = 0; j < WIDTH; j++) {
		float y = HEIGHT - numbers[j];
		float x = j;
		float height = numbers[j];
		rects[j].setPosition(x, y);
		rects[j].setSize(sf::Vector2f(1.f, height));
		rects[j].setFillColor(sf::Color::White);
	}
} 

// Function that swaps two variables
void swap(int* item1, int* item2) {
	int temp = *item1;
	*item1 = *item2;
	*item2 = temp;
}



int main() {

	// Calls functions to initialize the rects and numbers arrays 
	initNumbers();
	initRects();

	// Sets the maximum framerate of the window 
	window.setFramerateLimit(30);

	// Variables that are used in the algorithm
	int currentElement, predecessor;
	int i = 1;

	// Game Loop
	while (window.isOpen()) {
		// Event polling 
		while (window.pollEvent(event)) {
			switch (event.type) {

				// If the 'x' button is pushed, close the window 
			case sf::Event::Closed():
				window.close();
			}
		}

		// Algorithm 
		if(i < WIDTH)
		{
			// Sets the current element and its predecessor
			currentElement = numbers[i];
			predecessor = i - 1;

			// Moves all elements (numbers[ < i - 1]) that are bigger than key, up one position to make space for the swapped element
			while (predecessor >= 0 && numbers[predecessor] > currentElement)
			{
				numbers[predecessor + 1] = numbers[predecessor];
				predecessor = predecessor - 1;
			}
			numbers[predecessor + 1] = currentElement;
			i++;
		}

		// Clears the window, so that the new frame doesnt just sit on top of the old one
		window.clear(sf::Color::Black);

		updateRects();
		
		// Loops through the list of rectangles and draws them all
		for(sf::RectangleShape rect : rects) {
			window.draw(rect);
		}

		window.display();

	}

	return 0;
}