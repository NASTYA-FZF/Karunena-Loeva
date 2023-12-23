#include "pch.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Signal.h"

signal::signal(double* A, double* f, double* fi, int N, double fd)
{
	sig.clear();
	akp.clear();
	int kol_sin = 3;
	for (int i = 0; i < N; i++)
	{
		sig.push_back(0.);
		for (int j = 0; j < kol_sin; j++)
		{
			sig[i] += A[j] * sin(2 * M_PI * f[j] * i / fd + fi[j]);
		}
	}
}

void signal::GetAKP(int poryadok)
{
	int size = sig.size();
	for (int m = 0; m < poryadok; m++)
	{
		akp.push_back(0.);
		for (int j = 0; j < size - m; j++)
		{
			akp[m] += sig[j] * sig[j + m];
		}
		akp[m] = akp[m] / (size - m);
	}
}

void signal::CreateMatrixAKP(int poryadok)
{
	GetAKP(poryadok);
	vector<vector<double>> akm;
	vector<double> work;
	for (int i = 0; i < poryadok; i++)
	{
		for (int j = 0; j < poryadok; j++)
		{
			work.push_back(akp[abs(i - j)]);
		}
		akm.push_back(work);
		work.clear();
	}
	Rxx = Matrix(akm);
	Rxx.print_matrix_in_file("Rxx.txt", "Rxx", false);
}

vector<double> signal::Get_sig()
{
	return sig;
}

signal::signal()
{
	sig.assign(5, 0.);
	akp.assign(5, 0.);
	Rxx = Matrix();
}

Matrix signal::GetMatrixAKM()
{
	return Rxx;
}
