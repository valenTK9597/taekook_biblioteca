#include "../../include/prestamos/ModuloPrestamos.h"
#include "../../include/prestamos/PrestamoFactory.h"
#include "../../include/prestamos/EstadoDevuelto.h"
#include "../../include/prestamos/EstadoVencido.h"
#include "../../include/prestamos/EstadoPrestado.h"
#include "../../include/prestamos/EstadoDisponible.h"
#include "../../include/recursos/RecursoFactory.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <iomanip>
#include <ctime>

// Constructor
ModuloPrestamos::ModuloPrestamos(const std::string& rutaPrestamos,
                                 const std::string& rutaUsuarios,
                                 const std::string& rutaRecursos)
    : rutaArchivoPrestamos(rutaPrestamos),
      rutaArchivoUsuarios(rutaUsuarios),
      rutaArchivoRecursos(rutaRecursos) {}

// Obtener fecha actual en formato YYYY-MM-DD
std::string obtenerFechaActual() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", now);
    return std::string(buffer);
}

bool esFormatoFechaValido(const std::string& fecha) {
    std::tm tmFecha = {};
    std::istringstream ss(fecha);
    ss >> std::get_time(&tmFecha, "%Y-%m-%d");
    return !ss.fail();
}


// Calcular días de retraso entre dos fechas
int calcularDiasRetraso(const std::string& fechaLimite, const std::string& fechaActual) {
    std::tm tmLimite = {}, tmActual = {};
    std::istringstream ss1(fechaLimite);
    std::istringstream ss2(fechaActual);

    ss1 >> std::get_time(&tmLimite, "%Y-%m-%d");
    ss2 >> std::get_time(&tmActual, "%Y-%m-%d");

    std::time_t timeLimite = std::mktime(&tmLimite);
    std::time_t timeActual = std::mktime(&tmActual);

    double segundos = std::difftime(timeActual, timeLimite);
    return static_cast<int>(segundos / (60 * 60 * 24));
}

// Registrar nuevo préstamo
void ModuloPrestamos::registrarPrestamo() {
    std::string idPrestamo, idUsuario, idRecurso, fechaInicio, fechaFin;

    std::cout << "\n Registro de nuevo prestamo:\n";
    std::cout << "ID del prestamo: ";
    std::cin >> idPrestamo;

    if (PrestamoFactory::idPrestamoExistente(idPrestamo, rutaArchivoPrestamos)) {
        std::cout << " Ya existe un prestamo con ese ID.\n";
        return;
    }

    std::cout << "ID del usuario: ";
    std::cin >> idUsuario;
    std::cout << "ID del recurso: ";
    std::cin >> idRecurso;

    std::cout << "[DEBUG] Validando usuario: " << idUsuario << "\n";

    // Validar reglas
    if (!PrestamoFactory::validarReglasPrestamo(idUsuario, idRecurso,
                                                rutaArchivoUsuarios,
                                                rutaArchivoRecursos,
                                                rutaArchivoPrestamos)) {
        return;
    }

    // Validar si el recurso está prestado
    if (PrestamoFactory::recursoActualmentePrestado(idRecurso, rutaArchivoPrestamos)) {
        PrestamoFactory::registrarReserva(idUsuario, idRecurso);
        return;
    }

    fechaInicio = obtenerFechaActual();
    std::cout << " Fecha de prestamo generada automaticamente: " << fechaInicio << "\n";

    do {
        std::cout << "Fecha devolucion (YYYY-MM-DD): ";
        std::cin >> fechaFin;

        if (!esFormatoFechaValido(fechaFin)) {
            std::cout << " Formato invalido. Intente de nuevo.\n";
        }
    } while (!esFormatoFechaValido(fechaFin));

    Prestamo* nuevo = PrestamoFactory::crearPrestamo(idPrestamo, idUsuario, idRecurso,
                                                     fechaInicio, fechaFin, "Prestado");

    PrestamoFactory::guardarPrestamoEnArchivo(nuevo, rutaArchivoPrestamos);
    nuevo->registrar();

    // 🔁 Actualizar estado de disponibilidad en recurso
    std::vector<Recurso*> recursos = RecursoFactory::cargarRecursosDesdeArchivo(rutaArchivoRecursos);
    std::ofstream archivoTemp("data/temp_recursos.txt");

    for (Recurso* r : recursos) {
        if (r->getId() == idRecurso) {
            r->setDisponible(false);  // marcar como no disponible
        }
        archivoTemp << r->getId() << "|" << r->getTitulo() << "|" << r->getAutor() << "|"
                    << r->getAnioPublicacion() << "|" << r->estaDisponible() << "|"
                    << r->getTipo() << "\n";
        delete r;
    }

    archivoTemp.close();
    std::remove(rutaArchivoRecursos.c_str());
    std::rename("data/temp_recursos.txt", rutaArchivoRecursos.c_str());

    delete nuevo;
}


