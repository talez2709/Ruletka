//------------------ deklaracje bibiotek u�ywanych w programie -----------------------
#include <ctime> //time()
#include <fstream> //Obs�uga pliku
#include <io.h> //!_access()
#include <iostream> //Obs�uga strumenia cout,cin
#include <locale.h> //setlocale()
#include <random> //random_device,distribution()
#include <sstream> //stringstream, zamiana liczby na string
#include <string> //Obs�uga string�w
#include <windows.h> //SYSTEMTIME,GetSystemTime(),Sleep(),HANDLE,GetStdHandle(),SetConsoleTextAttribute()
#include <MMsystem.h> //PlaySound() (Aby dzia�a�o trzeba doda� winmm.lib lub coredll.lib do linkera (konsolidatora))
#pragma comment(lib, "winmm.lib") //Dodanie winmm.lib do linkera (konsolidatora)
#include <urlmon.h> //URLDownloadToFileA() (Aby dzia�a�o trzeba doda� urlmon.lib do linkera (konsolidatora))
#pragma comment(lib, "urlmon.lib") //Dodanie urlmon.lib do linkera (konsolidatora)
//-------------------------------------------------------------------------------------

//-------------------------- deklaracja wyboru przestrzeni nazw std -------------------
using namespace std;
//-------------------------------------------------------------------------------------

//---------------------------------- deklaracje funkcji w�asnych ----------------------
string Obstaw(); //Funkcja wczytywania typu zak�ad, do string aby mie� tak�e zak�ady sk�adaj�ce si� z liter i cyfr
void Wczytaj_Kwot�_Zak�adu(int & kwota, const int & ilo��_pieni�dzy); //Funkcja wczytywania kwoty zak�adu aby uchroni� si� przed problemem wpisania znaku,litery zamiast liczby i osbstawienie za wi�ksz� kwot� ni� si� ma
int Zakr��_Ruletk�(); //Funkcja losuje liczb� z ko�a ruletki
int Sprawd�_Zak�ad(const int & kwota, string typ_zak�adu, const int & wylosowana_liczba); //Funcja sprawdza czy wygrali�my i podaje kwote wygranej/przegranej/odzysku cz�ci w�o�onych pieni�dzy
bool Czy_Kontynuowa�(const int & ilo��_pieni�dzy); //Funkcja sprawdzj�ca czy ma si� �rodki do gry, je�eli ma si� to pyta czy chce si� gra� dalej
int Wylosuj(const int & od_liczby, const int & do_liczby); //Funkcja kt�ra losuje liczby od liczby do liczby losowo lub psudolosowo metod� MT
void Odczytaj_liczb�(const int & wylosowana_liczba, const string & typ_zak�adu); //Funkcja do odczytu wylosowanej liczby i jej po�o�enia
void Wczytaj_z_pliku(ofstream & log_og�lny, fstream & log, char & co_kontynuowa�, int & ilo��_pieni�dzy, int & kwota_zak�adu, int & wylosowana_liczba, string & typ_zak�adu); //Funkcja wczytuj�ca z pliku ostatnie ruchy gracza
void Sprawd�_Pliki(); //Funkcja sprawdzaj�ca czy wszystkie pliki d�wi�kowe s� na miejscu
void Sprawd�_ustawienia(); //sprawdzanie poprawno�ci deklaracji definicji preprocesora do zmian funcjonowania programu
void Og�o�_wynik(const int & wygrana, const int & kwota_zak�adu, int & ilo��_pieni�dzy, ofstream & log_og�lny, fstream & log); //Funkcja informuj�ca gracza o wyniku zak�adu
void Koniec_gry(ofstream & log_og�lny, fstream & log, int & ilo��_pieni�dzy); //Funkcja informuj�ca o wynikach gracza jak sko�czy� gr�
void P�tla_g��wna(int & wygrana, int & kwota_zak�adu, int & ilo��_pieni�dzy, ofstream & log_og�lny, fstream & log, char & co_kontynuowa�, string & typ_zak�adu, int & wylosowana_liczba); //Funkcja wywo�uj�ca funkcje obs�uguj�ce wszystkie elementy ruletki
void Ustaw_ustawienia(string & tekst); //Funkcja zamieniaj�ca wczytan� linijk� z ustawieniami na zmian� ustawie� programu
//-------------------------------------------------------------------------------------

//------------------------------- deklaracje funkcji obcych ---------------------------
void Change_Col(const int & num_of_col); //Funkcja zmieniaj�ca kolor tekstu 0 - czarny 1 - niebieski 2 - zielony 3 - b��kitny 4 - czerwony 5 - purpurowy 6 - ��ty 7 - bia�y 8 - szary 9 - jasnoniebieski 10 - jasnozielony 11 - jasnob��kitny 12 - jasnoczerwony 13 - jasnopurpurowy 14 - jasno��ty 15 - jaskrawobia�y
void Hide_Cursor(); //Funkcja w��cza pokazanie kursora tekstowego
void Show_Cursor(); //Funkcja wy��cza pokazanie kursora tekstowego
//-------------------------------------------------------------------------------------

//----------------------------- deklaracje tablic pomocniczych ------------------------
const int Ruletka_ko�o[] = { 0, 32, 15, 19, 4, 21, 2, 25, 17, 34, 6, 27, 13, 36, 11, 30, 8, 23, 10, 5, 24, 16, 33, 1, 20, 14, 31, 9, 22, 18, 29, 7, 28, 12, 35, 3, 26 }; // Kolejno�� liczb zgodna z ko�em ruletki
const char Ruletka_plansza_kolor[] = { 'g','r','b','r','b','r','b','r','b','r','b','b','r','b','r','b','r','b','r','r','b','r','b','r','b','r','b','r','b','b','r','b','r','b','r','b','r' }; //Kolor dla ka�dej liczby na planszy
const int Ruletka_plansza_kolor_col[] = { 2,4,8,4,8,4,8,4,8,4,8,8,4,8,4,8,4,8,4,4,8,4,8,4,8,4,8,4,8,8,4,8,4,8,4,8,4 }; //Kod koloru do funkcji zmiany koloru tekstu dla ka�dej liczby na planszy
//-------------------------------------------------------------------------------------

//------ deklaracje zmiennych globalnych do zmian funcjonowania programu --------------
short ilo��_minimalna_obrot�w_ruletki = 2; // Minimalna ilo�� obrot�w ruletki przed podaniem warto�ci wylosowanej
short ilo��_max_dodatkowych_obrot�w_ruletki = 3; // Maksymalna ilo�� dodatkowych obrot�w ruletki przed podaniem warto�ci wylosowanej
short czas_przeskoku_kulki_szybki = 50; //Czas w ms przerwy pomi�dzy przeskokami na pocz�tek losowania na kolejn� liczb� na kole ruletki
short czas_przeskoku_kulki_wolny = 75; //Czas w ms przerwy pomi�dzy przeskokami pod koniec losowania na kolejn� liczb� na kole ruletki
short czas_przerwy_dzwi�ku = 500; //Czas w ms przerwy pomi�dzy pikni�ciami oznaczaj�cymi wynik zak�adu
short styl_liczenia_wygranej = 1; //0 dla odejmowania w�o�onych w zak�ad pieni�dzy (przy tym zak�ady 1:1 nie zwi�kszaj� ilo��_pieni�dzy), 1 dla nie odejmowania (przy tym zak�ady 1:1 zwi�kszaj� ilo��_pieni�dzy)
int kwota_pocz�tkowa = 1000; //Ilo�� $ z kt�rymi zaczyna si� gr�
short stan_d�wi�k�w = 1; //Czy w��czone d�wi�ki 1 <-tak 0 <-nie
short czy_kontynuowa�_gr� = 1; //Czy w��czone kontynuowanie gry od sko�czonej poprzednio pozycji 1 <-tak 0 <-nie
short g�os_odczytu_numeru = 1; //Wyb�r g�osu kt�ry odczyta wylosowany numer 0 <- Brak 1 <- Jacek (Ivona) 2 <- Ewa (Ivona) 3 <- Maja (Ivona) 4 <- Jan (Ivona) 5 <- Jacek (Ivona 2) 6 <- Ewa (Ivona 2) 7 <- Maja (Ivona 2) 8 <- Jan (Ivona 2) 9 <- Agata (Scansoft)
short g�os_szybko��_odczytu_numeru = 4; //Wyb�r szybko�ci mowy, skala od 1 do 5
short efekty_d�wi�kowe = 1; //Czy w��czone efekty d�wi�kowe 1 <-tak 0 <-nie
//-------------------------------------------------------------------------------------

//---------------------------- deklaracje zmiennych globalnych ------------------------
SYSTEMTIME Czas; //Struktura do kt�rej zapisywana jest aktualna data i czas
bool G�osyKompletne = true;
bool EfektyKompletne = true;
string G�os;
//-------------------------------------------------------------------------------------

int main()
{
	//Inicjowanie funkcji
	setlocale(LC_ALL, "polish"); // W celu polskich liter w konsoli
	srand((unsigned int)time(nullptr)); //Zainicjowanie generatorza LCG (Liniowy Generator Kongruentny) dla ma�o wa�nych liczb
	Show_Cursor(); //Pokazanie kursora tekstowego w konsoli

//	string link = "https://github.com/talez2709/Ruletka/raw/master/Ruletka/G%C5%82os/Agata%20_1/0.wav";
//	string save = "a/bankrut.wav";

	//if (URLDownloadToFileA(nullptr, link.c_str(), save.c_str(), 0, nullptr) == S_OK) {
	//}
	//else {
	//	cout << "B��d pobierania" << endl;
	//}

	Sprawd�_ustawienia();
	Sprawd�_Pliki();

	//int a = 10;
	//string b = "10";
	//Odczytaj_liczb�(a, b);
	//b = "p";
	//Odczytaj_liczb�(a, b);
	//b = "r";
	//Odczytaj_liczb�(a, b);
	//b = "g";
	//Odczytaj_liczb�(a, b);
	//b = "k1";
	//Odczytaj_liczb�(a, b);
	//b = "w1";
	//Odczytaj_liczb�(a, b);

	//string c = "ilo��_minimalna_obrot�w_ruletki 000";
	//Ustaw_ustawienia(c);

	//Inicjowanie zmiennych lokalnych
	ofstream log_og�lny; //Utworzenie typu do celu zapisu do pliku
	log_og�lny.open("log_og�lny.txt", ios::app); //Otworzenie pliku z ustawieniem kursora zapisu do pliku
	fstream log; //Utworzenie typu do celu zapisu i/lub odczytu do i/lub z pliku
	int ilo��_pieni�dzy = kwota_pocz�tkowa, kwota_zak�adu, wylosowana_liczba, wygrana; //Zmienne do kt�rych wczytuje si� warto�ci liczbowe pobrane od u�ytkownika takie jak kwota zak�adu a przechowuje ilo�� posiadanych pieni�dzy a tak�e przechowuje wyniki funkcji losowania liczby z ruletki i kwote wygran� z zak�adu
	string typ_zak�adu; //Przechowuje typ zak�adu wprowadzony przez u�ytkownika
	char co_kontynuowa�; //Deklaracja znaku kt�ry przechowuje nazwany znakiem punkt od kt�rego kontynuowa� runde

	Wczytaj_z_pliku(log_og�lny, log, co_kontynuowa�, ilo��_pieni�dzy, kwota_zak�adu, wylosowana_liczba, typ_zak�adu);

	do
	{
		P�tla_g��wna(wygrana, kwota_zak�adu, ilo��_pieni�dzy, log_og�lny, log, co_kontynuowa�, typ_zak�adu, wylosowana_liczba);
		co_kontynuowa� = 'n'; //Przypisanie znaku rozpocz�cia rundy od pocz�tku
	} while (Czy_Kontynuowa�(ilo��_pieni�dzy)); //P�tla dza�aj�ca do czasu warto�ci fa�sz zwr�conej przez funkcj� Czy_kontynuowa�

	Koniec_gry(log_og�lny, log, ilo��_pieni�dzy);

	system("pause"); //Wywo�anie funkcji wymagaj�cej do zamkni�cia naci�ni�cie dowolnego klawisza

	return 0; //Zwr�cenie warto�� 0, czyli porogram zako�czy� si� bez b��du
}

