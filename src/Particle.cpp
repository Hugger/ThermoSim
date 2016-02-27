#include "Particle.h"

using namespace std;

Particle::Particle(double x_in, double y_in, double z_in, std::vector<double> velocity_in)
:x(x_in), y(y_in), z(z_in), velocity(velocity_in), energy(energy_in)
{
	

}

void Particle::setVelocity(std::vector<double> a)
{
	velocity = a;
}

void Particle::tick(double time))
{
	x = x + time*10^9*velocity[0];
	y = y + time*10^9*velocity[1];
	z = z + time*10^9*velocity[2];
}