#include "../../include/notificaciones/GestorNotificacionesArchivo.h"
#include <fstream>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <ctime>

void GestorNotificacionesArchivo::guardarMensaje(const std::string& idUsuario, const std::string& mensaje) {
    std::string ruta = "data/notificaciones/notificaciones_" + idUsuario + ".txt";

    // Crear directorio si no existe
    std::filesystem::create_directories("data/notificaciones");

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
