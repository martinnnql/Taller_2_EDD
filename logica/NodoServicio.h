#pragma once
#include <string>
#include "ArbolAVL.h"
using namespace std;

// Nodo de la lista principal del hospital
class NodoServicio {
private:
    string nombreServicio;
    ArbolAVL* arbol;
    NodoServicio* siguienteServicio;

    NodoServicio(const NodoServicio&);            
    NodoServicio& operator=(const NodoServicio&);

public:
    NodoServicio(string nombre);
    ~NodoServicio();

    string getNombre() const;
    ArbolAVL* getArbol() const;
    NodoServicio* getSiguienteServicio() const;
    void setSiguienteServicio(NodoServicio* siguiente);
};
