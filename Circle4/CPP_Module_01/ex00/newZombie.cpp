
#include <string>
#include "Zombie.hpp"

Zombie*	newZombie( std::string name )
{
	Zombie	*zombie;

	zombie = NULL;
	zombie = new Zombie(name);
	return (zombie);
}
