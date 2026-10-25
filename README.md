# Taller 2: Sistema de Gestión - Hospital Marmaja

Este proyecto es una extensión del sistema de gestión hospitalaria desarrollado en el **Taller 1** para la asignatura **Estructura de Datos**. Está implementado en **C++** y permite cargar pacientes desde un archivo de texto, atenderlos en orden de llegada, clasificarlos automáticamente mediante un **árbol binario de decisión** y almacenarlos en **árboles AVL** separados por servicio hospitalario.

Se aplican conceptos de Programación Orientada a Objetos (POO), punteros, memoria dinámica, cola FIFO, árboles binarios, recorridos, búsquedas, inserciones, eliminaciones y rotaciones AVL. Las estructuras principales se implementan **manualmente**, sin utilizar contenedores de la STL para reemplazarlas.

## Integrante

- **Nombre:** Martin Arancibia
- **RUT:** 22.273.853-9
- **Nombre en GitHub:** @martinnnql
- **Carrera:** ICCI
- **Paralelo:** C1

## Estructura del Proyecto

El proyecto sigue una arquitectura separada para mantener las responsabilidades claras:

- `dominio/`: Contiene las entidades del negocio (`Persona`, `Paciente`).
- `logica/`: Contiene las estructuras de datos y la lógica del sistema (`Cola`, `ArbolDecision`, `ArbolAVL`, `HospitalListaPrincipal`, nodos y utilidades).
- `main/`: Contiene el punto de entrada y la interfaz de usuario (`main.cpp`).
- `Pacientes.txt`: Archivo de entrada con la información de los pacientes.

## Instrucciones de Compilación y Ejecución
Para evaluar este proyecto, asegúrese de tener instalado el compilador MinGW-w64 (g++) y de abrir su terminal en la carpeta raíz del proyecto (donde se ubica el archivo pacientes.txt).
1. Compilación
Ejecute el siguiente comando para ensamblar todos los archivos en un único ejecutable:

g++ -std=c++11 -Wall -Wextra -o TallerHospital main/main.cpp dominio/Persona.cpp dominio/Paciente.cpp logica/Utilidades.cpp logica/Nodo.cpp logica/Cola.cpp logica/NodoDecision.cpp logica/ArbolDecision.cpp logica/NodoAVL.cpp logica/ArbolAVL.cpp logica/NodoServicio.cpp logica/HospitalListaPrincipal.cpp logica/CargadorPacientes.cpp

2. Ejecución
Una vez compilado sin errores, inicie el programa con el siguiente comando:
- En Windows (PowerShell/CMD): .\TallerHospital.exe
- En Linux/Mac: ./TallerHospital

## Funcionamiento del Sistema

El programa sigue el siguiente flujo de procesamiento:

**Archivo de pacientes → Cola FIFO → Árbol de decisión → Servicio asignado → Árbol AVL**

1. Se cargan los pacientes desde el archivo `Pacientes.txt`.
2. Los pacientes válidos se incorporan a una cola implementada manualmente, respetando su orden de llegada.
3. Al atender un paciente, este se retira de la cola y se evalúa mediante el árbol de decisión.
4. El árbol determina automáticamente el servicio correspondiente según sus características.
5. El paciente se almacena en el árbol AVL del servicio asignado, utilizando su ID como clave de ordenamiento.
6. El sistema permite consultar departamentos, buscar pacientes y visualizar los recorridos de los árboles.

## Árbol de Decisión

El árbol de decisión fue implementado manualmente mediante nodos y punteros. Su función es evaluar los atributos clínicos de cada paciente y determinar el servicio hospitalario correspondiente.

### Criterios de Clasificación

Las condiciones se evalúan en el siguiente orden de prioridad:

| Prioridad | Condición | Servicio o siguiente evaluación |
| --- | --- | --- |
| 1 | Dolor >= 9 | Urgencias |
| 2 | Presión arterial >= 180 | Urgencias |
| 3 | Edad < 14 | Pediatría |
| 4 | Trauma == 1 y RequiereCirugia == 1 | Cirugía |
| 5 | Trauma == 1 y RequiereCirugia == 0 | Traumatología |
| 6 | SintomasNeurologicos == 1 | Neurología |
| 7 | TipoDolor == "pecho" | Cardiología |
| 8 | RequiereCirugia == 1 | Cirugía |
| 9 | Temperatura >= 38.5 | Urgencias |
| 10 | DiasHospitalizacion >= 2 | Hospitalización |
| 11 | Ninguna condición anterior | Medicina General |

Las condiciones se comprueban siguiendo la estructura del árbol. Cuando se cumple una condición que determina un servicio, se termina la evaluación.

### Justificación de las Decisiones

- **Dolor intenso:** un dolor de nivel 9 o superior se considera prioritario y se asigna a Urgencias.
- **Presión arterial elevada:** una presión igual o superior a 180 deriva al paciente a Urgencias.
- **Edad:** los pacientes menores de 14 años son asignados a Pediatría, salvo que presenten una condición de urgencia evaluada anteriormente.
- **Trauma:** los pacientes con trauma se derivan a Traumatología o Cirugía, dependiendo de si requieren intervención quirúrgica.
- **Síntomas neurológicos:** los pacientes que presentan estos síntomas son asignados a Neurología.
- **Dolor de pecho:** se utiliza como criterio para derivar pacientes a Cardiología.
- **Requerimiento de cirugía:** permite asignar a Cirugía a pacientes que requieren una intervención, incluso cuando no presentan trauma.
- **Temperatura elevada:** una temperatura igual o superior a 38.5 °C permite identificar casos que requieren atención en Urgencias.
- **Días de hospitalización:** los pacientes que requieren una estancia estimada de dos o más días son asignados a Hospitalización.
- **Medicina General:** funciona como servicio predeterminado cuando no se cumple ninguna condición anterior.

## Árboles AVL por Servicio

Cada servicio hospitalario dispone de un árbol AVL independiente, implementado manualmente.

Los pacientes se almacenan utilizando su **ID numérico como clave de ordenamiento**, permitiendo realizar búsquedas y mantener una estructura balanceada.

## Archivo de Entrada

El programa utiliza un archivo llamado `Pacientes.txt`, ubicado en la carpeta raíz del proyecto.
