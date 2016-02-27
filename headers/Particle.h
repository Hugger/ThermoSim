#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <random>

#include "Settings.h"
#include "VectorUtilities.h"

class Particle
{
public:
	//Ctor
	Particle(double x_in, double y_in, double z_in, std::vector<double> velocity_in);

	////Public member functions////

	//Getters
	double getX() {return x;}
	double getY() {return y;}
	double getZ() {return z;}
	std::std::vector<double> getVelocity() {return velocity};
	double getXVel() {return velocity[0];}
	double getYVel() {return velocity[1];}
	double getZVel() {return velocity[2];}
	double getSpeed() {return mag(velocity)}

	//Setters
	void setVelocity( std::vector<double> a );
	void setSpeed(double a) {velocity = mult(a, unit(velocity))};
	void tick(double time); //Moves partcle forward in time in nanoseconds 

	friend std::ostream& operator<<(std::ostream& os, const Particle& particle);

private:
	////Private member variables////
	double x;
	double y;
	double z;
	std::vector<double> velocity;
};

#endif