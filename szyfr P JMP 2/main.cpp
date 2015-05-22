#include <iostream>
#include <fstream>

using namespace std;

//Struktura przechowujaca dane o znaku
struct znak {
	//Liczby szyfrujace
	int a, b;
	//Znak odszyfrowany
	char c;
};

//Funkcja szyfrujaca dany znak
void zaszyfruj(znak* wejscie)
{
	int liczba = static_cast<int>(wejscie->c);
	liczba -= 97;

	//Zmiejszamy o 1, bo dla 'i' i 'k' mamy ten sam kod szyfrujacy
	if (liczba > 8) liczba--;

	wejscie->a = static_cast<int>(liczba / 5);
	wejscie->b = liczba - 5 * wejscie->a;
}

//Funkcja deszyfrujaca
void odszyfruj(znak* wejscie)
{
	int liczba = 97 + 5 * wejscie->a + wejscie->b;
	//Zwiekszamy o 1, bo dla 'i' i 'k' mamy ten sam kod szyfrujacy
	if (liczba > 105) liczba++;
	wejscie->c = static_cast<char>(liczba);
}

int main()
{
	//Na poczatek zakladamy, ze wiadomosc mam max 25 znakow; dla ulatwienia
	znak znakI[25];

	//Tablica na kolejne kody znakow
	int tablica[50] = { 0 };
	int pomocnicza = 0;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	ifstream plik("zaszyfrowane.txt");

	if (!plik)
	{
		cout << "Nie mozna otworzyc pliku";
		getchar();
		return 1;
	}

	//Zakladamy, ze wszystko znajduje sie w jednej linijce
	while (!plik.eof())
		plik >> tablica[pomocnicza++];

	plik.close();

	//Wypisujemy dane, by sprawdzic, czy pobralismy dobrze
	for (int i = 0; i < 50 && tablica[i] != 0; i++)
	{
		cout << tablica[i] << " ";
	}

	//Wypelniamy tablice znakow danymi pobranymi
	for (int i = 0; i < 25; i++)
	{
		znakI[i].a = tablica[i]/10 - 1;
		znakI[i].b = tablica[i]%10 - 1;
	}

	
	cout << endl;

	//Wypisujemy odszyfrowany tekst
	for (int i = 0; i < 25 && znakI[i].a >= 0; i++)
	{
		odszyfruj(&znakI[i]);
		cout << znakI[i].c;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ofstream plik2("odszyfrowane.txt", ios_base::in | ios_base::app);

	if (!plik2)
		cout << "Nie mo¿na otworzyæ pliku!" << endl;

	//Zapisujemy do pliku odszyfrowana tresc
	for (int i = 0; i < 25 && znakI[i].a >= 0; i++)
	{
		plik2 << znakI[i].c;
	}

	plik2.close();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ifstream plik3("odszyfrowane2.txt");

	if (!plik3)
	{
		cout << "Nie mozna otworzyc pliku";
		getchar();
		return 1;
	}
	
	//Bedziemy od razy pakowac wszystko do tablicy typu 'znaki', bo wczytujemy konkretne litery
	pomocnicza = 0;
	while (!plik3.eof())
		plik3 >> znakI[pomocnicza++].c;

	plik3.close();

	//Szyfrujemy dane:
	for (int i = 0; i < 25 && znakI[i].c != NULL; i++)
	{
		zaszyfruj(&znakI[i]);
	}

	ofstream plik4("zaszyfrowane2.txt", ios_base::in | ios_base::app);

	if (!plik4)
		cout << "Nie mo¿na otworzyæ pliku!" << endl;

	//Zapisujemy zaszyfrowane dane do pliku
	for (int i = 0; i < 25 && znakI[i].a >= 0; i++)
	{
		plik4 << znakI[i].a + 1 << znakI[i].b + 1 << " ";
	}

	plik4.close();

	getchar();
	return 0;
}