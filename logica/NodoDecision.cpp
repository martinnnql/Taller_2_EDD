#include "NodoDecision.h"
#include <sstream>

NodoDecision::NodoDecision(const string& servicio) {
    this->hoja = true;
    this->servicio = servicio;
    this->atributo = ATR_EDAD;
    this->operador = OP_IGUAL;
    this->valorNumerico = 0;
    this->comparaTexto = false;
    this->si = nullptr;
    this->no = nullptr;
}

NodoDecision::NodoDecision(Atributo atributo, Operador operador, double valor) {
    this->hoja = false;
    this->servicio = "";
    this->atributo = atributo;
    this->operador = operador;
    this->valorNumerico = valor;
    this->comparaTexto = false;
    this->si = nullptr;
    this->no = nullptr;
}

NodoDecision::NodoDecision(Atributo atributo, Operador operador, const string& valor) {
    this->hoja = false;
    this->servicio = "";
    this->atributo = atributo;
    this->operador = operador;
    this->valorNumerico = 0;
    this->valorTexto = valor;
    this->comparaTexto = true;
    this->si = nullptr;
    this->no = nullptr;
}

NodoDecision::~NodoDecision() {}

bool NodoDecision::esHoja() const { return this->hoja; }
string NodoDecision::getServicio() const { return this->servicio; }
NodoDecision* NodoDecision::getSi() const { return this->si; }
NodoDecision* NodoDecision::getNo() const { return this->no; }
void NodoDecision::setSi(NodoDecision* nodo) { this->si = nodo; }
void NodoDecision::setNo(NodoDecision* nodo) { this->no = nodo; }

string NodoDecision::nombreAtributo(Atributo atributo) {
    switch (atributo) {
        case ATR_EDAD: return "Edad";
        case ATR_TEMPERATURA: return "Temperatura";
        case ATR_PRESION: return "PresionArterial";
        case ATR_DOLOR: return "Dolor";
        case ATR_TIPO_DOLOR: return "TipoDolor";
        case ATR_TRAUMA: return "Trauma";
        case ATR_SINTOMAS_NEURO: return "SintomasNeurologicos";
        case ATR_REQUIERE_CIRUGIA: return "RequiereCirugia";
        case ATR_DIAS_HOSPITALIZACION: return "DiasHospitalizacion";
    }
    return "?";
}

string NodoDecision::simboloOperador(Operador operador) {
    switch (operador) {
        case OP_MENOR: return "<";
        case OP_MENOR_IGUAL: return "<=";
        case OP_MAYOR: return ">";
        case OP_MAYOR_IGUAL: return ">=";
        case OP_IGUAL: return "==";
        case OP_DISTINTO: return "!=";
    }
    return "?";
}

Operador NodoDecision::negarOperador(Operador operador) {
    switch (operador) {
        case OP_MENOR: return OP_MAYOR_IGUAL;
        case OP_MENOR_IGUAL: return OP_MAYOR;
        case OP_MAYOR: return OP_MENOR_IGUAL;
        case OP_MAYOR_IGUAL: return OP_MENOR;
        case OP_IGUAL: return OP_DISTINTO;
        case OP_DISTINTO: return OP_IGUAL;
    }
    return operador;
}

double NodoDecision::valorDelPaciente(const Paciente& p) const {
    switch (this->atributo) {
        case ATR_EDAD: return p.getEdad();
        case ATR_TEMPERATURA: return p.getTemperatura();
        case ATR_PRESION: return p.getPresionArterial();
        case ATR_DOLOR: return p.getDolor();
        case ATR_TRAUMA: return p.getTrauma() ? 1 : 0;
        case ATR_SINTOMAS_NEURO: return p.getSintomasNeurologicos() ? 1 : 0;
        case ATR_REQUIERE_CIRUGIA: return p.getRequiereCirugia() ? 1 : 0;
        case ATR_DIAS_HOSPITALIZACION: return p.getDiasHospitalizacion();
        case ATR_TIPO_DOLOR: return 0;
    }
    return 0;
}

bool NodoDecision::cumpleCondicion(const Paciente& paciente) const {
    if (this->comparaTexto) {
        string actual = paciente.getTipoDolor();
        if (this->operador == OP_IGUAL) return actual == this->valorTexto;
        if (this->operador == OP_DISTINTO) return actual != this->valorTexto;
        return false;
    }

    double actual = this->valorDelPaciente(paciente);
    switch (this->operador) {
        case OP_MENOR: return actual < this->valorNumerico;
        case OP_MENOR_IGUAL: return actual <= this->valorNumerico;
        case OP_MAYOR: return actual > this->valorNumerico;
        case OP_MAYOR_IGUAL: return actual >= this->valorNumerico;
        case OP_IGUAL: return actual == this->valorNumerico;
        case OP_DISTINTO: return actual != this->valorNumerico;
    }
    return false;
}

string NodoDecision::descripcionCondicion(bool respuesta) const {
    Operador op = this->operador;
    double valor = this->valorNumerico;
    if (!respuesta) {
        if (!this->comparaTexto && op == OP_IGUAL && (valor == 0 || valor == 1)) {
            valor = 1 - valor;
        } else {
            op = negarOperador(op);
        }
    }

    ostringstream salida;
    salida << nombreAtributo(this->atributo) << " " << simboloOperador(op) << " ";
    if (this->comparaTexto) salida << this->valorTexto;
    else salida << valor;
    return salida.str();
}

string NodoDecision::etiqueta() const {
    if (this->hoja) return "[Servicio] " + this->servicio;
    return "[Pregunta] " + this->descripcionCondicion(true) + "?";
}
