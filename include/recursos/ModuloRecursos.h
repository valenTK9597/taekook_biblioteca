#ifndef MODULORECURSOS_H
#define MODULORECURSOS_H

#include "Recurso.h"
#include <string>

class ModuloRecursos {
private:
    std::string rutaArchivoRecursos;

public:
    ModuloRecursos(const std::string& ruta);

    void agregarRecurso();
    void verRecursosDisponibles();
    void verTodosLosRecursos();
    void eliminarRecursoPorId();
    void editarRecursoPorId();
    void buscarPorTitulo();
    void buscarPorAutor();
    void gestionarRecursosAdministrador();
};

#endif
