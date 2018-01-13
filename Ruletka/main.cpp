//------------------ deklaracje bibiotek u�ywanych w programie -----------------------
#include <array> //Kontener tablica
#include <clocale> //setlocale(), polskie znaki w konsoli
#include <chrono> //Obs�uga zegara wysokiej precyzji
#include <ctime> //time(), akualny czas w sekundach liczony od 1 stycznia 1970, 00:00:00 UTC
#include <deque> //Kontener lista dwukierunkowa (deque)
#include <fstream> //Obs�uga plik�w
#include <io.h> //_access(), spawdzanie czy plik istnieje
#include <iostream> //Obs�uga strumenia cout,cin
#include <map> //Kontener drzewo binarne (map)
#include <random> //random_device,distribution(), generowanie liczb losowych i lepsze generowanie licz pseudolosowych
#include <sstream> //stringstream, zamiana liczby na string
#include <stack> //Kontener stos
#include <string> //Obs�uga string�w
#include <thread> //Obs�uga w�tk�w
#include <windows.h> //SYSTEMTIME,GetSystemTime(),Sleep(),GetStdHandle(),SetConsoleTextAttribute(),DeleteFile(),RemoveDirectory(), zmiana ustawie� konsoli, pobieranie aktualnego czasu
#include <mmsystem.h> //PlaySound() (Aby dzia�a�o trzeba doda� winmm.lib lub coredll.lib do linkera (konsolidatora)), Odtwarzanie muzyki
#pragma comment(lib, "winmm.lib") //Dodanie winmm.lib do linkera (konsolidatora)
#include <urlmon.h> //URLDownloadToFile(), pobiranie plik�w (Aby dzia�a�o trzeba doda� urlmon.lib do linkera (konsolidatora)), pobieranie plik�w z internetu
#pragma comment(lib, "urlmon.lib") //Dodanie urlmon.lib do linkera (konsolidatora)
#include <vector> //Kontener vector
#include "resource.h" //Plik z zasobanie (ikony i d�wi�ki)
//-------------------------------------------------------------------------------------

//----------------- deklaracja wyboru standardowej przestrzeni nazw std ---------------
using namespace std;
//-------------------------------------------------------------------------------------

//---------------------------------- deklaracje funkcji w�asnych ----------------------
string Obstaw(); //Funkcja wczytywania typu zak�ad, do string aby mie� tak�e zak�ady sk�adaj�ce si� z liter i cyfr
void Wczytaj_Kwot�_Zak�adu(int & kwota, const int & ilo��_pieni�dzy); //Funkcja wczytywania kwoty zak�adu aby uchroni� si� przed problemem wpisania znaku,litery zamiast liczby i osbstawienie za wi�ksz� kwot� ni� si� ma
int Zakr��_Ruletk�(); //Funkcja losuje liczb� z ko�a ruletki
int Sprawd�_Zak�ad(const int & kwota, const string & typ_zak�adu, const int & wylosowana_liczba); //Funcja sprawdza czy wygrali�my i podaje kwote wygranej/przegranej/odzysku cz�ci w�o�onych pieni�dzy
bool Czy_Kontynuowa�(const int & ilo��_pieni�dzy); //Funkcja sprawdzj�ca czy ma si� �rodki do gry, je�eli ma si� to pyta czy chce si� gra� dalej
int Wylosuj(const int & od_liczby, const int & do_liczby); //Funkcja kt�ra losuje liczby od liczby do liczby losowo lub psudolosowo metod� MT
void Odczytaj_Liczb�(const int & wylosowana_liczba, const string & typ_zak�adu); //Funkcja do odczytu wylosowanej liczby i jej po�o�enia
void Wczytaj_z_Pliku(ofstream & log_og�lny, fstream & log, char & co_kontynuowa�, int & ilo��_pieni�dzy, int & kwota_zak�adu, int & wylosowana_liczba, string & typ_zak�adu); //Funkcja wczytuj�ca z pliku ostatnie ruchy gracza
void Sprawd�_Pliki(const short & g�os_odczytu_numeru, const short & g�os_szybko��_odczytu_numeru); //Funkcja sprawdzaj�ca czy wszystkie pliki d�wi�kowe s� na miejscu
void Sprawd�_Ustawienia(); //sprawdzanie poprawno�ci deklaracji definicji preprocesora do zmian funcjonowania programu
void Og�o�_Wynik(const int & wygrana, const int & kwota_zak�adu, int & ilo��_pieni�dzy, ofstream & log_og�lny, fstream & log); //Funkcja informuj�ca gracza o wyniku zak�adu
void Koniec_Gry(ofstream & log_og�lny, fstream & log, const int & ilo��_pieni�dzy); //Funkcja informuj�ca o wynikach gracza jak sko�czy� gr�
void P�tla_G��wna(int & wygrana, int & kwota_zak�adu, int & ilo��_pieni�dzy, ofstream & log_og�lny, fstream & log, const char & co_kontynuowa�, string & typ_zak�adu, int & wylosowana_liczba); //Funkcja wywo�uj�ca funkcje obs�uguj�ce wszystkie elementy ruletki
void Ustaw_Ustawienia(string & tekst); //Funkcja zamieniaj�ca wczytan� linijk� z ustawieniami na zmian� ustawie� programu
void Inicjacje_Pocz�tkowe(); //Funkcja do zainicjowanie funkcji pocz�tkowych
bool Wyci�gnij_z_Programu(const string & �cie�ka, const unsigned short & numer_zasobu); //Funkcja kopiuj�ca do folderu z programem plik b�d�cy wewn�trz exe
void Wypakuj_Rar(const string & nazwa_folderu); //Funkcja wypakowywuj�ca pliki z archiwum rar
bool Przenie�_Plik(const string & z_pliku, const string & do_pliku); //Funkcja przenosz�ca plik z �cie�ki z_pliku do �cie�ki do_pliku
void Usu�_Folder_Wypakowany_i_Winrar(const string & G�os); //Funkcja usuwaj�ca wypakowany folder i program Winrar z folderu z programem
//-------------------------------------------------------------------------------------

//------------------------------- deklaracje funkcji obcych ---------------------------
void Change_Col(const int & num_of_col); //Funkcja zmieniaj�ca kolor tekstu 0 - czarny 1 - niebieski 2 - zielony 3 - b��kitny 4 - czerwony 5 - purpurowy 6 - ��ty 7 - bia�y 8 - szary 9 - jasnoniebieski 10 - jasnozielony 11 - jasnob��kitny 12 - jasnoczerwony 13 - jasnopurpurowy 14 - jasno��ty 15 - jaskrawobia�y
void Hide_Cursor(); //Funkcja w��cza pokazywanie kursora tekstowego
void Show_Cursor(); //Funkcja wy��cza pokazywanie kursora tekstowego
bool StringtoBool(const string & var); //Funkcja zamienia string na bool
short stos(const string& _Str, size_t *_Idx = 0, int _Base = 10); //Przerobiona wersja stoi na sto(short)
BOOL TerminateProcess(const DWORD & dwProcessId, const UINT & uExitCode); //Funkcja zamykaj�ca dany proces
//-------------------------------------------------------------------------------------

//----------------------------- deklaracje sta�ych tablic pomocniczych ------------------------
const unsigned short Ruletka_ko�o[] = { 0, 32, 15, 19, 4, 21, 2, 25, 17, 34, 6, 27, 13, 36, 11, 30, 8, 23, 10, 5, 24, 16, 33, 1, 20, 14, 31, 9, 22, 18, 29, 7, 28, 12, 35, 3, 26 }; // Kolejno�� liczb zgodna z ko�em ruletki
const array <char, 37 > Ruletka_plansza_kolor = { 'g','r','b','r','b','r','b','r','b','r','b','b','r','b','r','b','r','b','r','r','b','r','b','r','b','r','b','r','b','b','r','b','r','b','r','b','r' }; //Kolor dla ka�dej liczby na planszy
const deque <unsigned short> Ruletka_plansza_kolor_col = { 2,4,8,4,8,4,8,4,8,4,8,8,4,8,4,8,4,8,4,4,8,4,8,4,8,4,8,4,8,8,4,8,4,8,4,8,4 }; //Kod koloru do funkcji zmiany koloru tekstu dla ka�dej liczby na planszy
const map <string, unsigned short> Numer_zasobu_rar = { { "Agata_1",IDR_RCDATA1 },{ "Agata_2",IDR_RCDATA2 },{ "Agata_3",IDR_RCDATA3 },{ "Agata_4",IDR_RCDATA4 },{ "Agata_5",IDR_RCDATA5 },{ "Ewa_1",IDR_RCDATA6 },{ "Ewa_2",IDR_RCDATA7 },{ "Ewa_3",IDR_RCDATA8 },{ "Ewa_4",IDR_RCDATA9 },{ "Ewa_5",IDR_RCDATA10 },{ "Ewa2_1",IDR_RCDATA11 },{ "Ewa2_2",IDR_RCDATA12 },{ "Ewa2_3",IDR_RCDATA13 },{ "Ewa2_4",IDR_RCDATA14 },{ "Ewa2_5",IDR_RCDATA15 },{ "Jacek_1",IDR_RCDATA16 },{ "Jacek_2",IDR_RCDATA17 },{ "Jacek_3",IDR_RCDATA18 },{ "Jacek_4",IDR_RCDATA19 },{ "Jacek_5",IDR_RCDATA20 },{ "Jacek2_1",IDR_RCDATA21 },{ "Jacek2_2",IDR_RCDATA22 },{ "Jacek2_3",IDR_RCDATA23 },{ "Jacek2_4",IDR_RCDATA24 },{ "Jacek2_5",IDR_RCDATA25 },{ "Jan_1",IDR_RCDATA26 },{ "Jan_2",IDR_RCDATA27 },{ "Jan_3",IDR_RCDATA28 },{ "Jan_4",IDR_RCDATA29 },{ "Jan_5",IDR_RCDATA30 },{ "Jan2_1",IDR_RCDATA31 },{ "Jan2_2",IDR_RCDATA32 },{ "Jan2_3",IDR_RCDATA33 },{ "Jan2_4",IDR_RCDATA34 },{ "Jan2_5",IDR_RCDATA35 },{ "Maja_1",IDR_RCDATA36 },{ "Maja_2",IDR_RCDATA37 },{ "Maja_3",IDR_RCDATA38 },{ "Maja_4",IDR_RCDATA39 },{ "Maja_5",IDR_RCDATA40 },{ "Maja2_1",IDR_RCDATA41 },{ "Maja2_2",IDR_RCDATA42 },{ "Maja2_3",IDR_RCDATA43 },{ "Maja2_4",IDR_RCDATA44 },{ "Maja2_5",IDR_RCDATA45 } }; //Drzewo wi���ce Nazw� g�osu z szybko�ci� a numerem zasobu
const vector <string> Nazwa_g�osu = { "","Jacek","Ewa","Maja","Jan","Jacek2","Ewa2","Maja2","Jan2","Agata" }; //Vector string�w w celu przypisania numer g�osu <-> nazwa g�osu
//-------------------------------------------------------------------------------------

//---------- deklaracje typu strukturalnego do zmian ustawie� programu ----------------
struct S_Ustawienia //Struktura z wpisanymi domy�lnymi ustawieniami
{
	short ilo��_min_dodatkowych_obrot�w_ruletki = 2; // Minimalna ilo�� obrot�w ruletki przed podaniem warto�ci wylosowanej
	short ilo��_max_dodatkowych_obrot�w_ruletki = 3; // Maksymalna ilo�� dodatkowych obrot�w ruletki przed podaniem warto�ci wylosowanej
	short czas_przeskoku_kulki_szybki = 50; //Czas w ms przerwy pomi�dzy przeskokami na pocz�tek losowania na kolejn� liczb� na kole ruletki
	short czas_przeskoku_kulki_wolny = 75; //Czas w ms przerwy pomi�dzy przeskokami pod koniec losowania na kolejn� liczb� na kole ruletki
	short czas_przerwy_dzwi�ku = 500; //Czas w ms przerwy pomi�dzy pikni�ciami oznaczaj�cymi wynik zak�adu
	bool styl_liczenia_wygranej = true; //0 dla odejmowania w�o�onych w zak�ad pieni�dzy (przy tym zak�ady 1:1 nie zwi�kszaj� ilo��_pieni�dzy), 1 dla nie odejmowania (przy tym zak�ady 1:1 zwi�kszaj� ilo��_pieni�dzy)
	int kwota_pocz�tkowa = 1000; //Ilo�� $ z kt�rymi zaczyna si� gr�
	bool stan_d�wi�k�w = true; //Czy w��czone d�wi�ki 1 <-tak 0 <-nie
	bool czy_kontynuowa�_gr� = true; //Czy w��czone kontynuowanie gry od sko�czonej poprzednio pozycji 1 <-tak 0 <-nie
	short g�os_odczytu_numeru = 1; //Wyb�r g�osu kt�ry odczyta wylosowany numer 0 <- Brak 1 <- Jacek (Ivona) 2 <- Ewa (Ivona) 3 <- Maja (Ivona) 4 <- Jan (Ivona) 5 <- Jacek (Ivona 2) 6 <- Ewa (Ivona 2) 7 <- Maja (Ivona 2) 8 <- Jan (Ivona 2) 9 <- Agata (Scansoft)
	short g�os_szybko��_odczytu_numeru = (2 * 2); //Wyb�r szybko�ci mowy, skala od 1 do 5
	bool efekty_d�wi�kowe = true; //Czy w��czone efekty d�wi�kowe 1 <-tak 0 <-nie
	bool metoda_liczenia_wygranej_zerowej = true; //0 dla nie uzyskiwania zwrotu po�owy zak�adu przy obstawieniu szans prostych a wylosowaniu 0, 1 dla uzyskiwania zwrotu po�owy zak�adu przy obstawieniu szans prostych a wylosowaniu 0
};
//-------------------------------------------------------------------------------------

//------------------ deklaracje zmiennych/struktur globalnych -------------------------
SYSTEMTIME Czas; //Struktura do kt�rej zapisywana jest aktualna data i czas
bool G�osyKompletne = true;
bool EfektyKompletne = true;
string G�os;
S_Ustawienia Ustawienia;
//-------------------------------------------------------------------------------------

int main()
{
	//Inicjowanie zmiennych lokalnych
	ofstream log_og�lny; //Utworzenie typu do celu zapisu do pliku
	log_og�lny.open("log_og�lny.txt", ios::app); //Otworzenie pliku z ustawieniem kursora zapisu do pliku
	fstream log; //Utworzenie typu do celu zapisu i/lub odczytu do i/lub z pliku
	int ilo��_pieni�dzy = Ustawienia.kwota_pocz�tkowa, kwota_zak�adu, wylosowana_liczba, wygrana; //Zmienne do kt�rych wczytuje si� warto�ci liczbowe pobrane od u�ytkownika takie jak kwota zak�adu a przechowuje ilo�� posiadanych pieni�dzy a tak�e przechowuje wyniki funkcji losowania liczby z ruletki i kwote wygran� z zak�adu
	string typ_zak�adu; //Przechowuje typ zak�adu wprowadzony przez u�ytkownika
	char co_kontynuowa�; //Deklaracja znaku kt�ry przechowuje nazwany znakiem punkt od kt�rego kontynuowa� runde

	thread w�tek1(Inicjacje_Pocz�tkowe); //Utworzenie i uruchomienie w�tku do zainicjowania funkcji pocz�tkowych
	thread w�tek2(Wczytaj_z_Pliku, ref(log_og�lny), ref(log), ref(co_kontynuowa�), ref(ilo��_pieni�dzy), ref(kwota_zak�adu), ref(wylosowana_liczba), ref(typ_zak�adu)); //Utworzenie i uruchomienie w�tku do wczytania stanu gry z pliku
	w�tek1.join(); //Poczekanie na zako�czenie w�tku1
	thread w�tek3(Sprawd�_Ustawienia); //Utworzenie i uruchomienie w�tku do wczytania ustawie� z pliku
	w�tek3.join(); //Poczekanie na zako�czenie w�tku3
	thread w�tek4(Sprawd�_Pliki, ref(Ustawienia.g�os_odczytu_numeru), ref(Ustawienia.g�os_szybko��_odczytu_numeru)); //Utworzenie i uruchomienie w�tku do wczytania plik�w audio
	w�tek4.join(); //Poczekanie na zako�czenie w�tku4
	w�tek2.join(); //Poczekanie na zako�czenie w�tku2
	do
	{
		P�tla_G��wna(wygrana, kwota_zak�adu, ilo��_pieni�dzy, log_og�lny, log, co_kontynuowa�, typ_zak�adu, wylosowana_liczba); //Funkcja obs�uguj�ca wszystkie elementy gry
		co_kontynuowa� = 'n'; //Przypisanie znaku rozpocz�cia rundy od pocz�tku
	} while (Czy_Kontynuowa�(ilo��_pieni�dzy)); //P�tla dza�aj�ca do czasu warto�ci fa�sz zwr�conej przez funkcj� Czy_kontynuowa�

	Koniec_Gry(log_og�lny, log, ilo��_pieni�dzy); //Zako�czenie gry i wskazanie wyniku

	system("pause"); //Wywo�anie funkcji wymagaj�cej do zamkni�cia naci�ni�cie dowolnego klawisza

	return 0; //Zwr�cenie warto�� 0, czyli porogram zako�czy� si� bez b��du
}

