//------------------ deklaracje bibiotek u¿ywanych w programie -----------------------
#include <ctime> //time()
#include <fstream> //Obs³uga pliku
#include <io.h> //!_access()
#include <iostream> //Obs³uga strumenia cout,cin
#include <locale.h> //setlocale()
#include <random> //random_device,distribution()
#include <sstream> //stringstream, zamiana liczby na string
#include <string> //Obs³uga stringów
#include <windows.h> //SYSTEMTIME,GetSystemTime(),Sleep(),HANDLE,GetStdHandle(),SetConsoleTextAttribute()
#include <MMsystem.h> //PlaySound() (Aby dzia³a³o trzeba dodaæ winmm.lib lub coredll.lib do linkera (konsolidatora))
#pragma comment(lib, "winmm.lib") //Dodanie winmm.lib do linkera (konsolidatora)
#include <urlmon.h> //URLDownloadToFileA() (Aby dzia³a³o trzeba dodaæ urlmon.lib do linkera (konsolidatora))
#pragma comment(lib, "urlmon.lib") //Dodanie urlmon.lib do linkera (konsolidatora)
//-------------------------------------------------------------------------------------

//-------------------------- deklaracja wyboru przestrzeni nazw std -------------------
using namespace std;
//-------------------------------------------------------------------------------------

//---------------------------------- deklaracje funkcji w³asnych ----------------------
string Obstaw(); //Funkcja wczytywania typu zak³ad, do string aby mieæ tak¿e zak³ady sk³adaj¹ce siê z liter i cyfr
void Wczytaj_Kwotê_Zak³adu(int & kwota, const int & iloœæ_pieniêdzy); //Funkcja wczytywania kwoty zak³adu aby uchroniæ siê przed problemem wpisania znaku,litery zamiast liczby i osbstawienie za wiêksz¹ kwotê ni¿ siê ma
int Zakrêæ_Ruletk¹(); //Funkcja losuje liczbê z ko³a ruletki
int SprawdŸ_Zak³ad(const int & kwota, string typ_zak³adu, const int & wylosowana_liczba); //Funcja sprawdza czy wygraliœmy i podaje kwote wygranej/przegranej/odzysku czêœci w³o¿onych pieniêdzy
bool Czy_Kontynuowaæ(const int & iloœæ_pieniêdzy); //Funkcja sprawdzj¹ca czy ma siê œrodki do gry, je¿eli ma siê to pyta czy chce siê graæ dalej
int Wylosuj(const int & od_liczby, const int & do_liczby); //Funkcja która losuje liczby od liczby do liczby losowo lub psudolosowo metod¹ MT
void Odczytaj_liczbê(const int & wylosowana_liczba, const string & typ_zak³adu); //Funkcja do odczytu wylosowanej liczby i jej po³o¿enia
void Wczytaj_z_pliku(ofstream & log_ogólny, fstream & log, char & co_kontynuowaæ, int & iloœæ_pieniêdzy, int & kwota_zak³adu, int & wylosowana_liczba, string & typ_zak³adu); //Funkcja wczytuj¹ca z pliku ostatnie ruchy gracza
void SprawdŸ_Pliki(); //Funkcja sprawdzaj¹ca czy wszystkie pliki dŸwiêkowe s¹ na miejscu
void SprawdŸ_ustawienia(); //sprawdzanie poprawnoœci deklaracji definicji preprocesora do zmian funcjonowania programu
void Og³oœ_wynik(const int & wygrana, const int & kwota_zak³adu, int & iloœæ_pieniêdzy, ofstream & log_ogólny, fstream & log); //Funkcja informuj¹ca gracza o wyniku zak³adu
void Koniec_gry(ofstream & log_ogólny, fstream & log, int & iloœæ_pieniêdzy); //Funkcja informuj¹ca o wynikach gracza jak skoñczy³ grê
void Pêtla_g³ówna(int & wygrana, int & kwota_zak³adu, int & iloœæ_pieniêdzy, ofstream & log_ogólny, fstream & log, char & co_kontynuowaæ, string & typ_zak³adu, int & wylosowana_liczba); //Funkcja wywo³uj¹ca funkcje obs³uguj¹ce wszystkie elementy ruletki
void Ustaw_ustawienia(string & tekst); //Funkcja zamieniaj¹ca wczytan¹ linijkê z ustawieniami na zmianê ustawieñ programu
//-------------------------------------------------------------------------------------

//------------------------------- deklaracje funkcji obcych ---------------------------
void Change_Col(const int & num_of_col); //Funkcja zmieniaj¹ca kolor tekstu 0 - czarny 1 - niebieski 2 - zielony 3 - b³êkitny 4 - czerwony 5 - purpurowy 6 - ¿ó³ty 7 - bia³y 8 - szary 9 - jasnoniebieski 10 - jasnozielony 11 - jasnob³êkitny 12 - jasnoczerwony 13 - jasnopurpurowy 14 - jasno¿ó³ty 15 - jaskrawobia³y
void Hide_Cursor(); //Funkcja w³¹cza pokazanie kursora tekstowego
void Show_Cursor(); //Funkcja wy³¹cza pokazanie kursora tekstowego
//-------------------------------------------------------------------------------------

//----------------------------- deklaracje tablic pomocniczych ------------------------
const int Ruletka_ko³o[] = { 0, 32, 15, 19, 4, 21, 2, 25, 17, 34, 6, 27, 13, 36, 11, 30, 8, 23, 10, 5, 24, 16, 33, 1, 20, 14, 31, 9, 22, 18, 29, 7, 28, 12, 35, 3, 26 }; // Kolejnoœæ liczb zgodna z ko³em ruletki
const char Ruletka_plansza_kolor[] = { 'g','r','b','r','b','r','b','r','b','r','b','b','r','b','r','b','r','b','r','r','b','r','b','r','b','r','b','r','b','b','r','b','r','b','r','b','r' }; //Kolor dla ka¿dej liczby na planszy
const int Ruletka_plansza_kolor_col[] = { 2,4,8,4,8,4,8,4,8,4,8,8,4,8,4,8,4,8,4,4,8,4,8,4,8,4,8,4,8,8,4,8,4,8,4,8,4 }; //Kod koloru do funkcji zmiany koloru tekstu dla ka¿dej liczby na planszy
//-------------------------------------------------------------------------------------

//------ deklaracje zmiennych globalnych do zmian funcjonowania programu --------------
short iloœæ_minimalna_obrotów_ruletki = 2; // Minimalna iloœæ obrotów ruletki przed podaniem wartoœci wylosowanej
short iloœæ_max_dodatkowych_obrotów_ruletki = 3; // Maksymalna iloœæ dodatkowych obrotów ruletki przed podaniem wartoœci wylosowanej
short czas_przeskoku_kulki_szybki = 50; //Czas w ms przerwy pomiêdzy przeskokami na pocz¹tek losowania na kolejn¹ liczbê na kole ruletki
short czas_przeskoku_kulki_wolny = 75; //Czas w ms przerwy pomiêdzy przeskokami pod koniec losowania na kolejn¹ liczbê na kole ruletki
short czas_przerwy_dzwiêku = 500; //Czas w ms przerwy pomiêdzy pikniêciami oznaczaj¹cymi wynik zak³adu
short styl_liczenia_wygranej = 1; //0 dla odejmowania w³o¿onych w zak³ad pieniêdzy (przy tym zak³ady 1:1 nie zwiêkszaj¹ iloœæ_pieniêdzy), 1 dla nie odejmowania (przy tym zak³ady 1:1 zwiêkszaj¹ iloœæ_pieniêdzy)
int kwota_pocz¹tkowa = 1000; //Iloœæ $ z którymi zaczyna siê grê
short stan_dŸwiêków = 1; //Czy w³¹czone dŸwiêki 1 <-tak 0 <-nie
short czy_kontynuowaæ_grê = 1; //Czy w³¹czone kontynuowanie gry od skoñczonej poprzednio pozycji 1 <-tak 0 <-nie
short g³os_odczytu_numeru = 1; //Wybór g³osu który odczyta wylosowany numer 0 <- Brak 1 <- Jacek (Ivona) 2 <- Ewa (Ivona) 3 <- Maja (Ivona) 4 <- Jan (Ivona) 5 <- Jacek (Ivona 2) 6 <- Ewa (Ivona 2) 7 <- Maja (Ivona 2) 8 <- Jan (Ivona 2) 9 <- Agata (Scansoft)
short g³os_szybkoœæ_odczytu_numeru = 4; //Wybór szybkoœci mowy, skala od 1 do 5
short efekty_dŸwiêkowe = 1; //Czy w³¹czone efekty dŸwiêkowe 1 <-tak 0 <-nie
//-------------------------------------------------------------------------------------

//---------------------------- deklaracje zmiennych globalnych ------------------------
SYSTEMTIME Czas; //Struktura do której zapisywana jest aktualna data i czas
bool G³osyKompletne = true;
bool EfektyKompletne = true;
string G³os;
//-------------------------------------------------------------------------------------

int main()
{
	//Inicjowanie funkcji
	setlocale(LC_ALL, "polish"); // W celu polskich liter w konsoli
	srand((unsigned int)time(nullptr)); //Zainicjowanie generatorza LCG (Liniowy Generator Kongruentny) dla ma³o wa¿nych liczb
	Show_Cursor(); //Pokazanie kursora tekstowego w konsoli

//	string link = "https://github.com/talez2709/Ruletka/raw/master/Ruletka/G%C5%82os/Agata%20_1/0.wav";
//	string save = "a/bankrut.wav";

	//if (URLDownloadToFileA(nullptr, link.c_str(), save.c_str(), 0, nullptr) == S_OK) {
	//}
	//else {
	//	cout << "B³¹d pobierania" << endl;
	//}

	SprawdŸ_ustawienia();
	SprawdŸ_Pliki();

	//int a = 10;
	//string b = "10";
	//Odczytaj_liczbê(a, b);
	//b = "p";
	//Odczytaj_liczbê(a, b);
	//b = "r";
	//Odczytaj_liczbê(a, b);
	//b = "g";
	//Odczytaj_liczbê(a, b);
	//b = "k1";
	//Odczytaj_liczbê(a, b);
	//b = "w1";
	//Odczytaj_liczbê(a, b);

	//string c = "iloœæ_minimalna_obrotów_ruletki 000";
	//Ustaw_ustawienia(c);

	//Inicjowanie zmiennych lokalnych
	ofstream log_ogólny; //Utworzenie typu do celu zapisu do pliku
	log_ogólny.open("log_ogólny.txt", ios::app); //Otworzenie pliku z ustawieniem kursora zapisu do pliku
	fstream log; //Utworzenie typu do celu zapisu i/lub odczytu do i/lub z pliku
	int iloœæ_pieniêdzy = kwota_pocz¹tkowa, kwota_zak³adu, wylosowana_liczba, wygrana; //Zmienne do których wczytuje siê wartoœci liczbowe pobrane od u¿ytkownika takie jak kwota zak³adu a przechowuje iloœæ posiadanych pieniêdzy a tak¿e przechowuje wyniki funkcji losowania liczby z ruletki i kwote wygran¹ z zak³adu
	string typ_zak³adu; //Przechowuje typ zak³adu wprowadzony przez u¿ytkownika
	char co_kontynuowaæ; //Deklaracja znaku który przechowuje nazwany znakiem punkt od którego kontynuowaæ runde

	Wczytaj_z_pliku(log_ogólny, log, co_kontynuowaæ, iloœæ_pieniêdzy, kwota_zak³adu, wylosowana_liczba, typ_zak³adu);

	do
	{
		Pêtla_g³ówna(wygrana, kwota_zak³adu, iloœæ_pieniêdzy, log_ogólny, log, co_kontynuowaæ, typ_zak³adu, wylosowana_liczba);
		co_kontynuowaæ = 'n'; //Przypisanie znaku rozpoczêcia rundy od pocz¹tku
	} while (Czy_Kontynuowaæ(iloœæ_pieniêdzy)); //Pêtla dza³aj¹ca do czasu wartoœci fa³sz zwróconej przez funkcjê Czy_kontynuowaæ

	Koniec_gry(log_ogólny, log, iloœæ_pieniêdzy);

	system("pause"); //Wywo³anie funkcji wymagaj¹cej do zamkniêcia naciœniêcie dowolnego klawisza

	return 0; //Zwrócenie wartoœæ 0, czyli porogram zakoñczy³ siê bez b³êdu
}

