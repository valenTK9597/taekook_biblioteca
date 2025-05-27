#include "../../include/prestamos/PrestamoFactory.h"
#include "../../include/prestamos/EstadoDisponible.h"
#include "../../include/prestamos/EstadoPrestado.h"
#include "../../include/prestamos/EstadoVencido.h"
#include "../../include/prestamos/EstadoDevuelto.h"
#include "../../include/recursos/RecursoFactory.h"
#include "../../include/usuarios/UsuarioFactory.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>

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

int PrestamoFactory::contarPrestamosActivosPorUsuario(const std::string& idUsuario, const std::string& rutaArchivo) {
    std::ifstream archivo(rutaArchivo);
    std::string linea;
    int contador = 0;

    while (getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string id, uid, rid, fechaI, fechaF, estado;
        std::getline(ss, id, '|');
        std::getline(ss, uid, '|');
        std::getline(ss, rid, '|');
        std::getline(ss, fechaI, '|');
        std::getline(ss, fechaF, '|');
        std::getline(ss, estado, '|');

        if (uid == idUsuario && estado == "Prestado") contador++;
    }

    return contador;
}

int PrestamoFactory::contarPrestamosActivosPorUsuarioYTipo(const std::string& idUsuario,
    const std::vector<std::string>& tipos, const std::string& rutaPrestamos, const std::string& rutaRecursos) {

    std::ifstream archivo(rutaPrestamos);
    std::string linea;
    int contador = 0;

    while (getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string id, uid, rid, fechaI, fechaF, estado;
        std::getline(ss, id, '|');
        std::getline(ss, uid, '|');
        std::getline(ss, rid, '|');
        std::getline(ss, fechaI, '|');
        std::getline(ss, fechaF, '|');
        std::getline(ss, estado, '|');

        if (uid == idUsuario && estado == "Prestado") {
            Recurso* recurso = RecursoFactory::obtenerRecursoPorId(rid, rutaRecursos);
            if (recurso && std::find(tipos.begin(), tipos.end(), recurso->getTipo()) != tipos.end()) {
                contador++;
            }
            delete recurso;
        }
    }

    return contador;
}

bool PrestamoFactory::validarReglasPrestamo(const std::string& idUsuario,
                                            const std::string& idRecurso,
                                            const std::string& rutaUsuarios,
                                            const std::string& rutaRecursos,
                                            const std::string& rutaPrestamos) {
    // Obtener datos del recurso
    Recurso* recurso = RecursoFactory::obtenerRecursoPorId(idRecurso, rutaRecursos);
    if (!recurso) {
        std::cout << "❌ Recurso no encontrado.\n";
        return false;
    }
    std::string tipoRecurso = recurso->getTipo();
    delete recurso;

    // Obtener datos del usuario
    Usuario* usuario = UsuarioFactory::obtenerUsuarioPorId(idUsuario, rutaUsuarios);
    if (!usuario) {
        std::cout << "❌ Usuario no encontrado.\n";
        return false;
    }
    std::string tipoUsuario = usuario->getTipo();
    delete usuario;

    // Reglas específicas para estudiantes
    if (tipoUsuario == "Estudiante") {
        if (tipoRecurso == "LibroFisico") {
            int prestamosLibro = contarPrestamosActivosPorUsuarioYTipo(idUsuario, {"LibroFisico"}, rutaPrestamos, rutaRecursos);
            if (prestamosLibro >= 3) {
                std::cout << "❌ Límite de libros físicos alcanzado (3).\n";
                return false;
            }
        }
        if (tipoRecurso == "Ebook" || tipoRecurso == "Articulo") {
            int digitales = contarPrestamosActivosPorUsuarioYTipo(idUsuario, {"Ebook", "Articulo"}, rutaPrestamos, rutaRecursos);
            if (digitales >= 5) {
                std::cout << "❌ Límite de recursos digitales alcanzado (5 entre Ebook y Artículo).\n";
                return false;
            }
        }
    }

    return true;
}
