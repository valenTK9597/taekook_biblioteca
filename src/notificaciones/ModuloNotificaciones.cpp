#include "../../include/notificaciones/ModuloNotificaciones.h"
#include "../../include/usuarios/UsuarioFactory.h"
#include "../../include/prestamos/ModuloPrestamos.h"
#include "../../include/notificaciones/GestorNotificacionesArchivo.h"
#include "../../include/notificaciones/SistemaNotificaciones.h"
#include "../../include/notificaciones/UsuarioObserver.h"
#include "../../include/recursos/RecursoFactory.h"
#include "../../include/prestamos/PrestamoFactory.h"
#include "utils/Utilidades.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <vector>


// Verifica si es administrador
bool ModuloNotificaciones::esAdministrador(const std::string& tipo) const {
    return tipo == "Administrador";
}

ModuloNotificaciones::ModuloNotificaciones() {
    // Constructor vacío o inicialización interna
}


// Constructor
ModuloNotificaciones::ModuloNotificaciones(const std::string& rutaUsuarios)
    : rutaArchivoUsuarios(rutaUsuarios) {}


// Obtener ruta completa para el canal y usuario
std::string ModuloNotificaciones::obtenerRutaNotificacion(const std::string& canal, const std::string& idUsuario) const {
    return rutaBase + canal + "_" + idUsuario + ".txt";
}

// Mostrar notificaciones según canal
void ModuloNotificaciones::verNotificacionesUsuario(const std::string& idUsuario, const std::string& canal) const {
    std::cout << "\n🔔 Notificaciones por " << canal << ":\n";

    std::vector<std::string> mensajes = GestorNotificacionesArchivo::leerMensajes(idUsuario, canal);

    if (mensajes.empty()) {
        std::cout << " No tienes notificaciones recientes en este canal.\n";
        return;
    }

    for (const std::string& linea : mensajes) {
        std::cout << " • " << linea << "\n";
    }
}


void ModuloNotificaciones::gestionarNotificacionesUsuario(const std::string& idUsuario, ModuloPrestamos& moduloPrestamos) {
    Usuario* usuario = UsuarioFactory::obtenerUsuarioPorId(idUsuario, rutaArchivoUsuarios);
    std::string tipo = usuario->getTipo();

    bool gestionando = true;
    while (gestionando) {
        std::cout << "\n🔔 Submenú de Notificaciones (" << tipo << "):\n";

        // Menú dinámico según tipo de usuario
        if (tipo == "Estudiante" || tipo == "Profesor") {
            std::cout << "1. Ver en la aplicación\n";
            std::cout << "2. Ver por correo (email)\n";
            std::cout << "3. Ver por SMS\n";
            std::cout << "4. Ver recordatorios de devolución\n";
            std::cout << "5. Volver\n";
        } else if (tipo == "Administrador") {
            std::cout << "1. Ver en la aplicación\n";
            std::cout << "2. Ver por correo (email)\n";
            std::cout << "3. Ver por SMS\n";
            std::cout << "4. Enviar notificación manual a un usuario\n";
            std::cout << "5. Enviar recordatorios de devolución a todos los usuarios\n";
            std::cout << "6. Enviar advertencia devolucion vencida a un usuario\n";
            std::cout << "7. Volver\n";
        } else {
            std::cout << "❌ Tipo de usuario no reconocido.\n";
            return;
        }

        int opcion;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        // Ejecutar acciones según tipo
        if (tipo == "Estudiante" || tipo == "Profesor") {
            switch (opcion) {
                case 1:
                    verNotificacionesUsuario(idUsuario, "app");
                    break;
                case 2:
                    verNotificacionesUsuario(idUsuario, "email");
                    break;
                case 3:
                    verNotificacionesUsuario(idUsuario, "sms");
                    break;
                case 4:
                    enviarRecordatoriosDevolucionPorUsuario(idUsuario, moduloPrestamos);
                    break;
                case 5:
                    gestionando = false;
                    break;
                default:
                    std::cout << "❌ Opción inválida.\n";
            }
        } else if (tipo == "Administrador") {
            switch (opcion) {
                case 1:
                    verNotificacionesUsuario(idUsuario, "app");
                    break;
                case 2:
                    verNotificacionesUsuario(idUsuario, "email");
                    break;
                case 3:
                    verNotificacionesUsuario(idUsuario, "sms");
                    break;
                case 4:
                    enviarNotificacionManual(idUsuario);  // Ya implementado
                    break;
                case 5:
                    enviarRecordatoriosDevolucion("data/prestamos.txt", rutaArchivoUsuarios);  // Para todos los usuarios
                    break;
                case 6:
                    enviarAdvertenciasGravesPorVencimiento("data/prestamos.txt", rutaArchivoUsuarios);
                    break;
                case 7:
                    gestionando = false;
                    break;
                default:
                    std::cout << "❌ Opción inválida.\n";
            }
        }
    }
}