string Obstaw()
{
	string zaklad_typ; //Deklaracja zmiennej typu string przechowywuj¹cej typ zak³adu

	do { //Pêtla do aby wykona³a siê conajmniej raz
		cout << "Jak¹ opcje chcesz obstawic ? (zgodnie z poni¿szym opisem) :" << endl; //Zadanie pytania u¿ytkownikowi
		cout << "p - parzyste" << endl; //Wskazaæ mo¿liw¹ odpowiedŸ
		cout << "n - nieparzyste" << endl; //Wskazaæ mo¿liw¹ odpowiedŸ
		cout << "r - czerwone(red)" << endl; //Wskazaæ mo¿liw¹ odpowiedŸ
		cout << "b - czarne(black)" << endl; //Wskazaæ mo¿liw¹ odpowiedŸ
		cout << "g - górna po³owa" << endl; //Wskazaæ mo¿liw¹ odpowiedŸ
		cout << "d - dolna po³owa" << endl; //Wskazaæ mo¿liw¹ odpowiedŸ
		cout << "k1, k2, k3 - kolumna 1, kolumna 2, kolumna 3" << endl; //Wskazaæ mo¿liw¹ odpowiedŸ
		cout << "w1, w2, ..., w12 - wiersz trzech numerów" << endl; //Wskazaæ mo¿liw¹ odpowiedŸ
		cout << "0 - 36 - pojedyncze pole o odpowiednim numerze" << endl; //Wskazaæ mo¿liw¹ odpowiedŸ
		cin >> zaklad_typ; //Pobranie od u¿ytkownika odpowiedzi na pytanie
	} while ( //U¿ywam takiej sk³adni poniewa¿ jeœli masz wyra¿enie z logicznymi operatorami && lub ||, to w momencie gdy wynik wyra¿enia ju¿ jest znany, to nie jest wyliczany dalej. (Poniewa¿ C++ jest "leniwe", co zarazem jest optymalne)
		zaklad_typ != "p" && //Sprawdzanie czy wprowadzono zak³ad na liczby parzyste
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
		zaklad_typ != "36" //Sprawdzanie czy wprowadzono zak³ad na liczbê 36
		); //Je¿eli któryœ z warunków siê niezgadza to pêtla nie jest kontynuowana

	return zaklad_typ; //Zwracam typ zak³adu podany przez u¿ytkownika
}

void Wczytaj_Kwotê_Zak³adu(int & kwota_zak³adu, const int & iloœæ_pieniêdzy)
{
	string kwota_zak³adu_s; //Deklaracja zmiennej typu string do wczytywania kwoty aby zabezpieczyæ siê przed b³êdem wpisania do zmiennej liczbowej litery

	while (true) //Rozpoczêcie pêtli nieskoñczonej
	{
		cout << "Masz " << iloœæ_pieniêdzy << "$, jak¹ kwotê chcesz obstawiæ wynik?" << endl; //Podanie akualnego stanu konta i zadanie pytania o kwotê zak³adu
		cin >> kwota_zak³adu_s; //Pobranie w tekœcie kwoty zak³¹du
		kwota_zak³adu = atoi(kwota_zak³adu_s.c_str()); //Zmiana stringaa na inta i wpisanie do zmiennej kwota_zak³adu
		if (kwota_zak³adu > 0 && kwota_zak³adu <= iloœæ_pieniêdzy) //Sprawdzenie czy kwota zak³¹du jest wiêksza od zeri i mniejsza lub równa dostêpnej gotówce
			break; //Je¿eli tak to zatrzymuje pêtle
		else //W przeciwym wypadku
			if (kwota_zak³adu == 0) //Je¿eli wynikiem zamiany na liczbê jest zero (wynikiem zamiany jest zero kiedy tekst to zero lub kiedy jest b³¹d zamiany) to
			{
				bool czy_zero = true; //Utworzenie zmiennej informuj¹cej czy znaleziono zero w tekœcie i przypisanie jej wartoœci true
				for (short i = 0; i < (short)kwota_zak³adu_s.size(); ++i) //Rozpoczêcie pêtli numerowanej przez zmienn¹ i przez wszystkie znaki wczytanego tekst
					if (kwota_zak³adu_s[i] != '0') //Je¿eli znak na i-tej pozycji
					{
						cout << "Wprowadzi³eæ nieprawid³ow¹ wartoœæ" << endl; //Poinformowanie u¿ytkownika, ¿e nie mo¿e obstawiæ tekstowego
						if (stan_dŸwiêków) cout << "\a"; //Wywo³anie pikniêcia w g³oœniku
						czy_zero = false; //Zmiana wartoœci zmiennej czy znaleziono zero w tekœcie na false
						break; //Zatrzymanie pêtli
					}
				if (czy_zero) //Sprawdzenie czy znaleziono same zera w tekœcie, je¿eli tak to
				{
					cout << "Nie mo¿esz obstawiæ zerowego zak³adu" << endl; //Poinformowanie u¿ytkownika, ¿e nie mo¿e obstawiæ zerowego zak³adu
					if (stan_dŸwiêków) cout << "\a"; //Wywo³anie pikniêcia w g³oœniku
				}
			}
			else if (kwota_zak³adu > iloœæ_pieniêdzy) //Je¿eli u¿ytkownik chce obstawiæ za wiêcej ni¿ ma, to
			{
				cout << "Nie masz tyle pieniêdzy" << endl; //Poinformowanie go o tym
				if (stan_dŸwiêków) cout << "\a"; //Wywo³anie pikniêcia w g³oœniku
			}
			else if (kwota_zak³adu < 0) //Je¿eli u¿ytkownik chce obstawiæ za ujemn¹ kwotê, to
			{
				cout << "Nie mo¿esz obstawiæ ujemn¹ kwot¹ zak³adu" << endl; //Poinformowanie go o tym
				if (stan_dŸwiêków) cout << "\a"; //Wywo³anie pikniêcia w g³oœniku
			}
	}
}

int Zakrêæ_Ruletk¹()
{
	int iloœæ_zakrêceñ = rand() % (iloœæ_max_dodatkowych_obrotów_ruletki + 1) + iloœæ_minimalna_obrotów_ruletki; //Deklarowanie i przpisanie zmiennej liczbowj zawieraj¹c¹ pseudolosow¹ (o niskiej pseoudolosowoœci) iloœæ obrotów ruletk¹ ((od 0 do max dodatkowych obrotów ruletki) + minimalna iloœæ obrotów ruletki) zanim nastêpi finalny obrót
	double czas_przeskoku_kulki_szybki_opóŸnienie = czas_przeskoku_kulki_szybki / (iloœæ_zakrêceñ * 37.0); //Deklarowanie i przpisanie zmiennej zmiennoprzecinkowej zawieraj¹c¹ czas o ile kolejna wartoœæ na kole ruletki powinna byæ szybciej pokazana
	Hide_Cursor(); //Ukrycie kursora tekstowego w konsoli
	for (int i = 0; i < iloœæ_zakrêceñ; ++i) //Wykonanie iloœæ_zakrêceñ obrotów ruletk¹
		for (int ii = 0; ii < 37; ++ii) //Przejœcie przez wszystkie pozycje ruletki
		{
			Change_Col(Ruletka_plansza_kolor_col[Ruletka_ko³o[ii]]); //Zmiana koloru tekstu w konsoli zgodnie z kolorem numeru na ruletce
			cout << Ruletka_ko³o[ii]; //Wypisanie numeru na kole ruletki na którym znajduje siê pêtla
			Sleep((DWORD)(czas_przeskoku_kulki_szybki_opóŸnienie*((double)i*37.0 + (double)ii))); //Przestój który zwiêksza siê co zmianê pozycji pêtli
			Change_Col(7); //Powrót do standardowego koloru tekstu w konsoli
			cout << "\b\b" << "  " << "\b\b"; //Cofniêcie kursora tekstowego do lewej strony konsoli aby zape³niæ podem spacjami czyli niewidocznym znakiem wiersza konsoli aby widaæ przejœcie pomiêdzy liczbami na ruletce
		}
	int wylosowana_pozycja = Wylosuj(0, 36); //Deklarowanie i przpisanie zmiennej liczbowj zawieraj¹c¹ losow¹ lub pseudolosow¹ liczbê (o wysokiej pseoudolosowoœci) pozycjê na ruletce
	double czas_przeskoku_kulki_wolny_przyspieszenie = (czas_przeskoku_kulki_wolny - czas_przeskoku_kulki_szybki) / (double)(wylosowana_pozycja); //Deklarowanie i przpisanie zmiennej zmiennoprzecinkowej zawieraj¹c¹ czas o ile kolejna wartoœæ na kole ruletki powinna byæ szybciej pokazana
	for (int i = 0; i < wylosowana_pozycja; ++i) //Przejœcie przez pozycje do pozycji o 1 mniejszej od wylosowanej pozyji na ruletce
	{
		Change_Col(Ruletka_plansza_kolor_col[Ruletka_ko³o[i]]); //Zmiana koloru tekstu w konsoli zgodnie z kolorem numeru na ruletce
		cout << Ruletka_ko³o[i]; //Wypisanie numeru na kole ruletki na którym znajduje siê pêtla
		Sleep((DWORD)(czas_przeskoku_kulki_szybki + (czas_przeskoku_kulki_wolny_przyspieszenie*i))); //Przestój który zwiêksza siê co zmianê pozycji pêtli
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

int SprawdŸ_Zak³ad(const int & kwota, string typ_zak³adu, const int & wylosowana_liczba)
{
	int wygrana = kwota; //Deklaracja zmiennej przechowywuj¹ca kwotê wygran¹ lub zwrócon¹ przy wylosowaniu 0

	if (wylosowana_liczba == 0) //Warunek sprawdzaj¹cy czy wylosowano 0
	{ //Je¿eli tak to
		if (typ_zak³adu == "p") wygrana /= 2; //Je¿eli typ zak³adu by³ p to wygrana, a dok³adniej zwrot wynosi po³owê zak³adu
		else if (typ_zak³adu == "n") wygrana /= 2; //Je¿eli typ zak³adu by³ p to wygrana, a dok³adniej zwrot wynosi po³owê zak³adu
		else if (typ_zak³adu == "r") wygrana /= 2; //Je¿eli typ zak³adu by³ r to wygrana, a dok³adniej zwrot wynosi po³owê zak³adu
		else if (typ_zak³adu == "b") wygrana /= 2; //Je¿eli typ zak³adu by³ b to wygrana, a dok³adniej zwrot wynosi po³owê zak³adu
		else if (typ_zak³adu == "g") wygrana /= 2; //Je¿eli typ zak³adu by³ g to wygrana, a dok³adniej zwrot wynosi po³owê zak³adu
		else if (typ_zak³adu == "d") wygrana /= 2; //Je¿eli typ zak³adu by³ d to wygrana, a dok³adniej zwrot wynosi po³owê zak³adu
		else if (typ_zak³adu[0] == 'k') wygrana *= 0; //Je¿eli typ zak³adu by³ k to przegra³o siê zak³ad
		else if (typ_zak³adu[0] == 'w') wygrana *= 0; //Je¿eli typ zak³adu by³ k to przegra³o siê zak³ad
		else if (typ_zak³adu[0] == '0') wygrana *= 35; //Je¿eli typ zak³adu by³ 0 to przegra³o siê zak³ad
	}
	else //Je¿eli wylosowana liczba nie jest zerem to
	{
		if (typ_zak³adu == "p") //Je¿eli typ zak³adu to p
			if (wylosowana_liczba % 2 == 0) wygrana *= 1; //To sprawdzam czy wylosowana liczba jest parzysta, je¿eli tak to wygrana jest 1:1
			else wygrana *= 0; //Je¿eli wylosowana liczba nie jest parzysta to przegra³o siê zak³ad
		else if (typ_zak³adu == "n") //Je¿eli typ zak³adu to n
			if (wylosowana_liczba % 2 == 1) wygrana *= 1; //To sprawdzam czy wylosowana liczba jest nieparzysta, je¿eli tak to wygrana jest 1:1
			else wygrana *= 0; //Je¿eli obstawiony numer nie jest nieparzysta to przegra³o siê zak³ad
		else if (typ_zak³adu == "r") //Je¿eli typ zak³adu to n
			if (Ruletka_plansza_kolor[wylosowana_liczba] == 'r') wygrana *= 1; //To sprawdzam czy wylosowana liczba jest czerwona, je¿eli tak to wygrana jest 1:1
			else wygrana *= 0; //Je¿eli wylosowana liczba nie jest czerwony to przegra³o siê zak³ad
		else if (typ_zak³adu == "b") //Je¿eli typ zak³adu to n
			if (Ruletka_plansza_kolor[wylosowana_liczba] == 'b') wygrana *= 1; //To sprawdzam czy wylosowana liczba jest czarna, je¿eli tak to wygrana jest 1:1
			else wygrana *= 0; //Je¿eli wylosowana liczba nie jest czarny to przegra³o siê zak³ad
		else if (typ_zak³adu == "g") //Je¿eli typ zak³adu to g
			if (wylosowana_liczba < 19) wygrana *= 1; //To sprawdzam czy wylosowana liczba jest od 1 do 18, je¿eli tak to wygrana jest 1:1
			else wygrana *= 0; //Je¿eli wylosowana liczba nie nale¿y do przedzia³u [1,18] to przegra³o siê zak³ad
		else if (typ_zak³adu == "d") //Je¿eli typ zak³adu to d
			if (wylosowana_liczba > 18) wygrana *= 1; //To sprawdzam czy wylosowana liczba jest od 19 do 36, je¿eli tak to wygrana jest 1:1
			else wygrana *= 0; //Je¿eli wylosowana liczba nie nale¿y do przedzia³u [19,36] to przegra³o siê zak³ad
		else if (typ_zak³adu[0] == 'k') //Je¿eli typ zak³adu to k
			if ((wylosowana_liczba - 1) % 3 == typ_zak³adu[1] - 49) wygrana *= 2; //To sprawdzam czy wylosowana liczba jest z obstawionej kolumny, je¿eli tak to wygrana jest 2:1
			else wygrana *= 0; //Je¿eli wylosowana liczba nie jest z obstawionej kolumny to przegra³o siê zak³ad
		else if (typ_zak³adu[0] == 'w') //Je¿eli typ zak³adu to w
			if (((wylosowana_liczba - 1) / 3 + 1) == atoi(typ_zak³adu.erase(0, 1).c_str())) wygrana *= 11; //To sprawdzam czy wylosowana liczba jest z obstawionego wiersza, je¿eli tak to wygrana jest 11:1
			else wygrana *= 0; //Je¿eli wylosowana liczba nie jest z obstawionego wiersza to przegra³o siê zak³ad
		else if (wylosowana_liczba == atoi(typ_zak³adu.c_str())) wygrana *= 35; //Je¿eli typ zak³adu to liczba, to sprawdzam czy wylosowana liczba jest równa obstawionej liczbie, je¿eli tak to wygrana jest 35:1
		else wygrana *= 0; //Je¿eli wylosowana liczba nie jest równa obstawionej liczbie to przegra³o siê zak³ad
	}

	if (wygrana >= kwota) cout << "Obstawiles poprawnie, wygrywasz " << wygrana << "$." << endl; //Je¿eli wygrana jest wiêksza lub równa obstawionej kwocie to informujê o tym, ¿e wygra³
	else if (wygrana == kwota / 2) cout << "Obstawiles niepoprawnie lecz uda³o Ci siê, dostajesz po³owê zak³adu " << wygrana << "$." << endl; //Je¿eli wygrana jest równa po³owie obstawionej kwocie to informujê o tym, ¿e przegra³ po³owe stawki
	else cout << "Obstawiles niepoprawnie, przegra³eœ " << kwota << "$." << endl; //Je¿eli wygrana jest równa zero to informujê o tym, ¿e przegra³

	return wygrana; //Zwracam wartoœ wygranej lub zwrotu
}

bool Czy_Kontynuowaæ(const int & iloœæ_pieniêdzy)
{
	string tak_nie; //Zadeklarowanie zmiennej typu string

	if (iloœæ_pieniêdzy == 0) //Je¿eli posiadana iloœæ gotówki jest róna 0
	{
		cout << "Nie mo¿esz kontynuowaæ, przegra³eœ wszystko" << endl; //Poinformowanie u¿ytkownika, ¿e jest bankrutem
		return false; //Zwrot wartoœci false, co oznacza, ¿e kolejna runda siê nie odbêdzie
	}

	while (true) //Rozpoczêcie pêtli nieskoñczonej
	{
		cout << "Na koncie masz " << iloœæ_pieniêdzy << "$, czy chcesz grac dalej('t' - tak, 'n' - nie) ?" << endl; //Pointormowanie o stanie konta i zapytanie o to czy gra dalej
		cin >> tak_nie; //Pobranie od u¿ytkownika odpowiedzi na powy¿sze pytanie
		if (tak_nie == "t" || tak_nie == "tak" || tak_nie == "Tak" || tak_nie == "TAK" || tak_nie == "n" || tak_nie == "nie" || tak_nie == "Nie" || tak_nie == "NIE") //Sprawdzenie czy odpowiedŸ pasuje do mo¿liwoœci
			if (tak_nie[0] == 't' || tak_nie[0] == 'T') return true; //Je¿eli pasuje to sprawdzam czy pierwsza litera to t i zwracam wartoœæ true
			else return false; //W przeciwym wypadku zwracam wartoœæ false
	}
}

void Change_Col(const int & num_of_col)
{
	HANDLE h_wyj = GetStdHandle(STD_OUTPUT_HANDLE); //Stworzenie zmiennej typu uchwyt i przypisanie do standardowego wyjœcia
	SetConsoleTextAttribute(h_wyj, num_of_col); //Zmienia atrybut koloru tekstu w konsoli
}

void Hide_Cursor()
{
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE); //Stworzenie zmiennej typu uchwyt i przypisanie do standardowego wyjœcia
	CONSOLE_CURSOR_INFO hCCI; //Stworzenie zmiennej typu informacji o kursorze tekstowym w konsoli
	GetConsoleCursorInfo(hConsoleOut, &hCCI); //Przypisanie do zmiennej informacji o kursorze tekstowym w konsoli
	hCCI.bVisible = FALSE; //Zmiena widocznoœci kursora na niewidoczny
	SetConsoleCursorInfo(hConsoleOut, &hCCI); //Ustawienie widocznoœci kursora zgodnie z poprzedni¹ zmienn¹
}

void Show_Cursor()
{
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE); //Stworzenie zmiennej typu uchwyt i przypisanie do standardowego wyjœcia
	CONSOLE_CURSOR_INFO hCCI; //Stworzenie zmiennej typu informacji o kursorze tekstowym w konsoli
	GetConsoleCursorInfo(hConsoleOut, &hCCI); //Przypisanie do zmiennej informacji o kursorze tekstowym w konsoli
	if (hCCI.bVisible != TRUE) //Sprawdzenie czy wartoœæ widocznoœci kursorsora tekstego w konsoli jest ró¿na od prawdy
	{
		hCCI.bVisible = TRUE;//Je¿eli tak, to zmiena widocznoœci kursora na widoczny
		SetConsoleCursorInfo(hConsoleOut, &hCCI); //I ustawienie widocznoœci kursora zgodnie z poprzedni¹ zmienn¹
	}
}

