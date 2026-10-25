#include "CargadorPacientes.h"
#include "Utilidades.h"
#include <fstream>
#include <iostream>

// Tipos de dolor permitidos
static const string TIPOS_DOLOR[] = { "pecho", "cabeza", "abdomen", "extremidad", "otro" };
static const int NUM_TIPOS_DOLOR = 5;

bool CargadorPacientes::tipoDolorValido(const string& tipo) {
    for (const string* p = TIPOS_DOLOR; p < TIPOS_DOLOR + NUM_TIPOS_DOLOR; ++p) {
        if (*p == tipo) return true;
    }
    return false;
}

// Convierte un campo "0"/"1" en booleano
static bool parsearBandera(const string& texto, bool& valor) {
    if (texto == "0") { valor = false; return true; }
    if (texto == "1") { valor = true; return true; }
    return false;
}

bool CargadorPacientes::procesarLinea(const string& linea, Paciente*& paciente, string& motivo) {
    const int NUM_CAMPOS = 11;
    string campos[NUM_CAMPOS + 1];

    
    int n = 0;
    size_t inicio = 0;
    bool fin = false;
    while (!fin) {
        size_t pos = linea.find(';', inicio);
        string campo;
        if (pos == string::npos) {
            campo = linea.substr(inicio);
            fin = true;
        } else {
            campo = linea.substr(inicio, pos - inicio);
            inicio = pos + 1;
        }
        if (n < NUM_CAMPOS + 1) campos[n] = recortar(campo);
        n++;
    }
    if (n != NUM_CAMPOS) {
        motivo = "se esperaban 11 campos y se encontraron " + to_string(n);
        return false;
    }

    int id = 0, edad = 0, presion = 0, dolor = 0, dias = 0;
    double temperatura = 0;
    bool trauma = false, neuro = false, cirugia = false;

    if (!parsearEntero(campos[0], id) || id <= 0) { motivo = "ID invalido (debe ser un numero positivo)"; return false; }
    if (campos[1].empty()) { motivo = "el nombre esta vacio"; return false; }
    if (!parsearEntero(campos[2], edad) || edad < 0 || edad > 120) { motivo = "edad invalida (0 a 120)"; return false; }
    if (!parsearDecimal(campos[3], temperatura) || temperatura < 30.0 || temperatura > 45.0) { motivo = "temperatura invalida (30.0 a 45.0)"; return false; }
    if (!parsearEntero(campos[4], presion) || presion < 40 || presion > 300) { motivo = "presion arterial invalida (40 a 300)"; return false; }
    if (!parsearEntero(campos[5], dolor) || dolor < 0 || dolor > 10) { motivo = "dolor invalido (0 a 10)"; return false; }

    string tipoDolor = aMinusculas(campos[6]);
    if (!tipoDolorValido(tipoDolor)) { motivo = "tipo de dolor invalido (pecho, cabeza, abdomen, extremidad u otro)"; return false; }

    if (!parsearBandera(campos[7], trauma)) { motivo = "Trauma debe ser 0 o 1"; return false; }
    if (!parsearBandera(campos[8], neuro)) { motivo = "SintomasNeurologicos debe ser 0 o 1"; return false; }
    if (!parsearBandera(campos[9], cirugia)) { motivo = "RequiereCirugia debe ser 0 o 1"; return false; }
    if (!parsearEntero(campos[10], dias) || dias < 0 || dias > 365) { motivo = "dias de hospitalizacion invalidos (0 a 365)"; return false; }

    paciente = new Paciente(id, campos[0], campos[1], edad, temperatura, presion, dolor,
                            tipoDolor, trauma, neuro, cirugia, dias);
    return true;
}

int CargadorPacientes::cargar(const string& nombreArchivo, Cola& cola) {
    ifstream archivo(nombreArchivo.c_str());
    if (!archivo.is_open()) {
        cout << "Error: no se pudo abrir el archivo '" << nombreArchivo << "'.\n";
        return -1;
    }

    string linea;
    int numeroLinea = 0;
    int cargados = 0;
    int rechazados = 0;

    while (getline(archivo, linea)) {
        numeroLinea++;
        string limpia = recortar(linea);
        if (limpia.empty() || limpia[0] == '#') continue;  

        Paciente* paciente = nullptr;
        string motivo;
        if (!procesarLinea(limpia, paciente, motivo)) {
            cout << "Linea " << numeroLinea << " rechazada: " << motivo << ".\n";
            rechazados++;
            continue;
        }
        if (cola.contieneId(paciente->getId())) {
            cout << "Linea " << numeroLinea << " rechazada: el ID " << paciente->getIdTexto()
                 << " esta duplicado.\n";
            delete paciente;
            rechazados++;
            continue;
        }

        cola.encolar(paciente);
        cargados++;
    }
    archivo.close();

    cout << "Archivo procesado: " << cargados << " paciente(s) cargado(s)";
    if (rechazados > 0) cout << ", " << rechazados << " linea(s) rechazada(s)";
    cout << ".\n\n";
    return cargados;
}
