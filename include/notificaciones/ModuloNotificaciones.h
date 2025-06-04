#ifndef MODULONOTIFICACIONES_H
#define MODULONOTIFICACIONES_H

#include <string>

class ModuloNotificaciones {
private:
    std::string rutaBase = "data/notificaciones/";
    std::string rutaArchivoUsuarios;

    bool esAdministrador(const std::string& tipo) const;
    std::string obtenerRutaNotificacion(const std::string& canal, const std::string& idUsuario) const;

public:
    ModuloNotificaciones(const std::string& rutaUsuarios);

    void verNotificacionesUsuario(const std::string& idUsuario, const std::string& canal) const;
    void gestionarNotificacionesUsuario(const std::string& idUsuario);
    void enviarNotificacionManual(const std::string& idUsuario);
};

#endif


