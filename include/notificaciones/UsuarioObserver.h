#ifndef USUARIOOBSERVER_H
#define USUARIOOBSERVER_H

#include "NotificacionObserver.h"
#include <string>
#include <iostream>

class UsuarioObserver : public NotificacionObserver {
private:
    std::string correo;

public:
    UsuarioObserver(const std::string& correo);
    void actualizar(const std::string& mensaje) override;
};

#endif
