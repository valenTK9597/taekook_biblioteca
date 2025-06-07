#ifndef MODULOPRESTAMOS_H
#define MODULOPRESTAMOS_H

#include "Prestamo.h"
#include "PrestamoFactory.h"
#include <string>
#include <vector>
#include "../include/notificaciones/ModuloNotificaciones.h"

class ModuloNotificaciones; // Forward declaration

class ModuloPrestamos {
private:
    std::string rutaArchivoPrestamos;
    std::string rutaArchivoUsuarios;
    std::string rutaArchivoRecursos;
    

public:

    // Constructor
    ModuloPrestamos(const std::string& rutaPrestamos, const std::string& rutaUsuarios, const std::string& rutaRecursos);

    // Registrar un nuevo préstamo (respetando reglas por tipo de usuario y recurso)
    void registrarPrestamo();

    // Permitir devolución por ID de préstamo (solo si está en estado Prestado)
    void devolverPrestamoPorId(ModuloNotificaciones& moduloNotificaciones);

    // Mostrar todos los préstamos de un usuario (para Estudiante o Profesor)
    void verPrestamosPorUsuario(const std::string& idUsuario);

    // Mostrar todas las reservas activas de un usuario
    void verReservasUsuario(const std::string& idUsuario);

    // Cancelar una reserva si el usuario ya no la necesita
    void cancelarReservaUsuario(const std::string& idUsuario);

    // Vista para administrador: gestionar todos los préstamos
    void gestionarPrestamosAdministrador();

    // Reporte completo en consola
    void mostrarReporteEnConsola();

    // Forzar devolución (por parte de administrador)
    void forzarDevolucionPorId(ModuloNotificaciones& moduloNotificaciones);

    // Cancelar un préstamo existente (error o anulación)
    void cancelarPrestamoPorId();

    // Exportar reporte general a archivo
    void exportarReporteAArchivo();
};

#endif
