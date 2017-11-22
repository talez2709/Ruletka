#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <locale.h>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <string>
#include <cstdio>
#include <ctime>
#include <io.h>

#define ilo��_minimalna_obrot�w_ruletki 2
#define ilo��_max_dodatkowych_obrot�w_ruletki 3
#define czas_przeskoku_kulki_szybki 100
#define czas_przeskoku_kulki_wolny 200
#define czas_przerwy_dzwi�ku 500

using namespace std;

string Obstaw(int & ilo��_pieni�dzy);
void Wczytaj_Kwot�_Zak�adu(int & kwota, int & ilo��_pieni�dzy);
int Zakr��_Ruletk�();
int Sprawd�_Zak�ad(int & kwota, string typ_zak�adu, int wylosowana_liczba);
bool Czy_Kontynuowa�(int & ilo��_pieni�dzy);

void Change_Col(int num_of_col);

const int Ruletka_ko�o[] = { 0, 32, 15, 19, 4, 21, 2, 25, 17, 34, 6, 27, 13, 36, 11, 30, 8, 23, 10, 5, 24, 16, 33, 1, 20, 14, 31, 9, 22, 18, 29, 7, 28, 12, 35, 3, 26 };
const char Ruletka_plansza_kolor[] = { 'g','r','b','r','b','r','b','r','b','r','b','b','r','b','r','b','r','b','r','r','b','r','b','r','b','r','b','r','b','b','r','b','r','b','r','b','r' };
int Ruletka_plansza_kolor_col[] = { 0,4,8,4,8,4,8,4,8,4,8,8,4,8,4,8,4,8,4,4,8,4,8,4,8,4,8,4,8,8,4,8,4,8,4,8,4 };

SYSTEMTIME Czas;

