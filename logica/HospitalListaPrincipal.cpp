#include "HospitalListaPrincipal.h"
#include <iostream>

//Servicios
static const char* const SERVICIOS[] = {
    "Urgencias", "Medicina General", "Cardiologia", "Neurologia",
    "Traumatologia", "Cirugia", "Pediatria", "Hospitalizacion"
};
static const int NUM_SERVICIOS = 8;

HospitalListaPrincipal::HospitalListaPrincipal() {
    this->inicioServicios = nullptr;
    this->finalServicios = nullptr;

    // Se recorre la tabla de nombres con aritmetica de punteros.
    for (const char* const* p = SERVICIOS; p < SERVICIOS + NUM_SERVICIOS; ++p) {
        NodoServicio* nuevo = new NodoServicio(*p);
        if (this->inicioServicios == nullptr) {
            this->inicioServicios = nuevo;
        } else {
            this->finalServicios->setSiguienteServicio(nuevo);
        }
        this->finalServicios = nuevo;
    }
}

HospitalListaPrincipal::~HospitalListaPrincipal() {
    NodoServicio* cursor = this->inicioServicios;
    while (cursor != nullptr) {
        NodoServicio* aBorrar = cursor;
        cursor = cursor->getSiguienteServicio();
        delete aBorrar;   
    }
}

NodoServicio* HospitalListaPrincipal::getServicio(const string& nombre) const {
    NodoServicio* cursor = this->inicioServicios;
    while (cursor != nullptr) {
        if (cursor->getNombre() == nombre) return cursor;
        cursor = cursor->getSiguienteServicio();
    }
    return nullptr;
}

NodoServicio* HospitalListaPrincipal::getServicioPorPosicion(int posicion) const {
    if (posicion < 1) return nullptr;
    NodoServicio* cursor = this->inicioServicios;
    int actual = 1;
    while (cursor != nullptr && actual < posicion) {
        cursor = cursor->getSiguienteServicio();
        actual++;
    }
    return cursor;
}

Paciente* HospitalListaPrincipal::buscarPorId(int id, string& ruta) const {
    NodoServicio* cursor = this->inicioServicios;
    while (cursor != nullptr) {
        Paciente* encontrado = cursor->getArbol()->buscar(id, ruta);
        if (encontrado != nullptr) return encontrado;
        cursor = cursor->getSiguienteServicio();
    }
    ruta = "";
    return nullptr;
}

bool HospitalListaPrincipal::existeId(int id) const {
    string ruta;
    return this->buscarPorId(id, ruta) != nullptr;
}

int HospitalListaPrincipal::buscarPorNombre(const string& nombre, Paciente** salida, int maximo) const {
    int total = 0;
    NodoServicio* cursor = this->inicioServicios;
    while (cursor != nullptr && total < maximo) {
        // avanza el puntero hasta la primera posicion libre del arreglo
        total += cursor->getArbol()->buscarPorNombre(nombre, salida + total, maximo - total);
        cursor = cursor->getSiguienteServicio();
    }
    return total;
}

ResultadoDerivacion HospitalListaPrincipal::derivarPaciente(const string& nombreServicio,
                                                            Paciente* paciente, string& rotaciones) {
    rotaciones = "";
    NodoServicio* servicio = this->getServicio(nombreServicio);
    if (servicio == nullptr) return DERIVACION_SERVICIO_INEXISTENTE;
    if (this->existeId(paciente->getId())) return DERIVACION_ID_DUPLICADO;

    if (!servicio->getArbol()->insertar(paciente)) return DERIVACION_ID_DUPLICADO;
    rotaciones = servicio->getArbol()->tomarRegistroRotaciones();
    return DERIVACION_OK;
}

void HospitalListaPrincipal::mostrarEstado() const {
    cout << "=== ESTADO DE LOS DEPARTAMENTOS ===\n";
    NodoServicio* cursor = this->inicioServicios;
    int numero = 1;
    while (cursor != nullptr) {
        cout << numero << ". " << cursor->getNombre() << "\n";
        ArbolAVL* arbol = cursor->getArbol();
        if (arbol->estaVacio()) {
            cout << "   Sin pacientes\n";
        } else {
            cout << "   Pacientes (" << arbol->getCantidad() << "): " << arbol->listaInorden() << "\n";
        }
        cursor = cursor->getSiguienteServicio();
        numero++;
    }
}