int Wylosuj(const int & od_liczby, const int & do_liczby)
{
	random_device generator; //Generator liczb losowych, który generuje niedeterministyczne liczby losowe, jeœli s¹ obs³ugiwane.
	if (generator.entropy() != 32) //Je¿eli entropia jest mniejsza od 32 oznacza, ¿e komputer nie dysponuje mo¿liwoœci¹ u¿ycia tego generatora liczb losowy
	{
#if defined(__x86_64__) || defined(_M_X64) || defined(__x86_64) || defined(__amd64) || defined(__amd64__) || defined(_M_AMD64) //Sprawdzenie czy sytem operacyjny jest 64-bitowy
		mt19937_64 generator((unsigned int)time(nullptr)); //Dla 64 bitowego systemu zamiast powy¿szego generatora u¿ywa generator liczb pseudolosowych Mersenne Twister 19937 w wersji 64 bitowej
#else
		mt19937 generator((unsigned int)time(nullptr)); //Dla 32 bitowego systemu zamiast powy¿szego generatora u¿ywa generator liczb pseudolosowych Mersenne Twister 19937 w wersji 32 bitowej
#endif
	}
	uniform_int_distribution<int> distribution(od_liczby, do_liczby); //Wsazuje zakres generowanych liczb
	return distribution(generator); //Zwraca wygenerowan¹ liczbê
}

void Odczytaj_liczbê(const int & wylosowana_liczba, const string & typ_zak³adu) {
	if ((g³os_odczytu_numeru == 0) || (!G³osyKompletne)) return;

	stringstream numers;
	numers << wylosowana_liczba;
	PlaySound((G³os + numers.str() + ".wav").c_str(), nullptr, SND_SYNC);
	if (typ_zak³adu == "p" || typ_zak³adu == "n")
		if (wylosowana_liczba % 2 == 0)
			PlaySound((G³os + "p.wav").c_str(), nullptr, SND_SYNC);
		else
			PlaySound((G³os + "n.wav").c_str(), nullptr, SND_SYNC);
	else if (typ_zak³adu == "r" || typ_zak³adu == "b")
		if (Ruletka_plansza_kolor[wylosowana_liczba] == 'r')
			PlaySound((G³os + "r.wav").c_str(), nullptr, SND_SYNC);
		else
			PlaySound((G³os + "b.wav").c_str(), nullptr, SND_SYNC);
	else if (typ_zak³adu == "g" || typ_zak³adu == "d")
		if (wylosowana_liczba < 19)
			PlaySound((G³os + "g.wav").c_str(), nullptr, SND_SYNC);
		else
			PlaySound((G³os + "d.wav").c_str(), nullptr, SND_SYNC);
	else if (typ_zak³adu[0] == 'k')
		PlaySound((G³os + "k" + (char)(((wylosowana_liczba - 1) % 3) + 49) + ".wav").c_str(), nullptr, SND_SYNC);
	else if (typ_zak³adu[0] == 'w')
	{
		stringstream numers;
		numers << ((wylosowana_liczba - 1) / 3 + 1);
		PlaySound((G³os + "w" + numers.str() + ".wav").c_str(), nullptr, SND_SYNC);
	}
}

