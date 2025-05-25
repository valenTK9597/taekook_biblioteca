#include "../../include/recomendaciones/RecomendacionParaEstudiantes.h"

std::vector<Recurso*> RecomendacionParaEstudiantes::recomendar(const std::vector<Recurso*>& recursos) const {
    std::vector<Recurso*> preferidos;
    std::vector<Recurso*> otros;

    for (Recurso* recurso : recursos) {
        std::string tipo = recurso->getTipo();

        if (tipo == "LibroFisico" || tipo == "Ebook") {
            preferidos.push_back(recurso);
        } else {
            otros.push_back(recurso);
        }
    }

    // Combinar: primero los preferidos, luego los demás
    preferidos.insert(preferidos.end(), otros.begin(), otros.end());
    return preferidos;
}
