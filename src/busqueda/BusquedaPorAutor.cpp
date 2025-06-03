#include "../../include/busqueda/BusquedaPorAutor.h"
#include <algorithm>

// Función auxiliar para normalizar texto
static std::string normalizar(const std::string& texto) {
    std::string limpio = texto;
    std::transform(limpio.begin(), limpio.end(), limpio.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    size_t inicio = limpio.find_first_not_of(" \t\n\r");
    size_t fin = limpio.find_last_not_of(" \t\n\r");
    if (inicio != std::string::npos && fin != std::string::npos)
        limpio = limpio.substr(inicio, fin - inicio + 1);
    else
        limpio = "";

    return limpio;
}

std::vector<Recurso*> BusquedaPorAutor::buscar(const std::vector<Recurso*>& recursos, const std::string& criterio) const {
    std::vector<Recurso*> resultados;
    std::string criterioNormalizado = normalizar(criterio);

    for (Recurso* recurso : recursos) {
        std::string autor = normalizar(recurso->getAutor());
        if (autor.find(criterioNormalizado) != std::string::npos) {
            resultados.push_back(recurso);
        }
    }

    return resultados;
}
