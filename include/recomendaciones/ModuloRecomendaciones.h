#ifndef MODULORECOMENDACIONES_H
#define MODULORECOMENDACIONES_H

#include "../recursos/Recurso.h"
#include "../recomendaciones/RecomendacionContexto.h"
#include <string>
#include <vector>
#include "../busqueda/ModuloBusqueda.h"

class ModuloRecomendaciones {
public:
    // Recomendación según tipo de usuario (usa historial o recursos totales)
    static void recomendarPorTipoUsuario(const std::string& nombreUsuario, const std::string& tipoUsuario);

    // Recomendación por tipo específico (ej: "LibroFisico", "Revista", etc.)
    static void recomendarPorTipoRecurso(const std::string& tipo);

    // Recomendación basada en el historial: detecta tipo de recurso más consultado
    static void recomendarPorPreferenciaDetectada(const std::string& nombreUsuario);

    static void mostrarSubmenuRecomendaciones(const std::string& nombreUsuario, const std::string& tipoUsuario);

    ModuloRecomendaciones(const std::string& recursos, const std::string& prestamos, const std::string& usuarios);

    

private:
    std::string rutaRecursos;
    std::string rutaPrestamos;
    std::string rutaUsuarios;
    ModuloBusqueda buscador;
    static std::vector<std::string> leerIdsHistorial(const std::string& nombreUsuario);
    static std::string obtenerIdDesdeNombre(const std::string& nombreUsuario);
    static std::map<std::string, int> contarTiposDesdeHistorial(const std::string& usuarioId);

};

#endif

