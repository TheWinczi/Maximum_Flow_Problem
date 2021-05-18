#include <iostream>
#include <string>
#include <list>
#include <math.h>
using namespace std;

//
// LISTA DNI I CZASOW
//
class WezelCzasu
{
public:
    WezelCzasu* nastepny;
    int czas;

    WezelCzasu(const int& czas)
        : nastepny(NULL), czas(czas) {};
};

class WezelDnia
{
public:
    WezelDnia* nastepny;
    WezelCzasu* czasy;
    int dzien;
    int ileCzasow;

    WezelDnia(int dzien)
        : nastepny(NULL), czasy(NULL), dzien(dzien), ileCzasow(0) {};
};

class ListaDniICzasow
{
public:
    WezelDnia* glowa;
    int iloscDni;

    ListaDniICzasow()
        : glowa(NULL), iloscDni(0) {};

    bool czyDzienOryginalny(const int& _dzien)
    {
        WezelDnia* tmp = this->glowa;
        while (tmp != NULL)
        {
            if (tmp->dzien == _dzien)
                return false;

            tmp = tmp->nastepny;
        }
        return true;
    }

    bool CzyCzasOryginalny(const int& _czas, const int& _dzien)
    {
        WezelDnia* wDnia = this->znajdzDzien(_dzien);
        if (wDnia != NULL)
        {
            WezelCzasu* wCzasu = wDnia->czasy;
            while (wCzasu != NULL)
            {
                if (wCzasu->czas == _czas)
                    return false;

                wCzasu = wCzasu->nastepny;
            }
            return true;
        }
        else
            return false;
    }

    void dodajCzasDoDnia(const int& _czas, const int& _dzien)
    {
        WezelDnia* doDnia = this->znajdzDzien(_dzien);
        WezelCzasu* nowyCzas = new WezelCzasu(_czas);
        if (doDnia != NULL)
        {
            WezelCzasu* wCzasu = doDnia->czasy;
            if (wCzasu == NULL)
            {
                doDnia->czasy = nowyCzas;
            }

            else
            {
                while (wCzasu->nastepny != NULL)
                    wCzasu = wCzasu->nastepny;

                wCzasu->nastepny = nowyCzas;
            }
        }
    }
    void dodajDzien(int _dzien)
    {
        WezelDnia* nowyDzien = new WezelDnia(_dzien);
        WezelDnia* tmp = this->glowa;
        if (tmp == NULL)
        {
            this->glowa = nowyDzien;
        }
        else
        {
            while (tmp->nastepny != NULL)
                tmp = tmp->nastepny;

            tmp->nastepny = nowyDzien;
        }
        this->iloscDni++;
    }

    WezelDnia* znajdzDzien(const int& _dzien)
    {
        WezelDnia* tmp = this->glowa;
        while (tmp != NULL)
        {
            if (tmp->dzien == _dzien)
                return tmp;

            tmp = tmp->nastepny;
        }

        return NULL;
    }
};



//
//  DANE WEJSCIOWE
//
class Pracownik
{
public:
    //
    //  KONSTRUKTORY
    //
    Pracownik()
        : imie(""), wartosc(0), liczbaGodzinOgolem(0), iloscGodzinNaDzien(0) {};

    Pracownik(const string& imie, const int& wartosc, const int& liczbaGodzinOgolem, const int& iloscGodzinNaDzien)
        : imie(imie), wartosc(wartosc), liczbaGodzinOgolem(liczbaGodzinOgolem), iloscGodzinNaDzien(iloscGodzinNaDzien) {};

    void przedstawSie()
    {
        cout << "Jesetem Pracownikiem: " << this->imie << " " << this->wartosc << " " << this->liczbaGodzinOgolem << " " << this->iloscGodzinNaDzien << endl;
    }

    //
    //  GETTERY
    //
    string getImie() const
    {
        return this->imie;
    }
    int getWartosc() const
    {
        return this->wartosc;
    }
    int getLiczbaGodzinOgolem() const
    {
        return this->liczbaGodzinOgolem;
    }
    int getIloscGodzinNaDzien() const
    {
        return this->iloscGodzinNaDzien;
    }

private:
    string imie;
    int wartosc;
    int liczbaGodzinOgolem;
    int iloscGodzinNaDzien;
};

/****************************************************************************************************************************/

class Katedra
{
public:
    //
    //  KONSTRUKTORY
    //
    Katedra()
        : nazwa(""), iloscPracownikow(0)
    {
        this->pracownicy = NULL;
    };

    Katedra(const string& nazwa, const int& iloscPracownikow)
        : nazwa(nazwa), iloscPracownikow(iloscPracownikow)
    {
        this->pracownicy = new Pracownik[iloscPracownikow];
    };


    void wczytajPracownikow()
    {
        string imie;
        int wartosc, liczbaGodzinOgolem, iloscGodzinNaDzien;

        for (int i = 0; i < this->iloscPracownikow; i++)
        {
            cin >> imie >> wartosc >> liczbaGodzinOgolem >> iloscGodzinNaDzien;
            this->pracownicy[i] = Pracownik(imie, wartosc, liczbaGodzinOgolem, iloscGodzinNaDzien);
        }
    }

