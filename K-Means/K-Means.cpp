#include <iostream>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<limits.h>
#include<assert.h>
#include <vector>
#include "Distance.h"
#include "SimpleKMeans.h"

using namespace std;

int main()
{
	printf("------------------------------------------------------------\n");
	printf("			KMeans聚类算法						\n");
	printf("------------------------------------------------------------\n");

	double data[] = {
		0.0, 0.2, 0.4,
		0.3, 0.2, 0.4,
		0.4, 0.2, 0.4,
		0.5, 0.2, 0.4,
		5.0, 5.2, 8.4,
		6.0, 5.2, 7.4,
		4.0, 5.2, 4.4,
		10.3, 10.4, 10.5,
		10.1, 10.6, 10.7,
		11.3, 10.2, 10.9
	};

	double data1[] = {
		0.90796996,		5.05836784,
		-2.88425582,	0.01687006,
		-3.3447423,		1.01730512,
		-0.32810867,	0.48063528,
		1.90508653,		3.530091,
		-3.00984169,	2.66771831,
		-3.38237045,	2.9473363,
		2.22463036,		1.37361589,
		2.54391447,		3.21299611,
		-2.46154315,	2.78737555,
		-3.38237045,	2.9473363,
		2.8692781,		2.54779119,
		2.6265299,		3.10868015,
		-2.46154315,	2.78737555,
		-3.38237045,	2.9473363,
		2.80293085,		2.7315146
	};

	int row = 16;
	int featureNum = 2;
	double** zzz = new double* [row];
	for (size_t i = 0; i < row; i++)
	{
		zzz[i] = new double[featureNum]{ 0 };
		for (size_t j = 0; j < featureNum; j++)
		{
			zzz[i][j] = data1[i * featureNum + j];
		}
	}

	SimpleKMeans skm(4, featureNum);
	skm.run(zzz, row);
	printf("------------------------------------------------------------\n");
	printf("			KMeans聚类算法						\n");
	printf("------------------------------------------------------------\n");
	//printf("|%10s|%15s|%15s|%15s|%10s  |\n", "样本编号", "特征1", "特征2", "特征3", "归类簇");
	printf("|%10s|%15s|%15s|%10s  |\n", "样本编号", "特征1", "特征2","归类簇");
	for (size_t i = 0; i < row; i++)
	{
		int label = -1;
		skm.getLabel(zzz[i], label);
		printf("|%10d|", i);
		for (size_t k = 0; k < featureNum; k++)
		{
			printf("%15.5lf|", zzz[i][k]);
		}
		printf(" cluster %d  |\n", label + 1);
	}
	system("pause");
}