string Obstaw()
{
	string zaklad_typ; //Deklaracja zmiennej typu string przechowywuj�cej typ zak�adu

	do { //P�tla do aby wykona�a si� conajmniej raz
		cout << "Jak� opcje chcesz obstawic ? (zgodnie z poni�szym opisem) :" << endl; //Zadanie pytania u�ytkownikowi
		cout << "p - parzyste" << endl; //Wskaza� mo�liw� odpowied�
		cout << "n - nieparzyste" << endl; //Wskaza� mo�liw� odpowied�
		cout << "r - czerwone(red)" << endl; //Wskaza� mo�liw� odpowied�
		cout << "b - czarne(black)" << endl; //Wskaza� mo�liw� odpowied�
		cout << "g - g�rna po�owa" << endl; //Wskaza� mo�liw� odpowied�
		cout << "d - dolna po�owa" << endl; //Wskaza� mo�liw� odpowied�
		cout << "k1, k2, k3 - kolumna 1, kolumna 2, kolumna 3" << endl; //Wskaza� mo�liw� odpowied�
		cout << "w1, w2, ..., w12 - wiersz trzech numer�w" << endl; //Wskaza� mo�liw� odpowied�
		cout << "0 - 36 - pojedyncze pole o odpowiednim numerze" << endl; //Wskaza� mo�liw� odpowied�
		cin >> zaklad_typ; //Pobranie od u�ytkownika odpowiedzi na pytanie
	} while ( //U�ywam takiej sk�adni poniewa� je�li masz wyra�enie z logicznymi operatorami && lub ||, to w momencie gdy wynik wyra�enia ju� jest znany, to nie jest wyliczany dalej. (Poniewa� C++ jest "leniwe", co zarazem jest optymalne)
		zaklad_typ != "p" && //Sprawdzanie czy wprowadzono zak�ad na liczby parzyste
		zaklad_typ != "n" && //Sprawdzanie czy wprowadzono zak�ad na liczby nieparzyste
		zaklad_typ != "r" && //Sprawdzanie czy wprowadzono zak�ad na czerwone liczby
		zaklad_typ != "b" && //Sprawdzanie czy wprowadzono zak�ad na czarne liczby
		zaklad_typ != "g" && //Sprawdzanie czy wprowadzono zak�ad na liczby z g�rnej po��wki
		zaklad_typ != "d" && //Sprawdzanie czy wprowadzono zak�ad na liczby z dolnej po��wki
		zaklad_typ != "k1" && //Sprawdzanie czy wprowadzono zak�ad na liczby z kolumny 1
		zaklad_typ != "k2" && //Sprawdzanie czy wprowadzono zak�ad na liczby z kolumny 2
		zaklad_typ != "k3" && //Sprawdzanie czy wprowadzono zak�ad na liczby z kolumny 3
		zaklad_typ != "w1" && //Sprawdzanie czy wprowadzono zak�ad na liczby z wiersza 1
		zaklad_typ != "w2" && //Sprawdzanie czy wprowadzono zak�ad na liczby z wiersza 2
		zaklad_typ != "w3" && //Sprawdzanie czy wprowadzono zak�ad na liczby z wiersza 3
		zaklad_typ != "w4" && //Sprawdzanie czy wprowadzono zak�ad na liczby z wiersza 4
		zaklad_typ != "w5" && //Sprawdzanie czy wprowadzono zak�ad na liczby z wiersza 5
		zaklad_typ != "w6" && //Sprawdzanie czy wprowadzono zak�ad na liczby z wiersza 6
		zaklad_typ != "w7" && //Sprawdzanie czy wprowadzono zak�ad na liczby z wiersza 7
		zaklad_typ != "w8" && //Sprawdzanie czy wprowadzono zak�ad na liczby z wiersza 8
		zaklad_typ != "w9" && //Sprawdzanie czy wprowadzono zak�ad na liczby z wiersza 9
		zaklad_typ != "w10" && //Sprawdzanie czy wprowadzono zak�ad na liczby z wiersza 10
		zaklad_typ != "w11" && //Sprawdzanie czy wprowadzono zak�ad na liczby z wiersza 11
		zaklad_typ != "w12" && //Sprawdzanie czy wprowadzono zak�ad na liczby z wiersza 12
		zaklad_typ != "0" && //Sprawdzanie czy wprowadzono zak�ad na cyfr� 0
		zaklad_typ != "1" && //Sprawdzanie czy wprowadzono zak�ad na cyfr� 1
		zaklad_typ != "2" && //Sprawdzanie czy wprowadzono zak�ad na cyfr� 2
		zaklad_typ != "3" && //Sprawdzanie czy wprowadzono zak�ad na cyfr� 3
		zaklad_typ != "4" && //Sprawdzanie czy wprowadzono zak�ad na cyfr� 4
		zaklad_typ != "5" && //Sprawdzanie czy wprowadzono zak�ad na cyfr� 5
		zaklad_typ != "6" && //Sprawdzanie czy wprowadzono zak�ad na cyfr� 6
		zaklad_typ != "7" && //Sprawdzanie czy wprowadzono zak�ad na cyfr� 7
		zaklad_typ != "8" && //Sprawdzanie czy wprowadzono zak�ad na cyfr� 8
		zaklad_typ != "9" && //Sprawdzanie czy wprowadzono zak�ad na cyfr� 9
		zaklad_typ != "10" && //Sprawdzanie czy wprowadzono zak�ad na liczb� 10
		zaklad_typ != "11" && //Sprawdzanie czy wprowadzono zak�ad na liczb� 11
		zaklad_typ != "12" && //Sprawdzanie czy wprowadzono zak�ad na liczb� 12
		zaklad_typ != "13" && //Sprawdzanie czy wprowadzono zak�ad na liczb� 13
		zaklad_typ != "14" && //Sprawdzanie czy wprowadzono zak�ad na liczb� 14
		zaklad_typ != "15" && //Sprawdzanie czy wprowadzono zak�ad na liczb� 15
		zaklad_typ != "16" && //Sprawdzanie czy wprowadzono zak�ad na liczb� 16
		zaklad_typ != "17" && //Sprawdzanie czy wprowadzono zak�ad na liczb� 17
		zaklad_typ != "18" && //Sprawdzanie czy wprowadzono zak�ad na liczb� 18
		zaklad_typ != "19" && //Sprawdzanie czy wprowadzono zak�ad na liczb� 19
		zaklad_typ != "20" && //Sprawdzanie czy wprowadzono zak�ad na liczb� 20
		zaklad_typ != "21" && //Sprawdzanie czy wprowadzono zak�ad na liczb� 21
		zaklad_typ != "22" && //Sprawdzanie czy wprowadzono zak�ad na liczb� 22
		zaklad_typ != "23" && //Sprawdzanie czy wprowadzono zak�ad na liczb� 23
		zaklad_typ != "24" && //Sprawdzanie czy wprowadzono zak�ad na liczb� 24
		zaklad_typ != "25" && //Sprawdzanie czy wprowadzono zak�ad na liczb� 25
		zaklad_typ != "26" && //Sprawdzanie czy wprowadzono zak�ad na liczb� 26
		zaklad_typ != "27" && //Sprawdzanie czy wprowadzono zak�ad na liczb� 27
		zaklad_typ != "28" && //Sprawdzanie czy wprowadzono zak�ad na liczb� 28
		zaklad_typ != "29" && //Sprawdzanie czy wprowadzono zak�ad na liczb� 29
		zaklad_typ != "30" && //Sprawdzanie czy wprowadzono zak�ad na liczb� 30
		zaklad_typ != "31" && //Sprawdzanie czy wprowadzono zak�ad na liczb� 31
		zaklad_typ != "32" && //Sprawdzanie czy wprowadzono zak�ad na liczb� 32
		zaklad_typ != "33" && //Sprawdzanie czy wprowadzono zak�ad na liczb� 33
		zaklad_typ != "34" && //Sprawdzanie czy wprowadzono zak�ad na liczb� 34
		zaklad_typ != "35" && //Sprawdzanie czy wprowadzono zak�ad na liczb� 35
		zaklad_typ != "36" //Sprawdzanie czy wprowadzono zak�ad na liczb� 36
		); //Je�eli kt�ry� z warunk�w si� niezgadza to p�tla nie jest kontynuowana

	return zaklad_typ; //Zwracam typ zak�adu podany przez u�ytkownika
}

void Wczytaj_Kwot�_Zak�adu(int & kwota_zak�adu, const int & ilo��_pieni�dzy)
{
	string kwota_zak�adu_s; //Deklaracja zmiennej typu string do wczytywania kwoty aby zabezpieczy� si� przed b��dem wpisania do zmiennej liczbowej litery

	while (true) //Rozpocz�cie p�tli niesko�czonej
	{
		cout << "Masz " << ilo��_pieni�dzy << "$, jak� kwot� chcesz obstawi� wynik?" << endl; //Podanie akualnego stanu konta i zadanie pytania o kwot� zak�adu
		cin >> kwota_zak�adu_s; //Pobranie w tek�cie kwoty zak��du
		kwota_zak�adu = atoi(kwota_zak�adu_s.c_str()); //Zmiana stringaa na inta i wpisanie do zmiennej kwota_zak�adu
		if (kwota_zak�adu > 0 && kwota_zak�adu <= ilo��_pieni�dzy) //Sprawdzenie czy kwota zak��du jest wi�ksza od zeri i mniejsza lub r�wna dost�pnej got�wce
			break; //Je�eli tak to zatrzymuje p�tle
		else //W przeciwym wypadku
			if (kwota_zak�adu == 0) //Je�eli wynikiem zamiany na liczb� jest zero (wynikiem zamiany jest zero kiedy tekst to zero lub kiedy jest b��d zamiany) to
			{
				bool czy_zero = true; //Utworzenie zmiennej informuj�cej czy znaleziono zero w tek�cie i przypisanie jej warto�ci true
				for (short i = 0; i < (short)kwota_zak�adu_s.size(); ++i) //Rozpocz�cie p�tli numerowanej przez zmienn� i przez wszystkie znaki wczytanego tekst
					if (kwota_zak�adu_s[i] != '0') //Je�eli znak na i-tej pozycji
					{
						cout << "Wprowadzi�e� nieprawid�ow� warto��" << endl; //Poinformowanie u�ytkownika, �e nie mo�e obstawi� tekstowego
						if (stan_d�wi�k�w) cout << "\a"; //Wywo�anie pikni�cia w g�o�niku
						czy_zero = false; //Zmiana warto�ci zmiennej czy znaleziono zero w tek�cie na false
						break; //Zatrzymanie p�tli
					}
				if (czy_zero) //Sprawdzenie czy znaleziono same zera w tek�cie, je�eli tak to
				{
					cout << "Nie mo�esz obstawi� zerowego zak�adu" << endl; //Poinformowanie u�ytkownika, �e nie mo�e obstawi� zerowego zak�adu
					if (stan_d�wi�k�w) cout << "\a"; //Wywo�anie pikni�cia w g�o�niku
				}
			}
			else if (kwota_zak�adu > ilo��_pieni�dzy) //Je�eli u�ytkownik chce obstawi� za wi�cej ni� ma, to
			{
				cout << "Nie masz tyle pieni�dzy" << endl; //Poinformowanie go o tym
				if (stan_d�wi�k�w) cout << "\a"; //Wywo�anie pikni�cia w g�o�niku
			}
			else if (kwota_zak�adu < 0) //Je�eli u�ytkownik chce obstawi� za ujemn� kwot�, to
			{
				cout << "Nie mo�esz obstawi� ujemn� kwot� zak�adu" << endl; //Poinformowanie go o tym
				if (stan_d�wi�k�w) cout << "\a"; //Wywo�anie pikni�cia w g�o�niku
			}
	}
}

int Zakr��_Ruletk�()
{
	int ilo��_zakr�ce� = rand() % (ilo��_max_dodatkowych_obrot�w_ruletki + 1) + ilo��_minimalna_obrot�w_ruletki; //Deklarowanie i przpisanie zmiennej liczbowj zawieraj�c� pseudolosow� (o niskiej pseoudolosowo�ci) ilo�� obrot�w ruletk� ((od 0 do max dodatkowych obrot�w ruletki) + minimalna ilo�� obrot�w ruletki) zanim nast�pi finalny obr�t
	double czas_przeskoku_kulki_szybki_op�nienie = czas_przeskoku_kulki_szybki / (ilo��_zakr�ce� * 37.0); //Deklarowanie i przpisanie zmiennej zmiennoprzecinkowej zawieraj�c� czas o ile kolejna warto�� na kole ruletki powinna by� szybciej pokazana
	Hide_Cursor(); //Ukrycie kursora tekstowego w konsoli
	for (int i = 0; i < ilo��_zakr�ce�; ++i) //Wykonanie ilo��_zakr�ce� obrot�w ruletk�
		for (int ii = 0; ii < 37; ++ii) //Przej�cie przez wszystkie pozycje ruletki
		{
			Change_Col(Ruletka_plansza_kolor_col[Ruletka_ko�o[ii]]); //Zmiana koloru tekstu w konsoli zgodnie z kolorem numeru na ruletce
			cout << Ruletka_ko�o[ii]; //Wypisanie numeru na kole ruletki na kt�rym znajduje si� p�tla
			Sleep((DWORD)(czas_przeskoku_kulki_szybki_op�nienie*((double)i*37.0 + (double)ii))); //Przest�j kt�ry zwi�ksza si� co zmian� pozycji p�tli
			Change_Col(7); //Powr�t do standardowego koloru tekstu w konsoli
			cout << "\b\b" << "  " << "\b\b"; //Cofni�cie kursora tekstowego do lewej strony konsoli aby zape�ni� podem spacjami czyli niewidocznym znakiem wiersza konsoli aby wida� przej�cie pomi�dzy liczbami na ruletce
		}
	int wylosowana_pozycja = Wylosuj(0, 36); //Deklarowanie i przpisanie zmiennej liczbowj zawieraj�c� losow� lub pseudolosow� liczb� (o wysokiej pseoudolosowo�ci) pozycj� na ruletce
	double czas_przeskoku_kulki_wolny_przyspieszenie = (czas_przeskoku_kulki_wolny - czas_przeskoku_kulki_szybki) / (double)(wylosowana_pozycja); //Deklarowanie i przpisanie zmiennej zmiennoprzecinkowej zawieraj�c� czas o ile kolejna warto�� na kole ruletki powinna by� szybciej pokazana
	for (int i = 0; i < wylosowana_pozycja; ++i) //Przej�cie przez pozycje do pozycji o 1 mniejszej od wylosowanej pozyji na ruletce
	{
		Change_Col(Ruletka_plansza_kolor_col[Ruletka_ko�o[i]]); //Zmiana koloru tekstu w konsoli zgodnie z kolorem numeru na ruletce
		cout << Ruletka_ko�o[i]; //Wypisanie numeru na kole ruletki na kt�rym znajduje si� p�tla
		Sleep((DWORD)(czas_przeskoku_kulki_szybki + (czas_przeskoku_kulki_wolny_przyspieszenie*i))); //Przest�j kt�ry zwi�ksza si� co zmian� pozycji p�tli
		Change_Col(7); //Powr�t do standardowego koloru tekstu w konsoli
		cout << "\b\b" << "  " << "\b\b"; //Cofni�cie kursora tekstowego do lewej strony konsoli aby zape�ni� podem spacjami czyli niewidocznym znakiem wiersza konsoli aby wida� przej�cie pomi�dzy liczbami na ruletce
	}
	cout << "Wylosowano numer "; //Poinformowanie o zako�czeniu (wy�wietlania) losowania
	Change_Col(Ruletka_plansza_kolor_col[Ruletka_ko�o[wylosowana_pozycja]]);//Zmiana koloru tekstu w konsoli zgodnie z kolorem numeru na ruletce
	cout << Ruletka_ko�o[wylosowana_pozycja]; //Wypisanie liczby na wylosowanej pozycji ruletki
	Change_Col(7); //Powr�t do standardowego koloru tekstu w konsoli
	cout << ". "; //Zako�czenie tekstu kropk�
	Show_Cursor(); //Pokazanie kursora tekstowego w konsoli

	return Ruletka_ko�o[wylosowana_pozycja]; //Zwracam warto�� b�d�c� na wylosowanym polu ruletki
}

