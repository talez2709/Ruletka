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

#define iloœæ_minimalna_obrotów_ruletki 2
#define iloœæ_max_dodatkowych_obrotów_ruletki 3
#define czas_przeskoku_kulki_szybki 100
#define czas_przeskoku_kulki_wolny 200
#define czas_przerwy_dzwiêku 500

using namespace std;

string Obstaw(int & iloœæ_pieniêdzy);
void Wczytaj_Kwotê_Zak³adu(int & kwota, int & iloœæ_pieniêdzy);
int Zakrêæ_Ruletk¹();
int SprawdŸ_Zak³ad(int & kwota, string typ_zak³adu, int wylosowana_liczba);
bool Czy_Kontynuowaæ(int & iloœæ_pieniêdzy);

void Change_Col(int num_of_col);

const int Ruletka_ko³o[] = { 0, 32, 15, 19, 4, 21, 2, 25, 17, 34, 6, 27, 13, 36, 11, 30, 8, 23, 10, 5, 24, 16, 33, 1, 20, 14, 31, 9, 22, 18, 29, 7, 28, 12, 35, 3, 26 };
const char Ruletka_plansza_kolor[] = { 'g','r','b','r','b','r','b','r','b','r','b','b','r','b','r','b','r','b','r','r','b','r','b','r','b','r','b','r','b','b','r','b','r','b','r','b','r' };
int Ruletka_plansza_kolor_col[] = { 0,4,8,4,8,4,8,4,8,4,8,8,4,8,4,8,4,8,4,4,8,4,8,4,8,4,8,4,8,8,4,8,4,8,4,8,4 };

SYSTEMTIME Czas;

