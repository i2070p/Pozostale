// Test.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <istream>
using namespace std;

/*******************/
struct Rozmiar {
	int h, w;
};

struct Macierz {
	struct Rozmiar rozmiar;
	int **tab;
};
/*******************/

string pokazMacierz(struct Macierz m) {
	stringstream ss;
	for (int i=0; i<m.rozmiar.h; i++) {
		for (int j=0; j<m.rozmiar.w; j++) {
			ss << m.tab[i][j] << ";";
		}
		ss << endl;
	}
	return(ss.str());
	//cout << "wysokosc: " << m.rozmiar.h << ", szerokosc: " << m.rozmiar.w << endl;
}

struct Rozmiar zmierzMacierz(string nazwa, char separator) {
	struct Rozmiar result={0,0};

	string line, firstline="";
	ifstream myfile (nazwa);
	if (myfile.is_open()) {
		while ( getline (myfile,line) ) {
			if (!result.h) {
				firstline=line;
			}
			result.h++;
		}
		for (unsigned int i=0; i<firstline.length(); i++) {
			if (firstline[i]==separator) result.w++;
		}
		myfile.close();
	} else cout << "Nie udalo sie otworzyc pliku."; 

	return(result);
}

int** tworzTablice2D(struct Rozmiar rozmiar) {
	int **tab = NULL;
	tab = (int**)malloc(rozmiar.h*sizeof(int*));

	for (int i=0; i<rozmiar.h; i++) {
		tab[i]=(int*)malloc(sizeof(int)*rozmiar.w);
	}
	return(tab);
}


struct Macierz wczytajMacierz(string nazwa, char separator) {
	struct Macierz m;
	string line;

	m.rozmiar = zmierzMacierz(nazwa, separator);
	m.tab = tworzTablice2D(m.rozmiar);

	ifstream myfile (nazwa);
	string num="";
	char z;
	int k=0, j=0;
	if (myfile.is_open()) {
		while (getline (myfile,line)) {
			j=0;
			for (int i=0; i<line.length(); i++) {
				z=line[i];
				if (z!=separator && z >=48 && z<=57) num += z; else {
					m.tab[k][j]=atoi(num.c_str()); 
					num="";
					j++;
				}
			}
			k++;
		}
		myfile.close();
	} else cout << "Nie udalo sie otworzyc pliku."; 

	return(m);
}

void zapiszMacierz(struct Macierz m, string nazwa) {
	ofstream myfile (nazwa);
	if (myfile.is_open()) {
		myfile << pokazMacierz(m);
		myfile.close();
	} else cout << "Nie udalo sie otworzyc pliku."; 
}

struct Macierz pomnozMacierze(struct Macierz m1, struct Macierz m2) {
	struct Macierz m;

	if (m1.rozmiar.h==m2.rozmiar.w) {
		m.rozmiar.h = m1.rozmiar.h;
		m.rozmiar.w = m2.rozmiar.w;
		m.tab=tworzTablice2D(m.rozmiar);
		int n = m2.rozmiar.h;

		for (int i=0; i<m.rozmiar.h; i++) 
			for (int j=0; j<m.rozmiar.w; j++) {
				m.tab[i][j]=0;
				for (int k=0; k<n; k++) m.tab[i][j]=m.tab[i][j]+m1.tab[i][k]*m2.tab[k][j]; 
			}

	} else cout << "Nie da sie wykonac mnozenia podanych macierzy.";

	return(m);
}

string pokazRozmiar(struct Macierz m) {
	stringstream ss;
	ss << endl << "Wysokosc: " << m.rozmiar.h << ", Wysokosc" << m.rozmiar.w <<endl;
	return(ss.str());
}

int _tmain(int argc, _TCHAR* argv[])
{
	struct Macierz m1=wczytajMacierz("C:\\Temp\\1.txt",';');
	struct Macierz m2=wczytajMacierz("C:\\Temp\\2.txt",';');
	struct Macierz m3=pomnozMacierze(m1, m2);
	
	cout << pokazMacierz(m1) << pokazRozmiar(m1) ;
	cout << pokazMacierz(m2) << pokazRozmiar(m2);
	cout << pokazMacierz(m3) << pokazRozmiar(m3);

	zapiszMacierz(m3,"C:\\Temp\\3.txt");
	getchar();
	return 0;
}

