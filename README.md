# Ruletka
Efekty dźwiękowe zostaną samodzienie pobrane po uruchomieniu programu, jeżeli nie zostaną proszę folder Efekty dzwiękowe skopiować do folderu gdzie znajduje się plik exe
Odczyt głosowy zostanie samodzienie pobrany po uruchomieniu programu, jeżeli nie zostaną proszę folder Głos skopiować do folderu gdzie znajduje się plik exe

Link do pobrania folderów https://github.com/talez2709/Ruletka/tree/master/Ruletka

Po pierwszym uruchomieniu zostanie wygenerowany plik z ustawieniami

Jeżeli log się nie tworzy proszę wyłączyć antywirusa lub dodać plik exe do wyjątków

Domyślne ustawienia programu
ilość_minimalna_obrotów_ruletki 2 // Minimalna ilość obrotów ruletki przed podaniem wartości wylosowanej
ilość_max_dodatkowych_obrotów_ruletki 3 // Maksymalna ilość dodatkowych obrotów ruletki przed podaniem wartości wylosowanej
czas_przeskoku_kulki_szybki 100 //Czas w ms przerwy pomiędzy przeskokami na początek losowania na kolejną liczbę na kole ruletki
czas_przeskoku_kulki_wolny 150 //Czas w ms przerwy pomiędzy przeskokami pod koniec losowania na kolejną liczbę na kole ruletki
czas_przerwy_dzwięku 500 //Czas w ms przerwy pomiędzy piknięciami oznaczającymi wynik zakładu
styl_liczenia_wygranej 1 //0 dla odejmowania włożonych w zakład pieniędzy (przy tym zakłady 1:1 nie zwiększają ilość_pieniędzy), 1 dla nie odejmowania (przy tym zakłady 1:1 zwiększają ilość_pieniędzy)
kwota_początkowa 1000 //Ilość $ z którymi zaczyna się grę
stan_dźwięków 1 //Czy włączone dźwięki 1 <-tak 0 <-nie
czy_kontynuować_grę 1 //Czy włączone kontynuowanie gry od skończonej poprzednio pozycji 1 <-tak 0 <-nie
głos_odczytu_numeru 1 //Wybór głosu który odczyta wylosowany numer 0 <- Brak 1 <- Jacek (Ivona) 2 <- Ewa (Ivona) 3 <- Maja (Ivona) 4 <- Jan (Ivona) 5 <- Jacek (Ivona 2) 6 <- Ewa (Ivona 2) 7 <- Maja (Ivona 2) 8 <- Jan (Ivona 2) 9 <- Agata (Scansoft)
short efekty_dźwiękowe = 1; //Czy włączone efekty dźwiękowe 1 <-tak 0 <-nie