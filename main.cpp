#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip> // std::quoted
#include <sstream>
#include <algorithm> // <- Esto permite usar std::find correctamente
#include <ctime>
#include <chrono>


#include "include/usuarios/UsuarioFactory.h"
#include "include/usuarios/Usuario.h"
#include "include/usuarios/Estudiante.h"
#include "include/usuarios/Profesor.h"
#include "include/usuarios/Administrador.h"
#include "include/recursos/RecursoFactory.h"
#include "include/recursos/Recurso.h"
#include "include/prestamos/PrestamoFactory.h"
#include "include/prestamos/Prestamo.h"
#include "include/prestamos/EstadoDevuelto.h"
#include "include/prestamos/EstadoVencido.h"


// Función para cargar usuarios desde archivo
std::vector<Usuario*> cargarUsuariosDesdeArchivo(const std::string& ruta) {
    std::ifstream archivo(ruta);
    std::vector<Usuario*> usuarios;

    if (!archivo.is_open()) {
        std::cerr << "❌ No se pudo abrir el archivo de usuarios.\n";
        return usuarios;
    }

    std::string tipo, id, nombre, correo, contrasena;
    while (!archivo.eof()) {
        archivo >> std::ws;
        if (archivo.peek() == EOF) break;

        archivo >> std::quoted(tipo) >> std::quoted(id) >> std::quoted(nombre)
                >> std::quoted(correo) >> std::quoted(contrasena);

        if (tipo.empty() || id.empty() || correo.empty()) continue;

        Usuario* u = UsuarioFactory::crearUsuario(tipo, id, nombre, correo, contrasena);
        if (u) usuarios.push_back(u);
    }

    archivo.close();
    return usuarios;
}

// Registro de usuario
void registrarUsuario(const std::string& ruta) {
    std::vector<Usuario*> usuarios = cargarUsuariosDesdeArchivo(ruta);
    std::string tipo, id, nombre, correo, contrasena;

    std::cout << "\n📋 Registro de nuevo usuario\n";
    std::cout << "Tipo (Estudiante / Profesor / Administrador): ";
    std::cin >> tipo;

    std::cout << "ID: "; std::cin >> id;
    std::cout << "Nombre: "; std::cin >> nombre;
    std::cout << "Correo: "; std::cin >> correo;

    // Validar correo único
    for (Usuario* u : usuarios) {
        if (u->getCorreo() == correo) {
            std::cout << "❌ Ya existe un usuario con ese correo.\n";
            for (Usuario* x : usuarios) delete x;
            return;
        }
    }

    std::cout << "Contraseña: "; std::cin >> contrasena;

    Usuario* nuevo = UsuarioFactory::crearUsuario(tipo, id, nombre, correo, contrasena);
    if (!nuevo) {
        std::cout << "❌ Tipo de usuario inválido.\n";
        for (Usuario* x : usuarios) delete x;
        return;
    }

    std::ofstream archivo(ruta, std::ios::app);
    if (!archivo.is_open()) {
        std::cout << "❌ No se pudo abrir el archivo para guardar.\n";
        delete nuevo;
        for (Usuario* x : usuarios) delete x;
        return;
    }

    archivo << std::quoted(tipo) << " "
            << std::quoted(id) << " "
            << std::quoted(nombre) << " "
            << std::quoted(correo) << " "
            << std::quoted(contrasena) << "\n";

    archivo.close();
    delete nuevo;
    for (Usuario* x : usuarios) delete x;

    std::cout << "✅ Usuario registrado exitosamente.\n";
}

// Mostrar recursos disponibles
void verRecursosDisponibles() {
    std::vector<Recurso*> recursos = RecursoFactory::cargarRecursosDesdeArchivo("data/recursos.txt");
    std::vector<Prestamo*> prestamos = PrestamoFactory::cargarPrestamosDesdeArchivo("data/prestamos.txt");

    std::vector<std::string> recursosPrestados;
    for (const auto& p : prestamos) {
        if (p->getNombreEstado() == "Prestado") {
            recursosPrestados.push_back(p->getIdRecurso());
        }
    }

    if (recursos.empty()) {
        std::cout << "\n⚠️ No hay recursos cargados.\n";
        return;
    }

    std::cout << "\n📚 Recursos disponibles:\n";
    bool algunoDisponible = false;

    for (const auto& recurso : recursos) {
        if (std::find(recursosPrestados.begin(), recursosPrestados.end(), recurso->getId()) == recursosPrestados.end()) {
            std::cout << " - [" << recurso->getTipo() << "] "
                      << recurso->getTitulo() << " | Autor: "
                      << recurso->getAutor() << "\n";
            algunoDisponible = true;
        }
    }

    if (!algunoDisponible) {
        std::cout << "⚠️ Todos los recursos están prestados actualmente.\n";
    }

    for (auto r : recursos) delete r;
    for (auto p : prestamos) delete p;
}