string Obstaw()
{
	string zaklad_typ; //Deklaracja zmiennej typu string przechowywuj�cej typ zak�adu

	do { //P�tla do aby wykona�a si� conajmniej raz
		cout << "Jak� opcje chcesz obstawi�? (zgodnie z poni�szym opisem) :" << endl; //Zadanie pytania u�ytkownikowi
		cout << "p - parzyste" << endl; //Wskaza� mo�liw� odpowied�
		cout << "n - nieparzyste" << endl; //Wskaza� mo�liw� odpowied�
		cout << "r - czerwone (red)" << endl; //Wskaza� mo�liw� odpowied�
		cout << "b - czarne (black)" << endl; //Wskaza� mo�liw� odpowied�
		cout << "g - g�rna po�owa" << endl; //Wskaza� mo�liw� odpowied�
		cout << "d - dolna po�owa" << endl; //Wskaza� mo�liw� odpowied�
		cout << "k1, k2, k3 - kolumna 1, kolumna 2, kolumna 3" << endl; //Wskaza� mo�liw� odpowied�
		cout << "w1, w2, ... , w12 - wiersz trzech numer�w" << endl; //Wskaza� mo�liw� odpowied�
		cout << "0-36 - pojedy�cze pole o odpowiednim numerze" << endl; //Wskaza� mo�liw� odpowied�
		cin >> zaklad_typ; //Pobranie od u�ytkownika odpowiedzi na pytanie
	} while ( //U�ywam takiej sk�adni poniewa� je�li masz wyra�enie z logicznymi operatorami && lub ||, to w momencie gdy wynik wyra�enia ju� jest znany, to nie jest wyliczany dalej. (Poniewa� C++ jest "leniwe", co zarazem jest optymalne)
		(zaklad_typ.size() > 3) ||  //Sprawdzanie czy wprowadzono zak�ad jest d�u�szy ni� 3
		((zaklad_typ != "p" && //Sprawdzanie czy wprowadzono zak�ad na liczby parzyste
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
			zaklad_typ != "36")) //Sprawdzanie czy wprowadzono zak�ad na liczb� 36
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
		kwota_zak�adu = atoi(kwota_zak�adu_s.c_str()); //Zmiana stringa na inta i wpisanie do zmiennej kwota_zak�adu
		if ((kwota_zak�adu > 0) && (kwota_zak�adu <= ilo��_pieni�dzy)) break; //Sprawdzenie czy kwota zak�adu jest wi�ksza od zera i mniejsza lub r�wna dost�pnej got�wce, je�eli tak to zatrzymuje p�tle
		if (kwota_zak�adu == 0) //W przeciwym wypadku je�eli wynikiem zamiany na liczb� jest zero (wynikiem zamiany jest zero kiedy tekst to zero lub kiedy jest b��d zamiany) to
		{
			bool czy_zero = true; //Utworzenie zmiennej informuj�cej czy znaleziono zero w tek�cie i przypisanie jej warto�ci true
			for (size_t i = 0; i < kwota_zak�adu_s.size(); ++i) //Rozpocz�cie p�tli numerowanej przez zmienn� i przez wszystkie znaki wczytanego tekst
				if (kwota_zak�adu_s[i] != '0') //Je�eli znak na i-tej pozycji
				{
					cout << "Wprowadzi�e� nieprawid�ow� warto��" << endl; //Poinformowanie u�ytkownika, �e nie mo�e obstawi� tekstowego
					if (Ustawienia.stan_d�wi�k�w) cout << '\a'; //Je�eli stan_d�wi�k�w == 1 to wywo�anie pikni�cia w g�o�niku
					czy_zero = false; //Zmiana warto�ci zmiennej czy znaleziono zero w tek�cie na false
					break; //Zatrzymanie p�tli
				}
			if (czy_zero) //Sprawdzenie czy znaleziono same zera w tek�cie, je�eli tak to
			{
				cout << "Nie mo�esz obstawi� zerowego zak�adu" << endl; //Poinformowanie u�ytkownika, �e nie mo�e obstawi� zerowego zak�adu
				if (Ustawienia.stan_d�wi�k�w) cout << '\a'; //Je�eli stan_d�wi�k�w == 1 to wywo�anie pikni�cia w g�o�niku
			}
		}
		else if (kwota_zak�adu > ilo��_pieni�dzy) //Je�eli u�ytkownik chce obstawi� za wi�cej ni� ma, to
		{
			cout << "Nie masz tyle pieni�dzy" << endl; //Poinformowanie go o tym
			if (Ustawienia.stan_d�wi�k�w) cout << '\a'; //Je�eli stan_d�wi�k�w == 1 to wywo�anie pikni�cia w g�o�niku
		}
		else if (kwota_zak�adu < 0) //Je�eli u�ytkownik chce obstawi� za ujemn� kwot�, to
		{
			cout << "Nie mo�esz obstawi� ujemn� kwot� zak�adu" << endl; //Poinformowanie go o tym
			if (Ustawienia.stan_d�wi�k�w) cout << '\a'; //Je�eli stan_d�wi�k�w == 1 to wywo�anie pikni�cia w g�o�niku
		}
	}
}

int Zakr��_Ruletk�()
{
	const int ilo��_zakr�ce� = rand() % (Ustawienia.ilo��_max_dodatkowych_obrot�w_ruletki + 1) + Ustawienia.ilo��_min_dodatkowych_obrot�w_ruletki; //Deklarowanie i przpisanie zmiennej liczbowj zawieraj�c� pseudolosow� (o niskiej pseoudolosowo�ci) ilo�� obrot�w ruletk� ((od 0 do max dodatkowych obrot�w ruletki) + minimalna ilo�� obrot�w ruletki) zanim nast�pi finalny obr�t
	const double czas_przeskoku_kulki_szybki_op�nienie = Ustawienia.czas_przeskoku_kulki_szybki / (ilo��_zakr�ce� * 37.0); //Deklarowanie i przpisanie zmiennej zmiennoprzecinkowej zawieraj�c� czas o ile kolejna warto�� na kole ruletki powinna by� szybciej pokazana
	Hide_Cursor(); //Ukrycie kursora tekstowego w konsoli
	for (auto i = 0; i < ilo��_zakr�ce�; ++i) //Wykonanie ilo��_zakr�ce� obrot�w ruletk�
		for (size_t ii = 0; ii < 37; ++ii) //Przej�cie przez wszystkie pozycje ruletki
		{
			Change_Col(Ruletka_plansza_kolor_col[Ruletka_ko�o[ii]]); //Zmiana koloru tekstu w konsoli zgodnie z kolorem numeru na ruletce
			cout << Ruletka_ko�o[ii]; //Wypisanie numeru na kole ruletki na kt�rym znajduje si� p�tla
			Sleep((DWORD)(czas_przeskoku_kulki_szybki_op�nienie*((double)i*37.0 + (double)ii))); //Przest�j kt�ry zwi�ksza si� co zmian� pozycji p�tli
			Change_Col(7); //Powr�t do standardowego koloru tekstu w konsoli
			cout << "\b\b" << "  " << "\b\b"; //Cofni�cie kursora tekstowego do lewej strony konsoli aby zape�ni� potem spacjami czyli niewidocznym znakiem wiersza konsoli aby wida� przej�cie pomi�dzy liczbami na ruletce
		}
	const auto wylosowana_pozycja = Wylosuj(0, 36); //Deklarowanie i przpisanie zmiennej liczbowj zawieraj�c� losow� lub pseudolosow� liczb� (o wysokiej pseoudolosowo�ci) pozycj� na ruletce
	const double czas_przeskoku_kulki_wolny_przyspieszenie = (Ustawienia.czas_przeskoku_kulki_wolny - Ustawienia.czas_przeskoku_kulki_szybki) / (double)(wylosowana_pozycja); //Deklarowanie i przpisanie zmiennej zmiennoprzecinkowej zawieraj�c� czas o ile kolejna warto�� na kole ruletki powinna by� szybciej pokazana
	for (auto i = 0; i < wylosowana_pozycja; ++i) //Przej�cie przez pozycje do pozycji o 1 mniejszej od wylosowanej pozyji na ruletce
	{
		Change_Col(Ruletka_plansza_kolor_col[Ruletka_ko�o[i]]); //Zmiana koloru tekstu w konsoli zgodnie z kolorem numeru na ruletce
		cout << Ruletka_ko�o[i]; //Wypisanie numeru na kole ruletki na kt�rym znajduje si� p�tla
		Sleep((DWORD)(Ustawienia.czas_przeskoku_kulki_szybki + (czas_przeskoku_kulki_wolny_przyspieszenie*i))); //Przest�j kt�ry zwi�ksza si� co zmian� pozycji p�tli
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

int Sprawd�_Zak�ad(const int & kwota, const string & typ_zak�adu, const int & wylosowana_liczba)
{
	int wygrana = kwota; //Deklaracja zmiennej przechowywuj�ca kwot� wygran� lub zwr�con� przy wylosowaniu 0 i przypisu� jej warto�� kwota jakby wygrana by�a 1:1

	if (wylosowana_liczba == 0 && Ustawienia.metoda_liczenia_wygranej_zerowej) //Warunek sprawdzaj�cy czy wylosowano 0
		switch (typ_zak�adu[0]) //Je�eli tak to switch do obliczenia wygranej lub przegranej
		{
		case 'p':
		{
			wygrana >>= 1; //Je�eli typ zak�adu by� p to wygrana, a dok�adniej zwrot wynosi po�ow� zak�adu
			break; //Wyj�cie z switcha
		}
		case 'n':
		{
			wygrana >>= 1; //Je�eli typ zak�adu by� n to wygrana, a dok�adniej zwrot wynosi po�ow� zak�adu
			break; //Wyj�cie z switcha
		}
		case 'r':
		{
			wygrana >>= 1; //Je�eli typ zak�adu by� r to wygrana, a dok�adniej zwrot wynosi po�ow� zak�adu
			break; //Wyj�cie z switcha
		}
		case 'b':
		{
			wygrana >>= 1; //Je�eli typ zak�adu by� b to wygrana, a dok�adniej zwrot wynosi po�ow� zak�adu
			break; //Wyj�cie z switcha
		}
		case 'g':
		{
			wygrana >>= 1; //Je�eli typ zak�adu by� g to wygrana, a dok�adniej zwrot wynosi po�ow� zak�adu
			break; //Wyj�cie z switcha
		}
		case 'd':
		{
			wygrana >>= 1; //Je�eli typ zak�adu by� d to wygrana, a dok�adniej zwrot wynosi po�ow� zak�adu
			break; //Wyj�cie z switcha
		}
		case 'k':
		{
			wygrana = 0; //Je�eli typ zak�adu by� k to przegra�o si� zak�ad
			break; //Wyj�cie z switcha
		}
		case 'w':
		{
			wygrana = 0; //Je�eli typ zak�adu by� w to przegra�o si� zak�ad
			break; //Wyj�cie z switcha
		}
		case '0':
		{
			wygrana = (wygrana << 0) + (wygrana << 1) + (wygrana << 5); //Je�eli typ zak�adu by� 0 to wygra�o si� zak�ad, wygrana jest 35:1
			break; //Wyj�cie z switcha
		}
		default:
			; //W przeciwym wypadkunic nie r�b
		}
	else //Je�eli wylosowana liczba nie jest zerem to
	{
		if (typ_zak�adu == "p") //Je�eli typ zak�adu to p
			if (!(wylosowana_liczba & 1)) /*wygrana *= 1*/; //To sprawdzam czy wylosowana liczba jest parzysta, je�eli tak to wygrana jest 1:1
			else wygrana = 0; //Je�eli wylosowana liczba nie jest parzysta to przegra�o si� zak�ad
		else if (typ_zak�adu == "n") //Je�eli typ zak�adu to n
			if (wylosowana_liczba & 1) /*wygrana *= 1*/; //To sprawdzam czy wylosowana liczba jest nieparzysta, je�eli tak to wygrana jest 1:1
			else wygrana = 0; //Je�eli obstawiony numer nie jest nieparzysta to przegra�o si� zak�ad
		else if (typ_zak�adu == "r") //Je�eli typ zak�adu to n
			if (Ruletka_plansza_kolor[wylosowana_liczba] == 'r') /*wygrana *= 1*/; //To sprawdzam czy wylosowana liczba jest czerwona, je�eli tak to wygrana jest 1:1
			else wygrana = 0; //Je�eli wylosowana liczba nie jest czerwony to przegra�o si� zak�ad
		else if (typ_zak�adu == "b") //Je�eli typ zak�adu to n
			if (Ruletka_plansza_kolor[wylosowana_liczba] == 'b') /*wygrana *= 1*/; //To sprawdzam czy wylosowana liczba jest czarna, je�eli tak to wygrana jest 1:1
			else wygrana = 0; //Je�eli wylosowana liczba nie jest czarny to przegra�o si� zak�ad
		else if (typ_zak�adu == "g") //Je�eli typ zak�adu to g
			if (wylosowana_liczba < 19) /*wygrana *= 1*/; //To sprawdzam czy wylosowana liczba jest od 1 do 18, je�eli tak to wygrana jest 1:1
			else wygrana = 0; //Je�eli wylosowana liczba nie nale�y do przedzia�u [1,18] to przegra�o si� zak�ad
		else if (typ_zak�adu == "d") //Je�eli typ zak�adu to d
			if (wylosowana_liczba > 18) /*wygrana *= 1*/; //To sprawdzam czy wylosowana liczba jest od 19 do 36, je�eli tak to wygrana jest 1:1
			else wygrana = 0; //Je�eli wylosowana liczba nie nale�y do przedzia�u [19,36] to przegra�o si� zak�ad
		else if (typ_zak�adu[0] == 'k') //Je�eli typ zak�adu to k
			if ((wylosowana_liczba - 1) % 3 == (typ_zak�adu[1] - '1')) wygrana <<= 1; //To sprawdzam czy wylosowana liczba jest z obstawionej kolumny, je�eli tak to wygrana jest 2:1
			else wygrana = 0; //Je�eli wylosowana liczba nie jest z obstawionej kolumny to przegra�o si� zak�ad
		else if (typ_zak�adu[0] == 'w') //Je�eli typ zak�adu to w
			if (((wylosowana_liczba - 1) / 3 + 1) == (typ_zak�adu[1] - '0')) wygrana = (wygrana << 0) + (wygrana << 1) + (wygrana << 3); //To sprawdzam czy wylosowana liczba jest z obstawionego wiersza, je�eli tak to wygrana jest 11:1
			else wygrana = 0; //Je�eli wylosowana liczba nie jest z obstawionego wiersza to przegra�o si� zak�ad
		else if (wylosowana_liczba == strtol(typ_zak�adu.c_str(), nullptr, 10)) wygrana = (wygrana << 0) + (wygrana << 1) + (wygrana << 5); //Je�eli typ zak�adu to liczba, to sprawdzam czy wylosowana liczba jest r�wna obstawionej liczbie, je�eli tak to wygrana jest 35:1
		else wygrana = 0; //Je�eli wylosowana liczba nie jest r�wna obstawionej liczbie to przegra�o si� zak�ad
	}

	if (wygrana >= kwota) cout << "Obstawi�e� poprawnie, wygrywasz " << wygrana << "$." << endl; //Je�eli wygrana jest wi�ksza lub r�wna obstawionej kwocie to informuj� o tym, �e wygra�
	else if (wygrana == (kwota >> 1)) cout << "Obstawi�e� niepoprawnie lecz uda�o Ci si�, dostajesz po�ow� zak�adu " << wygrana << "$." << endl; //Je�eli wygrana jest r�wna po�owie obstawionej kwocie to informuj� o tym, �e przegra� po�owe stawki
	else cout << "Obstawi�e� niepoprawnie, przegra�e� " << kwota << "$." << endl; //Je�eli wygrana jest r�wna zero to informuj� o tym, �e przegra�

	return wygrana; //Zwracam warto� wygranej lub zwrotu
}

bool Czy_Kontynuowa�(const int & ilo��_pieni�dzy)
{
	string tak_nie; //Zadeklarowanie zmiennej typu string

	if (ilo��_pieni�dzy == 0) //Je�eli posiadana ilo�� got�wki jest r�wna 0
	{
		cout << "Nie mo�esz kontynuowa�, przegra�e� wszystko" << endl; //Poinformowanie u�ytkownika, �e jest bankrutem
		return false; //Zwrot warto�ci false, co oznacza, �e kolejna runda si� nie odb�dzie
	}

	while (true) //Rozpocz�cie p�tli niesko�czonej
	{
		cout << "Na koncie masz " << ilo��_pieni�dzy << "$, czy chcesz grac dalej ('t'-tak, 'n'-nie) ?" << endl; //Pointormowanie o stanie konta i zapytanie o to czy gra dalej
		cin >> tak_nie; //Pobranie od u�ytkownika odpowiedzi na powy�sze pytanie
		if (tak_nie == "t" || tak_nie == "tak" || tak_nie == "Tak" || tak_nie == "TAK" || tak_nie == "n" || tak_nie == "nie" || tak_nie == "Nie" || tak_nie == "NIE") //Sprawdzenie czy odpowied� pasuje do mo�liwo�ci
			if (tak_nie[0] == 't' || tak_nie[0] == 'T') return true; //Je�eli pasuje to sprawdzam czy pierwsza litera to t i zwracam warto�� true
		return false; //W przeciwym wypadku zwracam warto�� false
	}
}

void Change_Col(const int & num_of_col)
{
	const HANDLE h_wyj = GetStdHandle(STD_OUTPUT_HANDLE); //Stworzenie zmiennej typu uchwyt i przypisanie do standardowego wyj�cia
	SetConsoleTextAttribute(h_wyj, num_of_col); //Zmienia atrybut koloru tekstu w konsoli
}

void Hide_Cursor()
{
	const HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE); //Stworzenie zmiennej typu uchwyt i przypisanie do standardowego wyj�cia
	CONSOLE_CURSOR_INFO hCCI; //Stworzenie zmiennej typu informacji o kursorze tekstowym w konsoli
	GetConsoleCursorInfo(hConsoleOut, &hCCI); //Przypisanie do zmiennej informacji o kursorze tekstowym w konsoli
	hCCI.bVisible = FALSE; //Zmiena widoczno�ci kursora na niewidoczny
	SetConsoleCursorInfo(hConsoleOut, &hCCI); //Ustawienie widoczno�ci kursora zgodnie z poprzedni� zmienn�
}

void Show_Cursor()
{
	const HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE); //Stworzenie zmiennej typu uchwyt i przypisanie do standardowego wyj�cia
	CONSOLE_CURSOR_INFO hCCI; //Stworzenie zmiennej typu informacji o kursorze tekstowym w konsoli
	GetConsoleCursorInfo(hConsoleOut, &hCCI); //Przypisanie do zmiennej informacji o kursorze tekstowym w konsoli
	if (!hCCI.bVisible) //Sprawdzenie czy warto�� widoczno�ci kursorsora tekstego w konsoli jest r�na od prawdy
	{
		hCCI.bVisible = TRUE;//Je�eli tak, to zmiena widoczno�ci kursora na widoczny
		SetConsoleCursorInfo(hConsoleOut, &hCCI); //I ustawienie widoczno�ci kursora zgodnie z poprzedni� zmienn�
	}
}

int Wylosuj(const int & od_liczby, const int & do_liczby)
{
	if (od_liczby > do_liczby) //Je�eli od jest wi�ksze ni� do to
		return Wylosuj(do_liczby, od_liczby); //Wywo�ujemy funkcje z przeciwn� kolejno�ci� argument�w

	random_device generator; //Generator liczb losowych, kt�ry generuje niedeterministyczne liczby losowe, je�li s� obs�ugiwane.
	if (fabs(generator.entropy() - 32.0) > DBL_EPSILON) //Je�eli entropia jest mniejsza od 32 oznacza, �e komputer nie dysponuje mo�liwo�ci� u�ycia tego generatora liczb losowy
	{
#if defined (__x86_64__) || defined(_M_X64) || defined(__x86_64) || defined(__amd64) || defined(__amd64__) || defined(_M_AMD64) //Sprawdzenie czy sytem operacyjny jest 64-bitowy
		mt19937_64 mgenerator((unsigned int)chrono::high_resolution_clock::now().time_since_epoch().count()); //Dla 64 bitowego systemu zamiast powy�szego generatora u�ywa generator liczb pseudolosowych Mersenne Twister 19937 w wersji 64 bitowej i wczytuje ziarno z precyzyjnego nanosekundowego zegara
		return ((mgenerator() % (do_liczby - od_liczby + 1)) + od_liczby); //Zwraca wygenerowan� liczb� z przedzia�u [od_liczby,do_liczby]
#else
		mt19937 mgenerator((unsigned int)chrono::high_resolution_clock::now().time_since_epoch().count()); //Dla 32 bitowego systemu zamiast powy�szego generatora u�ywa generator liczb pseudolosowych Mersenne Twister 19937 w wersji 32 bitowej i wczytuje ziarno z precyzyjnego nanosekundowego zegara
		return ((mgenerator() % (do_liczby - od_liczby + 1)) + od_liczby); //Zwraca wygenerowan� liczb� z przedzia�u [od_liczby,do_liczby]
#endif
	}
	uniform_int_distribution<int> distribution(od_liczby, do_liczby); //Wskazuje przedzia� generowanych liczb
	return distribution(generator); //Zwraca wygenerowan� liczb� z przedzia�u
}

