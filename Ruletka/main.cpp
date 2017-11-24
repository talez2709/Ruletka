//------------------ deklaracje bibiotek u¿ywanych w programie -----------------------
#include <ctime> //time()
#include <fstream> //Obs³uga pliku
#include <io.h> //!_access()
#include <iostream> //Obs³uga strumenia cout,cin
#include <locale.h> //setlocale()
#include <string> //Obs³uga stringów
#include <windows.h> //SYSTEMTIME,GetSystemTime(),Sleep(),HANDLE,GetStdHandle(),SetConsoleTextAttribute()
//-------------------------------------------------------------------------------------

//--------- deklaracje plików nag³ówkowych u¿ywanych w programie ----------------------
#include "MT.h" //Generator liczb pseudolosowych Mersenne Twister
//-------------------------------------------------------------------------------------

//------ deklaracje definicji preprocesora do zmian funcjonowania programu ------------
#define iloœæ_minimalna_obrotów_ruletki 2 // Minimalna iloœæ obrotów ruletki przed podaniem wartoœci wylosowanej
#define iloœæ_max_dodatkowych_obrotów_ruletki 3 // Maksymalna iloœæ dodatkowych obrotów ruletki przed podaniem wartoœci wylosowanej
#define czas_przeskoku_kulki_szybki 100 //Czas w ms przerwy pomiêdzy przeskokami na pocz¹tek losowania na kolejn¹ liczbê na kole ruletki
#define czas_przeskoku_kulki_wolny 200 //Czas w ms przerwy pomiêdzy przeskokami pod koniec losowania na kolejn¹ liczbê na kole ruletki
#define czas_przerwy_dzwiêku 500 //Czas w ms przerwy pomiêdzy pikniêciami oznaczaj¹cymi wynik zak³adu
#define styl_liczenia_wygranej 1 //0 dla odejmowania w³o¿onych w zak³ad pieniêdzy (przy tym zak³ady 1:1 nie zwiêkszaj¹ iloœæ_pieniêdzy), 1 dla nie odejmowania (przy tym zak³ady 1:1 zwiêkszaj¹ iloœæ_pieniêdzy)
#define kwota_pocz¹tkowa 1000 //Iloœæ $ z którymi zaczyna siê gre
//-------------------------------------------------------------------------------------

//-------------------------- deklaracja wyboru przestrzeni nazw std -------------------
using namespace std;
//-------------------------------------------------------------------------------------

//---------------------------------- deklaracje funkcji w³asnych ----------------------
string Obstaw(); //Funkcja wczytywania typu zak³ad, do string aby mieæ tak¿e zak³ady sk³adaj¹ce siê z liter i cyfr
void Wczytaj_Kwotê_Zak³adu(int & kwota, int & iloœæ_pieniêdzy); //Funkcja wczytywania kwoty zak³adu aby uchroniæ siê przed problemem wpisania znaku,litery zamiast liczby i osbstawienie za wiêksz¹ kwotê ni¿ siê ma
int Zakrêæ_Ruletk¹(); //Funkcja losuje liczbê z ko³a ruletki
int SprawdŸ_Zak³ad(int & kwota, string typ_zak³adu, int wylosowana_liczba); //Funcja sprawdza czy wygraliœmy i podaje kwote wygranej/przegranej/odzysku czêœci w³o¿onych pieniêdzy
bool Czy_Kontynuowaæ(int & iloœæ_pieniêdzy); //Funkcja sprawdzj¹ca czy ma siê œrodki do gry, je¿eli ma siê to pyta czy chce siê graæ dalej
//-------------------------------------------------------------------------------------
//------------------------------- deklaracje funkcji obcych ---------------------------
void Change_Col(int num_of_col); //Funcja zmieniaj¹ca kolor tekstu 0 - czarny 1 - niebieski 2 - zielony 3 - b³êkitny 4 - czerwony 5 - purpurowy 6 - ¿ó³ty 7 - bia³y 8 - szary 9 - jasnoniebieski 10 - jasnozielony 11 - jasnob³êkitny 12 - jasnoczerwony 13 - jasnopurpurowy 14 - jasno¿ó³ty 15 - jaskrawobia³y
void HideCursor();
void ShowCursor();
//-------------------------------------------------------------------------------------

