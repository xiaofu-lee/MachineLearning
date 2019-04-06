#include "Data.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX_RANGE 10

Data::Data(size_t trainDataVectorSize, size_t thetaParamVectorSize):
	trainDataVectorSize(trainDataVectorSize), thetaParamVectorSize(thetaParamVectorSize), realValueVectorSize(trainDataVectorSize)
{
	this->thetaParamVector = new double[this->thetaParamVectorSize]{ 0.0 };
	this->trainDataVector = new double[this->trainDataVectorSize]{ 0.0 };
	this->realValueVector = new double[this->realValueVectorSize]{ 0.0 };

	for (size_t i = 0; i < this->thetaParamVectorSize; i++)
	{
		this->thetaParamVector[i] = (double)(rand() % MAX_RANGE) + (rand() % RAND_MAX) / (RAND_MAX * 1.0);
	}
	for (size_t i = 0; i < trainDataVectorSize; i++)
	{
		double x = (double)(rand() % 150) + (rand() % RAND_MAX) / (RAND_MAX * 1.0);
		double y = this->thetaParamVector[0] * 1.0 + this->thetaParamVector[1] * x;
		int val = rand() % 50;
		if (rand() % 2) {
			y += (double)val;
		}
		else
		{
			y -= (double)val;
		}

		this->trainDataVector[i] = x;
		this->realValueVector[i] = y;
	}
}


Data::~Data()
{
	delete[] this->thetaParamVector;
	delete[] this->trainDataVector;
	delete[] this->realValueVector;
}

void Data::printData()
{
	for (size_t i = 0; i < this->trainDataVectorSize; i++)
	{
		printf("[Data::printData] x = %5.5f, y = %5.5f\n", this->trainDataVector[i], this->realValueVector[i]);
	}
}

double Data::getMin()
{
	double min = this->trainDataVector[0];
	for (size_t i = 0; i < this->trainDataVectorSize; i++)
	{
		if (this->trainDataVector[i] < min && fabs(this->trainDataVector[i] - min) > 1e-6)
		{
			min = this->trainDataVector[i];
		}
	}
	return min;
}
double Data::getMax()
{
	double max = this->trainDataVector[0];
	for (size_t i = 0; i < this->trainDataVectorSize; i++)
	{
		if (this->trainDataVector[i] > max && fabs(this->trainDataVector[i] - max) > 1e-6)
		{
			max = this->trainDataVector[i];
		}
	}
	return max;
}
