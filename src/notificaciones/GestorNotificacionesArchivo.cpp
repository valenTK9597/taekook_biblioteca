#include "../../include/notificaciones/GestorNotificacionesArchivo.h"
#include <fstream>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <iostream>
#include <vector>

std::vector<std::string> GestorNotificacionesArchivo::leerMensajes(const std::string& idUsuario, const std::string& canal) {
    std::vector<std::string> mensajes;
    std::string ruta = "data/notificaciones/" + canal + "/" + idUsuario + ".txt";
    std::ifstream archivo(ruta);

    if (!archivo.is_open()) return mensajes;

    std::string linea;
    while (getline(archivo, linea)) {
        mensajes.push_back(linea);
    }

    archivo.close();
    return mensajes;
}


void GestorNotificacionesArchivo::guardarMensaje(const std::string& idUsuario, const std::string& mensaje, const std::string& canal) {
    // Generar la ruta del archivo según el canal
    std::string directorio = "data/notificaciones/" + canal;
    std::string ruta = directorio + "/" + idUsuario + ".txt";

    // Crear directorio del canal si no existe
    std::filesystem::create_directories(directorio);

    std::ofstream archivo(ruta, std::ios::app);  // Abrir en modo append
    if (archivo.is_open()) {
        // Obtener fecha y hora actual
        auto ahora = std::chrono::system_clock::now();
        std::time_t tiempoActual = std::chrono::system_clock::to_time_t(ahora);
        std::tm* fechaHora = std::localtime(&tiempoActual);

        // Escribir la marca de tiempo y el mensaje
        archivo << "[" << std::put_time(fechaHora, "%Y-%m-%d %H:%M:%S") << "] " << mensaje << "\n";
        archivo.close();
    }
}

