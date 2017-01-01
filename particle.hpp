#pragma once

#include <SFML\System\Time.hpp>
#include <SFML\System\Vector2.hpp>




struct Particle
{
	sf::Vector2f velocity;
	sf::Time lifetime;

	enum Type
	{
		NONE,
		OTHER,

		ICE,
		LAVA,
		IONIC
	};
};

inline sf::Color GetParticleColorFromType(const Particle::Type& type)
{
	switch (type)
	{
		case Particle::Type::ICE:		return sf::Color(225, 231, 228);
		case Particle::Type::LAVA:		return sf::Color(207, 16, 32);
		case Particle::Type::IONIC:		return sf::Color(4, 93, 28);
		
		case Particle::Type::NONE:
		default:						return sf::Color::Transparent;
	}
}


inline Particle::Type GetParticleTypeFromColor(const sf::Color& color)
{
	if (color == GetParticleColorFromType(Particle::ICE))
		return Particle::ICE;

	if (color == GetParticleColorFromType(Particle::LAVA))
		return Particle::LAVA;

	if (color == GetParticleColorFromType(Particle::IONIC))
		return Particle::IONIC;

	if (color == GetParticleColorFromType(Particle::NONE))
		return Particle::NONE;

	return Particle::OTHER;
}

