#include <fstream>
#define VMAX 121
#define DimMaxStiva 90000
using namespace std;
ifstream fin("liste.in");
ofstream fout("liste.out");
int uz[VMAX], stv[DimMaxStiva][VMAX], vf;
int main()
{
	int L, K, i, x, ok, j;
	fin >> L;
	fin >> K;
	for (i = 0; i < K; i++)
	{
		fin >> x;
		stv[vf][x] = 1;
	}
	for (i = 1; i < L; i++)
	{
		fin >> K;
		for (ok = j = 0 ; j < K; j++)
		{
			fin >> x;
			uz[x] = 1;
			if (stv[vf][x])
			{
				ok = 1;
			}
		}
		while (ok && vf >= 0)
		{
			for (j = 0; j < VMAX; j++)
			{
				if (uz[j] || stv[vf][j])
				{
					uz[j] = 1;
				}
			}
			for (--vf, ok = j = 0; vf >= 0 && j < VMAX; j++)
			{
				if (stv[vf][j] && uz[j])
				{
					ok = 1;
				}
			}
		}
		vf++;
		for (j = 0; j < VMAX; j++)
		{
			stv[vf][j] = uz[j];
			uz[j] = 0;
		}
	}
	fout << vf+1;
	fin.close();
	fout.close();
	return 0;
}
// scor 100
