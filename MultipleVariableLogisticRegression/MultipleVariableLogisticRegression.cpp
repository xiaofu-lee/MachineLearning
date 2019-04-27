#include <iostream>
#include <stdio.h>
#include "LogisticRegressionAlgorithm.h"

#include "Data.h"

#define THETA_SIZE 3

void printLogisticRegressionAlgorithmTheta(const LogisticRegressionAlgorithm& lra)
{
	printf("[main::TrainTheta] ");
	for (size_t i = 0; i < lra.thetaParamVectorSize; i++)
	{
		printf("theta[%02d] = %5.8f, ", i, lra.thetaParamVector[i]);
	}
	printf("\n");
}

int main()
{
	Data data(3);
	data.readData("testSet.txt", 100);
	data.printData();
	LogisticRegressionAlgorithm lra(THETA_SIZE);
	lra.train(data);
	printLogisticRegressionAlgorithmTheta(lra);
}