int main() {

	setlocale(LC_ALL, "polish");
	srand((unsigned int)time(NULL));
	GetSystemTime(&Czas);

	ofstream log_og�lny;
	log_og�lny.open("log_og�lny.txt", ios::app);
	fstream log;
	int ilo��_pieni�dzy = 1000, kwota_zak�adu, wylosowana_liczba, wygrana;
	string typ_zak�adu;
	char co_kontynuowa� = 'n';


	if (!_access("log_aktualny.txt", 0)) /* Sprawdzenie dost�pu do pliku (je�eli takowy istnieje, musi istnie� plik) */
	{
		log.open("log_aktualny.txt", ios::in);
		string buf, buf2;
		while (!log.eof())
		{
			getline(log, buf);
			if (buf != "") buf2 = buf;
			else continue;

		}
		if (buf == "") buf = buf2;
		if (buf.find("Posiadasz") != string::npos || buf.find("Przegrales") != string::npos || buf.find("Wygrywasz") != string::npos)
		{
			co_kontynuowa� = 'n';
			int pocz�tek = (int)buf.size();
			while (buf[pocz�tek] != ' ' && pocz�tek > 0) --pocz�tek;
			++pocz�tek;
			string buf2 = buf;
			buf2.erase(0, pocz�tek);
			buf2.erase(buf2.size() - 1, 1);
			ilo��_pieni�dzy = atoi(buf2.c_str());
		}
		else if (buf.find("Wylosowano") != string::npos)
		{
			co_kontynuowa� = 'w';
			int pocz�tek = 0;
			while (buf[pocz�tek] != 'y' && pocz�tek < buf.size()) ++pocz�tek;
			pocz�tek += 10;
			string buf2 = buf;
			buf2.erase(0, pocz�tek);
			wylosowana_liczba = atoi(buf2.c_str());
			pocz�tek = 0;
			while (buf[pocz�tek] != 'd' && pocz�tek < buf.size()) ++pocz�tek;
			pocz�tek += 2;
			buf2 = buf;
			buf2.erase(0, pocz�tek);
			typ_zak�adu = buf2;
			buf.erase(buf.find("Obstawiono zaklad"), buf.size() - buf.find("Obstawiono zaklad"));
			pocz�tek = 0;
			if (buf[12] == 'a') { pocz�tek = 14; }
			else
			{
				while (buf[pocz�tek] != 'z' && pocz�tek < buf.size()) ++pocz�tek;
				pocz�tek += 3;
			}
			int koniec = pocz�tek + 1;
			while (buf[koniec] != '$' && koniec < buf.size()) koniec++;
			buf2 = buf;
			buf2.erase(koniec, buf2.size() - koniec);
			buf2.erase(0, pocz�tek);
			kwota_zak�adu = atoi(buf2.c_str());
		}
		else if (buf.find("Obstawiono zaklad") != string::npos)
		{
			co_kontynuowa� = 't';
			int pocz�tek = 0;
			while (buf[pocz�tek] != 'd' && pocz�tek < buf.size()) ++pocz�tek;
			pocz�tek += 2;
			string buf2 = buf;
			buf2.erase(0, pocz�tek);
			typ_zak�adu = buf2;
			buf.erase(buf.find("Obstawiono zaklad"), buf.size() - buf.find("Obstawiono zaklad"));
			pocz�tek = 0;
			if (buf[12] == 'a') { pocz�tek = 14; }
			else
			{
				while (buf[pocz�tek] != 'z' && pocz�tek < buf.size()) ++pocz�tek;
				pocz�tek += 3;
			}
			int koniec = pocz�tek + 1;
			while (buf[koniec] != '$' && koniec < buf.size()) koniec++;
			buf2 = buf;
			buf2.erase(koniec, buf2.size() - koniec);
			buf2.erase(0, pocz�tek);
			kwota_zak�adu = atoi(buf2.c_str());
		}
		else if (buf.find("Obstawiono za") != string::npos)
		{
			co_kontynuowa� = 'k';
			int pocz�tek = 0;
			if (buf[12] == 'a') { pocz�tek = 14; }
			else
			{
				while (buf[pocz�tek] != 'z' && pocz�tek < buf.size()) ++pocz�tek;
				pocz�tek += 3;
			}
			int koniec = pocz�tek + 1;
			while (buf[koniec] != '$' && koniec < buf.size()) koniec++;
			string buf2 = buf;
			buf2.erase(koniec, buf2.size() - koniec);
			buf2.erase(0, pocz�tek);
			kwota_zak�adu = atoi(buf2.c_str());
		}
		log.close();
		log.open("log_aktualny.txt", ios::out | ios::app);
	}
	else
	{
		log.open("log_aktualny.txt", ios::out);
		GetSystemTime(&Czas);
		log << "Gra rozpoczeta dnia " << Czas.wDay << "." << Czas.wMonth << "." << Czas.wYear << " o godzinie ";
		if (Czas.wHour < 10) log << "0";
		log << Czas.wHour << ":";
		if (Czas.wMinute < 10) log << "0";
		log << Czas.wMinute << ":";
		if (Czas.wSecond < 10) log << "0";
		log << Czas.wSecond << endl;
		log_og�lny << "Nowa gra rozpoczeta dnia " << Czas.wDay << "." << Czas.wMonth << "." << Czas.wYear << " o godzinie ";
		if (Czas.wHour < 10) log_og�lny << "0";
		log_og�lny << Czas.wHour << ":";
		if (Czas.wMinute < 10) log_og�lny << "0";
		log_og�lny << Czas.wMinute << ":";
		if (Czas.wSecond < 10) log_og�lny << "0";
		log_og�lny << Czas.wSecond << endl;
		log.flush();
		log_og�lny.flush();
		co_kontynuowa� = 'n';
	}




	//	while (1);

	do
	{
		if (co_kontynuowa� == 'n') Wczytaj_Kwot�_Zak�adu(kwota_zak�adu, ilo��_pieni�dzy);
		else cout << "Obstawiono za " << kwota_zak�adu << "$" << endl;
		if (co_kontynuowa� == 'n') log << "Obstawiono za " << kwota_zak�adu << "$";
		if (co_kontynuowa� == 'n') log_og�lny << "Obstawiono za " << kwota_zak�adu << "$";
		log.flush();
		log_og�lny.flush();
		if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k') typ_zak�adu = Obstaw(ilo��_pieni�dzy);
		else cout << "Obstawiono zak�ad " << typ_zak�adu << endl;
		if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k') log << " Obstawiono zaklad " << typ_zak�adu;
		if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k') log_og�lny << " Obstawiono zaklad " << typ_zak�adu;
		log.flush();
		log_og�lny.flush();
		if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k') ilo��_pieni�dzy -= kwota_zak�adu;
		if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k' || co_kontynuowa� == 't') cout << "Kulka w grze, zaczekaj na wylosowanie numeru..." << endl;
		if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k' || co_kontynuowa� == 't') wylosowana_liczba = Zakr��_Ruletk�();
		else {
			cout << "Wylosowano numer ";
			Change_Col(Ruletka_plansza_kolor_col[wylosowana_liczba]);
			cout << wylosowana_liczba;
			Change_Col(7);
			cout << ". ";
		}
		if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k' || co_kontynuowa� == 't') log << " Wylosowano " << wylosowana_liczba;
		if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k' || co_kontynuowa� == 't') log_og�lny << " Wylosowano " << wylosowana_liczba;
		log.flush();
		log_og�lny.flush();
		if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k' || co_kontynuowa� == 't' || co_kontynuowa� == 'w') wygrana = Sprawd�_Zak�ad(kwota_zak�adu, typ_zak�adu, wylosowana_liczba);
		if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k' || co_kontynuowa� == 't' || co_kontynuowa� == 'w')
			if (wygrana > kwota_zak�adu)
			{
				log_og�lny << " Wygrywasz " << wygrana << "$";
				log << " Wygrywasz " << wygrana << "$";
				cout << "\a";
				ilo��_pieni�dzy += wygrana;
				log << " Posiadasz " << ilo��_pieni�dzy << "$" << endl;
				log_og�lny << " Posiadasz " << ilo��_pieni�dzy << "$" << endl;
				log.flush();
				log_og�lny.flush();
				Sleep(czas_przerwy_dzwi�ku);
				cout << "\a";
				Sleep(czas_przerwy_dzwi�ku);
				cout << "\a";
			}
			else if (wygrana == kwota_zak�adu / 2)
			{
				log_og�lny << " Dostajesz polowe zak�adu " << wygrana << "$";
				log << " Dostajesz polowe zak�adu " << wygrana << "$";
				ilo��_pieni�dzy += wygrana;
				log << " Posiadasz " << ilo��_pieni�dzy << "$" << endl;
				log_og�lny << " Posiadasz " << ilo��_pieni�dzy << "$" << endl;
				log.flush();
				log_og�lny.flush();
				cout << "\a";
				Sleep(czas_przerwy_dzwi�ku);
				cout << "\a";
			}
			else if (wygrana == kwota_zak�adu)
			{
				log_og�lny << " Wygrywasz " << wygrana << "$";
				log << " Wygrywasz " << wygrana << "$";
				ilo��_pieni�dzy += wygrana;
				log << " Posiadasz " << ilo��_pieni�dzy << "$" << endl;
				log_og�lny << " Posiadasz " << ilo��_pieni�dzy << "$" << endl;
				log.flush();
				log_og�lny.flush();
				cout << "\a";
				Sleep(czas_przerwy_dzwi�ku);
				cout << "\a";
				Sleep(czas_przerwy_dzwi�ku);
				cout << "\a";
			}
			else if (wygrana == 0)
			{
				log_og�lny << " Przegrales " << kwota_zak�adu << "$";
				log << " Przegrales " << kwota_zak�adu << "$";
				ilo��_pieni�dzy += wygrana;
				log << " Posiadasz " << ilo��_pieni�dzy << "$" << endl;
				log_og�lny << " Posiadasz " << ilo��_pieni�dzy << "$" << endl;
				log.flush();
				log.flush();
				log_og�lny.flush();
				cout << "\a";
			}
		co_kontynuowa� = 'n';
	} while (Czy_Kontynuowa�(ilo��_pieni�dzy));

	cout << endl << "Ko�czysz gre z wynikiem " << ilo��_pieni�dzy << "$" << endl;
	log << endl << "Ko�czysz gre z wynikiem " << ilo��_pieni�dzy << "$" << endl;
	log_og�lny << "Ko�czysz gre z wynikiem " << ilo��_pieni�dzy << "$" << endl;
	log.flush();
	log_og�lny.flush();
	log.close();
	remove("log_aktualny.txt");


	system("pause");
	return 0;
}

