#include "ArbolAVL.h"
#include "Utilidades.h"
#include <iostream>

ArbolAVL::ArbolAVL() {
    this->raiz = nullptr;
    this->cantidad = 0;
}

ArbolAVL::~ArbolAVL() {
    this->destruir(this->raiz);
}

void ArbolAVL::destruir(NodoAVL* nodo) {
    if (nodo == nullptr) return;
    this->destruir(nodo->getIzq());
    this->destruir(nodo->getDer());
    delete nodo->getPaciente();
    delete nodo;
}

bool ArbolAVL::estaVacio() const { return this->raiz == nullptr; }
int ArbolAVL::getCantidad() const { return this->cantidad; }

// altura y factor de balance 

int ArbolAVL::alturaNodo(NodoAVL* nodo) const {
    return (nodo == nullptr) ? 0 : nodo->getAltura();
}

// Factor de balance = altura(izquierdo) - altura(derecho) NO OLVIDAR YA
int ArbolAVL::factorBalanceNodo(NodoAVL* nodo) const {
    if (nodo == nullptr) return 0;
    return this->alturaNodo(nodo->getIzq()) - this->alturaNodo(nodo->getDer());
}

void ArbolAVL::actualizarAltura(NodoAVL* nodo) {
    int hi = this->alturaNodo(nodo->getIzq());
    int hd = this->alturaNodo(nodo->getDer());
    nodo->setAltura(1 + (hi > hd ? hi : hd));
}

int ArbolAVL::altura() const {
    return this->alturaNodo(this->raiz);
}

// rotaciones

// Caso izquierda-izquierda
NodoAVL* ArbolAVL::rotacionSimpleDerecha(NodoAVL* nodo) {
    NodoAVL* nuevaRaiz = nodo->getIzq();
    NodoAVL* subarbol = nuevaRaiz->getDer();

    nuevaRaiz->setDer(nodo);
    nodo->setIzq(subarbol);

    this->actualizarAltura(nodo);
    this->actualizarAltura(nuevaRaiz);
    return nuevaRaiz;
}

// Caso el hijo derecho pasa a ser la raiz del subarbol
NodoAVL* ArbolAVL::rotacionSimpleIzquierda(NodoAVL* nodo) {
    NodoAVL* nuevaRaiz = nodo->getDer();
    NodoAVL* subarbol = nuevaRaiz->getIzq();

    nuevaRaiz->setIzq(nodo);
    nodo->setDer(subarbol);

    this->actualizarAltura(nodo);
    this->actualizarAltura(nuevaRaiz);
    return nuevaRaiz;
}

// Caso primero izquierda sobre el hijo izquierdo, luego derecha
NodoAVL* ArbolAVL::rotacionDobleIzquierdaDerecha(NodoAVL* nodo) {
    nodo->setIzq(this->rotacionSimpleIzquierda(nodo->getIzq()));
    return this->rotacionSimpleDerecha(nodo);
}

// Caso primero derecha sobre el hijo derecho, luego izquierda
NodoAVL* ArbolAVL::rotacionDobleDerechaIzquierda(NodoAVL* nodo) {
    nodo->setDer(this->rotacionSimpleDerecha(nodo->getDer()));
    return this->rotacionSimpleIzquierda(nodo);
}

NodoAVL* ArbolAVL::balancear(NodoAVL* nodo) {
    this->actualizarAltura(nodo);
    int fb = this->factorBalanceNodo(nodo);
    string idNodo = nodo->getPaciente()->getIdTexto();

    if (fb > 1) {
        if (this->factorBalanceNodo(nodo->getIzq()) >= 0) {
            this->registroRotaciones += "Rotacion simple derecha en el nodo " + idNodo + "\n";
            return this->rotacionSimpleDerecha(nodo);
        }
        this->registroRotaciones += "Rotacion doble izquierda-derecha en el nodo " + idNodo + "\n";
        return this->rotacionDobleIzquierdaDerecha(nodo);
    }
    if (fb < -1) {
        if (this->factorBalanceNodo(nodo->getDer()) <= 0) {
            this->registroRotaciones += "Rotacion simple izquierda en el nodo " + idNodo + "\n";
            return this->rotacionSimpleIzquierda(nodo);
        }
        this->registroRotaciones += "Rotacion doble derecha-izquierda en el nodo " + idNodo + "\n";
        return this->rotacionDobleDerechaIzquierda(nodo);
    }
    return nodo;
}