// Mostrar menú personalizado
void mostrarMenu(Usuario* usuario) {
    std::cout << "\n👤 Bienvenido, " << usuario->getNombre()
              << " (" << usuario->getTipo() << ")\n";

    if (usuario->getTipo() == "Estudiante" || usuario->getTipo() == "Profesor") {
    std::cout << "1. Ver recursos disponibles\n";
    std::cout << "2. Solicitar préstamo\n";
    std::cout << "3. Devolver préstamo\n";
    std::cout << "4. Buscar recursos\n";
    std::cout << "5. Ver recomendaciones\n";
    std::cout << "6. Ver mis préstamos\n";
    std::cout << "7. Ver reservas pendientes\n";
    std::cout << "8. Salir\n";
    } else if (usuario->getTipo() == "Administrador") {
        std::cout << "1. Gestionar usuarios\n";
        std::cout << "2. Gestionar recursos\n";
        std::cout << "3. Ver préstamos\n";
        std::cout << "4. Enviar notificaciones\n";
        std::cout << "5. Salir\n";
    }
}

// Función para iniciar sesión (devuelve copia viva)
Usuario* iniciarSesion(const std::string& rutaUsuarios) {
    std::vector<Usuario*> usuarios = cargarUsuariosDesdeArchivo(rutaUsuarios);

    if (usuarios.empty()) {
        std::cout << "\n Todavía no hay usuarios registrados. Registre uno primero.\n";
        return nullptr;
    }

    std::string correoInput, contrasenaInput;
    std::cout << "\n📥 Inicia sesión\nCorreo: ";
    std::cin >> correoInput;
    std::cout << "Contraseña: ";
    std::cin >> contrasenaInput;

    // Limpiar espacios invisibles
    correoInput.erase(correoInput.find_last_not_of(" \n\r\t") + 1);
    contrasenaInput.erase(contrasenaInput.find_last_not_of(" \n\r\t") + 1);

    Usuario* usuarioEncontrado = nullptr;

    for (Usuario* u : usuarios) {
        if (u->getCorreo() == correoInput && u->getContrasena() == contrasenaInput) {
            usuarioEncontrado = UsuarioFactory::crearUsuario(
                u->getTipo(), u->getId(), u->getNombre(), u->getCorreo(), u->getContrasena()
            );
            break;
        }
    }

    for (Usuario* u : usuarios) delete u;

    return usuarioEncontrado;
}

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

void realizarPrestamoInteractivo(const std::string& idUsuario) {
    std::string idPrestamo, idRecurso, fechaPrestamo, fechaDevolucion;

    std::cout << "\n📋 Solicitud de préstamo\n";
    std::cout << "ID del préstamo: "; std::cin >> idPrestamo;
    std::cout << "ID del recurso: "; std::cin >> idRecurso;
    std::cout << "Fecha de préstamo (YYYY-MM-DD): "; std::cin >> fechaPrestamo;
    std::cout << "Fecha de devolución (YYYY-MM-DD): "; std::cin >> fechaDevolucion;

    // Validar recurso existente
    if (!RecursoFactory::idExistente(idRecurso, "data/recursos.txt")) {
        std::cout << "❌ Recurso no encontrado.\n";
        return;
    }

    if (PrestamoFactory::recursoActualmentePrestado(idRecurso, "data/prestamos.txt")) {
    std::cout << "❌ El recurso ya está prestado. No puede solicitarse de nuevo hasta su devolución.\n";

    // Registrar reserva
    PrestamoFactory::registrarReserva(idUsuario, idRecurso);
    return;
    }

    // Validar préstamo duplicado
    if (PrestamoFactory::idPrestamoExistente(idPrestamo, "data/prestamos.txt")) {
        std::cout << "❌ Ya existe un préstamo con ese ID.\n";
        return;
    }

    // Crear y guardar el préstamo
    Prestamo* nuevo = PrestamoFactory::crearPrestamo(
        idPrestamo, idUsuario, idRecurso, fechaPrestamo, fechaDevolucion, "Prestado"
    );

    PrestamoFactory::guardarPrestamoEnArchivo(nuevo, "data/prestamos.txt");
    std::cout << "✅ Préstamo registrado correctamente.\n";
    delete nuevo;
}

// Función auxiliar para obtener la fecha actual en formato YYYY-MM-DD
std::string obtenerFechaActual() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", now);
    return std::string(buffer);
}