string Obstaw(int & ilo��_pieni�dzy) {
	string zaklad_typ;
	do {
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
		cin >> zaklad_typ;
	} while (!(
		zaklad_typ == "p" ||
		zaklad_typ == "n" ||
		zaklad_typ == "r" ||
		zaklad_typ == "b" ||
		zaklad_typ == "g" ||
		zaklad_typ == "d" ||
		zaklad_typ == "k1" ||
		zaklad_typ == "k2" ||
		zaklad_typ == "k3" ||
		zaklad_typ == "w1" ||
		zaklad_typ == "w2" ||
		zaklad_typ == "w3" ||
		zaklad_typ == "w4" ||
		zaklad_typ == "w5" ||
		zaklad_typ == "w6" ||
		zaklad_typ == "w7" ||
		zaklad_typ == "w8" ||
		zaklad_typ == "w9" ||
		zaklad_typ == "w10" ||
		zaklad_typ == "w11" ||
		zaklad_typ == "w12" ||
		zaklad_typ == "0" ||
		zaklad_typ == "1" ||
		zaklad_typ == "2" ||
		zaklad_typ == "3" ||
		zaklad_typ == "4" ||
		zaklad_typ == "5" ||
		zaklad_typ == "6" ||
		zaklad_typ == "7" ||
		zaklad_typ == "8" ||
		zaklad_typ == "9" ||
		zaklad_typ == "10" ||
		zaklad_typ == "11" ||
		zaklad_typ == "12" ||
		zaklad_typ == "13" ||
		zaklad_typ == "14" ||
		zaklad_typ == "15" ||
		zaklad_typ == "16" ||
		zaklad_typ == "17" ||
		zaklad_typ == "18" ||
		zaklad_typ == "19" ||
		zaklad_typ == "20" ||
		zaklad_typ == "21" ||
		zaklad_typ == "22" ||
		zaklad_typ == "23" ||
		zaklad_typ == "24" ||
		zaklad_typ == "25" ||
		zaklad_typ == "26" ||
		zaklad_typ == "27" ||
		zaklad_typ == "28" ||
		zaklad_typ == "29" ||
		zaklad_typ == "30" ||
		zaklad_typ == "31" ||
		zaklad_typ == "32"
		));
	return zaklad_typ;
}

