//------------------ deklaracje bibiotek u¿ywanych w programie -----------------------
#include <array> //Kontener tablica
#include <clocale> //setlocale(), polskie znaki w konsoli
#include <chrono> //Obs³uga zegara wysokiej precyzji
#include <ctime> //time(), akualny czas w sekundach liczony od 1 stycznia 1970, 00:00:00 UTC
#include <deque> //Kontener lista dwukierunkowa (deque)
#include <fstream> //Obs³uga plików
#include <io.h> //_access(), spawdzanie czy plik istnieje
#include <iostream> //Obs³uga strumenia cout,cin
#include <map> //Kontener drzewo binarne (map)
#include <random> //random_device,distribution(), generowanie liczb losowych i lepsze generowanie licz pseudolosowych
#include <sstream> //stringstream, zamiana liczby na string
#include <stack> //Kontener stos
#include <string> //Obs³uga stringów
#include <thread> //Obs³uga w¹tków
#include <windows.h> //SYSTEMTIME,GetSystemTime(),Sleep(),GetStdHandle(),SetConsoleTextAttribute(),DeleteFile(),RemoveDirectory(), zmiana ustawieñ konsoli, pobieranie aktualnego czasu
#include <mmsystem.h> //PlaySound() (Aby dzia³a³o trzeba dodaæ winmm.lib lub coredll.lib do linkera (konsolidatora)), Odtwarzanie muzyki
#pragma comment(lib, "winmm.lib") //Dodanie winmm.lib do linkera (konsolidatora)
#include <urlmon.h> //URLDownloadToFile(), pobiranie plików (Aby dzia³a³o trzeba dodaæ urlmon.lib do linkera (konsolidatora)), pobieranie plików z internetu
#pragma comment(lib, "urlmon.lib") //Dodanie urlmon.lib do linkera (konsolidatora)
#include <vector> //Kontener vector
#include "resource.h" //Plik z zasobanie (ikony i dŸwiêki)
//-------------------------------------------------------------------------------------

//----------------- deklaracja wyboru standardowej przestrzeni nazw std ---------------
using namespace std;
//-------------------------------------------------------------------------------------

//---------------------------------- deklaracje funkcji w³asnych ----------------------
string Obstaw(); //Funkcja wczytywania typu zak³ad, do string aby mieæ tak¿e zak³ady sk³adaj¹ce siê z liter i cyfr
void Wczytaj_Kwotê_Zak³adu(int & kwota, const int & iloœæ_pieniêdzy); //Funkcja wczytywania kwoty zak³adu aby uchroniæ siê przed problemem wpisania znaku,litery zamiast liczby i osbstawienie za wiêksz¹ kwotê ni¿ siê ma
int Zakrêæ_Ruletk¹(); //Funkcja losuje liczbê z ko³a ruletki
int SprawdŸ_Zak³ad(const int & kwota, const string & typ_zak³adu, const int & wylosowana_liczba); //Funcja sprawdza czy wygraliœmy i podaje kwote wygranej/przegranej/odzysku czêœci w³o¿onych pieniêdzy
bool Czy_Kontynuowaæ(const int & iloœæ_pieniêdzy); //Funkcja sprawdzj¹ca czy ma siê œrodki do gry, je¿eli ma siê to pyta czy chce siê graæ dalej
int Wylosuj(const int & od_liczby, const int & do_liczby); //Funkcja która losuje liczby od liczby do liczby losowo lub psudolosowo metod¹ MT
void Odczytaj_Liczbê(const int & wylosowana_liczba, const string & typ_zak³adu); //Funkcja do odczytu wylosowanej liczby i jej po³o¿enia
void Wczytaj_z_Pliku(ofstream & log_ogólny, fstream & log, char & co_kontynuowaæ, int & iloœæ_pieniêdzy, int & kwota_zak³adu, int & wylosowana_liczba, string & typ_zak³adu); //Funkcja wczytuj¹ca z pliku ostatnie ruchy gracza
void SprawdŸ_Pliki(const short & g³os_odczytu_numeru, const short & g³os_szybkoœæ_odczytu_numeru); //Funkcja sprawdzaj¹ca czy wszystkie pliki dŸwiêkowe s¹ na miejscu
void SprawdŸ_Ustawienia(); //sprawdzanie poprawnoœci deklaracji definicji preprocesora do zmian funcjonowania programu
void Og³oœ_Wynik(const int & wygrana, const int & kwota_zak³adu, int & iloœæ_pieniêdzy, ofstream & log_ogólny, fstream & log); //Funkcja informuj¹ca gracza o wyniku zak³adu
void Koniec_Gry(ofstream & log_ogólny, fstream & log, const int & iloœæ_pieniêdzy); //Funkcja informuj¹ca o wynikach gracza jak skoñczy³ grê
void Pêtla_G³ówna(int & wygrana, int & kwota_zak³adu, int & iloœæ_pieniêdzy, ofstream & log_ogólny, fstream & log, const char & co_kontynuowaæ, string & typ_zak³adu, int & wylosowana_liczba); //Funkcja wywo³uj¹ca funkcje obs³uguj¹ce wszystkie elementy ruletki
void Ustaw_Ustawienia(string & tekst); //Funkcja zamieniaj¹ca wczytan¹ linijkê z ustawieniami na zmianê ustawieñ programu
void Inicjacje_Pocz¹tkowe(); //Funkcja do zainicjowanie funkcji pocz¹tkowych
bool Wyci¹gnij_z_Programu(const string & œcie¿ka, const unsigned short & numer_zasobu); //Funkcja kopiuj¹ca do folderu z programem plik bêd¹cy wewn¹trz exe
void Wypakuj_Rar(const string & nazwa_folderu); //Funkcja wypakowywuj¹ca pliki z archiwum rar
bool Przenieœ_Plik(const string & z_pliku, const string & do_pliku); //Funkcja przenosz¹ca plik z œcie¿ki z_pliku do œcie¿ki do_pliku
void Usuñ_Folder_Wypakowany_i_Winrar(const string & G³os); //Funkcja usuwaj¹ca wypakowany folder i program Winrar z folderu z programem
//-------------------------------------------------------------------------------------

//------------------------------- deklaracje funkcji obcych ---------------------------
void Change_Col(const int & num_of_col); //Funkcja zmieniaj¹ca kolor tekstu 0 - czarny 1 - niebieski 2 - zielony 3 - b³êkitny 4 - czerwony 5 - purpurowy 6 - ¿ó³ty 7 - bia³y 8 - szary 9 - jasnoniebieski 10 - jasnozielony 11 - jasnob³êkitny 12 - jasnoczerwony 13 - jasnopurpurowy 14 - jasno¿ó³ty 15 - jaskrawobia³y
void Hide_Cursor(); //Funkcja w³¹cza pokazywanie kursora tekstowego
void Show_Cursor(); //Funkcja wy³¹cza pokazywanie kursora tekstowego
bool StringtoBool(const string & var); //Funkcja zamienia string na bool
short stos(const string& _Str, size_t *_Idx = 0, int _Base = 10); //Przerobiona wersja stoi na sto(short)
BOOL TerminateProcess(const DWORD & dwProcessId, const UINT & uExitCode); //Funkcja zamykaj¹ca dany proces
//-------------------------------------------------------------------------------------

//----------------------------- deklaracje sta³ych tablic pomocniczych ------------------------
const unsigned short Ruletka_ko³o[] = { 0, 32, 15, 19, 4, 21, 2, 25, 17, 34, 6, 27, 13, 36, 11, 30, 8, 23, 10, 5, 24, 16, 33, 1, 20, 14, 31, 9, 22, 18, 29, 7, 28, 12, 35, 3, 26 }; // Kolejnoœæ liczb zgodna z ko³em ruletki
const array <char, 37 > Ruletka_plansza_kolor = { 'g','r','b','r','b','r','b','r','b','r','b','b','r','b','r','b','r','b','r','r','b','r','b','r','b','r','b','r','b','b','r','b','r','b','r','b','r' }; //Kolor dla ka¿dej liczby na planszy
const deque <unsigned short> Ruletka_plansza_kolor_col = { 2,4,8,4,8,4,8,4,8,4,8,8,4,8,4,8,4,8,4,4,8,4,8,4,8,4,8,4,8,8,4,8,4,8,4,8,4 }; //Kod koloru do funkcji zmiany koloru tekstu dla ka¿dej liczby na planszy
const map <string, unsigned short> Numer_zasobu_rar = { { "Agata_1",IDR_RCDATA1 },{ "Agata_2",IDR_RCDATA2 },{ "Agata_3",IDR_RCDATA3 },{ "Agata_4",IDR_RCDATA4 },{ "Agata_5",IDR_RCDATA5 },{ "Ewa_1",IDR_RCDATA6 },{ "Ewa_2",IDR_RCDATA7 },{ "Ewa_3",IDR_RCDATA8 },{ "Ewa_4",IDR_RCDATA9 },{ "Ewa_5",IDR_RCDATA10 },{ "Ewa2_1",IDR_RCDATA11 },{ "Ewa2_2",IDR_RCDATA12 },{ "Ewa2_3",IDR_RCDATA13 },{ "Ewa2_4",IDR_RCDATA14 },{ "Ewa2_5",IDR_RCDATA15 },{ "Jacek_1",IDR_RCDATA16 },{ "Jacek_2",IDR_RCDATA17 },{ "Jacek_3",IDR_RCDATA18 },{ "Jacek_4",IDR_RCDATA19 },{ "Jacek_5",IDR_RCDATA20 },{ "Jacek2_1",IDR_RCDATA21 },{ "Jacek2_2",IDR_RCDATA22 },{ "Jacek2_3",IDR_RCDATA23 },{ "Jacek2_4",IDR_RCDATA24 },{ "Jacek2_5",IDR_RCDATA25 },{ "Jan_1",IDR_RCDATA26 },{ "Jan_2",IDR_RCDATA27 },{ "Jan_3",IDR_RCDATA28 },{ "Jan_4",IDR_RCDATA29 },{ "Jan_5",IDR_RCDATA30 },{ "Jan2_1",IDR_RCDATA31 },{ "Jan2_2",IDR_RCDATA32 },{ "Jan2_3",IDR_RCDATA33 },{ "Jan2_4",IDR_RCDATA34 },{ "Jan2_5",IDR_RCDATA35 },{ "Maja_1",IDR_RCDATA36 },{ "Maja_2",IDR_RCDATA37 },{ "Maja_3",IDR_RCDATA38 },{ "Maja_4",IDR_RCDATA39 },{ "Maja_5",IDR_RCDATA40 },{ "Maja2_1",IDR_RCDATA41 },{ "Maja2_2",IDR_RCDATA42 },{ "Maja2_3",IDR_RCDATA43 },{ "Maja2_4",IDR_RCDATA44 },{ "Maja2_5",IDR_RCDATA45 } }; //Drzewo wi¹¿¹ce Nazwê g³osu z szybkoœci¹ a numerem zasobu
const vector <string> Nazwa_g³osu = { "","Jacek","Ewa","Maja","Jan","Jacek2","Ewa2","Maja2","Jan2","Agata" }; //Vector stringów w celu przypisania numer g³osu <-> nazwa g³osu
//-------------------------------------------------------------------------------------

//---------- deklaracje typu strukturalnego do zmian ustawieñ programu ----------------
struct S_Ustawienia //Struktura z wpisanymi domyœlnymi ustawieniami
{
	short iloœæ_min_dodatkowych_obrotów_ruletki = 2; // Minimalna iloœæ obrotów ruletki przed podaniem wartoœci wylosowanej
	short iloœæ_max_dodatkowych_obrotów_ruletki = 3; // Maksymalna iloœæ dodatkowych obrotów ruletki przed podaniem wartoœci wylosowanej
	short czas_przeskoku_kulki_szybki = 50; //Czas w ms przerwy pomiêdzy przeskokami na pocz¹tek losowania na kolejn¹ liczbê na kole ruletki
	short czas_przeskoku_kulki_wolny = 75; //Czas w ms przerwy pomiêdzy przeskokami pod koniec losowania na kolejn¹ liczbê na kole ruletki
	short czas_przerwy_dzwiêku = 500; //Czas w ms przerwy pomiêdzy pikniêciami oznaczaj¹cymi wynik zak³adu
	bool styl_liczenia_wygranej = true; //0 dla odejmowania w³o¿onych w zak³ad pieniêdzy (przy tym zak³ady 1:1 nie zwiêkszaj¹ iloœæ_pieniêdzy), 1 dla nie odejmowania (przy tym zak³ady 1:1 zwiêkszaj¹ iloœæ_pieniêdzy)
	int kwota_pocz¹tkowa = 1000; //Iloœæ $ z którymi zaczyna siê grê
	bool stan_dŸwiêków = true; //Czy w³¹czone dŸwiêki 1 <-tak 0 <-nie
	bool czy_kontynuowaæ_grê = true; //Czy w³¹czone kontynuowanie gry od skoñczonej poprzednio pozycji 1 <-tak 0 <-nie
	short g³os_odczytu_numeru = 1; //Wybór g³osu który odczyta wylosowany numer 0 <- Brak 1 <- Jacek (Ivona) 2 <- Ewa (Ivona) 3 <- Maja (Ivona) 4 <- Jan (Ivona) 5 <- Jacek (Ivona 2) 6 <- Ewa (Ivona 2) 7 <- Maja (Ivona 2) 8 <- Jan (Ivona 2) 9 <- Agata (Scansoft)
	short g³os_szybkoœæ_odczytu_numeru = (2 * 2); //Wybór szybkoœci mowy, skala od 1 do 5
	bool efekty_dŸwiêkowe = true; //Czy w³¹czone efekty dŸwiêkowe 1 <-tak 0 <-nie
	bool metoda_liczenia_wygranej_zerowej = true; //0 dla nie uzyskiwania zwrotu po³owy zak³adu przy obstawieniu szans prostych a wylosowaniu 0, 1 dla uzyskiwania zwrotu po³owy zak³adu przy obstawieniu szans prostych a wylosowaniu 0
};
//-------------------------------------------------------------------------------------

//------------------ deklaracje zmiennych/struktur globalnych -------------------------
SYSTEMTIME Czas; //Struktura do której zapisywana jest aktualna data i czas
bool G³osyKompletne = true;
bool EfektyKompletne = true;
string G³os;
S_Ustawienia Ustawienia;
//-------------------------------------------------------------------------------------

int main()
{
	//Inicjowanie zmiennych lokalnych
	ofstream log_ogólny; //Utworzenie typu do celu zapisu do pliku
	log_ogólny.open("log_ogólny.txt", ios::app); //Otworzenie pliku z ustawieniem kursora zapisu do pliku
	fstream log; //Utworzenie typu do celu zapisu i/lub odczytu do i/lub z pliku
	int iloœæ_pieniêdzy = Ustawienia.kwota_pocz¹tkowa, kwota_zak³adu, wylosowana_liczba, wygrana; //Zmienne do których wczytuje siê wartoœci liczbowe pobrane od u¿ytkownika takie jak kwota zak³adu a przechowuje iloœæ posiadanych pieniêdzy a tak¿e przechowuje wyniki funkcji losowania liczby z ruletki i kwote wygran¹ z zak³adu
	string typ_zak³adu; //Przechowuje typ zak³adu wprowadzony przez u¿ytkownika
	char co_kontynuowaæ; //Deklaracja znaku który przechowuje nazwany znakiem punkt od którego kontynuowaæ runde

	thread w¹tek1(Inicjacje_Pocz¹tkowe); //Utworzenie i uruchomienie w¹tku do zainicjowania funkcji pocz¹tkowych
	thread w¹tek2(Wczytaj_z_Pliku, ref(log_ogólny), ref(log), ref(co_kontynuowaæ), ref(iloœæ_pieniêdzy), ref(kwota_zak³adu), ref(wylosowana_liczba), ref(typ_zak³adu)); //Utworzenie i uruchomienie w¹tku do wczytania stanu gry z pliku
	w¹tek1.join(); //Poczekanie na zakoñczenie w¹tku1
	thread w¹tek3(SprawdŸ_Ustawienia); //Utworzenie i uruchomienie w¹tku do wczytania ustawieñ z pliku
	w¹tek3.join(); //Poczekanie na zakoñczenie w¹tku3
	thread w¹tek4(SprawdŸ_Pliki, ref(Ustawienia.g³os_odczytu_numeru), ref(Ustawienia.g³os_szybkoœæ_odczytu_numeru)); //Utworzenie i uruchomienie w¹tku do wczytania plików audio
	w¹tek4.join(); //Poczekanie na zakoñczenie w¹tku4
	w¹tek2.join(); //Poczekanie na zakoñczenie w¹tku2
	do
	{
		Pêtla_G³ówna(wygrana, kwota_zak³adu, iloœæ_pieniêdzy, log_ogólny, log, co_kontynuowaæ, typ_zak³adu, wylosowana_liczba); //Funkcja obs³uguj¹ca wszystkie elementy gry
		co_kontynuowaæ = 'n'; //Przypisanie znaku rozpoczêcia rundy od pocz¹tku
	} while (Czy_Kontynuowaæ(iloœæ_pieniêdzy)); //Pêtla dza³aj¹ca do czasu wartoœci fa³sz zwróconej przez funkcjê Czy_kontynuowaæ

	Koniec_Gry(log_ogólny, log, iloœæ_pieniêdzy); //Zakoñczenie gry i wskazanie wyniku

	system("pause"); //Wywo³anie funkcji wymagaj¹cej do zamkniêcia naciœniêcie dowolnego klawisza

	return 0; //Zwrócenie wartoœæ 0, czyli porogram zakoñczy³ siê bez b³êdu
}

