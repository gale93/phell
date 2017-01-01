#pragma once

#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Image.hpp>
#include <SFML\Graphics\Sprite.hpp>


namespace sf {
	class RenderWindow;
}

class Background
{
	sf::Sprite sprite;
	sf::Image image;
	sf::Texture texture;

	unsigned short width, height;
	bool isOutBound(short x, short y) const;

	void test_loadmap();

public:
	Background();
	~Background();

	void reset();
	void setPixel(unsigned short x, unsigned short y, const sf::Color& color);
	sf::Color getPixel(unsigned short x, unsigned short y) const;
	sf::Color getPixel(const sf::Vector2f& pos) const;

	void draw(sf::RenderWindow *window);
};

