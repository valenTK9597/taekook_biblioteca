#include "../../include/notificaciones/UsuarioObserver.h"

UsuarioObserver::UsuarioObserver(const std::string& correo) : correo(correo) {}

void UsuarioObserver::actualizar(const std::string& mensaje) {
    std::cout << "📧 Enviando mensaje a " << correo << ": " << mensaje << "\n";
}
