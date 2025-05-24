#include "../../include/usuarios/Usuario.h"

Usuario::Usuario(std::string id, std::string nombre, std::string correo, std::string contrasena)
    : id(id), nombre(nombre), correo(correo), contrasena(contrasena) {}

std::string Usuario::getId() const { return id; }
std::string Usuario::getNombre() const { return nombre; }
std::string Usuario::getCorreo() const { return correo; }
std::string Usuario::getContrasena() const { return contrasena; }

void Usuario::setNombre(const std::string& n) { nombre = n; }
void Usuario::setCorreo(const std::string& c) { correo = c; }
void Usuario::setContrasena(const std::string& c) { contrasena = c; }
