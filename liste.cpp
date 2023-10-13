#include <fstream>

#define VMAX 120

using namespace std;
ifstream fin("liste.in");
ofstream fout("liste.out");

struct lista { int numere[VMAX+1]; };

void inchideFisiere();
bool auElementComun(lista a, lista b);
lista unifica(lista a, lista b);
void afiseazaLista(lista a);
void afiseazaStiva(lista stv[], int vf);

int main()
{
	int nrListe, nrElemente, i, numar, j, au, vf;
	fin >> nrListe;
	lista liste[nrListe], stv[nrListe], lst;
	for (i = 0; i < nrListe; i++)
	{
		for (j = 0; j <= VMAX; j++)
		{
			liste[i].numere[j] = stv[i].numere[j] = 0;
		}
	}
	fin >> nrElemente;
	for (i = 0; i < nrElemente; i++)
	{
		fin >> numar;
		liste[0].numere[numar] = 1;
	}
	vf = 0, stv[vf] = liste[0];
	for (i = 1; i < nrListe; i++)
	{
		fin >> nrElemente;
		for (j = 0; j < nrElemente; j++)
		{
			fin >> numar;
			liste[i].numere[numar] = 1;
		}
		lst = liste[i];
		au = auElementComun(lst, stv[vf]);
		while (au && vf > 0)
		{
			lst = unifica(lst, stv[vf--]);
			au = auElementComun(lst, stv[vf]);
		}
		if (au)
		{
			stv[vf] = unifica(lst, stv[vf]);
		}
		else
		{
			stv[++vf] = lst;
		}
	}
	fout << vf+1;
	inchideFisiere();
	return 0;
}
void inchideFisiere()
{
	fin.close();
	fout.close();
}
bool auElementComun(lista a, lista b)
{
	int nr;
	for (nr = 0; nr <= VMAX; nr++)
	{
		if (a.numere[nr] == 1 && b.numere[nr] == 1)
		{
			return 1;
		}
	}
	return 0;
}
lista unifica(lista a, lista b)
{
	int nr;
	lista u;
	for(nr = 0; nr <= VMAX; nr++)
	{
		u.numere[nr] = 0;
	}
	for (nr = 0; nr <= VMAX; nr++)
	{
		if (a.numere[nr] == 1
			|| b.numere[nr] == 1)
		{
			u.numere[nr] = 1;
		}
	}
	return u;
}
void afiseazaLista(lista a)
{
	int nr;
	fout << "Lista: ";
	for (nr = 0; nr <= VMAX; nr++)
	{
		if (a.numere[nr] == 1)
		{
			fout << nr << ' ';
		}
	}
	fout << '\n';
}
void afiseazaStiva(lista stv[], int vf)
{
	int nr;
	if (vf == -1)
	{
		fout << "Stiva este goala.\n";
	}
	else
	{
		int i = vf;
		while (i >= 0)
		{
			fout << "vf " << i << ": ";
			for (nr = 0; nr <= VMAX; nr++)
			{
				if (stv[i].numere[nr] == 1)
				{
					fout << nr << ' ';
				}
			}
			fout << '\n';
			i--;
		}
	}
}
// scor 30
