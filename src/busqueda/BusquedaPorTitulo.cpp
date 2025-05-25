#include "../../include/busqueda/BusquedaPorTitulo.h"
#include <algorithm>

std::vector<Recurso*> BusquedaPorTitulo::buscar(const std::vector<Recurso*>& recursos, const std::string& criterio) const {
    std::vector<Recurso*> resultados;

    for (Recurso* recurso : recursos) {
        std::string titulo = recurso->getTitulo();
        if (titulo.find(criterio) != std::string::npos) {
            resultados.push_back(recurso);
        }
    }

    return resultados;
}
