#ifndef ESTADOPRESTAMO_H
#define ESTADOPRESTAMO_H

#include <string>

// Declaración adelantada para evitar inclusión circular
class Prestamo;

class EstadoPrestamo {
public:
    virtual ~EstadoPrestamo() = default;

    // Nombre legible del estado (ej: "Prestado", "Vencido", etc.)
    virtual std::string getNombre() const = 0;

    // Calcula la multa en base al estado actual del préstamo
    virtual double calcularMulta(const Prestamo* prestamo, const std::string& fechaActual) const = 0;

    // Muestra el estado por consola
    virtual void mostrarEstado() const = 0;
};

#endif
