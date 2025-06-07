#ifndef MODULONOTIFICACIONES_H
#define MODULONOTIFICACIONES_H

#include <string>
#include "../prestamos/ModuloPrestamos.h"
#include <vector>


class ModuloPrestamos;

class ModuloNotificaciones {
private:
    std::string rutaBase = "data/notificaciones/";
    std::string rutaArchivoUsuarios;
    bool esAdministrador(const std::string& tipo) const;
    std::string obtenerRutaNotificacion(const std::string& canal, const std::string& idUsuario) const;
 
public:
    ModuloNotificaciones();
    ModuloNotificaciones(const std::string& rutaUsuarios);

    void verNotificacionesUsuario(const std::string& idUsuario, const std::string& canal) const;
    void gestionarNotificacionesUsuario(const std::string& idUsuario, ModuloPrestamos& moduloPrestamos);
    void enviarNotificacionManual(const std::string& idUsuario);
    void enviarRecordatoriosDevolucionPorUsuario(const std::string& idUsuario, ModuloPrestamos& moduloPrestamos);
    void enviarRecordatoriosDevolucion(const std::string& rutaArchivoPrestamos, const std::string& rutaArchivoUsuarios);
    void notificarDevolucionConRetraso(const std::string& idUsuario);
    void notificarDevolucionExitosa(const std::string& idUsuario);
    void notificarReservaDisponible(const std::vector<std::string>& usuarios, const std::string& idRecurso);
    void enviarAdvertenciasGravesPorVencimiento(const std::string& rutaArchivoPrestamos, const std::string& rutaArchivoUsuarios);


};

#endif


