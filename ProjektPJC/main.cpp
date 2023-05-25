#include <iostream>
#include <unistd.h>
#include "Password.h"
#include "Lista.h"
#include <fstream>

using namespace std;

bool endFlag=false;
int key=2;

void menu(Lista& list, string path){
    int choice=0;
    cout<<"Co chcesz zrobic: "<<endl;
    cout<<"1) wyswietilic liste hasel?"<<endl;
    cout<<"2) dodac haslo?"<<endl;
    cout<<"3) usunac haslo?"<<endl;
    cout<<"4) usunac hasla z podanej kategorii?"<<endl;
    cout<<"5) wyswietlic liste z podanej kategorii?"<<endl;
    cout<<"6) posortowac liste wedlug podanego parametru?"<<endl;
    cout<<"7) zakonczyc?"<<endl;
    cin>>choice;
    if(choice == 1) list.showList();
    if(choice == 2){
        string name;
        string pass;
        string kat;
        cout << "Podaj nazwe: ";
        cin >> name;
        cout << "Podaj haslo: ";
        cin >> pass;
        cout << "Podaj kategorie: ";
        cin >> kat;
        list.addPassword(name, pass, kat);
        cout<<"Dodano haslo o nazwie: "<<name<<", hasle: "<<pass<<", kategorii: "<<kat<<endl;
    }
    if(choice == 3){
        int pos = 0;
        cout << "Podaj pozycje hasla ktore chcesz usunac: ";
        cin >> pos;
        list.removeNode(pos);
        cout<<"Usunieteo."<<endl;
    }
    if(choice == 4){
        string kat;
        cout << "Podaj kategorie: ";
        cin >> kat;
        list.removeCategory(kat);
    }
    if(choice == 5){
        string kat;
        cout << "Podaj kategorie: ";
        cin >> kat;
        list.showListKat(kat);
    }
    if(choice == 6){
        cout<<"Wedlug czego chcesz sortowac:"<<endl;
        cout<<"1) nazwa"<<endl;
        cout<<"2) haslo"<<endl;
        cout<<"3) kategoria"<<endl;
        int by;
        cin>>by;
        list.sortBy(by);
        string sby;
        if(by==1) sby="nazwa";
        if(by==2) sby="haslo";
        if(by==3) sby="kategoria";
        if(by <= 4 && by >= 0 ) cout<<"Posortowano wedlug: "<<sby<<endl;
    }
    if(choice == 7){
        endFlag = true;
        cout<<"Zapisano liste."<<endl;
        list.save(path,key);
    }
    if(choice >= 8 && choice <= 0) cout<<"Podana bledna wartosc"<<endl;
    cout<<""<<endl;
    sleep(1);
}

string decrypt(string word,int key){
    for(int i=0;i<word.length();i++){
        word[i]-=key;
    }
    return word;
}

Lista readFile(string path,Lista list){
    ifstream file(path);
    Password* pass = new Password();
    int counter=0;
    while(!file.eof()) {
        string word;
        file>>word;
        word=decrypt(word,key);
        if (counter == 3) {
            counter = 0;
            list.addNode(pass);
            pass = new Password();
        }
        if (counter == 2){
            pass->setCategory(word);
            counter++;
        }
        if (counter == 1){
            pass->setPassword(word);
            counter++;
        }
        if(counter==0) {
            pass->setName(word);
            counter++;
        }
    }
    return list;
}

bool logg(){
    int pas;
    Password* pass=new Password();
    cout << "Podaj haslo: ";
    cin >> pas;
    return true;
}

int main() {
    bool log=logg();
    if(log == true) {
        Lista list;
        string path = "C:\\Users\\Dominik\\Desktop\\zakryptowane.txt";
        list = readFile(path, list);
        while (endFlag == false) {
            menu(list, path);
        }
    }
    return 0;
}