string ArbolAVL::tomarRegistroRotaciones() {
    string registro = this->registroRotaciones;
    this->registroRotaciones = "";
    return registro;
}

// insertar nodo

NodoAVL* ArbolAVL::insertarRec(NodoAVL* nodo, Paciente* paciente, bool& insertado) {
    if (nodo == nullptr) {
        insertado = true;
        return new NodoAVL(paciente);
    }

    if (paciente->getId() < nodo->getClave()) {
        nodo->setIzq(this->insertarRec(nodo->getIzq(), paciente, insertado));
    } else if (paciente->getId() > nodo->getClave()) {
        nodo->setDer(this->insertarRec(nodo->getDer(), paciente, insertado));
    } else {
        insertado = false;   // ID repetido
        return nodo;
    }
    return this->balancear(nodo);
}

bool ArbolAVL::insertar(Paciente* paciente) {
    if (paciente == nullptr) return false;
    this->registroRotaciones = "";
    bool insertado = false;
    this->raiz = this->insertarRec(this->raiz, paciente, insertado);
    if (insertado) this->cantidad++;
    return insertado;
}

// eliminar nodo

NodoAVL* ArbolAVL::extraerMinimo(NodoAVL* nodo, NodoAVL*& minimo) {
    if (nodo->getIzq() == nullptr) {
        minimo = nodo;
        return nodo->getDer();
    }
    nodo->setIzq(this->extraerMinimo(nodo->getIzq(), minimo));
    return this->balancear(nodo);
}

NodoAVL* ArbolAVL::eliminarRec(NodoAVL* nodo, int clave, bool& eliminado) {
    if (nodo == nullptr) return nullptr;

    if (clave < nodo->getClave()) {
        nodo->setIzq(this->eliminarRec(nodo->getIzq(), clave, eliminado));
    } else if (clave > nodo->getClave()) {
        nodo->setDer(this->eliminarRec(nodo->getDer(), clave, eliminado));
    } else {
        eliminado = true;
        NodoAVL* izq = nodo->getIzq();
        NodoAVL* der = nodo->getDer();

        if (izq == nullptr || der == nullptr) {
            NodoAVL* hijo = (izq != nullptr) ? izq : der;
            delete nodo->getPaciente();
            delete nodo;
            return hijo;
        }

        NodoAVL* sucesor = nullptr;
        NodoAVL* nuevaDer = this->extraerMinimo(der, sucesor);
        sucesor->setIzq(izq);
        sucesor->setDer(nuevaDer);
        delete nodo->getPaciente();
        delete nodo;
        nodo = sucesor;
    }
    return this->balancear(nodo);
}

bool ArbolAVL::eliminar(int clave) {
    this->registroRotaciones = "";
    bool eliminado = false;
    this->raiz = this->eliminarRec(this->raiz, clave, eliminado);
    if (eliminado) this->cantidad--;
    return eliminado;
}

// buscar nodo

Paciente* ArbolAVL::buscar(int clave, string& ruta) const {
    ruta = "";
    NodoAVL* actual = this->raiz;
    while (actual != nullptr) {
        if (!ruta.empty()) ruta += " -> ";
        ruta += actual->getPaciente()->getIdTexto();

        if (clave == actual->getClave()) return actual->getPaciente();
        actual = (clave < actual->getClave()) ? actual->getIzq() : actual->getDer();
    }
    return nullptr;
}

void ArbolAVL::buscarNombreRec(NodoAVL* nodo, const string& buscado, Paciente** salida,
                               int maximo, int& encontrados) const {
    if (nodo == nullptr) return;
    this->buscarNombreRec(nodo->getIzq(), buscado, salida, maximo, encontrados);
    if (encontrados < maximo && aMinusculas(nodo->getPaciente()->getNombre()) == buscado) {
        *(salida + encontrados) = nodo->getPaciente();   // aritmetica de punteros
        encontrados++;
    }
    this->buscarNombreRec(nodo->getDer(), buscado, salida, maximo, encontrados);
}

int ArbolAVL::buscarPorNombre(const string& nombre, Paciente** salida, int maximo) const {
    int encontrados = 0;
    this->buscarNombreRec(this->raiz, aMinusculas(nombre), salida, maximo, encontrados);
    return encontrados;
}

