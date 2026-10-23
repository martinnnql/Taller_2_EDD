#include "Utilidades.h"
#include <cstdlib>

string aMinusculas(const string& texto) {
    string resultado = texto;
    for (size_t i = 0; i < resultado.size(); i++) {
        char c = resultado[i];
        if (c >= 'A' && c <= 'Z') resultado[i] = c - 'A' + 'a';
    }
    return resultado;
}

string recortar(const string& texto) {
    const string espacios = " \t\r\n";
    size_t inicio = texto.find_first_not_of(espacios);
    if (inicio == string::npos) return "";
    size_t fin = texto.find_last_not_of(espacios);
    return texto.substr(inicio, fin - inicio + 1);
}

bool parsearEntero(const string& texto, int& valor) {
    if (texto.empty()) return false;
    size_t inicio = (texto[0] == '-') ? 1 : 0;
    size_t digitos = texto.size() - inicio;
    if (digitos == 0 || digitos > 9) return false;
    for (size_t i = inicio; i < texto.size(); i++) {
        if (texto[i] < '0' || texto[i] > '9') return false;
    }
    valor = atoi(texto.c_str());
    return true;
}

bool parsearDecimal(const string& texto, double& valor) {
    if (texto.empty()) return false;
    string limpio = texto;
    int puntos = 0;
    int digitos = 0;
    for (size_t i = 0; i < limpio.size(); i++) {
        char c = limpio[i];
        if (c == ',') { limpio[i] = '.'; c = '.'; }
        if (c == '.') { puntos++; }
        else if (c >= '0' && c <= '9') { digitos++; }
        else if (!(c == '-' && i == 0)) { return false; }
    }
    if (puntos > 1 || digitos == 0) return false;
    valor = atof(limpio.c_str());
    return true;
}
