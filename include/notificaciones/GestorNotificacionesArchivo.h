#ifndef GESTORNOTIFICACIONESARCHIVO_H
#define GESTORNOTIFICACIONESARCHIVO_H

#include <string>
#include <vector>
#include <fstream>

class GestorNotificacionesArchivo {
public:

    static void guardarMensaje(const std::string& idUsuario, const std::string& mensaje, const std::string& canal);

    // Versión anterior (opcional)
    static void guardarMensaje(const std::string& idUsuario, const std::string& mensaje) {
    guardarMensaje(idUsuario, mensaje, "app"); // Por defecto, canal "app"
}

    static std::vector<std::string> leerMensajes(const std::string& idUsuario, const std::string& canal);

};

#endif