void ModuloNotificaciones::enviarNotificacionManual(const std::string& idRemitente) {
    Usuario* remitente = UsuarioFactory::obtenerUsuarioPorId(idRemitente, rutaArchivoUsuarios);
    if (!remitente) {
        std::cout << "❌ No se pudo obtener el remitente.\n";
        return;
    }

    std::string tipoRemitente = remitente->getTipo();
    std::string idDestino;

    std::cout << "\n✉️ Enviar notificación\n";

    if (esAdministrador(tipoRemitente)) {
        std::cout << "ID del usuario destino: ";
        std::cin >> idDestino;
    } else {
        std::cout << "🔐 Solo puedes enviar notificaciones a administradores.\n";
        std::vector<Usuario*> usuarios = UsuarioFactory::cargarUsuariosDesdeArchivo(rutaArchivoUsuarios);
        for (Usuario* u : usuarios) {
            if (u->getTipo() == "Administrador") {
                idDestino = u->getId();
                break;
            }
        }
        for (Usuario* u : usuarios) delete u;

        if (idDestino.empty()) {
            std::cout << "⚠️ No hay administradores registrados.\n";
            delete remitente;
            return;
        }
    }

    Usuario* receptor = UsuarioFactory::obtenerUsuarioPorId(idDestino, rutaArchivoUsuarios);
    if (!receptor) {
        std::cout << "❌ Usuario destino no encontrado.\n";
        delete remitente;
        return;
    }

    std::cin.ignore();
    std::string mensaje;
    std::cout << "Escriba el mensaje: ";
    std::getline(std::cin, mensaje);

    std::cout << "Seleccione el canal (app/email/sms): ";
    std::string canal;
    std::getline(std::cin, canal);

    if (!canalValido(canal)) {
        std::cout << "❌ Canal inválido. Usa: app, email o sms.\n";
        delete remitente;
        delete receptor;
        return;
    }

    std::string mensajeFormateado = "(De: " + remitente->getNombre() + ") " + mensaje;

    GestorNotificacionesArchivo::guardarMensaje(idDestino, mensajeFormateado, canal);
    std::cout << "✅ Notificación enviada por " << canal << ".\n";

    delete remitente;
    delete receptor;
}


void procesarRecordatorios(const std::vector<Prestamo*>& prestamos, const std::string& rutaArchivoUsuarios, const std::string& idFiltrado = "") {
    std::string hoy = obtenerFechaActual();
    bool enviados = false;

    for (Prestamo* p : prestamos) {
        if (p->getNombreEstado() != "Prestado") continue;
        if (!idFiltrado.empty() && p->getIdUsuario() != idFiltrado) continue;

        int dias = calcularDiasEntre(hoy, p->getFechaDevolucion());
        
        if (dias >= 0 && dias <= 2) {
            Usuario* usuario = UsuarioFactory::obtenerUsuarioPorId(p->getIdUsuario(), rutaArchivoUsuarios);
            if (usuario) {
                std::stringstream mensaje;
                mensaje << "📅 Recordatorio: tu préstamo con ID " << p->getIdPrestamo()
                        << " vence en " << dias << " día(s).";
                GestorNotificacionesArchivo::guardarMensaje(usuario->getId(), mensaje.str(), "app");
                GestorNotificacionesArchivo::guardarMensaje(usuario->getId(), mensaje.str(), "email");
                GestorNotificacionesArchivo::guardarMensaje(usuario->getId(), mensaje.str(), "sms");
                std::cout << "📧 Email a " << usuario->getCorreo() << ": " << mensaje.str() << "\n";
                std::cout << "📱 SMS a " << usuario->getCorreo() << ": " << mensaje.str() << "\n";
                enviados = true;
                delete usuario;
            }
        }
    }

    if (!enviados) {
        std::cout << "✅ No hay préstamos próximos a vencer.\n";
    } else {
        std::cout << "✅ Recordatorios generados correctamente.\n";
    }
}


void ModuloNotificaciones::enviarRecordatoriosDevolucion(const std::string& rutaArchivoPrestamos, const std::string& rutaArchivoUsuarios) {
    std::vector<Prestamo*> prestamos = PrestamoFactory::cargarPrestamosDesdeArchivo(rutaArchivoPrestamos);
    procesarRecordatorios(prestamos, rutaArchivoUsuarios);
    for (Prestamo* p : prestamos) delete p;
}


