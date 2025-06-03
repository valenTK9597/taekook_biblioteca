#ifndef MODULOBUSQUEDA_H
#define MODULOBUSQUEDA_H

#include <string>
#include <vector>
#include "BusquedaContexto.h"
#include "../recursos/Recurso.h"

class ModuloBusqueda {
private:
    std::string rutaArchivoRecursos;

    // Cargar recursos según si se incluyen los no disponibles
    std::vector<Recurso*> cargarRecursos(bool incluirNoDisponibles) const;

public:
    ModuloBusqueda(const std::string& rutaRecursos);

    // Métodos de búsqueda con control de privilegios
    void buscarPorTitulo(bool incluirNoDisponibles) const;
    void buscarPorAutor(bool incluirNoDisponibles) const;
    void buscarPorTipo(bool incluirNoDisponibles) const;
};

#endif