    void wypisz()
    {
        cout << "Moja nazwa katedry: " << this->nazwa << endl << "Ilosc pracownikow: " << this->iloscPracownikow << endl;
        for (int i = 0; i < iloscPracownikow; i++)
            pracownicy[i].przedstawSie();
    }

    //
    //  GETTERY
    //
    string getNazwa() const
    {
        return this->nazwa;
    }
    int getIloscPracownikow()
    {
        return this->iloscPracownikow;
    }
    Pracownik* getPracownicy()
    {
        return this->pracownicy;
    }

private:
    string nazwa;
    int iloscPracownikow;
    Pracownik* pracownicy;
};

/****************************************************************************************************************************/

class Zadanie
{
public:
    //
    //  KONSTRUKTORY
    //
    Zadanie()
        : dzien(0), czas(0), minimalnaIloscOsoboGodzin(0), maksymalnaIloscOsoboGodzin(0) {};

    Zadanie(const int& dzien, const int& czas, const int minimalnaIloscOsoboGodzin, const int& maksymalnaIloscOsoboGodzin)
        : dzien(dzien), czas(czas), minimalnaIloscOsoboGodzin(minimalnaIloscOsoboGodzin), maksymalnaIloscOsoboGodzin(maksymalnaIloscOsoboGodzin) {};

    void przedstawSie()
    {
        cout << "Jesetem zadaniem: " << this->dzien << " " << this->czas << " " << this->minimalnaIloscOsoboGodzin << " " << this->maksymalnaIloscOsoboGodzin << endl;
    }

    //
    //  GETTERY
    //
    int getDzien() const
    {
        return this->dzien;
    }
    int getCzas() const
    {
        return this->czas;
    }
    int getMinimalnaIloscOsoboGodzin() const
    {
        return this->minimalnaIloscOsoboGodzin;
    }
    int getMaksymalnaIloscOsoboGodzin() const
    {
        return this->maksymalnaIloscOsoboGodzin;
    }

private:
    int dzien;
    int czas;
    int minimalnaIloscOsoboGodzin;
    int maksymalnaIloscOsoboGodzin;
};

/****************************************************************************************************************************/

class GrupaZadan
{
public:
    //
    //  KONSTRUKTORY
    //
    GrupaZadan()
        : nazwa(""), iloscZadan(0), lacznaIloscOsoboGodzin(0)
    {
        this->zadania = NULL;
    };

    GrupaZadan(const string& nazwa, const int iloscZadan, const int& lacznaIloscOsoboGodzin)
        : nazwa(nazwa), iloscZadan(iloscZadan), lacznaIloscOsoboGodzin(lacznaIloscOsoboGodzin)
    {
        this->zadania = new Zadanie[iloscZadan];
    }

    void wczytajZadania()
    {
        int dzien, czas, minimalnaIloscOsoboGodzin, maksymalnaIloscOsoboGodzin;
        for (int i = 0; i < this->iloscZadan; i++)
        {
            cin >> dzien >> czas >> minimalnaIloscOsoboGodzin >> maksymalnaIloscOsoboGodzin;
            this->zadania[i] = Zadanie(dzien, czas, minimalnaIloscOsoboGodzin, maksymalnaIloscOsoboGodzin);
        }
    }

    void wypisz()
    {
        cout << "Moja nazwa grupy: " << this->nazwa << endl << "Ilosc zadan: " << this->iloscZadan << endl << "Laczna ilosc potrzebnych godzin: " << this->lacznaIloscOsoboGodzin << endl;
        for (int i = 0; i < iloscZadan; i++)
            zadania[i].przedstawSie();
    }

    //
    //  GETTERY
    //
    string getNazwa() const
    {
        return this->nazwa;
    }
    int getIloscZadan() const
    {
        return this->iloscZadan;
    }
    int getLacznaIloscOsoboGodzin() const
    {
        return this->lacznaIloscOsoboGodzin;
    }
    Zadanie* getZadania()
    {
        return zadania;
    }

private:
    string nazwa;
    int iloscZadan;
    int lacznaIloscOsoboGodzin;
    Zadanie* zadania;
};




//
//  GRAF
//
class Krawedz;

class WezelListyKrawedzi
{
public:
    Krawedz* krawedz;
    WezelListyKrawedzi* nastepny;

    WezelListyKrawedzi(Krawedz* krawedz)
        : krawedz(krawedz), nastepny(NULL) {};
};
class ListaKrawedzi
{
public:
    WezelListyKrawedzi* glowa;
    WezelListyKrawedzi* ogon;
    int iloscKrawedzi;

    ListaKrawedzi()
        : glowa(NULL), ogon(NULL), iloscKrawedzi(0) {};

    void dodajKrawedz(Krawedz* krawedz)
    {
        WezelListyKrawedzi* nowy = new WezelListyKrawedzi(krawedz);
        if (this->glowa == NULL)
            this->glowa = nowy;
        else
            this->ogon->nastepny = nowy;

        this->ogon = nowy;
        this->iloscKrawedzi++;
    }

    bool czyJestNaLiscie(Krawedz* krawedz)
    {
        WezelListyKrawedzi* tmp = this->glowa;
        while (tmp != NULL)
        {
            if (krawedz == tmp->krawedz) // porownaj adresy krawedzi
                return true;

            tmp = tmp->nastepny;
        }
        return false;
    }