string Obstaw()
{
	string zaklad_typ; //Deklaracja zmiennej typu string przechowywuj¹cej typ zak³adu

	do { //Pêtla do aby wykona³a siê conajmniej raz
		cout << "Jak¹ opcje chcesz obstawiæ? (zgodnie z poni¿szym opisem) :" << endl; //Zadanie pytania u¿ytkownikowi
		cout << "p - parzyste" << endl; //Wskazaæ mo¿liw¹ odpowiedŸ
		cout << "n - nieparzyste" << endl; //Wskazaæ mo¿liw¹ odpowiedŸ
		cout << "r - czerwone (red)" << endl; //Wskazaæ mo¿liw¹ odpowiedŸ
		cout << "b - czarne (black)" << endl; //Wskazaæ mo¿liw¹ odpowiedŸ
		cout << "g - górna po³owa" << endl; //Wskazaæ mo¿liw¹ odpowiedŸ
		cout << "d - dolna po³owa" << endl; //Wskazaæ mo¿liw¹ odpowiedŸ
		cout << "k1, k2, k3 - kolumna 1, kolumna 2, kolumna 3" << endl; //Wskazaæ mo¿liw¹ odpowiedŸ
		cout << "w1, w2, ... , w12 - wiersz trzech numerów" << endl; //Wskazaæ mo¿liw¹ odpowiedŸ
		cout << "0-36 - pojedyñcze pole o odpowiednim numerze" << endl; //Wskazaæ mo¿liw¹ odpowiedŸ
		cin >> zaklad_typ; //Pobranie od u¿ytkownika odpowiedzi na pytanie
	} while ( //U¿ywam takiej sk³adni poniewa¿ jeœli masz wyra¿enie z logicznymi operatorami && lub ||, to w momencie gdy wynik wyra¿enia ju¿ jest znany, to nie jest wyliczany dalej. (Poniewa¿ C++ jest "leniwe", co zarazem jest optymalne)
		(zaklad_typ.size() > 3) ||  //Sprawdzanie czy wprowadzono zak³ad jest d³u¿szy ni¿ 3
		((zaklad_typ != "p" && //Sprawdzanie czy wprowadzono zak³ad na liczby parzyste
			zaklad_typ != "n" && //Sprawdzanie czy wprowadzono zak³ad na liczby nieparzyste
			zaklad_typ != "r" && //Sprawdzanie czy wprowadzono zak³ad na czerwone liczby
			zaklad_typ != "b" && //Sprawdzanie czy wprowadzono zak³ad na czarne liczby
			zaklad_typ != "g" && //Sprawdzanie czy wprowadzono zak³ad na liczby z górnej po³ówki
			zaklad_typ != "d" && //Sprawdzanie czy wprowadzono zak³ad na liczby z dolnej po³ówki
			zaklad_typ != "k1" && //Sprawdzanie czy wprowadzono zak³ad na liczby z kolumny 1
			zaklad_typ != "k2" && //Sprawdzanie czy wprowadzono zak³ad na liczby z kolumny 2
			zaklad_typ != "k3" && //Sprawdzanie czy wprowadzono zak³ad na liczby z kolumny 3
			zaklad_typ != "w1" && //Sprawdzanie czy wprowadzono zak³ad na liczby z wiersza 1
			zaklad_typ != "w2" && //Sprawdzanie czy wprowadzono zak³ad na liczby z wiersza 2
			zaklad_typ != "w3" && //Sprawdzanie czy wprowadzono zak³ad na liczby z wiersza 3
			zaklad_typ != "w4" && //Sprawdzanie czy wprowadzono zak³ad na liczby z wiersza 4
			zaklad_typ != "w5" && //Sprawdzanie czy wprowadzono zak³ad na liczby z wiersza 5
			zaklad_typ != "w6" && //Sprawdzanie czy wprowadzono zak³ad na liczby z wiersza 6
			zaklad_typ != "w7" && //Sprawdzanie czy wprowadzono zak³ad na liczby z wiersza 7
			zaklad_typ != "w8" && //Sprawdzanie czy wprowadzono zak³ad na liczby z wiersza 8
			zaklad_typ != "w9" && //Sprawdzanie czy wprowadzono zak³ad na liczby z wiersza 9
			zaklad_typ != "w10" && //Sprawdzanie czy wprowadzono zak³ad na liczby z wiersza 10
			zaklad_typ != "w11" && //Sprawdzanie czy wprowadzono zak³ad na liczby z wiersza 11
			zaklad_typ != "w12" && //Sprawdzanie czy wprowadzono zak³ad na liczby z wiersza 12
			zaklad_typ != "0" && //Sprawdzanie czy wprowadzono zak³ad na cyfrê 0
			zaklad_typ != "1" && //Sprawdzanie czy wprowadzono zak³ad na cyfrê 1
			zaklad_typ != "2" && //Sprawdzanie czy wprowadzono zak³ad na cyfrê 2
			zaklad_typ != "3" && //Sprawdzanie czy wprowadzono zak³ad na cyfrê 3
			zaklad_typ != "4" && //Sprawdzanie czy wprowadzono zak³ad na cyfrê 4
			zaklad_typ != "5" && //Sprawdzanie czy wprowadzono zak³ad na cyfrê 5
			zaklad_typ != "6" && //Sprawdzanie czy wprowadzono zak³ad na cyfrê 6
			zaklad_typ != "7" && //Sprawdzanie czy wprowadzono zak³ad na cyfrê 7
			zaklad_typ != "8" && //Sprawdzanie czy wprowadzono zak³ad na cyfrê 8
			zaklad_typ != "9" && //Sprawdzanie czy wprowadzono zak³ad na cyfrê 9
			zaklad_typ != "10" && //Sprawdzanie czy wprowadzono zak³ad na liczbê 10
			zaklad_typ != "11" && //Sprawdzanie czy wprowadzono zak³ad na liczbê 11
			zaklad_typ != "12" && //Sprawdzanie czy wprowadzono zak³ad na liczbê 12
			zaklad_typ != "13" && //Sprawdzanie czy wprowadzono zak³ad na liczbê 13
			zaklad_typ != "14" && //Sprawdzanie czy wprowadzono zak³ad na liczbê 14
			zaklad_typ != "15" && //Sprawdzanie czy wprowadzono zak³ad na liczbê 15
			zaklad_typ != "16" && //Sprawdzanie czy wprowadzono zak³ad na liczbê 16
			zaklad_typ != "17" && //Sprawdzanie czy wprowadzono zak³ad na liczbê 17
			zaklad_typ != "18" && //Sprawdzanie czy wprowadzono zak³ad na liczbê 18
			zaklad_typ != "19" && //Sprawdzanie czy wprowadzono zak³ad na liczbê 19
			zaklad_typ != "20" && //Sprawdzanie czy wprowadzono zak³ad na liczbê 20
			zaklad_typ != "21" && //Sprawdzanie czy wprowadzono zak³ad na liczbê 21
			zaklad_typ != "22" && //Sprawdzanie czy wprowadzono zak³ad na liczbê 22
			zaklad_typ != "23" && //Sprawdzanie czy wprowadzono zak³ad na liczbê 23
			zaklad_typ != "24" && //Sprawdzanie czy wprowadzono zak³ad na liczbê 24
			zaklad_typ != "25" && //Sprawdzanie czy wprowadzono zak³ad na liczbê 25
			zaklad_typ != "26" && //Sprawdzanie czy wprowadzono zak³ad na liczbê 26
			zaklad_typ != "27" && //Sprawdzanie czy wprowadzono zak³ad na liczbê 27
			zaklad_typ != "28" && //Sprawdzanie czy wprowadzono zak³ad na liczbê 28
			zaklad_typ != "29" && //Sprawdzanie czy wprowadzono zak³ad na liczbê 29
			zaklad_typ != "30" && //Sprawdzanie czy wprowadzono zak³ad na liczbê 30
			zaklad_typ != "31" && //Sprawdzanie czy wprowadzono zak³ad na liczbê 31
			zaklad_typ != "32" && //Sprawdzanie czy wprowadzono zak³ad na liczbê 32
			zaklad_typ != "33" && //Sprawdzanie czy wprowadzono zak³ad na liczbê 33
			zaklad_typ != "34" && //Sprawdzanie czy wprowadzono zak³ad na liczbê 34
			zaklad_typ != "35" && //Sprawdzanie czy wprowadzono zak³ad na liczbê 35
			zaklad_typ != "36")) //Sprawdzanie czy wprowadzono zak³ad na liczbê 36
		); //Je¿eli któryœ z warunków siê niezgadza to pêtla nie jest kontynuowana

	return zaklad_typ; //Zwracam typ zak³adu podany przez u¿ytkownika
}

void Wczytaj_Kwotê_Zak³adu(int & kwota_zak³adu, const int & iloœæ_pieniêdzy)
{
	string kwota_zak³adu_s; //Deklaracja zmiennej typu string do wczytywania kwoty aby zabezpieczyæ siê przed b³êdem wpisania do zmiennej liczbowej litery

	while (true) //Rozpoczêcie pêtli nieskoñczonej
	{
		cout << "Masz " << iloœæ_pieniêdzy << "$, jak¹ kwot¹ chcesz obstawiæ wynik?" << endl; //Podanie akualnego stanu konta i zadanie pytania o kwotê zak³adu
		cin >> kwota_zak³adu_s; //Pobranie w tekœcie kwoty zak³¹du
		kwota_zak³adu = atoi(kwota_zak³adu_s.c_str()); //Zmiana stringa na inta i wpisanie do zmiennej kwota_zak³adu
		if ((kwota_zak³adu > 0) && (kwota_zak³adu <= iloœæ_pieniêdzy)) break; //Sprawdzenie czy kwota zak³adu jest wiêksza od zera i mniejsza lub równa dostêpnej gotówce, je¿eli tak to zatrzymuje pêtle
		if (kwota_zak³adu == 0) //W przeciwym wypadku je¿eli wynikiem zamiany na liczbê jest zero (wynikiem zamiany jest zero kiedy tekst to zero lub kiedy jest b³¹d zamiany) to
		{
			bool czy_zero = true; //Utworzenie zmiennej informuj¹cej czy znaleziono zero w tekœcie i przypisanie jej wartoœci true
			for (size_t i = 0; i < kwota_zak³adu_s.size(); ++i) //Rozpoczêcie pêtli numerowanej przez zmienn¹ i przez wszystkie znaki wczytanego tekst
				if (kwota_zak³adu_s[i] != '0') //Je¿eli znak na i-tej pozycji
				{
					cout << "Wprowadzi³eæ nieprawid³ow¹ wartoœæ" << endl; //Poinformowanie u¿ytkownika, ¿e nie mo¿e obstawiæ tekstowego
					if (Ustawienia.stan_dŸwiêków) cout << '\a'; //Je¿eli stan_dŸwiêków == 1 to wywo³anie pikniêcia w g³oœniku
					czy_zero = false; //Zmiana wartoœci zmiennej czy znaleziono zero w tekœcie na false
					break; //Zatrzymanie pêtli
				}
			if (czy_zero) //Sprawdzenie czy znaleziono same zera w tekœcie, je¿eli tak to
			{
				cout << "Nie mo¿esz obstawiæ zerowego zak³adu" << endl; //Poinformowanie u¿ytkownika, ¿e nie mo¿e obstawiæ zerowego zak³adu
				if (Ustawienia.stan_dŸwiêków) cout << '\a'; //Je¿eli stan_dŸwiêków == 1 to wywo³anie pikniêcia w g³oœniku
			}
		}
		else if (kwota_zak³adu > iloœæ_pieniêdzy) //Je¿eli u¿ytkownik chce obstawiæ za wiêcej ni¿ ma, to
		{
			cout << "Nie masz tyle pieniêdzy" << endl; //Poinformowanie go o tym
			if (Ustawienia.stan_dŸwiêków) cout << '\a'; //Je¿eli stan_dŸwiêków == 1 to wywo³anie pikniêcia w g³oœniku
		}
		else if (kwota_zak³adu < 0) //Je¿eli u¿ytkownik chce obstawiæ za ujemn¹ kwotê, to
		{
			cout << "Nie mo¿esz obstawiæ ujemn¹ kwot¹ zak³adu" << endl; //Poinformowanie go o tym
			if (Ustawienia.stan_dŸwiêków) cout << '\a'; //Je¿eli stan_dŸwiêków == 1 to wywo³anie pikniêcia w g³oœniku
		}
	}
}

int Zakrêæ_Ruletk¹()
{
	const int iloœæ_zakrêceñ = rand() % (Ustawienia.iloœæ_max_dodatkowych_obrotów_ruletki + 1) + Ustawienia.iloœæ_min_dodatkowych_obrotów_ruletki; //Deklarowanie i przpisanie zmiennej liczbowj zawieraj¹c¹ pseudolosow¹ (o niskiej pseoudolosowoœci) iloœæ obrotów ruletk¹ ((od 0 do max dodatkowych obrotów ruletki) + minimalna iloœæ obrotów ruletki) zanim nastêpi finalny obrót
	const double czas_przeskoku_kulki_szybki_opóŸnienie = Ustawienia.czas_przeskoku_kulki_szybki / (iloœæ_zakrêceñ * 37.0); //Deklarowanie i przpisanie zmiennej zmiennoprzecinkowej zawieraj¹c¹ czas o ile kolejna wartoœæ na kole ruletki powinna byæ szybciej pokazana
	Hide_Cursor(); //Ukrycie kursora tekstowego w konsoli
	for (auto i = 0; i < iloœæ_zakrêceñ; ++i) //Wykonanie iloœæ_zakrêceñ obrotów ruletk¹
		for (size_t ii = 0; ii < 37; ++ii) //Przejœcie przez wszystkie pozycje ruletki
		{
			Change_Col(Ruletka_plansza_kolor_col[Ruletka_ko³o[ii]]); //Zmiana koloru tekstu w konsoli zgodnie z kolorem numeru na ruletce
			cout << Ruletka_ko³o[ii]; //Wypisanie numeru na kole ruletki na którym znajduje siê pêtla
			Sleep((DWORD)(czas_przeskoku_kulki_szybki_opóŸnienie*((double)i*37.0 + (double)ii))); //Przestój który zwiêksza siê co zmianê pozycji pêtli
			Change_Col(7); //Powrót do standardowego koloru tekstu w konsoli
			cout << "\b\b" << "  " << "\b\b"; //Cofniêcie kursora tekstowego do lewej strony konsoli aby zape³niæ potem spacjami czyli niewidocznym znakiem wiersza konsoli aby widaæ przejœcie pomiêdzy liczbami na ruletce
		}
	const auto wylosowana_pozycja = Wylosuj(0, 36); //Deklarowanie i przpisanie zmiennej liczbowj zawieraj¹c¹ losow¹ lub pseudolosow¹ liczbê (o wysokiej pseoudolosowoœci) pozycjê na ruletce
	const double czas_przeskoku_kulki_wolny_przyspieszenie = (Ustawienia.czas_przeskoku_kulki_wolny - Ustawienia.czas_przeskoku_kulki_szybki) / (double)(wylosowana_pozycja); //Deklarowanie i przpisanie zmiennej zmiennoprzecinkowej zawieraj¹c¹ czas o ile kolejna wartoœæ na kole ruletki powinna byæ szybciej pokazana
	for (auto i = 0; i < wylosowana_pozycja; ++i) //Przejœcie przez pozycje do pozycji o 1 mniejszej od wylosowanej pozyji na ruletce
	{
		Change_Col(Ruletka_plansza_kolor_col[Ruletka_ko³o[i]]); //Zmiana koloru tekstu w konsoli zgodnie z kolorem numeru na ruletce
		cout << Ruletka_ko³o[i]; //Wypisanie numeru na kole ruletki na którym znajduje siê pêtla
		Sleep((DWORD)(Ustawienia.czas_przeskoku_kulki_szybki + (czas_przeskoku_kulki_wolny_przyspieszenie*i))); //Przestój który zwiêksza siê co zmianê pozycji pêtli
		Change_Col(7); //Powrót do standardowego koloru tekstu w konsoli
		cout << "\b\b" << "  " << "\b\b"; //Cofniêcie kursora tekstowego do lewej strony konsoli aby zape³niæ podem spacjami czyli niewidocznym znakiem wiersza konsoli aby widaæ przejœcie pomiêdzy liczbami na ruletce
	}
	cout << "Wylosowano numer "; //Poinformowanie o zakoñczeniu (wyœwietlania) losowania
	Change_Col(Ruletka_plansza_kolor_col[Ruletka_ko³o[wylosowana_pozycja]]);//Zmiana koloru tekstu w konsoli zgodnie z kolorem numeru na ruletce
	cout << Ruletka_ko³o[wylosowana_pozycja]; //Wypisanie liczby na wylosowanej pozycji ruletki
	Change_Col(7); //Powrót do standardowego koloru tekstu w konsoli
	cout << ". "; //Zakoñczenie tekstu kropk¹
	Show_Cursor(); //Pokazanie kursora tekstowego w konsoli

	return Ruletka_ko³o[wylosowana_pozycja]; //Zwracam wartoœæ bêd¹c¹ na wylosowanym polu ruletki
}

int SprawdŸ_Zak³ad(const int & kwota, const string & typ_zak³adu, const int & wylosowana_liczba)
{
	int wygrana = kwota; //Deklaracja zmiennej przechowywuj¹ca kwotê wygran¹ lub zwrócon¹ przy wylosowaniu 0 i przypisuê jej wartoœæ kwota jakby wygrana by³a 1:1

	if (wylosowana_liczba == 0 && Ustawienia.metoda_liczenia_wygranej_zerowej) //Warunek sprawdzaj¹cy czy wylosowano 0
		switch (typ_zak³adu[0]) //Je¿eli tak to switch do obliczenia wygranej lub przegranej
		{
		case 'p':
		{
			wygrana >>= 1; //Je¿eli typ zak³adu by³ p to wygrana, a dok³adniej zwrot wynosi po³owê zak³adu
			break; //Wyjœcie z switcha
		}
		case 'n':
		{
			wygrana >>= 1; //Je¿eli typ zak³adu by³ n to wygrana, a dok³adniej zwrot wynosi po³owê zak³adu
			break; //Wyjœcie z switcha
		}
		case 'r':
		{
			wygrana >>= 1; //Je¿eli typ zak³adu by³ r to wygrana, a dok³adniej zwrot wynosi po³owê zak³adu
			break; //Wyjœcie z switcha
		}
		case 'b':
		{
			wygrana >>= 1; //Je¿eli typ zak³adu by³ b to wygrana, a dok³adniej zwrot wynosi po³owê zak³adu
			break; //Wyjœcie z switcha
		}
		case 'g':
		{
			wygrana >>= 1; //Je¿eli typ zak³adu by³ g to wygrana, a dok³adniej zwrot wynosi po³owê zak³adu
			break; //Wyjœcie z switcha
		}
		case 'd':
		{
			wygrana >>= 1; //Je¿eli typ zak³adu by³ d to wygrana, a dok³adniej zwrot wynosi po³owê zak³adu
			break; //Wyjœcie z switcha
		}
		case 'k':
		{
			wygrana = 0; //Je¿eli typ zak³adu by³ k to przegra³o siê zak³ad
			break; //Wyjœcie z switcha
		}
		case 'w':
		{
			wygrana = 0; //Je¿eli typ zak³adu by³ w to przegra³o siê zak³ad
			break; //Wyjœcie z switcha
		}
		case '0':
		{
			wygrana = (wygrana << 0) + (wygrana << 1) + (wygrana << 5); //Je¿eli typ zak³adu by³ 0 to wygra³o siê zak³ad, wygrana jest 35:1
			break; //Wyjœcie z switcha
		}
		default:
			; //W przeciwym wypadkunic nie rób
		}
	else //Je¿eli wylosowana liczba nie jest zerem to
	{
		if (typ_zak³adu == "p") //Je¿eli typ zak³adu to p
			if (!(wylosowana_liczba & 1)) /*wygrana *= 1*/; //To sprawdzam czy wylosowana liczba jest parzysta, je¿eli tak to wygrana jest 1:1
			else wygrana = 0; //Je¿eli wylosowana liczba nie jest parzysta to przegra³o siê zak³ad
		else if (typ_zak³adu == "n") //Je¿eli typ zak³adu to n
			if (wylosowana_liczba & 1) /*wygrana *= 1*/; //To sprawdzam czy wylosowana liczba jest nieparzysta, je¿eli tak to wygrana jest 1:1
			else wygrana = 0; //Je¿eli obstawiony numer nie jest nieparzysta to przegra³o siê zak³ad
		else if (typ_zak³adu == "r") //Je¿eli typ zak³adu to n
			if (Ruletka_plansza_kolor[wylosowana_liczba] == 'r') /*wygrana *= 1*/; //To sprawdzam czy wylosowana liczba jest czerwona, je¿eli tak to wygrana jest 1:1
			else wygrana = 0; //Je¿eli wylosowana liczba nie jest czerwony to przegra³o siê zak³ad
		else if (typ_zak³adu == "b") //Je¿eli typ zak³adu to n
			if (Ruletka_plansza_kolor[wylosowana_liczba] == 'b') /*wygrana *= 1*/; //To sprawdzam czy wylosowana liczba jest czarna, je¿eli tak to wygrana jest 1:1
			else wygrana = 0; //Je¿eli wylosowana liczba nie jest czarny to przegra³o siê zak³ad
		else if (typ_zak³adu == "g") //Je¿eli typ zak³adu to g
			if (wylosowana_liczba < 19) /*wygrana *= 1*/; //To sprawdzam czy wylosowana liczba jest od 1 do 18, je¿eli tak to wygrana jest 1:1
			else wygrana = 0; //Je¿eli wylosowana liczba nie nale¿y do przedzia³u [1,18] to przegra³o siê zak³ad
		else if (typ_zak³adu == "d") //Je¿eli typ zak³adu to d
			if (wylosowana_liczba > 18) /*wygrana *= 1*/; //To sprawdzam czy wylosowana liczba jest od 19 do 36, je¿eli tak to wygrana jest 1:1
			else wygrana = 0; //Je¿eli wylosowana liczba nie nale¿y do przedzia³u [19,36] to przegra³o siê zak³ad
		else if (typ_zak³adu[0] == 'k') //Je¿eli typ zak³adu to k
			if ((wylosowana_liczba - 1) % 3 == (typ_zak³adu[1] - '1')) wygrana <<= 1; //To sprawdzam czy wylosowana liczba jest z obstawionej kolumny, je¿eli tak to wygrana jest 2:1
			else wygrana = 0; //Je¿eli wylosowana liczba nie jest z obstawionej kolumny to przegra³o siê zak³ad
		else if (typ_zak³adu[0] == 'w') //Je¿eli typ zak³adu to w
			if (((wylosowana_liczba - 1) / 3 + 1) == (typ_zak³adu[1] - '0')) wygrana = (wygrana << 0) + (wygrana << 1) + (wygrana << 3); //To sprawdzam czy wylosowana liczba jest z obstawionego wiersza, je¿eli tak to wygrana jest 11:1
			else wygrana = 0; //Je¿eli wylosowana liczba nie jest z obstawionego wiersza to przegra³o siê zak³ad
		else if (wylosowana_liczba == strtol(typ_zak³adu.c_str(), nullptr, 10)) wygrana = (wygrana << 0) + (wygrana << 1) + (wygrana << 5); //Je¿eli typ zak³adu to liczba, to sprawdzam czy wylosowana liczba jest równa obstawionej liczbie, je¿eli tak to wygrana jest 35:1
		else wygrana = 0; //Je¿eli wylosowana liczba nie jest równa obstawionej liczbie to przegra³o siê zak³ad
	}

	if (wygrana >= kwota) cout << "Obstawi³eœ poprawnie, wygrywasz " << wygrana << "$." << endl; //Je¿eli wygrana jest wiêksza lub równa obstawionej kwocie to informujê o tym, ¿e wygra³
	else if (wygrana == (kwota >> 1)) cout << "Obstawi³eœ niepoprawnie lecz uda³o Ci siê, dostajesz po³owê zak³adu " << wygrana << "$." << endl; //Je¿eli wygrana jest równa po³owie obstawionej kwocie to informujê o tym, ¿e przegra³ po³owe stawki
	else cout << "Obstawi³eœ niepoprawnie, przegra³eœ " << kwota << "$." << endl; //Je¿eli wygrana jest równa zero to informujê o tym, ¿e przegra³

	return wygrana; //Zwracam wartoœ wygranej lub zwrotu
}

