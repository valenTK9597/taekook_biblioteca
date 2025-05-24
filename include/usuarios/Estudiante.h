#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include "Usuario.h"
#include <iostream>

class Estudiante : public Usuario {
public:
    Estudiante(std::string id, std::string nombre, std::string correo, std::string contrasena);

    std::string getTipo() const override;
    void mostrarInformacion() const override;
};

#endif
