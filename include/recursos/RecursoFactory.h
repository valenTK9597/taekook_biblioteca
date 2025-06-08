#ifndef RECURSOFACTORY_H
#define RECURSOFACTORY_H

#include "Recurso.h"
#include <vector>

class RecursoFactory {
public:
    static Recurso* crearRecurso(const std::string& tipo, const std::string& id,
                                  const std::string& titulo, const std::string& autor,
                                  int anio, bool disponible);

    static void guardarRecursoEnArchivo(Recurso* recurso, const std::string& rutaArchivo);
    static std::vector<Recurso*> cargarRecursosDesdeArchivo(const std::string& rutaArchivo);

    static bool idExistente(const std::string& id, const std::string& rutaArchivo);
    static bool eliminarRecursoPorId(const std::string& id, const std::string& rutaArchivo);
    static Recurso* obtenerRecursoPorId(const std::string& id, const std::string& rutaArchivo);
    static std::vector<Recurso*> leerRecursosDesdeArchivo(const std::string& ruta);
    static Recurso* buscarRecursoPorId(const std::string& id);

};

#endif

