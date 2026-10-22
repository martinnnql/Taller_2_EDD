#pragma once
#include <string>
#include "Persona.h"
using namespace std;

class Paciente : public Persona {
private:
    int id;                  
    string idTexto;          
    double temperatura;
    int presionArterial;   
    int dolor;              
    string tipoDolor;       
    bool trauma;
    bool sintomasNeurologicos;
    bool requiereCirugia;
    int diasHospitalizacion;
    string servicio;         // se asigna despues de evaluar el arbol

public:
    Paciente(int id, string idTexto, string nombre, int edad,
             double temperatura, int presionArterial, int dolor,
             string tipoDolor, bool trauma, bool sintomasNeurologicos,
             bool requiereCirugia, int diasHospitalizacion);
    ~Paciente();

    int getId() const;
    string getIdTexto() const;
    double getTemperatura() const;
    int getPresionArterial() const;
    int getDolor() const;
    string getTipoDolor() const;
    bool getTrauma() const;
    bool getSintomasNeurologicos() const;
    bool getRequiereCirugia() const;
    int getDiasHospitalizacion() const;
    string getServicio() const;
    void setServicio(const string& servicio);

    string resumen() const override;       
    string detalleClinico() const;         
};
