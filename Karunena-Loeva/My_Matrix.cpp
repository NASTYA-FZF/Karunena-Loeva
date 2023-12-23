#include "pch.h"
#include "My_Matrix.h"

Matrix::Matrix()
{
	vector <double> work;
	work.push_back(0.);
	work.push_back(0.);
	work.push_back(0.);
	work.push_back(0.);
	work.push_back(0.);
	A.push_back(work);
	work.clear();
	work.push_back(0.);
	work.push_back(0.);
	work.push_back(0.);
	work.push_back(0.);
	work.push_back(0.);
	A.push_back(work);
	work.clear();
	work.push_back(0.);
	work.push_back(0.);
	work.push_back(0.);
	work.push_back(0.);
	work.push_back(0.);
	A.push_back(work);
	work.clear();
	work.push_back(0.);
	work.push_back(0.);
	work.push_back(0.);
	work.push_back(0.);
	work.push_back(0.);
	A.push_back(work);
	work.clear();
}

Matrix::Matrix(vector<vector<double>> a)
{
	A = a;
}

Matrix::Matrix(vector<double> s, int strok, int stolb)
{
	vector<double> work;
	int size_s = s.size();
	for (int i = 0; i < strok; i++)
	{
		for (int j = 0; j < stolb; j++)
		{
			if (i == j && i < size_s) work.push_back(s[i]);
			else work.push_back(0.);
		}
		A.push_back(work);
		work.clear();
	}
}

Matrix::Matrix(int strok, int stolb, bool flag)
{
	vector <double> work;
	if (flag)
	{
		for (int i = 0; i < strok; i++)
		{
			for (int j = 0; j < stolb; j++)
			{
				work.push_back((double)rand() / RAND_MAX * 10. - 5.);
			}
			A.push_back(work);
			work.clear();
		}
	}
	else
	{
		work.assign(stolb, 0.);
		A.assign(strok, work);
	}
}

void Matrix::print_matrix_in_file(string file_name, string matrix_name, bool flag)
{
	ofstream out;
	if (!flag) out.open(file_name);
	else out.open(file_name, ios::app);
	out << "Matrix " << matrix_name << endl;
	for (int i = 0; i < A.size(); i++)
	{
		for (int j = 0; j < A[i].size(); j++)
		{
			out << A[i][j] << "\t\t";
		}
		out << endl;
	}
	out << endl;
	out.close();
}

vector<double>& Matrix::operator[](int index_strok)
{
	// TODO: вставьте здесь оператор return
	return A[index_strok];
}

Matrix Matrix::operator=(Matrix B)
{
	A.clear();
	A = B.A;
	return A;
}

int Matrix::Get_strok()
{
	return A.size();
}

int Matrix::Get_stolb()
{
	if (A.size() != 0) return A[0].size();
	else return 0;
}