int Sprawd�_Zak�ad(const int & kwota, string typ_zak�adu, const int & wylosowana_liczba)
{
	int wygrana = kwota; //Deklaracja zmiennej przechowywuj�ca kwot� wygran� lub zwr�con� przy wylosowaniu 0

	if (wylosowana_liczba == 0) //Warunek sprawdzaj�cy czy wylosowano 0
	{ //Je�eli tak to
		if (typ_zak�adu == "p") wygrana /= 2; //Je�eli typ zak�adu by� p to wygrana, a dok�adniej zwrot wynosi po�ow� zak�adu
		else if (typ_zak�adu == "n") wygrana /= 2; //Je�eli typ zak�adu by� p to wygrana, a dok�adniej zwrot wynosi po�ow� zak�adu
		else if (typ_zak�adu == "r") wygrana /= 2; //Je�eli typ zak�adu by� r to wygrana, a dok�adniej zwrot wynosi po�ow� zak�adu
		else if (typ_zak�adu == "b") wygrana /= 2; //Je�eli typ zak�adu by� b to wygrana, a dok�adniej zwrot wynosi po�ow� zak�adu
		else if (typ_zak�adu == "g") wygrana /= 2; //Je�eli typ zak�adu by� g to wygrana, a dok�adniej zwrot wynosi po�ow� zak�adu
		else if (typ_zak�adu == "d") wygrana /= 2; //Je�eli typ zak�adu by� d to wygrana, a dok�adniej zwrot wynosi po�ow� zak�adu
		else if (typ_zak�adu[0] == 'k') wygrana *= 0; //Je�eli typ zak�adu by� k to przegra�o si� zak�ad
		else if (typ_zak�adu[0] == 'w') wygrana *= 0; //Je�eli typ zak�adu by� k to przegra�o si� zak�ad
		else if (typ_zak�adu[0] == '0') wygrana *= 35; //Je�eli typ zak�adu by� 0 to przegra�o si� zak�ad
	}
	else //Je�eli wylosowana liczba nie jest zerem to
	{
		if (typ_zak�adu == "p") //Je�eli typ zak�adu to p
			if (wylosowana_liczba % 2 == 0) wygrana *= 1; //To sprawdzam czy wylosowana liczba jest parzysta, je�eli tak to wygrana jest 1:1
			else wygrana *= 0; //Je�eli wylosowana liczba nie jest parzysta to przegra�o si� zak�ad
		else if (typ_zak�adu == "n") //Je�eli typ zak�adu to n
			if (wylosowana_liczba % 2 == 1) wygrana *= 1; //To sprawdzam czy wylosowana liczba jest nieparzysta, je�eli tak to wygrana jest 1:1
			else wygrana *= 0; //Je�eli obstawiony numer nie jest nieparzysta to przegra�o si� zak�ad
		else if (typ_zak�adu == "r") //Je�eli typ zak�adu to n
			if (Ruletka_plansza_kolor[wylosowana_liczba] == 'r') wygrana *= 1; //To sprawdzam czy wylosowana liczba jest czerwona, je�eli tak to wygrana jest 1:1
			else wygrana *= 0; //Je�eli wylosowana liczba nie jest czerwony to przegra�o si� zak�ad
		else if (typ_zak�adu == "b") //Je�eli typ zak�adu to n
			if (Ruletka_plansza_kolor[wylosowana_liczba] == 'b') wygrana *= 1; //To sprawdzam czy wylosowana liczba jest czarna, je�eli tak to wygrana jest 1:1
			else wygrana *= 0; //Je�eli wylosowana liczba nie jest czarny to przegra�o si� zak�ad
		else if (typ_zak�adu == "g") //Je�eli typ zak�adu to g
			if (wylosowana_liczba < 19) wygrana *= 1; //To sprawdzam czy wylosowana liczba jest od 1 do 18, je�eli tak to wygrana jest 1:1
			else wygrana *= 0; //Je�eli wylosowana liczba nie nale�y do przedzia�u [1,18] to przegra�o si� zak�ad
		else if (typ_zak�adu == "d") //Je�eli typ zak�adu to d
			if (wylosowana_liczba > 18) wygrana *= 1; //To sprawdzam czy wylosowana liczba jest od 19 do 36, je�eli tak to wygrana jest 1:1
			else wygrana *= 0; //Je�eli wylosowana liczba nie nale�y do przedzia�u [19,36] to przegra�o si� zak�ad
		else if (typ_zak�adu[0] == 'k') //Je�eli typ zak�adu to k
			if ((wylosowana_liczba - 1) % 3 == typ_zak�adu[1] - 49) wygrana *= 2; //To sprawdzam czy wylosowana liczba jest z obstawionej kolumny, je�eli tak to wygrana jest 2:1
			else wygrana *= 0; //Je�eli wylosowana liczba nie jest z obstawionej kolumny to przegra�o si� zak�ad
		else if (typ_zak�adu[0] == 'w') //Je�eli typ zak�adu to w
			if (((wylosowana_liczba - 1) / 3 + 1) == atoi(typ_zak�adu.erase(0, 1).c_str())) wygrana *= 11; //To sprawdzam czy wylosowana liczba jest z obstawionego wiersza, je�eli tak to wygrana jest 11:1
			else wygrana *= 0; //Je�eli wylosowana liczba nie jest z obstawionego wiersza to przegra�o si� zak�ad
		else if (wylosowana_liczba == atoi(typ_zak�adu.c_str())) wygrana *= 35; //Je�eli typ zak�adu to liczba, to sprawdzam czy wylosowana liczba jest r�wna obstawionej liczbie, je�eli tak to wygrana jest 35:1
		else wygrana *= 0; //Je�eli wylosowana liczba nie jest r�wna obstawionej liczbie to przegra�o si� zak�ad
	}

	if (wygrana >= kwota) cout << "Obstawiles poprawnie, wygrywasz " << wygrana << "$." << endl; //Je�eli wygrana jest wi�ksza lub r�wna obstawionej kwocie to informuj� o tym, �e wygra�
	else if (wygrana == kwota / 2) cout << "Obstawiles niepoprawnie lecz uda�o Ci si�, dostajesz po�ow� zak�adu " << wygrana << "$." << endl; //Je�eli wygrana jest r�wna po�owie obstawionej kwocie to informuj� o tym, �e przegra� po�owe stawki
	else cout << "Obstawiles niepoprawnie, przegra�e� " << kwota << "$." << endl; //Je�eli wygrana jest r�wna zero to informuj� o tym, �e przegra�

	return wygrana; //Zwracam warto� wygranej lub zwrotu
}

bool Czy_Kontynuowa�(const int & ilo��_pieni�dzy)
{
	string tak_nie; //Zadeklarowanie zmiennej typu string

	if (ilo��_pieni�dzy == 0) //Je�eli posiadana ilo�� got�wki jest r�na 0
	{
		cout << "Nie mo�esz kontynuowa�, przegra�e� wszystko" << endl; //Poinformowanie u�ytkownika, �e jest bankrutem
		return false; //Zwrot warto�ci false, co oznacza, �e kolejna runda si� nie odb�dzie
	}

	while (true) //Rozpocz�cie p�tli niesko�czonej
	{
		cout << "Na koncie masz " << ilo��_pieni�dzy << "$, czy chcesz grac dalej('t' - tak, 'n' - nie) ?" << endl; //Pointormowanie o stanie konta i zapytanie o to czy gra dalej
		cin >> tak_nie; //Pobranie od u�ytkownika odpowiedzi na powy�sze pytanie
		if (tak_nie == "t" || tak_nie == "tak" || tak_nie == "Tak" || tak_nie == "TAK" || tak_nie == "n" || tak_nie == "nie" || tak_nie == "Nie" || tak_nie == "NIE") //Sprawdzenie czy odpowied� pasuje do mo�liwo�ci
			if (tak_nie[0] == 't' || tak_nie[0] == 'T') return true; //Je�eli pasuje to sprawdzam czy pierwsza litera to t i zwracam warto�� true
			else return false; //W przeciwym wypadku zwracam warto�� false
	}
}

void Change_Col(const int & num_of_col)
{
	HANDLE h_wyj = GetStdHandle(STD_OUTPUT_HANDLE); //Stworzenie zmiennej typu uchwyt i przypisanie do standardowego wyj�cia
	SetConsoleTextAttribute(h_wyj, num_of_col); //Zmienia atrybut koloru tekstu w konsoli
}

void Hide_Cursor()
{
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE); //Stworzenie zmiennej typu uchwyt i przypisanie do standardowego wyj�cia
	CONSOLE_CURSOR_INFO hCCI; //Stworzenie zmiennej typu informacji o kursorze tekstowym w konsoli
	GetConsoleCursorInfo(hConsoleOut, &hCCI); //Przypisanie do zmiennej informacji o kursorze tekstowym w konsoli
	hCCI.bVisible = FALSE; //Zmiena widoczno�ci kursora na niewidoczny
	SetConsoleCursorInfo(hConsoleOut, &hCCI); //Ustawienie widoczno�ci kursora zgodnie z poprzedni� zmienn�
}

void Show_Cursor()
{
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE); //Stworzenie zmiennej typu uchwyt i przypisanie do standardowego wyj�cia
	CONSOLE_CURSOR_INFO hCCI; //Stworzenie zmiennej typu informacji o kursorze tekstowym w konsoli
	GetConsoleCursorInfo(hConsoleOut, &hCCI); //Przypisanie do zmiennej informacji o kursorze tekstowym w konsoli
	if (hCCI.bVisible != TRUE) //Sprawdzenie czy warto�� widoczno�ci kursorsora tekstego w konsoli jest r�na od prawdy
	{
		hCCI.bVisible = TRUE;//Je�eli tak, to zmiena widoczno�ci kursora na widoczny
		SetConsoleCursorInfo(hConsoleOut, &hCCI); //I ustawienie widoczno�ci kursora zgodnie z poprzedni� zmienn�
	}
}

int Wylosuj(const int & od_liczby, const int & do_liczby)
{
	random_device generator; //Generator liczb losowych, kt�ry generuje niedeterministyczne liczby losowe, je�li s� obs�ugiwane.
	if (generator.entropy() != 32) //Je�eli entropia jest mniejsza od 32 oznacza, �e komputer nie dysponuje mo�liwo�ci� u�ycia tego generatora liczb losowy
	{
#if defined(__x86_64__) || defined(_M_X64) || defined(__x86_64) || defined(__amd64) || defined(__amd64__) || defined(_M_AMD64) //Sprawdzenie czy sytem operacyjny jest 64-bitowy
		mt19937_64 generator((unsigned int)time(nullptr)); //Dla 64 bitowego systemu zamiast powy�szego generatora u�ywa generator liczb pseudolosowych Mersenne Twister 19937 w wersji 64 bitowej
#else
		mt19937 generator((unsigned int)time(nullptr)); //Dla 32 bitowego systemu zamiast powy�szego generatora u�ywa generator liczb pseudolosowych Mersenne Twister 19937 w wersji 32 bitowej
#endif
	}
	uniform_int_distribution<int> distribution(od_liczby, do_liczby); //Wsazuje zakres generowanych liczb
	return distribution(generator); //Zwraca wygenerowan� liczb�
}

void Odczytaj_liczb�(const int & wylosowana_liczba, const string & typ_zak�adu) {
	if ((g�os_odczytu_numeru == 0) || (!G�osyKompletne)) return;

	stringstream numers;
	numers << wylosowana_liczba;
	PlaySound((G�os + numers.str() + ".wav").c_str(), nullptr, SND_SYNC);
	if (typ_zak�adu == "p" || typ_zak�adu == "n")
		if (wylosowana_liczba % 2 == 0)
			PlaySound((G�os + "p.wav").c_str(), nullptr, SND_SYNC);
		else
			PlaySound((G�os + "n.wav").c_str(), nullptr, SND_SYNC);
	else if (typ_zak�adu == "r" || typ_zak�adu == "b")
		if (Ruletka_plansza_kolor[wylosowana_liczba] == 'r')
			PlaySound((G�os + "r.wav").c_str(), nullptr, SND_SYNC);
		else
			PlaySound((G�os + "b.wav").c_str(), nullptr, SND_SYNC);
	else if (typ_zak�adu == "g" || typ_zak�adu == "d")
		if (wylosowana_liczba < 19)
			PlaySound((G�os + "g.wav").c_str(), nullptr, SND_SYNC);
		else
			PlaySound((G�os + "d.wav").c_str(), nullptr, SND_SYNC);
	else if (typ_zak�adu[0] == 'k')
		PlaySound((G�os + "k" + (char)(((wylosowana_liczba - 1) % 3) + 49) + ".wav").c_str(), nullptr, SND_SYNC);
	else if (typ_zak�adu[0] == 'w')
	{
		stringstream numers;
		numers << ((wylosowana_liczba - 1) / 3 + 1);
		PlaySound((G�os + "w" + numers.str() + ".wav").c_str(), nullptr, SND_SYNC);
	}
}

