#include "../../include/busqueda/BusquedaPorAutor.h"
#include <algorithm>

std::vector<Recurso*> BusquedaPorAutor::buscar(const std::vector<Recurso*>& recursos, const std::string& criterio) const {
    std::vector<Recurso*> resultados;

    for (Recurso* recurso : recursos) {
        std::string autor = recurso->getAutor();
        if (autor.find(criterio) != std::string::npos) {
            resultados.push_back(recurso);
        }
    }

    return resultados;
}