    Krawedz* getPoprzednia(Krawedz* krawedz)
    {
        WezelListyKrawedzi* tmp = this->glowa;
        bool czyZnaleziono = false;

        while (tmp != this->ogon)
        {
            if (tmp->nastepny->krawedz == krawedz)
                return tmp->krawedz;

            tmp = tmp->nastepny;
        }
        return NULL;
    }

    void clear()
    {
        WezelListyKrawedzi* tmp = this->glowa;
        while (tmp != NULL)
        {
            WezelListyKrawedzi* i = tmp;
            tmp = tmp->nastepny;
            delete i;
        }
        this->glowa = this->ogon = NULL;
    }
};

class Wierzcholek;
class Krawedz
{
public:
    Wierzcholek* poprzedni;
    Wierzcholek* polaczenie;
    int przepustowosc;
    int przeplyw;

    Krawedz()
        : poprzedni(NULL), polaczenie(NULL), przepustowosc(0), przeplyw(0) {};

    Krawedz(Wierzcholek* polaczenie, const int& przepustowosc)
        : poprzedni(NULL), polaczenie(polaczenie), przepustowosc(przepustowosc), przeplyw(0) {};
};

class Wierzcholek
{
public:
    string dane;
    int dzien, czas;
    ListaKrawedzi* listaKrawedzi;

    Wierzcholek()
        : dane(""), dzien(0), czas(0), listaKrawedzi(new ListaKrawedzi()) {};

    Wierzcholek(const string& dane)
        : dane(dane), dzien(0), czas(0), listaKrawedzi(new ListaKrawedzi()) {};

    Wierzcholek(const string& dane, const int& _dzien, const int& _czas)
        : dane(dane), dzien(_dzien), czas(_czas), listaKrawedzi(new ListaKrawedzi()) {};
};

class Graf
{
public:
    Wierzcholek* zrodlo;
    Wierzcholek* ujscie;
    int ileKrawedzi;
    int ileWierzcholkow;

    Graf()
    {
        this->zrodlo = new Wierzcholek("ZRODLO");
        this->ujscie = new Wierzcholek("UJSCIE");
        this->ileKrawedzi = 0;
        this->ileWierzcholkow = 0;
    }

    void dodajKrawedzDoWierzcholka(Wierzcholek* wierzcholek, Krawedz* nowaKrawedz)
    {
        wierzcholek->listaKrawedzi->dodajKrawedz(nowaKrawedz);
        nowaKrawedz->poprzedni = wierzcholek;

        this->ileKrawedzi++;
    }

    void dodajWierzcholekDoKrawedzi(Wierzcholek* wierzcholek, Krawedz* doKrawedzi)
    {
        doKrawedzi->polaczenie = wierzcholek;

        this->ileWierzcholkow++;
    }

    Wierzcholek* getZrodlo()
    {
        return this->zrodlo;
    }
    Wierzcholek* getUjscie()
    {
        return this->ujscie;
    }

    void wyzerujPrzeplywy()
    {
        WezelListyKrawedzi* wListyZadan;

        ListaKrawedzi* listaZrodla = this->zrodlo->listaKrawedzi;
        WezelListyKrawedzi* tmp = listaZrodla->glowa;
        while (tmp != NULL)
        {
            ListaKrawedzi* listaPracownika = tmp->krawedz->polaczenie->listaKrawedzi;
            WezelListyKrawedzi* tmp2 = listaPracownika->glowa;
            while (tmp2 != NULL)
            {
                ListaKrawedzi* listaDni = tmp2->krawedz->polaczenie->listaKrawedzi;
                WezelListyKrawedzi* tmp3 = listaDni->glowa;
                while (tmp3 != NULL)
                {
                    ListaKrawedzi* listaCzasow = tmp3->krawedz->polaczenie->listaKrawedzi;
                    WezelListyKrawedzi* tmp4 = listaCzasow->glowa;
                    while (tmp4 != NULL)
                    {
                        ListaKrawedzi* listaZadan = tmp4->krawedz->polaczenie->listaKrawedzi;
                        WezelListyKrawedzi* tmp5 = listaZadan->glowa;
                        while (tmp5 != NULL)
                        {
                            ListaKrawedzi* listaGrup = tmp5->krawedz->polaczenie->listaKrawedzi;
                            WezelListyKrawedzi* tmp6 = listaGrup->glowa;
                            while (tmp6 != NULL)
                            {
                                tmp6->krawedz->przeplyw = 0;
                                tmp6 = tmp6->nastepny;
                            }
                            tmp5->krawedz->przeplyw = 0;
                            tmp5 = tmp5->nastepny;
                        }
                        tmp4->krawedz->przeplyw = 0;
                        tmp4 = tmp4->nastepny;
                    }
                    tmp3->krawedz->przeplyw = 0;
                    tmp3 = tmp3->nastepny;
                }
                tmp2->krawedz->przeplyw = 0;
                tmp2 = tmp2->nastepny;
            }
            tmp->krawedz->przeplyw = 0;
            tmp = tmp->nastepny;
        }
    }
};




