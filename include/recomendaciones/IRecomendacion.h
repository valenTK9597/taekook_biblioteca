#ifndef IRECOMENDACION_H
#define IRECOMENDACION_H

#include <vector>
#include <string>
#include "../recursos/Recurso.h"

class IRecomendacion {
public:
    virtual ~IRecomendacion() = default;

    // Método que devuelve una lista de recursos recomendados según la estrategia
    virtual std::vector<Recurso*> recomendar(const std::vector<Recurso*>& recursos) const = 0;
};

#endif