// recorridos y consultas

void ArbolAVL::inordenRec(NodoAVL* nodo, int& contador) const {
    if (nodo == nullptr) return;
    this->inordenRec(nodo->getIzq(), contador);
    contador++;
    cout << contador << ". " << nodo->getPaciente()->getIdTexto() << " - "
         << nodo->getPaciente()->getNombre() << " (" << nodo->getPaciente()->getEdad() << ")\n";
    this->inordenRec(nodo->getDer(), contador);
}

void ArbolAVL::preordenRec(NodoAVL* nodo, int& contador) const {
    if (nodo == nullptr) return;
    contador++;
    cout << contador << ". " << nodo->getPaciente()->getIdTexto() << " - "
         << nodo->getPaciente()->getNombre() << " (" << nodo->getPaciente()->getEdad() << ")\n";
    this->preordenRec(nodo->getIzq(), contador);
    this->preordenRec(nodo->getDer(), contador);
}

void ArbolAVL::postordenRec(NodoAVL* nodo, int& contador) const {
    if (nodo == nullptr) return;
    this->postordenRec(nodo->getIzq(), contador);
    this->postordenRec(nodo->getDer(), contador);
    contador++;
    cout << contador << ". " << nodo->getPaciente()->getIdTexto() << " - "
         << nodo->getPaciente()->getNombre() << " (" << nodo->getPaciente()->getEdad() << ")\n";
}

void ArbolAVL::balanceRec(NodoAVL* nodo) const {
    if (nodo == nullptr) return;
    this->balanceRec(nodo->getIzq());
    cout << "ID " << nodo->getPaciente()->getIdTexto()
         << " | altura: " << nodo->getAltura()
         << " | factor de balance: " << this->factorBalanceNodo(nodo) << "\n";
    this->balanceRec(nodo->getDer());
}

void ArbolAVL::listaRec(NodoAVL* nodo, string& salida) const {
    if (nodo == nullptr) return;
    this->listaRec(nodo->getIzq(), salida);
    if (!salida.empty()) salida += ", ";
    salida += nodo->getPaciente()->resumen();
    this->listaRec(nodo->getDer(), salida);
}

void ArbolAVL::mostrarInorden() const {
    if (this->estaVacio()) { cout << "Sin pacientes.\n"; return; }
    int contador = 0;
    this->inordenRec(this->raiz, contador);
}

void ArbolAVL::mostrarPreorden() const {
    if (this->estaVacio()) { cout << "Sin pacientes.\n"; return; }
    int contador = 0;
    this->preordenRec(this->raiz, contador);
}

void ArbolAVL::mostrarPostorden() const {
    if (this->estaVacio()) { cout << "Sin pacientes.\n"; return; }
    int contador = 0;
    this->postordenRec(this->raiz, contador);
}

void ArbolAVL::mostrarAlturaYBalance() const {
    if (this->estaVacio()) { cout << "Sin pacientes (altura 0).\n"; return; }
    cout << "Altura del arbol: " << this->altura() << "\n";
    cout << "Factor de balance por nodo (inorden):\n";
    this->balanceRec(this->raiz);
}

string ArbolAVL::listaInorden() const {
    string salida = "";
    this->listaRec(this->raiz, salida);
    return salida;
}

// Devuelve la altura real del subarbol y marca valido=false si algo se rompe
int ArbolAVL::validarRec(NodoAVL* nodo, int minimo, int maximo, bool& valido) const {
    if (nodo == nullptr) return 0;
    if (nodo->getClave() <= minimo || nodo->getClave() >= maximo) valido = false;
    int hi = this->validarRec(nodo->getIzq(), minimo, nodo->getClave(), valido);
    int hd = this->validarRec(nodo->getDer(), nodo->getClave(), maximo, valido);
    int fb = hi - hd;
    if (fb < -1 || fb > 1) valido = false;
    int real = 1 + (hi > hd ? hi : hd);
    if (nodo->getAltura() != real) valido = false;
    return real;
}

bool ArbolAVL::esAVLValido() const {
    bool valido = true;
    this->validarRec(this->raiz, -2147483647 - 1, 2147483647, valido);
    return valido;
}