int main() {

	setlocale(LC_ALL, "polish");
	srand((unsigned int)time(NULL));
	GetSystemTime(&Czas);

	ofstream log_ogólny;
	log_ogólny.open("log_ogólny.txt", ios::app);
	fstream log;
	int iloœæ_pieniêdzy = 1000, kwota_zak³adu, wylosowana_liczba, wygrana;
	string typ_zak³adu;
	char co_kontynuowaæ = 'n';


	if (!_access("log_aktualny.txt", 0)) /* Sprawdzenie dostêpu do pliku (je¿eli takowy istnieje, musi istnieæ plik) */
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
			co_kontynuowaæ = 'n';
			int pocz¹tek = (int)buf.size();
			while (buf[pocz¹tek] != ' ' && pocz¹tek > 0) --pocz¹tek;
			++pocz¹tek;
			string buf2 = buf;
			buf2.erase(0, pocz¹tek);
			buf2.erase(buf2.size() - 1, 1);
			iloœæ_pieniêdzy = atoi(buf2.c_str());
		}
		else if (buf.find("Wylosowano") != string::npos)
		{
			co_kontynuowaæ = 'w';
			int pocz¹tek = 0;
			while (buf[pocz¹tek] != 'y' && pocz¹tek < buf.size()) ++pocz¹tek;
			pocz¹tek += 10;
			string buf2 = buf;
			buf2.erase(0, pocz¹tek);
			wylosowana_liczba = atoi(buf2.c_str());
			pocz¹tek = 0;
			while (buf[pocz¹tek] != 'd' && pocz¹tek < buf.size()) ++pocz¹tek;
			pocz¹tek += 2;
			buf2 = buf;
			buf2.erase(0, pocz¹tek);
			typ_zak³adu = buf2;
			buf.erase(buf.find("Obstawiono zaklad"), buf.size() - buf.find("Obstawiono zaklad"));
			pocz¹tek = 0;
			if (buf[12] == 'a') { pocz¹tek = 14; }
			else
			{
				while (buf[pocz¹tek] != 'z' && pocz¹tek < buf.size()) ++pocz¹tek;
				pocz¹tek += 3;
			}
			int koniec = pocz¹tek + 1;
			while (buf[koniec] != '$' && koniec < buf.size()) koniec++;
			buf2 = buf;
			buf2.erase(koniec, buf2.size() - koniec);
			buf2.erase(0, pocz¹tek);
			kwota_zak³adu = atoi(buf2.c_str());
		}
		else if (buf.find("Obstawiono zaklad") != string::npos)
		{
			co_kontynuowaæ = 't';
			int pocz¹tek = 0;
			while (buf[pocz¹tek] != 'd' && pocz¹tek < buf.size()) ++pocz¹tek;
			pocz¹tek += 2;
			string buf2 = buf;
			buf2.erase(0, pocz¹tek);
			typ_zak³adu = buf2;
			buf.erase(buf.find("Obstawiono zaklad"), buf.size() - buf.find("Obstawiono zaklad"));
			pocz¹tek = 0;
			if (buf[12] == 'a') { pocz¹tek = 14; }
			else
			{
				while (buf[pocz¹tek] != 'z' && pocz¹tek < buf.size()) ++pocz¹tek;
				pocz¹tek += 3;
			}
			int koniec = pocz¹tek + 1;
			while (buf[koniec] != '$' && koniec < buf.size()) koniec++;
			buf2 = buf;
			buf2.erase(koniec, buf2.size() - koniec);
			buf2.erase(0, pocz¹tek);
			kwota_zak³adu = atoi(buf2.c_str());
		}
		else if (buf.find("Obstawiono za") != string::npos)
		{
			co_kontynuowaæ = 'k';
			int pocz¹tek = 0;
			if (buf[12] == 'a') { pocz¹tek = 14; }
			else
			{
				while (buf[pocz¹tek] != 'z' && pocz¹tek < buf.size()) ++pocz¹tek;
				pocz¹tek += 3;
			}
			int koniec = pocz¹tek + 1;
			while (buf[koniec] != '$' && koniec < buf.size()) koniec++;
			string buf2 = buf;
			buf2.erase(koniec, buf2.size() - koniec);
			buf2.erase(0, pocz¹tek);
			kwota_zak³adu = atoi(buf2.c_str());
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
		log_ogólny << "Nowa gra rozpoczeta dnia " << Czas.wDay << "." << Czas.wMonth << "." << Czas.wYear << " o godzinie ";
		if (Czas.wHour < 10) log_ogólny << "0";
		log_ogólny << Czas.wHour << ":";
		if (Czas.wMinute < 10) log_ogólny << "0";
		log_ogólny << Czas.wMinute << ":";
		if (Czas.wSecond < 10) log_ogólny << "0";
		log_ogólny << Czas.wSecond << endl;
		log.flush();
		log_ogólny.flush();
		co_kontynuowaæ = 'n';
	}




	//	while (1);

	do
	{
		if (co_kontynuowaæ == 'n') Wczytaj_Kwotê_Zak³adu(kwota_zak³adu, iloœæ_pieniêdzy);
		else cout << "Obstawiono za " << kwota_zak³adu << "$" << endl;
		if (co_kontynuowaæ == 'n') log << "Obstawiono za " << kwota_zak³adu << "$";
		if (co_kontynuowaæ == 'n') log_ogólny << "Obstawiono za " << kwota_zak³adu << "$";
		log.flush();
		log_ogólny.flush();
		if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k') typ_zak³adu = Obstaw(iloœæ_pieniêdzy);
		else cout << "Obstawiono zak³ad " << typ_zak³adu << endl;
		if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k') log << " Obstawiono zaklad " << typ_zak³adu;
		if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k') log_ogólny << " Obstawiono zaklad " << typ_zak³adu;
		log.flush();
		log_ogólny.flush();
		if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k') iloœæ_pieniêdzy -= kwota_zak³adu;
		if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k' || co_kontynuowaæ == 't') cout << "Kulka w grze, zaczekaj na wylosowanie numeru..." << endl;
		if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k' || co_kontynuowaæ == 't') wylosowana_liczba = Zakrêæ_Ruletk¹();
		else {
			cout << "Wylosowano numer ";
			Change_Col(Ruletka_plansza_kolor_col[wylosowana_liczba]);
			cout << wylosowana_liczba;
			Change_Col(7);
			cout << ". ";
		}
		if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k' || co_kontynuowaæ == 't') log << " Wylosowano " << wylosowana_liczba;
		if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k' || co_kontynuowaæ == 't') log_ogólny << " Wylosowano " << wylosowana_liczba;
		log.flush();
		log_ogólny.flush();
		if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k' || co_kontynuowaæ == 't' || co_kontynuowaæ == 'w') wygrana = SprawdŸ_Zak³ad(kwota_zak³adu, typ_zak³adu, wylosowana_liczba);
		if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k' || co_kontynuowaæ == 't' || co_kontynuowaæ == 'w')
			if (wygrana > kwota_zak³adu)
			{
				log_ogólny << " Wygrywasz " << wygrana << "$";
				log << " Wygrywasz " << wygrana << "$";
				cout << "\a";
				iloœæ_pieniêdzy += wygrana;
				log << " Posiadasz " << iloœæ_pieniêdzy << "$" << endl;
				log_ogólny << " Posiadasz " << iloœæ_pieniêdzy << "$" << endl;
				log.flush();
				log_ogólny.flush();
				Sleep(czas_przerwy_dzwiêku);
				cout << "\a";
				Sleep(czas_przerwy_dzwiêku);
				cout << "\a";
			}
			else if (wygrana == kwota_zak³adu / 2)
			{
				log_ogólny << " Dostajesz polowe zak³adu " << wygrana << "$";
				log << " Dostajesz polowe zak³adu " << wygrana << "$";
				iloœæ_pieniêdzy += wygrana;
				log << " Posiadasz " << iloœæ_pieniêdzy << "$" << endl;
				log_ogólny << " Posiadasz " << iloœæ_pieniêdzy << "$" << endl;
				log.flush();
				log_ogólny.flush();
				cout << "\a";
				Sleep(czas_przerwy_dzwiêku);
				cout << "\a";
			}
			else if (wygrana == kwota_zak³adu)
			{
				log_ogólny << " Wygrywasz " << wygrana << "$";
				log << " Wygrywasz " << wygrana << "$";
				iloœæ_pieniêdzy += wygrana;
				log << " Posiadasz " << iloœæ_pieniêdzy << "$" << endl;
				log_ogólny << " Posiadasz " << iloœæ_pieniêdzy << "$" << endl;
				log.flush();
				log_ogólny.flush();
				cout << "\a";
				Sleep(czas_przerwy_dzwiêku);
				cout << "\a";
				Sleep(czas_przerwy_dzwiêku);
				cout << "\a";
			}
			else if (wygrana == 0)
			{
				log_ogólny << " Przegrales " << kwota_zak³adu << "$";
				log << " Przegrales " << kwota_zak³adu << "$";
				iloœæ_pieniêdzy += wygrana;
				log << " Posiadasz " << iloœæ_pieniêdzy << "$" << endl;
				log_ogólny << " Posiadasz " << iloœæ_pieniêdzy << "$" << endl;
				log.flush();
				log.flush();
				log_ogólny.flush();
				cout << "\a";
			}
		co_kontynuowaæ = 'n';
	} while (Czy_Kontynuowaæ(iloœæ_pieniêdzy));

	cout << endl << "Koñczysz gre z wynikiem " << iloœæ_pieniêdzy << "$" << endl;
	log << endl << "Koñczysz gre z wynikiem " << iloœæ_pieniêdzy << "$" << endl;
	log_ogólny << "Koñczysz gre z wynikiem " << iloœæ_pieniêdzy << "$" << endl;
	log.flush();
	log_ogólny.flush();
	log.close();
	remove("log_aktualny.txt");


	system("pause");
	return 0;
}