int Matrix::SVD(Matrix& U, Matrix& V, Matrix& sigma_matrix)
{
	double thr = 1.E-4f, nul = 1.E-16f;
	int strok, stolb, i, j, l, k, lort, iter, in, ll, kk;
	double alfa, betta, hamma, eta, t, cos0, sin0, buf, s;

	strok = this->Get_strok(); //m
	stolb = this->Get_stolb(); //n

	bool flag_pereopr_matrix = false;
	Matrix u;
	if (strok > stolb)
	{
		u = Transpon(*this);
		strok = u.Get_strok();
		stolb = u.Get_stolb();
		flag_pereopr_matrix = true;
	}
	else u = *this;

	Matrix v(stolb, stolb, false);
	for (i = 0; i < stolb; i++)
	{
		for (j = 0; j < stolb; j++)
		{
			if (i == j) v[i][j] = 1.;
			else v[i][j] = 0.;
		}
	}

	iter = 0;
	while (1)
	{
		lort = 0;
		iter++;
		for (l = 0; l < stolb - 1; l++)
			for (k = l + 1; k < stolb; k++)
			{
				alfa = 0.; betta = 0.; hamma = 0.;
				for (i = 0; i < strok; i++)
				{
					alfa += u[i][l] * u[i][l];
					betta += u[i][k] * u[i][k];
					hamma += u[i][l] * u[i][k];
				}

				if (sqrt(alfa * betta) < nul)	continue;
				if (fabs(hamma) / sqrt(alfa * betta) < thr) continue;

				lort = 1;
				eta = (betta - alfa) / (2.f * hamma);
				t = (double)((eta / fabs(eta)) / (fabs(eta) + sqrt(1. + eta * eta)));
				cos0 = (double)(1. / sqrt(1. + t * t));
				sin0 = t * cos0;

				for (i = 0; i < strok; i++)
				{
					buf = u[i][l] * cos0 - u[i][k] * sin0;
					u[i][k] = u[i][l] * sin0 + u[i][k] * cos0;
					u[i][l] = buf;
				}
				for (i = 0; i < stolb; i++)
				{
					if (i >= stolb) continue;
					buf = v[i][l] * cos0 - v[i][k] * sin0;
					v[i][k] = v[i][l] * sin0 + v[i][k] * cos0;
					v[i][l] = buf;
				}
			}

		if (!lort) break;
	}
	vector <double> sigma;
	for (i = 0; i < stolb; i++)
	{
		s = 0.;
		for (j = 0; j < strok; j++)	s += u[j][i] * u[j][i];
		s = (double)sqrt(s);
		sigma.push_back(s);
		if (s < nul)	continue;
		for (j = 0; j < strok; j++)	u[j][i] /= s;
	}
	//======= Sortirovka ==============
	for (i = 0; i < stolb - 1; i++)
		for (j = i; j < stolb; j++)
			if (sigma[i] < sigma[j])
			{
				s = sigma[i]; sigma[i] = sigma[j]; sigma[j] = s;
				for (k = 0; k < strok; k++)
				{
					s = u[k][i]; u[k][i] = u[k][j]; u[k][j] = s;
				}
				for (k = 0; k < stolb; k++)
				{
					s = v[k][i]; v[k][i] = v[k][j]; v[k][j] = s;
				}
			}

	if (stolb > strok)
	{
		int iter_delete = stolb - strok;
		int index_delete = stolb;
		for (int i = 0; i < iter_delete; i++)
		{
			u.delete_stolb(index_delete - 1);
			index_delete--;
		}
	}

	if (flag_pereopr_matrix)
	{
		sigma_matrix = Transpon(Matrix(sigma, strok, stolb));
		U = v;
		V = u;
	}
	else
	{
		sigma_matrix = Matrix(sigma, strok, stolb);
		U = u;
		V = v;
	}

	return iter;
}

void Matrix::add_stolb(double add)
{
	for (int i = 0; i < A.size(); i++)
	{
		A[i].push_back(add);
	}
}

void Matrix::delete_stolb(int index)
{
	for (int i = 0; i < A.size(); i++)
	{
		A[i].erase(next(A[i].begin(), index));
	}
}

Matrix Matrix::ObrDiagMatrix()
{
	int strok = this->Get_stolb(), stolb = this->Get_strok();
	Matrix res(strok, stolb, false);
	for (int i = 0; i < strok; i++)
	{
		for (int j = 0; j < stolb; j++)
		{
			if (i == j) res[i][j] = 1 / this->A[i][j];
		}
	}
	return res;
}

vector<double> Matrix::GetDiagAl()
{
	int strok = Get_strok(), stolb = Get_stolb();
	vector<double> res;
	for (int i = 0; i < strok; i++)
	{
		for (int j = 0; j < stolb; j++)
		{
			if (i == j) res.push_back(A[i][j]);
		}
	}
	return res;
}

Matrix operator*(Matrix& A, Matrix& B)
{
	int stolb_A = A.Get_stolb();
	int strok_B = B.Get_strok();

	if (stolb_A != strok_B) return Matrix();
	int strok_A = A.Get_strok();
	int stolb_B = B.Get_stolb();
	Matrix res(strok_A, stolb_B, false);

	for (int i = 0; i < strok_A; i++)
	{
		for (int j = 0; j < stolb_B; j++)
		{
			for (int k = 0; k < stolb_A; k++)
			{
				res[i][j] += A[i][k] * B[k][j];
			}
		}
	}

	return res;
}

Matrix Transpon(Matrix A)
{
	if (A.Get_strok() == 0) return Matrix();
	int strok_res = A.Get_stolb(), stolb_res = A.Get_strok();
	Matrix res(strok_res, stolb_res, false);
	for (int i = 0; i < strok_res; i++)
	{
		for (int j = 0; j < stolb_res; j++)
		{
			res[i][j] = A[j][i];
		}
	}
	return res;
}

double error(Matrix istina, Matrix score)
{
	int size = istina.Get_strok();
	double err(0.);
	for (int i = 0; i < size; i++)
	{
		err += (istina[i][0] - score[i][0]) * (istina[i][0] - score[i][0]);
	}
	err = err / size;
	return err;
}