void Wczytaj_z_pliku(ofstream & log_ogólny, fstream & log, char & co_kontynuowaæ, int & iloœæ_pieniêdzy, int & kwota_zak³adu, int & wylosowana_liczba, string & typ_zak³adu)
{
	if (!czy_kontynuowaæ_grê) //Kompilacja je¿eli czy_kontynuowaæ_grê == 0
		if (!_access("log_aktualny.txt", 0)) // Sprawdzenie dostêpu do pliku (je¿eli takowy istnieje, musi istnieæ plik)
		{
			co_kontynuowaæ = 'n'; //Przypisanie znaku rozpoczêcia rundy od pocz¹tku
			remove("log_aktualny.txt"); //Usuniêcie pliku log aktualny poniewa¿ rozpoczyna siê now¹ grê
			log_ogólny << endl << "Uruchomiono ponownie grê z wy³¹czon¹ opcj¹ kontynuowania" << endl; //Wpisanie do buforu logu ogólnego informacje o rozpoczêciu nowej gry spowodowane ustawieniem gry
			log_ogólny.flush(); //Zapisanie do pliku log_ogólny.txt danych wpisanych do bufora danych
		}

	if (!_access("log_aktualny.txt", 0)) // Sprawdzenie dostêpu do pliku (je¿eli takowy istnieje, musi istnieæ plik)
	{
		log.open("log_aktualny.txt", ios::in); //Otworzenie pliku w trybie odczytu z pliku
		string buf, bufor2; //Uworzenie 2 buforów na tekst, pierwszy na ostatni¹ linie tekst, drugi na przedostani¹ nie pust¹ linie tekstu lub ostani¹ w przypadku gdy ostania jest pusta
		getline(log, buf); //Odczyt ca³ej lini z pliku
		while (!log.eof()) //Pêtla dzia³j¹ca do czasu kiedy kursor odczytu z pliku nie bêdzie na koñcu pliku
		{
			if (buf != "") bufor2 = buf; //Sprawdzenie czy odczytana linia nie jest pusta, je¿eli nie jest pusta to skopiowanie do drugiego bufora celem posiadania dwóch ostatnich linijek tekstu bêd¹cego w pliku
			getline(log, buf); //Odczyt ca³ej lini z pliku
		}
		if (buf == "") buf = bufor2; //Sprawdzenie czy linia w buforze jest pusta, je¿eli jest pusta to zastopienie jej poprzedni¹ lini¹ tekstu z pliku
		if (buf.find("Posiadasz") != string::npos) //Sprawdzenie czy w ostatniej niepustej lini znajduj¹ siê s³owa œwiadcz¹ce o skoñczeniu rundy
		{
			co_kontynuowaæ = 'n'; //Je¿eli siê znajduj¹ to przypisanie znaku rozpoczêcia rundy od pocz¹tku
			auto pocz¹tek = (unsigned short)buf.size(); //Utworzenie i przypisanie do zmiennej wskazuj¹cej pocz¹tek tekst pozycji ostatniego znaku tekstu o kwocie pieniêdzy któr¹ posiada jeszcze gracz, typ zmiennej auto wsazuje, ¿e kompilator sam wybierze typ zmiennej
			while (buf[pocz¹tek] != ' ' && pocz¹tek > 0) --pocz¹tek; //Poszukiwanie od koñca spacji po której jest kwota pieniêdzy któr¹ posiada jeszcze gracz
			++pocz¹tek; //Kwota jest na nastêpnym znaku wiêc przesuniêcie o jeden znak do przodu
			string buf2 = buf; //Utworzenie bufora pomocniczego do ciêcia tekstu i w³o¿enie do niego wczeœniej odczytanego tekstu
			buf2.erase(0, pocz¹tek); //Usuniêcie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna³ siê liczb¹
			buf2.erase(buf2.size() - 1, 1); //Usuniêcie z bufora pomocniczego znaku dolara z prawej strony
			iloœæ_pieniêdzy = atoi(buf2.c_str()); //Zamiana liczby w tekœcie na wartoœæ w zmiennnej liczbowej
		}
		else if (buf.find("Wylosowano") != string::npos) //Sprawdzenie czy w ostatniej niepustej lini znajduj¹ siê s³owa œwiadcz¹ce o wylosowaniu liczby
		{
			co_kontynuowaæ = 'w'; //Je¿eli siê znajduj¹ to przypisanie znaku rozpoczêcia rundy od sprawdzenia wygranej
			unsigned short pocz¹tek = 0; //Utworzenie i przypisanie zera do zmiennej wskazuj¹cej pocz¹tek tekst o wylosowanej liczbie
			while (buf[pocz¹tek] != 'y' && pocz¹tek < (int)buf.size()) ++pocz¹tek; //Poszukiwanie od pocz¹tku litery y która wystêpuje w wyrazie po którym jest wylosowana liczba
			pocz¹tek += 10; //Przesuniêcie o +10 pozycji pocz¹tku tekstu o po której jest wylosowana liczba
			string buf2 = buf; //Utworzenie bufora pomocniczego do ciêcia tekstu i w³o¿enie do niego wczeœniej odczytanego tekstu
			buf2.erase(0, pocz¹tek); //Usuniêcie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna³ siê liczb¹
			wylosowana_liczba = atoi(buf2.c_str()); //Zamiana liczby w tekœcie na wartoœæ w zmiennnej liczbowej
			pocz¹tek = 0; //Przypisanie zera do zmiennej wskazuj¹cej pocz¹tek tekst o typie zak³adu
			while (buf[pocz¹tek] != 'd' && pocz¹tek < (int)buf.size()) ++pocz¹tek;
			pocz¹tek += 2;  //Przesuniêcie o +2 pozycji pocz¹tku tekstu o po której jest typ zak³adu
			buf2 = buf; //Utworzenie bufora pomocniczego do ciêcia tekstu i w³o¿enie do niego wczeœniej odczytanego tekstu
			buf2.erase(0, pocz¹tek); //Usuniêcie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna³ siê liczb¹
			buf2.erase(buf2.find(" Wylosowano"), buf2.size() - buf2.find(" Wylosowano"));
			typ_zak³adu = buf2; //Przypisanie do zmiennej przechowywuj¹cej typ zak³adu wczytanego typu zak³adu
			buf.erase(buf.find("Obstawiono zaklad"), buf.size() - buf.find("Obstawiono zaklad"));
			pocz¹tek = 0; //Przypisanie zera do zmiennej wskazuj¹cej pocz¹tek tekst o kwocie zak³adu
			if (buf[12] == 'a') { pocz¹tek = 14; } //Sprawdzenie czy na pozycji 12 teksty znajduje siê litera a œwiadcz¹ca o wyrazie po którym jest kwota zak³adu, je¿eli tak to pozycja pocz¹tkowa tekstu wynosi 14
			else //Je¿eli nie to
			{
				while (buf[pocz¹tek] != 'z' && pocz¹tek < (unsigned short)buf.size()) ++pocz¹tek; //Poszukanie litery z œwiadcz¹cej o wyrazie po którym jest kwota zak³adu
				pocz¹tek += 3; //Po znalezienu z przesuwamy pozycje +3
			}
			int koniec = pocz¹tek + 1; //Przypisanie do zmiennej pozycji pocz¹tku +1 wskazuj¹cej koniec tekst o kwocie zak³adu
			while (buf[koniec] != '$' && koniec < (unsigned short)buf.size()) ++koniec; //Poszukujemy znaku dolara przed którym jest kwota zak³adu
			buf2 = buf; //Utworzenie bufora pomocniczego do ciêcia tekstu i w³o¿enie do niego wczeœniej odczytanego tekstu
			buf2.erase(koniec, buf2.size() - koniec); //Usuniêcie z bufora pomocniczego tekstu z prawej strony, aby tekst koñczy³ siê liczb¹
			buf2.erase(0, pocz¹tek); //Usuniêcie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna³ siê liczb¹
			kwota_zak³adu = atoi(buf2.c_str()); //Zamiana liczby w tekœcie na wartoœæ w zmiennnej liczbowej
			pocz¹tek = (unsigned short)bufor2.size(); //Utworzenie i przypisanie do zmiennej wskazuj¹cej pocz¹tek tekst o kwocie pieniêdzy któr¹ posiada jeszcze gracz
			while (bufor2[pocz¹tek] != ' ' && pocz¹tek > 0) --pocz¹tek; //Poszukiwanie od koñca spacji po której jest kwota pieniêdzy któr¹ posiada jeszcze gracz
			++pocz¹tek; //Kwota jest na nastêpnym znaku wiêc przesuniêcie o jeden znak do przodu
			buf2 = bufor2; //Przypisanie do bufora pomocniczego do ciêcia tekstu i w³o¿enie do niego linie o jedn¹ wczeœniej wczeœniej odczytanego tekstu
			buf2.erase(0, pocz¹tek); //Usuniêcie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna³ siê liczb¹
			buf2.erase(buf2.size() - 1, 1); //Usuniêcie z bufora pomocniczego znaku dolara z prawej strony
			iloœæ_pieniêdzy = atoi(buf2.c_str()); //Zamiana liczby w tekœcie na wartoœæ w zmiennnej liczbowej
		}
		else if (buf.find("Obstawiono zaklad") != string::npos) //Sprawdzenie czy w ostatniej niepustej lini znajduj¹ siê s³owa œwiadcz¹ce o typie obstawionego zak³adu
		{
			co_kontynuowaæ = 't'; //Je¿eli siê znajduj¹ to przypisanie znaku rozpoczêcia rundy od wylosowania liczby
			unsigned short pocz¹tek = 0; //Utworzenie i przypisanie zera do zmiennej wskazuj¹cej pocz¹tek tekst o typie zak³adu
			while (buf[pocz¹tek] != 'd' && pocz¹tek < (unsigned short)buf.size()) ++pocz¹tek;
			pocz¹tek += 2; //Przesuniêcie pozycji pocz¹tku tekstu o 2 po której jest typ zak³adu
			string buf2 = buf; //Utworzenie bufora pomocniczego do ciêcia tekstu i w³o¿enie do niego wczeœniej odczytanego tekstu
			buf2.erase(0, pocz¹tek); //Usuniêcie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna³ siê liczb¹
			typ_zak³adu = buf2; //Przypisanie do zmiennej przechowywuj¹cej typ zak³adu wczytanego typu zak³adu
			buf.erase(buf.find("Obstawiono zaklad"), buf.size() - buf.find("Obstawiono zaklad"));
			pocz¹tek = 0; //Przypisanie zera do zmiennej wskazuj¹cej pocz¹tek tekst o kwocie zak³adu
			if (buf[12] == 'a') pocz¹tek = 14; //Sprawdzenie czy na pozycji 12 teksty znajduje siê litera a œwiadcz¹ca o wyrazie po którym jest kwota zak³adu, je¿eli tak to pozycja pocz¹tkowa tekstu wynosi 14
			else //Je¿eli nie to
			{
				while (buf[pocz¹tek] != 'z' && pocz¹tek < (int)buf.size()) ++pocz¹tek; //Poszukanie litery z œwiadcz¹cej o wyrazie po którym jest kwota zak³adu
				pocz¹tek += 3; //Po znalezienu z przesuwamy pozycje +3
			}
			unsigned short koniec = pocz¹tek + 1; //Przypisanie do zmiennej pozycji pocz¹tku +1 wskazuj¹cej koniec tekst o kwocie zak³adu
			while (buf[koniec] != '$' && koniec < (unsigned short)buf.size()) ++koniec; //Pêtla poszukuj¹ca znaku dolara, pêtla koñczy siê znalezieniem znaku dolara
			buf2 = buf; //W³o¿enie do bufora pomocniczego do ciêcia tekstu wczeœniej odczytanego tekstu
			buf2.erase(koniec, buf2.size() - koniec); //Usuniêcie z bufora pomocniczego tekstu z prawej strony, aby tekst koñczy³ siê liczb¹
			buf2.erase(0, pocz¹tek); //Usuniêcie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna³ siê liczb¹
			kwota_zak³adu = atoi(buf2.c_str()); //Zamiana liczby w tekœcie na wartoœæ w zmiennnej liczbowej
			pocz¹tek = (unsigned short)bufor2.size(); //Utworzenie i przypisanie do zmiennej wskazuj¹cej pocz¹tek tekst o kwocie pieniêdzy któr¹ posiada jeszcze gracz
			while (bufor2[pocz¹tek] != ' ' && pocz¹tek > 0) --pocz¹tek; //Poszukiwanie od koñca spacji po której jest kwota pieniêdzy któr¹ posiada jeszcze gracz
			++pocz¹tek; //Kwota jest na nastêpnym znaku wiêc przesuniêcie o jeden znak do przodu
			buf2 = bufor2; //Przypisanie do bufora pomocniczego do ciêcia tekstu i w³o¿enie do niego linie o jedn¹ wczeœniej wczeœniej odczytanego tekstu
			buf2.erase(0, pocz¹tek); //Usuniêcie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna³ siê liczb¹
			buf2.erase(buf2.size() - 1, 1); //Usuniêcie z bufora pomocniczego znaku dolara z prawej strony
			iloœæ_pieniêdzy = atoi(buf2.c_str()); //Zamiana liczby w tekœcie na wartoœæ w zmiennnej liczbowej
		}
		else if (buf.find("Obstawiono za") != string::npos) //Sprawdzenie czy w ostatniej niepustej lini znajduj¹ siê s³owa œwiadcz¹ce o kwocie obstawionego zak³adu
		{
			co_kontynuowaæ = 'k';  //Je¿eli siê znajduj¹ to przypisanie znaku rozpoczêcia rundy od zapytania o typ zak³adu
			unsigned short pocz¹tek = 0; //Utworzenie i przypisanie do zmiennej wskazuj¹cej pocz¹tek tekst o kwocie pieniêdzy któr¹ posiada jeszcze gracz
			if (buf[12] == 'a') { pocz¹tek = 14; } //Sprawdzenie czy na pozycji 12 teksty znajduje siê litera a œwiadcz¹ca o wyrazie po którym jest kwota zak³adu, je¿eli tak to pozycja pocz¹tkowa tekstu wynosi 14
			else //Je¿eli nie to
			{
				while (buf[pocz¹tek] != 'z' && pocz¹tek < (unsigned short)buf.size()) ++pocz¹tek; //Poszukanie litery z œwiadcz¹cej o wyrazie po którym jest kwota zak³adu
				pocz¹tek += 3; //Po znalezienu z przesuwamy pozycje +3
			}
			unsigned short koniec = pocz¹tek + 1; //Utworzenie i przypisanie do zmiennej pozycji pocz¹tku +1 wskazuj¹cej koniec tekst o kwocie zak³adu
			while (buf[koniec] != '$' && koniec < (int)buf.size()) ++koniec;
			string buf2 = buf; //Utworzenie bufora pomocniczego do ciêcia tekstu i w³o¿enie do niego wczeœniej odczytanego tekstu
			buf2.erase(koniec, buf2.size() - koniec); //Usuniêcie z bufora pomocniczego tekstu z prawej strony, aby tekst koñczy³ siê liczb¹
			buf2.erase(0, pocz¹tek); //Usuniêcie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna³ siê liczb¹
			kwota_zak³adu = atoi(buf2.c_str()); //Zamiana liczby w tekœcie na wartoœæ w zmiennnej liczbowej
			pocz¹tek = (unsigned short)bufor2.size(); //Utworzenie i przypisanie do zmiennej wskazuj¹cej pocz¹tek tekst o kwocie pieniêdzy któr¹ posiada jeszcze gracz
			while (bufor2[pocz¹tek] != ' ' && pocz¹tek > 0) --pocz¹tek; //Poszukiwanie od koñca spacji po której jest kwota pieniêdzy któr¹ posiada jeszcze gracz
			++pocz¹tek; //Kwota jest na nastêpnym znaku wiêc przesuniêcie o jeden znak do przodu
			buf2 = bufor2; //Przypisanie do bufora pomocniczego do ciêcia tekstu i w³o¿enie do niego linie o jedn¹ wczeœniej wczeœniej odczytanego tekstu
			buf2.erase(0, pocz¹tek); //Usuniêcie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna³ siê liczb¹
			buf2.erase(buf2.size() - 1, 1); //Usuniêcie z bufora pomocniczego znaku dolara z prawej strony
			iloœæ_pieniêdzy = atoi(buf2.c_str()); //Zamiana liczby w tekœcie na wartoœæ w zmiennnej liczbowej
		}
		else if (buf.find("Gra rozpoczeta dnia") != string::npos) //Sprawdzenie czy w ostatniej niepustej lini znajduj¹ siê s³owa œwiadcz¹ce o rozpoczêciu nowej gry
		{
			co_kontynuowaæ = 'n'; //Je¿eli siê znajduj¹ to przypisanie znaku rozpoczêcia rundy od pocz¹tku
		}
		else //Je¿eli coœ pójdzie nie tak, to warunek aby gra siê niewysypa³a
		{
			co_kontynuowaæ = 'n'; //Je¿eli siê znajduj¹ to przypisanie znaku rozpoczêcia rundy od pocz¹tku
		}
		log.close(); //Zamkniêcie pliku logu ogólnego
		log.open("log_aktualny.txt", ios::out | ios::app); //Ponowne wczytanie pliku, teraz tylko do odczytu i ustawienie kursora zapisu na koniec pliku
	}
	else
	{
		co_kontynuowaæ = 'n'; //Przypisanie znaku rozpoczêcia rundy od pocz¹tku
		log.open("log_aktualny.txt", ios::out);
		GetSystemTime(&Czas); //Pobieranie aktualnej daty i czasu z zegara systemowego
		log << "Gra rozpoczeta dnia " << Czas.wDay << "." << Czas.wMonth << "." << Czas.wYear << " o godzinie "; //Wpisanie do bufora zapisu danych o dniu,miesi¹cu i roku do pliku log_aktualny.txt
		if (Czas.wHour < 10) log << "0"; //Wpisanie do bufora zapisu znaku zera dla równego formatowania godzinny je¿eli godzina jest minejsza ni¿ 10 do pliku log_aktualny.txt
		log << Czas.wHour << ":"; //Wpisanie do bufora zapisu znaku : dla rozdzielenia godzin od minut do pliku log_aktualny.txt
		if (Czas.wMinute < 10) log << "0"; //Wpisanie do bufora zapisu znaku zera dla równego formatowania minut je¿eli minuty jest minejsze ni¿ 10 do pliku log_aktualny.txt
		log << Czas.wMinute << ":"; //Wpisanie do bufora zapisu znaku : dla rozdzielenia minut od sekund do pliku log_aktualny.txt
		if (Czas.wSecond < 10) log << "0"; //Wpisanie do bufora zapisu znaku zera dla równego formatowania sekund je¿eli sekundy jest minejsza ni¿ 10 do pliku log_aktualny.txt
		log << Czas.wSecond << endl; // Wpisanie do bufora zapisu danych o sekundzie do pliku log_aktualny.txt
		log_ogólny << "Nowa gra rozpoczeta dnia " << Czas.wDay << "." << Czas.wMonth << "." << Czas.wYear << " o godzinie "; //Wpisanie do bufora zapisu danych o dniu,miesi¹cu i roku do pliku log_ogólny.txt
		if (Czas.wHour < 10) log_ogólny << "0"; //Wpisanie do bufora zapisu znaku zera dla równego formatowania godzinny je¿eli godzina jest minejsza ni¿ 10 do pliku log_ogólny.txt
		log_ogólny << Czas.wHour << ":";//Wpisanie do bufora zapisu znaku : dla rozdzielenia godzin od minut do pliku log_aktualny.txt
		if (Czas.wMinute < 10) log_ogólny << "0"; //Wpisanie do bufora zapisu znaku zera dla równego formatowania minut je¿eli minuty jest minejsza ni¿ 10 do pliku log_ogólny.txt
		log_ogólny << Czas.wMinute << ":"; //Wpisanie do bufora zapisu znaku : dla rozdzielenia minut od sekund do pliku log_ogólny.txt
		if (Czas.wSecond < 10) log_ogólny << "0"; //Wpisanie do bufora zapisu znaku zera dla równego formatowania sekund je¿eli sekundy jest minejsza ni¿ 10 do pliku log_ogólny.txt
		log_ogólny << Czas.wSecond << endl; // Wpisanie do bufora zapisu danych o sekundzie do pliku log_ogólny.txt
		log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
		log_ogólny.flush(); //Zapisanie do pliku log_ogólny.txt danych wpisanych do bufora danych
	}
}

