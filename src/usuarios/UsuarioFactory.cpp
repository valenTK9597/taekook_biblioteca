#include "../../include/usuarios/UsuarioFactory.h"
#include "../../include/usuarios/Estudiante.h"
#include "../../include/usuarios/Profesor.h"
#include "../../include/usuarios/Administrador.h"

Usuario* UsuarioFactory::crearUsuario(const std::string& tipo, const std::string& id, const std::string& nombre,
                                      const std::string& correo, const std::string& contrasena) {
    if (tipo == "Estudiante") {
        return new Estudiante(id, nombre, correo, contrasena);
    } else if (tipo == "Profesor") {
        return new Profesor(id, nombre, correo, contrasena);
    } else if (tipo == "Administrador") {
        return new Administrador(id, nombre, correo, contrasena);
    } else {
        return nullptr;
    }
}
