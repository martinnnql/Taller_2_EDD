#include <iostream>
#include <iomanip>
#include <string>
#include "../dominio/Paciente.h"
#include "../logica/Cola.h"
#include "../logica/ArbolDecision.h"
#include "../logica/HospitalListaPrincipal.h"
#include "../logica/CargadorPacientes.h"
#include "../logica/Utilidades.h"

using namespace std;

// Lee una linea y la convierte en entero
static bool leerEntero(const string& mensaje, int& valor, bool& finEntrada) {
    cout << mensaje;
    string entrada;
    if (!getline(cin, entrada)) {
        finEntrada = true;
        return false;
    }
    return parsearEntero(recortar(entrada), valor);
}

static bool leerTexto(const string& mensaje, string& texto) {
    cout << mensaje;
    if (!getline(cin, texto)) return false;
    texto = recortar(texto);
    return true;
}

static void mostrarFichaPaciente(const Paciente* p) {
    cout << "ID: " << p->getIdTexto() << "\n";
    cout << "Nombre: " << p->getNombre() << "\n";
    cout << "Edad: " << p->getEdad() << "\n";
    cout << "Temperatura: " << fixed << setprecision(1) << p->getTemperatura() << "\n";
    cout.unsetf(ios::fixed);
    cout << "PresionArterial: " << p->getPresionArterial() << "\n";
    cout << "Dolor: " << p->getDolor() << "\n";
    cout << "TipoDolor: " << p->getTipoDolor() << "\n";
    cout << "Trauma: " << p->getTrauma() << "\n";
    cout << "SintomasNeurologicos: " << p->getSintomasNeurologicos() << "\n";
    cout << "RequiereCirugia: " << p->getRequiereCirugia() << "\n";
    cout << "DiasHospitalizacion: " << p->getDiasHospitalizacion() << "\n";
}

// opcion 1: atender pacientes 

static void atenderPacientes(Cola& cola, const ArbolDecision& arbol, HospitalListaPrincipal& hospital) {
    if (cola.estaVacia()) {
        cout << "No hay pacientes en espera.\n\n";
        return;
    }

    cola.mostrarCola();
    int cantidad = 0;
    bool finEntrada = false;
    if (!leerEntero("Indique la cantidad de pacientes a atender: ", cantidad, finEntrada) || cantidad <= 0) {
        cout << "Error: la cantidad debe ser un numero entero mayor a 0.\n\n";
        return;
    }

    cout << "\n=== ATENDIENDO PACIENTES ===\n";
    for (int i = 0; i < cantidad; i++) {
        if (cola.estaVacia()) {
            cout << "Ya no quedan mas pacientes en la cola.\n";
            break;
        }

        Paciente* paciente = cola.desencolar();
        mostrarFichaPaciente(paciente);

        string ruta;
        string servicio = arbol.evaluar(*paciente, ruta);
        paciente->setServicio(servicio);
        cout << "Ruta: " << ruta << "\n";
        cout << "Servicio asignado: " << servicio << "\n";

        string rotaciones;
        ResultadoDerivacion resultado = hospital.derivarPaciente(servicio, paciente, rotaciones);
        if (resultado == DERIVACION_OK) {
            cout << "Paciente insertado en el AVL de " << servicio << ".\n";
            if (!rotaciones.empty()) cout << "[AVL] " << rotaciones;
        } else {
            if (resultado == DERIVACION_ID_DUPLICADO) {
                cout << "Error: ya existe un paciente con el ID " << paciente->getIdTexto() << ". No fue insertado.\n";
            } else {
                cout << "Error: el servicio '" << servicio << "' no existe. No fue insertado.\n";
            }
            delete paciente;   
        }
        cout << "\n";
    }
}

// opcion 2: departamentos 

static void menuDetalleServicio(NodoServicio* servicio) {
    ArbolAVL* arbol = servicio->getArbol();
    bool volver = false;
    while (!volver) {
        cout << "\n--- AVL de " << servicio->getNombre() << " ---\n";
        cout << "1. Recorrido inorden\n2. Recorrido preorden\n3. Recorrido postorden\n";
        cout << "4. Altura y factor de balance\n5. Eliminar paciente por ID\n0. Volver\n";

        int opcion = 0;
        bool finEntrada = false;
        if (!leerEntero("Seleccionar opcion: ", opcion, finEntrada)) {
            if (finEntrada) return;
            cout << "Error: entrada invalida.\n";
            continue;
        }
        cout << "\n";

        switch (opcion) {
            case 1: cout << "=== INORDEN ===\n"; arbol->mostrarInorden(); break;
            case 2: cout << "=== PREORDEN ===\n"; arbol->mostrarPreorden(); break;
            case 3: cout << "=== POSTORDEN ===\n"; arbol->mostrarPostorden(); break;
            case 4: arbol->mostrarAlturaYBalance(); break;
            case 5: {
                if (arbol->estaVacio()) { cout << "Sin pacientes para eliminar.\n"; break; }
                int id = 0;
                if (!leerEntero("ID del paciente a eliminar: ", id, finEntrada)) {
                    cout << "Error: ID invalido.\n";
                    break;
                }
                string rutaBusqueda;
                Paciente* objetivo = arbol->buscar(id, rutaBusqueda);
                string descripcion = (objetivo != nullptr) ? objetivo->resumen() : "";
                if (arbol->eliminar(id)) {
                    cout << "Paciente " << descripcion << " eliminado del AVL.\n";
                    string rotaciones = arbol->tomarRegistroRotaciones();
                    if (!rotaciones.empty()) cout << "[AVL] " << rotaciones;
                } else {
                    cout << "No existe un paciente con ese ID en este departamento.\n";
                }
                break;
            }
            case 0: volver = true; break;
            default: cout << "Opcion invalida.\n"; break;
        }
    }
}

