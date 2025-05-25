#ifndef SISTEMANOTIFICACIONES_H
#define SISTEMANOTIFICACIONES_H

#include "NotificacionObserver.h"
#include <vector>
#include <string>

class SistemaNotificaciones {
private:
    std::vector<NotificacionObserver*> observadores;

public:
    ~SistemaNotificaciones();

    void agregarObservador(NotificacionObserver* observador);
    void eliminarObservador(NotificacionObserver* observador);
    void notificarATodos(const std::string& mensaje);
};

#endif