// Devolución por ID
void ModuloPrestamos::devolverPrestamoPorId() {
    std::string id;
    std::cout << "\n Devolver prestamo\nIngrese el ID del prestamo: ";
    std::cin >> id;

    std::ifstream entrada(rutaArchivoPrestamos);
    std::ofstream salida("data/temp_prestamos.txt");
    std::string linea;
    bool encontrado = false;
    std::string recursoDevueltoId;

    std::string fechaActual = obtenerFechaActual();

    while (getline(entrada, linea)) {
        std::stringstream ss(linea);
        std::string idL, uid, rid, fInicio, fFin, estado;
        getline(ss, idL, '|');
        getline(ss, uid, '|');
        getline(ss, rid, '|');
        getline(ss, fInicio, '|');
        getline(ss, fFin, '|');
        getline(ss, estado, '|');

        if (idL == id && estado == "Prestado") {
            recursoDevueltoId = rid;

            if (fechaActual > fFin) {
                estado = "Vencido";

                Recurso* recurso = RecursoFactory::obtenerRecursoPorId(rid, rutaArchivoRecursos);
                if (recurso) {
                    int diasRetraso = calcularDiasRetraso(fFin, fechaActual);
                    double multa = recurso->calcularMulta(diasRetraso);
                    std::cout << " El prestamo fue devuelto con retraso.\n";
                    std::cout << " Multa por " << diasRetraso << " dias de retraso: $" << multa << "\n";
                    delete recurso;
                } else {
                    std::cout << "⚠️ No se pudo calcular la multa (recurso no encontrado).\n";
                }

            } else {
                estado = "Devuelto";
                std::cout << " Prestamo devuelto a tiempo.\n";
            }

            encontrado = true;
        }

        salida << idL << "|" << uid << "|" << rid << "|"
               << fInicio << "|" << fFin << "|" << estado << "\n";
    }

    entrada.close();
    salida.close();

    std::remove(rutaArchivoPrestamos.c_str());
    std::rename("data/temp_prestamos.txt", rutaArchivoPrestamos.c_str());

    if (!encontrado) {
        std::cout << " No se encontro prestamo valido para devolver.\n";
        return;
    }

    // 🔁 Marcar recurso como disponible nuevamente
    std::vector<Recurso*> recursos = RecursoFactory::cargarRecursosDesdeArchivo(rutaArchivoRecursos);
    std::ofstream archivoTemp("data/temp_recursos.txt");

    for (Recurso* r : recursos) {
        if (r->getId() == recursoDevueltoId) {
            r->setDisponible(true);  // marcar como disponible
        }
        archivoTemp << r->getId() << "|" << r->getTitulo() << "|" << r->getAutor() << "|"
                    << r->getAnioPublicacion() << "|" << r->estaDisponible() << "|"
                    << r->getTipo() << "\n";
        delete r;
    }

    archivoTemp.close();
    std::remove(rutaArchivoRecursos.c_str());
    std::rename("data/temp_recursos.txt", rutaArchivoRecursos.c_str());
}


// Ver préstamos por usuario
void ModuloPrestamos::verPrestamosPorUsuario(const std::string& idUsuario) {
    std::vector<Prestamo*> prestamos = PrestamoFactory::cargarPrestamosDesdeArchivo(rutaArchivoPrestamos);
    bool encontrados = false;

    std::cout << "\n Prestamos del usuario " << idUsuario << ":\n";
    for (Prestamo* p : prestamos) {
        if (p->getIdUsuario() == idUsuario) {
            p->mostrarDetalle();
            encontrados = true;
        }
    }

    if (!encontrados) {
        std::cout << " No se encontraron prestamos asociados a ese usuario.\n";
    }

    for (Prestamo* p : prestamos) delete p;
}

