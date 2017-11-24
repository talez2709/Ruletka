//------------------ deklaracje bibiotek u�ywanych w programie -----------------------
#include <ctime> //time()
#include <fstream> //Obs�uga pliku
#include <io.h> //!_access()
#include <iostream> //Obs�uga strumenia cout,cin
#include <locale.h> //setlocale()
#include <string> //Obs�uga string�w
#include <windows.h> //SYSTEMTIME,GetSystemTime(),Sleep(),HANDLE,GetStdHandle(),SetConsoleTextAttribute()
//-------------------------------------------------------------------------------------

//--------- deklaracje plik�w nag��wkowych u�ywanych w programie ----------------------
#include "MT.h" //Generator liczb pseudolosowych Mersenne Twister
//-------------------------------------------------------------------------------------

//------ deklaracje definicji preprocesora do zmian funcjonowania programu ------------
#define ilo��_minimalna_obrot�w_ruletki 2 // Minimalna ilo�� obrot�w ruletki przed podaniem warto�ci wylosowanej
#define ilo��_max_dodatkowych_obrot�w_ruletki 3 // Maksymalna ilo�� dodatkowych obrot�w ruletki przed podaniem warto�ci wylosowanej
#define czas_przeskoku_kulki_szybki 100 //Czas w ms przerwy pomi�dzy przeskokami na pocz�tek losowania na kolejn� liczb� na kole ruletki
#define czas_przeskoku_kulki_wolny 200 //Czas w ms przerwy pomi�dzy przeskokami pod koniec losowania na kolejn� liczb� na kole ruletki
#define czas_przerwy_dzwi�ku 500 //Czas w ms przerwy pomi�dzy pikni�ciami oznaczaj�cymi wynik zak�adu
#define styl_liczenia_wygranej 1 //0 dla odejmowania w�o�onych w zak�ad pieni�dzy (przy tym zak�ady 1:1 nie zwi�kszaj� ilo��_pieni�dzy), 1 dla nie odejmowania (przy tym zak�ady 1:1 zwi�kszaj� ilo��_pieni�dzy)
#define kwota_pocz�tkowa 1000 //Ilo�� $ z kt�rymi zaczyna si� gre
//-------------------------------------------------------------------------------------

//-------------------------- deklaracja wyboru przestrzeni nazw std -------------------
using namespace std;
//-------------------------------------------------------------------------------------

//---------------------------------- deklaracje funkcji w�asnych ----------------------
string Obstaw(); //Funkcja wczytywania typu zak�ad, do string aby mie� tak�e zak�ady sk�adaj�ce si� z liter i cyfr
void Wczytaj_Kwot�_Zak�adu(int & kwota, int & ilo��_pieni�dzy); //Funkcja wczytywania kwoty zak�adu aby uchroni� si� przed problemem wpisania znaku,litery zamiast liczby i osbstawienie za wi�ksz� kwot� ni� si� ma
int Zakr��_Ruletk�(); //Funkcja losuje liczb� z ko�a ruletki
int Sprawd�_Zak�ad(int & kwota, string typ_zak�adu, int wylosowana_liczba); //Funcja sprawdza czy wygrali�my i podaje kwote wygranej/przegranej/odzysku cz�ci w�o�onych pieni�dzy
bool Czy_Kontynuowa�(int & ilo��_pieni�dzy); //Funkcja sprawdzj�ca czy ma si� �rodki do gry, je�eli ma si� to pyta czy chce si� gra� dalej
//-------------------------------------------------------------------------------------
//------------------------------- deklaracje funkcji obcych ---------------------------
void Change_Col(int num_of_col); //Funcja zmieniaj�ca kolor tekstu 0 - czarny 1 - niebieski 2 - zielony 3 - b��kitny 4 - czerwony 5 - purpurowy 6 - ��ty 7 - bia�y 8 - szary 9 - jasnoniebieski 10 - jasnozielony 11 - jasnob��kitny 12 - jasnoczerwony 13 - jasnopurpurowy 14 - jasno��ty 15 - jaskrawobia�y
void HideCursor();
void ShowCursor();
//-------------------------------------------------------------------------------------

