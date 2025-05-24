#include "../../include/usuarios/Profesor.h"

Profesor::Profesor(std::string id, std::string nombre, std::string correo, std::string contrasena)
    : Usuario(id, nombre, correo, contrasena) {}

std::string Profesor::getTipo() const {
    return "Profesor";
}

void Profesor::mostrarInformacion() const {
    std::cout << " - Profesor:\n";
    std::cout << " - ID: " << id << "\n";
    std::cout << " - Nombre: " << nombre << "\n";
    std::cout << " - Correo: " << correo << "\n";
}