static void verDepartamentos(HospitalListaPrincipal& hospital) {
    hospital.mostrarEstado();
    cout << "\n";

    int numero = 0;
    bool finEntrada = false;
    if (!leerEntero("Numero de departamento para ver su AVL en detalle (0 para volver): ", numero, finEntrada)) {
        if (!finEntrada) cout << "Error: entrada invalida.\n";
        cout << "\n";
        return;
    }
    if (numero == 0) { cout << "\n"; return; }

    NodoServicio* servicio = hospital.getServicioPorPosicion(numero);
    if (servicio == nullptr) {
        cout << "Error: no existe el departamento " << numero << ".\n\n";
        return;
    }
    menuDetalleServicio(servicio);
    cout << "\n";
}

// opcion 3: buscar paciente

static void buscarPaciente(const HospitalListaPrincipal& hospital, const Cola& cola) {
    string consulta;
    if (!leerTexto("Indique el ID o Nombre del paciente: ", consulta)) return;
    if (consulta.empty()) {
        cout << "Error: debe ingresar un ID o un nombre.\n\n";
        return;
    }

    cout << "Buscando en AVL...\n";
    int id = 0;
    if (parsearEntero(consulta, id)) {
        string ruta;
        Paciente* p = hospital.buscarPorId(id, ruta);
        if (p == nullptr) {
            cout << "Paciente no encontrado en los departamentos.\n";
            if (cola.contieneId(id)) cout << "Nota: sigue en la cola de espera, aun no ha sido atendido.\n";
            cout << "\n";
            return;
        }
        cout << "Paciente encontrado:\n-------\n";
        cout << "ID: " << p->getIdTexto() << "\nNombre: " << p->getNombre()
             << "\nEdad: " << p->getEdad() << "\nDepartamento: " << p->getServicio() << "\n";
        cout << p->detalleClinico() << "\n-------\n";
        cout << "Ruta de busqueda: " << ruta << "\n\n";
        return;
    }

    const int MAX_RESULTADOS = 64;
    Paciente* encontrados[MAX_RESULTADOS];
    int total = hospital.buscarPorNombre(consulta, encontrados, MAX_RESULTADOS);
    if (total == 0) {
        cout << "Paciente no encontrado en los departamentos.\n\n";
        return;
    }
    cout << "Coincidencias: " << total << "\n";
    for (Paciente** cursor = encontrados; cursor < encontrados + total; ++cursor) {
        Paciente* p = *cursor;
        cout << "-------\nID: " << p->getIdTexto() << "\nNombre: " << p->getNombre()
             << "\nEdad: " << p->getEdad() << "\nDepartamento: " << p->getServicio() << "\n";
        cout << p->detalleClinico() << "\n";
    }
    cout << "-------\n\n";
}

// opcion 4: arbol de decision

static void menuArbolDecision(const ArbolDecision& arbol) {
    bool volver = false;
    while (!volver) {
        cout << "\n--- ARBOL DE DECISION ---\n";
        cout << "1. Ver estructura\n2. Recorrido preorden\n3. Recorrido inorden\n";
        cout << "4. Recorrido postorden\n0. Volver\n";

        int opcion = 0;
        bool finEntrada = false;
        if (!leerEntero("Seleccionar opcion: ", opcion, finEntrada)) {
            if (finEntrada) return;
            cout << "Error: entrada invalida.\n";
            continue;
        }
        cout << "\n";

        switch (opcion) {
            case 1: arbol.mostrarEstructura(); break;
            case 2: arbol.mostrarPreorden(); break;
            case 3: arbol.mostrarInorden(); break;
            case 4: arbol.mostrarPostorden(); break;
            case 0: volver = true; break;
            default: cout << "Opcion invalida.\n"; break;
        }
    }
    cout << "\n";
}

int main(int argc, char* argv[]) {
    Cola colaEspera;
    ArbolDecision arbolDecision;
    HospitalListaPrincipal hospital;

    string archivo = (argc > 1) ? argv[1] : "Pacientes.txt";
    bool finEntrada = false;

    // Si el archivo no existe 
    while (CargadorPacientes::cargar(archivo, colaEspera) < 0) {
        if (!leerTexto("Ingrese otra ruta de archivo (o 0 para salir): ", archivo) || archivo == "0") {
            cout << "Hasta luego :D\n";
            return 1;
        }
    }

    bool salir = false;
    while (!salir) {
        cout << "=== HOSPITAL MARMAJA ===\n";
        cout << "1. Atender pacientes\n";
        cout << "2. Ver departamentos\n";
        cout << "3. Buscar paciente\n";
        cout << "4. Ver arbol de decision\n";
        cout << "5. Salir\n";

        int opcion = 0;
        if (!leerEntero("Seleccionar opcion: ", opcion, finEntrada)) {
            if (finEntrada) { cout << "\n"; break; }
            cout << "\nError: entrada invalida. Ingrese un numero.\n\n";
            continue;
        }
        cout << "\n";

        switch (opcion) {
            case 1: atenderPacientes(colaEspera, arbolDecision, hospital); break;
            case 2: verDepartamentos(hospital); break;
            case 3: buscarPaciente(hospital, colaEspera); break;
            case 4: menuArbolDecision(arbolDecision); break;
            case 5: cout << "Hasta luego :D.\n"; salir = true; break;
            default: cout << "Opcion invalida, intente nuevamente.\n\n"; break;
        }
    }

    return 0;
}
