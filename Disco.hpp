#include <iostream>
using namespace std; 

class Disco
{
private:
    int numeroDisco; 
    int PosX; 
    int PosY; 
public:
    Disco(int, int, int);
    int getPosX(); 
    int getPosY(); 
    int getNDisco(); 
    void setPosX(int);
    void setPosY(int);
    void setNDisco(int);
    ~Disco();
};

Disco::Disco(int numeroDisco, int PosX, int PosY)
{
    this->numeroDisco = numeroDisco; 
    this->PosX = PosX; 
    this->PosY = PosY;
}

int Disco::getPosX(){
    return PosX; 
}

int Disco::getPosY(){
    return PosY; 
}

int Disco::getNDisco(){
    return numeroDisco; 
}

void Disco::setPosX(int PosX_){
    PosX = PosX_; 
}

void Disco::setPosY(int PosY_){
    PosY = PosY_; 
}

void Disco::setNDisco(int ndisco_){
    numeroDisco = ndisco_;  
}

Disco::~Disco()
{
}
