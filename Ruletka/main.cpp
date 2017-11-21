#include <iostream>
#include <locale.h>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <string>
#include <cstdio>

using namespace std;

string Obstaw(int & ilo��_pieni�dzy);
void Wczytaj_kwot�_zak�adu(int & kwota, int & ilo��_pieni�dzy);

int main() {

	setlocale(LC_ALL, "polish");
	srand((unsigned int)time(NULL));
	//cout << rand() << endl;

	int ilo��_pieni�dzy = 1000, kwota_zak�adu;



	//while (true)
	//{
	//	cout << "Masz " << ilo��_pieni�dzy << "$, jak� kwot� chcesz obstawi� wynik?" << endl;
	//	cin >> kwota_zak�adu;

	//	if (cin.fail())
	//	{
	//		cout << "Wprowadzi�e� nieprawid�ow� warto��" << endl;

	//		cin.clear();
	//		cin.sync();
	//	}
	//	else
	//	{
	//		if (kwota_zak�adu > 0 && kwota_zak�adu <= ilo��_pieni�dzy)
	//			break;
	//		else
	//			if (kwota_zak�adu == 0) cout << "Nie mo�esz obstawi� zerowego zak�adu" << endl;
	//			else if (kwota_zak�adu>ilo��_pieni�dzy) cout << "Nie masz tyle pieni�dzy" << endl;
	//			else if (kwota_zak�adu<0) cout << "Nie mo�esz obstawi� ujemn� kwot� zak�adu" << endl;

	//	}
	//}

	//while (!(cin >> kwota_zak�adu)) //dop�ki strumie� jest w stanie b��du -> dop�ki podawane s� b��dne dane
	//{
	//	cout << "a" << endl;
	//	//ew komunikat b��du
	//	cin.clear(); //kasowanie flagi b��du strumienia
	//	cin.sync(); //kasowanie zb�dnych znak�w z bufora
	//}
	Wczytaj_kwot�_zak�adu(kwota_zak�adu, ilo��_pieni�dzy);
	Obstaw(ilo��_pieni�dzy);

	system("pause");
	return 0;
}
string Obstaw(int & ilo��_pieni�dzy) {
	string a;

	cout << "Jak� opcje chcesz obstawic ? (zgodnie z poni�szym opisem) :" << endl;
	cout << "p - parzyste" << endl;
	cout << "n - nieparzyste" << endl;
	cout << "r - czerwone(red)" << endl;
	cout << "b - czarne(black)" << endl;
	cout << "g - g�rna po�owa" << endl;
	cout << "d - dolna po�owa" << endl;
	cout << "k1, k2, k3 - kolumna 1, kolumna 2, kolumna 3" << endl;
	cout << "w1, w2, ..., w12 - wiersz trzech numer�w" << endl;
	cout << "0 - 36 - pojedyncze pole o odpowiednim numerze" << endl;
	cin >> a;



	return a;
}

void Wczytaj_kwot�_zak�adu(int & kwota_zak�adu, int & ilo��_pieni�dzy) {
	string k;
	while (true)
	{
		cout << "Masz " << ilo��_pieni�dzy << "$, jak� kwot� chcesz obstawi� wynik?" << endl;
		cin >> k;
		kwota_zak�adu = atoi(k.c_str());
		if (kwota_zak�adu > 0 && kwota_zak�adu <= ilo��_pieni�dzy)
			break;
		else
			if (kwota_zak�adu == 0)
			{
				bool czy_zero = 1;
				for (short i = 0; i < k.size(); i++)
					if (k[i] != '0')
					{
						cout << "Wprowadzi�e� nieprawid�ow� warto��" << endl;
						czy_zero=0;
						break;
					}
				if (czy_zero) cout << "Nie mo�esz obstawi� zerowego zak�adu" << endl;
			}
			else if (kwota_zak�adu > ilo��_pieni�dzy) cout << "Nie masz tyle pieni�dzy" << endl;
			else if (kwota_zak�adu < 0) cout << "Nie mo�esz obstawi� ujemn� kwot� zak�adu" << endl;
	}
}