void Wczytaj_z_pliku(ofstream & log_og�lny, fstream & log, char & co_kontynuowa�, int & ilo��_pieni�dzy, int & kwota_zak�adu, int & wylosowana_liczba, string & typ_zak�adu)
{
	if (!czy_kontynuowa�_gr�) //Kompilacja je�eli czy_kontynuowa�_gr� == 0
		if (!_access("log_aktualny.txt", 0)) // Sprawdzenie dost�pu do pliku (je�eli takowy istnieje, musi istnie� plik)
		{
			co_kontynuowa� = 'n'; //Przypisanie znaku rozpocz�cia rundy od pocz�tku
			remove("log_aktualny.txt"); //Usuni�cie pliku log aktualny poniewa� rozpoczyna si� now� gr�
			log_og�lny << endl << "Uruchomiono ponownie gr� z wy��czon� opcj� kontynuowania" << endl; //Wpisanie do buforu logu og�lnego informacje o rozpocz�ciu nowej gry spowodowane ustawieniem gry
			log_og�lny.flush(); //Zapisanie do pliku log_og�lny.txt danych wpisanych do bufora danych
		}

	if (!_access("log_aktualny.txt", 0)) // Sprawdzenie dost�pu do pliku (je�eli takowy istnieje, musi istnie� plik)
	{
		log.open("log_aktualny.txt", ios::in); //Otworzenie pliku w trybie odczytu z pliku
		string buf, bufor2; //Uworzenie 2 bufor�w na tekst, pierwszy na ostatni� linie tekst, drugi na przedostani� nie pust� linie tekstu lub ostani� w przypadku gdy ostania jest pusta
		getline(log, buf); //Odczyt ca�ej lini z pliku
		while (!log.eof()) //P�tla dzia�j�ca do czasu kiedy kursor odczytu z pliku nie b�dzie na ko�cu pliku
		{
			if (buf != "") bufor2 = buf; //Sprawdzenie czy odczytana linia nie jest pusta, je�eli nie jest pusta to skopiowanie do drugiego bufora celem posiadania dw�ch ostatnich linijek tekstu b�d�cego w pliku
			getline(log, buf); //Odczyt ca�ej lini z pliku
		}
		if (buf == "") buf = bufor2; //Sprawdzenie czy linia w buforze jest pusta, je�eli jest pusta to zastopienie jej poprzedni� lini� tekstu z pliku
		if (buf.find("Posiadasz") != string::npos) //Sprawdzenie czy w ostatniej niepustej lini znajduj� si� s�owa �wiadcz�ce o sko�czeniu rundy
		{
			co_kontynuowa� = 'n'; //Je�eli si� znajduj� to przypisanie znaku rozpocz�cia rundy od pocz�tku
			auto pocz�tek = (unsigned short)buf.size(); //Utworzenie i przypisanie do zmiennej wskazuj�cej pocz�tek tekst pozycji ostatniego znaku tekstu o kwocie pieni�dzy kt�r� posiada jeszcze gracz, typ zmiennej auto wsazuje, �e kompilator sam wybierze typ zmiennej
			while (buf[pocz�tek] != ' ' && pocz�tek > 0) --pocz�tek; //Poszukiwanie od ko�ca spacji po kt�rej jest kwota pieni�dzy kt�r� posiada jeszcze gracz
			++pocz�tek; //Kwota jest na nast�pnym znaku wi�c przesuni�cie o jeden znak do przodu
			string buf2 = buf; //Utworzenie bufora pomocniczego do ci�cia tekstu i w�o�enie do niego wcze�niej odczytanego tekstu
			buf2.erase(0, pocz�tek); //Usuni�cie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna� si� liczb�
			buf2.erase(buf2.size() - 1, 1); //Usuni�cie z bufora pomocniczego znaku dolara z prawej strony
			ilo��_pieni�dzy = atoi(buf2.c_str()); //Zamiana liczby w tek�cie na warto�� w zmiennnej liczbowej
		}
		else if (buf.find("Wylosowano") != string::npos) //Sprawdzenie czy w ostatniej niepustej lini znajduj� si� s�owa �wiadcz�ce o wylosowaniu liczby
		{
			co_kontynuowa� = 'w'; //Je�eli si� znajduj� to przypisanie znaku rozpocz�cia rundy od sprawdzenia wygranej
			unsigned short pocz�tek = 0; //Utworzenie i przypisanie zera do zmiennej wskazuj�cej pocz�tek tekst o wylosowanej liczbie
			while (buf[pocz�tek] != 'y' && pocz�tek < (int)buf.size()) ++pocz�tek; //Poszukiwanie od pocz�tku litery y kt�ra wyst�puje w wyrazie po kt�rym jest wylosowana liczba
			pocz�tek += 10; //Przesuni�cie o +10 pozycji pocz�tku tekstu o po kt�rej jest wylosowana liczba
			string buf2 = buf; //Utworzenie bufora pomocniczego do ci�cia tekstu i w�o�enie do niego wcze�niej odczytanego tekstu
			buf2.erase(0, pocz�tek); //Usuni�cie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna� si� liczb�
			wylosowana_liczba = atoi(buf2.c_str()); //Zamiana liczby w tek�cie na warto�� w zmiennnej liczbowej
			pocz�tek = 0; //Przypisanie zera do zmiennej wskazuj�cej pocz�tek tekst o typie zak�adu
			while (buf[pocz�tek] != 'd' && pocz�tek < (int)buf.size()) ++pocz�tek;
			pocz�tek += 2;  //Przesuni�cie o +2 pozycji pocz�tku tekstu o po kt�rej jest typ zak�adu
			buf2 = buf; //Utworzenie bufora pomocniczego do ci�cia tekstu i w�o�enie do niego wcze�niej odczytanego tekstu
			buf2.erase(0, pocz�tek); //Usuni�cie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna� si� liczb�
			buf2.erase(buf2.find(" Wylosowano"), buf2.size() - buf2.find(" Wylosowano"));
			typ_zak�adu = buf2; //Przypisanie do zmiennej przechowywuj�cej typ zak�adu wczytanego typu zak�adu
			buf.erase(buf.find("Obstawiono zaklad"), buf.size() - buf.find("Obstawiono zaklad"));
			pocz�tek = 0; //Przypisanie zera do zmiennej wskazuj�cej pocz�tek tekst o kwocie zak�adu
			if (buf[12] == 'a') { pocz�tek = 14; } //Sprawdzenie czy na pozycji 12 teksty znajduje si� litera a �wiadcz�ca o wyrazie po kt�rym jest kwota zak�adu, je�eli tak to pozycja pocz�tkowa tekstu wynosi 14
			else //Je�eli nie to
			{
				while (buf[pocz�tek] != 'z' && pocz�tek < (unsigned short)buf.size()) ++pocz�tek; //Poszukanie litery z �wiadcz�cej o wyrazie po kt�rym jest kwota zak�adu
				pocz�tek += 3; //Po znalezienu z przesuwamy pozycje +3
			}
			int koniec = pocz�tek + 1; //Przypisanie do zmiennej pozycji pocz�tku +1 wskazuj�cej koniec tekst o kwocie zak�adu
			while (buf[koniec] != '$' && koniec < (unsigned short)buf.size()) ++koniec; //Poszukujemy znaku dolara przed kt�rym jest kwota zak�adu
			buf2 = buf; //Utworzenie bufora pomocniczego do ci�cia tekstu i w�o�enie do niego wcze�niej odczytanego tekstu
			buf2.erase(koniec, buf2.size() - koniec); //Usuni�cie z bufora pomocniczego tekstu z prawej strony, aby tekst ko�czy� si� liczb�
			buf2.erase(0, pocz�tek); //Usuni�cie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna� si� liczb�
			kwota_zak�adu = atoi(buf2.c_str()); //Zamiana liczby w tek�cie na warto�� w zmiennnej liczbowej
			pocz�tek = (unsigned short)bufor2.size(); //Utworzenie i przypisanie do zmiennej wskazuj�cej pocz�tek tekst o kwocie pieni�dzy kt�r� posiada jeszcze gracz
			while (bufor2[pocz�tek] != ' ' && pocz�tek > 0) --pocz�tek; //Poszukiwanie od ko�ca spacji po kt�rej jest kwota pieni�dzy kt�r� posiada jeszcze gracz
			++pocz�tek; //Kwota jest na nast�pnym znaku wi�c przesuni�cie o jeden znak do przodu
			buf2 = bufor2; //Przypisanie do bufora pomocniczego do ci�cia tekstu i w�o�enie do niego linie o jedn� wcze�niej wcze�niej odczytanego tekstu
			buf2.erase(0, pocz�tek); //Usuni�cie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna� si� liczb�
			buf2.erase(buf2.size() - 1, 1); //Usuni�cie z bufora pomocniczego znaku dolara z prawej strony
			ilo��_pieni�dzy = atoi(buf2.c_str()); //Zamiana liczby w tek�cie na warto�� w zmiennnej liczbowej
		}
		else if (buf.find("Obstawiono zaklad") != string::npos) //Sprawdzenie czy w ostatniej niepustej lini znajduj� si� s�owa �wiadcz�ce o typie obstawionego zak�adu
		{
			co_kontynuowa� = 't'; //Je�eli si� znajduj� to przypisanie znaku rozpocz�cia rundy od wylosowania liczby
			unsigned short pocz�tek = 0; //Utworzenie i przypisanie zera do zmiennej wskazuj�cej pocz�tek tekst o typie zak�adu
			while (buf[pocz�tek] != 'd' && pocz�tek < (unsigned short)buf.size()) ++pocz�tek;
			pocz�tek += 2; //Przesuni�cie pozycji pocz�tku tekstu o 2 po kt�rej jest typ zak�adu
			string buf2 = buf; //Utworzenie bufora pomocniczego do ci�cia tekstu i w�o�enie do niego wcze�niej odczytanego tekstu
			buf2.erase(0, pocz�tek); //Usuni�cie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna� si� liczb�
			typ_zak�adu = buf2; //Przypisanie do zmiennej przechowywuj�cej typ zak�adu wczytanego typu zak�adu
			buf.erase(buf.find("Obstawiono zaklad"), buf.size() - buf.find("Obstawiono zaklad"));
			pocz�tek = 0; //Przypisanie zera do zmiennej wskazuj�cej pocz�tek tekst o kwocie zak�adu
			if (buf[12] == 'a') pocz�tek = 14; //Sprawdzenie czy na pozycji 12 teksty znajduje si� litera a �wiadcz�ca o wyrazie po kt�rym jest kwota zak�adu, je�eli tak to pozycja pocz�tkowa tekstu wynosi 14
			else //Je�eli nie to
			{
				while (buf[pocz�tek] != 'z' && pocz�tek < (int)buf.size()) ++pocz�tek; //Poszukanie litery z �wiadcz�cej o wyrazie po kt�rym jest kwota zak�adu
				pocz�tek += 3; //Po znalezienu z przesuwamy pozycje +3
			}
			unsigned short koniec = pocz�tek + 1; //Przypisanie do zmiennej pozycji pocz�tku +1 wskazuj�cej koniec tekst o kwocie zak�adu
			while (buf[koniec] != '$' && koniec < (unsigned short)buf.size()) ++koniec; //P�tla poszukuj�ca znaku dolara, p�tla ko�czy si� znalezieniem znaku dolara
			buf2 = buf; //W�o�enie do bufora pomocniczego do ci�cia tekstu wcze�niej odczytanego tekstu
			buf2.erase(koniec, buf2.size() - koniec); //Usuni�cie z bufora pomocniczego tekstu z prawej strony, aby tekst ko�czy� si� liczb�
			buf2.erase(0, pocz�tek); //Usuni�cie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna� si� liczb�
			kwota_zak�adu = atoi(buf2.c_str()); //Zamiana liczby w tek�cie na warto�� w zmiennnej liczbowej
			pocz�tek = (unsigned short)bufor2.size(); //Utworzenie i przypisanie do zmiennej wskazuj�cej pocz�tek tekst o kwocie pieni�dzy kt�r� posiada jeszcze gracz
			while (bufor2[pocz�tek] != ' ' && pocz�tek > 0) --pocz�tek; //Poszukiwanie od ko�ca spacji po kt�rej jest kwota pieni�dzy kt�r� posiada jeszcze gracz
			++pocz�tek; //Kwota jest na nast�pnym znaku wi�c przesuni�cie o jeden znak do przodu
			buf2 = bufor2; //Przypisanie do bufora pomocniczego do ci�cia tekstu i w�o�enie do niego linie o jedn� wcze�niej wcze�niej odczytanego tekstu
			buf2.erase(0, pocz�tek); //Usuni�cie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna� si� liczb�
			buf2.erase(buf2.size() - 1, 1); //Usuni�cie z bufora pomocniczego znaku dolara z prawej strony
			ilo��_pieni�dzy = atoi(buf2.c_str()); //Zamiana liczby w tek�cie na warto�� w zmiennnej liczbowej
		}
		else if (buf.find("Obstawiono za") != string::npos) //Sprawdzenie czy w ostatniej niepustej lini znajduj� si� s�owa �wiadcz�ce o kwocie obstawionego zak�adu
		{
			co_kontynuowa� = 'k';  //Je�eli si� znajduj� to przypisanie znaku rozpocz�cia rundy od zapytania o typ zak�adu
			unsigned short pocz�tek = 0; //Utworzenie i przypisanie do zmiennej wskazuj�cej pocz�tek tekst o kwocie pieni�dzy kt�r� posiada jeszcze gracz
			if (buf[12] == 'a') { pocz�tek = 14; } //Sprawdzenie czy na pozycji 12 teksty znajduje si� litera a �wiadcz�ca o wyrazie po kt�rym jest kwota zak�adu, je�eli tak to pozycja pocz�tkowa tekstu wynosi 14
			else //Je�eli nie to
			{
				while (buf[pocz�tek] != 'z' && pocz�tek < (unsigned short)buf.size()) ++pocz�tek; //Poszukanie litery z �wiadcz�cej o wyrazie po kt�rym jest kwota zak�adu
				pocz�tek += 3; //Po znalezienu z przesuwamy pozycje +3
			}
			unsigned short koniec = pocz�tek + 1; //Utworzenie i przypisanie do zmiennej pozycji pocz�tku +1 wskazuj�cej koniec tekst o kwocie zak�adu
			while (buf[koniec] != '$' && koniec < (int)buf.size()) ++koniec;
			string buf2 = buf; //Utworzenie bufora pomocniczego do ci�cia tekstu i w�o�enie do niego wcze�niej odczytanego tekstu
			buf2.erase(koniec, buf2.size() - koniec); //Usuni�cie z bufora pomocniczego tekstu z prawej strony, aby tekst ko�czy� si� liczb�
			buf2.erase(0, pocz�tek); //Usuni�cie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna� si� liczb�
			kwota_zak�adu = atoi(buf2.c_str()); //Zamiana liczby w tek�cie na warto�� w zmiennnej liczbowej
			pocz�tek = (unsigned short)bufor2.size(); //Utworzenie i przypisanie do zmiennej wskazuj�cej pocz�tek tekst o kwocie pieni�dzy kt�r� posiada jeszcze gracz
			while (bufor2[pocz�tek] != ' ' && pocz�tek > 0) --pocz�tek; //Poszukiwanie od ko�ca spacji po kt�rej jest kwota pieni�dzy kt�r� posiada jeszcze gracz
			++pocz�tek; //Kwota jest na nast�pnym znaku wi�c przesuni�cie o jeden znak do przodu
			buf2 = bufor2; //Przypisanie do bufora pomocniczego do ci�cia tekstu i w�o�enie do niego linie o jedn� wcze�niej wcze�niej odczytanego tekstu
			buf2.erase(0, pocz�tek); //Usuni�cie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna� si� liczb�
			buf2.erase(buf2.size() - 1, 1); //Usuni�cie z bufora pomocniczego znaku dolara z prawej strony
			ilo��_pieni�dzy = atoi(buf2.c_str()); //Zamiana liczby w tek�cie na warto�� w zmiennnej liczbowej
		}
		else if (buf.find("Gra rozpoczeta dnia") != string::npos) //Sprawdzenie czy w ostatniej niepustej lini znajduj� si� s�owa �wiadcz�ce o rozpocz�ciu nowej gry
		{
			co_kontynuowa� = 'n'; //Je�eli si� znajduj� to przypisanie znaku rozpocz�cia rundy od pocz�tku
		}
		else //Je�eli co� p�jdzie nie tak, to warunek aby gra si� niewysypa�a
		{
			co_kontynuowa� = 'n'; //Je�eli si� znajduj� to przypisanie znaku rozpocz�cia rundy od pocz�tku
		}
		log.close(); //Zamkni�cie pliku logu og�lnego
		log.open("log_aktualny.txt", ios::out | ios::app); //Ponowne wczytanie pliku, teraz tylko do odczytu i ustawienie kursora zapisu na koniec pliku
	}
	else
	{
		co_kontynuowa� = 'n'; //Przypisanie znaku rozpocz�cia rundy od pocz�tku
		log.open("log_aktualny.txt", ios::out);
		GetSystemTime(&Czas); //Pobieranie aktualnej daty i czasu z zegara systemowego
		log << "Gra rozpoczeta dnia " << Czas.wDay << "." << Czas.wMonth << "." << Czas.wYear << " o godzinie "; //Wpisanie do bufora zapisu danych o dniu,miesi�cu i roku do pliku log_aktualny.txt
		if (Czas.wHour < 10) log << "0"; //Wpisanie do bufora zapisu znaku zera dla r�wnego formatowania godzinny je�eli godzina jest minejsza ni� 10 do pliku log_aktualny.txt
		log << Czas.wHour << ":"; //Wpisanie do bufora zapisu znaku : dla rozdzielenia godzin od minut do pliku log_aktualny.txt
		if (Czas.wMinute < 10) log << "0"; //Wpisanie do bufora zapisu znaku zera dla r�wnego formatowania minut je�eli minuty jest minejsze ni� 10 do pliku log_aktualny.txt
		log << Czas.wMinute << ":"; //Wpisanie do bufora zapisu znaku : dla rozdzielenia minut od sekund do pliku log_aktualny.txt
		if (Czas.wSecond < 10) log << "0"; //Wpisanie do bufora zapisu znaku zera dla r�wnego formatowania sekund je�eli sekundy jest minejsza ni� 10 do pliku log_aktualny.txt
		log << Czas.wSecond << endl; // Wpisanie do bufora zapisu danych o sekundzie do pliku log_aktualny.txt
		log_og�lny << "Nowa gra rozpoczeta dnia " << Czas.wDay << "." << Czas.wMonth << "." << Czas.wYear << " o godzinie "; //Wpisanie do bufora zapisu danych o dniu,miesi�cu i roku do pliku log_og�lny.txt
		if (Czas.wHour < 10) log_og�lny << "0"; //Wpisanie do bufora zapisu znaku zera dla r�wnego formatowania godzinny je�eli godzina jest minejsza ni� 10 do pliku log_og�lny.txt
		log_og�lny << Czas.wHour << ":";//Wpisanie do bufora zapisu znaku : dla rozdzielenia godzin od minut do pliku log_aktualny.txt
		if (Czas.wMinute < 10) log_og�lny << "0"; //Wpisanie do bufora zapisu znaku zera dla r�wnego formatowania minut je�eli minuty jest minejsza ni� 10 do pliku log_og�lny.txt
		log_og�lny << Czas.wMinute << ":"; //Wpisanie do bufora zapisu znaku : dla rozdzielenia minut od sekund do pliku log_og�lny.txt
		if (Czas.wSecond < 10) log_og�lny << "0"; //Wpisanie do bufora zapisu znaku zera dla r�wnego formatowania sekund je�eli sekundy jest minejsza ni� 10 do pliku log_og�lny.txt
		log_og�lny << Czas.wSecond << endl; // Wpisanie do bufora zapisu danych o sekundzie do pliku log_og�lny.txt
		log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
		log_og�lny.flush(); //Zapisanie do pliku log_og�lny.txt danych wpisanych do bufora danych
	}
}

