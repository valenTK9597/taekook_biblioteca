#include "../../include/notificaciones/SistemaNotificaciones.h"
#include <algorithm>

SistemaNotificaciones::~SistemaNotificaciones() {
    for (auto o : observadores) {
        delete o;
    }
    observadores.clear();
}

void SistemaNotificaciones::agregarObservador(NotificacionObserver* observador) {
    observadores.push_back(observador);
}

void SistemaNotificaciones::eliminarObservador(NotificacionObserver* observador) {
    observadores.erase(std::remove(observadores.begin(), observadores.end(), observador), observadores.end());
}

void SistemaNotificaciones::notificarATodos(const std::string& mensaje) {
    for (auto o : observadores) {
        o->actualizar(mensaje);
    }
}
