#include <fstream>

#define KMAX 10
#define LMAX 100000
#define VMAX 120

using namespace std;

ifstream fin("liste.in");
ofstream fout("liste.out");

struct lista { int v[VMAX+1], lg, nr; };

int vf = -1;
lista stv[LMAX];
lista L[LMAX];

void citeste_date_intrare();
void citeste_lista(int nr);
void adauga_in_stiva_lista(lista a);
void afiseaza_lista(lista a);
void afiseaza_stiva();
void inchide_fisiere();
lista concateneaza_liste_sortate_crescator(lista a, lista b);
int cauta_binar(int x, int v[], int lg);
bool au_element_comun(lista a, lista b);

int main()
{
	int n, i, au;
	lista lst, c;
	fin >> n;
	citeste_lista(0);
	adauga_in_stiva_lista(L[0]);
	for (i = 1; i < n; i++)
	{
		citeste_lista(i);
		lst = L[i];
		au = au_element_comun(lst, stv[vf]);
		while (au && vf > 0)
		{
			lst = concateneaza_liste_sortate_crescator(lst, stv[vf--]);
			au = au_element_comun(lst, stv[vf]);	
		}
		if (au)
		{
			stv[vf] = concateneaza_liste_sortate_crescator(lst, stv[vf]);
		}
		else
		{
			adauga_in_stiva_lista(lst);
		}
	}
	fout << vf+1;
	inchide_fisiere();
	return 0;
}

void citeste_lista(int nr)
{
	int k, i, x, poz, j, lg;
	// citeste lungimea listei
	fin >> k;
	for (lg = i = 0; i < k; i++)
	{
		// citeste al i-lea element din lista
		fin >> x;
		// afla pozitia lui x in vectorul sortat crescator
		// care contine toate elementele din lista curenta
		poz = cauta_binar(x, L[nr].v, lg);
		// daca x nu se afla deja in vector sau vectorul este gol
		if (!lg || L[nr].v[poz] != x)
		{
			// fa loc pentru inserarea lui x
			for (j = lg; j > poz; j--)
			{
				L[nr].v[j] = L[nr].v[j-1];
			}
			// insereaza pe x in lista pe pozitia poz
			L[nr].v[poz] = x;
			// creste numarul de elemente din vector
			lg++;
		}
	}
	L[nr].lg = lg;
	L[nr].nr = nr;
}

void adauga_in_stiva_lista(lista a)
{
	int i;
	if (vf+1 >= LMAX)
	{
		fout << "Eroare stiva_push: Stiva este plina\n";
	}
	else
	{
		stv[++vf] = a;
	}
}

// verifica daca doua liste date contin un element comun
bool au_element_comun(lista a, lista b)
{
	int au, i, poz;
	for (au = i = 0; i < a.lg && !au; i++)
	{
		poz = cauta_binar(a.v[i], b.v, b.lg);
		if (a.v[i] == b.v[poz])
		{
			return 1;
		}
	}
	return 0;
}

lista concateneaza_liste_sortate_crescator(lista a, lista b) 
{
	lista c;
	int n, m, lg, i, j;
	n = a.lg, m = b.lg;
	for (lg = i = j = 0; i < n && j < m;)
	{
		if (a.v[i] < b.v[j])
		{
			c.v[lg++] = a.v[i];
			i++;
		}
		else if (b.v[j] < a.v[i])
		{
			c.v[lg++] = b.v[j];
			j++;
		}
		else
		{
			c.v[lg++] = a.v[i];
			i++, j++;
		}
	}
	for (; i < n; i++)
	{
		if (c.v[lg-1] != a.v[i])
		{
			c.v[lg++] = a.v[i];
		}
	}
	for (; j < m; j++)
	{
		if (c.v[lg-1] != b.v[j])
		{
			c.v[lg++] = b.v[j];
		}
	}
	c.lg = lg;
	c.nr = a.nr < b.nr ? a.nr : b.nr;
	return c;
}

// cauta pe x in vectorul v[] de lungime lg
// returneaza pozitia lui x (unde se afla,
// sau unde ar trebui sa se afle)
int cauta_binar(int x, int v[], int lg)
{
	int st, dr, mij;
	st = -1, dr = lg;
	while (dr-st > 1)
	{
		mij = st + (dr-st)/2;
		if (v[mij] < x)
		{
			st = mij;
		}
		else
		{
			dr = mij;
		}
	}
	return dr;
}

void afiseaza_lista(lista a)
{
	int i;
	fout << "Lista " << a.nr << ": ";
	for (i = 0; i < a.lg; i++)
	{
		fout << a.v[i] << ' ';
	}
	fout << "; lg = " << a.lg << ", nr = " << a.nr;
	fout << '\n';
}

void afiseaza_stiva()
{
	int i, j;
	// verifica daca stiva este vida
	if (vf == -1)
	{
		fout << "Stiva este vida\n";
	}
	else
	{
		// afiseaza fiecare lista din stiva, in ordine
		for (i = vf; i >= 0; i--)
		{
			fout << "vf = " << i << ": ";
			for (j = 0; j < stv[i].lg; j++)
			{
				fout << stv[i].v[j] << ' ';
			}
			fout << '\n';
		}
	}
}

void inchide_fisiere()
{
	fin.close();
	fout.close();
}

// scor 0
