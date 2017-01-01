#pragma once


#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\VertexArray.hpp>
#include <SFML\System\Time.hpp>

#include "background.hpp"
#include "particle.hpp"


class ParticleSystem : public sf::Drawable, public sf::Transformable
{
	Particle::Type currentParticle;
	std::vector<Particle> particles;
	sf::VertexArray vertices;
	sf::Time lifetime;
	sf::Vector2f position, lookAt;
	
	short max_particle_for_loop;
	bool casting;

	Background* bg;
public:

	ParticleSystem(Background& _bg);

	void setPos(const sf::Vector2f& _p);
	void moveEmitter(const sf::Time& elapsed);
	void setLookAt(const sf::Vector2f& _p);
	
	void setCurrentParticle(const Particle::Type& type);
	void toggle();

	void update(const sf::Time& elapsed);
	void calculatePhysics(Particle& p, sf::Vertex& v, const sf::Time& elapsed);

private:

	void resetParticle(std::size_t index);


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