void SprawdŸ_Pliki()
{
	if (stan_dŸwiêków == 1)
		if (efekty_dŸwiêkowe == 1)
		{
			if ((_access("Efekty_dŸwiêkowe", 0)))
			{
				CreateDirectoryA("Efekty_dŸwiêkowe", nullptr);
			}

			bool czy_pobierano = false;
			bool czy_pobrano = true;

			if ((_access("Efekty_dŸwiêkowe/bankrut.wav", 0)))
			{
				if (!czy_pobierano) cout << "Rozpoczynam pobieranie brakuj¹cych plików efektów" << endl;
				czy_pobierano = true;
				auto res = URLDownloadToFileA(nullptr, "https://github.com/talez2709/Ruletka/raw/master/Ruletka/Efekty_d%C5%BAwi%C4%99kowe/bankrut.wav", "Efekty_dŸwiêkowe/bankrut.wav", 0, nullptr);
				if (res != S_OK)
				{
					czy_pobrano = false;
					cout << "Brak plików dla efektów dŸwiêkowych oraz nie mo¿na pobraæ danych, wy³¹czono efekty dŸwiêkowe muzyczne, w³¹czono efekty systemowe" << endl;
					EfektyKompletne = false; //Wpisanie do zmiennej wartoœci false informuj¹cej o niekompletnych plikach audio
					return; //Wyjœcie z funkcji poniewa¿ nie ma sensu sprawdzania dalej
				}
			}

			if ((_access("Efekty_dŸwiêkowe/wygrana1.wav", 0)))
			{
				if (!czy_pobierano) cout << "Rozpoczynam pobieranie brakuj¹cych plików efektów" << endl;
				czy_pobierano = true;
				auto res = URLDownloadToFileA(nullptr, "https://github.com/talez2709/Ruletka/raw/master/Ruletka/Efekty_d%C5%BAwi%C4%99kowe/bankrut.wav", "Efekty_dŸwiêkowe/wygrana1.wav", 0, nullptr);
				if (res != S_OK)
				{
					czy_pobrano = false;
					cout << "Brak plików dla efektów dŸwiêkowych oraz nie mo¿na pobraæ danych, wy³¹czono efekty dŸwiêkowe muzyczne, w³¹czono efekty systemowe" << endl;
					EfektyKompletne = false; //Wpisanie do zmiennej wartoœci false informuj¹cej o niekompletnych plikach audio
					return; //Wyjœcie z funkcji poniewa¿ nie ma sensu sprawdzania dalej
				}
			}

			if ((_access("Efekty_dŸwiêkowe/wygrana2.wav", 0)))
			{
				if (!czy_pobierano) cout << "Rozpoczynam pobieranie brakuj¹cych plików efektów" << endl;
				czy_pobierano = true;
				auto res = URLDownloadToFileA(nullptr, "https://github.com/talez2709/Ruletka/raw/master/Ruletka/Efekty_d%C5%BAwi%C4%99kowe/wygrana2.wav", "Efekty_dŸwiêkowe/wygrana2.wav", 0, nullptr);
				if (res != S_OK)
				{
					czy_pobrano = false;
					cout << "Brak plików dla efektów dŸwiêkowych oraz nie mo¿na pobraæ danych, wy³¹czono efekty dŸwiêkowe muzyczne, w³¹czono efekty systemowe" << endl;
					EfektyKompletne = false; //Wpisanie do zmiennej wartoœci false informuj¹cej o niekompletnych plikach audio
					return; //Wyjœcie z funkcji poniewa¿ nie ma sensu sprawdzania dalej
				}
			}

			if ((_access("Efekty_dŸwiêkowe/zwielokrotnenie.wav", 0)))
			{
				if (!czy_pobierano) cout << "Rozpoczynam pobieranie brakuj¹cych plików efektów" << endl;
				czy_pobierano = true;
				auto res = URLDownloadToFileA(nullptr, "https://github.com/talez2709/Ruletka/raw/master/Ruletka/Efekty_d%C5%BAwi%C4%99kowe/zwielokrotnenie.wav", "Efekty_dŸwiêkowe/zwielokrotnenie.wav", 0, nullptr);
				if (res != S_OK)
				{
					czy_pobrano = false;
					cout << "Brak plików dla efektów dŸwiêkowych oraz nie mo¿na pobraæ danych, wy³¹czono efekty dŸwiêkowe muzyczne, w³¹czono efekty systemowe" << endl;
					EfektyKompletne = false; //Wpisanie do zmiennej wartoœci false informuj¹cej o niekompletnych plikach audio
					return; //Wyjœcie z funkcji poniewa¿ nie ma sensu sprawdzania dalej
				}
			}

			if (czy_pobierano) if (czy_pobierano) cout << "Pobrano brakuj¹ce pliki efektów" << endl;
		}

	if (stan_dŸwiêków == 1)
		if (g³os_odczytu_numeru > 0)
		{
			string buf; //Utworzenie bufora tekstowego do celu sprawdzania plików z g³osem

			G³os = "G³os/"; //Wpisanie do zmiennej G³os pocz¹tku œcie¿ki do pliku z g³osem

			switch (g³os_odczytu_numeru) //U¿ycie warunku wielokrotnego wyboru do wpisania odpowiedniej nazwy g³osu do zmiennej g³os_nazwa
			{
			case 1: //Gdy g³os_odczytu_numeru==1
			{
				G³os += "Jacek"; //Dodanie do zmiennej nazwy wybranego g³osu Jacek
				break; //Wyjœcie z instrukcji case //Wyjœcie z instrukcji case
			}
			case 2: //Gdy g³os_odczytu_numeru==2
			{
				G³os += "Ewa"; //Dodanie do zmiennej nazwy wybranego g³osu Ewa
				break; //Wyjœcie z instrukcji case
			}
			case 3: //Gdy g³os_odczytu_numeru==3
			{
				G³os += "Maja"; //Dodanie do zmiennej nazwy wybranego g³osu Maja
				break; //Wyjœcie z instrukcji case
			}
			case 4: //Gdy g³os_odczytu_numeru==4
			{
				G³os += "Jan"; //Dodanie do zmiennej nazwy wybranego g³osu Jan
				break; //Wyjœcie z instrukcji case
			}
			case 5: //Gdy g³os_odczytu_numeru==5
			{
				G³os += "Jacek2"; //Dodanie do zmiennej nazwy wybranego g³osu Jacek 2
				break; //Wyjœcie z instrukcji case
			}

			case 6: //Gdy g³os_odczytu_numeru==6
			{
				G³os += "Ewa2"; //Dodanie do zmiennej nazwy wybranego g³osu Ewa 2
				break; //Wyjœcie z instrukcji case
			}
			case 7: //Gdy g³os_odczytu_numeru==7
			{
				G³os += "Maja2"; //Dodanie do zmiennej nazwy wybranego g³osu Maja 2
				break; //Wyjœcie z instrukcji case
			}
			case 8: //Gdy g³os_odczytu_numeru==8
			{
				G³os += "Jan2"; //Dodanie do zmiennej nazwy wybranego g³osu Jan 2
				break; //Wyjœcie z instrukcji case
			}
			case 9: //Gdy g³os_odczytu_numeru==9
			{
				G³os += "Agata"; //Dodanie do zmiennej nazwy wybranego g³osu Agata
				break; //Wyjœcie z instrukcji case
			}
			default: //Je¿eli ¿aden warunek nie jest spe³niony to
				break; //Wyjœcie z instrukcji case
			}

			G³os += "_"; //Dodanie do zmiennej podkreœlenia odzielaj¹cego nazwê od szybkoœci
			G³os += '0' + g³os_szybkoœæ_odczytu_numeru; //Dodanie do zmiennej szybkoœci mowy
			G³os += "/"; //Dodanie do zmiennej ukoœnika który odziela nazwê folderu od pliku

			string link = "https://github.com/talez2709/Ruletka/raw/master/Ruletka/G%C5%82os/";

			string g³os2 = G³os;
			g³os2.erase(0, 5);

			if ((_access("G³os", 0)))
			{
				CreateDirectoryA("G³os", nullptr);
			}
			if ((_access(("G³os/" + g³os2).c_str(), 0)))
			{
				CreateDirectoryA(("G³os/" + g³os2).c_str(), nullptr);
			}

			bool czy_pobierano = false;
			bool czy_pobrano = true;

			if ((_access((G³os + "p.wav").c_str(), 0)))
			{
				if (!czy_pobierano) cout << "Rozpoczynam pobieranie brakuj¹cych plików g³osów" << endl;
				czy_pobierano = true;
				auto res = URLDownloadToFileA(nullptr, (link + g³os2 + "p.wav").c_str(), ("G³os/" + g³os2 + "p.wav").c_str(), 0, nullptr);
				if (res != S_OK)
				{
					czy_pobrano = false;
					cout << "Brak plików dla g³osu oraz nie mo¿na pobraæ danych, wy³¹czono odczytywanie wyniku" << endl;
					G³osyKompletne = false; //Wpisanie do zmiennej wartoœci false informuj¹cej o niekompletnych plikach audio
					return; //Wyjœcie z funkcji poniewa¿ nie ma sensu sprawdzania dalej
				}
			}

			if ((_access((G³os + "n.wav").c_str(), 0)))
			{
				if (!czy_pobierano) cout << "Rozpoczynam pobieranie brakuj¹cych plików g³osów" << endl;
				czy_pobierano = true;
				auto res = URLDownloadToFileA(nullptr, (link + g³os2 + "n.wav").c_str(), ("G³os/" + g³os2 + "n.wav").c_str(), 0, nullptr);
				if (res != S_OK)
				{
					czy_pobrano = false;
					cout << "Brak plików dla g³osu oraz nie mo¿na pobraæ danych, wy³¹czono odczytywanie wyniku" << endl;
					G³osyKompletne = false; //Wpisanie do zmiennej wartoœci false informuj¹cej o niekompletnych plikach audio
					return; //Wyjœcie z funkcji poniewa¿ nie ma sensu sprawdzania dalej
				}
			}

			if ((_access((G³os + "r.wav").c_str(), 0)))
			{
				if (!czy_pobierano) cout << "Rozpoczynam pobieranie brakuj¹cych plików g³osów" << endl;
				czy_pobierano = true;
				auto res = URLDownloadToFileA(nullptr, (link + g³os2 + "r.wav").c_str(), ("G³os/" + g³os2 + "r.wav").c_str(), 0, nullptr);
				if (res != S_OK)
				{
					czy_pobrano = false;
					cout << "Brak plików dla g³osu oraz nie mo¿na pobraæ danych, wy³¹czono odczytywanie wyniku" << endl;
					G³osyKompletne = false; //Wpisanie do zmiennej wartoœci false informuj¹cej o niekompletnych plikach audio
					return; //Wyjœcie z funkcji poniewa¿ nie ma sensu sprawdzania dalej
				}
			}

			if ((_access((G³os + "b.wav").c_str(), 0)))
			{
				if (!czy_pobierano) cout << "Rozpoczynam pobieranie brakuj¹cych plików g³osów" << endl;
				czy_pobierano = true;
				auto res = URLDownloadToFileA(nullptr, (link + g³os2 + "b.wav").c_str(), ("G³os/" + g³os2 + "b.wav").c_str(), 0, nullptr);
				if (res != S_OK)
				{
					czy_pobrano = false;
					cout << "Brak plików dla g³osu oraz nie mo¿na pobraæ danych, wy³¹czono odczytywanie wyniku" << endl;
					G³osyKompletne = false; //Wpisanie do zmiennej wartoœci false informuj¹cej o niekompletnych plikach audio
					return; //Wyjœcie z funkcji poniewa¿ nie ma sensu sprawdzania dalej
				}
			}

			if ((_access((G³os + "g.wav").c_str(), 0)))
			{
				if (!czy_pobierano) cout << "Rozpoczynam pobieranie brakuj¹cych plików g³osów" << endl;
				czy_pobierano = true;
				auto res = URLDownloadToFileA(nullptr, (link + g³os2 + "g.wav").c_str(), ("G³os/" + g³os2 + "g.wav").c_str(), 0, nullptr);
				if (res != S_OK)
				{
					czy_pobrano = false;
					cout << "Brak plików dla g³osu oraz nie mo¿na pobraæ danych, wy³¹czono odczytywanie wyniku" << endl;
					G³osyKompletne = false; //Wpisanie do zmiennej wartoœci false informuj¹cej o niekompletnych plikach audio
					return; //Wyjœcie z funkcji poniewa¿ nie ma sensu sprawdzania dalej
				}
			}

			if ((_access((G³os + "d.wav").c_str(), 0)))
			{
				if (!czy_pobierano) cout << "Rozpoczynam pobieranie brakuj¹cych plików g³osów" << endl;
				czy_pobierano = true;
				auto res = URLDownloadToFileA(nullptr, (link + g³os2 + "d.wav").c_str(), ("G³os/" + g³os2 + "d.wav").c_str(), 0, nullptr);
				if (res != S_OK)
				{
					czy_pobrano = false;
					cout << "Brak plików dla g³osu oraz nie mo¿na pobraæ danych, wy³¹czono odczytywanie wyniku" << endl;
					G³osyKompletne = false; //Wpisanie do zmiennej wartoœci false informuj¹cej o niekompletnych plikach audio
					return; //Wyjœcie z funkcji poniewa¿ nie ma sensu sprawdzania dalej
				}
			}

			for (unsigned short i = 1; i <= 3; ++i)
			{
				stringstream numers;
				numers << i;
				if ((_access((G³os + "k" + numers.str() + ".wav").c_str(), 0)))
				{
					if (!czy_pobierano) cout << "Rozpoczynam pobieranie brakuj¹cych plików g³osów" << endl;
					czy_pobierano = true;
					auto res = URLDownloadToFileA(nullptr, (link + g³os2 + "k" + numers.str() + ".wav").c_str(), ("G³os/" + g³os2 + "k" + numers.str() + ".wav").c_str(), 0, nullptr);
					if (res != S_OK)
					{
						czy_pobrano = false;
						cout << "Brak plików dla g³osu oraz nie mo¿na pobraæ danych, wy³¹czono odczytywanie wyniku" << endl;
						G³osyKompletne = false; //Wpisanie do zmiennej wartoœci false informuj¹cej o niekompletnych plikach audio
						return; //Wyjœcie z funkcji poniewa¿ nie ma sensu sprawdzania dalej
					}
				}
			}

			for (unsigned short i = 1; i <= 12; ++i)
			{
				stringstream numers;
				numers << i;
				if ((_access((G³os + "w" + numers.str() + ".wav").c_str(), 0)))
				{
					if (!czy_pobierano) cout << "Rozpoczynam pobieranie brakuj¹cych plików g³osów" << endl;
					czy_pobierano = true;
					auto res = URLDownloadToFileA(nullptr, (link + g³os2 + "w" + numers.str() + ".wav").c_str(), ("G³os/" + g³os2 + "w" + numers.str() + ".wav").c_str(), 0, nullptr);
					if (res != S_OK)
					{
						czy_pobrano = false;
						cout << "Brak plików dla g³osu oraz nie mo¿na pobraæ danych, wy³¹czono odczytywanie wyniku" << endl;
						G³osyKompletne = false; //Wpisanie do zmiennej wartoœci false informuj¹cej o niekompletnych plikach audio
						return; //Wyjœcie z funkcji poniewa¿ nie ma sensu sprawdzania dalej
					}
				}
			}

			for (unsigned short i = 0; i <= 36; ++i)
			{
				stringstream numers;
				numers << i;
				if ((_access((G³os + numers.str() + ".wav").c_str(), 0)))
				{
					if (!czy_pobierano) cout << "Rozpoczynam pobieranie brakuj¹cych plików g³osów" << endl;
					czy_pobierano = true;
					auto res = URLDownloadToFileA(nullptr, (link + g³os2 + numers.str() + ".wav").c_str(), ("G³os/" + g³os2 + numers.str() + ".wav").c_str(), 0, nullptr);
					if (res != S_OK)
					{
						czy_pobrano = false;
						cout << "Brak plików dla g³osu oraz nie mo¿na pobraæ danych, wy³¹czono odczytywanie wyniku" << endl;
						G³osyKompletne = false; //Wpisanie do zmiennej wartoœci false informuj¹cej o niekompletnych plikach audio
						return; //Wyjœcie z funkcji poniewa¿ nie ma sensu sprawdzania dalej
					}
				}
			}

			if (czy_pobierano) if (czy_pobierano) cout << "Pobrano brakuj¹ce pliki g³osów" << endl;
		}
}

