#pragma once
#include "../dominio/Paciente.h"

class NodoAVL {
private:
    Paciente* paciente;
    int clave;
    int altura;
    NodoAVL* izq;
    NodoAVL* der;

public:
    NodoAVL(Paciente* paciente);
    ~NodoAVL();

    Paciente* getPaciente() const;
    int getClave() const;
    int getAltura() const;
    NodoAVL* getIzq() const;
    NodoAVL* getDer() const;
    void setAltura(int altura);
    void setIzq(NodoAVL* nodo);
    void setDer(NodoAVL* nodo);
};