//
//  MAIN
//
bool wczytajKatedry(Katedra katedry[], const int& iloscKatedr);
bool wczytajGrupyZadan(GrupaZadan grupyZadan[], const int& iloscGrupZadan);
void wypiszDaneWejsciowe(const int& trybSzeregowania, const int& opcjaWyjscia, const int& parametrK,
    Katedra katedry[], const int& iloscKatedr, GrupaZadan grupyZadan[], const int& iloscGrupZadan);
void stworzListeDniICzasow(ListaDniICzasow* lista, GrupaZadan grupyZadan[], const int& iloscGrupZadan);

void zbudujGraf(Graf* graf, Katedra katedry[], const int& iloscKatedr, GrupaZadan grupyZadan[], const int& iloscGrupZadan, ListaDniICzasow* listaDniICzasow);
int uruchomAlgorytmNaGrafie(Graf* graf);
void wykonajZadanie(const int& trybSzeregowania, const int& opcjaWyjscia,
    Katedra katedry[], const int& iloscKatedr, GrupaZadan grupyZadan[], const int& iloscGrupZadan,
    Graf* graf, ListaDniICzasow* listaDniICzasow);

void wyswietlanieJeden(const string& najlepszaKombinacja, const int& najmniejszaSuma, Katedra katedry[], const int& iloscKatedr);
void wyswietlanieDwa(const string& najlepszaKombinacja, const int& najmniejszaSuma, Katedra katedry[], const int& iloscKatedr, GrupaZadan* grupyZadan, const int& ileGrupZadan, ListaDniICzasow* ListaDniICzasow);

bool czyDobraPermutacjaPierwszegoSzeregowania(Katedra katedry[], const int& iloscKatedr, const int& wymiarY, const string& permutacja, int& suma);
bool czyDobraPermutacjaDrugiegoSzeregowania(Katedra katedry[], const int& iloscKatedr, const int& wymiarY, const string& permutacja, int& suma);

int main()
{
    int trybSzeregowania, opcjaWyjscia;
    int iloscKatedr, iloscGrupZadan;

    int parametrK = 0; // tylko do trybu szeregowania = 3

    cin >> trybSzeregowania;
    if (trybSzeregowania == 3)
        cin >> parametrK;
    cin >> opcjaWyjscia;

    cin >> iloscKatedr;
    Katedra* katedry = new Katedra[iloscKatedr];
    wczytajKatedry(katedry, iloscKatedr);

    cin >> iloscGrupZadan;
    GrupaZadan* grupyZadan = new GrupaZadan[iloscGrupZadan];
    wczytajGrupyZadan(grupyZadan, iloscGrupZadan);

    Graf* graf = new Graf();
    ListaDniICzasow* listaDniICzasow = new ListaDniICzasow(); // w budowaniu grafu nie zmienia sie nigdy
    stworzListeDniICzasow(listaDniICzasow, grupyZadan, iloscGrupZadan);

    zbudujGraf(graf, katedry, iloscKatedr, grupyZadan, iloscGrupZadan, listaDniICzasow);

    wykonajZadanie(trybSzeregowania, opcjaWyjscia, katedry, iloscKatedr, grupyZadan, iloscGrupZadan, graf, listaDniICzasow);

    delete[] katedry;
    delete[] grupyZadan;

    return 0;
}




//
//  WCZYTYWANIE
//
bool wczytajKatedry(Katedra katedry[], const int& iloscKatedr)
{
    string nazwa;
    int iloscPracownikow;

    for (int i = 0; i < iloscKatedr; i++)
    {
        cin >> nazwa >> iloscPracownikow;
        katedry[i] = Katedra(nazwa, iloscPracownikow);
        katedry[i].wczytajPracownikow();
    }

    return true;
}

bool wczytajGrupyZadan(GrupaZadan grupyZadan[], const int& iloscGrupZadan)
{
    string nazwa;
    int lacznaIloscOsoboGodzin;
    int iloscZadan;

    for (int i = 0; i < iloscGrupZadan; i++)
    {
        cin >> nazwa >> iloscZadan >> lacznaIloscOsoboGodzin;
        grupyZadan[i] = GrupaZadan(nazwa, iloscZadan, lacznaIloscOsoboGodzin);
        grupyZadan[i].wczytajZadania();
    }

    return true;
}



//
//  ALGORYTM
//
void wypelnijTablicePermutacji(int wyk, char liczba[], string liczby[])
{
    static int index = 0;

    for (int i = 1; i <= 2; i++)
    {
        if (i % 2)
            liczba[wyk] = '1';
        else
            liczba[wyk] = '0';

        if (wyk > 0)
            wypelnijTablicePermutacji(wyk - 1, liczba, liczby);
        else
        {
            liczba += '\0';
            liczby[index] = liczba;
            index++;
        }
    }
}

