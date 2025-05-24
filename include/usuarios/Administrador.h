#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include "Usuario.h"
#include <iostream>

class Administrador : public Usuario {
public:
    Administrador(std::string id, std::string nombre, std::string correo, std::string contrasena);

    std::string getTipo() const override;
    void mostrarInformacion() const override;
};

#endif
