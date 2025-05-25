#include "../../include/prestamos/PrestamoFactory.h"
#include "../../include/prestamos/EstadoDisponible.h"
#include "../../include/prestamos/EstadoPrestado.h"
#include "../../include/prestamos/EstadoVencido.h"
#include "../../include/prestamos/EstadoDevuelto.h"

#include <fstream>
#include <sstream>
#include <iostream>

Prestamo* PrestamoFactory::crearPrestamo(const std::string& idPrestamo, const std::string& idUsuario,
                                         const std::string& idRecurso, const std::string& fechaPrestamo,
                                         const std::string& fechaDevolucion, const std::string& estadoNombre) {
    EstadoPrestamo* estado = nullptr;

    if (estadoNombre == "Disponible") estado = new EstadoDisponible();
    else if (estadoNombre == "Prestado") estado = new EstadoPrestado();
    else if (estadoNombre == "Vencido") estado = new EstadoVencido();
    else if (estadoNombre == "Devuelto") estado = new EstadoDevuelto();
    else estado = new EstadoDisponible(); // Default de seguridad

    return new Prestamo(idPrestamo, idUsuario, idRecurso, fechaPrestamo, fechaDevolucion, estado);
}

void PrestamoFactory::guardarPrestamoEnArchivo(Prestamo* prestamo, const std::string& rutaArchivo) {
    std::ofstream archivo(rutaArchivo, std::ios::app);
    if (archivo.is_open()) {
        archivo << prestamo->getIdPrestamo() << "|"
                << prestamo->getIdUsuario() << "|"
                << prestamo->getIdRecurso() << "|"
                << prestamo->getFechaPrestamo() << "|"
                << prestamo->getFechaDevolucion() << "|"
                << prestamo->getNombreEstado() << "\n";
        archivo.close();
    } else {
        std::cerr << "⚠️ No se pudo abrir el archivo de préstamos para guardar.\n";
    }
}

std::vector<Prestamo*> PrestamoFactory::cargarPrestamosDesdeArchivo(const std::string& rutaArchivo) {
    std::vector<Prestamo*> prestamos;
    std::ifstream archivo(rutaArchivo);
    std::string linea;

    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string id, usuario, recurso, fechaP, fechaD, estado;

        std::getline(ss, id, '|');
        std::getline(ss, usuario, '|');
        std::getline(ss, recurso, '|');
        std::getline(ss, fechaP, '|');
        std::getline(ss, fechaD, '|');
        std::getline(ss, estado, '|');

        Prestamo* p = crearPrestamo(id, usuario, recurso, fechaP, fechaD, estado);
        prestamos.push_back(p);
    }

    archivo.close();
    return prestamos;
}

bool PrestamoFactory::idPrestamoExistente(const std::string& id, const std::string& rutaArchivo) {
    std::ifstream archivo(rutaArchivo);
    std::string linea;

    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string idLeido;
        std::getline(ss, idLeido, '|');
        if (idLeido == id) return true;
    }

    return false;
}