//----------------------------- deklaracje tablic pomocniczych ------------------------
const int Ruletka_ko³o[] = { 0, 32, 15, 19, 4, 21, 2, 25, 17, 34, 6, 27, 13, 36, 11, 30, 8, 23, 10, 5, 24, 16, 33, 1, 20, 14, 31, 9, 22, 18, 29, 7, 28, 12, 35, 3, 26 };// Kolejnoœæ liczb zgodna z ko³em ruletki
const char Ruletka_plansza_kolor[] = { 'g','r','b','r','b','r','b','r','b','r','b','b','r','b','r','b','r','b','r','r','b','r','b','r','b','r','b','r','b','b','r','b','r','b','r','b','r' };// Kolor dla ka¿dej liczby na planszy
int Ruletka_plansza_kolor_col[] = { 0,4,8,4,8,4,8,4,8,4,8,8,4,8,4,8,4,8,4,4,8,4,8,4,8,4,8,4,8,8,4,8,4,8,4,8,4 }; // Kod koloru do funkcji zmiany koloru tekstu dla ka¿dej liczby na planszy
//-------------------------------------------------------------------------------------

//---------------------------- deklaracje zmiennych globalnych ------------------------
SYSTEMTIME Czas; //Struktura do której zapisywana jest aktualna data i czas
//-------------------------------------------------------------------------------------