void wykonajZadanie(
    const int& trybSzeregowania, const int& opcjaWyjscia,
    Katedra katedry[], const int& iloscKatedr, GrupaZadan grupyZadan[], const int& iloscGrupZadan,
    Graf* graf, ListaDniICzasow* listaDniICzasow
)
{
    Wierzcholek* zrodloCalegoGrafu = graf->zrodlo;
    int najmniejszaSuma = -1;
    int suma = 0;

    int potrzebnyPrzeplyw = 0;
    int iloscPracownikow = 0;
    int najwiekszaIloscPracownikow = 0;

    for (int i = 0; i < iloscGrupZadan; i++)
        potrzebnyPrzeplyw += grupyZadan[i].getLacznaIloscOsoboGodzin();

    for (int i = 0; i < iloscKatedr; i++)
    {
        iloscPracownikow += katedry[i].getIloscPracownikow();
        if (katedry[i].getIloscPracownikow() > najwiekszaIloscPracownikow)
            najwiekszaIloscPracownikow = katedry[i].getIloscPracownikow();
    }

    int wymiarY = pow(2, iloscPracownikow);
    string* permutacje = new string[wymiarY];
    char* liczba = new char[iloscPracownikow + 1];
    liczba[iloscPracownikow] = '\0';
    for (int i = 0; i < iloscPracownikow; i++)
        liczba[i] = '1';

    wypelnijTablicePermutacji(iloscPracownikow - 1, liczba, permutacje);
    string najlepszaKombinacja = "";

    for (int i = 0; i < wymiarY - 1; i++)
    {
        suma = 0;

        switch (trybSzeregowania)
        {
        case 1:
            if (!czyDobraPermutacjaPierwszegoSzeregowania(katedry, iloscKatedr, wymiarY, permutacje[i], suma))
                continue;
            break;

        case 2:
            if (!czyDobraPermutacjaDrugiegoSzeregowania(katedry, iloscKatedr, wymiarY, permutacje[i], suma))
                continue;
            break;
        case 3:
            cout << "NIE ZAIMPLEMENTOWANO" << endl;
            delete[] permutacje;
            return;
        }


        if (i > 0)
        {
            graf->zrodlo = zrodloCalegoGrafu;
            graf->wyzerujPrzeplywy();
        }

        Wierzcholek* tymczasoweZrodlo = new Wierzcholek("TEMPZRODLO");
        WezelListyKrawedzi* wezel = graf->zrodlo->listaKrawedzi->glowa;
        for (int j = 0; j < iloscPracownikow; j++)
        {
            if (permutacje[i][j] == '1')
            {
                Krawedz* tempKrawedz = new Krawedz(tymczasoweZrodlo, wezel->krawedz->przepustowosc);
                graf->dodajKrawedzDoWierzcholka(tymczasoweZrodlo, tempKrawedz);
                graf->dodajWierzcholekDoKrawedzi(wezel->krawedz->polaczenie, tempKrawedz);
            }
            wezel = wezel->nastepny;
        }
        graf->zrodlo = tymczasoweZrodlo;

        if (uruchomAlgorytmNaGrafie(graf) == potrzebnyPrzeplyw)
        {
            if (suma < najmniejszaSuma || najmniejszaSuma < 0)
            {
                najlepszaKombinacja = permutacje[i];
                najmniejszaSuma = suma;
            }
        }
    }

    switch (opcjaWyjscia)
    {
    case 1:
        wyswietlanieJeden(najlepszaKombinacja, najmniejszaSuma, katedry, iloscKatedr);
        break;
    case 2:
        wyswietlanieDwa(najlepszaKombinacja, najmniejszaSuma, katedry, iloscKatedr, grupyZadan, iloscGrupZadan, listaDniICzasow);
        break;
    }


    delete[] liczba;
    delete[] permutacje;
}



//
//  GLOWNY ALGORYTM
//
int uruchomAlgorytmNaGrafie(Graf* graf)
{
    Wierzcholek* zrodlo = graf->getZrodlo();
    Wierzcholek* ujscie = graf->getUjscie();

    ListaKrawedzi* listaPoprzednichKrawedzi = new ListaKrawedzi();
    list<Wierzcholek*>* kolejkaWierzcholkow = new list<Wierzcholek*>;
    list<Wierzcholek*>* listaPoprzednichWierzcholkow = new list<Wierzcholek*>;

    bool czyIstniejeSciezkaDoUjscia = false;
    int maksymalnyPrzeplyw = 0;

    while (true)
    {
        int poprzedniPrzeplyw = zrodlo->listaKrawedzi->glowa->krawedz->przepustowosc + 1;
        int przeplywKanalu = 0;
        int rzeczywistyPrzeplyw = 0;

        // wyczysc kolejke i liste
        kolejkaWierzcholkow->clear();
        kolejkaWierzcholkow->push_back(graf->getZrodlo());
        listaPoprzednichKrawedzi->clear();
        listaPoprzednichWierzcholkow->clear();

        while (!kolejkaWierzcholkow->empty())
        {
            czyIstniejeSciezkaDoUjscia = false;
            Wierzcholek* wierzcholek = kolejkaWierzcholkow->front();
            kolejkaWierzcholkow->pop_front(); // zdejmij pierwszy element

            for (WezelListyKrawedzi* wezelListyKrawedzi = wierzcholek->listaKrawedzi->glowa; wezelListyKrawedzi != NULL; wezelListyKrawedzi = wezelListyKrawedzi->nastepny)
            {
                rzeczywistyPrzeplyw = wezelListyKrawedzi->krawedz->przepustowosc - wezelListyKrawedzi->krawedz->przeplyw;

                int cp;
                if (rzeczywistyPrzeplyw && !listaPoprzednichKrawedzi->czyJestNaLiscie(wezelListyKrawedzi->krawedz))/////////////////////////////////////////////////////////////////////////////
                {
                    listaPoprzednichKrawedzi->dodajKrawedz(wezelListyKrawedzi->krawedz);
                    cp = rzeczywistyPrzeplyw < poprzedniPrzeplyw ? rzeczywistyPrzeplyw : poprzedniPrzeplyw;
                    poprzedniPrzeplyw = cp;

                    if (wezelListyKrawedzi->krawedz->polaczenie == ujscie)
                    {
                        czyIstniejeSciezkaDoUjscia = true;
                        przeplywKanalu = cp;
                        break;
                    }
                    else
                        kolejkaWierzcholkow->push_back(wezelListyKrawedzi->krawedz->polaczenie); // dodaj do listy kolejny wierzcholek
                }
            }
            if (czyIstniejeSciezkaDoUjscia)
                break;
        }
        if (!czyIstniejeSciezkaDoUjscia)
            break;

        maksymalnyPrzeplyw += przeplywKanalu;

        Wierzcholek* u = ujscie;
        for (Krawedz* i = listaPoprzednichKrawedzi->ogon->krawedz; i != NULL; i = listaPoprzednichKrawedzi->getPoprzednia(i))
        {
            for (WezelListyKrawedzi* k = listaPoprzednichKrawedzi->glowa; k != NULL; k = k->nastepny)
            {
                if (k->krawedz->polaczenie == u)
                {
                    u = k->krawedz->poprzedni;
                    k->krawedz->przeplyw += przeplywKanalu;
                    break;
                }
            }
        }
    }

    listaPoprzednichKrawedzi->clear();
    listaPoprzednichWierzcholkow->clear();
    kolejkaWierzcholkow->clear();

    delete listaPoprzednichKrawedzi;
    delete listaPoprzednichWierzcholkow;
    delete kolejkaWierzcholkow;

    return maksymalnyPrzeplyw;
}