void SprawdŸ_ustawienia()
{
	if (!_access("setting.txt", 0)) // Sprawdzenie dostêpu do pliku (je¿eli takowy istnieje, musi istnieæ plik)
	{
		ifstream ustawienia; //Utworzenie typu do celu odczytu z pliku
		ustawienia.open("setting.txt"); //Otwarcie pliku z ustawieniami
		string buf; //Utworzenie buforu do odczytu z pliku
		while (!ustawienia.eof()) //Pêtla trwaj¹ca do koñca pliku
		{
			getline(ustawienia, buf); //Wczytanie ca³ej lini tekstu z pliku
			Ustaw_ustawienia(buf); //Zamiana wczytanej lini na ustawienie programu
		}
	}
	else
	{
		ofstream ustawienia; //Utworzenie typu do celu zapisu do pliku
		ustawienia.open("setting.txt"); //Otwarcie pliku do wygenerowania ustawieñ domyœlnych
		ustawienia << "iloœæ_minimalna_obrotów_ruletki 2" << endl; //Wpisanie do pliku domyœnych ustawieñ dotycz¹cych iloœæ_minimalna_obrotów_ruletki
		ustawienia << "iloœæ_max_dodatkowych_obrotów_ruletki 3" << endl; //Wpisanie do pliku domyœnych ustawieñ dotycz¹cych iloœæ_max_dodatkowych_obrotów_ruletki
		ustawienia << "czas_przeskoku_kulki_szybki 50" << endl; //Wpisanie do pliku domyœnych ustawieñ dotycz¹cych czas_przeskoku_kulki_szybki
		ustawienia << "czas_przeskoku_kulki_wolny 75" << endl; //Wpisanie do pliku domyœnych ustawieñ dotycz¹cych czas_przeskoku_kulki_wolny
		ustawienia << "czas_przerwy_dzwiêku 500" << endl; //Wpisanie do pliku domyœnych ustawieñ dotycz¹cych czas_przerwy_dzwiêku
		ustawienia << "styl_liczenia_wygranej 1" << endl; //Wpisanie do pliku domyœnych ustawieñ dotycz¹cych styl_liczenia_wygranej
		ustawienia << "kwota_pocz¹tkowa 1000" << endl; //Wpisanie do pliku domyœnych ustawieñ dotycz¹cych kwota_pocz¹tkowa
		ustawienia << "stan_dŸwiêków 1" << endl; //Wpisanie do pliku domyœnych ustawieñ dotycz¹cych stan_dŸwiêków
		ustawienia << "czy_kontynuowaæ_grê 1" << endl; //Wpisanie do pliku domyœnych ustawieñ dotycz¹cych czy_kontynuowaæ_grê
		ustawienia << "g³os_odczytu_numeru 1" << endl; //Wpisanie do pliku domyœnych ustawieñ dotycz¹cych g³os_odczytu_numeru
		ustawienia << "g³os_szybkoœæ_odczytu_numeru 4" << endl; //Wpisanie do pliku domyœnych ustawieñ dotycz¹cych g³os_szybkoœæ_odczytu_numeru
		ustawienia << "efekty_dŸwiêkowe 1" << endl; //Wpisanie do pliku domyœnych ustawieñ dotycz¹cych efekty_dŸwiêkowe
	}

	if (czas_przeskoku_kulki_wolny < czas_przeskoku_kulki_szybki)
	{
		cout << "Wartoœæ wolnego czasu przeskoku kulki musi byæ ni¿sza ni¿ wartoœæ szybkiego czasu przeskoku kulki" << endl; //(Wartoœci tych zmiennych to czas opóŸnienia wiêc im jest wy¿szy tym d³u¿sza przerwa)
		cout << "Ustawiam domyœlne ustawienie" << endl;
		czas_przeskoku_kulki_szybki = 50;
		czas_przeskoku_kulki_wolny = 75;
	}
	if (iloœæ_minimalna_obrotów_ruletki < 0)
	{
		cout << "Iloœæ minimalna obrotów ruletki nie mo¿e byæ mniejsza od 0" << endl;
		cout << "Ustawiam domyœlne ustawienie" << endl;
		iloœæ_minimalna_obrotów_ruletki = 2;
	}
	if (iloœæ_max_dodatkowych_obrotów_ruletki < 0)
	{
		cout << "Iloœæ max obrotów ruletki nie mo¿e byæ mniejsza od 0" << endl;
		cout << "Ustawiam domyœlne ustawienie" << endl;
		iloœæ_max_dodatkowych_obrotów_ruletki = 3;
	}
	if ((iloœæ_minimalna_obrotów_ruletki == 0) && (iloœæ_max_dodatkowych_obrotów_ruletki == 0))
	{
		cout << "Jedna z deklaracji w sprawie obrotów ruletki musi byæ wiêksza od zera" << endl;
		cout << "Ustawiam domyœlne ustawienie" << endl;
		iloœæ_minimalna_obrotów_ruletki = 2;
		iloœæ_max_dodatkowych_obrotów_ruletki = 3;
	}
	if (((styl_liczenia_wygranej > 1) || (styl_liczenia_wygranej < 0)))
	{
		cout << "Styl liczeia wygranej przyjmuje wartoœci tylko 0 lub 1" << endl;
		cout << "Ustawiam domyœlne ustawienie" << endl;
		styl_liczenia_wygranej = 1;
	}
	if (czas_przerwy_dzwiêku < 0)
	{
		cout << "Czas przerwy dŸwiêku nie mo¿e byæ mniejszy od zera" << endl;
		cout << "Ustawiam domyœlne ustawienie" << endl;
		czas_przerwy_dzwiêku = 500;
	}
	if (kwota_pocz¹tkowa < 0)
	{
		cout << "Kwota pocz¹tkowa nie mo¿e byæ mniejsza od zera" << endl;
		cout << "Ustawiam domyœlne ustawienie" << endl;
		kwota_pocz¹tkowa = 1000;
	}
	if ((stan_dŸwiêków > 1) || (stan_dŸwiêków < 0))
	{
		cout << "Stan dŸwiêków przyjmuje wartoœci tylko 0 lub 1" << endl;
		cout << "Ustawiam domyœlne ustawienie" << endl;
		stan_dŸwiêków = 1;
	}
	if ((czy_kontynuowaæ_grê > 1) || (czy_kontynuowaæ_grê < 0))
	{
		cout << "Opcja kontynuowania gry przyjmuje wartoœci tylko 0 lub 1" << endl;
		cout << "Ustawiam domyœlne ustawienie" << endl;
		czy_kontynuowaæ_grê = 1;
	}
	if ((g³os_odczytu_numeru > 10) || (g³os_odczytu_numeru < 0))
	{
		cout << "Opcja g³os odczytu numeru przyjmuje wartoœci w przedziale [0;10]" << endl;
		cout << "Ustawiam domyœlne ustawienie" << endl;
		g³os_odczytu_numeru = 1;
	}
	if ((g³os_szybkoœæ_odczytu_numeru > 5) || (g³os_szybkoœæ_odczytu_numeru < 1))
	{
		cout << "Opcja szybkoœæ g³osu odczytu przyjmuje wartoœci w przedziale [1;5]" << endl;
		cout << "Ustawiam domyœlne ustawienie" << endl;
		g³os_szybkoœæ_odczytu_numeru = 4;
	}
	if ((efekty_dŸwiêkowe > 1) || (efekty_dŸwiêkowe < 0))
	{
		cout << "Opcja efekty dŸwiêkowe przyjmuje wartoœci 0 lub 1" << endl;
		cout << "Ustawiam domyœlne ustawienie" << endl;
		efekty_dŸwiêkowe = 1;
	}
	if (efekty_dŸwiêkowe == 1 && stan_dŸwiêków == 0)
	{
		cout << "Nie mo¿esz mieæ wy³¹czonych dŸwiêków i w³¹czonych efektów dŸwiêkowych" << endl;
		cout << "Ustawiam domyœlne ustawienie" << endl;
		stan_dŸwiêków = 1;
	}
	if (g³os_odczytu_numeru > 0 && stan_dŸwiêków == 0)
	{
		cout << "Nie mo¿esz mieæ wy³¹czonych dŸwiêków i w³¹czon¹ mowê" << endl;
		cout << "Ustawiam domyœlne ustawienie" << endl;
		stan_dŸwiêków = 1;
	}
}

