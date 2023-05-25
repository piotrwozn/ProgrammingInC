#include <iostream>
#include <fstream>
#include "Lista.h"

using namespace std;

Lista::Lista() {
    head=NULL;
    current=NULL;
    tmp=NULL;
}

void Lista::addNode(Password *addPassword) {
    nodePointer  n = new node;
    n->next = NULL;
    n->data = *addPassword;

    if(head != NULL){
        current = head;
        while (current->next != NULL){
            current = current->next;
        }
        current->next = n;
    } else{
        head=n;
    }

}

void Lista::addPassword(string name, string pass, string kat){
    Password* newPass = new Password;
    newPass->setName(name);
    newPass->setPassword(pass);
    newPass->setCategory(kat);
    addNode(newPass);
}

void Lista::removeNode(int pos) {
    pos-=1;
    tmp = head;
    if(pos == 0){
        head = head->next;
        return;
    }
    for(int i = 0;tmp != NULL && i<pos-1;i++){
        tmp=tmp->next;
    }
    if(tmp == NULL || tmp->next == NULL){
        return;
    }
    tmp->next = tmp->next->next;
}

void Lista::showList() {
    if(head == NULL){
        cout<< "Lista jest pusta" << endl;
    }else {
        current = head;
        cout<<"Lista: " << endl;
        int counter=1;
        while (current != NULL) {
            cout << counter <<") Nazwa: " << current->data.getName() << ", haslo: " << current->data.getPassword() << ", kategoria: " << current->data.getCategory() << endl;
            current = current->next;
            counter++;
        }
    }
}

void Lista::showListKat(string kat) {
    if(head == NULL){
        cout<< "Lista jest pusta" << endl;
    }else {
        current = head;
        cout<<"Lista kategorii \"" << kat << "\": " << endl;
        int counter=1;
        while (current != NULL) {
            if(current->data.getCategory() == kat) {
                cout << counter << ") Nazwa: " << current->data.getName() << ", haslo: " << current->data.getPassword()<< endl;
                counter++;
            }
            current = current->next;

        }
    }
}

void Lista::removeCategory(string kat) {
    tmp=head;
    bool jestHaslo = false;
    while (head->data.getCategory() == kat) {
        head = head->next;
        jestHaslo = true;
    }
    while (tmp->next != NULL) {
        if (tmp->next->data.getCategory() == kat) {
            tmp->next = tmp->next->next;
            jestHaslo = true;
        } else tmp = tmp->next;
    }
    if(jestHaslo==false){
        cout << "nie ma na liscie hasla o kategorii: " << kat << endl;
    }

    if(jestHaslo==true){
        cout << "Usunieto wszystkie hasla o kategorii: " << kat << endl;
    }
}

void Lista::sortBy(int by){
    node *tmp = head;
    last = NULL;
    node *current = tmp;
    while(current != NULL) {
        node *next=current->next;
        switch (by) {
            case 1:
                sortListName(current);
                break;
            case 2:
                sortListPassword(current);
                break;
            case 3:
                sortListCategory(current);
                break;
            default:
                cout<<"podano bledna wartosc"<<endl;
                break;
        }
        current = next;
    }
    head = last;

}

void Lista::sortListName(node *swapNode) {
    if (last == NULL || last->data.getName() >= swapNode->data.getName()) {
        swapNode->next = last;
        last = swapNode;
    } else {
        node *current = last;
        while (current->next != NULL && current->next->data.getName() < swapNode->data.getName()) {
            current = current->next;
        }
        swapNode->next = current->next;
        current->next = swapNode;
    }
}

void Lista::sortListPassword(node *swapNode){
    if (last == NULL || last->data.getPassword() >= swapNode->data.getPassword()) {
        swapNode->next = last;
        last = swapNode;
    } else {
        node *current = last;
        while (current->next != NULL && current->next->data.getPassword() < swapNode->data.getPassword()) {
            current = current->next;
        }
        swapNode->next = current->next;
        current->next = swapNode;
    }
}

void Lista::sortListCategory(node *swapNode){
    if (last == NULL || last->data.getCategory() >= swapNode->data.getCategory()) {
        swapNode->next = last;
        last = swapNode;
    } else {
        node *current = last;
        while (current->next != NULL && current->next->data.getCategory() < swapNode->data.getCategory()) {
            current = current->next;
        }
        swapNode->next = current->next;
        current->next = swapNode;
    }
}

void Lista::save(string path,int key){
        ofstream saveFile;
        saveFile.open(path);
        tmp=head;
        do {
            saveFile << encrypt(tmp,key) << " \n";
            tmp = tmp->next;
        }while(tmp !=NULL);
        saveFile.close();
}

string Lista::encrypt(nodePointer tmp,int key){
    string Name=tmp->data.getName();
    string Pass=tmp->data.getPassword();
    string Cat=tmp->data.getCategory();
    string input=Name+" "+Pass+" "+Cat;
    for(int i=0;i<input.length();i++) {
        if (input[i] == ' ') {
        } else {
            input[i] += key;
        }
    }
    return input;
}