bool Czy_Kontynuowaæ(const int & iloœæ_pieniêdzy)
{
	string tak_nie; //Zadeklarowanie zmiennej typu string

	if (iloœæ_pieniêdzy == 0) //Je¿eli posiadana iloœæ gotówki jest równa 0
	{
		cout << "Nie mo¿esz kontynuowaæ, przegra³eœ wszystko" << endl; //Poinformowanie u¿ytkownika, ¿e jest bankrutem
		return false; //Zwrot wartoœci false, co oznacza, ¿e kolejna runda siê nie odbêdzie
	}

	while (true) //Rozpoczêcie pêtli nieskoñczonej
	{
		cout << "Na koncie masz " << iloœæ_pieniêdzy << "$, czy chcesz grac dalej ('t'-tak, 'n'-nie) ?" << endl; //Pointormowanie o stanie konta i zapytanie o to czy gra dalej
		cin >> tak_nie; //Pobranie od u¿ytkownika odpowiedzi na powy¿sze pytanie
		if (tak_nie == "t" || tak_nie == "tak" || tak_nie == "Tak" || tak_nie == "TAK" || tak_nie == "n" || tak_nie == "nie" || tak_nie == "Nie" || tak_nie == "NIE") //Sprawdzenie czy odpowiedŸ pasuje do mo¿liwoœci
			if (tak_nie[0] == 't' || tak_nie[0] == 'T') return true; //Je¿eli pasuje to sprawdzam czy pierwsza litera to t i zwracam wartoœæ true
		return false; //W przeciwym wypadku zwracam wartoœæ false
	}
}

void Change_Col(const int & num_of_col)
{
	const HANDLE h_wyj = GetStdHandle(STD_OUTPUT_HANDLE); //Stworzenie zmiennej typu uchwyt i przypisanie do standardowego wyjœcia
	SetConsoleTextAttribute(h_wyj, num_of_col); //Zmienia atrybut koloru tekstu w konsoli
}

void Hide_Cursor()
{
	const HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE); //Stworzenie zmiennej typu uchwyt i przypisanie do standardowego wyjœcia
	CONSOLE_CURSOR_INFO hCCI; //Stworzenie zmiennej typu informacji o kursorze tekstowym w konsoli
	GetConsoleCursorInfo(hConsoleOut, &hCCI); //Przypisanie do zmiennej informacji o kursorze tekstowym w konsoli
	hCCI.bVisible = FALSE; //Zmiena widocznoœci kursora na niewidoczny
	SetConsoleCursorInfo(hConsoleOut, &hCCI); //Ustawienie widocznoœci kursora zgodnie z poprzedni¹ zmienn¹
}

void Show_Cursor()
{
	const HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE); //Stworzenie zmiennej typu uchwyt i przypisanie do standardowego wyjœcia
	CONSOLE_CURSOR_INFO hCCI; //Stworzenie zmiennej typu informacji o kursorze tekstowym w konsoli
	GetConsoleCursorInfo(hConsoleOut, &hCCI); //Przypisanie do zmiennej informacji o kursorze tekstowym w konsoli
	if (!hCCI.bVisible) //Sprawdzenie czy wartoœæ widocznoœci kursorsora tekstego w konsoli jest ró¿na od prawdy
	{
		hCCI.bVisible = TRUE;//Je¿eli tak, to zmiena widocznoœci kursora na widoczny
		SetConsoleCursorInfo(hConsoleOut, &hCCI); //I ustawienie widocznoœci kursora zgodnie z poprzedni¹ zmienn¹
	}
}

int Wylosuj(const int & od_liczby, const int & do_liczby)
{
	if (od_liczby > do_liczby) //Je¿eli od jest wiêksze ni¿ do to
		return Wylosuj(do_liczby, od_liczby); //Wywo³ujemy funkcje z przeciwn¹ kolejnoœci¹ argumentów

	random_device generator; //Generator liczb losowych, który generuje niedeterministyczne liczby losowe, jeœli s¹ obs³ugiwane.
	if (fabs(generator.entropy() - 32.0) > DBL_EPSILON) //Je¿eli entropia jest mniejsza od 32 oznacza, ¿e komputer nie dysponuje mo¿liwoœci¹ u¿ycia tego generatora liczb losowy
	{
#if defined (__x86_64__) || defined(_M_X64) || defined(__x86_64) || defined(__amd64) || defined(__amd64__) || defined(_M_AMD64) //Sprawdzenie czy sytem operacyjny jest 64-bitowy
		mt19937_64 mgenerator((unsigned int)chrono::high_resolution_clock::now().time_since_epoch().count()); //Dla 64 bitowego systemu zamiast powy¿szego generatora u¿ywa generator liczb pseudolosowych Mersenne Twister 19937 w wersji 64 bitowej i wczytuje ziarno z precyzyjnego nanosekundowego zegara
		return ((mgenerator() % (do_liczby - od_liczby + 1)) + od_liczby); //Zwraca wygenerowan¹ liczbê z przedzia³u [od_liczby,do_liczby]
#else
		mt19937 mgenerator((unsigned int)chrono::high_resolution_clock::now().time_since_epoch().count()); //Dla 32 bitowego systemu zamiast powy¿szego generatora u¿ywa generator liczb pseudolosowych Mersenne Twister 19937 w wersji 32 bitowej i wczytuje ziarno z precyzyjnego nanosekundowego zegara
		return ((mgenerator() % (do_liczby - od_liczby + 1)) + od_liczby); //Zwraca wygenerowan¹ liczbê z przedzia³u [od_liczby,do_liczby]
#endif
	}
	uniform_int_distribution<int> distribution(od_liczby, do_liczby); //Wskazuje przedzia³ generowanych liczb
	return distribution(generator); //Zwraca wygenerowan¹ liczbê z przedzia³u
}

void Odczytaj_Liczbê(const int & wylosowana_liczba, const string & typ_zak³adu) {
	if ((Ustawienia.g³os_odczytu_numeru == 0) || (!G³osyKompletne)) return; //Je¿eli ustawienia wy³¹czaj¹ g³os lub brak plików g³osu to wyjdŸ z funkcji

	stringstream numers; //Utworzenie typu do zamiany liczby na tekst
	numers << wylosowana_liczba; //Wpisanie to typu wylosowanej liczby
	PlaySound((G³os + numers.str() + ".wav").c_str(), nullptr, SND_SYNC); //Odczytanie wylosowanego numeru
	if (wylosowana_liczba | 0) //Je¿eli nie jest to 0
		if (typ_zak³adu == "p" || typ_zak³adu == "n") //Je¿eli typ zak³adu to p lub n
			if (wylosowana_liczba & 1) //Je¿eli wylosowana liczba modulo 2 jest 0 to
				PlaySound((G³os + "n.wav").c_str(), nullptr, SND_SYNC); //Powiedz, ¿e wylosowana licza jest nieparzysta
			else
				PlaySound((G³os + "p.wav").c_str(), nullptr, SND_SYNC); //W przeciwym wypadku powiedz, ¿e wylosowana licza jest parzysta
		else if (typ_zak³adu == "r" || typ_zak³adu == "b") //Je¿eli typ zak³adu to r lub b
			if (Ruletka_plansza_kolor[wylosowana_liczba] == 'r') //Je¿eli kolor wylosowanej liczby to czerwony
				PlaySound((G³os + "r.wav").c_str(), nullptr, SND_SYNC); //Powiedz, ¿e wylosowana liczba jest koloru czerwonego
			else
				PlaySound((G³os + "b.wav").c_str(), nullptr, SND_SYNC); //W przeciwym wypadku powiedz, ¿e liczba jest koloru czarnego
		else if (typ_zak³adu == "g" || typ_zak³adu == "d") //Je¿eli typ zak³adu to g lub d
			if (wylosowana_liczba < 19) //Je¿eli wylosowa liczba jest mniejsza ni¿ 19
				PlaySound((G³os + "g.wav").c_str(), nullptr, SND_SYNC); //Powiedz, ¿e wylosowana liczba jest z górnej po³ówki
			else
				PlaySound((G³os + "d.wav").c_str(), nullptr, SND_SYNC); //W przeciwym wypadku powiedz, ¿e wylosowana liczba jest z dolnej po³ówki
		else if (typ_zak³adu[0] == 'k') //Je¿eli typ zak³adu to k
			PlaySound((G³os + 'k' + (char)(((wylosowana_liczba - 1) % 3) + '1') + ".wav").c_str(), nullptr, SND_SYNC); //Powiedz z jakiej kolumny jest wylosowana liczba
		else if (typ_zak³adu[0] == 'w') //Je¿eli typ zak³adu to w
		{
			stringstream numers; //Utworzenie typu do zamiany liczby na tekst
			numers << ((wylosowana_liczba - 1) / 3 + 1); //Wpisanie do typu obliczonego wiersza wylosowanej liczby
			PlaySound((G³os + 'w' + numers.str() + ".wav").c_str(), nullptr, SND_SYNC); //Powiedz z jakiego wiersza jest wylosowana liczba
		}
}

