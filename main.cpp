#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
struct Przyjaciel {
    int id;
    string imie, nazwisko;
    string numerTelefonu;
    string email, adres;
};
int konwersjaStringNaInt(string wyraz) {
    int i;
    istringstream iss(wyraz);
    iss >> i;
    return i;
}
void zapiszPrzyjaciolWPlikuTekstowym(vector <Przyjaciel> &przyjaciele)
{
         fstream plikt;
        plikt.open("przyjaciele_nowy_format.txt",ios::out);
        for(vector<Przyjaciel>::iterator i=przyjaciele.begin(); i<przyjaciele.end(); i++) {
            plikt<<i->id<<'|';
            plikt<<i->imie<<'|';
            plikt<<i->nazwisko<<'|';
            plikt<<i->numerTelefonu<<'|';
            plikt<<i->email<<'|';
            plikt<<i->adres<<'|';
            plikt<<endl;
        }
        plikt.close();

}
void dodajPrzyjacielaDoListy(vector<Przyjaciel> &przyjaciele) {
    Przyjaciel nowyPrzyjaciel;
    cout<<"Podaj imie znajomego: ";
    cin>>nowyPrzyjaciel.imie;
    cout<<"Podaj nazwisko znajomego: ";
    cin>>nowyPrzyjaciel.nazwisko;
    cout<<"Podaj email znajomego: ";
    cin>>nowyPrzyjaciel.email;
    cout<<"Podaj numer telefonu znajomego: ";
    cin.sync();
    getline(cin,nowyPrzyjaciel.numerTelefonu);
    cout<<"Podaj adres znajomego: ";
    cin.sync();
    getline(cin,nowyPrzyjaciel.adres);

    if (przyjaciele.size()>0) {
        int idPoprzedniegoPrzyjaciela=przyjaciele.back().id;
        nowyPrzyjaciel.id=idPoprzedniegoPrzyjaciela+1;
    } else
        nowyPrzyjaciel.id=1;
    przyjaciele.push_back(nowyPrzyjaciel);
    zapiszPrzyjaciolWPlikuTekstowym(przyjaciele);
    Sleep(1500);
}
void wyswietlPrzyjaciela(Przyjaciel przyjaciel) {
    cout<<przyjaciel.id<<endl;
    cout<<przyjaciel.imie<<endl;
    cout<<przyjaciel.nazwisko<<endl;
    cout<<przyjaciel.numerTelefonu<<endl;
    cout<<przyjaciel.email<<endl;
    cout<<przyjaciel.adres<<endl;
}
void wyswietlWszystkichPrzyjaciol(vector <Przyjaciel> &przyjaciele) {
    for(vector<Przyjaciel> ::iterator itr=przyjaciele.begin(); itr!=przyjaciele.end(); itr++) {
        wyswietlPrzyjaciela(*itr);
    }
    system("pause");
}
void wyszukajPrzyjaciolOPodanymImieniu(vector<Przyjaciel> &przyjaciele) {
    string szukaneImie;
    int znalezieni=0;
    cout<<"Prosze podac imie do wyszukiwania przyjaciol: ";
    cin>>szukaneImie;
    for(vector<Przyjaciel> ::iterator itr=przyjaciele.begin(); itr!=przyjaciele.end(); itr++) {
        if(itr->imie==szukaneImie) {
            wyswietlPrzyjaciela(*itr);
            znalezieni++;
        }
    }
    if(znalezieni==0)
        cout<<"nie znaleziono przyjaciol o tym imieniu"<<endl;
    else
        cout<<"znaleziono "<<znalezieni<<" przyjaciol o podanym imieniu"<<endl;
    system("pause");
}
void wyszukajPrzyjaciolOPodanymNazwisku(vector<Przyjaciel> &przyjaciele) {
    string szukaneNazwisko;
    int znalezieni=0;
    cout<<"Prosze podac nazwisko do wyszukiwania przyjaciol: ";
    cin>>szukaneNazwisko;
    for(vector<Przyjaciel> ::iterator itr=przyjaciele.begin(); itr!=przyjaciele.end(); itr++) {
        if(itr->nazwisko==szukaneNazwisko) {
            wyswietlPrzyjaciela(*itr);
            znalezieni++;
        }
    }
    if(znalezieni==0)
        cout<<"nie znaleziono przyjaciol o tym nazwisku"<<endl;
    else
        cout<<"znaleziono "<<znalezieni<<" przyjaciol o podanym nazwisku"<<endl;
    system("pause");
}
void wczytajPrzyjaciolzPliku(vector<Przyjaciel> &przyjaciele) {
    fstream plik;
    string odczytywanaLinia;
    Przyjaciel nowyPrzyjaciel;
    plik.open("przyjaciele_nowy_format.txt",ios::in);
    while(plik.good()==true) {
        while( !plik.eof() ) {
            getline(plik,odczytywanaLinia,'|');
            if(odczytywanaLinia=="\n"||odczytywanaLinia=="") {
                break;
            }
            nowyPrzyjaciel.id=konwersjaStringNaInt(odczytywanaLinia);
            getline(plik,odczytywanaLinia,'|');
            nowyPrzyjaciel.imie=odczytywanaLinia;
            getline(plik,odczytywanaLinia,'|');
            nowyPrzyjaciel.nazwisko=odczytywanaLinia;
            getline(plik,odczytywanaLinia,'|');
            nowyPrzyjaciel.numerTelefonu=odczytywanaLinia;
            getline(plik,odczytywanaLinia,'|');
            nowyPrzyjaciel.email=odczytywanaLinia;
            getline(plik,odczytywanaLinia,'|');
            nowyPrzyjaciel.adres=odczytywanaLinia;
            przyjaciele.push_back(nowyPrzyjaciel);
        }
    }
    plik.close();
}
void usunZListyPrzyjaciol(vector <Przyjaciel> &przyjaciele) {
    if(przyjaciele.size()==0)
        cout<<"Brak zapisanych przyjaciol";
    else {
        int numerIDPrzyjaciela;
        cout<<"Podaj numer ID przyjaciela ktorego chcesz usunac z listy: ";
        cin>>numerIDPrzyjaciela;
        bool znalezionoIDPrzyjaciela=false;
        for(vector<Przyjaciel>::iterator i=przyjaciele.begin(); i<przyjaciele.end(); i++) {
            if(i->id==numerIDPrzyjaciela) {
                wyswietlPrzyjaciela(*i);
                cout<<"czy na pewno chcesz usnunac przyjaciela z listy(wcisnij 't' aby potwierdzic): ";
                cin.ignore();
                if(getchar()=='t') {
                    przyjaciele.erase(i);
                    znalezionoIDPrzyjaciela=true;
                    cout<<"Usunieto przyjaciela z listy. ";
                } else {
                    cout<<"Nie usunieto przyjaciela";
                    znalezionoIDPrzyjaciela=true;
                }
            }
        }
        if (znalezionoIDPrzyjaciela==false) {
            cout<<"Nie znalezniono przyjaciela o podanym ID.";
        }
        zapiszPrzyjaciolWPlikuTekstowym(przyjaciele);
    }
    Sleep(3000);
}
Przyjaciel edytujDanePrzyjaciela(Przyjaciel przyjacielDoEdycji) {
    cout<<"Edytowanie danych znajomego"<<endl;
    cout<<"---------------------------"<<endl;
    cout<<"1.Imie"<<endl;
    cout<<"2.Nazwisko"<<endl;
    cout<<"3.Numer telefonu"<<endl;
    cout<<"4.Email"<<endl;
    cout<<"5.Adres"<<endl;
    cout<<"6.Powrot do menu"<<endl;
    int wybor;

    cin>>wybor;
    switch(wybor) {
    case 1:
        cout<<"podaj zmienione imie: ";
        cin>>przyjacielDoEdycji.imie;
        return przyjacielDoEdycji;
    case 2:
        cout<<"podaj zmienione nazwisko: ";
        cin>>przyjacielDoEdycji.nazwisko;
        return przyjacielDoEdycji;
    case 3:
        cout<<"podaj zmieniony numer telefonu: ";
        cin.sync();
        getline(cin,przyjacielDoEdycji.numerTelefonu);
        return przyjacielDoEdycji;
    case 4:
        cout<<"podaj zmieniony email: ";
        cin>>przyjacielDoEdycji.email;
        return przyjacielDoEdycji;
    case 5:
        cout<<"podaj zmieniony adres: ";
        cin.sync();
        getline(cin,przyjacielDoEdycji.adres);
        return przyjacielDoEdycji;
    case 6:
        return przyjacielDoEdycji;
    }
}
int main() {
    char wybor;
    vector <Przyjaciel> przyjaciele;
    wczytajPrzyjaciolzPliku(przyjaciele);
    while(1) {
        system("cls");
        cout<<"MENU GLOWNE"<<endl;
        cout<<"-----------"<<endl;
        cout<<"1.Dodaj nowego przyjaciela"<<endl;
        cout<<"2.Wyswietl wszystkich przyjaciol o podanym imieniu"<<endl;
        cout<<"3.Wyswietl wszystkich przyjaciol o podanym nazwisku"<<endl;
        cout<<"4.Wyswietl wszystkich przyjaciol"<<endl;
        cout<<"5.Usun z listy przyjacol"<<endl;
        cout<<"6.Edytuj dane wybranego przyjaciela"<<endl;
        cout<<"9.Wyjscie z programu"<<endl;

        cin>>wybor;

        switch(wybor) {
        case '1': {
            system("cls");
            dodajPrzyjacielaDoListy(przyjaciele);
            break;
        }
        case '2': {
            system("cls");
            wyszukajPrzyjaciolOPodanymImieniu(przyjaciele);
            break;
        }
        case '3': {
            system("cls");
            wyszukajPrzyjaciolOPodanymNazwisku(przyjaciele);
            break;
        }
        case '4': {
            system("cls");
            wyswietlWszystkichPrzyjaciol(przyjaciele);
            break;
        }
        case '5':
            system("cls");
            usunZListyPrzyjaciol(przyjaciele);
            break;
        case '6':
            system("cls");
            int IDprzyjacielaDoEdycji;
            cout<<"Podaj ID przyjaciela do edycji: ";
            cin>>IDprzyjacielaDoEdycji;
            for(vector<Przyjaciel>::iterator i=przyjaciele.begin(); i<przyjaciele.end(); i++) {
                if(i->id==IDprzyjacielaDoEdycji) {
                    wyswietlPrzyjaciela(*i);
                    cout<<endl;
                    *i = edytujDanePrzyjaciela(*i);
                }
            }
          zapiszPrzyjaciolWPlikuTekstowym(przyjaciele);
            break;
        case '9': {
            exit(0);
        }
        default:
            cout<<"Podano niepoprawna opcje, sprobuj jeszce raz:";
            Sleep(1000);
        }
    }
    return 0;
}
