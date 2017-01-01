#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Event.hpp>

#include "particlesystem.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "phell");

	Background bg;
	ParticleSystem ps(bg);

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
				ps.toggle();

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1)
				ps.setCurrentParticle(Particle::ICE);

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2)
				ps.setCurrentParticle(Particle::LAVA);

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3)
				ps.setCurrentParticle(Particle::IONIC);
		}

		sf::Time elapsed = clock.restart();

		ps.moveEmitter(elapsed);
		ps.setLookAt(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

		ps.update(elapsed);
		
		window.clear();
		bg.draw(&window);
		window.draw(ps);

		window.display();
	}

	return 0;
}