#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <fstream>

using namespace std;

double wyraz_z_definicji(double potega, int wyraz) {
	double gora = pow(potega, wyraz);
	double dol = 1.0;
	for (int i = 1; i <= wyraz; i++) {
		dol *= (double)i;
	}
	return (gora / dol);
}

double wyraz_z_poprzedniego(double potega, int wyraz, double poprzedni) {
	double wart_wyraz = poprzedni*potega;
	wart_wyraz /= ((double)wyraz);
	return wart_wyraz;
}

double sumuj_od_poczatku(double *tablica_szer, int ilosc_elementow) {
	double suma = 0;
	for (int i = 0; i < ilosc_elementow; i++)
		suma += tablica_szer[i];
	return suma;
}

double sumuj_od_konca(double *tablica_szer, int ilosc_elementow) {
	double suma = 0;
	for (int i = ilosc_elementow-1; i >= 0; i--)
		suma += tablica_szer[i];
	return suma;
}

double suma(bool z_definicji, bool od_poczatku, int ilosc_iteracji, double argument) {
	double *tablica = new double [ilosc_iteracji];
	double suma_szer = 0;
	if (z_definicji == true) {
		for (int i = 0; i < ilosc_iteracji; i++) {
			tablica[i] = wyraz_z_definicji(argument, i);
		}
	}
	else {
		tablica[0] = 1;
		for (int i = 1; i < ilosc_iteracji; i++) {
			tablica[i] = wyraz_z_poprzedniego(argument, i, tablica[i-1]);
		}
	}
	if (od_poczatku == true)
		suma_szer = sumuj_od_poczatku(tablica, ilosc_iteracji);
	else
		suma_szer = sumuj_od_konca(tablica, ilosc_iteracji);
	return suma_szer;
}


int main()
{
	FILE *plik;
	if ((plik = fopen("wynik.txt", "w")) == NULL) {
		printf("Nie dziala!\n");
		exit(1);
	}
	double argument;
	int iteracje;
	double wartosc;
	for (int k = 0; k < 4; k++) {
		argument = 1.0;
		switch (k) {
		case 0:
			fprintf(plik, "Bledy dla obliczania wyrazow z definicji, sumujac od poczatku\n");
			break;
		case 1:
			fprintf(plik, "Bledy dla obliczania wyrazow z definicji, sumujac od konca\n");
			break;
		case 2:
			fprintf(plik, "Bledy dla liczenia wyrazu, korzystaj¹c z wartoœci poprzedniego, sumujac od poczatku\n");
			break;
		case 3:
			fprintf(plik, "Bledy dla liczenia wyrazu, korzystaj¹c z wartoœci poprzedniego, sumujac od konca\n");
			break;
		}
		fprintf(plik, "x\te^x\t");
		for (int j = 0; j < 4; j++) {
			switch (j) {
			case 0:
				iteracje = 10;
				break;
			case 1:
				iteracje = 25;
				break;
			case 2:
				iteracje = 50;
				break;
			case 3:
				iteracje = 100;
				break;
			}
			fprintf(plik, "ilosc iteracji: %d\t", iteracje);
		}
		fprintf(plik, "\n");
		for (int i = 0; i < 20; i++) {
			wartosc = exp(argument);
			fprintf(plik, "%d\t", i + 1);
			fprintf(plik, "%.50g\t", wartosc);
			for (int j = 0; j < 4; j++) {
				switch (j) {
				case 0:
					iteracje = 10;
					break;
				case 1:
					iteracje = 25;
					break;
				case 2:
					iteracje = 50;
					break;
				case 3:
					iteracje = 100;
					break;
				}
				switch (k) {
				case 0:
					fprintf(plik, "%.50g\t", abs(wartosc - suma(true, true, iteracje, argument)));
					break;
				case 1:
					fprintf(plik, "%.50g\t", abs(wartosc - suma(true, false, iteracje, argument)));
					break;
				case 2:
					fprintf(plik, "%.50g\t", abs(wartosc - suma(false, true, iteracje, argument)));
					break;
				case 3:
					fprintf(plik, "%.50g\t", abs(wartosc - suma(false, false, iteracje, argument)));
					break;
				}
				
			}
			fprintf(plik, "\n");
			argument += (double)1;
		}
	}
	fclose(plik);
    return 0;
}