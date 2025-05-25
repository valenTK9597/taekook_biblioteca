#ifndef RECOMENDACIONPARAESTUDIANTES_H
#define RECOMENDACIONPARAESTUDIANTES_H

#include "IRecomendacion.h"

class RecomendacionParaEstudiantes : public IRecomendacion {
public:
    std::vector<Recurso*> recomendar(const std::vector<Recurso*>& recursos) const override;
};

#endif