void Sprawd�_Pliki()
{
	if (stan_d�wi�k�w == 1)
		if (efekty_d�wi�kowe == 1)
		{
			if ((_access("Efekty_d�wi�kowe", 0)))
			{
				CreateDirectoryA("Efekty_d�wi�kowe", nullptr);
			}

			bool czy_pobierano = false;
			bool czy_pobrano = true;

			if ((_access("Efekty_d�wi�kowe/bankrut.wav", 0)))
			{
				if (!czy_pobierano) cout << "Rozpoczynam pobieranie brakuj�cych plik�w efekt�w" << endl;
				czy_pobierano = true;
				auto res = URLDownloadToFileA(nullptr, "https://github.com/talez2709/Ruletka/raw/master/Ruletka/Efekty_d%C5%BAwi%C4%99kowe/bankrut.wav", "Efekty_d�wi�kowe/bankrut.wav", 0, nullptr);
				if (res != S_OK)
				{
					czy_pobrano = false;
					cout << "Brak plik�w dla efekt�w d�wi�kowych oraz nie mo�na pobra� danych, wy��czono efekty d�wi�kowe muzyczne, w��czono efekty systemowe" << endl;
					EfektyKompletne = false; //Wpisanie do zmiennej warto�ci false informuj�cej o niekompletnych plikach audio
					return; //Wyj�cie z funkcji poniewa� nie ma sensu sprawdzania dalej
				}
			}

			if ((_access("Efekty_d�wi�kowe/wygrana1.wav", 0)))
			{
				if (!czy_pobierano) cout << "Rozpoczynam pobieranie brakuj�cych plik�w efekt�w" << endl;
				czy_pobierano = true;
				auto res = URLDownloadToFileA(nullptr, "https://github.com/talez2709/Ruletka/raw/master/Ruletka/Efekty_d%C5%BAwi%C4%99kowe/bankrut.wav", "Efekty_d�wi�kowe/wygrana1.wav", 0, nullptr);
				if (res != S_OK)
				{
					czy_pobrano = false;
					cout << "Brak plik�w dla efekt�w d�wi�kowych oraz nie mo�na pobra� danych, wy��czono efekty d�wi�kowe muzyczne, w��czono efekty systemowe" << endl;
					EfektyKompletne = false; //Wpisanie do zmiennej warto�ci false informuj�cej o niekompletnych plikach audio
					return; //Wyj�cie z funkcji poniewa� nie ma sensu sprawdzania dalej
				}
			}

			if ((_access("Efekty_d�wi�kowe/wygrana2.wav", 0)))
			{
				if (!czy_pobierano) cout << "Rozpoczynam pobieranie brakuj�cych plik�w efekt�w" << endl;
				czy_pobierano = true;
				auto res = URLDownloadToFileA(nullptr, "https://github.com/talez2709/Ruletka/raw/master/Ruletka/Efekty_d%C5%BAwi%C4%99kowe/wygrana2.wav", "Efekty_d�wi�kowe/wygrana2.wav", 0, nullptr);
				if (res != S_OK)
				{
					czy_pobrano = false;
					cout << "Brak plik�w dla efekt�w d�wi�kowych oraz nie mo�na pobra� danych, wy��czono efekty d�wi�kowe muzyczne, w��czono efekty systemowe" << endl;
					EfektyKompletne = false; //Wpisanie do zmiennej warto�ci false informuj�cej o niekompletnych plikach audio
					return; //Wyj�cie z funkcji poniewa� nie ma sensu sprawdzania dalej
				}
			}

			if ((_access("Efekty_d�wi�kowe/zwielokrotnenie.wav", 0)))
			{
				if (!czy_pobierano) cout << "Rozpoczynam pobieranie brakuj�cych plik�w efekt�w" << endl;
				czy_pobierano = true;
				auto res = URLDownloadToFileA(nullptr, "https://github.com/talez2709/Ruletka/raw/master/Ruletka/Efekty_d%C5%BAwi%C4%99kowe/zwielokrotnenie.wav", "Efekty_d�wi�kowe/zwielokrotnenie.wav", 0, nullptr);
				if (res != S_OK)
				{
					czy_pobrano = false;
					cout << "Brak plik�w dla efekt�w d�wi�kowych oraz nie mo�na pobra� danych, wy��czono efekty d�wi�kowe muzyczne, w��czono efekty systemowe" << endl;
					EfektyKompletne = false; //Wpisanie do zmiennej warto�ci false informuj�cej o niekompletnych plikach audio
					return; //Wyj�cie z funkcji poniewa� nie ma sensu sprawdzania dalej
				}
			}

			if (czy_pobierano) if (czy_pobierano) cout << "Pobrano brakuj�ce pliki efekt�w" << endl;
		}

	if (stan_d�wi�k�w == 1)
		if (g�os_odczytu_numeru > 0)
		{
			string buf; //Utworzenie bufora tekstowego do celu sprawdzania plik�w z g�osem

			G�os = "G�os/"; //Wpisanie do zmiennej G�os pocz�tku �cie�ki do pliku z g�osem

			switch (g�os_odczytu_numeru) //U�ycie warunku wielokrotnego wyboru do wpisania odpowiedniej nazwy g�osu do zmiennej g�os_nazwa
			{
			case 1: //Gdy g�os_odczytu_numeru==1
			{
				G�os += "Jacek"; //Dodanie do zmiennej nazwy wybranego g�osu Jacek
				break; //Wyj�cie z instrukcji case //Wyj�cie z instrukcji case
			}
			case 2: //Gdy g�os_odczytu_numeru==2
			{
				G�os += "Ewa"; //Dodanie do zmiennej nazwy wybranego g�osu Ewa
				break; //Wyj�cie z instrukcji case
			}
			case 3: //Gdy g�os_odczytu_numeru==3
			{
				G�os += "Maja"; //Dodanie do zmiennej nazwy wybranego g�osu Maja
				break; //Wyj�cie z instrukcji case
			}
			case 4: //Gdy g�os_odczytu_numeru==4
			{
				G�os += "Jan"; //Dodanie do zmiennej nazwy wybranego g�osu Jan
				break; //Wyj�cie z instrukcji case
			}
			case 5: //Gdy g�os_odczytu_numeru==5
			{
				G�os += "Jacek2"; //Dodanie do zmiennej nazwy wybranego g�osu Jacek 2
				break; //Wyj�cie z instrukcji case
			}

			case 6: //Gdy g�os_odczytu_numeru==6
			{
				G�os += "Ewa2"; //Dodanie do zmiennej nazwy wybranego g�osu Ewa 2
				break; //Wyj�cie z instrukcji case
			}
			case 7: //Gdy g�os_odczytu_numeru==7
			{
				G�os += "Maja2"; //Dodanie do zmiennej nazwy wybranego g�osu Maja 2
				break; //Wyj�cie z instrukcji case
			}
			case 8: //Gdy g�os_odczytu_numeru==8
			{
				G�os += "Jan2"; //Dodanie do zmiennej nazwy wybranego g�osu Jan 2
				break; //Wyj�cie z instrukcji case
			}
			case 9: //Gdy g�os_odczytu_numeru==9
			{
				G�os += "Agata"; //Dodanie do zmiennej nazwy wybranego g�osu Agata
				break; //Wyj�cie z instrukcji case
			}
			default: //Je�eli �aden warunek nie jest spe�niony to
				break; //Wyj�cie z instrukcji case
			}

			G�os += "_"; //Dodanie do zmiennej podkre�lenia odzielaj�cego nazw� od szybko�ci
			G�os += '0' + g�os_szybko��_odczytu_numeru; //Dodanie do zmiennej szybko�ci mowy
			G�os += "/"; //Dodanie do zmiennej uko�nika kt�ry odziela nazw� folderu od pliku

			string link = "https://github.com/talez2709/Ruletka/raw/master/Ruletka/G%C5%82os/";

			string g�os2 = G�os;
			g�os2.erase(0, 5);

			if ((_access("G�os", 0)))
			{
				CreateDirectoryA("G�os", nullptr);
			}
			if ((_access(("G�os/" + g�os2).c_str(), 0)))
			{
				CreateDirectoryA(("G�os/" + g�os2).c_str(), nullptr);
			}

			bool czy_pobierano = false;
			bool czy_pobrano = true;

			if ((_access((G�os + "p.wav").c_str(), 0)))
			{
				if (!czy_pobierano) cout << "Rozpoczynam pobieranie brakuj�cych plik�w g�os�w" << endl;
				czy_pobierano = true;
				auto res = URLDownloadToFileA(nullptr, (link + g�os2 + "p.wav").c_str(), ("G�os/" + g�os2 + "p.wav").c_str(), 0, nullptr);
				if (res != S_OK)
				{
					czy_pobrano = false;
					cout << "Brak plik�w dla g�osu oraz nie mo�na pobra� danych, wy��czono odczytywanie wyniku" << endl;
					G�osyKompletne = false; //Wpisanie do zmiennej warto�ci false informuj�cej o niekompletnych plikach audio
					return; //Wyj�cie z funkcji poniewa� nie ma sensu sprawdzania dalej
				}
			}

			if ((_access((G�os + "n.wav").c_str(), 0)))
			{
				if (!czy_pobierano) cout << "Rozpoczynam pobieranie brakuj�cych plik�w g�os�w" << endl;
				czy_pobierano = true;
				auto res = URLDownloadToFileA(nullptr, (link + g�os2 + "n.wav").c_str(), ("G�os/" + g�os2 + "n.wav").c_str(), 0, nullptr);
				if (res != S_OK)
				{
					czy_pobrano = false;
					cout << "Brak plik�w dla g�osu oraz nie mo�na pobra� danych, wy��czono odczytywanie wyniku" << endl;
					G�osyKompletne = false; //Wpisanie do zmiennej warto�ci false informuj�cej o niekompletnych plikach audio
					return; //Wyj�cie z funkcji poniewa� nie ma sensu sprawdzania dalej
				}
			}

			if ((_access((G�os + "r.wav").c_str(), 0)))
			{
				if (!czy_pobierano) cout << "Rozpoczynam pobieranie brakuj�cych plik�w g�os�w" << endl;
				czy_pobierano = true;
				auto res = URLDownloadToFileA(nullptr, (link + g�os2 + "r.wav").c_str(), ("G�os/" + g�os2 + "r.wav").c_str(), 0, nullptr);
				if (res != S_OK)
				{
					czy_pobrano = false;
					cout << "Brak plik�w dla g�osu oraz nie mo�na pobra� danych, wy��czono odczytywanie wyniku" << endl;
					G�osyKompletne = false; //Wpisanie do zmiennej warto�ci false informuj�cej o niekompletnych plikach audio
					return; //Wyj�cie z funkcji poniewa� nie ma sensu sprawdzania dalej
				}
			}

			if ((_access((G�os + "b.wav").c_str(), 0)))
			{
				if (!czy_pobierano) cout << "Rozpoczynam pobieranie brakuj�cych plik�w g�os�w" << endl;
				czy_pobierano = true;
				auto res = URLDownloadToFileA(nullptr, (link + g�os2 + "b.wav").c_str(), ("G�os/" + g�os2 + "b.wav").c_str(), 0, nullptr);
				if (res != S_OK)
				{
					czy_pobrano = false;
					cout << "Brak plik�w dla g�osu oraz nie mo�na pobra� danych, wy��czono odczytywanie wyniku" << endl;
					G�osyKompletne = false; //Wpisanie do zmiennej warto�ci false informuj�cej o niekompletnych plikach audio
					return; //Wyj�cie z funkcji poniewa� nie ma sensu sprawdzania dalej
				}
			}

			if ((_access((G�os + "g.wav").c_str(), 0)))
			{
				if (!czy_pobierano) cout << "Rozpoczynam pobieranie brakuj�cych plik�w g�os�w" << endl;
				czy_pobierano = true;
				auto res = URLDownloadToFileA(nullptr, (link + g�os2 + "g.wav").c_str(), ("G�os/" + g�os2 + "g.wav").c_str(), 0, nullptr);
				if (res != S_OK)
				{
					czy_pobrano = false;
					cout << "Brak plik�w dla g�osu oraz nie mo�na pobra� danych, wy��czono odczytywanie wyniku" << endl;
					G�osyKompletne = false; //Wpisanie do zmiennej warto�ci false informuj�cej o niekompletnych plikach audio
					return; //Wyj�cie z funkcji poniewa� nie ma sensu sprawdzania dalej
				}
			}

			if ((_access((G�os + "d.wav").c_str(), 0)))
			{
				if (!czy_pobierano) cout << "Rozpoczynam pobieranie brakuj�cych plik�w g�os�w" << endl;
				czy_pobierano = true;
				auto res = URLDownloadToFileA(nullptr, (link + g�os2 + "d.wav").c_str(), ("G�os/" + g�os2 + "d.wav").c_str(), 0, nullptr);
				if (res != S_OK)
				{
					czy_pobrano = false;
					cout << "Brak plik�w dla g�osu oraz nie mo�na pobra� danych, wy��czono odczytywanie wyniku" << endl;
					G�osyKompletne = false; //Wpisanie do zmiennej warto�ci false informuj�cej o niekompletnych plikach audio
					return; //Wyj�cie z funkcji poniewa� nie ma sensu sprawdzania dalej
				}
			}

			for (unsigned short i = 1; i <= 3; ++i)
			{
				stringstream numers;
				numers << i;
				if ((_access((G�os + "k" + numers.str() + ".wav").c_str(), 0)))
				{
					if (!czy_pobierano) cout << "Rozpoczynam pobieranie brakuj�cych plik�w g�os�w" << endl;
					czy_pobierano = true;
					auto res = URLDownloadToFileA(nullptr, (link + g�os2 + "k" + numers.str() + ".wav").c_str(), ("G�os/" + g�os2 + "k" + numers.str() + ".wav").c_str(), 0, nullptr);
					if (res != S_OK)
					{
						czy_pobrano = false;
						cout << "Brak plik�w dla g�osu oraz nie mo�na pobra� danych, wy��czono odczytywanie wyniku" << endl;
						G�osyKompletne = false; //Wpisanie do zmiennej warto�ci false informuj�cej o niekompletnych plikach audio
						return; //Wyj�cie z funkcji poniewa� nie ma sensu sprawdzania dalej
					}
				}
			}

			for (unsigned short i = 1; i <= 12; ++i)
			{
				stringstream numers;
				numers << i;
				if ((_access((G�os + "w" + numers.str() + ".wav").c_str(), 0)))
				{
					if (!czy_pobierano) cout << "Rozpoczynam pobieranie brakuj�cych plik�w g�os�w" << endl;
					czy_pobierano = true;
					auto res = URLDownloadToFileA(nullptr, (link + g�os2 + "w" + numers.str() + ".wav").c_str(), ("G�os/" + g�os2 + "w" + numers.str() + ".wav").c_str(), 0, nullptr);
					if (res != S_OK)
					{
						czy_pobrano = false;
						cout << "Brak plik�w dla g�osu oraz nie mo�na pobra� danych, wy��czono odczytywanie wyniku" << endl;
						G�osyKompletne = false; //Wpisanie do zmiennej warto�ci false informuj�cej o niekompletnych plikach audio
						return; //Wyj�cie z funkcji poniewa� nie ma sensu sprawdzania dalej
					}
				}
			}

			for (unsigned short i = 0; i <= 36; ++i)
			{
				stringstream numers;
				numers << i;
				if ((_access((G�os + numers.str() + ".wav").c_str(), 0)))
				{
					if (!czy_pobierano) cout << "Rozpoczynam pobieranie brakuj�cych plik�w g�os�w" << endl;
					czy_pobierano = true;
					auto res = URLDownloadToFileA(nullptr, (link + g�os2 + numers.str() + ".wav").c_str(), ("G�os/" + g�os2 + numers.str() + ".wav").c_str(), 0, nullptr);
					if (res != S_OK)
					{
						czy_pobrano = false;
						cout << "Brak plik�w dla g�osu oraz nie mo�na pobra� danych, wy��czono odczytywanie wyniku" << endl;
						G�osyKompletne = false; //Wpisanie do zmiennej warto�ci false informuj�cej o niekompletnych plikach audio
						return; //Wyj�cie z funkcji poniewa� nie ma sensu sprawdzania dalej
					}
				}
			}

			if (czy_pobierano) if (czy_pobierano) cout << "Pobrano brakuj�ce pliki g�os�w" << endl;
		}
}

