#include "Nodo.h"

Nodo::Nodo(Paciente* paciente) {
    this->paciente = paciente;
    this->siguiente = nullptr;
}

Nodo::~Nodo() {}

Paciente* Nodo::getPaciente() const { return this->paciente; }
Nodo* Nodo::getSiguiente() const { return this->siguiente; }
void Nodo::setSiguiente(Nodo* siguiente) { this->siguiente = siguiente; }
