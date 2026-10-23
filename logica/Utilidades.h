#pragma once
#include <string>
using namespace std;

// Funciones auxiliares de texto y conversion
string aMinusculas(const string& texto);
string recortar(const string& texto);                 // quita espacios, tabs y \r de los extremos
bool parsearEntero(const string& texto, int& valor);  
bool parsearDecimal(const string& texto, double& valor); 
