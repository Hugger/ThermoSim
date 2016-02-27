#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <math.h>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <getopt.h>

#include "Particle.h"
#include "VectorUtilities.h"

using namespace std;

int main(int argc, char**argv)
{
	/////////////////Init Settings////////////////////
	//
	//Global Static Variables
	int tickDuration = 1000; 	//Amount of time progressed each tick in nanoseconds
	int totalTime 10**9; 		//Total time to pass in Sim, in nanoseconds
	int particleNumber = 10**7; //Total number of particles to create
	double particleMass = 6.6464764*10^-27; //Mass of Helium Atom
	double amplitudeDriver = .01; //Range of motion of the driver
	double frequencyDriver = 1000; //Frequency of driver in hertz
	double lengthPipe = .1;		//Range of pipe along x axis
	double widthPipe = .01;		//Range of pipe along y axis
	double heightPipe = .01;	//Range of pipe along z axis
	double bathTemperature = 300; //Temperature of outside world and heat exchanger in Kelvin
	double heatExchangerStart = .4 //Upper limit of heat exchanger along x axis
	double heatExchangerEnd =  .3 //Lower limit of heat exchanger along x axis

	//Global Variables updated every tick
	int simTime = 0; 		//Time of simulation in nanoseconds
	int totalTicks = 0;
	double driverPosition = lengthPipe/2 + amplitudeDriver/2+amplitudeDriver*cos(2*math.Pi()*time*10^9*frequencyDriver - math.Pi())/2
	double driverSpeed = -1*amplitudeDriver*2*math.Pi()*frequencyDriver*sin(2*math.Pi()*time*10^9*frequencyDriver - math.Pi())
	Particle gas [particleNumber]; //This is an array of the the particles in the the simulation, collectivily known as gas


	//Global varaibles to use for tally information
	double workDoneByGas = 0; //Work done by gas over course of simulation (energy lost by scattering with driver)
	double workDoneOnGas = 0; //Work done on gas over course of simulation )energy gain by scattering with driver)
	double heatLost = 0;			//Energy given to heat exchanger through scatter
	double heatGain = 0;			//Energy lost by heat exchanger through scatter
	int heatExchangerDivisions = 10; //Number of regions to collect heat exchanger from
	double heatLostArray [heatExchangerDivisions]; //heat lost to bath in each segment of the heat exchanger

	int wholePipeTalyDivisions = 100; 	//Number of tally points along pipe
	double atomCountData [wholePipeTalyDivisions]; //List of number of atoms in each tally division
	double temperatureData [wholePipeTalyDivisions]; //List of temperatures in Pipe]

	//Initialize World
	//This process begins creating the gas a temperature given
		//Generate Random speed
		//Generate Radnom unit vector
		//Gen 3 random cordinates
		//Create Particle from this in array slot

	double speed = 0;

	std::Vector<double> randomUnit;
	randomUnit.push_back(0);
	randomUnit.push_back(0);
	randomUnit.push_back(0);

	double randX;
	double randY;
	double randZ;

	for (int i = 0; i < particleNumber; i++)
	{
		speed = genRandomSpeedAtTemp(300); //
		randomUnit[0] = rand();
		randomUnit[1] = rand();
		randomUnit[2] = rand();
		randomUnit = unit(randomUnit);			//This is from VectorUtilities

		randX = lengthPipe*rand() - lengthPipe/2;
		randY = widthPipe*rand() - widthPipe/2;
		randZ = heightPipe*rand() - heightPipe/2;

		gas[i] = particle(randX, randY, randZ, mult(speed, randomUnit));
	}

	//Testing for scatter
	while(simTime < totalTime)
	{
		for (int i = 0; i < particleNumber; i++)
		{
			//If x velocity is negative and position less than -lengthPipe/2
			if(gas[i].getXVel() < 0 && gas[i].getX() < -1*lengthPipe/2)
			{
				gas[i].scatterZY(); //Scatter in ZY Plane
				gas[i].tick();
			}
			//If x velcocity is positive and position greater than driverPosition
			if(gas[i].getXVel() > 0 && gas[i].getX() > driverPosition)
			{
				gas[i].scatterZY(); 	//Scatter off driver
				gas[i].addXvel(driverSpeed); //Add or sub speed from particle
				gas[i].tick();
			}
			//Test to see if particle is in range of heat exchanger
			if( gas[i].getX() > heatExchangerEnd && gas[i].getX() < heatExchangerStart)
			{ 			//Test for heat scatter
				//If z velocity is positive and position greater than heightPipe/2
				if(gas[i].getZVel() > 0 && gas[i].getZ() > heightPipe/2)
				{
					gas[i].scatterXY(); //scatterXYheat
					double energyInitial = (particleMass*gas[i].getSpeed()^2)/2;
					gas[i].setSpeed(genRandomSpeedAtTemp(bathTemperature));
					double energyFinal = (particleMass*gas[i].getSpeed()^2)/2;
					heatTally(energyFinal - energyInitial, gas[i].getX()); //Keeps track of energy into and out of the system
					gas[i].tick();
				}
				if(gas[i].getZVel() < 0 && gas[i].getZ() < -1*heightPipe/2) //If z velocity is negative and position less than -heightPipe/2
				{
					gas[i].scatterXY(); //scatterXYheat
					double energyInitial = (particleMass*gas[i].getSpeed()^2)/2;
					gas[i].setSpeed(genRandomSpeedAtTemp(bathTemperature));
					double energyFinal = (particleMass*gas[i].getSpeed()^2)/2;
					heatTally(energyFinal - energyInitial, gas[i].getX()); //Keeps track of energy into and out of the system
					gas[i].tick();
				}
				if(gas[i].getYVel() > 0 && gas[i].getY() > heightPipe/2)
				{
					gas[i].scatterXZ(); //scatter XZ
					double energyInitial = (particleMass*gas[i].getSpeed()^2)/2;
					gas[i].setSpeed(genRandomSpeedAtTemp(bathTemperature));
					double energyFinal = (particleMass*gas[i].getSpeed()^2)/2;
					heatTally(energyFinal - energyInitial, gas[i].getX()); //Keeps track of energy into and out of the system
					gas[i].tick();
				}
				if(gas[i].getYVel() < 0 && gas[i].getY() < -1*heightPipe/2) //If z velocity is negative and position less than -heightPipe/2
				{
					gas[i].scatterXZ(); //scatterXYheat
					double energyInitial = (particleMass*gas[i].getSpeed()^2)/2;
					gas[i].setSpeed(genRandomSpeedAtTemp(bathTemperature));
					double energyFinal = (particleMass*gas[i].getSpeed()^2)/2;
					heatTally(energyFinal - energyInitial, gas[i].getX()); //Keeps track of energy into and out of the system
					gas[i].tick();
				}
			}
			else //This is scattering not in the heat exchanger
			{
				//If z velocity is positive and position greater than heightPipe/2
				if(gas[i].getZVel() > 0 && gas[i].getZ() > heightPipe/2)
				{
					gas[i].scatterXY(); //scatterXYheat
					gas[i].tick();
				}
				if(gas[i].getZVel() < 0 && gas[i].getZ() < -1*heightPipe/2) //If z velocity is negative and position less than -heightPipe/2
				{
					gas[i].scatterXY(); //scatterXYheat
					gas[i].tick();
				}
				if(gas[i].getYVel() > 0 && gas[i].getY() > heightPipe/2)
				{
					gas[i].scatterXZ(); //scatter XZ
					gas[i].tick();
				}
				if(gas[i].getYVel() < 0 && gas[i].getY() < -1*heightPipe/2) //If z velocity is negative and position less than -heightPipe/2
				{
					gas[i].scatterXZ(); //scatterXYheat
					gas[i].tick();
				}
			}
		}

		//Process data
		if( totalTicks % 100 = 0 )
		{
			//Temp proportional to average energy
			//Pressure proportional to avergae energy times number of atoms
			for (int i = 0; i < particleNumber; i++)
			{
				int bin = (gas[i].getX()+lengthPipe/2)/wholePipeTalyDivisions;
				if(bin < wholePipeTalyDivisions -1) //Some may be outside pipe, near the driver. I don't want those tallied
				{
					atomCountData[bin] = atomCountData[bin] + 1;
					energyData[bin] =  energyData[bin] + gas[i].getSpeed()^2; //Pressure is just energy, temp is energy per particle
				}
			}

		}
		totalTicks ++;
		simTime = totalTicks*tickDuration;



	}
	
	
}

double simulate::genRandomSpeedAtTemp(double temp))
{
	return 1000; ///!!! this is just a filler number until I figure this out
}

void simulate::heatTally(double energy, double xPos)
{
	//Figure out which bin it goes into
	int bin = (xPos - heatExchangerEnd) / heatExchangerDivisions;
	//add it to that bin
	heatLostArray[bin] = heatLostArray[bin] + energy;
}