void Og³oœ_wynik(const int & wygrana, const int & kwota_zak³adu, int & iloœæ_pieniêdzy, ofstream & log_ogólny, fstream & log)
{
	if (wygrana >= kwota_zak³adu) //Je¿eli wygrana jest wiêksza lub równa kwocie zak³adu to znaczy, ¿e siê wygra³o zak³ad
	{
		iloœæ_pieniêdzy += wygrana; //Dopisanie do salda kwoty wygranej z zak³adu
		if (styl_liczenia_wygranej) iloœæ_pieniêdzy += kwota_zak³adu; //Dopisanie do salda kwoty zak³adu
		log << " Wygrywasz " << wygrana << "$"; //Zapisanie do bufora pliku logu aktualnego informacji o kwocie wygranej zak³adu
		log << " Posiadasz " << iloœæ_pieniêdzy << "$" << endl; //Zapisanie do bufora pliku logu aktualnego informacji o saldzie konta u¿ytkownika
		log_ogólny << " Wygrywasz " << wygrana << "$"; //Zapisanie do bufora pliku logu ogólnego informacji o kwocie wygranej zak³adu
		log_ogólny << " Posiadasz " << iloœæ_pieniêdzy << "$" << endl; //Zapisanie do bufora pliku logu ogólnego informacji o saldzie konta u¿ytkownika
		log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
		log_ogólny.flush(); //Zapisanie do pliku log_ogólny.txt danych wpisanych do bufora danych
		if (stan_dŸwiêków)
		{
			if (G³osyKompletne)
			{
				PlaySound((G³os + "win.wav").c_str(), nullptr, SND_SYNC);
			}
			else
			{
				cout << "\a"; //Wywo³anie pikniêcia w g³oœniku
				Sleep(czas_przerwy_dzwiêku); //Przerwa przed kolejnym pikniêciem
				cout << "\a"; //Wywo³anie pikniêcia w g³oœniku
				Sleep(czas_przerwy_dzwiêku); //Przerwa przed kolejnym pikniêciem
				cout << "\a"; //Wywo³anie pikniêcia w g³oœniku
			}
		}
	}
	else if (wygrana == (kwota_zak³adu / 2)) //Je¿eli wygrana jest równa po³owie kwocie zak³adu to znaczy, ¿e dostaje siê zwrot po³owy kwoty zak³adu
	{
		iloœæ_pieniêdzy += wygrana; //Dopisanie do salda kwoty zwrotu z zak³adu
		log << " Dostajesz polowe zak³adu " << wygrana << "$"; //Zapisanie do bufora pliku logu aktualnego informacji o kwocie zwrotu zak³adu
		log << " Posiadasz " << iloœæ_pieniêdzy << "$" << endl; //Zapisanie do bufora pliku logu aktualnego informacji o saldzie konta u¿ytkownika
		log_ogólny << " Dostajesz polowe zak³adu " << wygrana << "$"; //Zapisanie do bufora pliku logu ogólnego informacji o kwocie zwrotu zak³adu
		log_ogólny << " Posiadasz " << iloœæ_pieniêdzy << "$" << endl; //Zapisanie do bufora pliku logu ogólnego informacji o saldzie konta u¿ytkownika
		log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
		log_ogólny.flush(); //Zapisanie do pliku log_ogólny.txt danych wpisanych do bufora danych
		if (!G³osyKompletne)
		{
			cout << "\a"; //Wywo³anie pikniêcia w g³oœniku
			Sleep(czas_przerwy_dzwiêku); //Przerwa przed kolejnym pikniêciem
			cout << "\a"; //Wywo³anie pikniêcia w g³oœniku
		}
	}
	else if (wygrana == 0) //Je¿eli wygrana jest równa 0 to znaczy, ¿e siê zak³ad przegra³o
	{
		log << " Przegrales " << kwota_zak³adu << "$"; //Zapisanie do bufora pliku logu aktualnego informacji o przegranej kwocie
		log << " Posiadasz " << iloœæ_pieniêdzy << "$" << endl; //Zapisanie do bufora pliku logu aktualnego informacji o saldzie konta u¿ytkownika
		log_ogólny << " Przegrales " << kwota_zak³adu << "$"; //Zapisanie do bufora pliku logu ogólnego informacji o przegranej kwocie
		log_ogólny << " Posiadasz " << iloœæ_pieniêdzy << "$" << endl; //Zapisanie do bufora pliku logu aktualnego informacji o saldzie konta u¿ytkownika
		log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
		log_ogólny.flush(); //Zapisanie do pliku log_ogólny.txt danych wpisanych do bufora danych
		if (!G³osyKompletne) cout << "\a"; //Wywo³anie pikniêcia w g³oœniku
	}
}

void Koniec_gry(ofstream & log_ogólny, fstream & log, int & iloœæ_pieniêdzy)
{
	cout << endl << "Koñczysz grê z wynikiem " << iloœæ_pieniêdzy << "$" << endl; //Poinformowanie u¿ytkownika o saldzie konta
	log << endl << "Koñczysz grê z wynikiem " << iloœæ_pieniêdzy << "$" << endl; //Zapisanie do bufora pliku logu aktualnego informacji o saldzie konta u¿ytkownika
	log_ogólny << "Koñczysz grê z wynikiem " << iloœæ_pieniêdzy << "$" << endl; //Zapisanie do bufora pliku logu ogólnego informacji o saldzie konta u¿ytkownika
	log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
	log_ogólny.flush(); //Zapisanie do pliku log_ogólny.txt danych wpisanych do bufora danych
	log.close();
	remove("log_aktualny.txt"); //Usuniêcie pliku log aktualny poniewa¿ skoñczy³o siê grê

	if (stan_dŸwiêków == 1) //Kompilacja je¿eli stan_dŸwiêków == 1
		if (iloœæ_pieniêdzy == 0) //Je¿eli bud¿et jest równy 0 to
			if (EfektyKompletne) PlaySound("Efekty_dŸwiêkowe/bankrut.wav", nullptr, SND_SYNC);
			else
				for (int i = 0; i < 5; ++i) //Rozpoczêcie pêtli która wykona 5 obrotów
				{
					cout << "\a"; //Wywo³anie pikniêcia w g³oœniku
					Sleep(czas_przerwy_dzwiêku); //Przerwa przed kolejnym pikniêciem //Przerwa przed kolejnym pikniêciem
				}

	if (iloœæ_pieniêdzy > kwota_pocz¹tkowa && iloœæ_pieniêdzy < kwota_pocz¹tkowa * 2)
	{
		cout << "Gratuluje zwiêkszy³eœ swój zasób finansowy" << endl; //Wyœwietlenie gratulacji z powodu zwiêkszenia bud¿etu
		if (EfektyKompletne)
			if (rand() % 1) PlaySound("Efekty_dŸwiêkowe/wygrana1.wav", nullptr, SND_SYNC);
			else PlaySound("Efekty_dŸwiêkowe/wygrana2.wav", nullptr, SND_SYNC);
	}
	else if (iloœæ_pieniêdzy >= kwota_pocz¹tkowa * 2)
	{
		cout << "Gratuluje zwiêkszy³eœ " << iloœæ_pieniêdzy / kwota_pocz¹tkowa << " krotnie swój zasób finansowy" << endl; //Wyœwietlenie gratulacji z powodu zwielokrotnienia przynajmniej 2 razy bud¿etu
		if (EfektyKompletne) PlaySound("Efekty_dŸwiêkowe/zwielokrotnenie.wav", nullptr, SND_SYNC);
	}
}