int main() {
	//Inicjowanie funkcji
	setlocale(LC_ALL, "polish"); // W celu polskich liter w konsoli
	InicjujMT((unsigned int)time(NULL)); //Zainicjowanie generatorza MT (Mersenne-Twister) dla wa¿nych liczb
	srand((unsigned int)time(NULL)); //Zainicjowanie generatorza LCG (Liniowy Generator Kongruentny) dla ma³o wa¿nych liczb
	HideCursor(); //Ukrycie kursora tekstowego w konsoli

	ofstream log_ogólny; //Utworzenie typu do celu zapisu do pliku
	log_ogólny.open("log_ogólny.txt", ios::app); //Otworzenie pliku z ustawieniem kursora zapisu do pliku
	fstream log; //Utworzenie typu do celu zapisu i/lub odczytu do i/lub z pliku
	int iloœæ_pieniêdzy = kwota_pocz¹tkowa, kwota_zak³adu, wylosowana_liczba, wygrana; //Zmienne do których wczytuje siê wartoœci liczbowe pobrane od u¿ytkownika takie jak kwota zak³adu a przechowuje iloœæ posiadanych pieniêdzy a tak¿e przechowuje wyniki funcji losowania liczby z ruletki i kwote wygran¹ z zak³adu
	string typ_zak³adu; //Przechowuje typ zak³adu wprowadzony przez u¿ytkownika
	char co_kontynuowaæ = 'n'; //Przechowuje nazwan¹ znakiem od którego punktu kontynuowaæ runde

	if (!_access("log_aktualny.txt", 0)) // Sprawdzenie dostêpu do pliku (je¿eli takowy istnieje, musi istnieæ plik)
	{
		log.open("log_aktualny.txt", ios::in); //Otworzenie pliku w trybie odczytu z pliku
		string buf, buf2; //Uworzenie 2 buforów na tekst, pierwszy na ostatni¹ linie tekst, drugi na przedostani¹ nie pust¹ linie tekstu lub ostani¹ w przypadku gdy ostania jest pusta
		while (!log.eof()) //Pêtla dzia³j¹ca do czasu kiedy kursor odczytu z pliku nie bêdzie na koñcu pliku
		{
			getline(log, buf); //Odczyt ca³ej lini z pliku
			if (buf != "") buf2 = buf; //Sprawdzenie czy odczytana linia nie jest pusta, je¿eli nie jest pusta to skopiowanie do drugiego bufora celem posiadania dwóch ostatnich linijek tekstu bêd¹cego w pliku
		}
		if (buf == "") buf = buf2; //Sprawdzenie czy linia w buforze jest pusta, je¿eli jest pusta to zastopienie jej poprzedni¹ lini¹ tekstu z pliku
		if (buf.find("Posiadasz") != string::npos || buf.find("Przegrales") != string::npos || buf.find("Wygrywasz") != string::npos) //Sprawdzenie czy w ostatniej niepustej lini znajduj¹ siê s³owa œwiadcz¹ce o skoñczeniu rundy
		{
			co_kontynuowaæ = 'n'; //Je¿eli siê znajduj¹ to przypisanie znaku rozpoczêcia rundy od pocz¹tku
			int pocz¹tek = (int)buf.size(); //Utworzenie i przypisanie do zmiennej wskazuj¹cej pocz¹tek tekst o kwocie pieniêdzy któr¹ posiada jeszcze gracz
			while (buf[pocz¹tek] != ' ' && pocz¹tek > 0) --pocz¹tek; //Poszukiwanie od koñca spacji po której jest kwota pieniêdzy któr¹ posiada jeszcze gracz
			++pocz¹tek; //Kwota jest na nastêpnym znaku wiêc przesuniêcie o jeden znak do przodu
			string buf2 = buf; //Utworzenie bufora pomocniczego do ciêcia tekstu i w³o¿enie do niego wczeœniej odczytanego tekstu
			buf2.erase(0, pocz¹tek); //Usuniêcie z bufora pomocniczego tekstu z lewej strony, aby tekst rozpoczyna³ siê liczb¹
			buf2.erase(buf2.size() - 1, 1); //Usuniêcie z bufora pomocniczego znaku dolara z prawej strony
			iloœæ_pieniêdzy = atoi(buf2.c_str()); //Zamiana liczby w tekœcie na wartoœæ w zmiennnej liczbowej
		}
		else if (buf.find("Wylosowano") != string::npos)
		{
			co_kontynuowaæ = 'w';
			int pocz¹tek = 0;
			while (buf[pocz¹tek] != 'y' && pocz¹tek < (int)buf.size()) ++pocz¹tek;
			pocz¹tek += 10;
			string buf2 = buf;
			buf2.erase(0, pocz¹tek);
			wylosowana_liczba = atoi(buf2.c_str());
			pocz¹tek = 0;
			while (buf[pocz¹tek] != 'd' && pocz¹tek < (int)buf.size()) ++pocz¹tek;
			pocz¹tek += 2;
			buf2 = buf;
			buf2.erase(0, pocz¹tek);
			typ_zak³adu = buf2;
			buf.erase(buf.find("Obstawiono zaklad"), buf.size() - buf.find("Obstawiono zaklad"));
			pocz¹tek = 0;
			if (buf[12] == 'a') { pocz¹tek = 14; }
			else
			{
				while (buf[pocz¹tek] != 'z' && pocz¹tek < (int)buf.size()) ++pocz¹tek;
				pocz¹tek += 3;
			}
			int koniec = pocz¹tek + 1;
			while (buf[koniec] != '$' && koniec < (int)buf.size()) koniec++;
			buf2 = buf;
			buf2.erase(koniec, buf2.size() - koniec);
			buf2.erase(0, pocz¹tek);
			kwota_zak³adu = atoi(buf2.c_str());
		}
		else if (buf.find("Obstawiono zaklad") != string::npos)
		{
			co_kontynuowaæ = 't';
			int pocz¹tek = 0;
			while (buf[pocz¹tek] != 'd' && pocz¹tek < (int)buf.size()) ++pocz¹tek;
			pocz¹tek += 2;
			string buf2 = buf;
			buf2.erase(0, pocz¹tek);
			typ_zak³adu = buf2;
			buf.erase(buf.find("Obstawiono zaklad"), buf.size() - buf.find("Obstawiono zaklad"));
			pocz¹tek = 0;
			if (buf[12] == 'a') { pocz¹tek = 14; }
			else
			{
				while (buf[pocz¹tek] != 'z' && pocz¹tek < (int)buf.size()) ++pocz¹tek;
				pocz¹tek += 3;
			}
			int koniec = pocz¹tek + 1;
			while (buf[koniec] != '$' && koniec < (int)buf.size()) koniec++;
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
				while (buf[pocz¹tek] != 'z' && pocz¹tek < (int)buf.size()) ++pocz¹tek;
				pocz¹tek += 3;
			}
			int koniec = pocz¹tek + 1;
			while (buf[koniec] != '$' && koniec < (int)buf.size()) koniec++;
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
		GetSystemTime(&Czas); //Pobieranie aktualnej daty i czasu z zegara systemowego
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
	do
	{
		if (co_kontynuowaæ == 'n') Wczytaj_Kwotê_Zak³adu(kwota_zak³adu, iloœæ_pieniêdzy);
		else cout << "Obstawiono za " << kwota_zak³adu << "$" << endl;
		if (co_kontynuowaæ == 'n') log << "Obstawiono za " << kwota_zak³adu << "$";
		if (co_kontynuowaæ == 'n') log_ogólny << "Obstawiono za " << kwota_zak³adu << "$";
		log.flush();
		log_ogólny.flush();
		if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k') typ_zak³adu = Obstaw();
		else cout << "Obstawiono zak³ad " << typ_zak³adu << endl;
		if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k') log << " Obstawiono zaklad " << typ_zak³adu;
		if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k') log_ogólny << " Obstawiono zaklad " << typ_zak³adu;
		log.flush();
		log_ogólny.flush();
		if (co_kontynuowaæ == 'n' || co_kontynuowaæ == 'k' || co_kontynuowaæ == 't' || co_kontynuowaæ == 'w') iloœæ_pieniêdzy -= kwota_zak³adu;
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
			if (wygrana >= kwota_zak³adu)
			{
				log_ogólny << " Wygrywasz " << wygrana << "$";
				log << " Wygrywasz " << wygrana << "$";
				iloœæ_pieniêdzy += wygrana;
#if styl_liczenia_wygranej == 1
				iloœæ_pieniêdzy += kwota_zak³adu;
#endif // styl_liczenia_wygranej
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
			else if (wygrana == (kwota_zak³adu / 2))
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
			else if (wygrana == 0)
			{
				log_ogólny << " Przegrales " << kwota_zak³adu << "$";
				log << " Przegrales " << kwota_zak³adu << "$";
				log << " Posiadasz " << iloœæ_pieniêdzy << "$" << endl;
				log_ogólny << " Posiadasz " << iloœæ_pieniêdzy << "$" << endl;
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
	if (iloœæ_pieniêdzy == 0)
		for (int i = 0; i < 5; ++i)
		{
			cout << "\a";
			Sleep(czas_przerwy_dzwiêku);
		}
	if (iloœæ_pieniêdzy > kwota_pocz¹tkowa && iloœæ_pieniêdzy < kwota_pocz¹tkowa * 2) cout << "Gratuluje zwiêkszy³eœ swój zasób finansowy" << endl;
	else if (iloœæ_pieniêdzy >= kwota_pocz¹tkowa * 2) cout << "Gratuluje zwiêkszy³eœ " << iloœæ_pieniêdzy / kwota_pocz¹tkowa << " krotnie swój zasób finansowy" << endl;
	system("pause");
	return 0;
}

string Obstaw() {
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
		zaklad_typ == "p" || //Sprawdzanie czy wprowadzono zak³ad na liczby parzyste
		zaklad_typ == "n" || //Sprawdzanie czy wprowadzono zak³ad na liczby nieparzyste
		zaklad_typ == "r" || //Sprawdzanie czy wprowadzono zak³ad na czerwone liczby
		zaklad_typ == "b" || //Sprawdzanie czy wprowadzono zak³ad na czarne liczby
		zaklad_typ == "g" || //Sprawdzanie czy wprowadzono zak³ad na liczby z górnej po³ówki
		zaklad_typ == "d" || //Sprawdzanie czy wprowadzono zak³ad na liczby z dolnej po³ówki
		zaklad_typ == "k1" || //Sprawdzanie czy wprowadzono zak³ad na liczby z kolumny 1
		zaklad_typ == "k2" || //Sprawdzanie czy wprowadzono zak³ad na liczby z kolumny 2
		zaklad_typ == "k3" || //Sprawdzanie czy wprowadzono zak³ad na liczby z kolumny 3
		zaklad_typ == "w1" || //Sprawdzanie czy wprowadzono zak³ad na liczby z wiersza 1
		zaklad_typ == "w2" || //Sprawdzanie czy wprowadzono zak³ad na liczby z wiersza 2
		zaklad_typ == "w3" || //Sprawdzanie czy wprowadzono zak³ad na liczby z wiersza 3
		zaklad_typ == "w4" || //Sprawdzanie czy wprowadzono zak³ad na liczby z wiersza 4
		zaklad_typ == "w5" || //Sprawdzanie czy wprowadzono zak³ad na liczby z wiersza 5
		zaklad_typ == "w6" || //Sprawdzanie czy wprowadzono zak³ad na liczby z wiersza 6
		zaklad_typ == "w7" || //Sprawdzanie czy wprowadzono zak³ad na liczby z wiersza 7
		zaklad_typ == "w8" || //Sprawdzanie czy wprowadzono zak³ad na liczby z wiersza 8
		zaklad_typ == "w9" || //Sprawdzanie czy wprowadzono zak³ad na liczby z wiersza 9
		zaklad_typ == "w10" || //Sprawdzanie czy wprowadzono zak³ad na liczby z wiersza 10
		zaklad_typ == "w11" || //Sprawdzanie czy wprowadzono zak³ad na liczby z wiersza 11
		zaklad_typ == "w12" || //Sprawdzanie czy wprowadzono zak³ad na liczby z wiersza 12
		zaklad_typ == "0" || //Sprawdzanie czy wprowadzono zak³ad na cyfre 0
		zaklad_typ == "1" || //Sprawdzanie czy wprowadzono zak³ad na cyfre 1
		zaklad_typ == "2" || //Sprawdzanie czy wprowadzono zak³ad na cyfre 2
		zaklad_typ == "3" || //Sprawdzanie czy wprowadzono zak³ad na cyfre 3
		zaklad_typ == "4" || //Sprawdzanie czy wprowadzono zak³ad na cyfre 4
		zaklad_typ == "5" || //Sprawdzanie czy wprowadzono zak³ad na cyfre 5
		zaklad_typ == "6" || //Sprawdzanie czy wprowadzono zak³ad na cyfre 6
		zaklad_typ == "7" || //Sprawdzanie czy wprowadzono zak³ad na cyfre 7
		zaklad_typ == "8" || //Sprawdzanie czy wprowadzono zak³ad na cyfre 8
		zaklad_typ == "9" || //Sprawdzanie czy wprowadzono zak³ad na cyfre 9
		zaklad_typ == "10" || //Sprawdzanie czy wprowadzono zak³ad na liczbê 10
		zaklad_typ == "11" || //Sprawdzanie czy wprowadzono zak³ad na liczbê 11
		zaklad_typ == "12" || //Sprawdzanie czy wprowadzono zak³ad na liczbê 12
		zaklad_typ == "13" || //Sprawdzanie czy wprowadzono zak³ad na liczbê 13
		zaklad_typ == "14" || //Sprawdzanie czy wprowadzono zak³ad na liczbê 14
		zaklad_typ == "15" || //Sprawdzanie czy wprowadzono zak³ad na liczbê 15
		zaklad_typ == "16" || //Sprawdzanie czy wprowadzono zak³ad na liczbê 16
		zaklad_typ == "17" || //Sprawdzanie czy wprowadzono zak³ad na liczbê 17
		zaklad_typ == "18" || //Sprawdzanie czy wprowadzono zak³ad na liczbê 18
		zaklad_typ == "19" || //Sprawdzanie czy wprowadzono zak³ad na liczbê 19
		zaklad_typ == "20" || //Sprawdzanie czy wprowadzono zak³ad na liczbê 20
		zaklad_typ == "21" || //Sprawdzanie czy wprowadzono zak³ad na liczbê 21
		zaklad_typ == "22" || //Sprawdzanie czy wprowadzono zak³ad na liczbê 22
		zaklad_typ == "23" || //Sprawdzanie czy wprowadzono zak³ad na liczbê 23
		zaklad_typ == "24" || //Sprawdzanie czy wprowadzono zak³ad na liczbê 24
		zaklad_typ == "25" || //Sprawdzanie czy wprowadzono zak³ad na liczbê 25
		zaklad_typ == "26" || //Sprawdzanie czy wprowadzono zak³ad na liczbê 26
		zaklad_typ == "27" || //Sprawdzanie czy wprowadzono zak³ad na liczbê 27
		zaklad_typ == "28" || //Sprawdzanie czy wprowadzono zak³ad na liczbê 28
		zaklad_typ == "29" || //Sprawdzanie czy wprowadzono zak³ad na liczbê 29
		zaklad_typ == "30" || //Sprawdzanie czy wprowadzono zak³ad na liczbê 30
		zaklad_typ == "31" || //Sprawdzanie czy wprowadzono zak³ad na liczbê 31
		zaklad_typ == "32" || //Sprawdzanie czy wprowadzono zak³ad na liczbê 32
		zaklad_typ == "33" || //Sprawdzanie czy wprowadzono zak³ad na liczbê 33
		zaklad_typ == "34" || //Sprawdzanie czy wprowadzono zak³ad na liczbê 34
		zaklad_typ == "35" || //Sprawdzanie czy wprowadzono zak³ad na liczbê 35
		zaklad_typ == "36" //Sprawdzanie czy wprowadzono zak³ad na liczbê 36
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
				for (short i = 0; i < (int)kwota_zak³adu_s.size(); i++)
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
	int iloœæ_zakrêceñ = rand() % (iloœæ_max_dodatkowych_obrotów_ruletki + 1) + iloœæ_minimalna_obrotów_ruletki;
	for (int i = 0; i < iloœæ_zakrêceñ; ++i)
		for (int ii = 0; ii < 37; ++ii)
		{
			Change_Col(Ruletka_plansza_kolor_col[Ruletka_ko³o[ii]]); //Zmiana koloru tekstu w konsoli zgodnie z kolorem numeru na ruletce
			cout << Ruletka_ko³o[ii];
			Sleep(czas_przeskoku_kulki_szybki);
			Change_Col(7); //Powrót do standardowego koloru tekstu w konsoli
			cout << "\b\b" << "  " << "\b\b"; //Cofniêcie kursora tekstowego do lewej strony konsoli aby zape³niæ podem spacjami czyli niewidocznym znakiem wiersza konsoli aby widaæ przejœcie pomiêdzy liczbami na ruletce
		}
	int wylosowana_pozycja = MersenneTwister() % 37;
	for (int ii = 0; ii < wylosowana_pozycja; ++ii)
	{
		Change_Col(Ruletka_plansza_kolor_col[Ruletka_ko³o[ii]]); //Zmiana koloru tekstu w konsoli zgodnie z kolorem numeru na ruletce
		cout << Ruletka_ko³o[ii];
		Sleep(czas_przeskoku_kulki_wolny);
		Change_Col(7); //Powrót do standardowego koloru tekstu w konsoli
		cout << "\b\b" << "  " << "\b\b"; //Cofniêcie kursora tekstowego do lewej strony konsoli aby zape³niæ podem spacjami czyli niewidocznym znakiem wiersza konsoli aby widaæ przejœcie pomiêdzy liczbami na ruletce
	}
	cout << "Wylosowano numer ";
	Change_Col(Ruletka_plansza_kolor_col[Ruletka_ko³o[wylosowana_pozycja]]);
	cout << Ruletka_ko³o[wylosowana_pozycja];
	Change_Col(7);
	cout << ". ";

	return Ruletka_ko³o[wylosowana_pozycja];
}

int SprawdŸ_Zak³ad(int & kwota, string typ_zak³adu, int wylosowana_liczba) {
	int wygrana = kwota;

	if (wylosowana_liczba == 0)
		if (typ_zak³adu == "p")
			wygrana /= 2;
		else if (typ_zak³adu == "n")
			wygrana /= 2;
		else if (typ_zak³adu == "r")
			wygrana /= 2;
		else if (typ_zak³adu == "b")
			wygrana /= 2;
		else if (typ_zak³adu == "g")
			wygrana /= 2;
		else if (typ_zak³adu == "d")
			wygrana /= 2;
		else if (typ_zak³adu[0] == 'k')
			wygrana *= 0;
		else if (typ_zak³adu[0] == 'w')
			wygrana *= 0;
		else if (typ_zak³adu[0] == '0')
			wygrana *= 35;

	if (typ_zak³adu == "p")
		if (wylosowana_liczba % 2 == 0) wygrana *= 1;
		else wygrana *= 0;
	else if (typ_zak³adu == "n")
		if (wylosowana_liczba % 2 == 1) wygrana *= 1;
		else wygrana *= 0;
	else if (typ_zak³adu == "r")
		if (Ruletka_plansza_kolor[wylosowana_liczba] == 'r') wygrana *= 1;
		else wygrana *= 0;
	else if (typ_zak³adu == "b")
		if (Ruletka_plansza_kolor[wylosowana_liczba] == 'b') wygrana *= 1;
		else wygrana *= 0;
	else if (typ_zak³adu == "g")
		if (wylosowana_liczba < 19) wygrana *= 1;
		else wygrana *= 0;
	else if (typ_zak³adu == "d")
		if (wylosowana_liczba > 18) wygrana *= 1;
		else wygrana *= 0;
	else if (typ_zak³adu[0] == 'k')
		if ((wylosowana_liczba - 1) % 3 == typ_zak³adu[1] - 49) wygrana *= 2;
		else wygrana *= 0;
	else if (typ_zak³adu[0] == 'w')
		if (((wylosowana_liczba - 1) / 3 + 1) == atoi(typ_zak³adu.erase(0, 1).c_str())) wygrana *= 11;
		else wygrana *= 0;
	else if (wylosowana_liczba == atoi(typ_zak³adu.c_str())) wygrana *= 35;
	else wygrana *= 0;

	if (wygrana >= kwota) cout << "Obstawiles poprawnie, wygrywasz " << wygrana << "$." << endl;
	else if (wygrana == kwota / 2) cout << "Obstawiles niepoprawnie lecz uda³o Ci siê, dostajesz po³owê zak³adu " << wygrana << "$." << endl;
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
	HANDLE h_wyj; //Stworzenie zmiennej typu uchwyt
	h_wyj = GetStdHandle(STD_OUTPUT_HANDLE); //Pobiera uchwyt do standardowego wyjœcia
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