#include <iostream>
#include <locale.h>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <string>
#include <cstdio>

using namespace std;

string Obstaw(int & iloœæ_pieniêdzy);
void Wczytaj_kwotê_zak³adu(int & kwota, int & iloœæ_pieniêdzy);

int main() {

	setlocale(LC_ALL, "polish");
	srand((unsigned int)time(NULL));
	//cout << rand() << endl;

	int iloœæ_pieniêdzy = 1000, kwota_zak³adu;



	//while (true)
	//{
	//	cout << "Masz " << iloœæ_pieniêdzy << "$, jak¹ kwotê chcesz obstawiæ wynik?" << endl;
	//	cin >> kwota_zak³adu;

	//	if (cin.fail())
	//	{
	//		cout << "Wprowadzi³eæ nieprawid³ow¹ wartoœæ" << endl;

	//		cin.clear();
	//		cin.sync();
	//	}
	//	else
	//	{
	//		if (kwota_zak³adu > 0 && kwota_zak³adu <= iloœæ_pieniêdzy)
	//			break;
	//		else
	//			if (kwota_zak³adu == 0) cout << "Nie mo¿esz obstawiæ zerowego zak³adu" << endl;
	//			else if (kwota_zak³adu>iloœæ_pieniêdzy) cout << "Nie masz tyle pieniêdzy" << endl;
	//			else if (kwota_zak³adu<0) cout << "Nie mo¿esz obstawiæ ujemn¹ kwot¹ zak³adu" << endl;

	//	}
	//}

	//while (!(cin >> kwota_zak³adu)) //dopóki strumieñ jest w stanie b³êdu -> dopóki podawane s¹ b³êdne dane
	//{
	//	cout << "a" << endl;
	//	//ew komunikat b³êdu
	//	cin.clear(); //kasowanie flagi b³êdu strumienia
	//	cin.sync(); //kasowanie zbêdnych znaków z bufora
	//}
	Wczytaj_kwotê_zak³adu(kwota_zak³adu, iloœæ_pieniêdzy);
	Obstaw(iloœæ_pieniêdzy);

	system("pause");
	return 0;
}
string Obstaw(int & iloœæ_pieniêdzy) {
	string a;

	cout << "Jak¹ opcje chcesz obstawic ? (zgodnie z poni¿szym opisem) :" << endl;
	cout << "p - parzyste" << endl;
	cout << "n - nieparzyste" << endl;
	cout << "r - czerwone(red)" << endl;
	cout << "b - czarne(black)" << endl;
	cout << "g - górna po³owa" << endl;
	cout << "d - dolna po³owa" << endl;
	cout << "k1, k2, k3 - kolumna 1, kolumna 2, kolumna 3" << endl;
	cout << "w1, w2, ..., w12 - wiersz trzech numerów" << endl;
	cout << "0 - 36 - pojedyncze pole o odpowiednim numerze" << endl;
	cin >> a;



	return a;
}

void Wczytaj_kwotê_zak³adu(int & kwota_zak³adu, int & iloœæ_pieniêdzy) {
	string k;
	while (true)
	{
		cout << "Masz " << iloœæ_pieniêdzy << "$, jak¹ kwotê chcesz obstawiæ wynik?" << endl;
		cin >> k;
		kwota_zak³adu = atoi(k.c_str());
		if (kwota_zak³adu > 0 && kwota_zak³adu <= iloœæ_pieniêdzy)
			break;
		else
			if (kwota_zak³adu == 0)
			{
				bool czy_zero = 1;
				for (short i = 0; i < k.size(); i++)
					if (k[i] != '0')
					{
						cout << "Wprowadzi³eæ nieprawid³ow¹ wartoœæ" << endl;
						czy_zero=0;
						break;
					}
				if (czy_zero) cout << "Nie mo¿esz obstawiæ zerowego zak³adu" << endl;
			}
			else if (kwota_zak³adu > iloœæ_pieniêdzy) cout << "Nie masz tyle pieniêdzy" << endl;
			else if (kwota_zak³adu < 0) cout << "Nie mo¿esz obstawiæ ujemn¹ kwot¹ zak³adu" << endl;
	}
}