void ModuloNotificaciones::enviarRecordatoriosDevolucionPorUsuario(const std::string& idUsuario, ModuloPrestamos& moduloPrestamos) {
    std::vector<Prestamo*> prestamos = PrestamoFactory::cargarPrestamosDesdeArchivo("data/prestamos.txt");
    procesarRecordatorios(prestamos, rutaArchivoUsuarios, idUsuario);
    for (Prestamo* p : prestamos) delete p;
}

void ModuloNotificaciones::notificarDevolucionConRetraso(const std::string& idUsuario) {
    std::string mensaje = "⚠️ Has devuelto un préstamo vencido. Multa aplicada.";
    GestorNotificacionesArchivo::guardarMensaje(idUsuario, mensaje, "app");
    GestorNotificacionesArchivo::guardarMensaje(idUsuario, mensaje, "email");
    GestorNotificacionesArchivo::guardarMensaje(idUsuario, mensaje, "sms");
    std::cout << "📧 Enviando email a usuario: " << mensaje << "\n";
    std::cout << "📱 Enviando SMS: " << mensaje << "\n";
    
}

void ModuloNotificaciones::notificarDevolucionExitosa(const std::string& idUsuario) {
    std::string mensaje = "📚 Has devuelto correctamente un recurso.";
    GestorNotificacionesArchivo::guardarMensaje(idUsuario, mensaje, "app");
    GestorNotificacionesArchivo::guardarMensaje(idUsuario, mensaje, "email");
    GestorNotificacionesArchivo::guardarMensaje(idUsuario, mensaje, "sms");
    std::cout << "📧 Enviando email a usuario: " << mensaje << "\n";
    std::cout << "📱 Enviando SMS: " << mensaje << "\n";
 
}

void ModuloNotificaciones::notificarReservaDisponible(const std::vector<std::string>& usuarios, const std::string& idRecurso) {
    std::string mensaje = "🔔 El recurso que reservaste ya está disponible. Puedes solicitar el préstamo.";
    for (const std::string& uid : usuarios) {
        Usuario* u = UsuarioFactory::obtenerUsuarioPorId(uid, rutaArchivoUsuarios);
        if (u) {
            std::cout << "📧 Email a " << u->getCorreo() << ": " << mensaje << "\n";
            std::cout << "📱 SMS a " << u->getCorreo() << ": " << mensaje << "\n";

            GestorNotificacionesArchivo::guardarMensaje(uid, mensaje, "app");
            GestorNotificacionesArchivo::guardarMensaje(uid, mensaje, "email");
            GestorNotificacionesArchivo::guardarMensaje(uid, mensaje, "sms");
            std::cout << "✅ Notificación enviada a " << u->getNombre() << ".\n";
        
            delete u;
        }
    }
}



void ModuloNotificaciones::enviarAdvertenciasGravesPorVencimiento(const std::string& rutaArchivoPrestamos, const std::string& rutaArchivoUsuarios) {
    std::vector<Prestamo*> prestamos = PrestamoFactory::cargarPrestamosDesdeArchivo(rutaArchivoPrestamos);
    std::string hoy = obtenerFechaActual();
    bool enviadas = false;

    for (Prestamo* p : prestamos) {
        if (p->getNombreEstado() != "Prestado") continue;

        int diasRetraso = calcularDiasEntre(p->getFechaDevolucion(), hoy);
        if (diasRetraso > 0) {
            std::string uid = p->getIdUsuario();
            std::string rid = p->getIdRecurso();

            std::stringstream mensaje;
            mensaje << "⚠️ Advertencia Grave: El recurso con ID " << rid
                    << " fue devuelto con un retraso de " << diasRetraso << " día(s).";

            // Canales estándar
            GestorNotificacionesArchivo::guardarMensaje(uid, mensaje.str(), "app");
            GestorNotificacionesArchivo::guardarMensaje(uid, mensaje.str(), "email");
            GestorNotificacionesArchivo::guardarMensaje(uid, mensaje.str(), "sms");

            std::cout << "🚨 Advertencia enviada a " << uid << " por retraso de " << diasRetraso << " días.\n";
            enviadas = true;
        }
    }

    for (Prestamo* p : prestamos) delete p;

    if (!enviadas)
        std::cout << "✅ No hay préstamos vencidos actualmente.\n";
    else
        std::cout << "✅ Advertencias graves enviadas correctamente.\n";
}




