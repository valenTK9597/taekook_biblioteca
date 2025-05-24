#include "../../include/usuarios/Administrador.h"

Administrador::Administrador(std::string id, std::string nombre, std::string correo, std::string contrasena)
    : Usuario(id, nombre, correo, contrasena) {}

std::string Administrador::getTipo() const {
    return "Administrador";
}

void Administrador::mostrarInformacion() const {
    std::cout << " - Administrador:\n";
    std::cout << " - ID: " << id << "\n";
    std::cout << " - Nombre: " << nombre << "\n";
    std::cout << " - Correo: " << correo << "\n";
}
