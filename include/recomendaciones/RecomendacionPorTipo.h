#ifndef RECOMENDACIONPORTIPO_H
#define RECOMENDACIONPORTIPO_H

#include "IRecomendacion.h"

class RecomendacionPorTipo : public IRecomendacion {
private:
    std::string tipoDeseado;

public:
    RecomendacionPorTipo(const std::string& tipo);
    std::vector<Recurso*> recomendar(const std::vector<Recurso*>& recursos) const override;
};

#endif