void Wczytaj_z_Pliku(ofstream & log_ogólny, fstream & log, char & co_kontynuowaæ, int & iloœæ_pieniêdzy, int & kwota_zak³adu, int & wylosowana_liczba, string & typ_zak³adu)
{
	if (!Ustawienia.czy_kontynuowaæ_grê) //Je¿eli czy_kontynuowaæ_grê == 0
		if (!_access("log_aktualny.txt", NULL)) // Sprawdzenie dostêpu do pliku (je¿eli takowy istnieje, musi istnieæ plik)
		{
			co_kontynuowaæ = 'n'; //Przypisanie znaku rozpoczêcia rundy od pocz¹tku
			remove("log_aktualny.txt"); //Usuniêcie pliku log aktualny poniewa¿ rozpoczyna siê now¹ grê
			log_ogólny << '\n' << "Uruchomiono ponownie grê z wy³¹czon¹ opcj¹ kontynuowania" << '\n'; //Wpisanie do buforu logu ogólnego informacje o rozpoczêciu nowej gry spowodowane ustawieniem gry
			log_ogólny.flush(); //Zapisanie do pliku log_ogólny.txt danych wpisanych do bufora danych
		}

	if (!_access("log_aktualny.txt", NULL)) // Sprawdzenie dostêpu do pliku (je¿eli takowy istnieje, musi istnieæ plik)
	{
		log.open("log_aktualny.txt", ios::in); //Otworzenie pliku w trybie odczytu z pliku
		string buf, bufor2; //Uworzenie 2 buforów na tekst, pierwszy na ostatni¹ linie tekst, drugi na przedostani¹ nie pust¹ linie tekstu lub ostani¹ w przypadku gdy ostania jest pusta
		getline(log, buf); //Odczyt ca³ej lini z pliku
		while (!log.eof()) //Pêtla dzia³j¹ca do czasu kiedy kursor odczytu z pliku nie bêdzie na koñcu pliku
		{
			if (!(buf.empty()) && ((buf.find("Posiadasz") != string::npos) || (buf.find("Wylosowano") != string::npos) || (buf.find("Obstawiono zaklad") != string::npos) || (buf.find("Gra rozpoczeta dnia") != string::npos))) //Sprawdzenie czy odczytana linia zawiera interesuj¹ce s³owa kluczowe
				bufor2 = buf; //Je¿eli nie jest pusta to skopiowanie do drugiego bufora celem posiadania dwóch ostatnich linijek tekstu bêd¹cego w pliku
			getline(log, buf); //Odczyt ca³ej lini z pliku
		}
		if ((buf.empty()) || (!((buf.find("Posiadasz") != string::npos) || (buf.find("Wylosowano") != string::npos) || (buf.find("Obstawiono za") != string::npos) || (buf.find("Gra rozpoczeta dnia") != string::npos)))) //Sprawdzenie czy linia w buforze jest pusta lub czy nieznaleziono interesuj¹cego s³owa kluczowego
			buf = bufor2; //je¿eli jest pusta to zast¹pienie jej poprzedni¹ lini¹ tekstu z pliku
		if (buf.find("Posiadasz") != string::npos) //Sprawdzenie czy w ostatniej niepustej lini znajduj¹ siê s³owa œwiadcz¹ce o skoñczeniu rundy
		{
			co_kontynuowaæ = 'n'; //Je¿eli siê znajduj¹ to przypisanie znaku rozpoczêcia rundy od pocz¹tku
			auto pocz¹tek = buf.size(); //Utworzenie i przypisanie do zmiennej wskazuj¹cej pocz¹tek tekst pozycji ostatniego znaku tekstu o kwocie pieniêdzy któr¹ posiada jeszcze gracz, typ zmiennej auto wsazuje, ¿e kompilator sam wybierze typ zmiennej
			while (buf[pocz¹tek] != ' ' && pocz¹tek > 0) --pocz¹tek; //Poszukiwanie od koñca spacji po której jest kwota pieniêdzy któr¹ posiada jeszcze gracz
			++pocz¹tek; //Kwota jest na nastêpnym znaku wiêc przesuniêcie o jeden znak do przodu
			string buf2 = buf; //Utworzenie bufora pomocniczego do ciêcia tekstu i w³o¿enie do niego wczeœniej odczytanego tekstu
			buf2.erase(0, pocz¹tek); //Usuniêcie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna³ siê liczb¹
			buf2.erase(buf2.size() - 1, 1); //Usuniêcie z bufora pomocniczego znaku dolara z prawej strony
			istringstream numers(buf2); //Utorzenie typu do zamiany tekstu na liczbê
			numers >> iloœæ_pieniêdzy; //Zamiana liczby w tekœcie na wartoœæ w zmiennnej liczbowej
		}
		else if (buf.find("Wylosowano") != string::npos) //Sprawdzenie czy w ostatniej niepustej lini znajduj¹ siê s³owa œwiadcz¹ce o wylosowaniu liczby
		{
			co_kontynuowaæ = 'w'; //Je¿eli siê znajduj¹ to przypisanie znaku rozpoczêcia rundy od sprawdzenia wygranej
			size_t pocz¹tek = 0; //Utworzenie i przypisanie zera do zmiennej wskazuj¹cej pocz¹tek tekst o wylosowanej liczbie
			while (buf[pocz¹tek] != 'y' && pocz¹tek < buf.size()) ++pocz¹tek; //Poszukiwanie od pocz¹tku litery y która wystêpuje w wyrazie po którym jest wylosowana liczba
			pocz¹tek += 10; //Przesuniêcie o +10 pozycji pocz¹tku tekstu o po której jest wylosowana liczba
			string buf2 = buf; //Utworzenie bufora pomocniczego do ciêcia tekstu i w³o¿enie do niego wczeœniej odczytanego tekstu
			buf2.erase(0, pocz¹tek); //Usuniêcie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna³ siê liczb¹
			wylosowana_liczba = atoi(buf2.c_str()); //Zamiana liczby w tekœcie na wartoœæ w zmiennnej liczbowej
			pocz¹tek = 0; //Przypisanie zera do zmiennej wskazuj¹cej pocz¹tek tekst o typie zak³adu
			while (buf[pocz¹tek] != 'd' && pocz¹tek < buf.size()) ++pocz¹tek;
			pocz¹tek += 2;  //Przesuniêcie o +2 pozycji pocz¹tku tekstu o po której jest typ zak³adu
			buf2 = buf; //Utworzenie bufora pomocniczego do ciêcia tekstu i w³o¿enie do niego wczeœniej odczytanego tekstu
			buf2.erase(0, pocz¹tek); //Usuniêcie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna³ siê liczb¹
			buf2.erase(buf2.find(" Wylosowano"), string::npos); //Usuniêcie z bufora pomocniczego tekstu z prawej strony, aby tekst koñczy³ siê nazw¹ typu zak³adu
			typ_zak³adu = buf2; //Przypisanie do zmiennej przechowywuj¹cej typ zak³adu wczytanego typu zak³adu
			buf.erase(buf.find("Obstawiono zaklad"), string::npos); //Usuniêcie wszystkiego w prawo razem z wyszukanym tekstem
			pocz¹tek = 0; //Przypisanie zera do zmiennej wskazuj¹cej pocz¹tek tekst o kwocie zak³adu
			if (buf[12] == 'a') { pocz¹tek = 14; } //Sprawdzenie czy na pozycji 12 teksty znajduje siê litera a œwiadcz¹ca o wyrazie po którym jest kwota zak³adu, je¿eli tak to pozycja pocz¹tkowa tekstu wynosi 14
			else //Je¿eli nie to
			{
				while (buf[pocz¹tek] != 'z' && pocz¹tek < buf.size()) ++pocz¹tek; //Poszukanie litery z œwiadcz¹cej o wyrazie po którym jest kwota zak³adu
				pocz¹tek += 3; //Po znalezienu z przesuwamy pozycje +3
			}
			size_t koniec = pocz¹tek + 1; //Przypisanie do zmiennej pozycji pocz¹tku +1 wskazuj¹cej koniec tekst o kwocie zak³adu
			while (buf[koniec] != '$' && koniec < buf.size()) ++koniec; //Poszukujemy znaku dolara przed którym jest kwota zak³adu
			buf2 = buf; //Utworzenie bufora pomocniczego do ciêcia tekstu i w³o¿enie do niego wczeœniej odczytanego tekstu
			buf2.erase(koniec, string::npos); //Usuniêcie z bufora pomocniczego tekstu z prawej strony, aby tekst koñczy³ siê liczb¹
			buf2.erase(0, pocz¹tek); //Usuniêcie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna³ siê liczb¹
			kwota_zak³adu = atoi(buf2.c_str()); //Zamiana liczby w tekœcie na wartoœæ w zmiennnej liczbowej
			pocz¹tek = bufor2.size(); //Utworzenie i przypisanie do zmiennej wskazuj¹cej pocz¹tek tekst o kwocie pieniêdzy któr¹ posiada jeszcze gracz
			while (bufor2[pocz¹tek] != ' ' && pocz¹tek > 0) --pocz¹tek; //Poszukiwanie od koñca spacji po której jest kwota pieniêdzy któr¹ posiada jeszcze gracz
			++pocz¹tek; //Kwota jest na nastêpnym znaku wiêc przesuniêcie o jeden znak do przodu
			if (bufor2.find("Gra rozpoczeta") == string::npos) //Zabezpieczenie przed wczytymaniem iloœci pozosta³ych pieniêdzy jak siê nie rozegra³o pe³nej rundy
			{
				buf2 = move(bufor2); //Przeniesienie do bufora pomocniczego do ciêcia tekstu i w³o¿enie do niego linie o jedn¹ wczeœniej wczeœniej odczytanego tekstu
				buf2.erase(0, pocz¹tek); //Usuniêcie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna³ siê liczb¹
				buf2.erase(buf2.size() - 1, 1); //Usuniêcie z bufora pomocniczego znaku dolara z prawej strony
				sscanf_s(buf2.c_str(), "%d", &iloœæ_pieniêdzy); //Zamiana liczby w tekœcie na wartoœæ w zmiennnej liczbowej
			}
		}
		else if (buf.find("Obstawiono zaklad") != string::npos) //Sprawdzenie czy w ostatniej niepustej lini znajduj¹ siê s³owa œwiadcz¹ce o typie obstawionego zak³adu
		{
			co_kontynuowaæ = 't'; //Je¿eli siê znajduj¹ to przypisanie znaku rozpoczêcia rundy od wylosowania liczby
			size_t pocz¹tek = 0; //Utworzenie i przypisanie zera do zmiennej wskazuj¹cej pocz¹tek tekst o typie zak³adu
			while (buf[pocz¹tek] != 'd' && pocz¹tek < buf.size()) ++pocz¹tek;
			pocz¹tek += 2; //Przesuniêcie pozycji pocz¹tku tekstu o 2 po której jest typ zak³adu
			string buf2 = buf; //Utworzenie bufora pomocniczego do ciêcia tekstu i w³o¿enie do niego wczeœniej odczytanego tekstu
			buf2.erase(0, pocz¹tek); //Usuniêcie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna³ siê liczb¹
			typ_zak³adu = buf2; //Przypisanie do zmiennej przechowywuj¹cej typ zak³adu wczytanego typu zak³adu
			buf.erase(buf.find("Obstawiono zaklad"), string::npos); //Usuniêcie wszystkiego w prawo razem z wyszukanym tekstem
			pocz¹tek = 0; //Przypisanie zera do zmiennej wskazuj¹cej pocz¹tek tekst o kwocie zak³adu
			if (buf[12] == 'a') pocz¹tek = 14; //Sprawdzenie czy na pozycji 12 teksty znajduje siê litera a œwiadcz¹ca o wyrazie po którym jest kwota zak³adu, je¿eli tak to pozycja pocz¹tkowa tekstu wynosi 14
			else //Je¿eli nie to
			{
				while (buf[pocz¹tek] != 'z' && pocz¹tek < buf.size()) ++pocz¹tek; //Poszukanie litery z œwiadcz¹cej o wyrazie po którym jest kwota zak³adu
				pocz¹tek += 3; //Po znalezienu z przesuwamy pozycje +3
			}
			size_t koniec = pocz¹tek + 1; //Przypisanie do zmiennej pozycji pocz¹tku +1 wskazuj¹cej koniec tekst o kwocie zak³adu
			while (buf[koniec] != '$' && koniec < buf.size()) ++koniec; //Pêtla poszukuj¹ca znaku dolara, pêtla koñczy siê znalezieniem znaku dolara
			buf2 = buf; //W³o¿enie do bufora pomocniczego do ciêcia tekstu wczeœniej odczytanego tekstu
			buf2.erase(koniec, string::npos); //Usuniêcie z bufora pomocniczego tekstu z prawej strony, aby tekst koñczy³ siê liczb¹
			buf2.erase(0, pocz¹tek); //Usuniêcie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna³ siê liczb¹
			kwota_zak³adu = atoi(buf2.c_str()); //Zamiana liczby w tekœcie na wartoœæ w zmiennnej liczbowej
			pocz¹tek = bufor2.size(); //Utworzenie i przypisanie do zmiennej wskazuj¹cej pocz¹tek tekst o kwocie pieniêdzy któr¹ posiada jeszcze gracz
			while (bufor2[pocz¹tek] != ' ' && pocz¹tek > 0) --pocz¹tek; //Poszukiwanie od koñca spacji po której jest kwota pieniêdzy któr¹ posiada jeszcze gracz
			++pocz¹tek; //Kwota jest na nastêpnym znaku wiêc przesuniêcie o jeden znak do przodu
			if (bufor2.find("Gra rozpoczeta") == string::npos) //Zabezpieczenie przed wczytymaniem iloœci pozosta³ych pieniêdzy jak siê nie rozegra³o pe³nej rundy
			{
				buf2 = move(bufor2); //Przeniesienie do bufora pomocniczego do ciêcia tekstu i w³o¿enie do niego linie o jedn¹ wczeœniej wczeœniej odczytanego tekstu
				buf2.erase(0, pocz¹tek); //Usuniêcie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna³ siê liczb¹
				buf2.erase(buf2.size() - 1, 1); //Usuniêcie z bufora pomocniczego znaku dolara z prawej strony
				sscanf_s(buf2.c_str(), "%d", &iloœæ_pieniêdzy); //Zamiana liczby w tekœcie na wartoœæ w zmiennnej liczbowej
			}
		}
		else if (buf.find("Obstawiono za") != string::npos) //Sprawdzenie czy w ostatniej niepustej lini znajduj¹ siê s³owa œwiadcz¹ce o kwocie obstawionego zak³adu
		{
			co_kontynuowaæ = 'k';  //Je¿eli siê znajduj¹ to przypisanie znaku rozpoczêcia rundy od zapytania o typ zak³adu
			size_t pocz¹tek = 0; //Utworzenie i przypisanie do zmiennej wskazuj¹cej pocz¹tek tekst o kwocie pieniêdzy któr¹ posiada jeszcze gracz
			if (buf[12] == 'a') { pocz¹tek = 14; } //Sprawdzenie czy na pozycji 12 teksty znajduje siê litera a œwiadcz¹ca o wyrazie po którym jest kwota zak³adu, je¿eli tak to pozycja pocz¹tkowa tekstu wynosi 14
			else //Je¿eli nie to
			{
				while (buf[pocz¹tek] != 'z' && pocz¹tek < buf.size()) ++pocz¹tek; //Poszukanie litery z œwiadcz¹cej o wyrazie po którym jest kwota zak³adu
				pocz¹tek += 3; //Po znalezienu z przesuwamy pozycje +3
			}
			size_t koniec = pocz¹tek + 1; //Utworzenie i przypisanie do zmiennej pozycji pocz¹tku +1 wskazuj¹cej koniec tekst o kwocie zak³adu
			while (buf[koniec] != '$' && koniec < buf.size()) ++koniec; //Pêtla szukaj¹ca znaku dolara
			string buf2 = buf; //Utworzenie bufora pomocniczego do ciêcia tekstu i w³o¿enie do niego wczeœniej odczytanego tekstu
			buf2.erase(koniec, string::npos); //Usuniêcie z bufora pomocniczego tekstu z prawej strony, aby tekst koñczy³ siê liczb¹
			buf2.erase(0, pocz¹tek); //Usuniêcie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna³ siê liczb¹
			kwota_zak³adu = atoi(buf2.c_str()); //Zamiana liczby w tekœcie na wartoœæ w zmiennnej liczbowej
			pocz¹tek = bufor2.size(); //Utworzenie i przypisanie do zmiennej wskazuj¹cej pocz¹tek tekst o kwocie pieniêdzy któr¹ posiada jeszcze gracz
			while (bufor2[pocz¹tek] != ' ' && pocz¹tek > 0) --pocz¹tek; //Poszukiwanie od koñca spacji po której jest kwota pieniêdzy któr¹ posiada jeszcze gracz
			++pocz¹tek; //Kwota jest na nastêpnym znaku wiêc przesuniêcie o jeden znak do przodu
			if (bufor2.find("Gra rozpoczeta") == string::npos) //Zabezpieczenie przed wczytymaniem iloœci pozosta³ych pieniêdzy jak siê nie rozegra³o pe³nej rundy
			{
				buf2 = move(bufor2); //Przeniesienie do bufora pomocniczego do ciêcia tekstu i w³o¿enie do niego linie o jedn¹ wczeœniej wczeœniej odczytanego tekstu
				buf2.erase(0, pocz¹tek); //Usuniêcie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna³ siê liczb¹
				buf2.erase(buf2.size() - 1, 1); //Usuniêcie z bufora pomocniczego znaku dolara z prawej strony
				sscanf_s(buf2.c_str(), "%d", &iloœæ_pieniêdzy); //Zamiana liczby w tekœcie na wartoœæ w zmiennnej liczbowej
			}
		}
		else if (buf.find("Gra rozpoczeta dnia") != string::npos) //Sprawdzenie czy w ostatniej niepustej lini znajduj¹ siê s³owa œwiadcz¹ce o rozpoczêciu nowej gry
			co_kontynuowaæ = 'n'; //Je¿eli siê znajduj¹ to przypisanie znaku rozpoczêcia rundy od pocz¹tku
		else //Je¿eli coœ pójdzie nie tak, to warunek aby gra siê niewysypa³a
			co_kontynuowaæ = 'n'; //Je¿eli siê znajduj¹ to przypisanie znaku rozpoczêcia rundy od pocz¹tku
		log.close(); //Zamkniêcie pliku logu ogólnego
		log.open("log_aktualny.txt", ios::out | ios::app); //Ponowne wczytanie pliku, teraz tylko do odczytu i ustawienie kursora zapisu na koniec pliku
	}
	else
	{
		co_kontynuowaæ = 'n'; //Przypisanie znaku rozpoczêcia rundy od pocz¹tku
		log.open("log_aktualny.txt", ios::out); //Otwarcie pliku w trybie tylko do zapisu
		GetSystemTime(&Czas); //Pobieranie aktualnej daty i czasu z zegara systemowego

		string buf;
		buf += "Gra rozpoczeta dnia " + ((Czas.wDay < 10) ? ('0' + to_string(Czas.wDay)) : (to_string(Czas.wDay))) + '.' + ((Czas.wMonth < 10) ? ('0' + to_string(Czas.wMonth)) : (to_string(Czas.wMonth))) + '.' + to_string(Czas.wYear) + " o godzinie "; //Wpisanie do bufora zapisu danych o dniu,miesi¹cu i roku wraz z dodatkowymi zerami dla formatowania
		if (Czas.wHour < 10) buf += '0'; //Wpisanie do bufora zapisu znaku zera dla równego formatowania godzinny je¿eli godzina jest minejsza ni¿ 10
		buf += to_string(Czas.wHour) + ':'; //Wpisanie do bufora zapisu znaku : dla rozdzielenia godzin od minut
		if (Czas.wMinute < 10) buf += '0'; //Wpisanie do bufora zapisu znaku zera dla równego formatowania minut je¿eli minuty jest minejsze ni¿ 10 do pliku log_aktualny.txt
		buf += to_string(Czas.wMinute) + ':'; //Wpisanie do bufora zapisu znaku : dla rozdzielenia minut od sekund do pliku log_aktualny.txt
		if (Czas.wSecond < 10) buf += '0'; //Wpisanie do bufora zapisu znaku zera dla równego formatowania sekund je¿eli sekundy jest minejsza ni¿ 10 do pliku log_aktualny.txt
		buf += to_string(Czas.wSecond) + '\n'; // Wpisanie do bufora zapisu danych o sekundzie do pliku log_aktualny.txt

		log.write(buf.c_str(), buf.size()); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych

		buf.replace(buf.begin(), buf.begin() + 1, "Nowa g"); //Zamiana pierwszej litery bufora aby dodaæ na pocz¹tek stringa dopisek nowa
		log_ogólny.write(buf.c_str(), buf.size());  //Zapisanie do pliku log_ogólny.txt danych wpisanych do bufora danych

		log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
		log_ogólny.flush(); //Zapisanie do pliku log_ogólny.txt danych wpisanych do bufora danych
	}
}

