#include "background.hpp"

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\RenderTexture.hpp>


#include "particle.hpp"

Background::Background() : width(800), height(600)
{
	test_loadmap();

	texture.loadFromImage(image);
	sprite.setTexture(texture);
}

#include <iostream>
void Background::test_loadmap()
{
	// test todo load map
	sf::Texture t1;
	t1.loadFromFile("media/tree.png");
	sf::Sprite s1;
	s1.setTexture(t1);

	sf::RenderTexture rt;
	rt.create(800, 600);
	rt.clear(sf::Color::Transparent);
	
	s1.setPosition(0, 400);
	rt.draw(s1);
	s1.setPosition(450, 400);
	rt.draw(s1);

	t1.loadFromFile("media/gascan.png");

	s1.setPosition(600, 50);
	rt.draw(s1);
	

	rt.display();
	sf::Texture texture = rt.getTexture();
	image = texture.copyToImage();

	for (int x = 0; x < 150; x++)
		for (int y = 0; y < 150; y++)
			image.setPixel(x + 30, y + 100, sf::Color(128, 0, 128));
}

Background::~Background()
{
}

bool Background::isOutBound(short x, short y) const
{
	return x < 0 || y < 0 || x >= width || y >= height;
}

void Background::reset()
{
	test_loadmap();
}

void Background::setPixel(unsigned short x, unsigned short y, const sf::Color & color)
{
	if (!isOutBound(x,y))
		image.setPixel(x, y, color);
}

sf::Color Background::getPixel(unsigned short x, unsigned short y) const
{
	return isOutBound(x, y) ? sf::Color::Transparent : image.getPixel(x, y);
}

sf::Color Background::getPixel(const sf::Vector2f & pos) const
{
	return isOutBound(pos.x, pos.y) ? sf::Color::Transparent : image.getPixel(pos.x, pos.y);
}

void Background::draw(sf::RenderWindow * window)
{
	texture.update(image);

	window->draw(sprite);
}