// Comparación de fechas tipo YYYY-MM-DD
bool esFechaPosterior(const std::string& actual, const std::string& limite) {
    return actual > limite;
}

void devolverPrestamoInteractivo(const std::string& idUsuario) {
    std::string idPrestamo;
    std::cout << "\n🔄 Devolución de recurso\n";
    std::cout << "Ingrese el ID del préstamo a devolver: ";
    std::cin >> idPrestamo;

    std::vector<Prestamo*> prestamos = PrestamoFactory::cargarPrestamosDesdeArchivo("data/prestamos.txt");
    bool encontrado = false;
    std::string idRecurso;
    std::string fechaDevolucion;
    std::string nuevoEstado;

    for (Prestamo* p : prestamos) {
        if (p->getIdPrestamo() == idPrestamo && p->getIdUsuario() == idUsuario) {
            idRecurso = p->getIdRecurso();
            fechaDevolucion = p->getFechaDevolucion();
            std::string fechaActual = obtenerFechaActual();

           if (esFechaPosterior(fechaActual, fechaDevolucion)) {
                std::cout << "⚠️ Este préstamo fue devuelto con retraso.\n";
    
                // Calcular y mostrar multa
                Recurso* recurso = RecursoFactory::obtenerRecursoPorId(idRecurso, "data/recursos.txt");
                if (recurso) {
                    int diasRetraso = calcularDiasRetraso(fechaDevolucion, fechaActual);
                    double multa = recurso->calcularMulta(diasRetraso);
                    std::cout << "💰 Multa por " << diasRetraso << " días de retraso: $" << multa << "\n";
                    delete recurso;
                } else {
                    std::cout << "⚠️ No se pudo encontrar el recurso para calcular multa.\n";
                }
                    p->setEstado(new EstadoVencido());
                } else {
                    p->setEstado(new EstadoDevuelto());
                }
        encontrado = true;
        break;
    }
}

    if (!encontrado) {
        std::cout << "❌ No se encontró el préstamo con ese ID.\n";
        for (Prestamo* p : prestamos) delete p;
        return;
    }

    std::ofstream archivo("data/prestamos.txt");
    if (!archivo.is_open()) {
        std::cerr << "❌ Error al actualizar el archivo de préstamos.\n";
        return;
    }

    for (Prestamo* p : prestamos) {
        archivo << p->getIdPrestamo() << "|"
                << p->getIdUsuario() << "|"
                << p->getIdRecurso() << "|"
                << p->getFechaPrestamo() << "|"
                << p->getFechaDevolucion() << "|"
                << p->getNombreEstado() << "\n";
    }

    archivo.close();
    std::cout << "✅ Recurso devuelto correctamente.\n";

    for (Prestamo* p : prestamos) delete p;
}



// Ver préstamos de un usuario

void verPrestamosUsuario(const std::string& idUsuario) {
    std::vector<Prestamo*> prestamos = PrestamoFactory::cargarPrestamosDesdeArchivo("data/prestamos.txt");

    bool tienePrestamos = false;
    std::cout << "\n📄 Préstamos realizados:\n";

    for (Prestamo* p : prestamos) {
        if (p->getIdUsuario() == idUsuario) {
            std::cout << "🔸 ID Préstamo: " << p->getIdPrestamo()
                      << " | Recurso: " << p->getIdRecurso()
                      << " | Estado: " << p->getNombreEstado()
                      << " | Desde: " << p->getFechaPrestamo()
                      << " hasta: " << p->getFechaDevolucion() << "\n";
            tienePrestamos = true;
        }
    }

    if (!tienePrestamos) {
        std::cout << "⚠️ No se encontraron préstamos para este usuario.\n";
    }

    for (Prestamo* p : prestamos) delete p;
}

void verReservasPendientes(const std::string& idUsuario) {
    PrestamoFactory::mostrarReservasDelUsuario(idUsuario);

    std::string respuesta;
    std::cout << "\n¿Deseas cancelar alguna reserva? (s/n): ";
    std::cin >> respuesta;

    if (respuesta == "s" || respuesta == "S") {
        std::string idRecursoCancelar;
        std::cout << "Ingresa el ID del recurso que deseas cancelar: ";
        std::cin >> idRecursoCancelar;

        PrestamoFactory::cancelarReserva(idUsuario, idRecursoCancelar);
    }
}

