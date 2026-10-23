#pragma once
#include <string>
#include "NodoAVL.h"
using namespace std;

// Arbol AVL de pacientes ordenado por ID. 
class ArbolAVL {
private:
    NodoAVL* raiz;
    int cantidad;
    string registroRotaciones;   // rotaciones hechas durante la ultima operacion

    ArbolAVL(const ArbolAVL&);            
    ArbolAVL& operator=(const ArbolAVL&);

    int alturaNodo(NodoAVL* nodo) const;
    int factorBalanceNodo(NodoAVL* nodo) const;
    void actualizarAltura(NodoAVL* nodo);

    NodoAVL* rotacionSimpleDerecha(NodoAVL* nodo);
    NodoAVL* rotacionSimpleIzquierda(NodoAVL* nodo);
    NodoAVL* rotacionDobleIzquierdaDerecha(NodoAVL* nodo);
    NodoAVL* rotacionDobleDerechaIzquierda(NodoAVL* nodo);
    NodoAVL* balancear(NodoAVL* nodo);

    NodoAVL* insertarRec(NodoAVL* nodo, Paciente* paciente, bool& insertado);
    NodoAVL* eliminarRec(NodoAVL* nodo, int clave, bool& eliminado);
    NodoAVL* extraerMinimo(NodoAVL* nodo, NodoAVL*& minimo);
    void destruir(NodoAVL* nodo);

    void inordenRec(NodoAVL* nodo, int& contador) const;
    void preordenRec(NodoAVL* nodo, int& contador) const;
    void postordenRec(NodoAVL* nodo, int& contador) const;
    void balanceRec(NodoAVL* nodo) const;
    void listaRec(NodoAVL* nodo, string& salida) const;
    int validarRec(NodoAVL* nodo, int minimo, int maximo, bool& valido) const;
    void buscarNombreRec(NodoAVL* nodo, const string& buscado, Paciente** salida,
                         int maximo, int& encontrados) const;

public:
    ArbolAVL();
    ~ArbolAVL();

    bool estaVacio() const;
    int getCantidad() const;

    bool insertar(Paciente* paciente);    // false si el ID ya existe
    bool eliminar(int clave);             // libera el paciente eliminado
    Paciente* buscar(int clave, string& ruta) const;
    int buscarPorNombre(const string& nombre, Paciente** salida, int maximo) const;

    int altura() const;
    void mostrarInorden() const;
    void mostrarPreorden() const;
    void mostrarPostorden() const;
    void mostrarAlturaYBalance() const;
    string listaInorden() const;         
    // Comprueba orden por ID, alturas guardadas y balance de todos los nodos
    bool esAVLValido() const;

    string tomarRegistroRotaciones();     
};
