#include "../../include/notificaciones/ModuloNotificaciones.h"
#include "../../include/usuarios/UsuarioFactory.h"

#include <fstream>
#include <iostream>
#include <sstream>

// Constructor
ModuloNotificaciones::ModuloNotificaciones(const std::string& rutaUsuarios)
    : rutaArchivoUsuarios(rutaUsuarios) {}

// Obtener ruta completa para el canal y usuario
std::string ModuloNotificaciones::obtenerRutaNotificacion(const std::string& canal, const std::string& idUsuario) const {
    return rutaBase + canal + "_" + idUsuario + ".txt";
}

// Mostrar notificaciones según canal
void ModuloNotificaciones::verNotificacionesUsuario(const std::string& idUsuario, const std::string& canal) const {
    std::string ruta = obtenerRutaNotificacion(canal, idUsuario);
    std::ifstream archivo(ruta);

    std::cout << "\n🔔 Notificaciones (" << canal << "):\n";

    if (!archivo.is_open()) {
        std::cout << " No tienes notificaciones recientes en este canal.\n";
        return;
    }

    std::string linea;
    bool hayContenido = false;

    while (getline(archivo, linea)) {
        std::cout << " - " << linea << "\n";
        hayContenido = true;
    }

    if (!hayContenido) {
        std::cout << " No tienes notificaciones recientes en este canal.\n";
    }

    archivo.close();
}

// Submenú interactivo
void ModuloNotificaciones::gestionarNotificacionesUsuario(const std::string& idUsuario) {
    bool gestionando = true;
    while (gestionando) {
        std::cout << "\n🔔 Submenú de Notificaciones:\n";
        std::cout << "1. Ver en la aplicación\n";
        std::cout << "2. Ver por correo (email)\n";
        std::cout << "3. Ver por SMS\n";
        std::cout << "4. Enviar notificación manual\n";
        std::cout << "5. Volver\n";

        int opcion;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();

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
                enviarNotificacionManual(idUsuario);
                break;
            case 5:
                gestionando = false;
                break;
            default:
                std::cout << "❌ Opción inválida.\n";
        }
    }
}

// Enviar mensaje con selección de canal
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

    std::string ruta = obtenerRutaNotificacion(canal, idDestino);
    std::ofstream archivo(ruta, std::ios::app);

    if (archivo.is_open()) {
        archivo << "(De: " << remitente->getNombre() << ") " << mensaje << "\n";
        std::cout << "✅ Notificación enviada por " << canal << ".\n";
        archivo.close();
    } else {
        std::cout << "❌ No se pudo abrir el archivo de notificaciones del canal.\n";
    }

    delete remitente;
    delete receptor;
}

// Verifica si es administrador
bool ModuloNotificaciones::esAdministrador(const std::string& tipo) const {
    return tipo == "Administrador";
}
