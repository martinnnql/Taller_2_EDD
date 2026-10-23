#include "NodoAVL.h"

NodoAVL::NodoAVL(Paciente* paciente) {
    this->paciente = paciente;
    this->clave = paciente->getId();
    this->altura = 1;
    this->izq = nullptr;
    this->der = nullptr;
}

NodoAVL::~NodoAVL() {}

Paciente* NodoAVL::getPaciente() const { return this->paciente; }
int NodoAVL::getClave() const { return this->clave; }
int NodoAVL::getAltura() const { return this->altura; }
NodoAVL* NodoAVL::getIzq() const { return this->izq; }
NodoAVL* NodoAVL::getDer() const { return this->der; }
void NodoAVL::setAltura(int altura) { this->altura = altura; }
void NodoAVL::setIzq(NodoAVL* nodo) { this->izq = nodo; }
void NodoAVL::setDer(NodoAVL* nodo) { this->der = nodo; }
