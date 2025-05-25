#include "../../include/recomendaciones/RecomendacionPorTipo.h"

RecomendacionPorTipo::RecomendacionPorTipo(const std::string& tipo) : tipoDeseado(tipo) {}

std::vector<Recurso*> RecomendacionPorTipo::recomendar(const std::vector<Recurso*>& recursos) const {
    std::vector<Recurso*> recomendados;

    for (Recurso* recurso : recursos) {
        if (recurso->getTipo() == tipoDeseado) {
            recomendados.push_back(recurso);
        }
    }

    return recomendados;
}