void cancelarPrestamoPorAdministrador() {
    std::string idCancelar;
    std::cout << "\n❌ Cancelar préstamo\n";
    std::cout << "Ingrese el ID del préstamo a cancelar: ";
    std::cin >> idCancelar;

    std::ifstream archivoEntrada("data/prestamos.txt");
    std::ofstream archivoTemporal("data/temp_prestamos.txt");
    bool encontrado = false;
    std::string linea;

    while (getline(archivoEntrada, linea)) {
        std::stringstream ss(linea);
        std::string id;
        getline(ss, id, '|');

        if (id != idCancelar) {
            archivoTemporal << linea << "\n";
        } else {
            encontrado = true;
        }
    }

    archivoEntrada.close();
    archivoTemporal.close();

    if (encontrado) {
        std::remove("data/prestamos.txt");
        std::rename("data/temp_prestamos.txt", "data/prestamos.txt");
        std::cout << "✅ Préstamo cancelado exitosamente.\n";
    } else {
        std::remove("data/temp_prestamos.txt");
        std::cout << "❌ No se encontró el préstamo con ese ID.\n";
    }
}

void mostrarReportePrestamosEnConsola() {
    std::vector<Prestamo*> prestamos = PrestamoFactory::cargarPrestamosDesdeArchivo("data/prestamos.txt");

    if (prestamos.empty()) {
        std::cout << "⚠️ No hay préstamos registrados.\n";
        return;
    }

    std::cout << "\n📋 REPORTE GENERAL DE PRÉSTAMOS:\n";
    std::cout << "--------------------------------------\n";

    for (Prestamo* p : prestamos) {
        std::cout << "ID Préstamo:     " << p->getIdPrestamo() << "\n";
        std::cout << "ID Usuario:      " << p->getIdUsuario() << "\n";
        std::cout << "ID Recurso:      " << p->getIdRecurso() << "\n";
        std::cout << "Fecha Préstamo:  " << p->getFechaPrestamo() << "\n";
        std::cout << "Fecha Devolución:" << p->getFechaDevolucion() << "\n";
        std::cout << "Estado:          " << p->getNombreEstado() << "\n";
        std::cout << "--------------------------------------\n";
    }

    for (Prestamo* p : prestamos) delete p;
}


void forzarDevolucionPorAdministrador() {
    std::string idPrestamo;
    std::cout << "\n🔐 Forzar devolución\n";
    std::cout << "Ingrese el ID del préstamo: ";
    std::cin >> idPrestamo;

    std::vector<Prestamo*> prestamos = PrestamoFactory::cargarPrestamosDesdeArchivo("data/prestamos.txt");
    bool encontrado = false;

    for (Prestamo* p : prestamos) {
        if (p->getIdPrestamo() == idPrestamo) {
            encontrado = true;

            std::cout << "\n📄 Detalle del préstamo:\n";
            p->mostrarDetalle();

            if (p->getNombreEstado() == "Devuelto") {
                std::cout << "⚠️ Este préstamo ya está marcado como devuelto.\n";
                break;
            }

            std::cout << "\n📨 Se simula el envío de notificación al usuario.\n";
            std::cout << "¿Deseas confirmar manualmente la devolución?\n";
            std::cout << "1. Sí, marcar como devuelto\n";
            std::cout << "2. No, dejar pendiente\n";
            int decision;
            std::cin >> decision;

            if (decision == 1) {
                p->setEstado(new EstadoDevuelto());
                std::cout << "✅ Préstamo marcado como devuelto exitosamente.\n";
            } else {
                std::cout << "🔄 Devolución pendiente. No se han realizado cambios.\n";
            }

            break;
        }
    }

    if (!encontrado) {
        std::cout << "❌ No se encontró un préstamo con ese ID.\n";
    }

    // Guardar cambios
    std::ofstream archivo("data/prestamos.txt");
    for (Prestamo* p : prestamos) {
        archivo << p->getIdPrestamo() << "|"
                << p->getIdUsuario() << "|"
                << p->getIdRecurso() << "|"
                << p->getFechaPrestamo() << "|"
                << p->getFechaDevolucion() << "|"
                << p->getNombreEstado() << "\n";
    }
    archivo.close();

    for (Prestamo* p : prestamos) delete p;
}