// Ver reservas del usuario
void ModuloPrestamos::verReservasUsuario(const std::string& idUsuario) {
    PrestamoFactory::mostrarReservasDelUsuario(idUsuario);
}

// Cancelar una reserva
void ModuloPrestamos::cancelarReservaUsuario(const std::string& idUsuario) {
    std::string idRecurso;
    std::cout << "ID del recurso a cancelar reserva: ";
    std::cin >> idRecurso;
    PrestamoFactory::cancelarReserva(idUsuario, idRecurso);
}

// Gestión completa de administrador
void ModuloPrestamos::gestionarPrestamosAdministrador() {
    bool continuar = true;

    while (continuar) {
        std::cout << "\n Gestion de prestamos (Administrador):\n";
        std::cout << "1. Ver todos los prestamos\n";
        std::cout << "2. Buscar por ID de usuario\n";
        std::cout << "3. Buscar por ID de recurso\n";
        std::cout << "4. Forzar devolucion\n";
        std::cout << "5. Cancelar prestamo activo\n";
        std::cout << "6. Registrar nuevo préstamo\n";
        std::cout << "7. Ver reporte en consola\n";
        std::cout << "8. Exportar reporte a archivo\n";
        std::cout << "9. Volver\n";

        int opcion;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        std::vector<Prestamo*> prestamos = PrestamoFactory::cargarPrestamosDesdeArchivo(rutaArchivoPrestamos);

        switch (opcion) {
            case 1:
                for (Prestamo* p : prestamos) p->mostrarDetalle();
                break;
            case 2: {
                std::string uid;
                std::cout << "ID de usuario: ";
                std::cin >> uid;
                for (Prestamo* p : prestamos)
                    if (p->getIdUsuario() == uid) p->mostrarDetalle();
                break;
            }
            case 3: {
                std::string rid;
                std::cout << "ID de recurso: ";
                std::cin >> rid;
                for (Prestamo* p : prestamos)
                    if (p->getIdRecurso() == rid) p->mostrarDetalle();
                break;
            }
            case 4: forzarDevolucionPorId(); break;
            case 5: cancelarPrestamoPorId(); break;
            case 6: registrarPrestamo(); break;
            case 7: mostrarReporteEnConsola(); break;
            case 8: exportarReporteAArchivo(); break;
            case 9: continuar = false; break;
            default: std::cout << "❌ Opción invalida.\n";
        }

        for (Prestamo* p : prestamos) delete p;
    }
}

// Forzar devolución por parte del administrador
void ModuloPrestamos::forzarDevolucionPorId() {
    std::string id;
    std::cout << "ID del prestamo a forzar devolucion: ";
    std::cin >> id;

    std::ifstream entrada(rutaArchivoPrestamos);
    std::ofstream salida("data/temp_prestamos.txt");
    std::string linea;
    bool modificado = false;
    std::string ridPrestado;  // guardamos el ID del recurso afectado

    while (getline(entrada, linea)) {
        std::stringstream ss(linea);
        std::string idL, uid, rid, fInicio, fFin, estado;
        getline(ss, idL, '|');
        getline(ss, uid, '|');
        getline(ss, rid, '|');
        getline(ss, fInicio, '|');
        getline(ss, fFin, '|');
        getline(ss, estado, '|');

        if (idL == id && estado == "Prestado") {
            std::string fechaActual = obtenerFechaActual();

            if (fechaActual > fFin) {
                estado = "Vencido";

                Recurso* recurso = RecursoFactory::obtenerRecursoPorId(rid, rutaArchivoRecursos);
                if (recurso) {
                    int diasRetraso = calcularDiasRetraso(fFin, fechaActual);
                    double multa = recurso->calcularMulta(diasRetraso);
                    std::cout << " El prestamo tiene estado vencido.\n";
                    std::cout << " Multa acumulada: $" << multa << " por " << diasRetraso << " dias de retraso.\n";
                    delete recurso;
                } else {
                    std::cout << " No se pudo calcular multa (recurso no encontrado).\n";
                }
            } else {
                estado = "Devuelto";
                std::cout << " Prestamo aún en fecha, marcado como devuelto.\n";
            }

            ridPrestado = rid;  // guardar para actualizar recurso
            modificado = true;
        }

        salida << idL << "|" << uid << "|" << rid << "|"
               << fInicio << "|" << fFin << "|" << estado << "\n";
    }

    entrada.close();
    salida.close();

    std::remove(rutaArchivoPrestamos.c_str());
    std::rename("data/temp_prestamos.txt", rutaArchivoPrestamos.c_str());

    if (modificado) {
        std::cout << " Devolucion forzada con exito.\n";

        // 🔁 Actualizar disponibilidad en recursos.txt
        std::vector<Recurso*> recursos = RecursoFactory::cargarRecursosDesdeArchivo(rutaArchivoRecursos);
        std::ofstream archivoTemp("data/temp_recursos.txt");

        for (Recurso* r : recursos) {
            if (r->getId() == ridPrestado) {
                r->setDisponible(true);
            }
            archivoTemp << r->getId() << "|" << r->getTitulo() << "|" << r->getAutor() << "|"
                        << r->getAnioPublicacion() << "|" << r->estaDisponible() << "|"
                        << r->getTipo() << "\n";
            delete r;
        }

        archivoTemp.close();
        std::remove(rutaArchivoRecursos.c_str());
        std::rename("data/temp_recursos.txt", rutaArchivoRecursos.c_str());
    } else {
        std::cout << " No se pudo modificar. Verifica el estado del prestamo.\n";
    }
}

