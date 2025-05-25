#ifndef ESTADOPRESTADO_H
#define ESTADOPRESTADO_H

#include "EstadoPrestamo.h"

class EstadoPrestado : public EstadoPrestamo {
public:
    std::string getNombre() const override;
    double calcularMulta(const Prestamo* prestamo, const std::string& fechaActual) const override;
    void mostrarEstado() const override;
};

#endif
