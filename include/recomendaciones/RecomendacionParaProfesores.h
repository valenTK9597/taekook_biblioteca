#ifndef RECOMENDACIONPARAPROFESORES_H
#define RECOMENDACIONPARAPROFESORES_H

#include "IRecomendacion.h"

class RecomendacionParaProfesores : public IRecomendacion {
public:
    std::vector<Recurso*> recomendar(const std::vector<Recurso*>& recursos) const override;
};

#endif
