#ifndef GESTORNOTIFICACIONESARCHIVO_H
#define GESTORNOTIFICACIONESARCHIVO_H

#include <string>

class GestorNotificacionesArchivo {
public:
    static void guardarMensaje(const std::string& idUsuario, const std::string& mensaje);
};

#endif
