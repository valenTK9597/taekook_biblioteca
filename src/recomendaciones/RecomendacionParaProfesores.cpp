#include "../../include/recomendaciones/RecomendacionParaProfesores.h"

std::vector<Recurso*> RecomendacionParaProfesores::recomendar(const std::vector<Recurso*>& recursos) const {
    std::vector<Recurso*> preferidos;
    std::vector<Recurso*> otros;

    for (Recurso* recurso : recursos) {
        std::string tipo = recurso->getTipo();

        if (tipo == "Revista" || tipo == "Articulo") {
            preferidos.push_back(recurso);
        } else {
            otros.push_back(recurso);
        }
    }

    // Combinar: primero los preferidos, luego los demás
    preferidos.insert(preferidos.end(), otros.begin(), otros.end());
    return preferidos;
}
