#include "ArbolDecision.h"
#include <iostream>

static NodoDecision* hoja(const string& servicio) {
    return new NodoDecision(servicio);
}

static NodoDecision* pregunta(Atributo atributo, Operador operador, double valor,
                              NodoDecision* si, NodoDecision* no) {
    NodoDecision* nodo = new NodoDecision(atributo, operador, valor);
    nodo->setSi(si);
    nodo->setNo(no);
    return nodo;
}

static NodoDecision* preguntaTexto(Atributo atributo, Operador operador, const string& valor,
                                   NodoDecision* si, NodoDecision* no) {
    NodoDecision* nodo = new NodoDecision(atributo, operador, valor);
    nodo->setSi(si);
    nodo->setNo(no);
    return nodo;
}

ArbolDecision::ArbolDecision() {
    this->raiz = nullptr;
    this->construir();
}

ArbolDecision::~ArbolDecision() {
    this->destruir(this->raiz);
}

void ArbolDecision::destruir(NodoDecision* nodo) {
    if (nodo == nullptr) return;
    this->destruir(nodo->getSi());
    this->destruir(nodo->getNo());
    delete nodo;
}

// criterio para evaluar
void ArbolDecision::construir() {
    this->raiz =
        pregunta(ATR_DOLOR, OP_MAYOR_IGUAL, 9, hoja("Urgencias"),
        pregunta(ATR_PRESION, OP_MAYOR_IGUAL, 180, hoja("Urgencias"),
        pregunta(ATR_EDAD, OP_MENOR, 14, hoja("Pediatria"),
        pregunta(ATR_TRAUMA, OP_IGUAL, 1,
            pregunta(ATR_REQUIERE_CIRUGIA, OP_IGUAL, 1, hoja("Cirugia"), hoja("Traumatologia")),
        pregunta(ATR_SINTOMAS_NEURO, OP_IGUAL, 1, hoja("Neurologia"),
        preguntaTexto(ATR_TIPO_DOLOR, OP_IGUAL, "pecho", hoja("Cardiologia"),
        pregunta(ATR_REQUIERE_CIRUGIA, OP_IGUAL, 1, hoja("Cirugia"),
        pregunta(ATR_TEMPERATURA, OP_MAYOR_IGUAL, 38.5, hoja("Urgencias"),
        pregunta(ATR_DIAS_HOSPITALIZACION, OP_MAYOR_IGUAL, 2,
            hoja("Hospitalizacion"), hoja("Medicina General"))))))))));
}

string ArbolDecision::evaluar(const Paciente& paciente, string& ruta) const {
    ruta = "";
    if (this->raiz == nullptr) {
        ruta = "Arbol vacio (datos insuficientes)";
        return "Urgencias";
    }

    NodoDecision* actual = this->raiz;
    while (!actual->esHoja()) {
        bool respuesta = actual->cumpleCondicion(paciente);
        if (!ruta.empty()) ruta += " -> ";
        ruta += actual->descripcionCondicion(respuesta);
        actual = respuesta ? actual->getSi() : actual->getNo();
    }
    return actual->getServicio();
}

void ArbolDecision::preordenRec(NodoDecision* nodo, int& contador) const {
    if (nodo == nullptr) return;
    contador++;
    cout << contador << ". " << nodo->etiqueta() << "\n";
    this->preordenRec(nodo->getSi(), contador);
    this->preordenRec(nodo->getNo(), contador);
}

void ArbolDecision::inordenRec(NodoDecision* nodo, int& contador) const {
    if (nodo == nullptr) return;
    this->inordenRec(nodo->getSi(), contador);
    contador++;
    cout << contador << ". " << nodo->etiqueta() << "\n";
    this->inordenRec(nodo->getNo(), contador);
}

void ArbolDecision::postordenRec(NodoDecision* nodo, int& contador) const {
    if (nodo == nullptr) return;
    this->postordenRec(nodo->getSi(), contador);
    this->postordenRec(nodo->getNo(), contador);
    contador++;
    cout << contador << ". " << nodo->etiqueta() << "\n";
}

void ArbolDecision::estructuraRec(NodoDecision* nodo, const string& sangria, const string& rama) const {
    if (nodo == nullptr) return;
    cout << sangria << rama << ": ";
    if (nodo->esHoja()) {
        cout << nodo->getServicio() << "\n";
        return;
    }
    cout << nodo->descripcionCondicion(true) << "?\n";
    this->estructuraRec(nodo->getSi(), sangria + "   ", "Si");
    this->estructuraRec(nodo->getNo(), sangria + "   ", "No");
}

int ArbolDecision::contarHojasRec(NodoDecision* nodo) const {
    if (nodo == nullptr) return 0;
    if (nodo->esHoja()) return 1;
    return this->contarHojasRec(nodo->getSi()) + this->contarHojasRec(nodo->getNo());
}

void ArbolDecision::mostrarEstructura() const {
    cout << "=== ESTRUCTURA DEL ARBOL DE DECISION ===\n";
    this->estructuraRec(this->raiz, "", "Raiz");
}

void ArbolDecision::mostrarPreorden() const {
    cout << "=== RECORRIDO PREORDEN (nodo, Si, No) ===\n";
    int contador = 0;
    this->preordenRec(this->raiz, contador);
}

void ArbolDecision::mostrarInorden() const {
    cout << "=== RECORRIDO INORDEN (Si, nodo, No) ===\n";
    int contador = 0;
    this->inordenRec(this->raiz, contador);
}

void ArbolDecision::mostrarPostorden() const {
    cout << "=== RECORRIDO POSTORDEN (Si, No, nodo) ===\n";
    int contador = 0;
    this->postordenRec(this->raiz, contador);
}

int ArbolDecision::contarHojas() const {
    return this->contarHojasRec(this->raiz);
}