void Wczytaj_Kwot�_Zak�adu(int & kwota_zak�adu, int & ilo��_pieni�dzy) {
	string kwota_zak�adu_s;
	while (true)
	{
		cout << "Masz " << ilo��_pieni�dzy << "$, jak� kwot� chcesz obstawi� wynik?" << endl;
		cin >> kwota_zak�adu_s;
		kwota_zak�adu = atoi(kwota_zak�adu_s.c_str());
		if (kwota_zak�adu > 0 && kwota_zak�adu <= ilo��_pieni�dzy)
			break;
		else
			if (kwota_zak�adu == 0)
			{
				bool czy_zero = 1;
				for (short i = 0; i < kwota_zak�adu_s.size(); i++)
					if (kwota_zak�adu_s[i] != '0')
					{
						cout << "Wprowadzi�e� nieprawid�ow� warto��" << endl;
						czy_zero = 0;
						break;
					}
				if (czy_zero) cout << "Nie mo�esz obstawi� zerowego zak�adu" << endl;
			}
			else if (kwota_zak�adu > ilo��_pieni�dzy) cout << "Nie masz tyle pieni�dzy" << endl;
			else if (kwota_zak�adu < 0) cout << "Nie mo�esz obstawi� ujemn� kwot� zak�adu" << endl;
	}
}

int Zakr��_Ruletk�() {
	int ilo��_zakr�ce� = rand() % (ilo��_max_dodatkowych_obrot�w_ruletki - 1) + ilo��_minimalna_obrot�w_ruletki;
	for (int i = 0; i < ilo��_zakr�ce�; ++i)
		for (int ii = 0; ii < 37; ++ii)
		{
			Change_Col(Ruletka_plansza_kolor_col[Ruletka_ko�o[ii]]);
			cout << Ruletka_ko�o[ii];
			Sleep(czas_przeskoku_kulki_szybki);
			Change_Col(7);
			cout << "\b\b" << "  " << "\b\b";
		}
	int wylosowana_liczba = rand() % 37;
	for (int ii = 0; ii < wylosowana_liczba; ++ii)
	{
		Change_Col(Ruletka_plansza_kolor_col[Ruletka_ko�o[ii]]);
		cout << Ruletka_ko�o[ii];
		Sleep(czas_przeskoku_kulki_wolny);
		Change_Col(7);
		cout << "\b\b" << "  " << "\b\b";

	}
	cout << "Wylosowano numer ";
	Change_Col(Ruletka_plansza_kolor_col[Ruletka_ko�o[wylosowana_liczba]]);
	cout << Ruletka_ko�o[wylosowana_liczba];
	Change_Col(7);
	cout << ". ";
	return Ruletka_ko�o[wylosowana_liczba];
}

