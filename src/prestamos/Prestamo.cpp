#include "../../include/prestamos/Prestamo.h"
#include "../../include/prestamos/EstadoPrestamo.h"
#include <iostream>

Prestamo::Prestamo(std::string idPrestamo, std::string idUsuario, std::string idRecurso,
                   std::string fechaPrestamo, std::string fechaDevolucion, EstadoPrestamo* estado)
    : idPrestamo(idPrestamo), idUsuario(idUsuario), idRecurso(idRecurso),
      fechaPrestamo(fechaPrestamo), fechaDevolucion(fechaDevolucion), estado(estado) {}

Prestamo::~Prestamo() {
    delete estado;
}

std::string Prestamo::getIdPrestamo() const { return idPrestamo; }
std::string Prestamo::getIdUsuario() const { return idUsuario; }
std::string Prestamo::getIdRecurso() const { return idRecurso; }
std::string Prestamo::getFechaPrestamo() const { return fechaPrestamo; }
std::string Prestamo::getFechaDevolucion() const { return fechaDevolucion; }

EstadoPrestamo* Prestamo::getEstado() const { return estado; }
std::string Prestamo::getNombreEstado() const { return estado->getNombre(); }

void Prestamo::setEstado(EstadoPrestamo* nuevoEstado) {
    if (estado != nullptr)
        delete estado;
    estado = nuevoEstado;
}

void Prestamo::registrar() const {
    std::cout << " - Préstamo registrado:\n";
    std::cout << " - ID Préstamo: " << idPrestamo << "\n";
    std::cout << " - Usuario: " << idUsuario << "\n";
    std::cout << " - Recurso: " << idRecurso << "\n";
    std::cout << " - Fecha préstamo: " << fechaPrestamo << "\n";
    std::cout << " - Fecha devolución: " << fechaDevolucion << "\n";
    estado->mostrarEstado();
}

double Prestamo::calcularMulta(const std::string& fechaActual) const {
    return estado->calcularMulta(this, fechaActual);
}

void Prestamo::mostrarDetalle() const {
    std::cout << "\n Detalle del préstamo:\n";
    std::cout << " - ID: " << idPrestamo << "\n";
    std::cout << " - Usuario: " << idUsuario << "\n";
    std::cout << " - Recurso: " << idRecurso << "\n";
    std::cout << " - Fecha préstamo: " << fechaPrestamo << "\n";
    std::cout << " - Fecha devolución: " << fechaDevolucion << "\n";
    std::cout << " - Estado: " << estado->getNombre() << "\n";
}