string Obstaw(int & iloœæ_pieniêdzy) {
	string zaklad_typ;
	do {
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

void Wczytaj_Kwotê_Zak³adu(int & kwota_zak³adu, int & iloœæ_pieniêdzy) {
	string kwota_zak³adu_s;
	while (true)
	{
		cout << "Masz " << iloœæ_pieniêdzy << "$, jak¹ kwotê chcesz obstawiæ wynik?" << endl;
		cin >> kwota_zak³adu_s;
		kwota_zak³adu = atoi(kwota_zak³adu_s.c_str());
		if (kwota_zak³adu > 0 && kwota_zak³adu <= iloœæ_pieniêdzy)
			break;
		else
			if (kwota_zak³adu == 0)
			{
				bool czy_zero = 1;
				for (short i = 0; i < kwota_zak³adu_s.size(); i++)
					if (kwota_zak³adu_s[i] != '0')
					{
						cout << "Wprowadzi³eæ nieprawid³ow¹ wartoœæ" << endl;
						czy_zero = 0;
						break;
					}
				if (czy_zero) cout << "Nie mo¿esz obstawiæ zerowego zak³adu" << endl;
			}
			else if (kwota_zak³adu > iloœæ_pieniêdzy) cout << "Nie masz tyle pieniêdzy" << endl;
			else if (kwota_zak³adu < 0) cout << "Nie mo¿esz obstawiæ ujemn¹ kwot¹ zak³adu" << endl;
	}
}

int Zakrêæ_Ruletk¹() {
	int iloœæ_zakrêceñ = rand() % (iloœæ_max_dodatkowych_obrotów_ruletki - 1) + iloœæ_minimalna_obrotów_ruletki;
	for (int i = 0; i < iloœæ_zakrêceñ; ++i)
		for (int ii = 0; ii < 37; ++ii)
		{
			Change_Col(Ruletka_plansza_kolor_col[Ruletka_ko³o[ii]]);
			cout << Ruletka_ko³o[ii];
			Sleep(czas_przeskoku_kulki_szybki);
			Change_Col(7);
			cout << "\b\b" << "  " << "\b\b";
		}
	int wylosowana_liczba = rand() % 37;
	for (int ii = 0; ii < wylosowana_liczba; ++ii)
	{
		Change_Col(Ruletka_plansza_kolor_col[Ruletka_ko³o[ii]]);
		cout << Ruletka_ko³o[ii];
		Sleep(czas_przeskoku_kulki_wolny);
		Change_Col(7);
		cout << "\b\b" << "  " << "\b\b";

	}
	cout << "Wylosowano numer ";
	Change_Col(Ruletka_plansza_kolor_col[Ruletka_ko³o[wylosowana_liczba]]);
	cout << Ruletka_ko³o[wylosowana_liczba];
	Change_Col(7);
	cout << ". ";
	return Ruletka_ko³o[wylosowana_liczba];
}

int SprawdŸ_Zak³ad(int & kwota, string typ_zak³adu, int wylosowana_liczba) {
	int wygrana = kwota;

	if (typ_zak³adu == "p")
		if (wylosowana_liczba % 2 == 0 && wylosowana_liczba != 0) wygrana *= 1;
		else if (wylosowana_liczba == 0) wygrana /= 2;
		else wygrana *= 0;
	else if (typ_zak³adu == "n")
		if (wylosowana_liczba % 2 == 1 && wylosowana_liczba != 0) wygrana *= 1;
		else if (wylosowana_liczba == 0) wygrana /= 2;
		else wygrana *= 0;
	else if (typ_zak³adu == "r")
		if (Ruletka_plansza_kolor[wylosowana_liczba] == 'r' && wylosowana_liczba != 0) wygrana *= 1;
		else if (wylosowana_liczba == 0) wygrana /= 2;
		else wygrana *= 0;
	else if (typ_zak³adu == "b")
		if (Ruletka_plansza_kolor[wylosowana_liczba] == 'b' && wylosowana_liczba != 0) wygrana *= 1;
		else if (wylosowana_liczba == 0) wygrana /= 2;
		else wygrana *= 0;
	else if (typ_zak³adu == "g")
		if (wylosowana_liczba < 19 && wylosowana_liczba != 0) wygrana *= 1;
		else if (wylosowana_liczba == 0) wygrana /= 2;
		else wygrana *= 0;
	else if (typ_zak³adu == "d")
		if (wylosowana_liczba > 18 && wylosowana_liczba != 0) wygrana *= 1;
		else if (wylosowana_liczba == 0) wygrana /= 2;
		else wygrana *= 0;
	else if (typ_zak³adu[0] == 'k')
		if (wylosowana_liczba % 3 == typ_zak³adu[1] - 49 && wylosowana_liczba != 0) wygrana *= 2;
		else if (wylosowana_liczba == 0) wygrana *= 0;
		else wygrana *= 0;
	else if (typ_zak³adu[0] == 'w')
		if (wylosowana_liczba >= ((atoi(typ_zak³adu.erase(1, 1).c_str()) - 1) * 3 + 1) && wylosowana_liczba <= (atoi(typ_zak³adu.erase(1, 1).c_str()) * 3) && wylosowana_liczba != 0) wygrana *= 11;
		else if (wylosowana_liczba == 0) wygrana *= 0;
		else wygrana *= 0;
	else if (wylosowana_liczba == atoi(typ_zak³adu.c_str())) wygrana *= 35;
	else wygrana *= 0;

	if (wygrana > kwota) cout << "Obstawiles poprawnie, wygrywasz " << wygrana << "$." << endl;
	else if (wygrana == kwota / 2) cout << "Obstawiles niepoprawnie, dostajesz po³owê zak³adu " << wygrana << "$." << endl;
	else if (wygrana == kwota) cout << "Obstawiles poprawnie, wygrywasz " << wygrana << "$." << endl;
	else if (wygrana == 0) cout << "Obstawiles niepoprawnie, przegra³eœ " << kwota << "$." << endl;

	return wygrana;
}

bool Czy_Kontynuowaæ(int & iloœæ_pieniêdzy) {
	string tak_nie;
	if (iloœæ_pieniêdzy == 0) {
		cout << "Nie mo¿esz kontynuowaæ, przegra³eœ wzystko" << endl;
		return 0;
	}
	while (true)
	{
		cout << "Na koncie masz " << iloœæ_pieniêdzy << "$, czy chcesz grac dalej('t' - tak, 'n' - nie) ?" << endl;
		cin >> tak_nie;
		if (tak_nie == "t" || tak_nie == "n" || tak_nie == "tak" || tak_nie == "nie" || tak_nie == "Tak" || tak_nie == "Nie")
			if (tak_nie[0] == 't' || tak_nie[0] == 'T') return 1;
			else return 0;
	}
}

void Change_Col(int num_of_col) {
	// 0 - czarny 1 - niebieski 2 - zielony 3 - b³êkitny 4 - czerwony 5 - purpurowy 6 - ¿ó³ty 7 - bia³y 8 - szary 9 - jasnoniebieski 10 - jasnozielony 11 - jasnob³êkitny 12 - jasnoczerwony 13 - jasnopurpurowy 14 - jasno¿ó³ty 15 - jaskrawobia³y
	HANDLE h_wyj;
	h_wyj = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h_wyj, num_of_col);
}

