#pragma once
#include <string>
#include "../dominio/Paciente.h"
using namespace std;

enum Atributo {
    ATR_EDAD, ATR_TEMPERATURA, ATR_PRESION, ATR_DOLOR, ATR_TIPO_DOLOR,
    ATR_TRAUMA, ATR_SINTOMAS_NEURO, ATR_REQUIERE_CIRUGIA, ATR_DIAS_HOSPITALIZACION
};

enum Operador {
    OP_MENOR, OP_MENOR_IGUAL, OP_MAYOR, OP_MAYOR_IGUAL, OP_IGUAL, OP_DISTINTO
};

// Nodo del arbol de decision
class NodoDecision {
private:
    bool hoja;
    string servicio;
    Atributo atributo;
    Operador operador;
    double valorNumerico;
    string valorTexto;
    bool comparaTexto;
    NodoDecision* si;
    NodoDecision* no;

    static string nombreAtributo(Atributo atributo);
    static string simboloOperador(Operador operador);
    static Operador negarOperador(Operador operador);
    double valorDelPaciente(const Paciente& paciente) const;

public:
    explicit NodoDecision(const string& servicio);                        // hoja
    NodoDecision(Atributo atributo, Operador operador, double valor);     // pregunta numerica
    NodoDecision(Atributo atributo, Operador operador, const string& valor); // pregunta de texto
    ~NodoDecision();

    bool esHoja() const;
    string getServicio() const;
    NodoDecision* getSi() const;
    NodoDecision* getNo() const;
    void setSi(NodoDecision* nodo);
    void setNo(NodoDecision* nodo);

    bool cumpleCondicion(const Paciente& paciente) const;
    // Texto de la condicion si respuesta=true, o de su negacion si es false.
    string descripcionCondicion(bool respuesta) const;
    string etiqueta() const;
};
