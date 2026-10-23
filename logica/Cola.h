#pragma once
#include <iostream>
#include "Nodo.h"
using namespace std;

// Cola FIFO de pacientes en espera
class Cola {
private:
    Nodo* frente;
    Nodo* final;
    int tamano;

    Cola(const Cola&);             
    Cola& operator=(const Cola&);

public:
    Cola();
    ~Cola();

    bool estaVacia() const;
    int getTamano() const;
    void encolar(Paciente* paciente);
    Paciente* desencolar();
    bool contieneId(int id) const;
    void mostrarCola() const;
};
