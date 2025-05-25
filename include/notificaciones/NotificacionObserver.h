#ifndef NOTIFICACIONOBSERVER_H
#define NOTIFICACIONOBSERVER_H

#include <string>

class NotificacionObserver {
public:
    virtual ~NotificacionObserver() = default;

    // Método que debe implementar todo observador
    virtual void actualizar(const std::string& mensaje) = 0;
};

#endif