//----------------------------- deklaracje tablic pomocniczych ------------------------
const int Ruletka_ko�o[] = { 0, 32, 15, 19, 4, 21, 2, 25, 17, 34, 6, 27, 13, 36, 11, 30, 8, 23, 10, 5, 24, 16, 33, 1, 20, 14, 31, 9, 22, 18, 29, 7, 28, 12, 35, 3, 26 };// Kolejno�� liczb zgodna z ko�em ruletki
const char Ruletka_plansza_kolor[] = { 'g','r','b','r','b','r','b','r','b','r','b','b','r','b','r','b','r','b','r','r','b','r','b','r','b','r','b','r','b','b','r','b','r','b','r','b','r' };// Kolor dla ka�dej liczby na planszy
int Ruletka_plansza_kolor_col[] = { 0,4,8,4,8,4,8,4,8,4,8,8,4,8,4,8,4,8,4,4,8,4,8,4,8,4,8,4,8,8,4,8,4,8,4,8,4 }; // Kod koloru do funkcji zmiany koloru tekstu dla ka�dej liczby na planszy
//-------------------------------------------------------------------------------------

//---------------------------- deklaracje zmiennych globalnych ------------------------
SYSTEMTIME Czas; //Struktura do kt�rej zapisywana jest aktualna data i czas
//-------------------------------------------------------------------------------------

