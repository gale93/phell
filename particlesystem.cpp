#include "particlesystem.hpp"

#include <SFML\Window\Keyboard.hpp>

ParticleSystem::ParticleSystem(Background& _bg) :
	particles(1000),
	vertices(sf::Points, 1000),
	max_particle_for_loop(1000 / 90),
	lifetime(sf::seconds(3)),
	position(400,300),
	currentParticle(Particle::Type::ICE),
	bg(&_bg)
{
}


void ParticleSystem::setPos(const sf::Vector2f & _p)
{
	position = _p;
}

void ParticleSystem::moveEmitter(const sf::Time & elapsed)
{
	float speed = elapsed.asSeconds() * 250.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		position.y -= speed;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		position.y += speed;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		position.x -= speed;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		position.x += speed;
}

void ParticleSystem::setLookAt(const sf::Vector2f& _p)
{
	lookAt = _p;
}

void ParticleSystem::setCurrentParticle(const Particle::Type& type)
{
	currentParticle = type;
}

void ParticleSystem::toggle()
{
	casting = !casting;
}

void ParticleSystem::update(const sf::Time& elapsed)
{
	short particles_emitted = 0;

	for (std::size_t i = 0; i < particles.size(); ++i)
	{
		Particle& p = particles[i];
		
		p.lifetime -= elapsed;
		if (p.lifetime <= sf::Time::Zero)
		{
			if (casting && particles_emitted++ < max_particle_for_loop)
				resetParticle(i);
			else
				vertices[i].color = sf::Color::Transparent;
		}			
		else
			calculatePhysics(p, vertices[i], elapsed);
	}
}

void ParticleSystem::calculatePhysics(Particle &p, sf::Vertex &v, const sf::Time& elapsed)
{
	const sf::Vector2f old_pos = v.position;
	v.position += p.velocity * elapsed.asSeconds();

	Particle::Type type = GetParticleTypeFromColor(v.color);
	auto matched_type = GetParticleTypeFromColor(bg->getPixel(v.position));

	switch (type)
	{
	case Particle::ICE:
	{	
		if (matched_type != Particle::LAVA && matched_type != Particle::NONE)
		{
			p.lifetime = sf::Time::Zero;
			bg->setPixel(old_pos.x, old_pos.y, v.color);
		}
	}
	break;
	case Particle::LAVA:
	{
		if (matched_type == Particle::ICE)
		{
			p.lifetime = sf::Time::Zero;
			bg->setPixel(v.position.x,v.position.y, GetParticleColorFromType(Particle::NONE));
		}
		else if (matched_type == Particle::OTHER)
			p.lifetime = sf::Time::Zero;
	}
	break;
	case Particle::IONIC:
		if (matched_type != Particle::NONE)
		{
			p.lifetime = sf::Time::Zero;
			bg->setPixel(v.position.x, v.position.y, GetParticleColorFromType(Particle::NONE));
		}
		break;
	}


	if (bg->getPixel(v.position) == v.color)
	{
		p.lifetime = sf::Time::Zero;
		bg->setPixel(old_pos.x, old_pos.y, v.color);
	}
}

void ParticleSystem::resetParticle(std::size_t index)
{
	float speed = (std::rand() % 50) + 250.f;
	auto normalize = [](const sf::Vector2f& source) {
		float length = sqrt((source.x * source.x) + (source.y * source.y));
		if (length != 0)
			return sf::Vector2f(source.x / length, source.y / length);
		else
			return source;
	};

	float x = lookAt.x - position.x + std::rand() % 100 - 50;
	float y = lookAt.y - position.y + std::rand() % 100 - 50;


	particles[index].lifetime = sf::milliseconds((std::rand() % 1000) + 500);
	particles[index].velocity = normalize(sf::Vector2f(x, y)) * speed;


	vertices[index].position = position;
	vertices[index].color = GetParticleColorFromType(currentParticle);
}


void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = NULL;
	target.draw(vertices, states);
}



