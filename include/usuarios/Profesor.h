#ifndef PROFESOR_H
#define PROFESOR_H

#include "Usuario.h"
#include <iostream>

class Profesor : public Usuario {
public:
    Profesor(std::string id, std::string nombre, std::string correo, std::string contrasena);

    std::string getTipo() const override;
    void mostrarInformacion() const override;
};

#endif
