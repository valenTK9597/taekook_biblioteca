#ifndef PRESTAMO_H
#define PRESTAMO_H

#include <string>
#include <iostream>

// Declaración adelantada de EstadoPrestamo
class EstadoPrestamo;

class Prestamo {
private:
    std::string idPrestamo;
    std::string idUsuario;
    std::string idRecurso;
    std::string fechaPrestamo;
    std::string fechaDevolucion;
    EstadoPrestamo* estado;

public:
    Prestamo(std::string idPrestamo, std::string idUsuario, std::string idRecurso,
             std::string fechaPrestamo, std::string fechaDevolucion, EstadoPrestamo* estado);

    ~Prestamo(); // destructor con delete de estado

    std::string getIdPrestamo() const;
    std::string getIdUsuario() const;
    std::string getIdRecurso() const;
    std::string getFechaPrestamo() const;
    std::string getFechaDevolucion() const;

    EstadoPrestamo* getEstado() const;
    std::string getNombreEstado() const;

    void setEstado(EstadoPrestamo* nuevoEstado); // permite transición de estado

    void registrar() const;
    double calcularMulta(const std::string& fechaActual) const;
    void mostrarDetalle() const; 
};
#endif // PRESTAMO_H