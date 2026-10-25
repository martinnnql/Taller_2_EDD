#include "Paciente.h"
#include <sstream>
#include <iomanip>

Paciente::Paciente(int id, string idTexto, string nombre, int edad,
                   double temperatura, int presionArterial, int dolor,
                   string tipoDolor, bool trauma, bool sintomasNeurologicos,
                   bool requiereCirugia, int diasHospitalizacion)
    : Persona(nombre, edad) {
    this->id = id;
    this->idTexto = idTexto;
    this->temperatura = temperatura;
    this->presionArterial = presionArterial;
    this->dolor = dolor;
    this->tipoDolor = tipoDolor;
    this->trauma = trauma;
    this->sintomasNeurologicos = sintomasNeurologicos;
    this->requiereCirugia = requiereCirugia;
    this->diasHospitalizacion = diasHospitalizacion;
    this->servicio = "";
}

Paciente::~Paciente() {}

int Paciente::getId() const { return this->id; }
string Paciente::getIdTexto() const { return this->idTexto; }
double Paciente::getTemperatura() const { return this->temperatura; }
int Paciente::getPresionArterial() const { return this->presionArterial; }
int Paciente::getDolor() const { return this->dolor; }
string Paciente::getTipoDolor() const { return this->tipoDolor; }
bool Paciente::getTrauma() const { return this->trauma; }
bool Paciente::getSintomasNeurologicos() const { return this->sintomasNeurologicos; }
bool Paciente::getRequiereCirugia() const { return this->requiereCirugia; }
int Paciente::getDiasHospitalizacion() const { return this->diasHospitalizacion; }
string Paciente::getServicio() const { return this->servicio; }
void Paciente::setServicio(const string& servicio) { this->servicio = servicio; }

string Paciente::resumen() const {
    return this->nombre + " (" + this->idTexto + ")";
}

string Paciente::detalleClinico() const {
    ostringstream salida;
    salida << fixed << setprecision(1) << "T: " << this->temperatura << " C"
           << " | P: " << this->presionArterial
           << " | D: " << this->dolor
           << " | TD: " << this->tipoDolor
           << " | Tr: " << (this->trauma ? "Si" : "No")
           << " | SN: " << (this->sintomasNeurologicos ? "Si" : "No")
           << " | RC: " << (this->requiereCirugia ? "Si" : "No")
           << " | DH: ";
    if (this->diasHospitalizacion == 0) salida << "Ninguno";
    else salida << this->diasHospitalizacion << " dias";
    return salida.str();
}
