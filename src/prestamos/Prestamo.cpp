#include "../../include/prestamos/Prestamo.h"
#include "../../include/prestamos/EstadoPrestamo.h"
#include <iostream>
#include <algorithm>

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
std::string Prestamo::getFechaDevolucion() const { std::string fechaLimpia = fechaDevolucion;
    fechaLimpia.erase(remove(fechaLimpia.begin(), fechaLimpia.end(), '\n'), fechaLimpia.end());
    fechaLimpia.erase(remove(fechaLimpia.begin(), fechaLimpia.end(), '\r'), fechaLimpia.end());
    fechaLimpia.erase(remove_if(fechaLimpia.begin(), fechaLimpia.end(), ::isspace), fechaLimpia.end());
    return fechaLimpia;}

EstadoPrestamo* Prestamo::getEstado() const { return estado; }
std::string Prestamo::getNombreEstado() const { return estado->getNombre(); }

void Prestamo::setEstado(EstadoPrestamo* nuevoEstado) {
    if (estado != nullptr)
        delete estado;
    estado = nuevoEstado;
}

void Prestamo::registrar() const {
    std::cout << " - Prestamo registrado:\n";
    std::cout << " - ID Prestamo: " << idPrestamo << "\n";
    std::cout << " - Usuario: " << idUsuario << "\n";
    std::cout << " - Recurso: " << idRecurso << "\n";
    std::cout << " - Fecha prestamo: " << fechaPrestamo << "\n";
    std::cout << " - Fecha devolucion: " << fechaDevolucion << "\n";
    estado->mostrarEstado();
}

double Prestamo::calcularMulta(const std::string& fechaActual) const {
    return estado->calcularMulta(this, fechaActual);
}

void Prestamo::mostrarDetalle() const {
    std::cout << "\n Detalle del prestamo:\n";
    std::cout << " - ID: " << idPrestamo << "\n";
    std::cout << " - Usuario: " << idUsuario << "\n";
    std::cout << " - Recurso: " << idRecurso << "\n";
    std::cout << " - Fecha prestamo: " << fechaPrestamo << "\n";
    std::cout << " - Fecha devolucion: " << fechaDevolucion << "\n";
    std::cout << " - Estado: " << estado->getNombre() << "\n";
}


