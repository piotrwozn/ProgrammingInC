#ifndef PROJEKTPJC_LISTA_H
#define PROJEKTPJC_LISTA_H

#include "Password.h"

class Lista {
private:

    struct node{
        node* next;
        Password data;
    };

    typedef struct node* nodePointer;
    nodePointer head;
    nodePointer current;
    nodePointer tmp;
    nodePointer last;
public:

    Lista();
    void addNode(Password *addPassword);
    void removeNode(int pos);
    void showList();
    void showListKat(string kat);
    void addPassword(string name, string pass, string kat, string strona, string login);
    void removeCategory(string category);
    void sortBy(int by);
    void sortListName(node *swapNode);
    void sortListPassword(node *swapNode);
    void sortListCategory(node *swapNode);
    void save(string path,int key);
    string encrypt(nodePointer tmp,int key);
};


#endif //PROJEKTPJC_LISTA_H
