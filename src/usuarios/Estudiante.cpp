#include "../../include/usuarios/Estudiante.h"

Estudiante::Estudiante(std::string id, std::string nombre, std::string correo, std::string contrasena)
    : Usuario(id, nombre, correo, contrasena) {}

std::string Estudiante::getTipo() const {
    return "Estudiante";
}

void Estudiante::mostrarInformacion() const {
    std::cout << " - Estudiante:\n";
    std::cout << " - ID: " << id << "\n";
    std::cout << " - Nombre: " << nombre << "\n";
    std::cout << " - Correo: " << correo << "\n";
}
