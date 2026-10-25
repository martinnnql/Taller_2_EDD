#pragma once
#include <string>
#include "Cola.h"
using namespace std;

// Lee el archivo de pacientes y valida cada linea
class CargadorPacientes {
private:
    static bool procesarLinea(const string& linea, Paciente*& paciente, string& motivo);
    static bool tipoDolorValido(const string& tipo);

public:
    // Devuelve la cantidad de pacientes cargados
    static int cargar(const string& nombreArchivo, Cola& cola);
};
