#pragma once
#include <string>
#include "NodoDecision.h"
using namespace std;

// Arbol de decision para clasificar pacientes en servicios
// hijo izquierdo = rama "Si", derecho = "No"
class ArbolDecision {
private:
    NodoDecision* raiz;

    ArbolDecision(const ArbolDecision&);             
    ArbolDecision& operator=(const ArbolDecision&);

    void construir();
    void destruir(NodoDecision* nodo);
    void preordenRec(NodoDecision* nodo, int& contador) const;
    void inordenRec(NodoDecision* nodo, int& contador) const;
    void postordenRec(NodoDecision* nodo, int& contador) const;
    void estructuraRec(NodoDecision* nodo, const string& sangria, const string& rama) const;
    int contarHojasRec(NodoDecision* nodo) const;

public:
    ArbolDecision();
    ~ArbolDecision();

    // Devuelve el servicio y deja en "ruta" las condiciones cumplidas.
    string evaluar(const Paciente& paciente, string& ruta) const;

    void mostrarEstructura() const;
    void mostrarPreorden() const;
    void mostrarInorden() const;
    void mostrarPostorden() const;
    int contarHojas() const;
};