//
//  OPCJE WYSWIETLANIA
//
void wyswietlanieJeden(const string& najlepszaKombinacja, const int& najmniejszaSuma, Katedra katedry[], const int& iloscKatedr)
{
    cout << najmniejszaSuma << endl;

    int suma = 0;
    int ileZKatedry;
    int poprzednie = 0;
    for (int j = 0; j < iloscKatedr; j++)
    {
        ileZKatedry = 0;

        for (int k = 0; k < katedry[j].getIloscPracownikow(); k++)
        {
            if (najlepszaKombinacja[poprzednie + k] == '1')
                ileZKatedry++;
        }
        poprzednie += (katedry[j].getIloscPracownikow());

        if (ileZKatedry > 0)
            cout << katedry[j].getNazwa() << " " << ileZKatedry << endl;
    }
}

void wyswietlanieDwa(const string& najlepszaKombinacja, const int& najmniejszaSuma, Katedra katedry[], const int& iloscKatedr, GrupaZadan* grupyZadan, const int& ileGrupZadan, ListaDniICzasow* ListaDniICzasow)
{

    wyswietlanieJeden(najlepszaKombinacja, najmniejszaSuma, katedry, iloscKatedr);

    int suma = 0;
    int poprzednie = 0;
    int index = 0;

    for (int j = 0; j < iloscKatedr; j++)
    {
        int indexZadania = grupyZadan[index].getIloscZadan();
        for (int k = 0; k < katedry[j].getIloscPracownikow(); k++)
        {
            index = 0;
            if (najlepszaKombinacja[poprzednie + k] == '1')
            {
                cout << katedry[j].getPracownicy()[k].getImie() << " " << indexZadania << endl;
                WezelDnia* wDnia = ListaDniICzasow->glowa;
                WezelCzasu* wCzasu = wDnia->czasy;
                for (int i = 0; i < indexZadania; i++)
                {
                    cout << grupyZadan[index].getNazwa() << " " << wDnia->dzien << " " << wCzasu->czas << endl;
                    wCzasu = wCzasu->nastepny;
                }
            }
            indexZadania--;
        }
        poprzednie += (katedry[j].getIloscPracownikow());
    }
}



//
//  SPRAWDZANIE PERMUTACJI
//
void usunTablice(int tablica[])
{
    delete[] tablica;
}

bool czyDobraPermutacjaPierwszegoSzeregowania(Katedra katedry[], const int& iloscKatedr, const int& wymiarY, const string& permutacja, int& suma)
{
    int poprzednie = 0;
    for (int j = 0; j < iloscKatedr; j++)
    {
        bool czyByloZero = false;
        for (int k = 0; k < katedry[j].getIloscPracownikow(); k++)
            if (permutacja[poprzednie + k] == '1')
            {
                if (czyByloZero)
                    return false;

                suma += katedry[j].getPracownicy()[k].getWartosc();
            }
            else
                czyByloZero = true;

        poprzednie += (katedry[j].getIloscPracownikow());
    }

    return true;
}