void SprawdŸ_Pliki(const short & g³os_odczytu_numeru, const short & g³os_szybkoœæ_odczytu_numeru)
{
	if (Ustawienia.efekty_dŸwiêkowe == 1) //Je¿eli w³¹czono efekty dŸwiêkowe
	{
		if ((_access("Efekty_dŸwiêkowe", NULL))) //SprawdŸ czy nie ma folderu Efekty dŸwiêkowe
			CreateDirectory("Efekty_dŸwiêkowe", nullptr); //Je¿eli nie ma to utwórz go

		bool czy_pobierano = false; //Utworzenie zmiennej informuj¹c¹ czy rozpoczêto pobieranie plików
		bool czy_pobrano = true; //Utworzenie zmiennej informuj¹c¹ czy ostatnie pobieranie zakoñczy³o siê sukesem

		if ((_access("Efekty_dŸwiêkowe/bankrut.wav", NULL))) //Sprawdzenie czy plik nie istnieje
		{
			cout << "Rozpoczynam pobieranie brakuj¹cych plików efektów" << endl; //Poinformowaniu o rozpoczêciu pobierania
			czy_pobierano = true; //Zmiana zmiennej aby wiadomo, ¿e rozpoczêto pobieranie
			if (!Wyci¹gnij_z_Programu("Efekty_dŸwiêkowe/bankrut.wav", IDR_BANKRUT)) //Je¿eli nie uda³o wydobyæ siê z zasobów pliku bankrut.wav
			{
				const auto res = URLDownloadToFile(nullptr, "https://github.com/talez2709/Ruletka/raw/master/Ruletka/Efekty_d%C5%BAwi%C4%99kowe/bankrut.wav", "Efekty_dŸwiêkowe/bankrut.wav", 0, nullptr); //Rozpoczêcie pobierania pliku
				if (res != S_OK) //Je¿eli nie powiod³o siê pobieranie pliku
				{
					czy_pobrano = false; //Ustawienie zmiennej informuj¹cej o sukcesie pobierania na wartoœæ false
					cout << "Brak plików dla efektów dŸwiêkowych oraz nie mo¿na pobraæ danych, wy³¹czono efekty dŸwiêkowe muzyczne, w³¹czono efekty systemowe" << endl; //Poinformowanie o nieudanym pobieraniu i konsekwencji tego
					EfektyKompletne = false; //Wpisanie do zmiennej wartoœci false informuj¹cej o niekompletnych plikach audio
				}
			}
		}

		if (czy_pobrano) //Je¿eli ostatnie pobieranie zakoñczono prawid³owo
			if ((_access("Efekty_dŸwiêkowe/wygrana1.wav", NULL))) //Sprawdzenie czy plik nie istnieje
			{
				if (!czy_pobierano) //Sprawdzanie czy jakieœ pobieranie siê rozpocze³o
				{
					cout << "Rozpoczynam pobieranie brakuj¹cych plików efektów" << endl; //Poinformowaniu o rozpoczêciu pobierania
					czy_pobierano = true; //Zmiana zmiennej aby wiadomo, ¿e rozpoczêto pobieranie
				}
				if (!Wyci¹gnij_z_Programu("Efekty_dŸwiêkowe/wygrana1.wav", IDR_WYGRANA1)) //Je¿eli nie uda³o wydobyæ siê z zasobów pliku wygrana1.wav
				{
					const auto res = URLDownloadToFile(nullptr, "https://github.com/talez2709/Ruletka/raw/master/Ruletka/Efekty_d%C5%BAwi%C4%99kowe/wygrana1.wav", "Efekty_dŸwiêkowe/wygrana1.wav", 0, nullptr); //Rozpoczêcie pobierania pliku
					if (res != S_OK) //Je¿eli nie powiod³o siê pobieranie pliku
					{
						czy_pobrano = false; //Ustawienie zmiennej informuj¹cej o sukcesie pobierania na wartoœæ false
						cout << "Brak plików dla efektów dŸwiêkowych oraz nie mo¿na pobraæ danych, wy³¹czono efekty dŸwiêkowe muzyczne, w³¹czono efekty systemowe" << endl; //Poinformowanie o nieudanym pobieraniu i konsekwencji tego
						EfektyKompletne = false; //Wpisanie do zmiennej wartoœci false informuj¹cej o niekompletnych plikach audio
					}
				}
			}

		if (czy_pobrano) //Je¿eli ostatnie pobieranie zakoñczono prawid³owo
			if ((_access("Efekty_dŸwiêkowe/wygrana2.wav", NULL))) //Sprawdzenie czy plik nie istnieje
			{
				if (!czy_pobierano) //Sprawdzanie czy jakieœ pobieranie siê rozpocze³o
				{
					cout << "Rozpoczynam pobieranie brakuj¹cych plików efektów" << endl; //Poinformowaniu o rozpoczêciu pobierania
					czy_pobierano = true; //Zmiana zmiennej aby wiadomo, ¿e rozpoczêto pobieranie
				}
				if (!Wyci¹gnij_z_Programu("Efekty_dŸwiêkowe/wygrana2.wav", IDR_WYGRANA2)) //Je¿eli nie uda³o wydobyæ siê z zasobów pliku wygrana2.wav
				{
					const auto res = URLDownloadToFile(nullptr, "https://github.com/talez2709/Ruletka/raw/master/Ruletka/Efekty_d%C5%BAwi%C4%99kowe/wygrana2.wav", "Efekty_dŸwiêkowe/wygrana2.wav", 0, nullptr); //Rozpoczêcie pobierania pliku
					if (res != S_OK) //Je¿eli nie powiod³o siê pobieranie pliku
					{
						czy_pobrano = false; //Ustawienie zmiennej informuj¹cej o sukcesie pobierania na wartoœæ false
						cout << "Brak plików dla efektów dŸwiêkowych oraz nie mo¿na pobraæ danych, wy³¹czono efekty dŸwiêkowe muzyczne, w³¹czono efekty systemowe" << endl; //Poinformowanie o nieudanym pobieraniu i konsekwencji tego
						EfektyKompletne = false; //Wpisanie do zmiennej wartoœci false informuj¹cej o niekompletnych plikach audio
					}
				}
			}

		if (czy_pobrano) //Je¿eli ostatnie pobieranie zakoñczono prawid³owo
			if ((_access("Efekty_dŸwiêkowe/zwielokrotnenie.wav", NULL))) //Sprawdzenie czy plik nie istnieje
			{
				if (!czy_pobierano) //Sprawdzanie czy jakieœ pobieranie siê rozpocze³o
				{
					cout << "Rozpoczynam pobieranie brakuj¹cych plików efektów" << endl; //Poinformowaniu o rozpoczêciu pobierania
					czy_pobierano = true; //Zmiana zmiennej aby wiadomo, ¿e rozpoczêto pobieranie
				}
				if (!Wyci¹gnij_z_Programu("Efekty_dŸwiêkowe/zwielokrotnenie.wav", IDR_ZWIELOKROTNIENIE)) //Je¿eli nie uda³o wydobyæ siê z zasobów pliku zwielokrotnienie.wav
				{
					const auto res = URLDownloadToFile(nullptr, "https://github.com/talez2709/Ruletka/raw/master/Ruletka/Efekty_d%C5%BAwi%C4%99kowe/zwielokrotnenie.wav", "Efekty_dŸwiêkowe/zwielokrotnenie.wav", 0, nullptr); //Rozpoczêcie pobierania pliku
					if (res != S_OK) //Je¿eli nie powiod³o siê pobieranie pliku
					{
						czy_pobrano = false; //Ustawienie zmiennej informuj¹cej o sukcesie pobierania na wartoœæ false
						cout << "Brak plików dla efektów dŸwiêkowych oraz nie mo¿na pobraæ danych, wy³¹czono efekty dŸwiêkowe muzyczne, w³¹czono efekty systemowe" << endl; //Poinformowanie o nieudajnym pobieraniu i konsekwencji tego
						EfektyKompletne = false; //Wpisanie do zmiennej wartoœci false informuj¹cej o niekompletnych plikach audio
					}
				}
			}

		if (czy_pobierano && czy_pobrano) cout << "Pobrano brakuj¹ce pliki efektów" << endl; //Poinformowanie o ukoñczonu pobierania plików
	}

	if (g³os_odczytu_numeru > 0) //Je¿eli w³¹czono odczyt g³osowy
	{
		G³osyKompletne = true; //Ustawienie domyœnej wartoœci zmiennej globalnej G³osyKompletne

		G³os = "G³os/"; //Wpisanie do zmiennej G³os pocz¹tku œcie¿ki do pliku z g³osem
		G³os += Nazwa_g³osu[g³os_odczytu_numeru]; //U¿ycie tablicy do wpisania odpowiedniej nazwy g³osu do zmiennej G³os
		G³os += "_"; //Dodanie do zmiennej podkreœlenia odzielaj¹cego nazwê od szybkoœci
		G³os += '0' + g³os_szybkoœæ_odczytu_numeru; //Dodanie do zmiennej szybkoœci mowy
		G³os += "/"; //Dodanie do zmiennej ukoœnika który odziela nazwê folderu od pliku

		const string link = "https://github.com/talez2709/Ruletka/raw/master/Ruletka/G%C5%82os/"; //Zmienna przechowywuj¹ca pocz¹tek strony do pobierania g³osu

		string g³os2 = G³os.substr(5, string::npos); //Utworzenie zmiennej typu string do celów operowania adresem przy pobieraniu danych i w³o¿enie do zmiennej napisu z zmiennej G³os z pominiêciem 5 pierwszych znaków

		const string g³os3 = g³os2.substr(0, g³os2.size() - 1); //Utorzenie stringa obez ostatniego znaku g³os2

		if (!(_access("Do_u¿ytkownika.txt", NULL))) //Sprawdzam czy plik istnieje
		{
			if ( //Je¿eli tak to sprawdzam czy wszystkie pliki s¹ pobrane
				(!(_access((G³os + "p.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk p
				(!(_access((G³os + "n.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk n
				(!(_access((G³os + "r.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk r
				(!(_access((G³os + "b.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk b
				(!(_access((G³os + "g.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk g
				(!(_access((G³os + "d.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk d
				(!(_access((G³os + "win.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk win
				(!(_access((G³os + "k1.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk k1
				(!(_access((G³os + "k2.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk k2
				(!(_access((G³os + "k3.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk k3
				(!(_access((G³os + "w1.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk w1
				(!(_access((G³os + "w2.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk w2
				(!(_access((G³os + "w3.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk w3
				(!(_access((G³os + "w4.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk w4
				(!(_access((G³os + "w5.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk w5
				(!(_access((G³os + "w6.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk w6
				(!(_access((G³os + "w7.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk w7
				(!(_access((G³os + "w8.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk w8
				(!(_access((G³os + "w9.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk w9
				(!(_access((G³os + "w10.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk w10
				(!(_access((G³os + "w11.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk w11
				(!(_access((G³os + "w12.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk w12
				(!(_access((G³os + "0.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 0
				(!(_access((G³os + "1.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 1
				(!(_access((G³os + "2.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 2
				(!(_access((G³os + "3.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 3
				(!(_access((G³os + "4.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 4
				(!(_access((G³os + "5.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 5
				(!(_access((G³os + "6.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 6
				(!(_access((G³os + "7.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 7
				(!(_access((G³os + "8.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 8
				(!(_access((G³os + "9.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 9
				(!(_access((G³os + "10.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 10
				(!(_access((G³os + "11.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 11
				(!(_access((G³os + "12.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 12
				(!(_access((G³os + "13.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 13
				(!(_access((G³os + "14.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 14
				(!(_access((G³os + "15.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 15
				(!(_access((G³os + "16.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 16
				(!(_access((G³os + "17.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 17
				(!(_access((G³os + "18.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 18
				(!(_access((G³os + "19.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 19
				(!(_access((G³os + "20.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 20
				(!(_access((G³os + "21.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 21
				(!(_access((G³os + "22.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 22
				(!(_access((G³os + "23.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 23
				(!(_access((G³os + "24.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 24
				(!(_access((G³os + "25.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 25
				(!(_access((G³os + "26.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 26
				(!(_access((G³os + "27.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 27
				(!(_access((G³os + "28.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 28
				(!(_access((G³os + "29.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 29
				(!(_access((G³os + "30.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 30
				(!(_access((G³os + "31.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 31
				(!(_access((G³os + "32.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 32
				(!(_access((G³os + "33.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 33
				(!(_access((G³os + "34.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 34
				(!(_access((G³os + "35.wav").c_str(), NULL))) && //Sprawdzam czy jest dŸwiêk 35
				(!(_access((G³os + "36.wav").c_str(), NULL))) //Sprawdzam czy jest dŸwiêk 36
				)
			{
				cout << "Pobrano wszystkie pliki g³osów" << endl; //Poinformowanie, ¿e pobrano wszystkie pliki g³osów
				DeleteFile("Do_u¿ytkownika.txt"); //Usuwam plik Do_u¿ytkownika.txt
				Usuñ_Folder_Wypakowany_i_Winrar(g³os2); //Usniêcie folderu z wypakowanymi elementami i programu do wypakowywania
				return; //Wyjœcie z funkcji
			}

			G³osyKompletne = false; //Zmieniam wartoœæ zmiennej na false poniewa¿ nie ma wszystkich plików g³osu
			cout << "Wy³¹czono g³os z powodu braku plików" << endl; //Informujê o tym u¿ytkownika
			Usuñ_Folder_Wypakowany_i_Winrar(g³os2); //Usniêcie folderu z wypakowanymi elementami i programu do wypakowywania
			return; //Wyjœcie z funkcji
		}

		if ((_access("G³os", NULL))) //SprawdŸ czy nie ma folderu G³os
			CreateDirectory("G³os", nullptr); //Je¿eli nie ma to utwórz go
		if ((_access((G³os).c_str(), NULL))) //SprawdŸ czy nie ma w folderze G³os podfolderu z nazw¹ i szybkoœci¹ g³osu
		{
			CreateDirectory((G³os).c_str(), nullptr); //Je¿eli nie ma to utwórz go
			cout << "Rozpoczynam pobieranie brakuj¹cych plików g³osu " << g³os3 << endl; //Poinformowaniu o rozpoczêciu pobierania
			Wyci¹gnij_z_Programu((g³os3 + ".rar"), Numer_zasobu_rar.at(g³os3)); //Wyci¹gniêcie z zasobów folderu rar z g³osem
			Wypakuj_Rar(g³os3 + ".rar"); //Wypakowanie folderu rar z g³osem
			vector<thread> vec_thr; //Utworzenie kontenera vector na w¹tki
			stack<string> stos_nazw_plików; //Utworzenie kontenera stos na nazwy plików
			stos_nazw_plików.push("p"); stos_nazw_plików.push("n"); stos_nazw_plików.push("r"); stos_nazw_plików.push("b"); stos_nazw_plików.push("d"); stos_nazw_plików.push("g"); stos_nazw_plików.push("k1"); stos_nazw_plików.push("k2"); stos_nazw_plików.push("k3"); stos_nazw_plików.push("w1"); stos_nazw_plików.push("w2"); stos_nazw_plików.push("w3"); stos_nazw_plików.push("w4"); stos_nazw_plików.push("w5"); stos_nazw_plików.push("w6"); stos_nazw_plików.push("w7"); stos_nazw_plików.push("w8"); stos_nazw_plików.push("w9"); stos_nazw_plików.push("w10"); stos_nazw_plików.push("w11"); stos_nazw_plików.push("w12"); stos_nazw_plików.push("0"); stos_nazw_plików.push("1"); stos_nazw_plików.push("2"); stos_nazw_plików.push("3"); stos_nazw_plików.push("4"); stos_nazw_plików.push("5"); stos_nazw_plików.push("6"); stos_nazw_plików.push("7"); stos_nazw_plików.push("8"); stos_nazw_plików.push("9"); stos_nazw_plików.push("10"); stos_nazw_plików.push("11"); stos_nazw_plików.push("12"); stos_nazw_plików.push("13"); stos_nazw_plików.push("14"); stos_nazw_plików.push("15"); stos_nazw_plików.push("16"); stos_nazw_plików.push("17"); stos_nazw_plików.push("18"); stos_nazw_plików.push("19"); stos_nazw_plików.push("20"); stos_nazw_plików.push("21"); stos_nazw_plików.push("22"); stos_nazw_plików.push("23"); stos_nazw_plików.push("24"); stos_nazw_plików.push("25"); stos_nazw_plików.push("26"); stos_nazw_plików.push("27"); stos_nazw_plików.push("28"); stos_nazw_plików.push("29"); stos_nazw_plików.push("30"); stos_nazw_plików.push("31"); stos_nazw_plików.push("32"); stos_nazw_plików.push("33"); stos_nazw_plików.push("34"); stos_nazw_plików.push("35"); stos_nazw_plików.push("36"); stos_nazw_plików.push("win"); //Umieszczenie na stosie nazw plików dŸwiêkowy do przeniesienia

			while (!stos_nazw_plików.empty()) //Pêtla do czasu wyczyszczenia stosu
			{
				thread thr([](string a, const string & g³os2, const string & link)->void {if (!Przenieœ_Plik(g³os2 + a + ".wav", G³os + a + ".wav")) { //U¿ycie wyra¿enia lambda aby utworzyæ w¹tki do przenoszenia plików
					const auto res = URLDownloadToFile(nullptr, (link + g³os2 + a + ".wav").c_str(), (G³os + a + ".wav").c_str(), 0, nullptr); if (res != S_OK) { //Je¿eli nieuda³o siê wydobyæ z zasobów pliku to spróbuj pobraæ plik
						if (G³osyKompletne) { //Je¿eli nieuda³o siê pobraæ pliku
							cout << "Brak plików dla g³osu oraz nie mo¿na pobraæ danych, wy³¹czono odczytywanie wyniku" << endl; G³osyKompletne = false; Usuñ_Folder_Wypakowany_i_Winrar(g³os2); return; //Poinformuj o tym u¿ytkownika
						}
					}
				}}, stos_nazw_plików.top(), ref(g³os2), ref(link)); //utworzenie w¹tku do przenoszenia pliku
				vec_thr.push_back(move(thr)); //Przeniesienie w¹tku do vectora
				stos_nazw_plików.pop(); //Zdjêcie elementu z wieszcho³ka stosu
			}
			for (auto& t : vec_thr) t.join(); //Poczekanie na zakoñczenie wszystkich w¹tków
			if (G³osyKompletne) cout << endl << "Pobrano brakuj¹ce pliki g³osów" << endl; //Poinformowanie o ukoñczonu pobierania plików , je¿eli pobra³o siê wszystkie pliki
			Usuñ_Folder_Wypakowany_i_Winrar(g³os2); //Usniêcie folderu z wypakowanymi elementami i programu do wypakowywania
			Wyci¹gnij_z_Programu("Do_u¿ytkownika.txt", IDR_RCDATA46); //Wyci¹gniêcie z programu pliku informuj¹cego o mo¿liwym b³êdzie
			ShellExecuteA(nullptr, nullptr, "Ruletka.exe", nullptr, nullptr, SW_SHOW); //Ponowne uruchomienie programu
			const auto PID = GetCurrentProcessId(); //Pobranie numeru aktualnego procesu
			if (!TerminateProcess(PID, 123)) //Zamkniêcie bie¿¹cego procesu
				cout << "Nie uda³o siê ponownie uruchomiæ programu, mog¹ pojawiæ siê b³êdy z wyœwietlaniem tekstu" << endl; //Poinformowanie o mo¿liwym b³êdzie
		}

		bool czy_pobierano = false; //Utworzenie zmiennej logicznej informuj¹cej czy jakieœ pobieranie siê rozpocze³o

		if ((_access((G³os + "p.wav").c_str(), NULL))) //Sprawdzenie czy plik nie istnieje
		{
			cout << "Rozpoczynam pobieranie brakuj¹cych plików g³osu" << endl; //Poinformowaniu o rozpoczêciu pobierania
			czy_pobierano = true; //Zmiana zmiennej aby wiadomo, ¿e rozpoczêto pobieranie
			Wyci¹gnij_z_Programu((g³os3 + ".rar"), Numer_zasobu_rar.at(g³os3)); //Wyci¹gniêcie z zasobów folderu rar z g³osem
			Wypakuj_Rar(g³os3 + ".rar"); //Wypakowanie folderu rar z g³osem
			if (!Przenieœ_Plik(g³os2 + "p.wav", G³os + "p.wav")) //Je¿eli nie uda³o siê przenieœæ wypakowanego pliku
			{
				const auto res = URLDownloadToFile(nullptr, (link + g³os2 + "p.wav").c_str(), (G³os + "p.wav").c_str(), 0, nullptr); //Rozpoczêcie pobierania pliku
				if (res != S_OK) //Je¿eli nie powiod³o siê pobieranie pliku
				{
					cout << "Brak plików dla g³osu oraz nie mo¿na pobraæ danych, wy³¹czono odczytywanie wyniku" << endl; //Poinformowanie o nieudajnym pobieraniu i konsekwencji tego
					G³osyKompletne = false; //Wpisanie do zmiennej wartoœci false informuj¹cej o niekompletnych plikach audio
					Usuñ_Folder_Wypakowany_i_Winrar(g³os2); //Usniêcie folderu z wypakowanymi elementami i programu do wypakowywania
					return; //Wyjœcie z funkcji poniewa¿ nie ma sensu sprawdzania dalej
				}
			}
		}

		if ((_access((G³os + "n.wav").c_str(), NULL))) //Sprawdzenie czy plik nie istnieje
		{
			if (!czy_pobierano) //Sprawdzanie czy jakieœ pobieranie siê nie rozpocze³o
			{
				cout << "Rozpoczynam pobieranie brakuj¹cych plików g³osu" << endl; //Poinformowaniu o rozpoczêciu pobierania
				czy_pobierano = true; //Zmiana zmiennej aby wiadomo, ¿e rozpoczêto pobieranie
				Wyci¹gnij_z_Programu((g³os3 + ".rar"), Numer_zasobu_rar.at(g³os3)); //Wyci¹gniêcie z zasobów folderu rar z g³osem
				Wypakuj_Rar(g³os3 + ".rar"); //Wypakowanie folderu rar z g³osem
			}
			if (!Przenieœ_Plik(g³os2 + "n.wav", G³os + "n.wav")) //Je¿eli nie uda³o siê przenieœæ wypakowanego pliku
			{
				const auto res = URLDownloadToFile(nullptr, (link + g³os2 + "n.wav").c_str(), (G³os + "n.wav").c_str(), 0, nullptr); //Rozpoczêcie pobierania pliku
				if (res != S_OK) //Je¿eli nie powiod³o siê pobieranie pliku
				{
					cout << "Brak plików dla g³osu oraz nie mo¿na pobraæ danych, wy³¹czono odczytywanie wyniku" << endl; //Poinformowanie o nieudajnym pobieraniu i konsekwencji tego
					G³osyKompletne = false; //Wpisanie do zmiennej wartoœci false informuj¹cej o niekompletnych plikach audio
					Usuñ_Folder_Wypakowany_i_Winrar(g³os2); //Usniêcie folderu z wypakowanymi elementami i programu do wypakowywania
					return; //Wyjœcie z funkcji poniewa¿ nie ma sensu sprawdzania dalej
				}
			}
		}

		if ((_access((G³os + "r.wav").c_str(), NULL))) //Sprawdzenie czy plik nie istnieje
		{
			if (!czy_pobierano) //Sprawdzanie czy jakieœ pobieranie siê nie rozpocze³o
			{
				cout << "Rozpoczynam pobieranie brakuj¹cych plików g³osu" << endl; //Poinformowaniu o rozpoczêciu pobierania
				czy_pobierano = true; //Zmiana zmiennej aby wiadomo, ¿e rozpoczêto pobieranie
				Wyci¹gnij_z_Programu((g³os3 + ".rar"), Numer_zasobu_rar.at(g³os3)); //Wyci¹gniêcie z zasobów folderu rar z g³osem
				Wypakuj_Rar(g³os3 + ".rar"); //Wypakowanie folderu rar z g³osem
			}
			if (!Przenieœ_Plik(g³os2 + "r.wav", G³os + "r.wav")) //Je¿eli nie uda³o siê przenieœæ wypakowanego pliku
			{
				const auto res = URLDownloadToFile(nullptr, (link + g³os2 + "r.wav").c_str(), (G³os + "r.wav").c_str(), 0, nullptr); //Rozpoczêcie pobierania pliku
				if (res != S_OK) //Je¿eli nie powiod³o siê pobieranie pliku
				{
					cout << "Brak plików dla g³osu oraz nie mo¿na pobraæ danych, wy³¹czono odczytywanie wyniku" << endl; //Poinformowanie o nieudajnym pobieraniu i konsekwencji tego
					G³osyKompletne = false; //Wpisanie do zmiennej wartoœci false informuj¹cej o niekompletnych plikach audio
					Usuñ_Folder_Wypakowany_i_Winrar(g³os2); //Usniêcie folderu z wypakowanymi elementami i programu do wypakowywania
					return; //Wyjœcie z funkcji poniewa¿ nie ma sensu sprawdzania dalej
				}
			}
		}

		if ((_access((G³os + "b.wav").c_str(), NULL))) //Sprawdzenie czy plik nie istnieje
		{
			if (!czy_pobierano) //Sprawdzanie czy jakieœ pobieranie siê nie rozpocze³o
			{
				cout << "Rozpoczynam pobieranie brakuj¹cych plików g³osu" << endl; //Poinformowaniu o rozpoczêciu pobierania
				czy_pobierano = true; //Zmiana zmiennej aby wiadomo, ¿e rozpoczêto pobieranie
				Wyci¹gnij_z_Programu((g³os3 + ".rar"), Numer_zasobu_rar.at(g³os3)); //Wyci¹gniêcie z zasobów folderu rar z g³osem
				Wypakuj_Rar(g³os3 + ".rar"); //Wypakowanie folderu rar z g³osem
			}
			if (!Przenieœ_Plik(g³os2 + "b.wav", G³os + "b.wav")) //Je¿eli nie uda³o siê przenieœæ wypakowanego pliku
			{
				const auto res = URLDownloadToFile(nullptr, (link + g³os2 + "b.wav").c_str(), (G³os + "b.wav").c_str(), 0, nullptr); //Rozpoczêcie pobierania pliku
				if (res != S_OK) //Je¿eli nie powiod³o siê pobieranie pliku
				{
					cout << "Brak plików dla g³osu oraz nie mo¿na pobraæ danych, wy³¹czono odczytywanie wyniku" << endl; //Poinformowanie o nieudajnym pobieraniu i konsekwencji tego
					G³osyKompletne = false; //Wpisanie do zmiennej wartoœci false informuj¹cej o niekompletnych plikach audio
					Usuñ_Folder_Wypakowany_i_Winrar(g³os2); //Usniêcie folderu z wypakowanymi elementami i programu do wypakowywania
					return; //Wyjœcie z funkcji poniewa¿ nie ma sensu sprawdzania dalej
				}
			}
		}

		if ((_access((G³os + "g.wav").c_str(), NULL))) //Sprawdzenie czy plik nie istnieje
		{
			if (!czy_pobierano) //Sprawdzanie czy jakieœ pobieranie siê nie rozpocze³o
			{
				cout << "Rozpoczynam pobieranie brakuj¹cych plików g³osu" << endl; //Poinformowaniu o rozpoczêciu pobierania
				czy_pobierano = true; //Zmiana zmiennej aby wiadomo, ¿e rozpoczêto pobieranie
				Wyci¹gnij_z_Programu((g³os3 + ".rar"), Numer_zasobu_rar.at(g³os3)); //Wyci¹gniêcie z zasobów folderu rar z g³osem
				Wypakuj_Rar(g³os3 + ".rar"); //Wypakowanie folderu rar z g³osem
			}
			if (!Przenieœ_Plik(g³os2 + "g.wav", G³os + "g.wav")) //Je¿eli nie uda³o siê przenieœæ wypakowanego pliku
			{
				const auto res = URLDownloadToFile(nullptr, (link + g³os2 + "g.wav").c_str(), (G³os + "g.wav").c_str(), 0, nullptr); //Rozpoczêcie pobierania pliku
				if (res != S_OK) //Je¿eli nie powiod³o siê pobieranie pliku
				{
					cout << "Brak plików dla g³osu oraz nie mo¿na pobraæ danych, wy³¹czono odczytywanie wyniku" << endl; //Poinformowanie o nieudajnym pobieraniu i konsekwencji tego
					G³osyKompletne = false; //Wpisanie do zmiennej wartoœci false informuj¹cej o niekompletnych plikach audio
					Usuñ_Folder_Wypakowany_i_Winrar(g³os2); //Usniêcie folderu z wypakowanymi elementami i programu do wypakowywania
					return; //Wyjœcie z funkcji poniewa¿ nie ma sensu sprawdzania dalej
				}
			}
		}

		if ((_access((G³os + "d.wav").c_str(), NULL))) //Sprawdzenie czy plik nie istnieje
		{
			if (!czy_pobierano) //Sprawdzanie czy jakieœ pobieranie siê nie rozpocze³o
			{
				cout << "Rozpoczynam pobieranie brakuj¹cych plików g³osu" << endl; //Poinformowaniu o rozpoczêciu pobierania
				czy_pobierano = true; //Zmiana zmiennej aby wiadomo, ¿e rozpoczêto pobieranie
				Wyci¹gnij_z_Programu((g³os3 + ".rar"), Numer_zasobu_rar.at(g³os3)); //Wyci¹gniêcie z zasobów folderu rar z g³osem
				Wypakuj_Rar(g³os3 + ".rar"); //Wypakowanie folderu rar z g³osem
			}
			if (!Przenieœ_Plik(g³os2 + "d.wav", G³os + "d.wav")) //Je¿eli nie uda³o siê przenieœæ wypakowanego pliku
			{
				const auto res = URLDownloadToFile(nullptr, (link + g³os2 + "d.wav").c_str(), (G³os + "d.wav").c_str(), 0, nullptr); //Rozpoczêcie pobierania pliku
				if (res != S_OK) //Je¿eli nie powiod³o siê pobieranie pliku
				{
					cout << "Brak plików dla g³osu oraz nie mo¿na pobraæ danych, wy³¹czono odczytywanie wyniku" << endl; //Poinformowanie o nieudajnym pobieraniu i konsekwencji tego
					G³osyKompletne = false; //Wpisanie do zmiennej wartoœci false informuj¹cej o niekompletnych plikach audio
					Usuñ_Folder_Wypakowany_i_Winrar(g³os2); //Usniêcie folderu z wypakowanymi elementami i programu do wypakowywania
					return; //Wyjœcie z funkcji poniewa¿ nie ma sensu sprawdzania dalej
				}
			}
		}

		for (auto i = 1; i <= 3; ++i) //Pêtla licz¹ca od 1 do 3
		{
			if ((_access((G³os + 'k' + char('0' + i) + ".wav").c_str(), NULL))) //Sprawdzenie czy plik nie istnieje
			{
				if (!czy_pobierano) //Sprawdzanie czy jakieœ pobieranie siê nie rozpocze³o
				{
					cout << "Rozpoczynam pobieranie brakuj¹cych plików g³osu" << endl; //Poinformowaniu o rozpoczêciu pobierania
					czy_pobierano = true; //Zmiana zmiennej aby wiadomo, ¿e rozpoczêto pobieranie
					Wyci¹gnij_z_Programu((g³os3 + ".rar"), Numer_zasobu_rar.at(g³os3)); //Wyci¹gniêcie z zasobów folderu rar z g³osem
					Wypakuj_Rar(g³os3 + ".rar"); //Wypakowanie folderu rar z g³osem
				}
				if (!Przenieœ_Plik(g³os2 + 'k' + char('0' + i) + ".wav", G³os + 'k' + char('0' + i) + ".wav")) //Je¿eli nie uda³o siê przenieœæ wypakowanego pliku
				{
					const auto res = URLDownloadToFile(nullptr, (link + g³os2 + 'k' + char('0' + i) + ".wav").c_str(), (G³os + 'k' + char('0' + i) + ".wav").c_str(), 0, nullptr); //Rozpoczêcie pobierania pliku
					if (res != S_OK) //Je¿eli nie powiod³o siê pobieranie pliku
					{
						cout << "Brak plików dla g³osu oraz nie mo¿na pobraæ danych, wy³¹czono odczytywanie wyniku" << endl; //Poinformowanie o nieudajnym pobieraniu i konsekwencji tego
						G³osyKompletne = false; //Wpisanie do zmiennej wartoœci false informuj¹cej o niekompletnych plikach audio
						Usuñ_Folder_Wypakowany_i_Winrar(g³os2); //Usniêcie folderu z wypakowanymi elementami i programu do wypakowywania
						return; //Wyjœcie z funkcji poniewa¿ nie ma sensu sprawdzania dalej
					}
				}
			}
		}

		auto const numersw = new char[3]; //Utworzenie tablicy do zamiany liczby na tekst
		for (auto i = 1; i <= 12; ++i) //Pêtla licz¹ca od 1 do 12
		{
			_itoa_s(i, numersw, 3, 10); //Wpisanie do tablicy wartoœci z obrotu pêtli
			if ((_access((G³os + 'w' + numersw + ".wav").c_str(), NULL))) //Sprawdzenie czy plik nie istnieje
			{
				if (!czy_pobierano) //Sprawdzanie czy jakieœ pobieranie siê nie rozpocze³o
				{
					cout << "Rozpoczynam pobieranie brakuj¹cych plików g³osu" << endl; //Poinformowaniu o rozpoczêciu pobierania
					czy_pobierano = true; //Zmiana zmiennej aby wiadomo, ¿e rozpoczêto pobieranie
					Wyci¹gnij_z_Programu((g³os3 + ".rar"), Numer_zasobu_rar.at(g³os3)); //Wyci¹gniêcie z zasobów folderu rar z g³osem
					Wypakuj_Rar(g³os3 + ".rar"); //Wypakowanie folderu rar z g³osem
				}
				if (!Przenieœ_Plik(g³os2 + 'w' + numersw + ".wav", G³os + 'w' + numersw + ".wav")) //Je¿eli nie uda³o siê przenieœæ wypakowanego pliku
				{
					const auto res = URLDownloadToFile(nullptr, (link + g³os2 + 'w' + numersw + ".wav").c_str(), (G³os + 'w' + numersw + ".wav").c_str(), 0, nullptr); //Rozpoczêcie pobierania pliku
					if (res != S_OK) //Je¿eli nie powiod³o siê pobieranie pliku
					{
						cout << "Brak plików dla g³osu oraz nie mo¿na pobraæ danych, wy³¹czono odczytywanie wyniku" << endl; //Poinformowanie o nieudajnym pobieraniu i konsekwencji tego
						G³osyKompletne = false; //Wpisanie do zmiennej wartoœci false informuj¹cej o niekompletnych plikach audio
						Usuñ_Folder_Wypakowany_i_Winrar(g³os2); //Usniêcie folderu z wypakowanymi elementami i programu do wypakowywania
						return; //Wyjœcie z funkcji poniewa¿ nie ma sensu sprawdzania dalej
					}
				}
			}
		}
		delete[] numersw; //Usuwam tablicê, poniewa¿ tablice dynamiczne same siê nie usuwaj¹ po wyjœciu z scop-a

		char numers[3]; //Utworzenie tablicy do zamiany liczby na tekst
		for (auto i = 0; i <= 36; ++i) //Pêtla licz¹ca od 0 do 36
		{
			_itoa_s(i, numers, 10); //Wpisanie do tablicy wartoœci z obrotu pêtli
			if ((_access((G³os + numers + ".wav").c_str(), NULL))) //Sprawdzenie czy plik nie istnieje
			{
				if (!czy_pobierano) //Sprawdzanie czy jakieœ pobieranie siê nie rozpocze³o
				{
					cout << "Rozpoczynam pobieranie brakuj¹cych plików g³osu" << endl; //Poinformowaniu o rozpoczêciu pobierania
					czy_pobierano = true; //Zmiana zmiennej aby wiadomo, ¿e rozpoczêto pobieranie
					Wyci¹gnij_z_Programu((g³os3 + ".rar"), Numer_zasobu_rar.at(g³os3)); //Wyci¹gniêcie z zasobów folderu rar z g³osem
					Wypakuj_Rar(g³os3 + ".rar"); //Wypakowanie folderu rar z g³osem
				}
				if (!Przenieœ_Plik(g³os2 + numers + ".wav", G³os + numers + ".wav")) //Je¿eli nie uda³o siê przenieœæ wypakowanego pliku
				{
					const auto res = URLDownloadToFile(nullptr, (link + g³os2 + numers + ".wav").c_str(), (G³os + numers + ".wav").c_str(), 0, nullptr); //Rozpoczêcie pobierania pliku
					if (res != S_OK) //Je¿eli nie powiod³o siê pobieranie pliku
					{
						cout << "Brak plików dla g³osu oraz nie mo¿na pobraæ danych, wy³¹czono odczytywanie wyniku" << endl; //Poinformowanie o nieudajnym pobieraniu i konsekwencji tego
						G³osyKompletne = false; //Wpisanie do zmiennej wartoœci false informuj¹cej o niekompletnych plikach audio
						Usuñ_Folder_Wypakowany_i_Winrar(g³os2); //Usniêcie folderu z wypakowanymi elementami i programu do wypakowywania
						return; //Wyjœcie z funkcji poniewa¿ nie ma sensu sprawdzania dalej
					}
				}
			}
		}

		if ((_access((G³os + "win.wav").c_str(), NULL))) //Sprawdzenie czy plik nie istnieje
		{
			if (!czy_pobierano) //Sprawdzanie czy jakieœ pobieranie siê nie rozpocze³o
			{
				cout << "Rozpoczynam pobieranie brakuj¹cych plików g³osu" << endl; //Poinformowaniu o rozpoczêciu pobierania
				czy_pobierano = true; //Zmiana zmiennej aby wiadomo, ¿e rozpoczêto pobieranie
				Wyci¹gnij_z_Programu((g³os3 + ".rar"), Numer_zasobu_rar.at(g³os3)); //Wyci¹gniêcie z zasobów folderu rar z g³osem
				Wypakuj_Rar(g³os3 + ".rar"); //Wypakowanie folderu rar z g³osem
			}
			if (!Przenieœ_Plik(g³os2 + "win.wav", G³os + "win.wav")) //Je¿eli nie uda³o siê przenieœæ wypakowanego pliku
			{
				const auto res = URLDownloadToFile(nullptr, (link + g³os2 + "win.wav").c_str(), (G³os + "win.wav").c_str(), 0, nullptr); //Rozpoczêcie pobierania pliku
				if (res != S_OK) //Je¿eli nie powiod³o siê pobieranie pliku
				{
					cout << "Brak plików dla g³osu oraz nie mo¿na pobraæ danych, wy³¹czono odczytywanie wyniku" << endl; //Poinformowanie o nieudajnym pobieraniu i konsekwencji tego
					G³osyKompletne = false; //Wpisanie do zmiennej wartoœci false informuj¹cej o niekompletnych plikach audio
					Usuñ_Folder_Wypakowany_i_Winrar(g³os2); //Usniêcie folderu z wypakowanymi elementami i programu do wypakowywania
					return; //Wyjœcie z funkcji poniewa¿ nie ma sensu sprawdzania dalej
				}
			}
		}

		if (czy_pobierano) //Sprawdzenie czy pobra³o siê wszystkie pliki
		{
			cout << endl << "Pobrano brakuj¹ce pliki g³osów" << endl; //Poinformowanie o ukoñczonu pobierania plików
			Usuñ_Folder_Wypakowany_i_Winrar(g³os2); //Usniêcie folderu z wypakowanymi elementami i programu do wypakowywania
			Wyci¹gnij_z_Programu("Do_u¿ytkownika.txt", IDR_RCDATA46); //Wyci¹gniêcie z programu pliku informuj¹cego o mo¿liwym b³êdzie
			ShellExecuteA(nullptr, nullptr, "Ruletka.exe", nullptr, nullptr, SW_SHOW); //Ponowne uruchomienie programu
			const auto PID = GetCurrentProcessId(); //Pobranie numeru aktualnego procesu
			if (!TerminateProcess(PID, 123)) //Zamkniêcie bie¿¹cego procesu
				cout << "Nie uda³o siê ponownie uruchomiæ programu, mog¹ pojawiæ siê b³êdy z wyœwietlaniem tekstu" << endl; //Poinformowanie o mo¿liwym b³êdzie
		}
	}
}

void SprawdŸ_Ustawienia()
{
	if (!_access("setting.txt", NULL)) // Sprawdzenie dostêpu do pliku (je¿eli takowy istnieje, musi istnieæ plik)
	{
		ifstream ustawienia; //Utworzenie typu do celu odczytu z pliku
		ustawienia.open("setting.txt"); //Otwarcie pliku z ustawieniami
		string buf; //Utworzenie buforu do odczytu z pliku
		unsigned char licznik = 0;
		while (!ustawienia.eof()) //Pêtla trwaj¹ca do koñca pliku
		{
			getline(ustawienia, buf); //Wczytanie ca³ej lini tekstu z pliku
			Ustaw_Ustawienia(buf); //Zamiana wczytanej lini na ustawienie programu
			++licznik;
		}
		ustawienia.close(); //Zamkniêcie pliku setting.txt
		if (licznik < 13) //Je¿eli iloœæ wczytanych liniejek jest mniejsza ni¿ 12 to znacz, ¿e brakuje jakieœ linijki w pliku ustawieñ
		{
			cout << "Plik z ustawieniami jest niekompletny, utworzy³em nowy" << endl;
			DeleteFile("setting.txt"); //wiêc usuñ nieca³kowity plik
			SprawdŸ_Ustawienia(); //Uruchom jeszcze raz funkcje, aby utorzyæ prawid³owy plik
			return; //WyjdŸ z funkcji
		}
	}
	else
	{
		ofstream ustawienia; //Utworzenie typu do celu zapisu do pliku
		ustawienia.open("setting.txt"); //Otwarcie pliku do wygenerowania ustawieñ domyœlnych
		auto const bufor_zapisu = new char[358]; //Utworzenie buforu
		memcpy(bufor_zapisu, "iloœæ_min_dodatkowych_obrotów_ruletki 2\niloœæ_max_dodatkowych_obrotów_ruletki 3\nczas_przeskoku_kulki_szybki 50\nczas_przeskoku_kulki_wolny 75\nczas_przerwy_dzwiêku 500\nstyl_liczenia_wygranej 1\nkwota_pocz¹tkowa 1000\nstan_dŸwiêków 1\nczy_kontynuowaæ_grê 1\ng³os_odczytu_numeru 1\ng³os_szybkoœæ_odczytu_numeru 4\nefekty_dŸwiêkowe 1\nmetoda_liczenia_wygranej_zerowej 1", 358); //Wpisanie do pliku domyœnych ustawieñ
		ustawienia.write(bufor_zapisu, 357); //Zapisanie do pliku setting.txt danych wpisanych do bufora danych
		delete[] bufor_zapisu; //Usuniêcie buforu
		ustawienia.close(); //Zamkniêcie pliku setting.txt
		return; //WyjdŸ z funkcji
	}

	if (Ustawienia.czas_przeskoku_kulki_wolny < Ustawienia.czas_przeskoku_kulki_szybki) //Sprawdzenie czy prawid³owo wprowadzono ustawienie, czy ³apie siê w zakresie i warunkach
	{
		cout << "Wartoœæ wolnego czasu przeskoku kulki musi byæ ni¿sza ni¿ wartoœæ szybkiego czasu przeskoku kulki" << endl; //(Wartoœci tych zmiennych to czas opóŸnienia wiêc im jest wy¿szy tym d³u¿sza przerwa)
		cout << "Ustawiam domyœlne ustawienie" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje zmienone na domyœlne
		Ustawienia.czas_przeskoku_kulki_szybki = 50; //Ustawienie wartoœci domyœlnej
		Ustawienia.czas_przeskoku_kulki_wolny = 75; //Ustawienie wartoœci domyœlnej
	}
	if (Ustawienia.iloœæ_min_dodatkowych_obrotów_ruletki < 0) //Sprawdzenie czy prawid³owo wprowadzono ustawienie, czy ³apie siê w zakresie i warunkach
	{
		cout << "Iloœæ minimalna obrotów ruletki nie mo¿e byæ mniejsza od 0" << endl; //Poinformowanie u¿ytkownika o problemie
		cout << "Ustawiam domyœlne ustawienie" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje zmienone na domyœlne
		Ustawienia.iloœæ_min_dodatkowych_obrotów_ruletki = 2; //Ustawienie wartoœci domyœlnej
	}
	if (Ustawienia.iloœæ_max_dodatkowych_obrotów_ruletki < 0) //Sprawdzenie czy prawid³owo wprowadzono ustawienie, czy ³apie siê w zakresie i warunkach
	{
		cout << "Iloœæ max obrotów ruletki nie mo¿e byæ mniejsza od 0" << endl; //Poinformowanie u¿ytkownika o problemie
		cout << "Ustawiam domyœlne ustawienie" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje zmienone na domyœlne
		Ustawienia.iloœæ_max_dodatkowych_obrotów_ruletki = 3; //Ustawienie wartoœci domyœlnej
	}
	if (Ustawienia.iloœæ_max_dodatkowych_obrotów_ruletki < Ustawienia.iloœæ_min_dodatkowych_obrotów_ruletki) //Sprawdzenie czy prawid³owo wprowadzono ustawienie, czy ³apie siê w zakresie i warunkach
	{
		cout << "Max dodoatkowych obrotów ruletki nie mo¿e byæ mniejszy od min dodatkowych obrotów ruletki" << endl; //Poinformowanie u¿ytkownika o problemie
		cout << "Zamieniam miejscami ustawienia" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje zmienone na domyœlne
		swap(Ustawienia.iloœæ_min_dodatkowych_obrotów_ruletki, Ustawienia.iloœæ_max_dodatkowych_obrotów_ruletki); //Zamiana miejscami ustawieñ
	}
	if (Ustawienia.czas_przerwy_dzwiêku < 0) //Sprawdzenie czy prawid³owo wprowadzono ustawienie, czy ³apie siê w zakresie i warunkach
	{
		cout << "Czas przerwy dŸwiêku nie mo¿e byæ mniejszy od zera" << endl; //Poinformowanie u¿ytkownika o problemie
		cout << "Ustawiam domyœlne ustawienie" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje zmienone na domyœlne
		Ustawienia.czas_przerwy_dzwiêku = 500; //Ustawienie wartoœci domyœlnej
	}
	if (Ustawienia.kwota_pocz¹tkowa < 0) //Sprawdzenie czy prawid³owo wprowadzono ustawienie, czy ³apie siê w zakresie i warunkach
	{
		cout << "Kwota pocz¹tkowa nie mo¿e byæ mniejsza od zera" << endl; //Poinformowanie u¿ytkownika o problemie
		cout << "Ustawiam domyœlne ustawienie" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje zmienone na domyœlne
		Ustawienia.kwota_pocz¹tkowa = 1000; //Ustawienie wartoœci domyœlnej
	}
	if ((Ustawienia.g³os_odczytu_numeru > 10) || (Ustawienia.g³os_odczytu_numeru < 0)) //Sprawdzenie czy prawid³owo wprowadzono ustawienie, czy ³apie siê w zakresie i warunkach
	{
		cout << "Opcja g³os odczytu numeru przyjmuje wartoœci w przedziale [0;10]" << endl; //Poinformowanie u¿ytkownika o problemie
		cout << "Ustawiam domyœlne ustawienie" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje zmienone na domyœlne
		Ustawienia.g³os_odczytu_numeru = 1; //Ustawienie wartoœci domyœlnej
	}
	if ((Ustawienia.g³os_szybkoœæ_odczytu_numeru > 5) || (Ustawienia.g³os_szybkoœæ_odczytu_numeru < 1)) //Sprawdzenie czy prawid³owo wprowadzono ustawienie, czy ³apie siê w zakresie i warunkach
	{
		cout << "Opcja szybkoœæ g³osu odczytu przyjmuje wartoœci w przedziale [1;5]" << endl; //Poinformowanie u¿ytkownika o problemie
		cout << "Ustawiam domyœlne ustawienie" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje zmienone na domyœlne
		Ustawienia.g³os_szybkoœæ_odczytu_numeru = (4 >> 0); //Ustawienie wartoœci domyœlnej
	}
	if (Ustawienia.efekty_dŸwiêkowe && !Ustawienia.stan_dŸwiêków) //Sprawdzenie czy prawid³owo wprowadzono ustawienie, czy ³apie siê w zakresie i warunkach
	{
		cout << "Nie mo¿esz mieæ wy³¹czonych dŸwiêków i w³¹czonych efektów dŸwiêkowych" << endl; //Poinformowanie u¿ytkownika o problemie
		cout << "Ustawiam domyœlne ustawienie" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje zmienone na domyœlne
		Ustawienia.stan_dŸwiêków = true; //Ustawienie wartoœci domyœlnej
	}
	if (Ustawienia.g³os_odczytu_numeru > 0 && !Ustawienia.stan_dŸwiêków) //Sprawdzenie czy prawid³owo wprowadzono ustawienie, czy ³apie siê w zakresie i warunkach
	{
		cout << "Nie mo¿esz mieæ wy³¹czonych dŸwiêków i w³¹czon¹ mowê" << endl; //Poinformowanie u¿ytkownika o problemie
		cout << "Ustawiam domyœlne ustawienie" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje zmienone na domyœlne
		Ustawienia.stan_dŸwiêków = true; //Ustawienie wartoœci domyœlnej
	}
}

void Og³oœ_Wynik(const int & wygrana, const int & kwota_zak³adu, int & iloœæ_pieniêdzy, ofstream & log_ogólny, fstream & log)
{
	if (wygrana >= kwota_zak³adu) //Je¿eli wygrana jest wiêksza lub równa kwocie zak³adu to znaczy, ¿e siê wygra³o zak³ad
	{
		iloœæ_pieniêdzy += wygrana; //Dopisanie do salda kwoty wygranej z zak³adu
		if (Ustawienia.styl_liczenia_wygranej) iloœæ_pieniêdzy += kwota_zak³adu; //Dopisanie do salda kwoty zak³adu
		log << " Wygrywasz " << wygrana << "$"; //Zapisanie do bufora pliku logu aktualnego informacji o kwocie wygranej zak³adu
		log << " Posiadasz " << iloœæ_pieniêdzy << "$" << '\n'; //Zapisanie do bufora pliku logu aktualnego informacji o saldzie konta u¿ytkownika
		log_ogólny << " Wygrywasz " << wygrana << "$"; //Zapisanie do bufora pliku logu ogólnego informacji o kwocie wygranej zak³adu
		log_ogólny << " Posiadasz " << iloœæ_pieniêdzy << "$" << '\n'; //Zapisanie do bufora pliku logu ogólnego informacji o saldzie konta u¿ytkownika
		log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
		log_ogólny.flush(); //Zapisanie do pliku log_ogólny.txt danych wpisanych do bufora danych
		if (Ustawienia.stan_dŸwiêków) //Je¿eli stan_dŸwiêków == 1
		{
			if (G³osyKompletne) PlaySound((G³os + "win.wav").c_str(), nullptr, SND_SYNC); //Je¿eli s¹ wszystkie pliki g³osów to odtworzenie efektu wygrania zak³adu
			else //W przeciwym wypadku
			{
				short i = 2; //Zmienna steruj¹ca pêtl¹
				while (i--) //Pêtla która wykona siê 2 razy
				{
					cout << '\a'; //Wywo³anie pikniêcia w g³oœniku
					Sleep(Ustawienia.czas_przerwy_dzwiêku); //Przerwa przed kolejnym pikniêciem
				}
				cout << '\a'; //Wywo³anie pikniêcia w g³oœniku
			}
		}
	}
	else if (wygrana == (kwota_zak³adu >> 1)) //Je¿eli wygrana jest równa po³owie kwocie zak³adu to znaczy, ¿e dostaje siê zwrot po³owy kwoty zak³adu
	{
		iloœæ_pieniêdzy += wygrana; //Dopisanie do salda kwoty zwrotu z zak³adu
		log << " Dostajesz polowe zak³adu " << wygrana << "$"; //Zapisanie do bufora pliku logu aktualnego informacji o kwocie zwrotu zak³adu
		log << " Posiadasz " << iloœæ_pieniêdzy << "$" << '\n'; //Zapisanie do bufora pliku logu aktualnego informacji o saldzie konta u¿ytkownika
		log_ogólny << " Dostajesz polowe zak³adu " << wygrana << "$"; //Zapisanie do bufora pliku logu ogólnego informacji o kwocie zwrotu zak³adu
		log_ogólny << " Posiadasz " << iloœæ_pieniêdzy << "$" << '\n'; //Zapisanie do bufora pliku logu ogólnego informacji o saldzie konta u¿ytkownika
		log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
		log_ogólny.flush(); //Zapisanie do pliku log_ogólny.txt danych wpisanych do bufora danych
		if (Ustawienia.stan_dŸwiêków) //Je¿eli stan_dŸwiêków == 1
			if (!G³osyKompletne) //Je¿eli nie ma wszystkich plików g³osów to
			{
				cout << '\a'; //Wywo³anie pikniêcia w g³oœniku
				Sleep(Ustawienia.czas_przerwy_dzwiêku); //Przerwa przed kolejnym pikniêciem
				cout << '\a'; //Wywo³anie pikniêcia w g³oœniku
			}
	}
	else if (wygrana == 0) //Je¿eli wygrana jest równa 0 to znaczy, ¿e siê zak³ad przegra³o
	{
		log << " Przegrales " << kwota_zak³adu << "$"; //Zapisanie do bufora pliku logu aktualnego informacji o przegranej kwocie
		log << " Posiadasz " << iloœæ_pieniêdzy << "$" << '\n'; //Zapisanie do bufora pliku logu aktualnego informacji o saldzie konta u¿ytkownika
		log_ogólny << " Przegrales " << kwota_zak³adu << "$"; //Zapisanie do bufora pliku logu ogólnego informacji o przegranej kwocie
		log_ogólny << " Posiadasz " << iloœæ_pieniêdzy << "$" << '\n'; //Zapisanie do bufora pliku logu aktualnego informacji o saldzie konta u¿ytkownika
		log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
		log_ogólny.flush(); //Zapisanie do pliku log_ogólny.txt danych wpisanych do bufora danych
		if (Ustawienia.stan_dŸwiêków) //Je¿eli w³¹czono dŸwiêki
			if (!G³osyKompletne) cout << '\a';  //Je¿eli nie ma wszystkich plików g³osów to wywo³anie pikniêcia w g³oœniku
	}
}

void Koniec_Gry(ofstream & log_ogólny, fstream & log, const int & iloœæ_pieniêdzy)
{
	cout << endl << "Koñczysz grê z wynikiem " << iloœæ_pieniêdzy << "$" << endl; //Poinformowanie u¿ytkownika o saldzie konta
	log << '\n' << "Koñczysz grê z wynikiem " << iloœæ_pieniêdzy << "$" << '\n'; //Zapisanie do bufora pliku logu aktualnego informacji o saldzie konta u¿ytkownika
	log_ogólny << "Koñczysz grê z wynikiem " << iloœæ_pieniêdzy << "$" << '\n'; //Zapisanie do bufora pliku logu ogólnego informacji o saldzie konta u¿ytkownika
	log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
	log_ogólny.flush(); //Zapisanie do pliku log_ogólny.txt danych wpisanych do bufora danych
	log.close(); //Zamkniêcie pliku log aktualny
	remove("log_aktualny.txt"); //Usuniêcie pliku log aktualny poniewa¿ skoñczy³o siê grê

	if (Ustawienia.stan_dŸwiêków == 1) //Je¿eli stan_dŸwiêków == 1
		if (iloœæ_pieniêdzy == 0) //Je¿eli bud¿et jest równy 0 to
			if (EfektyKompletne) PlaySound("Efekty_dŸwiêkowe/bankrut.wav", nullptr, SND_ASYNC); //Je¿eli pliki efektów s¹ dostêpne, odtworzenie efektu bankruta
			else //W przeciwym wypadku
				for (auto i = 0; i < 5; ++i) //Rozpoczêcie pêtli która wykona 5 obrotów
				{
					cout << '\a'; //Wywo³anie pikniêcia w g³oœniku
					Sleep(Ustawienia.czas_przerwy_dzwiêku); //Przerwa przed kolejnym pikniêciem //Przerwa przed kolejnym pikniêciem
				}

	if (iloœæ_pieniêdzy > Ustawienia.kwota_pocz¹tkowa && iloœæ_pieniêdzy < (Ustawienia.kwota_pocz¹tkowa << 1)) //Sprawdzenie czy zwiêkszy³o siê bud¿et
	{
		cout << "Gratuluje zwiêkszy³eœ swój zasób finansowy" << endl; //Wyœwietlenie gratulacji z powodu zwiêkszenia bud¿etu
		if (EfektyKompletne) //Je¿eli pliki efektów s¹ dostêpne
			if (rand() & 1) PlaySound("Efekty_dŸwiêkowe/wygrana1.wav", nullptr, SND_ASYNC); //Wylosowanie numeru otworzonego efektu, odtworzenie je¿eli wylosowano efekt 0
			else PlaySound("Efekty_dŸwiêkowe/wygrana2.wav", nullptr, SND_ASYNC); //Odtworzenie je¿eli wylosowano efekt 1
	}
	else if (iloœæ_pieniêdzy >= (Ustawienia.kwota_pocz¹tkowa << 1)) //Sprawdzenie czy zwielokrotniono przynajmniej 2 razy bud¿et
	{
		cout << "Gratuluje zwiêkszy³eœ " << iloœæ_pieniêdzy / Ustawienia.kwota_pocz¹tkowa << "-krotnie swój zasób finansowy" << endl; //Wyœwietlenie gratulacji z powodu zwielokrotnienia przynajmniej 2 razy bud¿etu
		if (EfektyKompletne) PlaySound("Efekty_dŸwiêkowe/zwielokrotnenie.wav", nullptr, SND_ASYNC); //Odtworzenie efektu dŸwiêkowego wzamian za zwielokrotnienie bud¿etu, je¿eli pliki efektów s¹ dostêpne
	}
}

void Pêtla_G³ówna(int & wygrana, int & kwota_zak³adu, int & iloœæ_pieniêdzy, ofstream & log_ogólny, fstream & log, const char & co_kontynuowaæ, string & typ_zak³adu, int & wylosowana_liczba)
{
	if (co_kontynuowaæ == 'n') //Je¿eli punkt kontynuowania jest odpowiedni to
	{
		Wczytaj_Kwotê_Zak³adu(kwota_zak³adu, iloœæ_pieniêdzy); //Przypisanie do zmiennej pobranej od u¿ytkownika kwoty zak³adu
		log << "Obstawiono za " << kwota_zak³adu << "$"; //Zapisanie do bufora pliku logu aktualnego informacji o kwocie obstawionego zak³adu
		log_ogólny << "Obstawiono za " << kwota_zak³adu << "$"; //Zapisanie do bufora pliku logu ogólnego informacji o kwocie obstawionego zak³adu
		log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
		log_ogólny.flush(); //Zapisanie do pliku log_ogólny.txt danych wpisanych do bufora danych
	}
	else //W przeciwym wypadku
	{
		cout << "Masz " << iloœæ_pieniêdzy << "$" << endl; //Wypisanie wczytanej informacji o posiadanej iloœci pieniêdzy
		cout << "Obstawiono za " << kwota_zak³adu << "$" << endl; //Wypisanie wczytanej kwoty zak³adu
	}
	if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k') //Je¿eli punkt kontynuowania jest odpowiedni to
	{
		typ_zak³adu = Obstaw(); //Przypisanie do zmiennej pobranej od u¿ytkownika typu zak³adu
		log << " Obstawiono zaklad " << typ_zak³adu; //Zapisanie do bufora pliku logu aktualnego informacji o typie obstawionego zak³adu
		log_ogólny << " Obstawiono zaklad " << typ_zak³adu; //Zapisanie do bufora pliku logu ogólnego informacji o typie obstawionego zak³adu
		log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
		log_ogólny.flush(); //Zapisanie do pliku log_ogólny.txt danych wpisanych do bufora danych
	}
	else cout << "Obstawiono zak³ad " << typ_zak³adu << endl; //Wypisanie wczytanego typu zak³adu
	if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k' || co_kontynuowaæ == 't' || co_kontynuowaæ == 'w') iloœæ_pieniêdzy -= kwota_zak³adu;  //Je¿eli punkt kontynuowania jest odpowiedni to odjêcie od iloœci pieniêdzy kwoty zak³adu
	if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k' || co_kontynuowaæ == 't') //Je¿eli punkt kontynuowania jest odpowiedni to
	{
		cout << "Kulka w grze, zaczekaj na wylosowanie numeru..." << endl; //Poinformowanie u¿ytkownika o rozpoczêciu losowania
		wylosowana_liczba = Zakrêæ_Ruletk¹(); //Wylosowanie i przypisanie do zmiennej liczby bêdêcej na  wylosowanej pozycji na kole ruletki
	}
	else //W przeciwym wypadku
	{
		cout << "Wylosowano numer "; //Poinformowaniu o wylosowaniu liczby
		Change_Col(Ruletka_plansza_kolor_col[(size_t)wylosowana_liczba]); //Zmiana koloru tekstu w konsoli zgodnie z kolorem numeru na ruletce
		cout << wylosowana_liczba; //Wypisanie wylosowanej liczby
		Change_Col(7); //Powrót do standardowego koloru tekstu w konsoli
		cout << ". "; //Wypisanie kropki koñcz¹cej zdanie
	}
	if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k' || co_kontynuowaæ == 't') //Je¿eli punkt kontynuowania jest odpowiedni to
	{
		log << " Wylosowano " << wylosowana_liczba; //Zapisanie do bufora pliku logu aktualnego informacji o wylosowanej liczbie
		log_ogólny << " Wylosowano " << wylosowana_liczba; //Zapisanie do bufora pliku logu ogólnego informacji o wylosowanej liczbie
		log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
		log_ogólny.flush(); //Zapisanie do pliku log_ogólny.txt danych wpisanych do bufora danych
		Odczytaj_Liczbê(wylosowana_liczba, typ_zak³adu);
	}
	if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k' || co_kontynuowaæ == 't' || co_kontynuowaæ == 'w') //Je¿eli punkt kontynuowania jest odpowiedni to
	{
		wygrana = SprawdŸ_Zak³ad(kwota_zak³adu, typ_zak³adu, wylosowana_liczba); //Przypisanie do wygranej kwoty zgodnej z wygran¹, je¿eli siê coœwygra³o
		Og³oœ_Wynik(wygrana, kwota_zak³adu, iloœæ_pieniêdzy, log_ogólny, log); //Funkcja informuj¹ca u¿ytkownika czy wygra³ zak³ad
	}
}
void Ustaw_Ustawienia(string & tekst)
{
	if (tekst.find("iloœæ_min_dodatkowych_obrotów_ruletki") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("iloœæ_min_dodatkowych_obrotów_ruletki")); //Usuniêcie s³owa z tekst aby zosta³a tylko liczba która jest wartoœci¹ ustawienia

		try {//Próba
			Ustawienia.iloœæ_min_dodatkowych_obrotów_ruletki = stos(tekst);  //Przypisaninie wartoœci odczytanej z tekstu
		}
		catch (invalid_argument&) { //Je¿eli zostanie z³apany wyj¹tek "nieprawid³owy argument"
			cout << "Ustawiam domyœlne ustawienie iloœæ_minimalna_obrotów_ruletki" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje pozostawione przy domyœlnych
		}
		catch (out_of_range&) { //Je¿eli zostanie z³apany wyj¹tek "zbyt du¿y argument"
			cout << "Ustawiam domyœlne ustawienie iloœæ_minimalna_obrotów_ruletki" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje pozostawione przy domyœlnych
		}
	}
	else if (tekst.find("iloœæ_max_dodatkowych_obrotów_ruletki") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("iloœæ_max_dodatkowych_obrotów_ruletki")); //Usuniêcie s³owa z tekst aby zosta³a tylko liczba która jest wartoœci¹ ustawienia

		try {//Próba
			Ustawienia.iloœæ_max_dodatkowych_obrotów_ruletki = stos(tekst);  //Przypisaninie wartoœci odczytanej z tekstu
		}
		catch (invalid_argument&) { //Je¿eli zostanie z³apany wyj¹tek "nieprawid³owy argument"
			cout << "Ustawiam domyœlne ustawienie iloœæ_max_dodatkowych_obrotów_ruletki" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje pozostawione przy domyœlnych
		}
		catch (out_of_range&) { //Je¿eli zostanie z³apany wyj¹tek "zbyt du¿y argument"
			cout << "Ustawiam domyœlne ustawienie iloœæ_max_dodatkowych_obrotów_ruletki" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje pozostawione przy domyœlnych
		}
	}
	else if (tekst.find("czas_przeskoku_kulki_szybki") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("czas_przeskoku_kulki_szybki")); //Usuniêcie s³owa z tekst aby zosta³a tylko liczba która jest wartoœci¹ ustawienia

		try {//Próba
			Ustawienia.czas_przeskoku_kulki_szybki = stos(tekst);  //Przypisaninie wartoœci odczytanej z tekstu
		}
		catch (invalid_argument&) { //Je¿eli zostanie z³apany wyj¹tek "nieprawid³owy argument"
			cout << "Ustawiam domyœlne ustawienie czas_przeskoku_kulki_szybki" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje pozostawione przy domyœlnych
		}
		catch (out_of_range&) { //Je¿eli zostanie z³apany wyj¹tek "zbyt du¿y argument"
			cout << "Ustawiam domyœlne ustawienie czas_przeskoku_kulki_szybki" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje pozostawione przy domyœlnych
		}
	}
	else if (tekst.find("czas_przeskoku_kulki_wolny") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("czas_przeskoku_kulki_wolny")); //Usuniêcie s³owa z tekst aby zosta³a tylko liczba która jest wartoœci¹ ustawienia

		try {//Próba
			Ustawienia.czas_przeskoku_kulki_wolny = stos(tekst);  //Przypisaninie wartoœci odczytanej z tekstu
		}
		catch (invalid_argument&) { //Je¿eli zostanie z³apany wyj¹tek "nieprawid³owy argument"
			cout << "Ustawiam domyœlne ustawienie czas_przeskoku_kulki_wolny" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje pozostawione przy domyœlnych
		}
		catch (out_of_range&) { //Je¿eli zostanie z³apany wyj¹tek "zbyt du¿y argument"
			cout << "Ustawiam domyœlne ustawienie czas_przeskoku_kulki_wolny" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje pozostawione przy domyœlnych
		}
	}
	else if (tekst.find("styl_liczenia_wygranej") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("styl_liczenia_wygranej")); //Usuniêcie s³owa z tekst aby zosta³a tylko liczba która jest wartoœci¹ ustawienia

		try {//Próba
			Ustawienia.styl_liczenia_wygranej = StringtoBool(tekst);  //Przypisaninie wartoœci odczytanej z tekstu
		}
		catch (invalid_argument&) { //Je¿eli zostanie z³apany wyj¹tek "nieprawid³owy argument"
			cout << "Ustawiam domyœlne ustawienie styl_liczenia_wygranej" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje pozostawione przy domyœlnych
		}
	}
	else if (tekst.find("kwota_pocz¹tkowa") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("kwota_pocz¹tkowa")); //Usuniêcie s³owa z tekst aby zosta³a tylko liczba która jest wartoœci¹ ustawienia

		try {//Próba
			Ustawienia.kwota_pocz¹tkowa = stoi(tekst);  //Przypisaninie wartoœci odczytanej z tekstu
		}
		catch (invalid_argument&) { //Je¿eli zostanie z³apany wyj¹tek "nieprawid³owy argument"
			cout << "Ustawiam domyœlne ustawienie kwota_pocz¹tkowa" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje pozostawione przy domyœlnych
		}
		catch (out_of_range&) { //Je¿eli zostanie z³apany wyj¹tek "zbyt du¿y argument"
			cout << "Ustawiam domyœlne ustawienie kwota_pocz¹tkowa" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje pozostawione przy domyœlnych
		}
	}
	else if (tekst.find("stan_dŸwiêków") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("stan_dŸwiêków")); //Usuniêcie s³owa z tekst aby zosta³a tylko liczba która jest wartoœci¹ ustawienia

		try {//Próba
			Ustawienia.stan_dŸwiêków = StringtoBool(tekst);  //Przypisaninie wartoœci odczytanej z tekstu
		}
		catch (invalid_argument&) { //Je¿eli zostanie z³apany wyj¹tek "nieprawid³owy argument"
			cout << "Ustawiam domyœlne ustawienie stan_dŸwiêków" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje pozostawione przy domyœlnych
		}
	}
	else if (tekst.find("czy_kontynuowaæ_grê") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("czy_kontynuowaæ_grê")); //Usuniêcie s³owa z tekst aby zosta³a tylko liczba która jest wartoœci¹ ustawienia

		try {//Próba
			Ustawienia.czy_kontynuowaæ_grê = StringtoBool(tekst);  //Przypisaninie wartoœci odczytanej z tekstu
		}
		catch (invalid_argument&) { //Je¿eli zostanie z³apany wyj¹tek "nieprawid³owy argument"
			cout << "Ustawiam domyœlne ustawienie czy_kontynuowaæ_grê" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje pozostawione przy domyœlnych
		}
	}
	else if (tekst.find("g³os_odczytu_numeru") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("g³os_odczytu_numeru")); //Usuniêcie s³owa z tekst aby zosta³a tylko liczba która jest wartoœci¹ ustawienia

		try {//Próba
			Ustawienia.g³os_odczytu_numeru = stos(tekst);  //Przypisaninie wartoœci odczytanej z tekstu
		}
		catch (invalid_argument&) { //Je¿eli zostanie z³apany wyj¹tek "nieprawid³owy argument"
			cout << "Ustawiam domyœlne ustawienie g³os_odczytu_numeru" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje pozostawione przy domyœlnych
		}
		catch (out_of_range&) { //Je¿eli zostanie z³apany wyj¹tek "zbyt du¿y argument"
			cout << "Ustawiam domyœlne ustawienie g³os_odczytu_numeru" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje pozostawione przy domyœlnych
		}
	}
	else if (tekst.find("g³os_szybkoœæ_odczytu_numeru") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("g³os_szybkoœæ_odczytu_numeru")); //Usuniêcie s³owa z tekst aby zosta³a tylko liczba która jest wartoœci¹ ustawienia

		try {//Próba
			Ustawienia.g³os_szybkoœæ_odczytu_numeru = stos(tekst);  //Przypisaninie wartoœci odczytanej z tekstu
		}
		catch (invalid_argument&) { //Je¿eli zostanie z³apany wyj¹tek "nieprawid³owy argument"
			cout << "Ustawiam domyœlne ustawienie g³os_szybkoœæ_odczytu_numeru" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje pozostawione przy domyœlnych
		}
		catch (out_of_range&) { //Je¿eli zostanie z³apany wyj¹tek "zbyt du¿y argument"
			cout << "Ustawiam domyœlne ustawienie g³os_szybkoœæ_odczytu_numeru" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje pozostawione przy domyœlnych
		}
	}
	else if (tekst.find("efekty_dŸwiêkowe") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("efekty_dŸwiêkowe")); //Usuniêcie s³owa z tekst aby zosta³a tylko liczba która jest wartoœci¹ ustawienia

		try {//Próba
			Ustawienia.efekty_dŸwiêkowe = StringtoBool(tekst);  //Przypisaninie wartoœci odczytanej z tekstu
		}
		catch (invalid_argument&) { //Je¿eli zostanie z³apany wyj¹tek "nieprawid³owy argument"
			cout << "Ustawiam domyœlne ustawienie efekty_dŸwiêkowe" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje pozostawione przy domyœlnych
		}
	}
	else if (tekst.find("metoda_liczenia_wygranej_zerowej") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("metoda_liczenia_wygranej_zerowej")); //Usuniêcie s³owa z tekst aby zosta³a tylko liczba która jest wartoœci¹ ustawienia

		try {//Próba
			Ustawienia.metoda_liczenia_wygranej_zerowej = StringtoBool(tekst);  //Przypisaninie wartoœci odczytanej z tekstu
		}
		catch (invalid_argument&) { //Je¿eli zostanie z³apany wyj¹tek "nieprawid³owy argument"
			cout << "Ustawiam domyœlne ustawienie metoda_liczenia_wygranej_zerowej" << endl; //Poinformowanie u¿ytkownika, ¿e bie¿¹ce ustawienie zostaje pozostawione przy domyœlnych
		}
	}
}

void Inicjacje_Pocz¹tkowe()
{
	//Inicjowanie ustawieñ programu
	WNDCLASSEX wincl; //Utworzenie typu do zmiany w³aœciwoœci programu
	wincl.hIcon = LoadIcon(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_ICON1)); //Przypisanie ikony programu
	wincl.hIconSm = LoadIcon(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_ICON1));//Przypisanie ma³ej ikony programu

	//Inicjowanie funkcji
	setlocale(LC_ALL, "polish"); // W celu polskich liter w konsoli
	srand((unsigned)time(nullptr)); //Zainicjowanie generatorza LCG (Liniowy Generator Kongruentny) dla ma³o wa¿nych liczb
	Show_Cursor(); //Pokazanie kursora tekstowego w konsoli
}

bool Wyci¹gnij_z_Programu(const string & œcie¿ka, const unsigned short & numer_zasobu)
{
	const HRSRC hPlik = FindResource(GetModuleHandle(nullptr), MAKEINTRESOURCE(numer_zasobu), RT_RCDATA); //Tworz¹ uchwyt do pliku znajduj¹cego siê w plikach zasobów
	if (hPlik != nullptr) //Je¿eli uchyt nie jest pusty (Znalaz³o zasób)
	{
		const auto pPlik = LoadResource(GetModuleHandle(nullptr), hPlik); //Przypisujê uchwytowi miejsce Ÿród³owe pliku
		const auto dwDlugosc = SizeofResource(GetModuleHandle(nullptr), hPlik); //Przypisujê zmiennej wielkoœæ pliku
		const auto hPlik = CreateFile(œcie¿ka.c_str(), GENERIC_WRITE, NULL, nullptr, CREATE_NEW, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, nullptr); //Tworzê plik
		DWORD dwBajtyZapisane; //Tworzê i inicjujê zmiennn¹ informuj¹c¹ o iloœæi zapisanych danych
		if (!WriteFile(hPlik, pPlik, dwDlugosc, &dwBajtyZapisane, nullptr)) return false; //Je¿eli zapis do pliku siê nie uda³ zwróæ fa³sz
		if (dwBajtyZapisane != dwDlugosc) return false; //Je¿eli iloœæ zapisanych danych jest inna ni¿ iloœæ danych do zapisania zwróæ fa³sz
		CloseHandle(hPlik); //Zamykam uchwyt do pliku Ÿród³owego
		return true; //Zwracam, ¿e zapis siê uda³
	}
	return false; //W przeciwym wypadku zwracam fa³sz
}

void Wypakuj_Rar(const string & nazwa_folderu)
{
	if ((_access("Rar.exe", NULL))) Wyci¹gnij_z_Programu("Rar.exe", IDR_RAR);  //Sprawdzenie czy plik nie istnieje je¿eli nie istnieje to wyci¹gam z pamiêci
	if ((_access(nazwa_folderu.substr(0, nazwa_folderu.size() - (4 << 0)).c_str(), NULL))) system(("Rar.exe x " + nazwa_folderu + " -o+ -idq").c_str()); //Wydajê polecenie rozpakowania archiwum rar je¿eli wczeœniej niewypakowano
}

bool Przenieœ_Plik(const string & z_pliku, const string & do_pliku)
{
	return MoveFile(z_pliku.c_str(), do_pliku.c_str()); //Zwracam wynik przenoszenia pliku
}

void Usuñ_Folder_Wypakowany_i_Winrar(const string & G³os)
{
	DeleteFile((G³os + "p.wav").c_str()); //Usuwam plik p.wav

	DeleteFile((G³os + "n.wav").c_str()); //Usuwam plik n.wav

	DeleteFile((G³os + "r.wav").c_str()); //Usuwam plik r.wav

	DeleteFile((G³os + "b.wav").c_str()); //Usuwam plik b.wav

	DeleteFile((G³os + "g.wav").c_str()); //Usuwam plik g.wav

	DeleteFile((G³os + "d.wav").c_str()); //Usuwam plik d.wav

	DeleteFile((G³os + "win.wav").c_str()); //Usuwam plik win.wav

	for (auto i = 1; i <= 3; ++i) //Pêtla licz¹ca od 1 do 3
		DeleteFile((G³os + 'k' + char('0' + i) + ".wav").c_str()); //Usuwam plik k z odpowienim indeksem

	auto const numers = new char[3]; //Utworzenie tablicy do przechowywania zamienionej liczby na tekst

	for (auto i = 1; i <= 12; ++i) //Pêtla licz¹ca od 1 do 12
	{
		_snprintf_s(numers, 3, 3, "%d", i); //Wpisanie do tablicy wartoœci z obrotu pêtli
		DeleteFile((G³os + 'w' + numers + ".wav").c_str());  //Usuwam plik w z odpowienim indeksem
	}

	for (auto i = 0; i <= 36; ++i) //Pêtla licz¹ca od 0 do 36
	{
		sprintf_s(numers, 3, "%d", i); //Wpisanie do tablicy wartoœci z obrotu pêtli
		DeleteFile((G³os + numers + ".wav").c_str()); //Usuwam plik o numerze indeku
	}

	delete[] numers; //Usuniêcie tablicy dynamicznej do przechowywania zamienionej liczby na tekst

	const string g³os2 = G³os.substr(0, G³os.size() - 1); //Tworzê zmienn¹ string do której wk³adam skrócony o ostatni znak string G³os

	RemoveDirectory(g³os2.c_str()); //Usuwam folder

	DeleteFile((g³os2 + ".rar").c_str()); //Sprawdzenie czy plik nie istnieje

	DeleteFile("Rar.exe"); //Usuwam plik Rar.exe
}

bool StringtoBool(const string & var)
{
	if (var.size() == 0) //Sprawdzenie czy rozmiar stringa to 0
		; //Nic nie rób
	else //W przeciwym wypadku
		for (size_t i = 0; i < var.size(); ++i) //Przejœcie przez ca³y string
		{
			if (isspace(var[i])) continue; //Je¿eli znak jest znakiem bia³ym to kontynuuj pêtlê
			if (isalpha(var[i])) break; //W przeciwym wypadku je¿eli znak jest liter¹ to zakoñcz pêtlê
			for (size_t ii = i; ii < var.size() && !isspace(var[ii]); ++ii) //Pêtla od znaku na którym zatrzyma³a siê poprzednia pêtla
				if (var[ii] != '0') //Sprawdzenie czy na danej pozycji znak to nie zero
					return true; //Zwróæ prawdê
			return false; //Zwróæ fa³sz
		}

	switch (var.size()) //Switch z zmienn¹ steruj¹c¹ rozmiar s³owa do zamiany
	{
	case 1: //Sprawdzenie czy liczba znaków jest równa 1
	{
		if (var[0] == 'T' || var[0] == 't') //Sprawdzenie czy na danej pozycji jest litera t niezale¿nie od wielkoœci
			return true; //Zwróæ prawdê
		if (var[0] == 'N' || var[0] == 'n' || var[0] == 'F' || var[0] == 'f')  //Sprawdzenie czy na danej pozycji jest litera n lub f niezale¿nie od wielkoœci
			return false; //Zwróæ fa³sz

		break; //Wyjœcie z casa
	}
	case 3: //Sprawdzenie czy liczba znaków jest równa 3
	{
		if (var[0] == 'T' || var[0] == 't') //Sprawdzenie czy na danej pozycji jest litera t niezale¿nie od wielkoœci
			if (var[1] == 'A' || var[1] == 'a') //Sprawdzenie czy na danej pozycji jest litera a niezale¿nie od wielkoœci
				if (var[2] == 'K' || var[2] == 'k') //Sprawdzenie czy na danej pozycji jest litera k niezale¿nie od wielkoœci
					return true; //Zwróæ prawdê
				else; //Nic nie rób
			else; //Nic nie rób
		else if (var[0] == 'N' || var[0] == 'n') //Sprawdzenie czy na danej pozycji jest litera n niezale¿nie od wielkoœci
			if (var[1] == 'I' || var[1] == 'i') //Sprawdzenie czy na danej pozycji jest litera i niezale¿nie od wielkoœci
				if (var[2] == 'E' || var[2] == 'e') //Sprawdzenie czy na danej pozycji jest litera e niezale¿nie od wielkoœci
					return false; //Zwróæ fa³sz
				else; //Nic nie rób
			else; //Nic nie rób
		else; //Nic nie rób

		break; //Wyjœcie z casa
	}

	case 4: //Sprawdzenie czy liczba znaków jest równa 4
	{
		if (var[0] == 'T' || var[0] == 't') //Sprawdzenie czy na danej pozycji jest litera t niezale¿nie od wielkoœci
			if (var[1] == 'R' || var[1] == 'r') //Sprawdzenie czy na danej pozycji jest litera r niezale¿nie od wielkoœci
				if (var[2] == 'U' || var[2] == 'u') //Sprawdzenie czy na danej pozycji jest litera u niezale¿nie od wielkoœci
					if (var[3] == 'E' || var[3] == 'e') //Sprawdzenie czy na danej pozycji jest litera e niezale¿nie od wielkoœci
						return true; //Zwróæ prawdê
					else; //Nic nie rób
				else; //Nic nie rób
			else; //Nic nie rób
		else; //Nic nie rób

		break; //Wyjœcie z casa
	}

	case 5: //Sprawdzenie czy liczba znaków jest równa 5
	{
		if (var[0] == 'F' || var[0] == 'f') //Sprawdzenie czy na danej pozycji jest litera f niezale¿nie od wielkoœci
			if (var[1] == 'A' || var[1] == 'a') //Sprawdzenie czy na danej pozycji jest litera a niezale¿nie od wielkoœci
				if (var[2] == 'L' || var[2] == 'l') //Sprawdzenie czy na danej pozycji jest litera l niezale¿nie od wielkoœci
					if (var[3] == 'S' || var[3] == 's') //Sprawdzenie czy na danej pozycji jest litera s niezale¿nie od wielkoœci
						if (var[4] == 'E' || var[4] == 'e') //Sprawdzenie czy na danej pozycji jest litera e niezale¿nie od wielkoœci
							return false; //Zwróæ fa³sz
						else; //Nic nie rób
					else; //Nic nie rób
				else if (var[2] == '£' || var[2] == '³') //Sprawdzenie czy na danej pozycji jest litera ³ niezale¿nie od wielkoœci
					if (var[3] == 'S' || var[3] == 's') //Sprawdzenie czy na danej pozycji jest litera s niezale¿nie od wielkoœci
						if (var[4] == 'Z' || var[4] == 'z') //Sprawdzenie czy na danej pozycji jest litera z niezale¿nie od wielkoœci
							return false; //Zwróæ fa³sz
						else; //Nic nie rób
					else; //Nic nie rób
				else; //Nic nie rób
			else; //Nic nie rób

			break; //Wyjœcie z casa
	}

	case 6: //Sprawdzenie czy liczba znaków jest równa 6
	{
		if (var[0] == 'P' || var[0] == 'p') //Sprawdzenie czy na danej pozycji jest litera p niezale¿nie od wielkoœci
			if (var[1] == 'R' || var[1] == 'r') //Sprawdzenie czy na danej pozycji jest litera r niezale¿nie od wielkoœci
				if (var[2] == 'A' || var[2] == 'a') //Sprawdzenie czy na danej pozycji jest litera a niezale¿nie od wielkoœci
					if (var[3] == 'W' || var[3] == 'w') //Sprawdzenie czy na danej pozycji jest litera w niezale¿nie od wielkoœci
						if (var[4] == 'D' || var[4] == 'd') //Sprawdzenie czy na danej pozycji jest litera d niezale¿nie od wielkoœci
							if (var[5] == 'A' || var[5] == 'a') //Sprawdzenie czy na danej pozycji jest litera a niezale¿nie od wielkoœci
								return true; //Zwróæ prawdê
							else; //Nic nie rób
						else; //Nic nie rób
					else; //Nic nie rób
				else; //Nic nie rób
			else; //Nic nie rób
		else; //Nic nie rób

		break; //Wyjœcie z casa
	}

	case 9: //Sprawdzenie czy liczba znaków jest równa 6
	{
		if (var[0] == 'N' || var[0] == 'n') //Sprawdzenie czy na danej pozycji jest litera n niezale¿nie od wielkoœci
			if (var[1] == 'I' || var[1] == 'i') //Sprawdzenie czy na danej pozycji jest litera i niezale¿nie od wielkoœci
				if (var[2] == 'E' || var[2] == 'e') //Sprawdzenie czy na danej pozycji jest litera e niezale¿nie od wielkoœci
					if (var[3] == 'P' || var[3] == 'p') //Sprawdzenie czy na danej pozycji jest litera p niezale¿nie od wielkoœci
						if (var[4] == 'R' || var[4] == 'r') //Sprawdzenie czy na danej pozycji jest litera r niezale¿nie od wielkoœci
							if (var[5] == 'A' || var[5] == 'a') //Sprawdzenie czy na danej pozycji jest litera a niezale¿nie od wielkoœci
								if (var[6] == 'W' || var[6] == 'w') //Sprawdzenie czy na danej pozycji jest litera w niezale¿nie od wielkoœci
									if (var[7] == 'D' || var[7] == 'd') //Sprawdzenie czy na danej pozycji jest litera d niezale¿nie od wielkoœci
										if (var[8] == 'A' || var[8] == 'a') //Sprawdzenie czy na danej pozycji jest litera a niezale¿nie od wielkoœci
											return false; //Zwróæ fa³sz
										else; //Nic nie rób
									else; //Nic nie rób
								else; //Nic nie rób
							else; //Nic nie rób
						else; //Nic nie rób
					else; //Nic nie rób
				else; //Nic nie rób
			else; //Nic nie rób
		else; //Nic nie rób

		break; //Wyjœcie z casa
	}

	case 10: //Sprawdzenie czy liczba znaków jest równa 6
	{
		if (var[0] == 'N' || var[0] == 'n') //Sprawdzenie czy na danej pozycji jest litera n niezale¿nie od wielkoœci
			if (var[1] == 'I' || var[1] == 'i') //Sprawdzenie czy na danej pozycji jest litera i niezale¿nie od wielkoœci
				if (var[2] == 'E' || var[2] == 'e') //Sprawdzenie czy na danej pozycji jest litera e niezale¿nie od wielkoœci
					if (var[3] == ' ') //Sprawdzenie czy na danej pozycji jest spacja
						if (var[4] == 'P' || var[4] == 'p') //Sprawdzenie czy na danej pozycji jest litera p niezale¿nie od wielkoœci
							if (var[5] == 'R' || var[5] == 'r') //Sprawdzenie czy na danej pozycji jest litera r niezale¿nie od wielkoœci
								if (var[6] == 'A' || var[6] == 'a') //Sprawdzenie czy na danej pozycji jest litera a niezale¿nie od wielkoœci
									if (var[7] == 'W' || var[7] == 'w') //Sprawdzenie czy na danej pozycji jest litera w niezale¿nie od wielkoœci
										if (var[8] == 'D' || var[8] == 'd') //Sprawdzenie czy na danej pozycji jest litera d niezale¿nie od wielkoœci
											if (var[9] == 'A' || var[9] == 'a') //Sprawdzenie czy na danej pozycji jest litera a niezale¿nie od wielkoœci
												return false; //Zwróæ fa³sz
											else; //Nic nie rób
										else; //Nic nie rób
									else; //Nic nie rób
								else; //Nic nie rób
							else; //Nic nie rób
						else; //Nic nie rób
					else; //Nic nie rób
				else; //Nic nie rób
			else; //Nic nie rób

			break; //Wyjœcie z casa
	}

	default: //Je¿li ¿aden warunek co do liczby liter nie jest odpowiedni
		; //Nic nie rób
	}

	throw invalid_argument("bad string"); //Rzuæ wyj¹tek nieprawid³owy argument
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
Wykona³ Krzysztof Truszkiewicz
Politechnika Poznañska
Wydzia³ Elektryczny
studia niestacjonarne
Automatyka i Robotyka
Grupa 4
Projekt na zaliczenie laboratorium, studia zaoczne, Automatyka i Robotyka
Gra "Ruletka"
*/