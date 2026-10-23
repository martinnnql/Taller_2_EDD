#include "NodoServicio.h"

NodoServicio::NodoServicio(string nombre) {
    this->nombreServicio = nombre;
    this->arbol = new ArbolAVL();
    this->siguienteServicio = nullptr;
}

NodoServicio::~NodoServicio() {
    delete this->arbol;   
}

string NodoServicio::getNombre() const { return this->nombreServicio; }
ArbolAVL* NodoServicio::getArbol() const { return this->arbol; }
NodoServicio* NodoServicio::getSiguienteServicio() const { return this->siguienteServicio; }
void NodoServicio::setSiguienteServicio(NodoServicio* siguiente) { this->siguienteServicio = siguiente; }