bool czyDobraPermutacjaDrugiegoSzeregowania(Katedra katedry[], const int& iloscKatedr, const int& wymiarY, const string& permutacja, int& suma)
{
    int* ileJedynek = new int[iloscKatedr];
    for (int j = 0; j < iloscKatedr; j++)
        ileJedynek[j] = 0;
    int maksJedynek = 0;
    int indexKatedry;

    int poprzednie = 0;
    for (int j = 0; j < iloscKatedr; j++)
    {
        bool czyByloZero = false;
        for (int k = 0; k < katedry[j].getIloscPracownikow(); k++)
        {
            if (permutacja[poprzednie + k] == '1')
            {
                if (czyByloZero)
                {
                    usunTablice(ileJedynek);
                    return false;
                }

                ileJedynek[j]++;
                suma += katedry[j].getPracownicy()[k].getWartosc();
            }
            else
                czyByloZero = true;
        }

        if (ileJedynek[j] > maksJedynek)
        {
            maksJedynek = ileJedynek[j];
            indexKatedry = j;
        }

        poprzednie += katedry[j].getIloscPracownikow();
    }

    for (int j = 0; j < iloscKatedr; j++)
    {
        if (ileJedynek[indexKatedry] == katedry[indexKatedry].getIloscPracownikow()) // wzieto wszystkich
        {
            if (katedry[j].getIloscPracownikow() > ileJedynek[j])
            {
                usunTablice(ileJedynek);
                return false;
            }
        }
        else
        {
            if (maksJedynek > katedry[j].getIloscPracownikow() && ileJedynek[j] < katedry[j].getIloscPracownikow())
            {
                usunTablice(ileJedynek);
                return false;
            }
            else
                for (int k = 0; k < iloscKatedr; k++)
                {
                    if (ileJedynek[j] - ileJedynek[k] > 1 || ileJedynek[j] - ileJedynek[k] < -1)
                    {
                        usunTablice(ileJedynek);
                        return false;
                    }
                }
        }
    }

    usunTablice(ileJedynek);
    return true;
}



//
// BUDOWANIE GRAFU
//
void dodajDniICzasyDoPracownika(Graf* graf, Pracownik* pracownik, Wierzcholek* wierzcholekPracownika, ListaDniICzasow* listaDniICzasow);
void dodajZadania(Graf* graf, GrupaZadan grupyZadan[], const int& iloscGrupZadan, ListaKrawedzi* listaKrawedzi);
void scalGraf(Graf* graf, ListaKrawedzi* listaZadan);
void dodajPracownikow(Graf* graf, Katedra katedry[], const int& iloscKatedr, ListaDniICzasow* listaDniICzasow);

void zbudujGraf(Graf* graf, Katedra katedry[], const int& iloscKatedr, GrupaZadan grupyZadan[], const int& iloscGrupZadan, ListaDniICzasow* listaDniICzasow)
{
    dodajPracownikow(graf, katedry, iloscKatedr, listaDniICzasow);

    ListaKrawedzi* listaZadan = new ListaKrawedzi();
    dodajZadania(graf, grupyZadan, iloscGrupZadan, listaZadan);

    scalGraf(graf, listaZadan);
}


void dodajPracownikow(Graf* graf, Katedra katedry[], const int& iloscKatedr, ListaDniICzasow* listaDniICzasow)
{
    Wierzcholek* zrodlo = graf->getZrodlo();

    for (int i = 0; i < iloscKatedr; i++)
    {
        for (int j = 0; j < katedry[i].getIloscPracownikow(); j++)
        {
            Wierzcholek* nowyWierzcholek = new Wierzcholek(katedry[i].getPracownicy()[j].getImie());
            Krawedz* nowaKrawedz = new Krawedz(nowyWierzcholek, katedry[i].getPracownicy()[j].getLiczbaGodzinOgolem());

            graf->dodajKrawedzDoWierzcholka(zrodlo, nowaKrawedz);
            graf->dodajWierzcholekDoKrawedzi(nowyWierzcholek, nowaKrawedz);

            dodajDniICzasyDoPracownika(graf, &katedry[i].getPracownicy()[j], nowyWierzcholek, listaDniICzasow);
        }
    }
}


void dodajDniICzasyDoPracownika(Graf* graf, Pracownik* pracownik, Wierzcholek* wierzcholekPracownika, ListaDniICzasow* listaDniICzasow)
{
    WezelDnia* wDnia = listaDniICzasow->glowa;

    while (wDnia != NULL)
    {
        Wierzcholek* nowyWierzcholekDnia = new Wierzcholek("DZIEN", wDnia->dzien, 0);
        Krawedz* nowaKrawedzDnia = new Krawedz(nowyWierzcholekDnia, pracownik->getIloscGodzinNaDzien());

        graf->dodajKrawedzDoWierzcholka(wierzcholekPracownika, nowaKrawedzDnia);
        graf->dodajWierzcholekDoKrawedzi(nowyWierzcholekDnia, nowaKrawedzDnia);

        WezelCzasu* wCzasu = wDnia->czasy;
        while (wCzasu != NULL)
        {
            Wierzcholek* nowyWierzcholekCzasu = new Wierzcholek("CZAS", 0, wCzasu->czas);
            Krawedz* nowaKrawedzCzasu = new Krawedz(nowyWierzcholekCzasu, 1);

            graf->dodajKrawedzDoWierzcholka(nowyWierzcholekDnia, nowaKrawedzCzasu);
            graf->dodajWierzcholekDoKrawedzi(nowyWierzcholekCzasu, nowaKrawedzCzasu);

            wCzasu = wCzasu->nastepny;
        }
        wDnia = wDnia->nastepny;
    }
}