// Función para gestionar préstamos como administrador
void gestionarPrestamosAdministrador() {
    bool continuar = true;

    while (continuar) {
        std::cout << "\n Gestión de préstamos\n";
        std::cout << "1. Ver todos los préstamos\n";
        std::cout << "2. Buscar préstamo por ID de usuario\n";
        std::cout << "3. Buscar préstamo por ID de recurso\n";
        std::cout << "4. Forzar devolución de préstamo\n";
        std::cout << "5. Cancelar un préstamo activo\n";
        std::cout << "6. Ver reporte de préstamos\n";
        std::cout << "7. Volver al menú principal\n";


        int opcion;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        std::vector<Prestamo*> prestamos = PrestamoFactory::cargarPrestamosDesdeArchivo("data/prestamos.txt");

        if (opcion == 1) {
            std::cout << "\n📄 Todos los préstamos registrados:\n";
            for (Prestamo* p : prestamos) {
                p->mostrarDetalle();
            }
        } else if (opcion == 2) {
            std::string idUsuario;
            std::cout << "Ingrese el ID del usuario: ";
            std::cin >> idUsuario;
            bool encontrado = false;
            for (Prestamo* p : prestamos) {
                if (p->getIdUsuario() == idUsuario) {
                    p->mostrarDetalle();
                    encontrado = true;
                }
            }
            if (!encontrado) std::cout << "❌ No se encontraron préstamos para ese usuario.\n";
        } else if (opcion == 3) {
            std::string idRecurso;
            std::cout << "Ingrese el ID del recurso: ";
            std::cin >> idRecurso;
            bool encontrado = false;
            for (Prestamo* p : prestamos) {
                if (p->getIdRecurso() == idRecurso) {
                    p->mostrarDetalle();
                    encontrado = true;
                }
            }
            if (!encontrado) std::cout << "❌ No se encontraron préstamos para ese recurso.\n";
        } else if (opcion == 4) {
            forzarDevolucionPorAdministrador();
        } else if (opcion == 5) {
            cancelarPrestamoPorAdministrador();
        } else if (opcion == 6) {
            mostrarReportePrestamosEnConsola();
        } else if (opcion == 7) {
            continuar = false;
        } else {
            std::cout << "⚠️ Opcion inválida.\n";
        }


        for (Prestamo* p : prestamos) delete p;
    }
}



int main() {
    const std::string rutaUsuarios = "data/usuarios.txt";
    Usuario* usuarioActivo = nullptr;

    while (true) {
        std::cout << "\n📚 Sistema de Biblioteca Virtual\n";
        std::cout << "1. Iniciar sesión\n";
        std::cout << "2. Registrarse\n";
        std::cout << "3. Salir\n";

        int opcion;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
//++++++++++++++++++++++
        
if (opcion == 1) {
    usuarioActivo = iniciarSesion(rutaUsuarios);

    if (!usuarioActivo) {
    std::cout << "❌ Usuario o contraseña incorrectos.\n";
    continue;
}

    bool continuarSesion = true;
    while (continuarSesion) {
        mostrarMenu(usuarioActivo);

        int opcionUsuario;
        std::cout << "\nSeleccione una opción: ";
        std::cin >> opcionUsuario;

        if (usuarioActivo->getTipo() == "Estudiante" || usuarioActivo->getTipo() == "Profesor") {
            if (opcionUsuario == 1) {
                verRecursosDisponibles();
            } else if (opcionUsuario == 2) {
                realizarPrestamoInteractivo(usuarioActivo->getId());
            } else if (opcionUsuario == 3) {
                devolverPrestamoInteractivo(usuarioActivo->getId());
            } else if (opcionUsuario == 6) {
                verPrestamosUsuario(usuarioActivo->getId());
            } else if (opcionUsuario == 7) {
                verReservasPendientes(usuarioActivo->getId());
            } else if (opcionUsuario == 8) {
                std::cout << "👋 Sesión finalizada.\n";
                continuarSesion = false;
            } else {
                std::cout << "⚠️ Opción inválida.\n";
            }
        } else if (usuarioActivo->getTipo() == "Administrador") {
            if (opcionUsuario == 1) {
            // Aquí iría gestionarUsuarios(); si lo implementas
            } else if (opcionUsuario == 2) {
            // Aquí iría gestionarRecursos(); si lo implementas
            } else if (opcionUsuario == 3) {
                gestionarPrestamosAdministrador(); // NUEVA FUNCIÓN
            } else if (opcionUsuario == 4) {
                // Aquí iría enviarNotificaciones(); si se implementa
            } else if (opcionUsuario == 5) {
                std::cout << "👋 Sesión finalizada.\n";
                continuarSesion = false;
            } else {
                std::cout << "⚠️ Opción inválida.\n";
            }
        }
    }

    delete usuarioActivo;
    usuarioActivo = nullptr;
}


        else if (opcion == 2) {
            registrarUsuario(rutaUsuarios);
        }

        else if (opcion == 3) {
            std::cout << "👋 Hasta pronto.\n";
            break;
        }

        else {
            std::cout << "❌ Opción no válida. Intente de nuevo.\n";
        }
    }

    return 0;
}