# taekook_biblioteca
Sistema de gestión de biblioteca digital (C++)

Sistema de Gestión Bibliotecaria Digital – Taekook_Biblioteca

🧩 Descripción General

Taekook_Biblioteca es un sistema modular de gestión bibliotecaria diseñado con fines educativos y prácticos, que permite aplicar y afianzar conceptos de Programación Orientada a Objetos (POO), patrones de diseño, y diseño de software escalable.

Este proyecto fue desarrollado en C++ desde cero, siguiendo un enfoque profesional que divide el sistema en módulos funcionales separados, cada uno con su propia lógica, estructura y responsabilidad definida. Se utiliza una simulación de base de datos a través de archivos .txt, lo que permite conservar la persistencia de datos sin depender de tecnologías externas.

🛠️ Tecnologías y Herramientas

Lenguaje: C++ (estándar 11+)
IDE recomendado: Visual Studio Code
Control de versiones: Git + GitHub
Persistencia de datos: Archivos .txt ubicados en /data
Entorno de construcción: g++, tareas en tasks.json
Sistema Operativo objetivo: multiplataforma

🎯 Objetivos de Aprendizaje

Este proyecto tiene como propósito:
Aplicar los principios de POO: encapsulamiento, herencia, polimorfismo, abstracción.
Comprender y utilizar patrones de diseño en situaciones reales:
Factory Method para la creación dinámica de usuarios y recursos.
Strategy en el módulo de recomendaciones.
Principio de Responsabilidad Única aplicado a cada clase y archivo.
Estructurar un proyecto real de software utilizando diseño modular y mantenible.
Simular una base de datos persistente sin romper la arquitectura orientada a objetos.
Utilizar herramientas de desarrollo colaborativo como Git y GitHub.

📦 Módulos Principales

Cada módulo fue diseñado para tener una única responsabilidad clara y encapsular tanto su lógica como sus datos. A continuación se describen brevemente:

🔐 Módulo Usuario

Registra y autentica usuarios (Estudiantes, Profesores, Administradores).
Usa Factory Method para instanciar dinámicamente según tipo.
Persistencia en usuarios.txt.

📖 Módulo Recurso

Gestiona libros, ebooks, artículos y revistas.
Validación de duplicados, eliminación, búsqueda.
Simula inventario en recursos.txt.

🔄 Módulo Préstamo

Administra préstamos y devoluciones.
Cálculo de fechas de vencimiento.
Actualiza prestamos.txt y lanza notificaciones si corresponde.

🔔 Módulo Notificaciones

Envia mensajes por tres canales simulados: app, email, sms.
Notifica recordatorios, retrasos, disponibilidad de reservas.
Muestra historial de notificaciones por usuario.

🤖 Módulo Recomendaciones

Implementa el patrón Strategy para cambiar dinámicamente el tipo de recomendación.
Usa criterios como tipo de usuario, historial, autor y popularidad.
Información extraída de prestamos.txt y recursos.txt.

