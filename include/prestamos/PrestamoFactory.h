#ifndef PRESTAMOFACTORY_H
#define PRESTAMOFACTORY_H

#include "Prestamo.h"
#include <vector>
#include <string>

class PrestamoFactory {
public:
    // Crea un préstamo con su estado (desde parámetros)
    static Prestamo* crearPrestamo(const std::string& idPrestamo, const std::string& idUsuario,
                                   const std::string& idRecurso, const std::string& fechaPrestamo,
                                   const std::string& fechaDevolucion, const std::string& estadoNombre);

    // Guarda préstamo en archivo
    static void guardarPrestamoEnArchivo(Prestamo* prestamo, const std::string& rutaArchivo);

    // Carga todos los préstamos desde archivo
    static std::vector<Prestamo*> cargarPrestamosDesdeArchivo(const std::string& rutaArchivo);

    // Verifica existencia de un ID de préstamo
    static bool idPrestamoExistente(const std::string& id, const std::string& rutaArchivo);

    // Reglas específicas según usuario y tipo de recurso
    static bool validarReglasPrestamo(const std::string& idUsuario,
                                      const std::string& idRecurso,
                                      const std::string& rutaUsuarios,
                                      const std::string& rutaRecursos,
                                      const std::string& rutaPrestamos);

    // Cuenta préstamos activos (estado == "Prestado") para un usuario
    static int contarPrestamosActivosPorUsuario(const std::string& idUsuario,
                                                const std::string& ruta);

    // Cuenta préstamos activos por tipo de recurso
    static int contarPrestamosActivosPorUsuarioYTipo(const std::string& idUsuario,
                                                     const std::vector<std::string>& tipos,
                                                     const std::string& rutaPrestamos,
                                                     const std::string& rutaRecursos);
};

#endif

