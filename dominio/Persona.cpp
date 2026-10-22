#include "Persona.h"

Persona::Persona(string nombre, int edad) {
    this->nombre = nombre;
    this->edad = edad;
}

Persona::~Persona() {}

string Persona::getNombre() const { return this->nombre; }
int Persona::getEdad() const { return this->edad; }

string Persona::resumen() const {
    return this->nombre + " (" + to_string(this->edad) + ")";
}
