#pragma once
#include <string>
#include "NodoServicio.h"
using namespace std;

enum ResultadoDerivacion {
    DERIVACION_OK,
    DERIVACION_SERVICIO_INEXISTENTE,
    DERIVACION_ID_DUPLICADO
};

// Lista enlazada de servicios
class HospitalListaPrincipal {
private:
    NodoServicio* inicioServicios; //Head
    NodoServicio* finalServicios;  // Tail

    HospitalListaPrincipal(const HospitalListaPrincipal&);            
    HospitalListaPrincipal& operator=(const HospitalListaPrincipal&);

public:
    HospitalListaPrincipal();
    ~HospitalListaPrincipal();

    NodoServicio* getServicio(const string& nombre) const;
    NodoServicio* getServicioPorPosicion(int posicion) const;   // 1 = primer servicio

    bool existeId(int id) const;
    ResultadoDerivacion derivarPaciente(const string& nombreServicio, Paciente* paciente, string& rotaciones);

    void mostrarEstado() const;
    Paciente* buscarPorId(int id, string& ruta) const;
    int buscarPorNombre(const string& nombre, Paciente** salida, int maximo) const;
};