void dodajZadania(Graf* graf, GrupaZadan grupyZadan[], const int& iloscGrupZadan, ListaKrawedzi* listaZadan)
{
    Wierzcholek* ujscie = graf->getUjscie();

    for (int i = 0; i < iloscGrupZadan; i++)
    {
        Wierzcholek* nowyWierzcholekGrupyZadan = new Wierzcholek(grupyZadan[i].getNazwa());
        Krawedz* nowaKrawedzGrupyZadan = new Krawedz(ujscie, grupyZadan[i].getLacznaIloscOsoboGodzin());

        graf->dodajKrawedzDoWierzcholka(nowyWierzcholekGrupyZadan, nowaKrawedzGrupyZadan);
        graf->dodajWierzcholekDoKrawedzi(ujscie, nowaKrawedzGrupyZadan);

        int suma = 0;
        for (int j = 0; j < grupyZadan[i].getIloscZadan(); j++)
        {
            Wierzcholek* nowyWierzcholekZadania = new Wierzcholek("ZADANIE", grupyZadan[i].getZadania()[j].getDzien(), grupyZadan[i].getZadania()[j].getCzas());
            Krawedz* nowaKrawedzZadania = new Krawedz(nowyWierzcholekZadania, grupyZadan[i].getZadania()[j].getMaksymalnaIloscOsoboGodzin() - grupyZadan[i].getZadania()[j].getMinimalnaIloscOsoboGodzin());
            graf->dodajKrawedzDoWierzcholka(nowyWierzcholekZadania, nowaKrawedzZadania);
            graf->dodajWierzcholekDoKrawedzi(nowyWierzcholekGrupyZadan, nowaKrawedzZadania);

            nowaKrawedzZadania = new Krawedz(ujscie, grupyZadan[i].getZadania()[j].getMinimalnaIloscOsoboGodzin());
            graf->dodajKrawedzDoWierzcholka(nowyWierzcholekZadania, nowaKrawedzZadania);
            graf->dodajWierzcholekDoKrawedzi(ujscie, nowaKrawedzZadania);

            suma += grupyZadan[i].getZadania()[j].getMinimalnaIloscOsoboGodzin();
            Krawedz* nowaKrawedzListy = new Krawedz(nowyWierzcholekZadania, 0);
            listaZadan->dodajKrawedz(nowaKrawedzListy);
        }
        nowaKrawedzGrupyZadan->przepustowosc = grupyZadan[i].getLacznaIloscOsoboGodzin() - suma;
    }
}


void scalGraf(Graf* graf, ListaKrawedzi* listaZadan)
{
    Wierzcholek* zrodlo = graf->getZrodlo();
    WezelListyKrawedzi* wListyZadan;

    ListaKrawedzi* listaZrodla = zrodlo->listaKrawedzi;
    WezelListyKrawedzi* tmp = listaZrodla->glowa;
    while (tmp != NULL)
    {
        ListaKrawedzi* listaPracownika = tmp->krawedz->polaczenie->listaKrawedzi;
        WezelListyKrawedzi* tmp2 = listaPracownika->glowa;

        while (tmp2 != NULL)
        {
            ListaKrawedzi* listaDnia = tmp2->krawedz->polaczenie->listaKrawedzi;
            WezelListyKrawedzi* tmp3 = listaDnia->glowa;
            wListyZadan = listaZadan->glowa;
            while (wListyZadan != NULL)
            {
                if (wListyZadan->krawedz->polaczenie->dzien == tmp2->krawedz->polaczenie->dzien)
                {
                    ListaKrawedzi* listaCzasu = tmp2->krawedz->polaczenie->listaKrawedzi;
                    WezelListyKrawedzi* tmp3 = listaCzasu->glowa;
                    while (tmp3 != NULL)
                    {
                        if (wListyZadan->krawedz->polaczenie->czas == tmp3->krawedz->polaczenie->czas)
                        {
                            Krawedz* nowaKrawedzCzasu = new Krawedz(wListyZadan->krawedz->polaczenie, 1);
                            graf->dodajKrawedzDoWierzcholka(tmp3->krawedz->polaczenie, nowaKrawedzCzasu);
                        }
                        tmp3 = tmp3->nastepny;
                    }
                }
                wListyZadan = wListyZadan->nastepny;
            }
            tmp2 = tmp2->nastepny;
        }
        tmp = tmp->nastepny;
    }
}


void stworzListeDniICzasow(ListaDniICzasow* lista, GrupaZadan grupyZadan[], const int& iloscGrupZadan)
{
    for (int i = 0; i < iloscGrupZadan; i++)
    {
        for (int j = 0; j < grupyZadan[i].getIloscZadan(); j++)
        {
            int dzien = grupyZadan[i].getZadania()[j].getDzien();
            int czas = grupyZadan[i].getZadania()[j].getCzas();

            if (lista->czyDzienOryginalny(dzien))
                lista->dodajDzien(dzien);

            if (lista->CzyCzasOryginalny(czas, dzien))
                lista->dodajCzasDoDnia(czas, dzien);
        }
    }
}