void Odczytaj_Liczb�(const int & wylosowana_liczba, const string & typ_zak�adu) {
	if ((Ustawienia.g�os_odczytu_numeru == 0) || (!G�osyKompletne)) return; //Je�eli ustawienia wy��czaj� g�os lub brak plik�w g�osu to wyjd� z funkcji

	stringstream numers; //Utworzenie typu do zamiany liczby na tekst
	numers << wylosowana_liczba; //Wpisanie to typu wylosowanej liczby
	PlaySound((G�os + numers.str() + ".wav").c_str(), nullptr, SND_SYNC); //Odczytanie wylosowanego numeru
	if (wylosowana_liczba | 0) //Je�eli nie jest to 0
		if (typ_zak�adu == "p" || typ_zak�adu == "n") //Je�eli typ zak�adu to p lub n
			if (wylosowana_liczba & 1) //Je�eli wylosowana liczba modulo 2 jest 0 to
				PlaySound((G�os + "n.wav").c_str(), nullptr, SND_SYNC); //Powiedz, �e wylosowana licza jest nieparzysta
			else
				PlaySound((G�os + "p.wav").c_str(), nullptr, SND_SYNC); //W przeciwym wypadku powiedz, �e wylosowana licza jest parzysta
		else if (typ_zak�adu == "r" || typ_zak�adu == "b") //Je�eli typ zak�adu to r lub b
			if (Ruletka_plansza_kolor[wylosowana_liczba] == 'r') //Je�eli kolor wylosowanej liczby to czerwony
				PlaySound((G�os + "r.wav").c_str(), nullptr, SND_SYNC); //Powiedz, �e wylosowana liczba jest koloru czerwonego
			else
				PlaySound((G�os + "b.wav").c_str(), nullptr, SND_SYNC); //W przeciwym wypadku powiedz, �e liczba jest koloru czarnego
		else if (typ_zak�adu == "g" || typ_zak�adu == "d") //Je�eli typ zak�adu to g lub d
			if (wylosowana_liczba < 19) //Je�eli wylosowa liczba jest mniejsza ni� 19
				PlaySound((G�os + "g.wav").c_str(), nullptr, SND_SYNC); //Powiedz, �e wylosowana liczba jest z g�rnej po��wki
			else
				PlaySound((G�os + "d.wav").c_str(), nullptr, SND_SYNC); //W przeciwym wypadku powiedz, �e wylosowana liczba jest z dolnej po��wki
		else if (typ_zak�adu[0] == 'k') //Je�eli typ zak�adu to k
			PlaySound((G�os + 'k' + (char)(((wylosowana_liczba - 1) % 3) + '1') + ".wav").c_str(), nullptr, SND_SYNC); //Powiedz z jakiej kolumny jest wylosowana liczba
		else if (typ_zak�adu[0] == 'w') //Je�eli typ zak�adu to w
		{
			stringstream numers; //Utworzenie typu do zamiany liczby na tekst
			numers << ((wylosowana_liczba - 1) / 3 + 1); //Wpisanie do typu obliczonego wiersza wylosowanej liczby
			PlaySound((G�os + 'w' + numers.str() + ".wav").c_str(), nullptr, SND_SYNC); //Powiedz z jakiego wiersza jest wylosowana liczba
		}
}

void Wczytaj_z_Pliku(ofstream & log_og�lny, fstream & log, char & co_kontynuowa�, int & ilo��_pieni�dzy, int & kwota_zak�adu, int & wylosowana_liczba, string & typ_zak�adu)
{
	if (!Ustawienia.czy_kontynuowa�_gr�) //Je�eli czy_kontynuowa�_gr� == 0
		if (!_access("log_aktualny.txt", NULL)) // Sprawdzenie dost�pu do pliku (je�eli takowy istnieje, musi istnie� plik)
		{
			co_kontynuowa� = 'n'; //Przypisanie znaku rozpocz�cia rundy od pocz�tku
			remove("log_aktualny.txt"); //Usuni�cie pliku log aktualny poniewa� rozpoczyna si� now� gr�
			log_og�lny << '\n' << "Uruchomiono ponownie gr� z wy��czon� opcj� kontynuowania" << '\n'; //Wpisanie do buforu logu og�lnego informacje o rozpocz�ciu nowej gry spowodowane ustawieniem gry
			log_og�lny.flush(); //Zapisanie do pliku log_og�lny.txt danych wpisanych do bufora danych
		}

	if (!_access("log_aktualny.txt", NULL)) // Sprawdzenie dost�pu do pliku (je�eli takowy istnieje, musi istnie� plik)
	{
		log.open("log_aktualny.txt", ios::in); //Otworzenie pliku w trybie odczytu z pliku
		string buf, bufor2; //Uworzenie 2 bufor�w na tekst, pierwszy na ostatni� linie tekst, drugi na przedostani� nie pust� linie tekstu lub ostani� w przypadku gdy ostania jest pusta
		getline(log, buf); //Odczyt ca�ej lini z pliku
		while (!log.eof()) //P�tla dzia�j�ca do czasu kiedy kursor odczytu z pliku nie b�dzie na ko�cu pliku
		{
			if (!(buf.empty()) && ((buf.find("Posiadasz") != string::npos) || (buf.find("Wylosowano") != string::npos) || (buf.find("Obstawiono zaklad") != string::npos) || (buf.find("Gra rozpoczeta dnia") != string::npos))) //Sprawdzenie czy odczytana linia zawiera interesuj�ce s�owa kluczowe
				bufor2 = buf; //Je�eli nie jest pusta to skopiowanie do drugiego bufora celem posiadania dw�ch ostatnich linijek tekstu b�d�cego w pliku
			getline(log, buf); //Odczyt ca�ej lini z pliku
		}
		if ((buf.empty()) || (!((buf.find("Posiadasz") != string::npos) || (buf.find("Wylosowano") != string::npos) || (buf.find("Obstawiono za") != string::npos) || (buf.find("Gra rozpoczeta dnia") != string::npos)))) //Sprawdzenie czy linia w buforze jest pusta lub czy nieznaleziono interesuj�cego s�owa kluczowego
			buf = bufor2; //je�eli jest pusta to zast�pienie jej poprzedni� lini� tekstu z pliku
		if (buf.find("Posiadasz") != string::npos) //Sprawdzenie czy w ostatniej niepustej lini znajduj� si� s�owa �wiadcz�ce o sko�czeniu rundy
		{
			co_kontynuowa� = 'n'; //Je�eli si� znajduj� to przypisanie znaku rozpocz�cia rundy od pocz�tku
			auto pocz�tek = buf.size(); //Utworzenie i przypisanie do zmiennej wskazuj�cej pocz�tek tekst pozycji ostatniego znaku tekstu o kwocie pieni�dzy kt�r� posiada jeszcze gracz, typ zmiennej auto wsazuje, �e kompilator sam wybierze typ zmiennej
			while (buf[pocz�tek] != ' ' && pocz�tek > 0) --pocz�tek; //Poszukiwanie od ko�ca spacji po kt�rej jest kwota pieni�dzy kt�r� posiada jeszcze gracz
			++pocz�tek; //Kwota jest na nast�pnym znaku wi�c przesuni�cie o jeden znak do przodu
			string buf2 = buf; //Utworzenie bufora pomocniczego do ci�cia tekstu i w�o�enie do niego wcze�niej odczytanego tekstu
			buf2.erase(0, pocz�tek); //Usuni�cie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna� si� liczb�
			buf2.erase(buf2.size() - 1, 1); //Usuni�cie z bufora pomocniczego znaku dolara z prawej strony
			istringstream numers(buf2); //Utorzenie typu do zamiany tekstu na liczb�
			numers >> ilo��_pieni�dzy; //Zamiana liczby w tek�cie na warto�� w zmiennnej liczbowej
		}
		else if (buf.find("Wylosowano") != string::npos) //Sprawdzenie czy w ostatniej niepustej lini znajduj� si� s�owa �wiadcz�ce o wylosowaniu liczby
		{
			co_kontynuowa� = 'w'; //Je�eli si� znajduj� to przypisanie znaku rozpocz�cia rundy od sprawdzenia wygranej
			size_t pocz�tek = 0; //Utworzenie i przypisanie zera do zmiennej wskazuj�cej pocz�tek tekst o wylosowanej liczbie
			while (buf[pocz�tek] != 'y' && pocz�tek < buf.size()) ++pocz�tek; //Poszukiwanie od pocz�tku litery y kt�ra wyst�puje w wyrazie po kt�rym jest wylosowana liczba
			pocz�tek += 10; //Przesuni�cie o +10 pozycji pocz�tku tekstu o po kt�rej jest wylosowana liczba
			string buf2 = buf; //Utworzenie bufora pomocniczego do ci�cia tekstu i w�o�enie do niego wcze�niej odczytanego tekstu
			buf2.erase(0, pocz�tek); //Usuni�cie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna� si� liczb�
			wylosowana_liczba = atoi(buf2.c_str()); //Zamiana liczby w tek�cie na warto�� w zmiennnej liczbowej
			pocz�tek = 0; //Przypisanie zera do zmiennej wskazuj�cej pocz�tek tekst o typie zak�adu
			while (buf[pocz�tek] != 'd' && pocz�tek < buf.size()) ++pocz�tek;
			pocz�tek += 2;  //Przesuni�cie o +2 pozycji pocz�tku tekstu o po kt�rej jest typ zak�adu
			buf2 = buf; //Utworzenie bufora pomocniczego do ci�cia tekstu i w�o�enie do niego wcze�niej odczytanego tekstu
			buf2.erase(0, pocz�tek); //Usuni�cie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna� si� liczb�
			buf2.erase(buf2.find(" Wylosowano"), string::npos); //Usuni�cie z bufora pomocniczego tekstu z prawej strony, aby tekst ko�czy� si� nazw� typu zak�adu
			typ_zak�adu = buf2; //Przypisanie do zmiennej przechowywuj�cej typ zak�adu wczytanego typu zak�adu
			buf.erase(buf.find("Obstawiono zaklad"), string::npos); //Usuni�cie wszystkiego w prawo razem z wyszukanym tekstem
			pocz�tek = 0; //Przypisanie zera do zmiennej wskazuj�cej pocz�tek tekst o kwocie zak�adu
			if (buf[12] == 'a') { pocz�tek = 14; } //Sprawdzenie czy na pozycji 12 teksty znajduje si� litera a �wiadcz�ca o wyrazie po kt�rym jest kwota zak�adu, je�eli tak to pozycja pocz�tkowa tekstu wynosi 14
			else //Je�eli nie to
			{
				while (buf[pocz�tek] != 'z' && pocz�tek < buf.size()) ++pocz�tek; //Poszukanie litery z �wiadcz�cej o wyrazie po kt�rym jest kwota zak�adu
				pocz�tek += 3; //Po znalezienu z przesuwamy pozycje +3
			}
			size_t koniec = pocz�tek + 1; //Przypisanie do zmiennej pozycji pocz�tku +1 wskazuj�cej koniec tekst o kwocie zak�adu
			while (buf[koniec] != '$' && koniec < buf.size()) ++koniec; //Poszukujemy znaku dolara przed kt�rym jest kwota zak�adu
			buf2 = buf; //Utworzenie bufora pomocniczego do ci�cia tekstu i w�o�enie do niego wcze�niej odczytanego tekstu
			buf2.erase(koniec, string::npos); //Usuni�cie z bufora pomocniczego tekstu z prawej strony, aby tekst ko�czy� si� liczb�
			buf2.erase(0, pocz�tek); //Usuni�cie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna� si� liczb�
			kwota_zak�adu = atoi(buf2.c_str()); //Zamiana liczby w tek�cie na warto�� w zmiennnej liczbowej
			pocz�tek = bufor2.size(); //Utworzenie i przypisanie do zmiennej wskazuj�cej pocz�tek tekst o kwocie pieni�dzy kt�r� posiada jeszcze gracz
			while (bufor2[pocz�tek] != ' ' && pocz�tek > 0) --pocz�tek; //Poszukiwanie od ko�ca spacji po kt�rej jest kwota pieni�dzy kt�r� posiada jeszcze gracz
			++pocz�tek; //Kwota jest na nast�pnym znaku wi�c przesuni�cie o jeden znak do przodu
			if (bufor2.find("Gra rozpoczeta") == string::npos) //Zabezpieczenie przed wczytymaniem ilo�ci pozosta�ych pieni�dzy jak si� nie rozegra�o pe�nej rundy
			{
				buf2 = move(bufor2); //Przeniesienie do bufora pomocniczego do ci�cia tekstu i w�o�enie do niego linie o jedn� wcze�niej wcze�niej odczytanego tekstu
				buf2.erase(0, pocz�tek); //Usuni�cie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna� si� liczb�
				buf2.erase(buf2.size() - 1, 1); //Usuni�cie z bufora pomocniczego znaku dolara z prawej strony
				sscanf_s(buf2.c_str(), "%d", &ilo��_pieni�dzy); //Zamiana liczby w tek�cie na warto�� w zmiennnej liczbowej
			}
		}
		else if (buf.find("Obstawiono zaklad") != string::npos) //Sprawdzenie czy w ostatniej niepustej lini znajduj� si� s�owa �wiadcz�ce o typie obstawionego zak�adu
		{
			co_kontynuowa� = 't'; //Je�eli si� znajduj� to przypisanie znaku rozpocz�cia rundy od wylosowania liczby
			size_t pocz�tek = 0; //Utworzenie i przypisanie zera do zmiennej wskazuj�cej pocz�tek tekst o typie zak�adu
			while (buf[pocz�tek] != 'd' && pocz�tek < buf.size()) ++pocz�tek;
			pocz�tek += 2; //Przesuni�cie pozycji pocz�tku tekstu o 2 po kt�rej jest typ zak�adu
			string buf2 = buf; //Utworzenie bufora pomocniczego do ci�cia tekstu i w�o�enie do niego wcze�niej odczytanego tekstu
			buf2.erase(0, pocz�tek); //Usuni�cie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna� si� liczb�
			typ_zak�adu = buf2; //Przypisanie do zmiennej przechowywuj�cej typ zak�adu wczytanego typu zak�adu
			buf.erase(buf.find("Obstawiono zaklad"), string::npos); //Usuni�cie wszystkiego w prawo razem z wyszukanym tekstem
			pocz�tek = 0; //Przypisanie zera do zmiennej wskazuj�cej pocz�tek tekst o kwocie zak�adu
			if (buf[12] == 'a') pocz�tek = 14; //Sprawdzenie czy na pozycji 12 teksty znajduje si� litera a �wiadcz�ca o wyrazie po kt�rym jest kwota zak�adu, je�eli tak to pozycja pocz�tkowa tekstu wynosi 14
			else //Je�eli nie to
			{
				while (buf[pocz�tek] != 'z' && pocz�tek < buf.size()) ++pocz�tek; //Poszukanie litery z �wiadcz�cej o wyrazie po kt�rym jest kwota zak�adu
				pocz�tek += 3; //Po znalezienu z przesuwamy pozycje +3
			}
			size_t koniec = pocz�tek + 1; //Przypisanie do zmiennej pozycji pocz�tku +1 wskazuj�cej koniec tekst o kwocie zak�adu
			while (buf[koniec] != '$' && koniec < buf.size()) ++koniec; //P�tla poszukuj�ca znaku dolara, p�tla ko�czy si� znalezieniem znaku dolara
			buf2 = buf; //W�o�enie do bufora pomocniczego do ci�cia tekstu wcze�niej odczytanego tekstu
			buf2.erase(koniec, string::npos); //Usuni�cie z bufora pomocniczego tekstu z prawej strony, aby tekst ko�czy� si� liczb�
			buf2.erase(0, pocz�tek); //Usuni�cie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna� si� liczb�
			kwota_zak�adu = atoi(buf2.c_str()); //Zamiana liczby w tek�cie na warto�� w zmiennnej liczbowej
			pocz�tek = bufor2.size(); //Utworzenie i przypisanie do zmiennej wskazuj�cej pocz�tek tekst o kwocie pieni�dzy kt�r� posiada jeszcze gracz
			while (bufor2[pocz�tek] != ' ' && pocz�tek > 0) --pocz�tek; //Poszukiwanie od ko�ca spacji po kt�rej jest kwota pieni�dzy kt�r� posiada jeszcze gracz
			++pocz�tek; //Kwota jest na nast�pnym znaku wi�c przesuni�cie o jeden znak do przodu
			if (bufor2.find("Gra rozpoczeta") == string::npos) //Zabezpieczenie przed wczytymaniem ilo�ci pozosta�ych pieni�dzy jak si� nie rozegra�o pe�nej rundy
			{
				buf2 = move(bufor2); //Przeniesienie do bufora pomocniczego do ci�cia tekstu i w�o�enie do niego linie o jedn� wcze�niej wcze�niej odczytanego tekstu
				buf2.erase(0, pocz�tek); //Usuni�cie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna� si� liczb�
				buf2.erase(buf2.size() - 1, 1); //Usuni�cie z bufora pomocniczego znaku dolara z prawej strony
				sscanf_s(buf2.c_str(), "%d", &ilo��_pieni�dzy); //Zamiana liczby w tek�cie na warto�� w zmiennnej liczbowej
			}
		}
		else if (buf.find("Obstawiono za") != string::npos) //Sprawdzenie czy w ostatniej niepustej lini znajduj� si� s�owa �wiadcz�ce o kwocie obstawionego zak�adu
		{
			co_kontynuowa� = 'k';  //Je�eli si� znajduj� to przypisanie znaku rozpocz�cia rundy od zapytania o typ zak�adu
			size_t pocz�tek = 0; //Utworzenie i przypisanie do zmiennej wskazuj�cej pocz�tek tekst o kwocie pieni�dzy kt�r� posiada jeszcze gracz
			if (buf[12] == 'a') { pocz�tek = 14; } //Sprawdzenie czy na pozycji 12 teksty znajduje si� litera a �wiadcz�ca o wyrazie po kt�rym jest kwota zak�adu, je�eli tak to pozycja pocz�tkowa tekstu wynosi 14
			else //Je�eli nie to
			{
				while (buf[pocz�tek] != 'z' && pocz�tek < buf.size()) ++pocz�tek; //Poszukanie litery z �wiadcz�cej o wyrazie po kt�rym jest kwota zak�adu
				pocz�tek += 3; //Po znalezienu z przesuwamy pozycje +3
			}
			size_t koniec = pocz�tek + 1; //Utworzenie i przypisanie do zmiennej pozycji pocz�tku +1 wskazuj�cej koniec tekst o kwocie zak�adu
			while (buf[koniec] != '$' && koniec < buf.size()) ++koniec; //P�tla szukaj�ca znaku dolara
			string buf2 = buf; //Utworzenie bufora pomocniczego do ci�cia tekstu i w�o�enie do niego wcze�niej odczytanego tekstu
			buf2.erase(koniec, string::npos); //Usuni�cie z bufora pomocniczego tekstu z prawej strony, aby tekst ko�czy� si� liczb�
			buf2.erase(0, pocz�tek); //Usuni�cie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna� si� liczb�
			kwota_zak�adu = atoi(buf2.c_str()); //Zamiana liczby w tek�cie na warto�� w zmiennnej liczbowej
			pocz�tek = bufor2.size(); //Utworzenie i przypisanie do zmiennej wskazuj�cej pocz�tek tekst o kwocie pieni�dzy kt�r� posiada jeszcze gracz
			while (bufor2[pocz�tek] != ' ' && pocz�tek > 0) --pocz�tek; //Poszukiwanie od ko�ca spacji po kt�rej jest kwota pieni�dzy kt�r� posiada jeszcze gracz
			++pocz�tek; //Kwota jest na nast�pnym znaku wi�c przesuni�cie o jeden znak do przodu
			if (bufor2.find("Gra rozpoczeta") == string::npos) //Zabezpieczenie przed wczytymaniem ilo�ci pozosta�ych pieni�dzy jak si� nie rozegra�o pe�nej rundy
			{
				buf2 = move(bufor2); //Przeniesienie do bufora pomocniczego do ci�cia tekstu i w�o�enie do niego linie o jedn� wcze�niej wcze�niej odczytanego tekstu
				buf2.erase(0, pocz�tek); //Usuni�cie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna� si� liczb�
				buf2.erase(buf2.size() - 1, 1); //Usuni�cie z bufora pomocniczego znaku dolara z prawej strony
				sscanf_s(buf2.c_str(), "%d", &ilo��_pieni�dzy); //Zamiana liczby w tek�cie na warto�� w zmiennnej liczbowej
			}
		}
		else if (buf.find("Gra rozpoczeta dnia") != string::npos) //Sprawdzenie czy w ostatniej niepustej lini znajduj� si� s�owa �wiadcz�ce o rozpocz�ciu nowej gry
			co_kontynuowa� = 'n'; //Je�eli si� znajduj� to przypisanie znaku rozpocz�cia rundy od pocz�tku
		else //Je�eli co� p�jdzie nie tak, to warunek aby gra si� niewysypa�a
			co_kontynuowa� = 'n'; //Je�eli si� znajduj� to przypisanie znaku rozpocz�cia rundy od pocz�tku
		log.close(); //Zamkni�cie pliku logu og�lnego
		log.open("log_aktualny.txt", ios::out | ios::app); //Ponowne wczytanie pliku, teraz tylko do odczytu i ustawienie kursora zapisu na koniec pliku
	}
	else
	{
		co_kontynuowa� = 'n'; //Przypisanie znaku rozpocz�cia rundy od pocz�tku
		log.open("log_aktualny.txt", ios::out); //Otwarcie pliku w trybie tylko do zapisu
		GetSystemTime(&Czas); //Pobieranie aktualnej daty i czasu z zegara systemowego

		string buf;
		buf += "Gra rozpoczeta dnia " + ((Czas.wDay < 10) ? ('0' + to_string(Czas.wDay)) : (to_string(Czas.wDay))) + '.' + ((Czas.wMonth < 10) ? ('0' + to_string(Czas.wMonth)) : (to_string(Czas.wMonth))) + '.' + to_string(Czas.wYear) + " o godzinie "; //Wpisanie do bufora zapisu danych o dniu,miesi�cu i roku wraz z dodatkowymi zerami dla formatowania
		if (Czas.wHour < 10) buf += '0'; //Wpisanie do bufora zapisu znaku zera dla r�wnego formatowania godzinny je�eli godzina jest minejsza ni� 10
		buf += to_string(Czas.wHour) + ':'; //Wpisanie do bufora zapisu znaku : dla rozdzielenia godzin od minut
		if (Czas.wMinute < 10) buf += '0'; //Wpisanie do bufora zapisu znaku zera dla r�wnego formatowania minut je�eli minuty jest minejsze ni� 10 do pliku log_aktualny.txt
		buf += to_string(Czas.wMinute) + ':'; //Wpisanie do bufora zapisu znaku : dla rozdzielenia minut od sekund do pliku log_aktualny.txt
		if (Czas.wSecond < 10) buf += '0'; //Wpisanie do bufora zapisu znaku zera dla r�wnego formatowania sekund je�eli sekundy jest minejsza ni� 10 do pliku log_aktualny.txt
		buf += to_string(Czas.wSecond) + '\n'; // Wpisanie do bufora zapisu danych o sekundzie do pliku log_aktualny.txt

		log.write(buf.c_str(), buf.size()); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych

		buf.replace(buf.begin(), buf.begin() + 1, "Nowa g"); //Zamiana pierwszej litery bufora aby doda� na pocz�tek stringa dopisek nowa
		log_og�lny.write(buf.c_str(), buf.size());  //Zapisanie do pliku log_og�lny.txt danych wpisanych do bufora danych

		log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
		log_og�lny.flush(); //Zapisanie do pliku log_og�lny.txt danych wpisanych do bufora danych
	}
}

