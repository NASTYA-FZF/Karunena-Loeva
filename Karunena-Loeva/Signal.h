#pragma once
#include <vector>
#include "My_Matrix.h"
using namespace std;

class signal
{
	vector<double> sig, akp;
	Matrix Rxx;

public:
	signal(double* A, double* f, double* fi, int N, double fd);

	void GetAKP(int poryadok);

	void CreateMatrixAKP(int poryadok);

	vector<double> Get_sig();

	signal();

	Matrix GetMatrixAKM();
};