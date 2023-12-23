#pragma once

#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Matrix
{
	vector < vector < double> > A;

public:
	Matrix();

	Matrix(vector< vector < double > > a);

	Matrix(vector<double> s, int strok, int stolb);

	Matrix(int strok, int stolb, bool flag);

	void print_matrix_in_file(string file_name, string matrix_name, bool flag); //flag - true - дозапись, false - не дозапись

	vector<double>& operator[] (int index_strok);

	Matrix operator=(Matrix B);

	friend Matrix operator*(Matrix& A, Matrix& B);

	int Get_strok();

	int Get_stolb();

	friend Matrix Transpon(Matrix A);

	int SVD(Matrix& U, Matrix& V, Matrix& sigma);

	void add_stolb(double add);

	void delete_stolb(int index);

	Matrix ObrDiagMatrix();

	vector<double> GetDiagAl();
};

double error(Matrix istina, Matrix score);