#include "../../include/busqueda/BusquedaPorTipo.h"

std::vector<Recurso*> BusquedaPorTipo::buscar(const std::vector<Recurso*>& recursos, const std::string& criterio) const {
    std::vector<Recurso*> resultados;

    for (Recurso* recurso : recursos) {
        if (recurso->getTipo() == criterio) {
            resultados.push_back(recurso);
        }
    }

    return resultados;
}