void Sprawd�_ustawienia()
{
	if (!_access("setting.txt", 0)) // Sprawdzenie dost�pu do pliku (je�eli takowy istnieje, musi istnie� plik)
	{
		ifstream ustawienia; //Utworzenie typu do celu odczytu z pliku
		ustawienia.open("setting.txt"); //Otwarcie pliku z ustawieniami
		string buf; //Utworzenie buforu do odczytu z pliku
		while (!ustawienia.eof()) //P�tla trwaj�ca do ko�ca pliku
		{
			getline(ustawienia, buf); //Wczytanie ca�ej lini tekstu z pliku
			Ustaw_ustawienia(buf); //Zamiana wczytanej lini na ustawienie programu
		}
	}
	else
	{
		ofstream ustawienia; //Utworzenie typu do celu zapisu do pliku
		ustawienia.open("setting.txt"); //Otwarcie pliku do wygenerowania ustawie� domy�lnych
		ustawienia << "ilo��_minimalna_obrot�w_ruletki 2" << endl; //Wpisanie do pliku domy�nych ustawie� dotycz�cych ilo��_minimalna_obrot�w_ruletki
		ustawienia << "ilo��_max_dodatkowych_obrot�w_ruletki 3" << endl; //Wpisanie do pliku domy�nych ustawie� dotycz�cych ilo��_max_dodatkowych_obrot�w_ruletki
		ustawienia << "czas_przeskoku_kulki_szybki 50" << endl; //Wpisanie do pliku domy�nych ustawie� dotycz�cych czas_przeskoku_kulki_szybki
		ustawienia << "czas_przeskoku_kulki_wolny 75" << endl; //Wpisanie do pliku domy�nych ustawie� dotycz�cych czas_przeskoku_kulki_wolny
		ustawienia << "czas_przerwy_dzwi�ku 500" << endl; //Wpisanie do pliku domy�nych ustawie� dotycz�cych czas_przerwy_dzwi�ku
		ustawienia << "styl_liczenia_wygranej 1" << endl; //Wpisanie do pliku domy�nych ustawie� dotycz�cych styl_liczenia_wygranej
		ustawienia << "kwota_pocz�tkowa 1000" << endl; //Wpisanie do pliku domy�nych ustawie� dotycz�cych kwota_pocz�tkowa
		ustawienia << "stan_d�wi�k�w 1" << endl; //Wpisanie do pliku domy�nych ustawie� dotycz�cych stan_d�wi�k�w
		ustawienia << "czy_kontynuowa�_gr� 1" << endl; //Wpisanie do pliku domy�nych ustawie� dotycz�cych czy_kontynuowa�_gr�
		ustawienia << "g�os_odczytu_numeru 1" << endl; //Wpisanie do pliku domy�nych ustawie� dotycz�cych g�os_odczytu_numeru
		ustawienia << "g�os_szybko��_odczytu_numeru 4" << endl; //Wpisanie do pliku domy�nych ustawie� dotycz�cych g�os_szybko��_odczytu_numeru
		ustawienia << "efekty_d�wi�kowe 1" << endl; //Wpisanie do pliku domy�nych ustawie� dotycz�cych efekty_d�wi�kowe
	}

	if (czas_przeskoku_kulki_wolny < czas_przeskoku_kulki_szybki)
	{
		cout << "Warto�� wolnego czasu przeskoku kulki musi by� ni�sza ni� warto�� szybkiego czasu przeskoku kulki" << endl; //(Warto�ci tych zmiennych to czas op�nienia wi�c im jest wy�szy tym d�u�sza przerwa)
		cout << "Ustawiam domy�lne ustawienie" << endl;
		czas_przeskoku_kulki_szybki = 50;
		czas_przeskoku_kulki_wolny = 75;
	}
	if (ilo��_minimalna_obrot�w_ruletki < 0)
	{
		cout << "Ilo�� minimalna obrot�w ruletki nie mo�e by� mniejsza od 0" << endl;
		cout << "Ustawiam domy�lne ustawienie" << endl;
		ilo��_minimalna_obrot�w_ruletki = 2;
	}
	if (ilo��_max_dodatkowych_obrot�w_ruletki < 0)
	{
		cout << "Ilo�� max obrot�w ruletki nie mo�e by� mniejsza od 0" << endl;
		cout << "Ustawiam domy�lne ustawienie" << endl;
		ilo��_max_dodatkowych_obrot�w_ruletki = 3;
	}
	if ((ilo��_minimalna_obrot�w_ruletki == 0) && (ilo��_max_dodatkowych_obrot�w_ruletki == 0))
	{
		cout << "Jedna z deklaracji w sprawie obrot�w ruletki musi by� wi�ksza od zera" << endl;
		cout << "Ustawiam domy�lne ustawienie" << endl;
		ilo��_minimalna_obrot�w_ruletki = 2;
		ilo��_max_dodatkowych_obrot�w_ruletki = 3;
	}
	if (((styl_liczenia_wygranej > 1) || (styl_liczenia_wygranej < 0)))
	{
		cout << "Styl liczeia wygranej przyjmuje warto�ci tylko 0 lub 1" << endl;
		cout << "Ustawiam domy�lne ustawienie" << endl;
		styl_liczenia_wygranej = 1;
	}
	if (czas_przerwy_dzwi�ku < 0)
	{
		cout << "Czas przerwy d�wi�ku nie mo�e by� mniejszy od zera" << endl;
		cout << "Ustawiam domy�lne ustawienie" << endl;
		czas_przerwy_dzwi�ku = 500;
	}
	if (kwota_pocz�tkowa < 0)
	{
		cout << "Kwota pocz�tkowa nie mo�e by� mniejsza od zera" << endl;
		cout << "Ustawiam domy�lne ustawienie" << endl;
		kwota_pocz�tkowa = 1000;
	}
	if ((stan_d�wi�k�w > 1) || (stan_d�wi�k�w < 0))
	{
		cout << "Stan d�wi�k�w przyjmuje warto�ci tylko 0 lub 1" << endl;
		cout << "Ustawiam domy�lne ustawienie" << endl;
		stan_d�wi�k�w = 1;
	}
	if ((czy_kontynuowa�_gr� > 1) || (czy_kontynuowa�_gr� < 0))
	{
		cout << "Opcja kontynuowania gry przyjmuje warto�ci tylko 0 lub 1" << endl;
		cout << "Ustawiam domy�lne ustawienie" << endl;
		czy_kontynuowa�_gr� = 1;
	}
	if ((g�os_odczytu_numeru > 10) || (g�os_odczytu_numeru < 0))
	{
		cout << "Opcja g�os odczytu numeru przyjmuje warto�ci w przedziale [0;10]" << endl;
		cout << "Ustawiam domy�lne ustawienie" << endl;
		g�os_odczytu_numeru = 1;
	}
	if ((g�os_szybko��_odczytu_numeru > 5) || (g�os_szybko��_odczytu_numeru < 1))
	{
		cout << "Opcja szybko�� g�osu odczytu przyjmuje warto�ci w przedziale [1;5]" << endl;
		cout << "Ustawiam domy�lne ustawienie" << endl;
		g�os_szybko��_odczytu_numeru = 4;
	}
	if ((efekty_d�wi�kowe > 1) || (efekty_d�wi�kowe < 0))
	{
		cout << "Opcja efekty d�wi�kowe przyjmuje warto�ci 0 lub 1" << endl;
		cout << "Ustawiam domy�lne ustawienie" << endl;
		efekty_d�wi�kowe = 1;
	}
	if (efekty_d�wi�kowe == 1 && stan_d�wi�k�w == 0)
	{
		cout << "Nie mo�esz mie� wy��czonych d�wi�k�w i w��czonych efekt�w d�wi�kowych" << endl;
		cout << "Ustawiam domy�lne ustawienie" << endl;
		stan_d�wi�k�w = 1;
	}
	if (g�os_odczytu_numeru > 0 && stan_d�wi�k�w == 0)
	{
		cout << "Nie mo�esz mie� wy��czonych d�wi�k�w i w��czon� mow�" << endl;
		cout << "Ustawiam domy�lne ustawienie" << endl;
		stan_d�wi�k�w = 1;
	}
}