void Sprawd�_Pliki(const short & g�os_odczytu_numeru, const short & g�os_szybko��_odczytu_numeru)
{
	if (Ustawienia.efekty_d�wi�kowe == 1) //Je�eli w��czono efekty d�wi�kowe
	{
		if ((_access("Efekty_d�wi�kowe", NULL))) //Sprawd� czy nie ma folderu Efekty d�wi�kowe
			CreateDirectory("Efekty_d�wi�kowe", nullptr); //Je�eli nie ma to utw�rz go

		bool czy_pobierano = false; //Utworzenie zmiennej informuj�c� czy rozpocz�to pobieranie plik�w
		bool czy_pobrano = true; //Utworzenie zmiennej informuj�c� czy ostatnie pobieranie zako�czy�o si� sukesem

		if ((_access("Efekty_d�wi�kowe/bankrut.wav", NULL))) //Sprawdzenie czy plik nie istnieje
		{
			cout << "Rozpoczynam pobieranie brakuj�cych plik�w efekt�w" << endl; //Poinformowaniu o rozpocz�ciu pobierania
			czy_pobierano = true; //Zmiana zmiennej aby wiadomo, �e rozpocz�to pobieranie
			if (!Wyci�gnij_z_Programu("Efekty_d�wi�kowe/bankrut.wav", IDR_BANKRUT)) //Je�eli nie uda�o wydoby� si� z zasob�w pliku bankrut.wav
			{
				const auto res = URLDownloadToFile(nullptr, "https://github.com/talez2709/Ruletka/raw/master/Ruletka/Efekty_d%C5%BAwi%C4%99kowe/bankrut.wav", "Efekty_d�wi�kowe/bankrut.wav", 0, nullptr); //Rozpocz�cie pobierania pliku
				if (res != S_OK) //Je�eli nie powiod�o si� pobieranie pliku
				{
					czy_pobrano = false; //Ustawienie zmiennej informuj�cej o sukcesie pobierania na warto�� false
					cout << "Brak plik�w dla efekt�w d�wi�kowych oraz nie mo�na pobra� danych, wy��czono efekty d�wi�kowe muzyczne, w��czono efekty systemowe" << endl; //Poinformowanie o nieudanym pobieraniu i konsekwencji tego
					EfektyKompletne = false; //Wpisanie do zmiennej warto�ci false informuj�cej o niekompletnych plikach audio
				}
			}
		}

		if (czy_pobrano) //Je�eli ostatnie pobieranie zako�czono prawid�owo
			if ((_access("Efekty_d�wi�kowe/wygrana1.wav", NULL))) //Sprawdzenie czy plik nie istnieje
			{
				if (!czy_pobierano) //Sprawdzanie czy jakie� pobieranie si� rozpocze�o
				{
					cout << "Rozpoczynam pobieranie brakuj�cych plik�w efekt�w" << endl; //Poinformowaniu o rozpocz�ciu pobierania
					czy_pobierano = true; //Zmiana zmiennej aby wiadomo, �e rozpocz�to pobieranie
				}
				if (!Wyci�gnij_z_Programu("Efekty_d�wi�kowe/wygrana1.wav", IDR_WYGRANA1)) //Je�eli nie uda�o wydoby� si� z zasob�w pliku wygrana1.wav
				{
					const auto res = URLDownloadToFile(nullptr, "https://github.com/talez2709/Ruletka/raw/master/Ruletka/Efekty_d%C5%BAwi%C4%99kowe/wygrana1.wav", "Efekty_d�wi�kowe/wygrana1.wav", 0, nullptr); //Rozpocz�cie pobierania pliku
					if (res != S_OK) //Je�eli nie powiod�o si� pobieranie pliku
					{
						czy_pobrano = false; //Ustawienie zmiennej informuj�cej o sukcesie pobierania na warto�� false
						cout << "Brak plik�w dla efekt�w d�wi�kowych oraz nie mo�na pobra� danych, wy��czono efekty d�wi�kowe muzyczne, w��czono efekty systemowe" << endl; //Poinformowanie o nieudanym pobieraniu i konsekwencji tego
						EfektyKompletne = false; //Wpisanie do zmiennej warto�ci false informuj�cej o niekompletnych plikach audio
					}
				}
			}

		if (czy_pobrano) //Je�eli ostatnie pobieranie zako�czono prawid�owo
			if ((_access("Efekty_d�wi�kowe/wygrana2.wav", NULL))) //Sprawdzenie czy plik nie istnieje
			{
				if (!czy_pobierano) //Sprawdzanie czy jakie� pobieranie si� rozpocze�o
				{
					cout << "Rozpoczynam pobieranie brakuj�cych plik�w efekt�w" << endl; //Poinformowaniu o rozpocz�ciu pobierania
					czy_pobierano = true; //Zmiana zmiennej aby wiadomo, �e rozpocz�to pobieranie
				}
				if (!Wyci�gnij_z_Programu("Efekty_d�wi�kowe/wygrana2.wav", IDR_WYGRANA2)) //Je�eli nie uda�o wydoby� si� z zasob�w pliku wygrana2.wav
				{
					const auto res = URLDownloadToFile(nullptr, "https://github.com/talez2709/Ruletka/raw/master/Ruletka/Efekty_d%C5%BAwi%C4%99kowe/wygrana2.wav", "Efekty_d�wi�kowe/wygrana2.wav", 0, nullptr); //Rozpocz�cie pobierania pliku
					if (res != S_OK) //Je�eli nie powiod�o si� pobieranie pliku
					{
						czy_pobrano = false; //Ustawienie zmiennej informuj�cej o sukcesie pobierania na warto�� false
						cout << "Brak plik�w dla efekt�w d�wi�kowych oraz nie mo�na pobra� danych, wy��czono efekty d�wi�kowe muzyczne, w��czono efekty systemowe" << endl; //Poinformowanie o nieudanym pobieraniu i konsekwencji tego
						EfektyKompletne = false; //Wpisanie do zmiennej warto�ci false informuj�cej o niekompletnych plikach audio
					}
				}
			}

		if (czy_pobrano) //Je�eli ostatnie pobieranie zako�czono prawid�owo
			if ((_access("Efekty_d�wi�kowe/zwielokrotnenie.wav", NULL))) //Sprawdzenie czy plik nie istnieje
			{
				if (!czy_pobierano) //Sprawdzanie czy jakie� pobieranie si� rozpocze�o
				{
					cout << "Rozpoczynam pobieranie brakuj�cych plik�w efekt�w" << endl; //Poinformowaniu o rozpocz�ciu pobierania
					czy_pobierano = true; //Zmiana zmiennej aby wiadomo, �e rozpocz�to pobieranie
				}
				if (!Wyci�gnij_z_Programu("Efekty_d�wi�kowe/zwielokrotnenie.wav", IDR_ZWIELOKROTNIENIE)) //Je�eli nie uda�o wydoby� si� z zasob�w pliku zwielokrotnienie.wav
				{
					const auto res = URLDownloadToFile(nullptr, "https://github.com/talez2709/Ruletka/raw/master/Ruletka/Efekty_d%C5%BAwi%C4%99kowe/zwielokrotnenie.wav", "Efekty_d�wi�kowe/zwielokrotnenie.wav", 0, nullptr); //Rozpocz�cie pobierania pliku
					if (res != S_OK) //Je�eli nie powiod�o si� pobieranie pliku
					{
						czy_pobrano = false; //Ustawienie zmiennej informuj�cej o sukcesie pobierania na warto�� false
						cout << "Brak plik�w dla efekt�w d�wi�kowych oraz nie mo�na pobra� danych, wy��czono efekty d�wi�kowe muzyczne, w��czono efekty systemowe" << endl; //Poinformowanie o nieudajnym pobieraniu i konsekwencji tego
						EfektyKompletne = false; //Wpisanie do zmiennej warto�ci false informuj�cej o niekompletnych plikach audio
					}
				}
			}

		if (czy_pobierano && czy_pobrano) cout << "Pobrano brakuj�ce pliki efekt�w" << endl; //Poinformowanie o uko�czonu pobierania plik�w
	}

	if (g�os_odczytu_numeru > 0) //Je�eli w��czono odczyt g�osowy
	{
		G�osyKompletne = true; //Ustawienie domy�nej warto�ci zmiennej globalnej G�osyKompletne

		G�os = "G�os/"; //Wpisanie do zmiennej G�os pocz�tku �cie�ki do pliku z g�osem
		G�os += Nazwa_g�osu[g�os_odczytu_numeru]; //U�ycie tablicy do wpisania odpowiedniej nazwy g�osu do zmiennej G�os
		G�os += "_"; //Dodanie do zmiennej podkre�lenia odzielaj�cego nazw� od szybko�ci
		G�os += '0' + g�os_szybko��_odczytu_numeru; //Dodanie do zmiennej szybko�ci mowy
		G�os += "/"; //Dodanie do zmiennej uko�nika kt�ry odziela nazw� folderu od pliku

		const string link = "https://github.com/talez2709/Ruletka/raw/master/Ruletka/G%C5%82os/"; //Zmienna przechowywuj�ca pocz�tek strony do pobierania g�osu

		string g�os2 = G�os.substr(5, string::npos); //Utworzenie zmiennej typu string do cel�w operowania adresem przy pobieraniu danych i w�o�enie do zmiennej napisu z zmiennej G�os z pomini�ciem 5 pierwszych znak�w

		const string g�os3 = g�os2.substr(0, g�os2.size() - 1); //Utorzenie stringa obez ostatniego znaku g�os2

		if (!(_access("Do_u�ytkownika.txt", NULL))) //Sprawdzam czy plik istnieje
		{
			if ( //Je�eli tak to sprawdzam czy wszystkie pliki s� pobrane
				(!(_access((G�os + "p.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k p
				(!(_access((G�os + "n.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k n
				(!(_access((G�os + "r.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k r
				(!(_access((G�os + "b.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k b
				(!(_access((G�os + "g.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k g
				(!(_access((G�os + "d.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k d
				(!(_access((G�os + "win.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k win
				(!(_access((G�os + "k1.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k k1
				(!(_access((G�os + "k2.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k k2
				(!(_access((G�os + "k3.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k k3
				(!(_access((G�os + "w1.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k w1
				(!(_access((G�os + "w2.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k w2
				(!(_access((G�os + "w3.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k w3
				(!(_access((G�os + "w4.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k w4
				(!(_access((G�os + "w5.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k w5
				(!(_access((G�os + "w6.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k w6
				(!(_access((G�os + "w7.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k w7
				(!(_access((G�os + "w8.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k w8
				(!(_access((G�os + "w9.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k w9
				(!(_access((G�os + "w10.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k w10
				(!(_access((G�os + "w11.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k w11
				(!(_access((G�os + "w12.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k w12
				(!(_access((G�os + "0.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 0
				(!(_access((G�os + "1.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 1
				(!(_access((G�os + "2.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 2
				(!(_access((G�os + "3.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 3
				(!(_access((G�os + "4.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 4
				(!(_access((G�os + "5.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 5
				(!(_access((G�os + "6.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 6
				(!(_access((G�os + "7.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 7
				(!(_access((G�os + "8.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 8
				(!(_access((G�os + "9.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 9
				(!(_access((G�os + "10.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 10
				(!(_access((G�os + "11.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 11
				(!(_access((G�os + "12.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 12
				(!(_access((G�os + "13.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 13
				(!(_access((G�os + "14.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 14
				(!(_access((G�os + "15.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 15
				(!(_access((G�os + "16.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 16
				(!(_access((G�os + "17.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 17
				(!(_access((G�os + "18.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 18
				(!(_access((G�os + "19.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 19
				(!(_access((G�os + "20.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 20
				(!(_access((G�os + "21.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 21
				(!(_access((G�os + "22.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 22
				(!(_access((G�os + "23.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 23
				(!(_access((G�os + "24.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 24
				(!(_access((G�os + "25.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 25
				(!(_access((G�os + "26.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 26
				(!(_access((G�os + "27.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 27
				(!(_access((G�os + "28.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 28
				(!(_access((G�os + "29.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 29
				(!(_access((G�os + "30.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 30
				(!(_access((G�os + "31.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 31
				(!(_access((G�os + "32.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 32
				(!(_access((G�os + "33.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 33
				(!(_access((G�os + "34.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 34
				(!(_access((G�os + "35.wav").c_str(), NULL))) && //Sprawdzam czy jest d�wi�k 35
				(!(_access((G�os + "36.wav").c_str(), NULL))) //Sprawdzam czy jest d�wi�k 36
				)
			{
				cout << "Pobrano wszystkie pliki g�os�w" << endl; //Poinformowanie, �e pobrano wszystkie pliki g�os�w
				DeleteFile("Do_u�ytkownika.txt"); //Usuwam plik Do_u�ytkownika.txt
				Usu�_Folder_Wypakowany_i_Winrar(g�os2); //Usni�cie folderu z wypakowanymi elementami i programu do wypakowywania
				return; //Wyj�cie z funkcji
			}

			G�osyKompletne = false; //Zmieniam warto�� zmiennej na false poniewa� nie ma wszystkich plik�w g�osu
			cout << "Wy��czono g�os z powodu braku plik�w" << endl; //Informuj� o tym u�ytkownika
			Usu�_Folder_Wypakowany_i_Winrar(g�os2); //Usni�cie folderu z wypakowanymi elementami i programu do wypakowywania
			return; //Wyj�cie z funkcji
		}

		if ((_access("G�os", NULL))) //Sprawd� czy nie ma folderu G�os
			CreateDirectory("G�os", nullptr); //Je�eli nie ma to utw�rz go
		if ((_access((G�os).c_str(), NULL))) //Sprawd� czy nie ma w folderze G�os podfolderu z nazw� i szybko�ci� g�osu
		{
			CreateDirectory((G�os).c_str(), nullptr); //Je�eli nie ma to utw�rz go
			cout << "Rozpoczynam pobieranie brakuj�cych plik�w g�osu " << g�os3 << endl; //Poinformowaniu o rozpocz�ciu pobierania
			Wyci�gnij_z_Programu((g�os3 + ".rar"), Numer_zasobu_rar.at(g�os3)); //Wyci�gni�cie z zasob�w folderu rar z g�osem
			Wypakuj_Rar(g�os3 + ".rar"); //Wypakowanie folderu rar z g�osem
			vector<thread> vec_thr; //Utworzenie kontenera vector na w�tki
			stack<string> stos_nazw_plik�w; //Utworzenie kontenera stos na nazwy plik�w
			stos_nazw_plik�w.push("p"); stos_nazw_plik�w.push("n"); stos_nazw_plik�w.push("r"); stos_nazw_plik�w.push("b"); stos_nazw_plik�w.push("d"); stos_nazw_plik�w.push("g"); stos_nazw_plik�w.push("k1"); stos_nazw_plik�w.push("k2"); stos_nazw_plik�w.push("k3"); stos_nazw_plik�w.push("w1"); stos_nazw_plik�w.push("w2"); stos_nazw_plik�w.push("w3"); stos_nazw_plik�w.push("w4"); stos_nazw_plik�w.push("w5"); stos_nazw_plik�w.push("w6"); stos_nazw_plik�w.push("w7"); stos_nazw_plik�w.push("w8"); stos_nazw_plik�w.push("w9"); stos_nazw_plik�w.push("w10"); stos_nazw_plik�w.push("w11"); stos_nazw_plik�w.push("w12"); stos_nazw_plik�w.push("0"); stos_nazw_plik�w.push("1"); stos_nazw_plik�w.push("2"); stos_nazw_plik�w.push("3"); stos_nazw_plik�w.push("4"); stos_nazw_plik�w.push("5"); stos_nazw_plik�w.push("6"); stos_nazw_plik�w.push("7"); stos_nazw_plik�w.push("8"); stos_nazw_plik�w.push("9"); stos_nazw_plik�w.push("10"); stos_nazw_plik�w.push("11"); stos_nazw_plik�w.push("12"); stos_nazw_plik�w.push("13"); stos_nazw_plik�w.push("14"); stos_nazw_plik�w.push("15"); stos_nazw_plik�w.push("16"); stos_nazw_plik�w.push("17"); stos_nazw_plik�w.push("18"); stos_nazw_plik�w.push("19"); stos_nazw_plik�w.push("20"); stos_nazw_plik�w.push("21"); stos_nazw_plik�w.push("22"); stos_nazw_plik�w.push("23"); stos_nazw_plik�w.push("24"); stos_nazw_plik�w.push("25"); stos_nazw_plik�w.push("26"); stos_nazw_plik�w.push("27"); stos_nazw_plik�w.push("28"); stos_nazw_plik�w.push("29"); stos_nazw_plik�w.push("30"); stos_nazw_plik�w.push("31"); stos_nazw_plik�w.push("32"); stos_nazw_plik�w.push("33"); stos_nazw_plik�w.push("34"); stos_nazw_plik�w.push("35"); stos_nazw_plik�w.push("36"); stos_nazw_plik�w.push("win"); //Umieszczenie na stosie nazw plik�w d�wi�kowy do przeniesienia

			while (!stos_nazw_plik�w.empty()) //P�tla do czasu wyczyszczenia stosu
			{
				thread thr([](string a, const string & g�os2, const string & link)->void {if (!Przenie�_Plik(g�os2 + a + ".wav", G�os + a + ".wav")) { //U�ycie wyra�enia lambda aby utworzy� w�tki do przenoszenia plik�w
					const auto res = URLDownloadToFile(nullptr, (link + g�os2 + a + ".wav").c_str(), (G�os + a + ".wav").c_str(), 0, nullptr); if (res != S_OK) { //Je�eli nieuda�o si� wydoby� z zasob�w pliku to spr�buj pobra� plik
						if (G�osyKompletne) { //Je�eli nieuda�o si� pobra� pliku
							cout << "Brak plik�w dla g�osu oraz nie mo�na pobra� danych, wy��czono odczytywanie wyniku" << endl; G�osyKompletne = false; Usu�_Folder_Wypakowany_i_Winrar(g�os2); return; //Poinformuj o tym u�ytkownika
						}
					}
				}}, stos_nazw_plik�w.top(), ref(g�os2), ref(link)); //utworzenie w�tku do przenoszenia pliku
				vec_thr.push_back(move(thr)); //Przeniesienie w�tku do vectora
				stos_nazw_plik�w.pop(); //Zdj�cie elementu z wieszcho�ka stosu
			}
			for (auto& t : vec_thr) t.join(); //Poczekanie na zako�czenie wszystkich w�tk�w
			if (G�osyKompletne) cout << endl << "Pobrano brakuj�ce pliki g�os�w" << endl; //Poinformowanie o uko�czonu pobierania plik�w , je�eli pobra�o si� wszystkie pliki
			Usu�_Folder_Wypakowany_i_Winrar(g�os2); //Usni�cie folderu z wypakowanymi elementami i programu do wypakowywania
			Wyci�gnij_z_Programu("Do_u�ytkownika.txt", IDR_RCDATA46); //Wyci�gni�cie z programu pliku informuj�cego o mo�liwym b��dzie
			ShellExecuteA(nullptr, nullptr, "Ruletka.exe", nullptr, nullptr, SW_SHOW); //Ponowne uruchomienie programu
			const auto PID = GetCurrentProcessId(); //Pobranie numeru aktualnego procesu
			if (!TerminateProcess(PID, 123)) //Zamkni�cie bie��cego procesu
				cout << "Nie uda�o si� ponownie uruchomi� programu, mog� pojawi� si� b��dy z wy�wietlaniem tekstu" << endl; //Poinformowanie o mo�liwym b��dzie
		}

		bool czy_pobierano = false; //Utworzenie zmiennej logicznej informuj�cej czy jakie� pobieranie si� rozpocze�o

		if ((_access((G�os + "p.wav").c_str(), NULL))) //Sprawdzenie czy plik nie istnieje
		{
			cout << "Rozpoczynam pobieranie brakuj�cych plik�w g�osu" << endl; //Poinformowaniu o rozpocz�ciu pobierania
			czy_pobierano = true; //Zmiana zmiennej aby wiadomo, �e rozpocz�to pobieranie
			Wyci�gnij_z_Programu((g�os3 + ".rar"), Numer_zasobu_rar.at(g�os3)); //Wyci�gni�cie z zasob�w folderu rar z g�osem
			Wypakuj_Rar(g�os3 + ".rar"); //Wypakowanie folderu rar z g�osem
			if (!Przenie�_Plik(g�os2 + "p.wav", G�os + "p.wav")) //Je�eli nie uda�o si� przenie�� wypakowanego pliku
			{
				const auto res = URLDownloadToFile(nullptr, (link + g�os2 + "p.wav").c_str(), (G�os + "p.wav").c_str(), 0, nullptr); //Rozpocz�cie pobierania pliku
				if (res != S_OK) //Je�eli nie powiod�o si� pobieranie pliku
				{
					cout << "Brak plik�w dla g�osu oraz nie mo�na pobra� danych, wy��czono odczytywanie wyniku" << endl; //Poinformowanie o nieudajnym pobieraniu i konsekwencji tego
					G�osyKompletne = false; //Wpisanie do zmiennej warto�ci false informuj�cej o niekompletnych plikach audio
					Usu�_Folder_Wypakowany_i_Winrar(g�os2); //Usni�cie folderu z wypakowanymi elementami i programu do wypakowywania
					return; //Wyj�cie z funkcji poniewa� nie ma sensu sprawdzania dalej
				}
			}
		}

		if ((_access((G�os + "n.wav").c_str(), NULL))) //Sprawdzenie czy plik nie istnieje
		{
			if (!czy_pobierano) //Sprawdzanie czy jakie� pobieranie si� nie rozpocze�o
			{
				cout << "Rozpoczynam pobieranie brakuj�cych plik�w g�osu" << endl; //Poinformowaniu o rozpocz�ciu pobierania
				czy_pobierano = true; //Zmiana zmiennej aby wiadomo, �e rozpocz�to pobieranie
				Wyci�gnij_z_Programu((g�os3 + ".rar"), Numer_zasobu_rar.at(g�os3)); //Wyci�gni�cie z zasob�w folderu rar z g�osem
				Wypakuj_Rar(g�os3 + ".rar"); //Wypakowanie folderu rar z g�osem
			}
			if (!Przenie�_Plik(g�os2 + "n.wav", G�os + "n.wav")) //Je�eli nie uda�o si� przenie�� wypakowanego pliku
			{
				const auto res = URLDownloadToFile(nullptr, (link + g�os2 + "n.wav").c_str(), (G�os + "n.wav").c_str(), 0, nullptr); //Rozpocz�cie pobierania pliku
				if (res != S_OK) //Je�eli nie powiod�o si� pobieranie pliku
				{
					cout << "Brak plik�w dla g�osu oraz nie mo�na pobra� danych, wy��czono odczytywanie wyniku" << endl; //Poinformowanie o nieudajnym pobieraniu i konsekwencji tego
					G�osyKompletne = false; //Wpisanie do zmiennej warto�ci false informuj�cej o niekompletnych plikach audio
					Usu�_Folder_Wypakowany_i_Winrar(g�os2); //Usni�cie folderu z wypakowanymi elementami i programu do wypakowywania
					return; //Wyj�cie z funkcji poniewa� nie ma sensu sprawdzania dalej
				}
			}
		}

		if ((_access((G�os + "r.wav").c_str(), NULL))) //Sprawdzenie czy plik nie istnieje
		{
			if (!czy_pobierano) //Sprawdzanie czy jakie� pobieranie si� nie rozpocze�o
			{
				cout << "Rozpoczynam pobieranie brakuj�cych plik�w g�osu" << endl; //Poinformowaniu o rozpocz�ciu pobierania
				czy_pobierano = true; //Zmiana zmiennej aby wiadomo, �e rozpocz�to pobieranie
				Wyci�gnij_z_Programu((g�os3 + ".rar"), Numer_zasobu_rar.at(g�os3)); //Wyci�gni�cie z zasob�w folderu rar z g�osem
				Wypakuj_Rar(g�os3 + ".rar"); //Wypakowanie folderu rar z g�osem
			}
			if (!Przenie�_Plik(g�os2 + "r.wav", G�os + "r.wav")) //Je�eli nie uda�o si� przenie�� wypakowanego pliku
			{
				const auto res = URLDownloadToFile(nullptr, (link + g�os2 + "r.wav").c_str(), (G�os + "r.wav").c_str(), 0, nullptr); //Rozpocz�cie pobierania pliku
				if (res != S_OK) //Je�eli nie powiod�o si� pobieranie pliku
				{
					cout << "Brak plik�w dla g�osu oraz nie mo�na pobra� danych, wy��czono odczytywanie wyniku" << endl; //Poinformowanie o nieudajnym pobieraniu i konsekwencji tego
					G�osyKompletne = false; //Wpisanie do zmiennej warto�ci false informuj�cej o niekompletnych plikach audio
					Usu�_Folder_Wypakowany_i_Winrar(g�os2); //Usni�cie folderu z wypakowanymi elementami i programu do wypakowywania
					return; //Wyj�cie z funkcji poniewa� nie ma sensu sprawdzania dalej
				}
			}
		}

		if ((_access((G�os + "b.wav").c_str(), NULL))) //Sprawdzenie czy plik nie istnieje
		{
			if (!czy_pobierano) //Sprawdzanie czy jakie� pobieranie si� nie rozpocze�o
			{
				cout << "Rozpoczynam pobieranie brakuj�cych plik�w g�osu" << endl; //Poinformowaniu o rozpocz�ciu pobierania
				czy_pobierano = true; //Zmiana zmiennej aby wiadomo, �e rozpocz�to pobieranie
				Wyci�gnij_z_Programu((g�os3 + ".rar"), Numer_zasobu_rar.at(g�os3)); //Wyci�gni�cie z zasob�w folderu rar z g�osem
				Wypakuj_Rar(g�os3 + ".rar"); //Wypakowanie folderu rar z g�osem
			}
			if (!Przenie�_Plik(g�os2 + "b.wav", G�os + "b.wav")) //Je�eli nie uda�o si� przenie�� wypakowanego pliku
			{
				const auto res = URLDownloadToFile(nullptr, (link + g�os2 + "b.wav").c_str(), (G�os + "b.wav").c_str(), 0, nullptr); //Rozpocz�cie pobierania pliku
				if (res != S_OK) //Je�eli nie powiod�o si� pobieranie pliku
				{
					cout << "Brak plik�w dla g�osu oraz nie mo�na pobra� danych, wy��czono odczytywanie wyniku" << endl; //Poinformowanie o nieudajnym pobieraniu i konsekwencji tego
					G�osyKompletne = false; //Wpisanie do zmiennej warto�ci false informuj�cej o niekompletnych plikach audio
					Usu�_Folder_Wypakowany_i_Winrar(g�os2); //Usni�cie folderu z wypakowanymi elementami i programu do wypakowywania
					return; //Wyj�cie z funkcji poniewa� nie ma sensu sprawdzania dalej
				}
			}
		}

		if ((_access((G�os + "g.wav").c_str(), NULL))) //Sprawdzenie czy plik nie istnieje
		{
			if (!czy_pobierano) //Sprawdzanie czy jakie� pobieranie si� nie rozpocze�o
			{
				cout << "Rozpoczynam pobieranie brakuj�cych plik�w g�osu" << endl; //Poinformowaniu o rozpocz�ciu pobierania
				czy_pobierano = true; //Zmiana zmiennej aby wiadomo, �e rozpocz�to pobieranie
				Wyci�gnij_z_Programu((g�os3 + ".rar"), Numer_zasobu_rar.at(g�os3)); //Wyci�gni�cie z zasob�w folderu rar z g�osem
				Wypakuj_Rar(g�os3 + ".rar"); //Wypakowanie folderu rar z g�osem
			}
			if (!Przenie�_Plik(g�os2 + "g.wav", G�os + "g.wav")) //Je�eli nie uda�o si� przenie�� wypakowanego pliku
			{
				const auto res = URLDownloadToFile(nullptr, (link + g�os2 + "g.wav").c_str(), (G�os + "g.wav").c_str(), 0, nullptr); //Rozpocz�cie pobierania pliku
				if (res != S_OK) //Je�eli nie powiod�o si� pobieranie pliku
				{
					cout << "Brak plik�w dla g�osu oraz nie mo�na pobra� danych, wy��czono odczytywanie wyniku" << endl; //Poinformowanie o nieudajnym pobieraniu i konsekwencji tego
					G�osyKompletne = false; //Wpisanie do zmiennej warto�ci false informuj�cej o niekompletnych plikach audio
					Usu�_Folder_Wypakowany_i_Winrar(g�os2); //Usni�cie folderu z wypakowanymi elementami i programu do wypakowywania
					return; //Wyj�cie z funkcji poniewa� nie ma sensu sprawdzania dalej
				}
			}
		}

		if ((_access((G�os + "d.wav").c_str(), NULL))) //Sprawdzenie czy plik nie istnieje
		{
			if (!czy_pobierano) //Sprawdzanie czy jakie� pobieranie si� nie rozpocze�o
			{
				cout << "Rozpoczynam pobieranie brakuj�cych plik�w g�osu" << endl; //Poinformowaniu o rozpocz�ciu pobierania
				czy_pobierano = true; //Zmiana zmiennej aby wiadomo, �e rozpocz�to pobieranie
				Wyci�gnij_z_Programu((g�os3 + ".rar"), Numer_zasobu_rar.at(g�os3)); //Wyci�gni�cie z zasob�w folderu rar z g�osem
				Wypakuj_Rar(g�os3 + ".rar"); //Wypakowanie folderu rar z g�osem
			}
			if (!Przenie�_Plik(g�os2 + "d.wav", G�os + "d.wav")) //Je�eli nie uda�o si� przenie�� wypakowanego pliku
			{
				const auto res = URLDownloadToFile(nullptr, (link + g�os2 + "d.wav").c_str(), (G�os + "d.wav").c_str(), 0, nullptr); //Rozpocz�cie pobierania pliku
				if (res != S_OK) //Je�eli nie powiod�o si� pobieranie pliku
				{
					cout << "Brak plik�w dla g�osu oraz nie mo�na pobra� danych, wy��czono odczytywanie wyniku" << endl; //Poinformowanie o nieudajnym pobieraniu i konsekwencji tego
					G�osyKompletne = false; //Wpisanie do zmiennej warto�ci false informuj�cej o niekompletnych plikach audio
					Usu�_Folder_Wypakowany_i_Winrar(g�os2); //Usni�cie folderu z wypakowanymi elementami i programu do wypakowywania
					return; //Wyj�cie z funkcji poniewa� nie ma sensu sprawdzania dalej
				}
			}
		}

		for (auto i = 1; i <= 3; ++i) //P�tla licz�ca od 1 do 3
		{
			if ((_access((G�os + 'k' + char('0' + i) + ".wav").c_str(), NULL))) //Sprawdzenie czy plik nie istnieje
			{
				if (!czy_pobierano) //Sprawdzanie czy jakie� pobieranie si� nie rozpocze�o
				{
					cout << "Rozpoczynam pobieranie brakuj�cych plik�w g�osu" << endl; //Poinformowaniu o rozpocz�ciu pobierania
					czy_pobierano = true; //Zmiana zmiennej aby wiadomo, �e rozpocz�to pobieranie
					Wyci�gnij_z_Programu((g�os3 + ".rar"), Numer_zasobu_rar.at(g�os3)); //Wyci�gni�cie z zasob�w folderu rar z g�osem
					Wypakuj_Rar(g�os3 + ".rar"); //Wypakowanie folderu rar z g�osem
				}
				if (!Przenie�_Plik(g�os2 + 'k' + char('0' + i) + ".wav", G�os + 'k' + char('0' + i) + ".wav")) //Je�eli nie uda�o si� przenie�� wypakowanego pliku
				{
					const auto res = URLDownloadToFile(nullptr, (link + g�os2 + 'k' + char('0' + i) + ".wav").c_str(), (G�os + 'k' + char('0' + i) + ".wav").c_str(), 0, nullptr); //Rozpocz�cie pobierania pliku
					if (res != S_OK) //Je�eli nie powiod�o si� pobieranie pliku
					{
						cout << "Brak plik�w dla g�osu oraz nie mo�na pobra� danych, wy��czono odczytywanie wyniku" << endl; //Poinformowanie o nieudajnym pobieraniu i konsekwencji tego
						G�osyKompletne = false; //Wpisanie do zmiennej warto�ci false informuj�cej o niekompletnych plikach audio
						Usu�_Folder_Wypakowany_i_Winrar(g�os2); //Usni�cie folderu z wypakowanymi elementami i programu do wypakowywania
						return; //Wyj�cie z funkcji poniewa� nie ma sensu sprawdzania dalej
					}
				}
			}
		}

		auto const numersw = new char[3]; //Utworzenie tablicy do zamiany liczby na tekst
		for (auto i = 1; i <= 12; ++i) //P�tla licz�ca od 1 do 12
		{
			_itoa_s(i, numersw, 3, 10); //Wpisanie do tablicy warto�ci z obrotu p�tli
			if ((_access((G�os + 'w' + numersw + ".wav").c_str(), NULL))) //Sprawdzenie czy plik nie istnieje
			{
				if (!czy_pobierano) //Sprawdzanie czy jakie� pobieranie si� nie rozpocze�o
				{
					cout << "Rozpoczynam pobieranie brakuj�cych plik�w g�osu" << endl; //Poinformowaniu o rozpocz�ciu pobierania
					czy_pobierano = true; //Zmiana zmiennej aby wiadomo, �e rozpocz�to pobieranie
					Wyci�gnij_z_Programu((g�os3 + ".rar"), Numer_zasobu_rar.at(g�os3)); //Wyci�gni�cie z zasob�w folderu rar z g�osem
					Wypakuj_Rar(g�os3 + ".rar"); //Wypakowanie folderu rar z g�osem
				}
				if (!Przenie�_Plik(g�os2 + 'w' + numersw + ".wav", G�os + 'w' + numersw + ".wav")) //Je�eli nie uda�o si� przenie�� wypakowanego pliku
				{
					const auto res = URLDownloadToFile(nullptr, (link + g�os2 + 'w' + numersw + ".wav").c_str(), (G�os + 'w' + numersw + ".wav").c_str(), 0, nullptr); //Rozpocz�cie pobierania pliku
					if (res != S_OK) //Je�eli nie powiod�o si� pobieranie pliku
					{
						cout << "Brak plik�w dla g�osu oraz nie mo�na pobra� danych, wy��czono odczytywanie wyniku" << endl; //Poinformowanie o nieudajnym pobieraniu i konsekwencji tego
						G�osyKompletne = false; //Wpisanie do zmiennej warto�ci false informuj�cej o niekompletnych plikach audio
						Usu�_Folder_Wypakowany_i_Winrar(g�os2); //Usni�cie folderu z wypakowanymi elementami i programu do wypakowywania
						return; //Wyj�cie z funkcji poniewa� nie ma sensu sprawdzania dalej
					}
				}
			}
		}
		delete[] numersw; //Usuwam tablic�, poniewa� tablice dynamiczne same si� nie usuwaj� po wyj�ciu z scop-a

		char numers[3]; //Utworzenie tablicy do zamiany liczby na tekst
		for (auto i = 0; i <= 36; ++i) //P�tla licz�ca od 0 do 36
		{
			_itoa_s(i, numers, 10); //Wpisanie do tablicy warto�ci z obrotu p�tli
			if ((_access((G�os + numers + ".wav").c_str(), NULL))) //Sprawdzenie czy plik nie istnieje
			{
				if (!czy_pobierano) //Sprawdzanie czy jakie� pobieranie si� nie rozpocze�o
				{
					cout << "Rozpoczynam pobieranie brakuj�cych plik�w g�osu" << endl; //Poinformowaniu o rozpocz�ciu pobierania
					czy_pobierano = true; //Zmiana zmiennej aby wiadomo, �e rozpocz�to pobieranie
					Wyci�gnij_z_Programu((g�os3 + ".rar"), Numer_zasobu_rar.at(g�os3)); //Wyci�gni�cie z zasob�w folderu rar z g�osem
					Wypakuj_Rar(g�os3 + ".rar"); //Wypakowanie folderu rar z g�osem
				}
				if (!Przenie�_Plik(g�os2 + numers + ".wav", G�os + numers + ".wav")) //Je�eli nie uda�o si� przenie�� wypakowanego pliku
				{
					const auto res = URLDownloadToFile(nullptr, (link + g�os2 + numers + ".wav").c_str(), (G�os + numers + ".wav").c_str(), 0, nullptr); //Rozpocz�cie pobierania pliku
					if (res != S_OK) //Je�eli nie powiod�o si� pobieranie pliku
					{
						cout << "Brak plik�w dla g�osu oraz nie mo�na pobra� danych, wy��czono odczytywanie wyniku" << endl; //Poinformowanie o nieudajnym pobieraniu i konsekwencji tego
						G�osyKompletne = false; //Wpisanie do zmiennej warto�ci false informuj�cej o niekompletnych plikach audio
						Usu�_Folder_Wypakowany_i_Winrar(g�os2); //Usni�cie folderu z wypakowanymi elementami i programu do wypakowywania
						return; //Wyj�cie z funkcji poniewa� nie ma sensu sprawdzania dalej
					}
				}
			}
		}

		if ((_access((G�os + "win.wav").c_str(), NULL))) //Sprawdzenie czy plik nie istnieje
		{
			if (!czy_pobierano) //Sprawdzanie czy jakie� pobieranie si� nie rozpocze�o
			{
				cout << "Rozpoczynam pobieranie brakuj�cych plik�w g�osu" << endl; //Poinformowaniu o rozpocz�ciu pobierania
				czy_pobierano = true; //Zmiana zmiennej aby wiadomo, �e rozpocz�to pobieranie
				Wyci�gnij_z_Programu((g�os3 + ".rar"), Numer_zasobu_rar.at(g�os3)); //Wyci�gni�cie z zasob�w folderu rar z g�osem
				Wypakuj_Rar(g�os3 + ".rar"); //Wypakowanie folderu rar z g�osem
			}
			if (!Przenie�_Plik(g�os2 + "win.wav", G�os + "win.wav")) //Je�eli nie uda�o si� przenie�� wypakowanego pliku
			{
				const auto res = URLDownloadToFile(nullptr, (link + g�os2 + "win.wav").c_str(), (G�os + "win.wav").c_str(), 0, nullptr); //Rozpocz�cie pobierania pliku
				if (res != S_OK) //Je�eli nie powiod�o si� pobieranie pliku
				{
					cout << "Brak plik�w dla g�osu oraz nie mo�na pobra� danych, wy��czono odczytywanie wyniku" << endl; //Poinformowanie o nieudajnym pobieraniu i konsekwencji tego
					G�osyKompletne = false; //Wpisanie do zmiennej warto�ci false informuj�cej o niekompletnych plikach audio
					Usu�_Folder_Wypakowany_i_Winrar(g�os2); //Usni�cie folderu z wypakowanymi elementami i programu do wypakowywania
					return; //Wyj�cie z funkcji poniewa� nie ma sensu sprawdzania dalej
				}
			}
		}

		if (czy_pobierano) //Sprawdzenie czy pobra�o si� wszystkie pliki
		{
			cout << endl << "Pobrano brakuj�ce pliki g�os�w" << endl; //Poinformowanie o uko�czonu pobierania plik�w
			Usu�_Folder_Wypakowany_i_Winrar(g�os2); //Usni�cie folderu z wypakowanymi elementami i programu do wypakowywania
			Wyci�gnij_z_Programu("Do_u�ytkownika.txt", IDR_RCDATA46); //Wyci�gni�cie z programu pliku informuj�cego o mo�liwym b��dzie
			ShellExecuteA(nullptr, nullptr, "Ruletka.exe", nullptr, nullptr, SW_SHOW); //Ponowne uruchomienie programu
			const auto PID = GetCurrentProcessId(); //Pobranie numeru aktualnego procesu
			if (!TerminateProcess(PID, 123)) //Zamkni�cie bie��cego procesu
				cout << "Nie uda�o si� ponownie uruchomi� programu, mog� pojawi� si� b��dy z wy�wietlaniem tekstu" << endl; //Poinformowanie o mo�liwym b��dzie
		}
	}
}

void Sprawd�_Ustawienia()
{
	if (!_access("setting.txt", NULL)) // Sprawdzenie dost�pu do pliku (je�eli takowy istnieje, musi istnie� plik)
	{
		ifstream ustawienia; //Utworzenie typu do celu odczytu z pliku
		ustawienia.open("setting.txt"); //Otwarcie pliku z ustawieniami
		string buf; //Utworzenie buforu do odczytu z pliku
		unsigned char licznik = 0;
		while (!ustawienia.eof()) //P�tla trwaj�ca do ko�ca pliku
		{
			getline(ustawienia, buf); //Wczytanie ca�ej lini tekstu z pliku
			Ustaw_Ustawienia(buf); //Zamiana wczytanej lini na ustawienie programu
			++licznik;
		}
		ustawienia.close(); //Zamkni�cie pliku setting.txt
		if (licznik < 13) //Je�eli ilo�� wczytanych liniejek jest mniejsza ni� 12 to znacz, �e brakuje jakie� linijki w pliku ustawie�
		{
			cout << "Plik z ustawieniami jest niekompletny, utworzy�em nowy" << endl;
			DeleteFile("setting.txt"); //wi�c usu� nieca�kowity plik
			Sprawd�_Ustawienia(); //Uruchom jeszcze raz funkcje, aby utorzy� prawid�owy plik
			return; //Wyjd� z funkcji
		}
	}
	else
	{
		ofstream ustawienia; //Utworzenie typu do celu zapisu do pliku
		ustawienia.open("setting.txt"); //Otwarcie pliku do wygenerowania ustawie� domy�lnych
		auto const bufor_zapisu = new char[358]; //Utworzenie buforu
		memcpy(bufor_zapisu, "ilo��_min_dodatkowych_obrot�w_ruletki 2\nilo��_max_dodatkowych_obrot�w_ruletki 3\nczas_przeskoku_kulki_szybki 50\nczas_przeskoku_kulki_wolny 75\nczas_przerwy_dzwi�ku 500\nstyl_liczenia_wygranej 1\nkwota_pocz�tkowa 1000\nstan_d�wi�k�w 1\nczy_kontynuowa�_gr� 1\ng�os_odczytu_numeru 1\ng�os_szybko��_odczytu_numeru 4\nefekty_d�wi�kowe 1\nmetoda_liczenia_wygranej_zerowej 1", 358); //Wpisanie do pliku domy�nych ustawie�
		ustawienia.write(bufor_zapisu, 357); //Zapisanie do pliku setting.txt danych wpisanych do bufora danych
		delete[] bufor_zapisu; //Usuni�cie buforu
		ustawienia.close(); //Zamkni�cie pliku setting.txt
		return; //Wyjd� z funkcji
	}

	if (Ustawienia.czas_przeskoku_kulki_wolny < Ustawienia.czas_przeskoku_kulki_szybki) //Sprawdzenie czy prawid�owo wprowadzono ustawienie, czy �apie si� w zakresie i warunkach
	{
		cout << "Warto�� wolnego czasu przeskoku kulki musi by� ni�sza ni� warto�� szybkiego czasu przeskoku kulki" << endl; //(Warto�ci tych zmiennych to czas op�nienia wi�c im jest wy�szy tym d�u�sza przerwa)
		cout << "Ustawiam domy�lne ustawienie" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje zmienone na domy�lne
		Ustawienia.czas_przeskoku_kulki_szybki = 50; //Ustawienie warto�ci domy�lnej
		Ustawienia.czas_przeskoku_kulki_wolny = 75; //Ustawienie warto�ci domy�lnej
	}
	if (Ustawienia.ilo��_min_dodatkowych_obrot�w_ruletki < 0) //Sprawdzenie czy prawid�owo wprowadzono ustawienie, czy �apie si� w zakresie i warunkach
	{
		cout << "Ilo�� minimalna obrot�w ruletki nie mo�e by� mniejsza od 0" << endl; //Poinformowanie u�ytkownika o problemie
		cout << "Ustawiam domy�lne ustawienie" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje zmienone na domy�lne
		Ustawienia.ilo��_min_dodatkowych_obrot�w_ruletki = 2; //Ustawienie warto�ci domy�lnej
	}
	if (Ustawienia.ilo��_max_dodatkowych_obrot�w_ruletki < 0) //Sprawdzenie czy prawid�owo wprowadzono ustawienie, czy �apie si� w zakresie i warunkach
	{
		cout << "Ilo�� max obrot�w ruletki nie mo�e by� mniejsza od 0" << endl; //Poinformowanie u�ytkownika o problemie
		cout << "Ustawiam domy�lne ustawienie" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje zmienone na domy�lne
		Ustawienia.ilo��_max_dodatkowych_obrot�w_ruletki = 3; //Ustawienie warto�ci domy�lnej
	}
	if (Ustawienia.ilo��_max_dodatkowych_obrot�w_ruletki < Ustawienia.ilo��_min_dodatkowych_obrot�w_ruletki) //Sprawdzenie czy prawid�owo wprowadzono ustawienie, czy �apie si� w zakresie i warunkach
	{
		cout << "Max dodoatkowych obrot�w ruletki nie mo�e by� mniejszy od min dodatkowych obrot�w ruletki" << endl; //Poinformowanie u�ytkownika o problemie
		cout << "Zamieniam miejscami ustawienia" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje zmienone na domy�lne
		swap(Ustawienia.ilo��_min_dodatkowych_obrot�w_ruletki, Ustawienia.ilo��_max_dodatkowych_obrot�w_ruletki); //Zamiana miejscami ustawie�
	}
	if (Ustawienia.czas_przerwy_dzwi�ku < 0) //Sprawdzenie czy prawid�owo wprowadzono ustawienie, czy �apie si� w zakresie i warunkach
	{
		cout << "Czas przerwy d�wi�ku nie mo�e by� mniejszy od zera" << endl; //Poinformowanie u�ytkownika o problemie
		cout << "Ustawiam domy�lne ustawienie" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje zmienone na domy�lne
		Ustawienia.czas_przerwy_dzwi�ku = 500; //Ustawienie warto�ci domy�lnej
	}
	if (Ustawienia.kwota_pocz�tkowa < 0) //Sprawdzenie czy prawid�owo wprowadzono ustawienie, czy �apie si� w zakresie i warunkach
	{
		cout << "Kwota pocz�tkowa nie mo�e by� mniejsza od zera" << endl; //Poinformowanie u�ytkownika o problemie
		cout << "Ustawiam domy�lne ustawienie" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje zmienone na domy�lne
		Ustawienia.kwota_pocz�tkowa = 1000; //Ustawienie warto�ci domy�lnej
	}
	if ((Ustawienia.g�os_odczytu_numeru > 10) || (Ustawienia.g�os_odczytu_numeru < 0)) //Sprawdzenie czy prawid�owo wprowadzono ustawienie, czy �apie si� w zakresie i warunkach
	{
		cout << "Opcja g�os odczytu numeru przyjmuje warto�ci w przedziale [0;10]" << endl; //Poinformowanie u�ytkownika o problemie
		cout << "Ustawiam domy�lne ustawienie" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje zmienone na domy�lne
		Ustawienia.g�os_odczytu_numeru = 1; //Ustawienie warto�ci domy�lnej
	}
	if ((Ustawienia.g�os_szybko��_odczytu_numeru > 5) || (Ustawienia.g�os_szybko��_odczytu_numeru < 1)) //Sprawdzenie czy prawid�owo wprowadzono ustawienie, czy �apie si� w zakresie i warunkach
	{
		cout << "Opcja szybko�� g�osu odczytu przyjmuje warto�ci w przedziale [1;5]" << endl; //Poinformowanie u�ytkownika o problemie
		cout << "Ustawiam domy�lne ustawienie" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje zmienone na domy�lne
		Ustawienia.g�os_szybko��_odczytu_numeru = (4 >> 0); //Ustawienie warto�ci domy�lnej
	}
	if (Ustawienia.efekty_d�wi�kowe && !Ustawienia.stan_d�wi�k�w) //Sprawdzenie czy prawid�owo wprowadzono ustawienie, czy �apie si� w zakresie i warunkach
	{
		cout << "Nie mo�esz mie� wy��czonych d�wi�k�w i w��czonych efekt�w d�wi�kowych" << endl; //Poinformowanie u�ytkownika o problemie
		cout << "Ustawiam domy�lne ustawienie" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje zmienone na domy�lne
		Ustawienia.stan_d�wi�k�w = true; //Ustawienie warto�ci domy�lnej
	}
	if (Ustawienia.g�os_odczytu_numeru > 0 && !Ustawienia.stan_d�wi�k�w) //Sprawdzenie czy prawid�owo wprowadzono ustawienie, czy �apie si� w zakresie i warunkach
	{
		cout << "Nie mo�esz mie� wy��czonych d�wi�k�w i w��czon� mow�" << endl; //Poinformowanie u�ytkownika o problemie
		cout << "Ustawiam domy�lne ustawienie" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje zmienone na domy�lne
		Ustawienia.stan_d�wi�k�w = true; //Ustawienie warto�ci domy�lnej
	}
}

void Og�o�_Wynik(const int & wygrana, const int & kwota_zak�adu, int & ilo��_pieni�dzy, ofstream & log_og�lny, fstream & log)
{
	if (wygrana >= kwota_zak�adu) //Je�eli wygrana jest wi�ksza lub r�wna kwocie zak�adu to znaczy, �e si� wygra�o zak�ad
	{
		ilo��_pieni�dzy += wygrana; //Dopisanie do salda kwoty wygranej z zak�adu
		if (Ustawienia.styl_liczenia_wygranej) ilo��_pieni�dzy += kwota_zak�adu; //Dopisanie do salda kwoty zak�adu
		log << " Wygrywasz " << wygrana << "$"; //Zapisanie do bufora pliku logu aktualnego informacji o kwocie wygranej zak�adu
		log << " Posiadasz " << ilo��_pieni�dzy << "$" << '\n'; //Zapisanie do bufora pliku logu aktualnego informacji o saldzie konta u�ytkownika
		log_og�lny << " Wygrywasz " << wygrana << "$"; //Zapisanie do bufora pliku logu og�lnego informacji o kwocie wygranej zak�adu
		log_og�lny << " Posiadasz " << ilo��_pieni�dzy << "$" << '\n'; //Zapisanie do bufora pliku logu og�lnego informacji o saldzie konta u�ytkownika
		log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
		log_og�lny.flush(); //Zapisanie do pliku log_og�lny.txt danych wpisanych do bufora danych
		if (Ustawienia.stan_d�wi�k�w) //Je�eli stan_d�wi�k�w == 1
		{
			if (G�osyKompletne) PlaySound((G�os + "win.wav").c_str(), nullptr, SND_SYNC); //Je�eli s� wszystkie pliki g�os�w to odtworzenie efektu wygrania zak�adu
			else //W przeciwym wypadku
			{
				short i = 2; //Zmienna steruj�ca p�tl�
				while (i--) //P�tla kt�ra wykona si� 2 razy
				{
					cout << '\a'; //Wywo�anie pikni�cia w g�o�niku
					Sleep(Ustawienia.czas_przerwy_dzwi�ku); //Przerwa przed kolejnym pikni�ciem
				}
				cout << '\a'; //Wywo�anie pikni�cia w g�o�niku
			}
		}
	}
	else if (wygrana == (kwota_zak�adu >> 1)) //Je�eli wygrana jest r�wna po�owie kwocie zak�adu to znaczy, �e dostaje si� zwrot po�owy kwoty zak�adu
	{
		ilo��_pieni�dzy += wygrana; //Dopisanie do salda kwoty zwrotu z zak�adu
		log << " Dostajesz polowe zak�adu " << wygrana << "$"; //Zapisanie do bufora pliku logu aktualnego informacji o kwocie zwrotu zak�adu
		log << " Posiadasz " << ilo��_pieni�dzy << "$" << '\n'; //Zapisanie do bufora pliku logu aktualnego informacji o saldzie konta u�ytkownika
		log_og�lny << " Dostajesz polowe zak�adu " << wygrana << "$"; //Zapisanie do bufora pliku logu og�lnego informacji o kwocie zwrotu zak�adu
		log_og�lny << " Posiadasz " << ilo��_pieni�dzy << "$" << '\n'; //Zapisanie do bufora pliku logu og�lnego informacji o saldzie konta u�ytkownika
		log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
		log_og�lny.flush(); //Zapisanie do pliku log_og�lny.txt danych wpisanych do bufora danych
		if (Ustawienia.stan_d�wi�k�w) //Je�eli stan_d�wi�k�w == 1
			if (!G�osyKompletne) //Je�eli nie ma wszystkich plik�w g�os�w to
			{
				cout << '\a'; //Wywo�anie pikni�cia w g�o�niku
				Sleep(Ustawienia.czas_przerwy_dzwi�ku); //Przerwa przed kolejnym pikni�ciem
				cout << '\a'; //Wywo�anie pikni�cia w g�o�niku
			}
	}
	else if (wygrana == 0) //Je�eli wygrana jest r�wna 0 to znaczy, �e si� zak�ad przegra�o
	{
		log << " Przegrales " << kwota_zak�adu << "$"; //Zapisanie do bufora pliku logu aktualnego informacji o przegranej kwocie
		log << " Posiadasz " << ilo��_pieni�dzy << "$" << '\n'; //Zapisanie do bufora pliku logu aktualnego informacji o saldzie konta u�ytkownika
		log_og�lny << " Przegrales " << kwota_zak�adu << "$"; //Zapisanie do bufora pliku logu og�lnego informacji o przegranej kwocie
		log_og�lny << " Posiadasz " << ilo��_pieni�dzy << "$" << '\n'; //Zapisanie do bufora pliku logu aktualnego informacji o saldzie konta u�ytkownika
		log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
		log_og�lny.flush(); //Zapisanie do pliku log_og�lny.txt danych wpisanych do bufora danych
		if (Ustawienia.stan_d�wi�k�w) //Je�eli w��czono d�wi�ki
			if (!G�osyKompletne) cout << '\a';  //Je�eli nie ma wszystkich plik�w g�os�w to wywo�anie pikni�cia w g�o�niku
	}
}

void Koniec_Gry(ofstream & log_og�lny, fstream & log, const int & ilo��_pieni�dzy)
{
	cout << endl << "Ko�czysz gr� z wynikiem " << ilo��_pieni�dzy << "$" << endl; //Poinformowanie u�ytkownika o saldzie konta
	log << '\n' << "Ko�czysz gr� z wynikiem " << ilo��_pieni�dzy << "$" << '\n'; //Zapisanie do bufora pliku logu aktualnego informacji o saldzie konta u�ytkownika
	log_og�lny << "Ko�czysz gr� z wynikiem " << ilo��_pieni�dzy << "$" << '\n'; //Zapisanie do bufora pliku logu og�lnego informacji o saldzie konta u�ytkownika
	log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
	log_og�lny.flush(); //Zapisanie do pliku log_og�lny.txt danych wpisanych do bufora danych
	log.close(); //Zamkni�cie pliku log aktualny
	remove("log_aktualny.txt"); //Usuni�cie pliku log aktualny poniewa� sko�czy�o si� gr�

	if (Ustawienia.stan_d�wi�k�w == 1) //Je�eli stan_d�wi�k�w == 1
		if (ilo��_pieni�dzy == 0) //Je�eli bud�et jest r�wny 0 to
			if (EfektyKompletne) PlaySound("Efekty_d�wi�kowe/bankrut.wav", nullptr, SND_ASYNC); //Je�eli pliki efekt�w s� dost�pne, odtworzenie efektu bankruta
			else //W przeciwym wypadku
				for (auto i = 0; i < 5; ++i) //Rozpocz�cie p�tli kt�ra wykona 5 obrot�w
				{
					cout << '\a'; //Wywo�anie pikni�cia w g�o�niku
					Sleep(Ustawienia.czas_przerwy_dzwi�ku); //Przerwa przed kolejnym pikni�ciem //Przerwa przed kolejnym pikni�ciem
				}

	if (ilo��_pieni�dzy > Ustawienia.kwota_pocz�tkowa && ilo��_pieni�dzy < (Ustawienia.kwota_pocz�tkowa << 1)) //Sprawdzenie czy zwi�kszy�o si� bud�et
	{
		cout << "Gratuluje zwi�kszy�e� sw�j zas�b finansowy" << endl; //Wy�wietlenie gratulacji z powodu zwi�kszenia bud�etu
		if (EfektyKompletne) //Je�eli pliki efekt�w s� dost�pne
			if (rand() & 1) PlaySound("Efekty_d�wi�kowe/wygrana1.wav", nullptr, SND_ASYNC); //Wylosowanie numeru otworzonego efektu, odtworzenie je�eli wylosowano efekt 0
			else PlaySound("Efekty_d�wi�kowe/wygrana2.wav", nullptr, SND_ASYNC); //Odtworzenie je�eli wylosowano efekt 1
	}
	else if (ilo��_pieni�dzy >= (Ustawienia.kwota_pocz�tkowa << 1)) //Sprawdzenie czy zwielokrotniono przynajmniej 2 razy bud�et
	{
		cout << "Gratuluje zwi�kszy�e� " << ilo��_pieni�dzy / Ustawienia.kwota_pocz�tkowa << "-krotnie sw�j zas�b finansowy" << endl; //Wy�wietlenie gratulacji z powodu zwielokrotnienia przynajmniej 2 razy bud�etu
		if (EfektyKompletne) PlaySound("Efekty_d�wi�kowe/zwielokrotnenie.wav", nullptr, SND_ASYNC); //Odtworzenie efektu d�wi�kowego wzamian za zwielokrotnienie bud�etu, je�eli pliki efekt�w s� dost�pne
	}
}

void P�tla_G��wna(int & wygrana, int & kwota_zak�adu, int & ilo��_pieni�dzy, ofstream & log_og�lny, fstream & log, const char & co_kontynuowa�, string & typ_zak�adu, int & wylosowana_liczba)
{
	if (co_kontynuowa� == 'n') //Je�eli punkt kontynuowania jest odpowiedni to
	{
		Wczytaj_Kwot�_Zak�adu(kwota_zak�adu, ilo��_pieni�dzy); //Przypisanie do zmiennej pobranej od u�ytkownika kwoty zak�adu
		log << "Obstawiono za " << kwota_zak�adu << "$"; //Zapisanie do bufora pliku logu aktualnego informacji o kwocie obstawionego zak�adu
		log_og�lny << "Obstawiono za " << kwota_zak�adu << "$"; //Zapisanie do bufora pliku logu og�lnego informacji o kwocie obstawionego zak�adu
		log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
		log_og�lny.flush(); //Zapisanie do pliku log_og�lny.txt danych wpisanych do bufora danych
	}
	else //W przeciwym wypadku
	{
		cout << "Masz " << ilo��_pieni�dzy << "$" << endl; //Wypisanie wczytanej informacji o posiadanej ilo�ci pieni�dzy
		cout << "Obstawiono za " << kwota_zak�adu << "$" << endl; //Wypisanie wczytanej kwoty zak�adu
	}
	if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k') //Je�eli punkt kontynuowania jest odpowiedni to
	{
		typ_zak�adu = Obstaw(); //Przypisanie do zmiennej pobranej od u�ytkownika typu zak�adu
		log << " Obstawiono zaklad " << typ_zak�adu; //Zapisanie do bufora pliku logu aktualnego informacji o typie obstawionego zak�adu
		log_og�lny << " Obstawiono zaklad " << typ_zak�adu; //Zapisanie do bufora pliku logu og�lnego informacji o typie obstawionego zak�adu
		log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
		log_og�lny.flush(); //Zapisanie do pliku log_og�lny.txt danych wpisanych do bufora danych
	}
	else cout << "Obstawiono zak�ad " << typ_zak�adu << endl; //Wypisanie wczytanego typu zak�adu
	if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k' || co_kontynuowa� == 't' || co_kontynuowa� == 'w') ilo��_pieni�dzy -= kwota_zak�adu;  //Je�eli punkt kontynuowania jest odpowiedni to odj�cie od ilo�ci pieni�dzy kwoty zak�adu
	if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k' || co_kontynuowa� == 't') //Je�eli punkt kontynuowania jest odpowiedni to
	{
		cout << "Kulka w grze, zaczekaj na wylosowanie numeru..." << endl; //Poinformowanie u�ytkownika o rozpocz�ciu losowania
		wylosowana_liczba = Zakr��_Ruletk�(); //Wylosowanie i przypisanie do zmiennej liczby b�d�cej na  wylosowanej pozycji na kole ruletki
	}
	else //W przeciwym wypadku
	{
		cout << "Wylosowano numer "; //Poinformowaniu o wylosowaniu liczby
		Change_Col(Ruletka_plansza_kolor_col[(size_t)wylosowana_liczba]); //Zmiana koloru tekstu w konsoli zgodnie z kolorem numeru na ruletce
		cout << wylosowana_liczba; //Wypisanie wylosowanej liczby
		Change_Col(7); //Powr�t do standardowego koloru tekstu w konsoli
		cout << ". "; //Wypisanie kropki ko�cz�cej zdanie
	}
	if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k' || co_kontynuowa� == 't') //Je�eli punkt kontynuowania jest odpowiedni to
	{
		log << " Wylosowano " << wylosowana_liczba; //Zapisanie do bufora pliku logu aktualnego informacji o wylosowanej liczbie
		log_og�lny << " Wylosowano " << wylosowana_liczba; //Zapisanie do bufora pliku logu og�lnego informacji o wylosowanej liczbie
		log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
		log_og�lny.flush(); //Zapisanie do pliku log_og�lny.txt danych wpisanych do bufora danych
		Odczytaj_Liczb�(wylosowana_liczba, typ_zak�adu);
	}
	if (co_kontynuowa� == 'n' || co_kontynuowa� == 'k' || co_kontynuowa� == 't' || co_kontynuowa� == 'w') //Je�eli punkt kontynuowania jest odpowiedni to
	{
		wygrana = Sprawd�_Zak�ad(kwota_zak�adu, typ_zak�adu, wylosowana_liczba); //Przypisanie do wygranej kwoty zgodnej z wygran�, je�eli si� co�wygra�o
		Og�o�_Wynik(wygrana, kwota_zak�adu, ilo��_pieni�dzy, log_og�lny, log); //Funkcja informuj�ca u�ytkownika czy wygra� zak�ad
	}
}
void Ustaw_Ustawienia(string & tekst)
{
	if (tekst.find("ilo��_min_dodatkowych_obrot�w_ruletki") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("ilo��_min_dodatkowych_obrot�w_ruletki")); //Usuni�cie s�owa z tekst aby zosta�a tylko liczba kt�ra jest warto�ci� ustawienia

		try {//Pr�ba
			Ustawienia.ilo��_min_dodatkowych_obrot�w_ruletki = stos(tekst);  //Przypisaninie warto�ci odczytanej z tekstu
		}
		catch (invalid_argument&) { //Je�eli zostanie z�apany wyj�tek "nieprawid�owy argument"
			cout << "Ustawiam domy�lne ustawienie ilo��_minimalna_obrot�w_ruletki" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje pozostawione przy domy�lnych
		}
		catch (out_of_range&) { //Je�eli zostanie z�apany wyj�tek "zbyt du�y argument"
			cout << "Ustawiam domy�lne ustawienie ilo��_minimalna_obrot�w_ruletki" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje pozostawione przy domy�lnych
		}
	}
	else if (tekst.find("ilo��_max_dodatkowych_obrot�w_ruletki") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("ilo��_max_dodatkowych_obrot�w_ruletki")); //Usuni�cie s�owa z tekst aby zosta�a tylko liczba kt�ra jest warto�ci� ustawienia

		try {//Pr�ba
			Ustawienia.ilo��_max_dodatkowych_obrot�w_ruletki = stos(tekst);  //Przypisaninie warto�ci odczytanej z tekstu
		}
		catch (invalid_argument&) { //Je�eli zostanie z�apany wyj�tek "nieprawid�owy argument"
			cout << "Ustawiam domy�lne ustawienie ilo��_max_dodatkowych_obrot�w_ruletki" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje pozostawione przy domy�lnych
		}
		catch (out_of_range&) { //Je�eli zostanie z�apany wyj�tek "zbyt du�y argument"
			cout << "Ustawiam domy�lne ustawienie ilo��_max_dodatkowych_obrot�w_ruletki" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje pozostawione przy domy�lnych
		}
	}
	else if (tekst.find("czas_przeskoku_kulki_szybki") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("czas_przeskoku_kulki_szybki")); //Usuni�cie s�owa z tekst aby zosta�a tylko liczba kt�ra jest warto�ci� ustawienia

		try {//Pr�ba
			Ustawienia.czas_przeskoku_kulki_szybki = stos(tekst);  //Przypisaninie warto�ci odczytanej z tekstu
		}
		catch (invalid_argument&) { //Je�eli zostanie z�apany wyj�tek "nieprawid�owy argument"
			cout << "Ustawiam domy�lne ustawienie czas_przeskoku_kulki_szybki" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje pozostawione przy domy�lnych
		}
		catch (out_of_range&) { //Je�eli zostanie z�apany wyj�tek "zbyt du�y argument"
			cout << "Ustawiam domy�lne ustawienie czas_przeskoku_kulki_szybki" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje pozostawione przy domy�lnych
		}
	}
	else if (tekst.find("czas_przeskoku_kulki_wolny") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("czas_przeskoku_kulki_wolny")); //Usuni�cie s�owa z tekst aby zosta�a tylko liczba kt�ra jest warto�ci� ustawienia

		try {//Pr�ba
			Ustawienia.czas_przeskoku_kulki_wolny = stos(tekst);  //Przypisaninie warto�ci odczytanej z tekstu
		}
		catch (invalid_argument&) { //Je�eli zostanie z�apany wyj�tek "nieprawid�owy argument"
			cout << "Ustawiam domy�lne ustawienie czas_przeskoku_kulki_wolny" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje pozostawione przy domy�lnych
		}
		catch (out_of_range&) { //Je�eli zostanie z�apany wyj�tek "zbyt du�y argument"
			cout << "Ustawiam domy�lne ustawienie czas_przeskoku_kulki_wolny" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje pozostawione przy domy�lnych
		}
	}
	else if (tekst.find("styl_liczenia_wygranej") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("styl_liczenia_wygranej")); //Usuni�cie s�owa z tekst aby zosta�a tylko liczba kt�ra jest warto�ci� ustawienia

		try {//Pr�ba
			Ustawienia.styl_liczenia_wygranej = StringtoBool(tekst);  //Przypisaninie warto�ci odczytanej z tekstu
		}
		catch (invalid_argument&) { //Je�eli zostanie z�apany wyj�tek "nieprawid�owy argument"
			cout << "Ustawiam domy�lne ustawienie styl_liczenia_wygranej" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje pozostawione przy domy�lnych
		}
	}
	else if (tekst.find("kwota_pocz�tkowa") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("kwota_pocz�tkowa")); //Usuni�cie s�owa z tekst aby zosta�a tylko liczba kt�ra jest warto�ci� ustawienia

		try {//Pr�ba
			Ustawienia.kwota_pocz�tkowa = stoi(tekst);  //Przypisaninie warto�ci odczytanej z tekstu
		}
		catch (invalid_argument&) { //Je�eli zostanie z�apany wyj�tek "nieprawid�owy argument"
			cout << "Ustawiam domy�lne ustawienie kwota_pocz�tkowa" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje pozostawione przy domy�lnych
		}
		catch (out_of_range&) { //Je�eli zostanie z�apany wyj�tek "zbyt du�y argument"
			cout << "Ustawiam domy�lne ustawienie kwota_pocz�tkowa" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje pozostawione przy domy�lnych
		}
	}
	else if (tekst.find("stan_d�wi�k�w") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("stan_d�wi�k�w")); //Usuni�cie s�owa z tekst aby zosta�a tylko liczba kt�ra jest warto�ci� ustawienia

		try {//Pr�ba
			Ustawienia.stan_d�wi�k�w = StringtoBool(tekst);  //Przypisaninie warto�ci odczytanej z tekstu
		}
		catch (invalid_argument&) { //Je�eli zostanie z�apany wyj�tek "nieprawid�owy argument"
			cout << "Ustawiam domy�lne ustawienie stan_d�wi�k�w" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje pozostawione przy domy�lnych
		}
	}
	else if (tekst.find("czy_kontynuowa�_gr�") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("czy_kontynuowa�_gr�")); //Usuni�cie s�owa z tekst aby zosta�a tylko liczba kt�ra jest warto�ci� ustawienia

		try {//Pr�ba
			Ustawienia.czy_kontynuowa�_gr� = StringtoBool(tekst);  //Przypisaninie warto�ci odczytanej z tekstu
		}
		catch (invalid_argument&) { //Je�eli zostanie z�apany wyj�tek "nieprawid�owy argument"
			cout << "Ustawiam domy�lne ustawienie czy_kontynuowa�_gr�" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje pozostawione przy domy�lnych
		}
	}
	else if (tekst.find("g�os_odczytu_numeru") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("g�os_odczytu_numeru")); //Usuni�cie s�owa z tekst aby zosta�a tylko liczba kt�ra jest warto�ci� ustawienia

		try {//Pr�ba
			Ustawienia.g�os_odczytu_numeru = stos(tekst);  //Przypisaninie warto�ci odczytanej z tekstu
		}
		catch (invalid_argument&) { //Je�eli zostanie z�apany wyj�tek "nieprawid�owy argument"
			cout << "Ustawiam domy�lne ustawienie g�os_odczytu_numeru" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje pozostawione przy domy�lnych
		}
		catch (out_of_range&) { //Je�eli zostanie z�apany wyj�tek "zbyt du�y argument"
			cout << "Ustawiam domy�lne ustawienie g�os_odczytu_numeru" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje pozostawione przy domy�lnych
		}
	}
	else if (tekst.find("g�os_szybko��_odczytu_numeru") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("g�os_szybko��_odczytu_numeru")); //Usuni�cie s�owa z tekst aby zosta�a tylko liczba kt�ra jest warto�ci� ustawienia

		try {//Pr�ba
			Ustawienia.g�os_szybko��_odczytu_numeru = stos(tekst);  //Przypisaninie warto�ci odczytanej z tekstu
		}
		catch (invalid_argument&) { //Je�eli zostanie z�apany wyj�tek "nieprawid�owy argument"
			cout << "Ustawiam domy�lne ustawienie g�os_szybko��_odczytu_numeru" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje pozostawione przy domy�lnych
		}
		catch (out_of_range&) { //Je�eli zostanie z�apany wyj�tek "zbyt du�y argument"
			cout << "Ustawiam domy�lne ustawienie g�os_szybko��_odczytu_numeru" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje pozostawione przy domy�lnych
		}
	}
	else if (tekst.find("efekty_d�wi�kowe") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("efekty_d�wi�kowe")); //Usuni�cie s�owa z tekst aby zosta�a tylko liczba kt�ra jest warto�ci� ustawienia

		try {//Pr�ba
			Ustawienia.efekty_d�wi�kowe = StringtoBool(tekst);  //Przypisaninie warto�ci odczytanej z tekstu
		}
		catch (invalid_argument&) { //Je�eli zostanie z�apany wyj�tek "nieprawid�owy argument"
			cout << "Ustawiam domy�lne ustawienie efekty_d�wi�kowe" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje pozostawione przy domy�lnych
		}
	}
	else if (tekst.find("metoda_liczenia_wygranej_zerowej") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("metoda_liczenia_wygranej_zerowej")); //Usuni�cie s�owa z tekst aby zosta�a tylko liczba kt�ra jest warto�ci� ustawienia

		try {//Pr�ba
			Ustawienia.metoda_liczenia_wygranej_zerowej = StringtoBool(tekst);  //Przypisaninie warto�ci odczytanej z tekstu
		}
		catch (invalid_argument&) { //Je�eli zostanie z�apany wyj�tek "nieprawid�owy argument"
			cout << "Ustawiam domy�lne ustawienie metoda_liczenia_wygranej_zerowej" << endl; //Poinformowanie u�ytkownika, �e bie��ce ustawienie zostaje pozostawione przy domy�lnych
		}
	}
}

void Inicjacje_Pocz�tkowe()
{
	//Inicjowanie ustawie� programu
	WNDCLASSEX wincl; //Utworzenie typu do zmiany w�a�ciwo�ci programu
	wincl.hIcon = LoadIcon(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_ICON1)); //Przypisanie ikony programu
	wincl.hIconSm = LoadIcon(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_ICON1));//Przypisanie ma�ej ikony programu

	//Inicjowanie funkcji
	setlocale(LC_ALL, "polish"); // W celu polskich liter w konsoli
	srand((unsigned)time(nullptr)); //Zainicjowanie generatorza LCG (Liniowy Generator Kongruentny) dla ma�o wa�nych liczb
	Show_Cursor(); //Pokazanie kursora tekstowego w konsoli
}

bool Wyci�gnij_z_Programu(const string & �cie�ka, const unsigned short & numer_zasobu)
{
	const HRSRC hPlik = FindResource(GetModuleHandle(nullptr), MAKEINTRESOURCE(numer_zasobu), RT_RCDATA); //Tworz� uchwyt do pliku znajduj�cego si� w plikach zasob�w
	if (hPlik != nullptr) //Je�eli uchyt nie jest pusty (Znalaz�o zas�b)
	{
		const auto pPlik = LoadResource(GetModuleHandle(nullptr), hPlik); //Przypisuj� uchwytowi miejsce �r�d�owe pliku
		const auto dwDlugosc = SizeofResource(GetModuleHandle(nullptr), hPlik); //Przypisuj� zmiennej wielko�� pliku
		const auto hPlik = CreateFile(�cie�ka.c_str(), GENERIC_WRITE, NULL, nullptr, CREATE_NEW, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, nullptr); //Tworz� plik
		DWORD dwBajtyZapisane; //Tworz� i inicjuj� zmiennn� informuj�c� o ilo��i zapisanych danych
		if (!WriteFile(hPlik, pPlik, dwDlugosc, &dwBajtyZapisane, nullptr)) return false; //Je�eli zapis do pliku si� nie uda� zwr�� fa�sz
		if (dwBajtyZapisane != dwDlugosc) return false; //Je�eli ilo�� zapisanych danych jest inna ni� ilo�� danych do zapisania zwr�� fa�sz
		CloseHandle(hPlik); //Zamykam uchwyt do pliku �r�d�owego
		return true; //Zwracam, �e zapis si� uda�
	}
	return false; //W przeciwym wypadku zwracam fa�sz
}

void Wypakuj_Rar(const string & nazwa_folderu)
{
	if ((_access("Rar.exe", NULL))) Wyci�gnij_z_Programu("Rar.exe", IDR_RAR);  //Sprawdzenie czy plik nie istnieje je�eli nie istnieje to wyci�gam z pami�ci
	if ((_access(nazwa_folderu.substr(0, nazwa_folderu.size() - (4 << 0)).c_str(), NULL))) system(("Rar.exe x " + nazwa_folderu + " -o+ -idq").c_str()); //Wydaj� polecenie rozpakowania archiwum rar je�eli wcze�niej niewypakowano
}

bool Przenie�_Plik(const string & z_pliku, const string & do_pliku)
{
	return MoveFile(z_pliku.c_str(), do_pliku.c_str()); //Zwracam wynik przenoszenia pliku
}

void Usu�_Folder_Wypakowany_i_Winrar(const string & G�os)
{
	DeleteFile((G�os + "p.wav").c_str()); //Usuwam plik p.wav

	DeleteFile((G�os + "n.wav").c_str()); //Usuwam plik n.wav

	DeleteFile((G�os + "r.wav").c_str()); //Usuwam plik r.wav

	DeleteFile((G�os + "b.wav").c_str()); //Usuwam plik b.wav

	DeleteFile((G�os + "g.wav").c_str()); //Usuwam plik g.wav

	DeleteFile((G�os + "d.wav").c_str()); //Usuwam plik d.wav

	DeleteFile((G�os + "win.wav").c_str()); //Usuwam plik win.wav

	for (auto i = 1; i <= 3; ++i) //P�tla licz�ca od 1 do 3
		DeleteFile((G�os + 'k' + char('0' + i) + ".wav").c_str()); //Usuwam plik k z odpowienim indeksem

	auto const numers = new char[3]; //Utworzenie tablicy do przechowywania zamienionej liczby na tekst

	for (auto i = 1; i <= 12; ++i) //P�tla licz�ca od 1 do 12
	{
		_snprintf_s(numers, 3, 3, "%d", i); //Wpisanie do tablicy warto�ci z obrotu p�tli
		DeleteFile((G�os + 'w' + numers + ".wav").c_str());  //Usuwam plik w z odpowienim indeksem
	}

	for (auto i = 0; i <= 36; ++i) //P�tla licz�ca od 0 do 36
	{
		sprintf_s(numers, 3, "%d", i); //Wpisanie do tablicy warto�ci z obrotu p�tli
		DeleteFile((G�os + numers + ".wav").c_str()); //Usuwam plik o numerze indeku
	}

	delete[] numers; //Usuni�cie tablicy dynamicznej do przechowywania zamienionej liczby na tekst

	const string g�os2 = G�os.substr(0, G�os.size() - 1); //Tworz� zmienn� string do kt�rej wk�adam skr�cony o ostatni znak string G�os

	RemoveDirectory(g�os2.c_str()); //Usuwam folder

	DeleteFile((g�os2 + ".rar").c_str()); //Sprawdzenie czy plik nie istnieje

	DeleteFile("Rar.exe"); //Usuwam plik Rar.exe
}

bool StringtoBool(const string & var)
{
	if (var.size() == 0) //Sprawdzenie czy rozmiar stringa to 0
		; //Nic nie r�b
	else //W przeciwym wypadku
		for (size_t i = 0; i < var.size(); ++i) //Przej�cie przez ca�y string
		{
			if (isspace(var[i])) continue; //Je�eli znak jest znakiem bia�ym to kontynuuj p�tl�
			if (isalpha(var[i])) break; //W przeciwym wypadku je�eli znak jest liter� to zako�cz p�tl�
			for (size_t ii = i; ii < var.size() && !isspace(var[ii]); ++ii) //P�tla od znaku na kt�rym zatrzyma�a si� poprzednia p�tla
				if (var[ii] != '0') //Sprawdzenie czy na danej pozycji znak to nie zero
					return true; //Zwr�� prawd�
			return false; //Zwr�� fa�sz
		}

	switch (var.size()) //Switch z zmienn� steruj�c� rozmiar s�owa do zamiany
	{
	case 1: //Sprawdzenie czy liczba znak�w jest r�wna 1
	{
		if (var[0] == 'T' || var[0] == 't') //Sprawdzenie czy na danej pozycji jest litera t niezale�nie od wielko�ci
			return true; //Zwr�� prawd�
		if (var[0] == 'N' || var[0] == 'n' || var[0] == 'F' || var[0] == 'f')  //Sprawdzenie czy na danej pozycji jest litera n lub f niezale�nie od wielko�ci
			return false; //Zwr�� fa�sz

		break; //Wyj�cie z casa
	}
	case 3: //Sprawdzenie czy liczba znak�w jest r�wna 3
	{
		if (var[0] == 'T' || var[0] == 't') //Sprawdzenie czy na danej pozycji jest litera t niezale�nie od wielko�ci
			if (var[1] == 'A' || var[1] == 'a') //Sprawdzenie czy na danej pozycji jest litera a niezale�nie od wielko�ci
				if (var[2] == 'K' || var[2] == 'k') //Sprawdzenie czy na danej pozycji jest litera k niezale�nie od wielko�ci
					return true; //Zwr�� prawd�
				else; //Nic nie r�b
			else; //Nic nie r�b
		else if (var[0] == 'N' || var[0] == 'n') //Sprawdzenie czy na danej pozycji jest litera n niezale�nie od wielko�ci
			if (var[1] == 'I' || var[1] == 'i') //Sprawdzenie czy na danej pozycji jest litera i niezale�nie od wielko�ci
				if (var[2] == 'E' || var[2] == 'e') //Sprawdzenie czy na danej pozycji jest litera e niezale�nie od wielko�ci
					return false; //Zwr�� fa�sz
				else; //Nic nie r�b
			else; //Nic nie r�b
		else; //Nic nie r�b

		break; //Wyj�cie z casa
	}

	case 4: //Sprawdzenie czy liczba znak�w jest r�wna 4
	{
		if (var[0] == 'T' || var[0] == 't') //Sprawdzenie czy na danej pozycji jest litera t niezale�nie od wielko�ci
			if (var[1] == 'R' || var[1] == 'r') //Sprawdzenie czy na danej pozycji jest litera r niezale�nie od wielko�ci
				if (var[2] == 'U' || var[2] == 'u') //Sprawdzenie czy na danej pozycji jest litera u niezale�nie od wielko�ci
					if (var[3] == 'E' || var[3] == 'e') //Sprawdzenie czy na danej pozycji jest litera e niezale�nie od wielko�ci
						return true; //Zwr�� prawd�
					else; //Nic nie r�b
				else; //Nic nie r�b
			else; //Nic nie r�b
		else; //Nic nie r�b

		break; //Wyj�cie z casa
	}

	case 5: //Sprawdzenie czy liczba znak�w jest r�wna 5
	{
		if (var[0] == 'F' || var[0] == 'f') //Sprawdzenie czy na danej pozycji jest litera f niezale�nie od wielko�ci
			if (var[1] == 'A' || var[1] == 'a') //Sprawdzenie czy na danej pozycji jest litera a niezale�nie od wielko�ci
				if (var[2] == 'L' || var[2] == 'l') //Sprawdzenie czy na danej pozycji jest litera l niezale�nie od wielko�ci
					if (var[3] == 'S' || var[3] == 's') //Sprawdzenie czy na danej pozycji jest litera s niezale�nie od wielko�ci
						if (var[4] == 'E' || var[4] == 'e') //Sprawdzenie czy na danej pozycji jest litera e niezale�nie od wielko�ci
							return false; //Zwr�� fa�sz
						else; //Nic nie r�b
					else; //Nic nie r�b
				else if (var[2] == '�' || var[2] == '�') //Sprawdzenie czy na danej pozycji jest litera � niezale�nie od wielko�ci
					if (var[3] == 'S' || var[3] == 's') //Sprawdzenie czy na danej pozycji jest litera s niezale�nie od wielko�ci
						if (var[4] == 'Z' || var[4] == 'z') //Sprawdzenie czy na danej pozycji jest litera z niezale�nie od wielko�ci
							return false; //Zwr�� fa�sz
						else; //Nic nie r�b
					else; //Nic nie r�b
				else; //Nic nie r�b
			else; //Nic nie r�b

			break; //Wyj�cie z casa
	}

	case 6: //Sprawdzenie czy liczba znak�w jest r�wna 6
	{
		if (var[0] == 'P' || var[0] == 'p') //Sprawdzenie czy na danej pozycji jest litera p niezale�nie od wielko�ci
			if (var[1] == 'R' || var[1] == 'r') //Sprawdzenie czy na danej pozycji jest litera r niezale�nie od wielko�ci
				if (var[2] == 'A' || var[2] == 'a') //Sprawdzenie czy na danej pozycji jest litera a niezale�nie od wielko�ci
					if (var[3] == 'W' || var[3] == 'w') //Sprawdzenie czy na danej pozycji jest litera w niezale�nie od wielko�ci
						if (var[4] == 'D' || var[4] == 'd') //Sprawdzenie czy na danej pozycji jest litera d niezale�nie od wielko�ci
							if (var[5] == 'A' || var[5] == 'a') //Sprawdzenie czy na danej pozycji jest litera a niezale�nie od wielko�ci
								return true; //Zwr�� prawd�
							else; //Nic nie r�b
						else; //Nic nie r�b
					else; //Nic nie r�b
				else; //Nic nie r�b
			else; //Nic nie r�b
		else; //Nic nie r�b

		break; //Wyj�cie z casa
	}

	case 9: //Sprawdzenie czy liczba znak�w jest r�wna 6
	{
		if (var[0] == 'N' || var[0] == 'n') //Sprawdzenie czy na danej pozycji jest litera n niezale�nie od wielko�ci
			if (var[1] == 'I' || var[1] == 'i') //Sprawdzenie czy na danej pozycji jest litera i niezale�nie od wielko�ci
				if (var[2] == 'E' || var[2] == 'e') //Sprawdzenie czy na danej pozycji jest litera e niezale�nie od wielko�ci
					if (var[3] == 'P' || var[3] == 'p') //Sprawdzenie czy na danej pozycji jest litera p niezale�nie od wielko�ci
						if (var[4] == 'R' || var[4] == 'r') //Sprawdzenie czy na danej pozycji jest litera r niezale�nie od wielko�ci
							if (var[5] == 'A' || var[5] == 'a') //Sprawdzenie czy na danej pozycji jest litera a niezale�nie od wielko�ci
								if (var[6] == 'W' || var[6] == 'w') //Sprawdzenie czy na danej pozycji jest litera w niezale�nie od wielko�ci
									if (var[7] == 'D' || var[7] == 'd') //Sprawdzenie czy na danej pozycji jest litera d niezale�nie od wielko�ci
										if (var[8] == 'A' || var[8] == 'a') //Sprawdzenie czy na danej pozycji jest litera a niezale�nie od wielko�ci
											return false; //Zwr�� fa�sz
										else; //Nic nie r�b
									else; //Nic nie r�b
								else; //Nic nie r�b
							else; //Nic nie r�b
						else; //Nic nie r�b
					else; //Nic nie r�b
				else; //Nic nie r�b
			else; //Nic nie r�b
		else; //Nic nie r�b

		break; //Wyj�cie z casa
	}

	case 10: //Sprawdzenie czy liczba znak�w jest r�wna 6
	{
		if (var[0] == 'N' || var[0] == 'n') //Sprawdzenie czy na danej pozycji jest litera n niezale�nie od wielko�ci
			if (var[1] == 'I' || var[1] == 'i') //Sprawdzenie czy na danej pozycji jest litera i niezale�nie od wielko�ci
				if (var[2] == 'E' || var[2] == 'e') //Sprawdzenie czy na danej pozycji jest litera e niezale�nie od wielko�ci
					if (var[3] == ' ') //Sprawdzenie czy na danej pozycji jest spacja
						if (var[4] == 'P' || var[4] == 'p') //Sprawdzenie czy na danej pozycji jest litera p niezale�nie od wielko�ci
							if (var[5] == 'R' || var[5] == 'r') //Sprawdzenie czy na danej pozycji jest litera r niezale�nie od wielko�ci
								if (var[6] == 'A' || var[6] == 'a') //Sprawdzenie czy na danej pozycji jest litera a niezale�nie od wielko�ci
									if (var[7] == 'W' || var[7] == 'w') //Sprawdzenie czy na danej pozycji jest litera w niezale�nie od wielko�ci
										if (var[8] == 'D' || var[8] == 'd') //Sprawdzenie czy na danej pozycji jest litera d niezale�nie od wielko�ci
											if (var[9] == 'A' || var[9] == 'a') //Sprawdzenie czy na danej pozycji jest litera a niezale�nie od wielko�ci
												return false; //Zwr�� fa�sz
											else; //Nic nie r�b
										else; //Nic nie r�b
									else; //Nic nie r�b
								else; //Nic nie r�b
							else; //Nic nie r�b
						else; //Nic nie r�b
					else; //Nic nie r�b
				else; //Nic nie r�b
			else; //Nic nie r�b

			break; //Wyj�cie z casa
	}

	default: //Je�li �aden warunek co do liczby liter nie jest odpowiedni
		; //Nic nie r�b
	}

	throw invalid_argument("bad string"); //Rzu� wyj�tek nieprawid�owy argument
}

//Przerobiona wersja stoi na sto(short)
inline short stos(const string& _Str, size_t *_Idx,
	int _Base)
{	// convert string to short
	int& _Errno_ref = errno;	// Nonzero cost, pay it once
	const char *_Ptr = _Str.c_str();
	char *_Eptr;
	_Errno_ref = 0;
	long _Ans = _CSTD strtol(_Ptr, &_Eptr, _Base);

	if (_Ptr == _Eptr)
		_Xinvalid_argument("invalid stos argument");
	if (_Errno_ref == ERANGE || _Ans < SHRT_MIN || SHRT_MAX < _Ans)
		_Xout_of_range("stos argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return ((short)_Ans);
}

BOOL TerminateProcess(const DWORD & dwProcessId, const UINT & uExitCode)
{
	const DWORD dwDesiredAccess = PROCESS_TERMINATE;
	const BOOL  bInheritHandle = FALSE;
	const HANDLE hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
	if (hProcess == nullptr)
		return FALSE;

	const BOOL result = TerminateProcess(hProcess, uExitCode);

	CloseHandle(hProcess);

	return result;
}

/*
Wykona� Krzysztof Truszkiewicz
Politechnika Pozna�ska
Wydzia� Elektryczny
studia niestacjonarne
Automatyka i Robotyka
Grupa 4
Projekt na zaliczenie laboratorium, studia zaoczne, Automatyka i Robotyka
Gra "Ruletka"
*/