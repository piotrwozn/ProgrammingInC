#include <string>

using namespace std;
#ifndef PROJEKTPJC_PASSWORD_H
#define PROJEKTPJC_PASSWORD_H


class Password {
private:
    string name;
    int password;
    string kat;
    int haslo = 64;
public:
    string getName(){
        return name;
    }
    int getPassword(){
        return password;
    }
    string getCategory(){
        return kat;
    }
    void setName(string n){
        name=n;
    }
    void setPassword(int p){
        password=p;
    }
    void setCategory(string c){
        kat=c;
    }

    int getHaslo(){
        return haslo;
    }
};


#endif //PROJEKTPJC_PASSWORD_H