void Og�o�_wynik(const int & wygrana, const int & kwota_zak�adu, int & ilo��_pieni�dzy, ofstream & log_og�lny, fstream & log)
{
	if (wygrana >= kwota_zak�adu) //Je�eli wygrana jest wi�ksza lub r�wna kwocie zak�adu to znaczy, �e si� wygra�o zak�ad
	{
		ilo��_pieni�dzy += wygrana; //Dopisanie do salda kwoty wygranej z zak�adu
		if (styl_liczenia_wygranej) ilo��_pieni�dzy += kwota_zak�adu; //Dopisanie do salda kwoty zak�adu
		log << " Wygrywasz " << wygrana << "$"; //Zapisanie do bufora pliku logu aktualnego informacji o kwocie wygranej zak�adu
		log << " Posiadasz " << ilo��_pieni�dzy << "$" << endl; //Zapisanie do bufora pliku logu aktualnego informacji o saldzie konta u�ytkownika
		log_og�lny << " Wygrywasz " << wygrana << "$"; //Zapisanie do bufora pliku logu og�lnego informacji o kwocie wygranej zak�adu
		log_og�lny << " Posiadasz " << ilo��_pieni�dzy << "$" << endl; //Zapisanie do bufora pliku logu og�lnego informacji o saldzie konta u�ytkownika
		log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
		log_og�lny.flush(); //Zapisanie do pliku log_og�lny.txt danych wpisanych do bufora danych
		if (stan_d�wi�k�w)
		{
			if (G�osyKompletne)
			{
				PlaySound((G�os + "win.wav").c_str(), nullptr, SND_SYNC);
			}
			else
			{
				cout << "\a"; //Wywo�anie pikni�cia w g�o�niku
				Sleep(czas_przerwy_dzwi�ku); //Przerwa przed kolejnym pikni�ciem
				cout << "\a"; //Wywo�anie pikni�cia w g�o�niku
				Sleep(czas_przerwy_dzwi�ku); //Przerwa przed kolejnym pikni�ciem
				cout << "\a"; //Wywo�anie pikni�cia w g�o�niku
			}
		}
	}
	else if (wygrana == (kwota_zak�adu / 2)) //Je�eli wygrana jest r�wna po�owie kwocie zak�adu to znaczy, �e dostaje si� zwrot po�owy kwoty zak�adu
	{
		ilo��_pieni�dzy += wygrana; //Dopisanie do salda kwoty zwrotu z zak�adu
		log << " Dostajesz polowe zak�adu " << wygrana << "$"; //Zapisanie do bufora pliku logu aktualnego informacji o kwocie zwrotu zak�adu
		log << " Posiadasz " << ilo��_pieni�dzy << "$" << endl; //Zapisanie do bufora pliku logu aktualnego informacji o saldzie konta u�ytkownika
		log_og�lny << " Dostajesz polowe zak�adu " << wygrana << "$"; //Zapisanie do bufora pliku logu og�lnego informacji o kwocie zwrotu zak�adu
		log_og�lny << " Posiadasz " << ilo��_pieni�dzy << "$" << endl; //Zapisanie do bufora pliku logu og�lnego informacji o saldzie konta u�ytkownika
		log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
		log_og�lny.flush(); //Zapisanie do pliku log_og�lny.txt danych wpisanych do bufora danych
		if (!G�osyKompletne)
		{
			cout << "\a"; //Wywo�anie pikni�cia w g�o�niku
			Sleep(czas_przerwy_dzwi�ku); //Przerwa przed kolejnym pikni�ciem
			cout << "\a"; //Wywo�anie pikni�cia w g�o�niku
		}
	}
	else if (wygrana == 0) //Je�eli wygrana jest r�wna 0 to znaczy, �e si� zak�ad przegra�o
	{
		log << " Przegrales " << kwota_zak�adu << "$"; //Zapisanie do bufora pliku logu aktualnego informacji o przegranej kwocie
		log << " Posiadasz " << ilo��_pieni�dzy << "$" << endl; //Zapisanie do bufora pliku logu aktualnego informacji o saldzie konta u�ytkownika
		log_og�lny << " Przegrales " << kwota_zak�adu << "$"; //Zapisanie do bufora pliku logu og�lnego informacji o przegranej kwocie
		log_og�lny << " Posiadasz " << ilo��_pieni�dzy << "$" << endl; //Zapisanie do bufora pliku logu aktualnego informacji o saldzie konta u�ytkownika
		log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
		log_og�lny.flush(); //Zapisanie do pliku log_og�lny.txt danych wpisanych do bufora danych
		if (!G�osyKompletne) cout << "\a"; //Wywo�anie pikni�cia w g�o�niku
	}
}

void Koniec_gry(ofstream & log_og�lny, fstream & log, int & ilo��_pieni�dzy)
{
	cout << endl << "Ko�czysz gr� z wynikiem " << ilo��_pieni�dzy << "$" << endl; //Poinformowanie u�ytkownika o saldzie konta
	log << endl << "Ko�czysz gr� z wynikiem " << ilo��_pieni�dzy << "$" << endl; //Zapisanie do bufora pliku logu aktualnego informacji o saldzie konta u�ytkownika
	log_og�lny << "Ko�czysz gr� z wynikiem " << ilo��_pieni�dzy << "$" << endl; //Zapisanie do bufora pliku logu og�lnego informacji o saldzie konta u�ytkownika
	log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
	log_og�lny.flush(); //Zapisanie do pliku log_og�lny.txt danych wpisanych do bufora danych
	log.close();
	remove("log_aktualny.txt"); //Usuni�cie pliku log aktualny poniewa� sko�czy�o si� gr�

	if (stan_d�wi�k�w == 1) //Kompilacja je�eli stan_d�wi�k�w == 1
		if (ilo��_pieni�dzy == 0) //Je�eli bud�et jest r�wny 0 to
			if (EfektyKompletne) PlaySound("Efekty_d�wi�kowe/bankrut.wav", nullptr, SND_SYNC);
			else
				for (int i = 0; i < 5; ++i) //Rozpocz�cie p�tli kt�ra wykona 5 obrot�w
				{
					cout << "\a"; //Wywo�anie pikni�cia w g�o�niku
					Sleep(czas_przerwy_dzwi�ku); //Przerwa przed kolejnym pikni�ciem //Przerwa przed kolejnym pikni�ciem
				}

	if (ilo��_pieni�dzy > kwota_pocz�tkowa && ilo��_pieni�dzy < kwota_pocz�tkowa * 2)
	{
		cout << "Gratuluje zwi�kszy�e� sw�j zas�b finansowy" << endl; //Wy�wietlenie gratulacji z powodu zwi�kszenia bud�etu
		if (EfektyKompletne)
			if (rand() % 1) PlaySound("Efekty_d�wi�kowe/wygrana1.wav", nullptr, SND_SYNC);
			else PlaySound("Efekty_d�wi�kowe/wygrana2.wav", nullptr, SND_SYNC);
	}
	else if (ilo��_pieni�dzy >= kwota_pocz�tkowa * 2)
	{
		cout << "Gratuluje zwi�kszy�e� " << ilo��_pieni�dzy / kwota_pocz�tkowa << " krotnie sw�j zas�b finansowy" << endl; //Wy�wietlenie gratulacji z powodu zwielokrotnienia przynajmniej 2 razy bud�etu
		if (EfektyKompletne) PlaySound("Efekty_d�wi�kowe/zwielokrotnenie.wav", nullptr, SND_SYNC);
	}
}