// Cancelar préstamo activo
void ModuloPrestamos::cancelarPrestamoPorId() {
    std::string id;
    std::cout << "ID del prestamo a cancelar: ";
    std::cin >> id;

    std::ifstream entrada(rutaArchivoPrestamos);
    std::ofstream salida("data/temp_prestamos.txt");
    std::string linea;
    bool eliminado = false;

    while (getline(entrada, linea)) {
        std::stringstream ss(linea);
        std::string idL;
        getline(ss, idL, '|');

        if (idL != id) {
            salida << linea << "\n";
        } else {
            eliminado = true;
        }
    }

    entrada.close();
    salida.close();

    if (eliminado) {
        std::remove(rutaArchivoPrestamos.c_str());
        std::rename("data/temp_prestamos.txt", rutaArchivoPrestamos.c_str());
        std::cout << " Prestamo eliminado correctamente.\n";
    } else {
        std::remove("data/temp_prestamos.txt");
        std::cout << " No se encontro el prestamo.\n";
    }
}

// Mostrar reporte por consola
void ModuloPrestamos::mostrarReporteEnConsola() {
    std::vector<Prestamo*> prestamos = PrestamoFactory::cargarPrestamosDesdeArchivo(rutaArchivoPrestamos);
    std::cout << "\n📋 REPORTE GENERAL DE PRESTAMOS:\n";
    for (Prestamo* p : prestamos) {
        p->mostrarDetalle();
    }
    for (Prestamo* p : prestamos) delete p;
}

// Exportar reporte a archivo
void ModuloPrestamos::exportarReporteAArchivo() {
    std::ifstream entrada(rutaArchivoPrestamos);
    std::ofstream salida("reportes/reporte_prestamos.txt");
    std::string linea;

    if (!entrada.is_open() || !salida.is_open()) {
        std::cout << " No se pudo abrir los archivos.\n";
        return;
    }

    salida << "ID | Usuario | Recurso | Fecha prestamo | Fecha devolucion | Estado\n";
    salida << "-------------------------------------------------------------------\n";

    while (getline(entrada, linea)) {
        std::stringstream ss(linea);
        std::string id, usuario, recurso, fInicio, fFin, estado;
        getline(ss, id, '|');
        getline(ss, usuario, '|');
        getline(ss, recurso, '|');
        getline(ss, fInicio, '|');
        getline(ss, fFin, '|');
        getline(ss, estado, '|');

        salida << id << "\t" << usuario << "\t" << recurso << "\t"
               << fInicio << "\t" << fFin << "\t" << estado << "\n";
    }

    entrada.close();
    salida.close();
    std::cout << " Reporte exportado en reportes/reporte_prestamos.txt.\n";
}

