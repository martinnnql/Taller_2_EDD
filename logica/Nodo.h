#pragma once
#include "../dominio/Paciente.h"

// Nodo de la cola de espera lista enlazada
class Nodo {
private:
    Paciente* paciente;
    Nodo* siguiente;

public:
    Nodo(Paciente* paciente);
    ~Nodo();

    Paciente* getPaciente() const;
    Nodo* getSiguiente() const;
    void setSiguiente(Nodo* siguiente);
};