void P�tla_g��wna(int & wygrana, int & kwota_zak�adu, int & ilo��_pieni�dzy, ofstream & log_og�lny, fstream & log, char & co_kontynuowa�, string & typ_zak�adu, int & wylosowana_liczba)
{
	if (co_kontynuowa� == 'n') Wczytaj_Kwot�_Zak�adu(kwota_zak�adu, ilo��_pieni�dzy); //Przypisanie do zmiennej pobranej od u�ytkownika kwoty zak�adu
	else cout << "Obstawiono za " << kwota_zak�adu << "$" << endl; //Wypisanie wczytanej kwoty zak�adu
	if (co_kontynuowa� == 'n') log << "Obstawiono za " << kwota_zak�adu << "$"; //Zapisanie do bufora pliku logu aktualnego informacji o kwocie obstawionego zak�adu
	if (co_kontynuowa� == 'n') log_og�lny << "Obstawiono za " << kwota_zak�adu << "$"; //Zapisanie do bufora pliku logu og�lnego informacji o kwocie obstawionego zak�adu
	log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
	log_og�lny.flush(); //Zapisanie do pliku log_og�lny.txt danych wpisanych do bufora danych
	if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k') typ_zak�adu = Obstaw(); //Przypisanie do zmiennej pobranej od u�ytkownika typu zak�adu
	else cout << "Obstawiono zak�ad " << typ_zak�adu << endl; //Wypisanie wczytanego typu zak�adu
	if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k') log << " Obstawiono zaklad " << typ_zak�adu; //Zapisanie do bufora pliku logu aktualnego informacji o typie obstawionego zak�adu
	if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k') log_og�lny << " Obstawiono zaklad " << typ_zak�adu; //Zapisanie do bufora pliku logu og�lnego informacji o typie obstawionego zak�adu
	log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
	log_og�lny.flush(); //Zapisanie do pliku log_og�lny.txt danych wpisanych do bufora danych
	if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k' || co_kontynuowa� == 't' || co_kontynuowa� == 'w') ilo��_pieni�dzy -= kwota_zak�adu; //Odj�cie od ilo�ci pieni�dzy kwoty zak�adu
	if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k' || co_kontynuowa� == 't') cout << "Kulka w grze, zaczekaj na wylosowanie numeru..." << endl; //Poinformowanie u�ytkownika o rozpocz�ciu losowania
	if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k' || co_kontynuowa� == 't') wylosowana_liczba = Zakr��_Ruletk�(); //Wylosowanie i przypisanie do zmiennej liczby b�d�cej na  wylosowanej pozycji na kole ruletki
	else {
		cout << "Wylosowano numer "; //Poinformowaniu o wylosowaniu liczby
		Change_Col(Ruletka_plansza_kolor_col[wylosowana_liczba]); //Zmiana koloru tekstu w konsoli zgodnie z kolorem numeru na ruletce
		cout << wylosowana_liczba; //Wypisanie wylosowanej liczby
		Change_Col(7); //Powr�t do standardowego koloru tekstu w konsoli
		cout << ". "; //Wypisanie kropki ko�cz�cej zdanie
	}
	if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k' || co_kontynuowa� == 't') log << " Wylosowano " << wylosowana_liczba; //Zapisanie do bufora pliku logu aktualnego informacji o wylosowanej liczbie
	if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k' || co_kontynuowa� == 't') log_og�lny << " Wylosowano " << wylosowana_liczba; //Zapisanie do bufora pliku logu og�lnego informacji o wylosowanej liczbie
	log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
	log_og�lny.flush(); //Zapisanie do pliku log_og�lny.txt danych wpisanych do bufora danych
	if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k' || co_kontynuowa� == 't') Odczytaj_liczb�(wylosowana_liczba, typ_zak�adu);
	if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k' || co_kontynuowa� == 't' || co_kontynuowa� == 'w') wygrana = Sprawd�_Zak�ad(kwota_zak�adu, typ_zak�adu, wylosowana_liczba);
	if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k' || co_kontynuowa� == 't' || co_kontynuowa� == 'w') Og�o�_wynik(wygrana, kwota_zak�adu, ilo��_pieni�dzy, log_og�lny, log);
}
void Ustaw_ustawienia(string & tekst)
{
	if (tekst.find("ilo��_minimalna_obrot�w_ruletki") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("ilo��_minimalna_obrot�w_ruletki")); //Usuni�cie s�owa z tekst aby zosta�a tylko liczba kt�ra jest warto�ci� ustawienia
		if (atoi(tekst.c_str())) ilo��_minimalna_obrot�w_ruletki = atoi(tekst.c_str()); //Sprawdzenie czy po usuni�ciu tekstu, to co pozosta�o jest warto�ci� r�n� od zera
		else
		{
			for (const char & i : tekst) //P�tla id�ca po ka�dym elemencie tablicy tekst i przypisuj�ca warto�� na tym polu do zmiennej i
				if (i != '0') return; //Je�eli zmienna i jest r�na od znaku 0 to wychodzi z funkcji
			g�os_szybko��_odczytu_numeru = 0; //Je�eli wszystkie pozycje wyrazu tekst s� zerami to zaczy, �e jego warto�� liczbowa to 0
		}
	}
	else if (tekst.find("ilo��_max_dodatkowych_obrot�w_ruletki") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("ilo��_max_dodatkowych_obrot�w_ruletki")); //Usuni�cie s�owa z tekst aby zosta�a tylko liczba kt�ra jest warto�ci� ustawienia
		if (atoi(tekst.c_str())) ilo��_max_dodatkowych_obrot�w_ruletki = atoi(tekst.c_str()); //Sprawdzenie czy po usuni�ciu tekstu, to co pozosta�o jest warto�ci� r�n� od zera
		else
		{
			for (const char & i : tekst) //P�tla id�ca po ka�dym elemencie tablicy tekst i przypisuj�ca warto�� na tym polu do zmiennej i
				if (i != '0') return; //Je�eli zmienna i jest r�na od znaku 0 to wychodzi z funkcji
			ilo��_max_dodatkowych_obrot�w_ruletki = 0; //Je�eli wszystkie pozycje wyrazu tekst s� zerami to zaczy, �e jego warto�� liczbowa to 0
		}
	}
	else if (tekst.find("czas_przeskoku_kulki_szybki") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("czas_przeskoku_kulki_szybki")); //Usuni�cie s�owa z tekst aby zosta�a tylko liczba kt�ra jest warto�ci� ustawienia
		if (atoi(tekst.c_str())) czas_przeskoku_kulki_szybki = atoi(tekst.c_str()); //Sprawdzenie czy po usuni�ciu tekstu, to co pozosta�o jest warto�ci� r�n� od zera
		else
		{
			for (const char & i : tekst) //P�tla id�ca po ka�dym elemencie tablicy tekst i przypisuj�ca warto�� na tym polu do zmiennej i
				if (i != '0') return; //Je�eli zmienna i jest r�na od znaku 0 to wychodzi z funkcji
			czas_przeskoku_kulki_szybki = 0; //Je�eli wszystkie pozycje wyrazu tekst s� zerami to zaczy, �e jego warto�� liczbowa to 0
		}
	}
	else if (tekst.find("czas_przeskoku_kulki_wolny") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("czas_przeskoku_kulki_wolny")); //Usuni�cie s�owa z tekst aby zosta�a tylko liczba kt�ra jest warto�ci� ustawienia
		if (atoi(tekst.c_str())) czas_przeskoku_kulki_wolny = atoi(tekst.c_str()); //Sprawdzenie czy po usuni�ciu tekstu, to co pozosta�o jest warto�ci� r�n� od zera
		else
		{
			for (const char & i : tekst) //P�tla id�ca po ka�dym elemencie tablicy tekst i przypisuj�ca warto�� na tym polu do zmiennej i
				if (i != '0') return; //Je�eli zmienna i jest r�na od znaku 0 to wychodzi z funkcji
			czas_przeskoku_kulki_wolny = 0; //Je�eli wszystkie pozycje wyrazu tekst s� zerami to zaczy, �e jego warto�� liczbowa to 0
		}
	}
	else if (tekst.find("styl_liczenia_wygranej") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("styl_liczenia_wygranej")); //Usuni�cie s�owa z tekst aby zosta�a tylko liczba kt�ra jest warto�ci� ustawienia
		if (atoi(tekst.c_str())) styl_liczenia_wygranej = atoi(tekst.c_str()); //Sprawdzenie czy po usuni�ciu tekstu, to co pozosta�o jest warto�ci� r�n� od zera
		else
		{
			for (const char & i : tekst) //P�tla id�ca po ka�dym elemencie tablicy tekst i przypisuj�ca warto�� na tym polu do zmiennej i
				if (i != '0') return; //Je�eli zmienna i jest r�na od znaku 0 to wychodzi z funkcji
			styl_liczenia_wygranej = 0; //Je�eli wszystkie pozycje wyrazu tekst s� zerami to zaczy, �e jego warto�� liczbowa to 0
		}
	}
	else if (tekst.find("kwota_pocz�tkowa") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("kwota_pocz�tkowa")); //Usuni�cie s�owa z tekst aby zosta�a tylko liczba kt�ra jest warto�ci� ustawienia
		if (atoi(tekst.c_str())) kwota_pocz�tkowa = atoi(tekst.c_str()); //Sprawdzenie czy po usuni�ciu tekstu, to co pozosta�o jest warto�ci� r�n� od zera
		else
		{
			for (const char & i : tekst) //P�tla id�ca po ka�dym elemencie tablicy tekst i przypisuj�ca warto�� na tym polu do zmiennej i
				if (i != '0') return; //Je�eli zmienna i jest r�na od znaku 0 to wychodzi z funkcji
			kwota_pocz�tkowa = 0; //Je�eli wszystkie pozycje wyrazu tekst s� zerami to zaczy, �e jego warto�� liczbowa to 0
		}
	}
	else if (tekst.find("stan_d�wi�k�w") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("stan_d�wi�k�w")); //Usuni�cie s�owa z tekst aby zosta�a tylko liczba kt�ra jest warto�ci� ustawienia
		if (atoi(tekst.c_str())) stan_d�wi�k�w = atoi(tekst.c_str()); //Sprawdzenie czy po usuni�ciu tekstu, to co pozosta�o jest warto�ci� r�n� od zera
		else
		{
			for (const char & i : tekst) //P�tla id�ca po ka�dym elemencie tablicy tekst i przypisuj�ca warto�� na tym polu do zmiennej i
				if (i != '0') return; //Je�eli zmienna i jest r�na od znaku 0 to wychodzi z funkcji
			stan_d�wi�k�w = 0; //Je�eli wszystkie pozycje wyrazu tekst s� zerami to zaczy, �e jego warto�� liczbowa to 0
		}
	}
	else if (tekst.find("czy_kontynuowa�_gr�") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("czy_kontynuowa�_gr�")); //Usuni�cie s�owa z tekst aby zosta�a tylko liczba kt�ra jest warto�ci� ustawienia
		if (atoi(tekst.c_str())) czy_kontynuowa�_gr� = atoi(tekst.c_str()); //Sprawdzenie czy po usuni�ciu tekstu, to co pozosta�o jest warto�ci� r�n� od zera
		else
		{
			for (const char & i : tekst) //P�tla id�ca po ka�dym elemencie tablicy tekst i przypisuj�ca warto�� na tym polu do zmiennej i
				if (i != '0') return; //Je�eli zmienna i jest r�na od znaku 0 to wychodzi z funkcji
			czy_kontynuowa�_gr� = 0; //Je�eli wszystkie pozycje wyrazu tekst s� zerami to zaczy, �e jego warto�� liczbowa to 0
		}
	}
	else if (tekst.find("g�os_odczytu_numeru") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("g�os_odczytu_numeru")); //Usuni�cie s�owa z tekst aby zosta�a tylko liczba kt�ra jest warto�ci� ustawienia
		if (atoi(tekst.c_str())) g�os_odczytu_numeru = atoi(tekst.c_str()); //Sprawdzenie czy po usuni�ciu tekstu, to co pozosta�o jest warto�ci� r�n� od zera
		else
		{
			for (const char & i : tekst) //P�tla id�ca po ka�dym elemencie tablicy tekst i przypisuj�ca warto�� na tym polu do zmiennej i
				if (i != '0') return; //Je�eli zmienna i jest r�na od znaku 0 to wychodzi z funkcji
			g�os_odczytu_numeru = 0; //Je�eli wszystkie pozycje wyrazu tekst s� zerami to zaczy, �e jego warto�� liczbowa to 0
		}
	}
	else if (tekst.find("g�os_szybko��_odczytu_numeru") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("g�os_szybko��_odczytu_numeru")); //Usuni�cie s�owa z tekst aby zosta�a tylko liczba kt�ra jest warto�ci� ustawienia
		if (atoi(tekst.c_str())) g�os_szybko��_odczytu_numeru = atoi(tekst.c_str()); //Sprawdzenie czy po usuni�ciu tekstu, to co pozosta�o jest warto�ci� r�n� od zera
		else
		{
			for (const char & i : tekst) //P�tla id�ca po ka�dym elemencie tablicy tekst i przypisuj�ca warto�� na tym polu do zmiennej i
				if (i != '0') return; //Je�eli zmienna i jest r�na od znaku 0 to wychodzi z funkcji //Je�eli zmienna i jest r�na od znaku 0 to wychodzi z funkcji
			g�os_szybko��_odczytu_numeru = 0; //Je�eli wszystkie pozycje wyrazu tekst s� zerami to zaczy, �e jego warto�� liczbowa to 0
		}
	}
	else if (tekst.find("efekty_d�wi�kowe") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("efekty_d�wi�kowe")); //Usuni�cie s�owa z tekst aby zosta�a tylko liczba kt�ra jest warto�ci� ustawienia
		if (atoi(tekst.c_str())) efekty_d�wi�kowe = atoi(tekst.c_str()); //Sprawdzenie czy po usuni�ciu tekstu, to co pozosta�o jest warto�ci� r�n� od zera
		else
		{
			for (const char & i : tekst) //P�tla id�ca po ka�dym elemencie tablicy tekst i przypisuj�ca warto�� na tym polu do zmiennej i
				if (i != '0') return; //Je�eli zmienna i jest r�na od znaku 0 to wychodzi z funkcji //Je�eli zmienna i jest r�na od znaku 0 to wychodzi z funkcji
			efekty_d�wi�kowe = 0; //Je�eli wszystkie pozycje wyrazu tekst s� zerami to zaczy, �e jego warto�� liczbowa to 0
		}
	}
}

/*
* Wykona� Krzysztof Truszkiewicz
Politechnika Pozna�ska
Wydzia� Elektryczny
studia niestacjonarne
Automatyka i Robotyka
Grupa 4
*/