int main() {
	//Inicjowanie funkcji
	setlocale(LC_ALL, "polish"); // W celu polskich liter w konsoli
	InicjujMT((unsigned int)time(NULL)); //Zainicjowanie generatorza MT (Mersenne-Twister) dla wa�nych liczb
	srand((unsigned int)time(NULL)); //Zainicjowanie generatorza LCG (Liniowy Generator Kongruentny) dla ma�o wa�nych liczb
	HideCursor(); //Ukrycie kursora tekstowego w konsoli

	ofstream log_og�lny; //Utworzenie typu do celu zapisu do pliku
	log_og�lny.open("log_og�lny.txt", ios::app); //Otworzenie pliku z ustawieniem kursora zapisu do pliku
	fstream log; //Utworzenie typu do celu zapisu i/lub odczytu do i/lub z pliku
	int ilo��_pieni�dzy = kwota_pocz�tkowa, kwota_zak�adu, wylosowana_liczba, wygrana; //Zmienne do kt�rych wczytuje si� warto�ci liczbowe pobrane od u�ytkownika takie jak kwota zak�adu a przechowuje ilo�� posiadanych pieni�dzy a tak�e przechowuje wyniki funcji losowania liczby z ruletki i kwote wygran� z zak�adu
	string typ_zak�adu; //Przechowuje typ zak�adu wprowadzony przez u�ytkownika
	char co_kontynuowa� = 'n'; //Przechowuje nazwan� znakiem od kt�rego punktu kontynuowa� runde

	if (!_access("log_aktualny.txt", 0)) // Sprawdzenie dost�pu do pliku (je�eli takowy istnieje, musi istnie� plik)
	{
		log.open("log_aktualny.txt", ios::in); //Otworzenie pliku w trybie odczytu z pliku
		string buf, buf2; //Uworzenie 2 bufor�w na tekst, pierwszy na ostatni� linie tekst, drugi na przedostani� nie pust� linie tekstu lub ostani� w przypadku gdy ostania jest pusta
		while (!log.eof()) //P�tla dzia�j�ca do czasu kiedy kursor odczytu z pliku nie b�dzie na ko�cu pliku
		{
			getline(log, buf); //Odczyt ca�ej lini z pliku
			if (buf != "") buf2 = buf; //Sprawdzenie czy odczytana linia nie jest pusta, je�eli nie jest pusta to skopiowanie do drugiego bufora celem posiadania dw�ch ostatnich linijek tekstu b�d�cego w pliku
		}
		if (buf == "") buf = buf2; //Sprawdzenie czy linia w buforze jest pusta, je�eli jest pusta to zastopienie jej poprzedni� lini� tekstu z pliku
		if (buf.find("Posiadasz") != string::npos || buf.find("Przegrales") != string::npos || buf.find("Wygrywasz") != string::npos) //Sprawdzenie czy w ostatniej niepustej lini znajduj� si� s�owa �wiadcz�ce o sko�czeniu rundy
		{
			co_kontynuowa� = 'n'; //Je�eli si� znajduj� to przypisanie znaku rozpocz�cia rundy od pocz�tku
			int pocz�tek = (int)buf.size(); //Utworzenie i przypisanie do zmiennej wskazuj�cej pocz�tek tekst o kwocie pieni�dzy kt�r� posiada jeszcze gracz
			while (buf[pocz�tek] != ' ' && pocz�tek > 0) --pocz�tek; //Poszukiwanie od ko�ca spacji po kt�rej jest kwota pieni�dzy kt�r� posiada jeszcze gracz
			++pocz�tek; //Kwota jest na nast�pnym znaku wi�c przesuni�cie o jeden znak do przodu
			string buf2 = buf; //Utworzenie bufora pomocniczego do ci�cia tekstu i w�o�enie do niego wcze�niej odczytanego tekstu
			buf2.erase(0, pocz�tek); //Usuni�cie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna� si� liczb�
			buf2.erase(buf2.size() - 1, 1); //Usuni�cie z bufora pomocniczego znaku dolara z prawej strony
			ilo��_pieni�dzy = atoi(buf2.c_str()); //Zamiana liczby w tek�cie na warto�� w zmiennnej liczbowej
		}
		else if (buf.find("Wylosowano") != string::npos)
		{
			co_kontynuowa� = 'w';
			int pocz�tek = 0;
			while (buf[pocz�tek] != 'y' && pocz�tek < (int)buf.size()) ++pocz�tek;
			pocz�tek += 10;
			string buf2 = buf;
			buf2.erase(0, pocz�tek);
			wylosowana_liczba = atoi(buf2.c_str());
			pocz�tek = 0;
			while (buf[pocz�tek] != 'd' && pocz�tek < (int)buf.size()) ++pocz�tek;
			pocz�tek += 2;
			buf2 = buf;
			buf2.erase(0, pocz�tek);
			typ_zak�adu = buf2;
			buf.erase(buf.find("Obstawiono zaklad"), buf.size() - buf.find("Obstawiono zaklad"));
			pocz�tek = 0;
			if (buf[12] == 'a') { pocz�tek = 14; }
			else
			{
				while (buf[pocz�tek] != 'z' && pocz�tek < (int)buf.size()) ++pocz�tek;
				pocz�tek += 3;
			}
			int koniec = pocz�tek + 1;
			while (buf[koniec] != '$' && koniec < (int)buf.size()) koniec++;
			buf2 = buf;
			buf2.erase(koniec, buf2.size() - koniec);
			buf2.erase(0, pocz�tek);
			kwota_zak�adu = atoi(buf2.c_str());
		}
		else if (buf.find("Obstawiono zaklad") != string::npos)
		{
			co_kontynuowa� = 't';
			int pocz�tek = 0;
			while (buf[pocz�tek] != 'd' && pocz�tek < (int)buf.size()) ++pocz�tek;
			pocz�tek += 2;
			string buf2 = buf;
			buf2.erase(0, pocz�tek);
			typ_zak�adu = buf2;
			buf.erase(buf.find("Obstawiono zaklad"), buf.size() - buf.find("Obstawiono zaklad"));
			pocz�tek = 0;
			if (buf[12] == 'a') { pocz�tek = 14; }
			else
			{
				while (buf[pocz�tek] != 'z' && pocz�tek < (int)buf.size()) ++pocz�tek;
				pocz�tek += 3;
			}
			int koniec = pocz�tek + 1;
			while (buf[koniec] != '$' && koniec < (int)buf.size()) koniec++;
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
				while (buf[pocz�tek] != 'z' && pocz�tek < (int)buf.size()) ++pocz�tek;
				pocz�tek += 3;
			}
			int koniec = pocz�tek + 1;
			while (buf[koniec] != '$' && koniec < (int)buf.size()) koniec++;
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
		GetSystemTime(&Czas); //Pobieranie aktualnej daty i czasu z zegara systemowego
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
	do
	{
		if (co_kontynuowa� == 'n') Wczytaj_Kwot�_Zak�adu(kwota_zak�adu, ilo��_pieni�dzy);
		else cout << "Obstawiono za " << kwota_zak�adu << "$" << endl;
		if (co_kontynuowa� == 'n') log << "Obstawiono za " << kwota_zak�adu << "$";
		if (co_kontynuowa� == 'n') log_og�lny << "Obstawiono za " << kwota_zak�adu << "$";
		log.flush();
		log_og�lny.flush();
		if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k') typ_zak�adu = Obstaw();
		else cout << "Obstawiono zak�ad " << typ_zak�adu << endl;
		if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k') log << " Obstawiono zaklad " << typ_zak�adu;
		if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k') log_og�lny << " Obstawiono zaklad " << typ_zak�adu;
		log.flush();
		log_og�lny.flush();
		if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k' || co_kontynuowa� == 't' || co_kontynuowa� == 'w') ilo��_pieni�dzy -= kwota_zak�adu;
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
			if (wygrana >= kwota_zak�adu)
			{
				log_og�lny << " Wygrywasz " << wygrana << "$";
				log << " Wygrywasz " << wygrana << "$";
				ilo��_pieni�dzy += wygrana;
#if styl_liczenia_wygranej == 1
				ilo��_pieni�dzy += kwota_zak�adu;
#endif // styl_liczenia_wygranej
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
			else if (wygrana == (kwota_zak�adu / 2))
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
			else if (wygrana == 0)
			{
				log_og�lny << " Przegrales " << kwota_zak�adu << "$";
				log << " Przegrales " << kwota_zak�adu << "$";
				log << " Posiadasz " << ilo��_pieni�dzy << "$" << endl;
				log_og�lny << " Posiadasz " << ilo��_pieni�dzy << "$" << endl;
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
	if (ilo��_pieni�dzy == 0)
		for (int i = 0; i < 5; ++i)
		{
			cout << "\a";
			Sleep(czas_przerwy_dzwi�ku);
		}
	if (ilo��_pieni�dzy > kwota_pocz�tkowa && ilo��_pieni�dzy < kwota_pocz�tkowa * 2) cout << "Gratuluje zwi�kszy�e� sw�j zas�b finansowy" << endl;
	else if (ilo��_pieni�dzy >= kwota_pocz�tkowa * 2) cout << "Gratuluje zwi�kszy�e� " << ilo��_pieni�dzy / kwota_pocz�tkowa << " krotnie sw�j zas�b finansowy" << endl;
	system("pause");
	return 0;
}

string Obstaw() {
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
		zaklad_typ == "p" || //Sprawdzanie czy wprowadzono zak�ad na liczby parzyste
		zaklad_typ == "n" || //Sprawdzanie czy wprowadzono zak�ad na liczby nieparzyste
		zaklad_typ == "r" || //Sprawdzanie czy wprowadzono zak�ad na czerwone liczby
		zaklad_typ == "b" || //Sprawdzanie czy wprowadzono zak�ad na czarne liczby
		zaklad_typ == "g" || //Sprawdzanie czy wprowadzono zak�ad na liczby z g�rnej po��wki
		zaklad_typ == "d" || //Sprawdzanie czy wprowadzono zak�ad na liczby z dolnej po��wki
		zaklad_typ == "k1" || //Sprawdzanie czy wprowadzono zak�ad na liczby z kolumny 1
		zaklad_typ == "k2" || //Sprawdzanie czy wprowadzono zak�ad na liczby z kolumny 2
		zaklad_typ == "k3" || //Sprawdzanie czy wprowadzono zak�ad na liczby z kolumny 3
		zaklad_typ == "w1" || //Sprawdzanie czy wprowadzono zak�ad na liczby z wiersza 1
		zaklad_typ == "w2" || //Sprawdzanie czy wprowadzono zak�ad na liczby z wiersza 2
		zaklad_typ == "w3" || //Sprawdzanie czy wprowadzono zak�ad na liczby z wiersza 3
		zaklad_typ == "w4" || //Sprawdzanie czy wprowadzono zak�ad na liczby z wiersza 4
		zaklad_typ == "w5" || //Sprawdzanie czy wprowadzono zak�ad na liczby z wiersza 5
		zaklad_typ == "w6" || //Sprawdzanie czy wprowadzono zak�ad na liczby z wiersza 6
		zaklad_typ == "w7" || //Sprawdzanie czy wprowadzono zak�ad na liczby z wiersza 7
		zaklad_typ == "w8" || //Sprawdzanie czy wprowadzono zak�ad na liczby z wiersza 8
		zaklad_typ == "w9" || //Sprawdzanie czy wprowadzono zak�ad na liczby z wiersza 9
		zaklad_typ == "w10" || //Sprawdzanie czy wprowadzono zak�ad na liczby z wiersza 10
		zaklad_typ == "w11" || //Sprawdzanie czy wprowadzono zak�ad na liczby z wiersza 11
		zaklad_typ == "w12" || //Sprawdzanie czy wprowadzono zak�ad na liczby z wiersza 12
		zaklad_typ == "0" || //Sprawdzanie czy wprowadzono zak�ad na cyfre 0
		zaklad_typ == "1" || //Sprawdzanie czy wprowadzono zak�ad na cyfre 1
		zaklad_typ == "2" || //Sprawdzanie czy wprowadzono zak�ad na cyfre 2
		zaklad_typ == "3" || //Sprawdzanie czy wprowadzono zak�ad na cyfre 3
		zaklad_typ == "4" || //Sprawdzanie czy wprowadzono zak�ad na cyfre 4
		zaklad_typ == "5" || //Sprawdzanie czy wprowadzono zak�ad na cyfre 5
		zaklad_typ == "6" || //Sprawdzanie czy wprowadzono zak�ad na cyfre 6
		zaklad_typ == "7" || //Sprawdzanie czy wprowadzono zak�ad na cyfre 7
		zaklad_typ == "8" || //Sprawdzanie czy wprowadzono zak�ad na cyfre 8
		zaklad_typ == "9" || //Sprawdzanie czy wprowadzono zak�ad na cyfre 9
		zaklad_typ == "10" || //Sprawdzanie czy wprowadzono zak�ad na liczb� 10
		zaklad_typ == "11" || //Sprawdzanie czy wprowadzono zak�ad na liczb� 11
		zaklad_typ == "12" || //Sprawdzanie czy wprowadzono zak�ad na liczb� 12
		zaklad_typ == "13" || //Sprawdzanie czy wprowadzono zak�ad na liczb� 13
		zaklad_typ == "14" || //Sprawdzanie czy wprowadzono zak�ad na liczb� 14
		zaklad_typ == "15" || //Sprawdzanie czy wprowadzono zak�ad na liczb� 15
		zaklad_typ == "16" || //Sprawdzanie czy wprowadzono zak�ad na liczb� 16
		zaklad_typ == "17" || //Sprawdzanie czy wprowadzono zak�ad na liczb� 17
		zaklad_typ == "18" || //Sprawdzanie czy wprowadzono zak�ad na liczb� 18
		zaklad_typ == "19" || //Sprawdzanie czy wprowadzono zak�ad na liczb� 19
		zaklad_typ == "20" || //Sprawdzanie czy wprowadzono zak�ad na liczb� 20
		zaklad_typ == "21" || //Sprawdzanie czy wprowadzono zak�ad na liczb� 21
		zaklad_typ == "22" || //Sprawdzanie czy wprowadzono zak�ad na liczb� 22
		zaklad_typ == "23" || //Sprawdzanie czy wprowadzono zak�ad na liczb� 23
		zaklad_typ == "24" || //Sprawdzanie czy wprowadzono zak�ad na liczb� 24
		zaklad_typ == "25" || //Sprawdzanie czy wprowadzono zak�ad na liczb� 25
		zaklad_typ == "26" || //Sprawdzanie czy wprowadzono zak�ad na liczb� 26
		zaklad_typ == "27" || //Sprawdzanie czy wprowadzono zak�ad na liczb� 27
		zaklad_typ == "28" || //Sprawdzanie czy wprowadzono zak�ad na liczb� 28
		zaklad_typ == "29" || //Sprawdzanie czy wprowadzono zak�ad na liczb� 29
		zaklad_typ == "30" || //Sprawdzanie czy wprowadzono zak�ad na liczb� 30
		zaklad_typ == "31" || //Sprawdzanie czy wprowadzono zak�ad na liczb� 31
		zaklad_typ == "32" || //Sprawdzanie czy wprowadzono zak�ad na liczb� 32
		zaklad_typ == "33" || //Sprawdzanie czy wprowadzono zak�ad na liczb� 33
		zaklad_typ == "34" || //Sprawdzanie czy wprowadzono zak�ad na liczb� 34
		zaklad_typ == "35" || //Sprawdzanie czy wprowadzono zak�ad na liczb� 35
		zaklad_typ == "36" //Sprawdzanie czy wprowadzono zak�ad na liczb� 36
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
				for (short i = 0; i < (int)kwota_zak�adu_s.size(); i++)
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
	int ilo��_zakr�ce� = rand() % (ilo��_max_dodatkowych_obrot�w_ruletki + 1) + ilo��_minimalna_obrot�w_ruletki;
	for (int i = 0; i < ilo��_zakr�ce�; ++i)
		for (int ii = 0; ii < 37; ++ii)
		{
			Change_Col(Ruletka_plansza_kolor_col[Ruletka_ko�o[ii]]); //Zmiana koloru tekstu w konsoli zgodnie z kolorem numeru na ruletce
			cout << Ruletka_ko�o[ii];
			Sleep(czas_przeskoku_kulki_szybki);
			Change_Col(7); //Powr�t do standardowego koloru tekstu w konsoli
			cout << "\b\b" << "  " << "\b\b"; //Cofni�cie kursora tekstowego do lewej strony konsoli aby zape�ni� podem spacjami czyli niewidocznym znakiem wiersza konsoli aby wida� przej�cie pomi�dzy liczbami na ruletce
		}
	int wylosowana_pozycja = MersenneTwister() % 37;
	for (int ii = 0; ii < wylosowana_pozycja; ++ii)
	{
		Change_Col(Ruletka_plansza_kolor_col[Ruletka_ko�o[ii]]); //Zmiana koloru tekstu w konsoli zgodnie z kolorem numeru na ruletce
		cout << Ruletka_ko�o[ii];
		Sleep(czas_przeskoku_kulki_wolny);
		Change_Col(7); //Powr�t do standardowego koloru tekstu w konsoli
		cout << "\b\b" << "  " << "\b\b"; //Cofni�cie kursora tekstowego do lewej strony konsoli aby zape�ni� podem spacjami czyli niewidocznym znakiem wiersza konsoli aby wida� przej�cie pomi�dzy liczbami na ruletce
	}
	cout << "Wylosowano numer ";
	Change_Col(Ruletka_plansza_kolor_col[Ruletka_ko�o[wylosowana_pozycja]]);
	cout << Ruletka_ko�o[wylosowana_pozycja];
	Change_Col(7);
	cout << ". ";

	return Ruletka_ko�o[wylosowana_pozycja];
}

int Sprawd�_Zak�ad(int & kwota, string typ_zak�adu, int wylosowana_liczba) {
	int wygrana = kwota;

	if (wylosowana_liczba == 0)
		if (typ_zak�adu == "p")
			wygrana /= 2;
		else if (typ_zak�adu == "n")
			wygrana /= 2;
		else if (typ_zak�adu == "r")
			wygrana /= 2;
		else if (typ_zak�adu == "b")
			wygrana /= 2;
		else if (typ_zak�adu == "g")
			wygrana /= 2;
		else if (typ_zak�adu == "d")
			wygrana /= 2;
		else if (typ_zak�adu[0] == 'k')
			wygrana *= 0;
		else if (typ_zak�adu[0] == 'w')
			wygrana *= 0;
		else if (typ_zak�adu[0] == '0')
			wygrana *= 35;

	if (typ_zak�adu == "p")
		if (wylosowana_liczba % 2 == 0) wygrana *= 1;
		else wygrana *= 0;
	else if (typ_zak�adu == "n")
		if (wylosowana_liczba % 2 == 1) wygrana *= 1;
		else wygrana *= 0;
	else if (typ_zak�adu == "r")
		if (Ruletka_plansza_kolor[wylosowana_liczba] == 'r') wygrana *= 1;
		else wygrana *= 0;
	else if (typ_zak�adu == "b")
		if (Ruletka_plansza_kolor[wylosowana_liczba] == 'b') wygrana *= 1;
		else wygrana *= 0;
	else if (typ_zak�adu == "g")
		if (wylosowana_liczba < 19) wygrana *= 1;
		else wygrana *= 0;
	else if (typ_zak�adu == "d")
		if (wylosowana_liczba > 18) wygrana *= 1;
		else wygrana *= 0;
	else if (typ_zak�adu[0] == 'k')
		if ((wylosowana_liczba - 1) % 3 == typ_zak�adu[1] - 49) wygrana *= 2;
		else wygrana *= 0;
	else if (typ_zak�adu[0] == 'w')
		if (((wylosowana_liczba - 1) / 3 + 1) == atoi(typ_zak�adu.erase(0, 1).c_str())) wygrana *= 11;
		else wygrana *= 0;
	else if (wylosowana_liczba == atoi(typ_zak�adu.c_str())) wygrana *= 35;
	else wygrana *= 0;

	if (wygrana >= kwota) cout << "Obstawiles poprawnie, wygrywasz " << wygrana << "$." << endl;
	else if (wygrana == kwota / 2) cout << "Obstawiles niepoprawnie lecz uda�o Ci si�, dostajesz po�ow� zak�adu " << wygrana << "$." << endl;
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
	HANDLE h_wyj; //Stworzenie zmiennej typu uchwyt
	h_wyj = GetStdHandle(STD_OUTPUT_HANDLE); //Pobiera uchwyt do standardowego wyj�cia
	SetConsoleTextAttribute(h_wyj, num_of_col); //Zmienia atrybut koloru tekstu w konsoli
}
void HideCursor()
{
	::HANDLE hConsoleOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::CONSOLE_CURSOR_INFO hCCI;
	::GetConsoleCursorInfo(hConsoleOut, &hCCI);
	hCCI.bVisible = FALSE;
	::SetConsoleCursorInfo(hConsoleOut, &hCCI);
}

void ShowCursor()
{
	::HANDLE hConsoleOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::CONSOLE_CURSOR_INFO hCCI;
	::GetConsoleCursorInfo(hConsoleOut, &hCCI);
	if (hCCI.bVisible != TRUE)
	{
		hCCI.bVisible = TRUE;
		::SetConsoleCursorInfo(hConsoleOut, &hCCI);
	}
}