int Sprawd�_Zak�ad(int & kwota, string typ_zak�adu, int wylosowana_liczba) {
	int wygrana = kwota;

	if (typ_zak�adu == "p")
		if (wylosowana_liczba % 2 == 0 && wylosowana_liczba != 0) wygrana *= 1;
		else if (wylosowana_liczba == 0) wygrana /= 2;
		else wygrana *= 0;
	else if (typ_zak�adu == "n")
		if (wylosowana_liczba % 2 == 1 && wylosowana_liczba != 0) wygrana *= 1;
		else if (wylosowana_liczba == 0) wygrana /= 2;
		else wygrana *= 0;
	else if (typ_zak�adu == "r")
		if (Ruletka_plansza_kolor[wylosowana_liczba] == 'r' && wylosowana_liczba != 0) wygrana *= 1;
		else if (wylosowana_liczba == 0) wygrana /= 2;
		else wygrana *= 0;
	else if (typ_zak�adu == "b")
		if (Ruletka_plansza_kolor[wylosowana_liczba] == 'b' && wylosowana_liczba != 0) wygrana *= 1;
		else if (wylosowana_liczba == 0) wygrana /= 2;
		else wygrana *= 0;
	else if (typ_zak�adu == "g")
		if (wylosowana_liczba < 19 && wylosowana_liczba != 0) wygrana *= 1;
		else if (wylosowana_liczba == 0) wygrana /= 2;
		else wygrana *= 0;
	else if (typ_zak�adu == "d")
		if (wylosowana_liczba > 18 && wylosowana_liczba != 0) wygrana *= 1;
		else if (wylosowana_liczba == 0) wygrana /= 2;
		else wygrana *= 0;
	else if (typ_zak�adu[0] == 'k')
		if (wylosowana_liczba % 3 == typ_zak�adu[1] - 49 && wylosowana_liczba != 0) wygrana *= 2;
		else if (wylosowana_liczba == 0) wygrana *= 0;
		else wygrana *= 0;
	else if (typ_zak�adu[0] == 'w')
		if (wylosowana_liczba >= ((atoi(typ_zak�adu.erase(1, 1).c_str()) - 1) * 3 + 1) && wylosowana_liczba <= (atoi(typ_zak�adu.erase(1, 1).c_str()) * 3) && wylosowana_liczba != 0) wygrana *= 11;
		else if (wylosowana_liczba == 0) wygrana *= 0;
		else wygrana *= 0;
	else if (wylosowana_liczba == atoi(typ_zak�adu.c_str())) wygrana *= 35;
	else wygrana *= 0;

	if (wygrana > kwota) cout << "Obstawiles poprawnie, wygrywasz " << wygrana << "$." << endl;
	else if (wygrana == kwota / 2) cout << "Obstawiles niepoprawnie, dostajesz po�ow� zak�adu " << wygrana << "$." << endl;
	else if (wygrana == kwota) cout << "Obstawiles poprawnie, wygrywasz " << wygrana << "$." << endl;
	else if (wygrana == 0) cout << "Obstawiles niepoprawnie, przegra�e� " << kwota << "$." << endl;

	return wygrana;
}

bool Czy_Kontynuowa�(int & ilo��_pieni�dzy) {
	string tak_nie;
	if (ilo��_pieni�dzy == 0) {
		cout << "Nie mo�esz kontynuowa�, przegra�e� wzystko" << endl;
		return 0;
	}
	while (true)
	{
		cout << "Na koncie masz " << ilo��_pieni�dzy << "$, czy chcesz grac dalej('t' - tak, 'n' - nie) ?" << endl;
		cin >> tak_nie;
		if (tak_nie == "t" || tak_nie == "n" || tak_nie == "tak" || tak_nie == "nie" || tak_nie == "Tak" || tak_nie == "Nie")
			if (tak_nie[0] == 't' || tak_nie[0] == 'T') return 1;
			else return 0;
	}
}

void Change_Col(int num_of_col) {
	// 0 - czarny 1 - niebieski 2 - zielony 3 - b��kitny 4 - czerwony 5 - purpurowy 6 - ��ty 7 - bia�y 8 - szary 9 - jasnoniebieski 10 - jasnozielony 11 - jasnob��kitny 12 - jasnoczerwony 13 - jasnopurpurowy 14 - jasno��ty 15 - jaskrawobia�y
	HANDLE h_wyj;
	h_wyj = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h_wyj, num_of_col);
}

