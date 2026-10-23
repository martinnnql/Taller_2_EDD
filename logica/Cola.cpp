#include "Cola.h"

Cola::Cola() {
    this->frente = nullptr;
    this->final = nullptr;
    this->tamano = 0;
}

Cola::~Cola() {
    while (!this->estaVacia()) {
        Paciente* p = this->desencolar();
        delete p;
    }
}

bool Cola::estaVacia() const {
    return this->frente == nullptr;
}

int Cola::getTamano() const {
    return this->tamano;
}

void Cola::encolar(Paciente* paciente) {
    Nodo* nuevoNodo = new Nodo(paciente);
    if (this->estaVacia()) {
        this->frente = nuevoNodo;
        this->final = nuevoNodo;
    } else {
        this->final->setSiguiente(nuevoNodo);
        this->final = nuevoNodo;
    }
    this->tamano++;
}

Paciente* Cola::desencolar() {
    if (this->estaVacia()) return nullptr;

    Nodo* nodoAtendido = this->frente;
    Paciente* pacienteAtendido = nodoAtendido->getPaciente();

    this->frente = this->frente->getSiguiente();
    if (this->frente == nullptr) {
        this->final = nullptr;
    }

    delete nodoAtendido;
    this->tamano--;
    return pacienteAtendido;
}

bool Cola::contieneId(int id) const {
    Nodo* cursor = this->frente;
    while (cursor != nullptr) {
        if (cursor->getPaciente()->getId() == id) return true;
        cursor = cursor->getSiguiente();
    }
    return false;
}

void Cola::mostrarCola() const {
    if (this->estaVacia()) {
        cout << "No hay pacientes en espera.\n";
        return;
    }
    Nodo* cursor = this->frente;
    int i = 1;
    cout << "=== PACIENTES EN ESPERA ===\n";
    while (cursor != nullptr) {
        cout << i << ". " << cursor->getPaciente()->getIdTexto() << " - "
             << cursor->getPaciente()->getNombre() << "\n";
        cursor = cursor->getSiguiente();
        i++;
    }
}
