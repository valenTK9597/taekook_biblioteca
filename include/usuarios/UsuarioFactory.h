#ifndef USUARIOFACTORY_H
#define USUARIOFACTORY_H

#include "Usuario.h"

class UsuarioFactory {
public:
    static Usuario* crearUsuario(const std::string& tipo, const std::string& id, const std::string& nombre,
                                 const std::string& correo, const std::string& contrasena);
};

#endif