void Pêtla_g³ówna(int & wygrana, int & kwota_zak³adu, int & iloœæ_pieniêdzy, ofstream & log_ogólny, fstream & log, char & co_kontynuowaæ, string & typ_zak³adu, int & wylosowana_liczba)
{
	if (co_kontynuowaæ == 'n') Wczytaj_Kwotê_Zak³adu(kwota_zak³adu, iloœæ_pieniêdzy); //Przypisanie do zmiennej pobranej od u¿ytkownika kwoty zak³adu
	else cout << "Obstawiono za " << kwota_zak³adu << "$" << endl; //Wypisanie wczytanej kwoty zak³adu
	if (co_kontynuowaæ == 'n') log << "Obstawiono za " << kwota_zak³adu << "$"; //Zapisanie do bufora pliku logu aktualnego informacji o kwocie obstawionego zak³adu
	if (co_kontynuowaæ == 'n') log_ogólny << "Obstawiono za " << kwota_zak³adu << "$"; //Zapisanie do bufora pliku logu ogólnego informacji o kwocie obstawionego zak³adu
	log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
	log_ogólny.flush(); //Zapisanie do pliku log_ogólny.txt danych wpisanych do bufora danych
	if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k') typ_zak³adu = Obstaw(); //Przypisanie do zmiennej pobranej od u¿ytkownika typu zak³adu
	else cout << "Obstawiono zak³ad " << typ_zak³adu << endl; //Wypisanie wczytanego typu zak³adu
	if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k') log << " Obstawiono zaklad " << typ_zak³adu; //Zapisanie do bufora pliku logu aktualnego informacji o typie obstawionego zak³adu
	if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k') log_ogólny << " Obstawiono zaklad " << typ_zak³adu; //Zapisanie do bufora pliku logu ogólnego informacji o typie obstawionego zak³adu
	log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
	log_ogólny.flush(); //Zapisanie do pliku log_ogólny.txt danych wpisanych do bufora danych
	if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k' || co_kontynuowaæ == 't' || co_kontynuowaæ == 'w') iloœæ_pieniêdzy -= kwota_zak³adu; //Odjêcie od iloœci pieniêdzy kwoty zak³adu
	if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k' || co_kontynuowaæ == 't') cout << "Kulka w grze, zaczekaj na wylosowanie numeru..." << endl; //Poinformowanie u¿ytkownika o rozpoczêciu losowania
	if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k' || co_kontynuowaæ == 't') wylosowana_liczba = Zakrêæ_Ruletk¹(); //Wylosowanie i przypisanie do zmiennej liczby bêdêcej na  wylosowanej pozycji na kole ruletki
	else {
		cout << "Wylosowano numer "; //Poinformowaniu o wylosowaniu liczby
		Change_Col(Ruletka_plansza_kolor_col[wylosowana_liczba]); //Zmiana koloru tekstu w konsoli zgodnie z kolorem numeru na ruletce
		cout << wylosowana_liczba; //Wypisanie wylosowanej liczby
		Change_Col(7); //Powrót do standardowego koloru tekstu w konsoli
		cout << ". "; //Wypisanie kropki koñcz¹cej zdanie
	}
	if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k' || co_kontynuowaæ == 't') log << " Wylosowano " << wylosowana_liczba; //Zapisanie do bufora pliku logu aktualnego informacji o wylosowanej liczbie
	if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k' || co_kontynuowaæ == 't') log_ogólny << " Wylosowano " << wylosowana_liczba; //Zapisanie do bufora pliku logu ogólnego informacji o wylosowanej liczbie
	log.flush(); //Zapisanie do pliku log_aktualny.txt danych wpisanych do bufora danych
	log_ogólny.flush(); //Zapisanie do pliku log_ogólny.txt danych wpisanych do bufora danych
	if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k' || co_kontynuowaæ == 't') Odczytaj_liczbê(wylosowana_liczba, typ_zak³adu);
	if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k' || co_kontynuowaæ == 't' || co_kontynuowaæ == 'w') wygrana = SprawdŸ_Zak³ad(kwota_zak³adu, typ_zak³adu, wylosowana_liczba);
	if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k' || co_kontynuowaæ == 't' || co_kontynuowaæ == 'w') Og³oœ_wynik(wygrana, kwota_zak³adu, iloœæ_pieniêdzy, log_ogólny, log);
}
void Ustaw_ustawienia(string & tekst)
{
	if (tekst.find("iloœæ_minimalna_obrotów_ruletki") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("iloœæ_minimalna_obrotów_ruletki")); //Usuniêcie s³owa z tekst aby zosta³a tylko liczba która jest wartoœci¹ ustawienia
		if (atoi(tekst.c_str())) iloœæ_minimalna_obrotów_ruletki = atoi(tekst.c_str()); //Sprawdzenie czy po usuniêciu tekstu, to co pozosta³o jest wartoœci¹ ró¿n¹ od zera
		else
		{
			for (const char & i : tekst) //Pêtla id¹ca po ka¿dym elemencie tablicy tekst i przypisuj¹ca wartoœæ na tym polu do zmiennej i
				if (i != '0') return; //Je¿eli zmienna i jest ró¿na od znaku 0 to wychodzi z funkcji
			g³os_szybkoœæ_odczytu_numeru = 0; //Je¿eli wszystkie pozycje wyrazu tekst s¹ zerami to zaczy, ¿e jego wartoœæ liczbowa to 0
		}
	}
	else if (tekst.find("iloœæ_max_dodatkowych_obrotów_ruletki") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("iloœæ_max_dodatkowych_obrotów_ruletki")); //Usuniêcie s³owa z tekst aby zosta³a tylko liczba która jest wartoœci¹ ustawienia
		if (atoi(tekst.c_str())) iloœæ_max_dodatkowych_obrotów_ruletki = atoi(tekst.c_str()); //Sprawdzenie czy po usuniêciu tekstu, to co pozosta³o jest wartoœci¹ ró¿n¹ od zera
		else
		{
			for (const char & i : tekst) //Pêtla id¹ca po ka¿dym elemencie tablicy tekst i przypisuj¹ca wartoœæ na tym polu do zmiennej i
				if (i != '0') return; //Je¿eli zmienna i jest ró¿na od znaku 0 to wychodzi z funkcji
			iloœæ_max_dodatkowych_obrotów_ruletki = 0; //Je¿eli wszystkie pozycje wyrazu tekst s¹ zerami to zaczy, ¿e jego wartoœæ liczbowa to 0
		}
	}
	else if (tekst.find("czas_przeskoku_kulki_szybki") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("czas_przeskoku_kulki_szybki")); //Usuniêcie s³owa z tekst aby zosta³a tylko liczba która jest wartoœci¹ ustawienia
		if (atoi(tekst.c_str())) czas_przeskoku_kulki_szybki = atoi(tekst.c_str()); //Sprawdzenie czy po usuniêciu tekstu, to co pozosta³o jest wartoœci¹ ró¿n¹ od zera
		else
		{
			for (const char & i : tekst) //Pêtla id¹ca po ka¿dym elemencie tablicy tekst i przypisuj¹ca wartoœæ na tym polu do zmiennej i
				if (i != '0') return; //Je¿eli zmienna i jest ró¿na od znaku 0 to wychodzi z funkcji
			czas_przeskoku_kulki_szybki = 0; //Je¿eli wszystkie pozycje wyrazu tekst s¹ zerami to zaczy, ¿e jego wartoœæ liczbowa to 0
		}
	}
	else if (tekst.find("czas_przeskoku_kulki_wolny") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("czas_przeskoku_kulki_wolny")); //Usuniêcie s³owa z tekst aby zosta³a tylko liczba która jest wartoœci¹ ustawienia
		if (atoi(tekst.c_str())) czas_przeskoku_kulki_wolny = atoi(tekst.c_str()); //Sprawdzenie czy po usuniêciu tekstu, to co pozosta³o jest wartoœci¹ ró¿n¹ od zera
		else
		{
			for (const char & i : tekst) //Pêtla id¹ca po ka¿dym elemencie tablicy tekst i przypisuj¹ca wartoœæ na tym polu do zmiennej i
				if (i != '0') return; //Je¿eli zmienna i jest ró¿na od znaku 0 to wychodzi z funkcji
			czas_przeskoku_kulki_wolny = 0; //Je¿eli wszystkie pozycje wyrazu tekst s¹ zerami to zaczy, ¿e jego wartoœæ liczbowa to 0
		}
	}
	else if (tekst.find("styl_liczenia_wygranej") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("styl_liczenia_wygranej")); //Usuniêcie s³owa z tekst aby zosta³a tylko liczba która jest wartoœci¹ ustawienia
		if (atoi(tekst.c_str())) styl_liczenia_wygranej = atoi(tekst.c_str()); //Sprawdzenie czy po usuniêciu tekstu, to co pozosta³o jest wartoœci¹ ró¿n¹ od zera
		else
		{
			for (const char & i : tekst) //Pêtla id¹ca po ka¿dym elemencie tablicy tekst i przypisuj¹ca wartoœæ na tym polu do zmiennej i
				if (i != '0') return; //Je¿eli zmienna i jest ró¿na od znaku 0 to wychodzi z funkcji
			styl_liczenia_wygranej = 0; //Je¿eli wszystkie pozycje wyrazu tekst s¹ zerami to zaczy, ¿e jego wartoœæ liczbowa to 0
		}
	}
	else if (tekst.find("kwota_pocz¹tkowa") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("kwota_pocz¹tkowa")); //Usuniêcie s³owa z tekst aby zosta³a tylko liczba która jest wartoœci¹ ustawienia
		if (atoi(tekst.c_str())) kwota_pocz¹tkowa = atoi(tekst.c_str()); //Sprawdzenie czy po usuniêciu tekstu, to co pozosta³o jest wartoœci¹ ró¿n¹ od zera
		else
		{
			for (const char & i : tekst) //Pêtla id¹ca po ka¿dym elemencie tablicy tekst i przypisuj¹ca wartoœæ na tym polu do zmiennej i
				if (i != '0') return; //Je¿eli zmienna i jest ró¿na od znaku 0 to wychodzi z funkcji
			kwota_pocz¹tkowa = 0; //Je¿eli wszystkie pozycje wyrazu tekst s¹ zerami to zaczy, ¿e jego wartoœæ liczbowa to 0
		}
	}
	else if (tekst.find("stan_dŸwiêków") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("stan_dŸwiêków")); //Usuniêcie s³owa z tekst aby zosta³a tylko liczba która jest wartoœci¹ ustawienia
		if (atoi(tekst.c_str())) stan_dŸwiêków = atoi(tekst.c_str()); //Sprawdzenie czy po usuniêciu tekstu, to co pozosta³o jest wartoœci¹ ró¿n¹ od zera
		else
		{
			for (const char & i : tekst) //Pêtla id¹ca po ka¿dym elemencie tablicy tekst i przypisuj¹ca wartoœæ na tym polu do zmiennej i
				if (i != '0') return; //Je¿eli zmienna i jest ró¿na od znaku 0 to wychodzi z funkcji
			stan_dŸwiêków = 0; //Je¿eli wszystkie pozycje wyrazu tekst s¹ zerami to zaczy, ¿e jego wartoœæ liczbowa to 0
		}
	}
	else if (tekst.find("czy_kontynuowaæ_grê") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("czy_kontynuowaæ_grê")); //Usuniêcie s³owa z tekst aby zosta³a tylko liczba która jest wartoœci¹ ustawienia
		if (atoi(tekst.c_str())) czy_kontynuowaæ_grê = atoi(tekst.c_str()); //Sprawdzenie czy po usuniêciu tekstu, to co pozosta³o jest wartoœci¹ ró¿n¹ od zera
		else
		{
			for (const char & i : tekst) //Pêtla id¹ca po ka¿dym elemencie tablicy tekst i przypisuj¹ca wartoœæ na tym polu do zmiennej i
				if (i != '0') return; //Je¿eli zmienna i jest ró¿na od znaku 0 to wychodzi z funkcji
			czy_kontynuowaæ_grê = 0; //Je¿eli wszystkie pozycje wyrazu tekst s¹ zerami to zaczy, ¿e jego wartoœæ liczbowa to 0
		}
	}
	else if (tekst.find("g³os_odczytu_numeru") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("g³os_odczytu_numeru")); //Usuniêcie s³owa z tekst aby zosta³a tylko liczba która jest wartoœci¹ ustawienia
		if (atoi(tekst.c_str())) g³os_odczytu_numeru = atoi(tekst.c_str()); //Sprawdzenie czy po usuniêciu tekstu, to co pozosta³o jest wartoœci¹ ró¿n¹ od zera
		else
		{
			for (const char & i : tekst) //Pêtla id¹ca po ka¿dym elemencie tablicy tekst i przypisuj¹ca wartoœæ na tym polu do zmiennej i
				if (i != '0') return; //Je¿eli zmienna i jest ró¿na od znaku 0 to wychodzi z funkcji
			g³os_odczytu_numeru = 0; //Je¿eli wszystkie pozycje wyrazu tekst s¹ zerami to zaczy, ¿e jego wartoœæ liczbowa to 0
		}
	}
	else if (tekst.find("g³os_szybkoœæ_odczytu_numeru") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("g³os_szybkoœæ_odczytu_numeru")); //Usuniêcie s³owa z tekst aby zosta³a tylko liczba która jest wartoœci¹ ustawienia
		if (atoi(tekst.c_str())) g³os_szybkoœæ_odczytu_numeru = atoi(tekst.c_str()); //Sprawdzenie czy po usuniêciu tekstu, to co pozosta³o jest wartoœci¹ ró¿n¹ od zera
		else
		{
			for (const char & i : tekst) //Pêtla id¹ca po ka¿dym elemencie tablicy tekst i przypisuj¹ca wartoœæ na tym polu do zmiennej i
				if (i != '0') return; //Je¿eli zmienna i jest ró¿na od znaku 0 to wychodzi z funkcji //Je¿eli zmienna i jest ró¿na od znaku 0 to wychodzi z funkcji
			g³os_szybkoœæ_odczytu_numeru = 0; //Je¿eli wszystkie pozycje wyrazu tekst s¹ zerami to zaczy, ¿e jego wartoœæ liczbowa to 0
		}
	}
	else if (tekst.find("efekty_dŸwiêkowe") != string::npos) //Sprawdzenie czy znaleziony jest poszukiwany tekst
	{
		tekst.erase(0, size("efekty_dŸwiêkowe")); //Usuniêcie s³owa z tekst aby zosta³a tylko liczba która jest wartoœci¹ ustawienia
		if (atoi(tekst.c_str())) efekty_dŸwiêkowe = atoi(tekst.c_str()); //Sprawdzenie czy po usuniêciu tekstu, to co pozosta³o jest wartoœci¹ ró¿n¹ od zera
		else
		{
			for (const char & i : tekst) //Pêtla id¹ca po ka¿dym elemencie tablicy tekst i przypisuj¹ca wartoœæ na tym polu do zmiennej i
				if (i != '0') return; //Je¿eli zmienna i jest ró¿na od znaku 0 to wychodzi z funkcji //Je¿eli zmienna i jest ró¿na od znaku 0 to wychodzi z funkcji
			efekty_dŸwiêkowe = 0; //Je¿eli wszystkie pozycje wyrazu tekst s¹ zerami to zaczy, ¿e jego wartoœæ liczbowa to 0
		}
	}
}

/*
* Wykona³ Krzysztof Truszkiewicz
Politechnika Poznañska
Wydzia³ Elektryczny
studia niestacjonarne
Automatyka i Robotyka
Grupa 4
*/