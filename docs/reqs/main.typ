#import "@local/unrn-template:1.0.0": proyecto

#show: proyecto.with(
  titulo: "Nano-Kernel Bare-Metal para RP2040",
  subtitulo: "Requerimientos",
  indice: true,
  fuente: "IBM Plex Sans",
  caratula: true,
  autores: ("Matías Cajal",),
  materia: "Laboratorio de Sistemas Embebidos",
  carrera: "Ingeniería en Computación",
  año: "2025",
  fecha: "12 de Abril de 2025",
  version: "1.0",
)

#set heading(numbering: "1.1)")
#show heading.where(level: 3): set text(weight: "regular")
#show heading.where(level: 4): set text(weight: "regular")
#show heading.where(level: 5): set text(weight: "regular")
#show heading.where(level: 6): set text(weight: "regular")

#let indent-amount = 1.5em

// 1. Define un estado para rastrear el nivel del encabezado actual (para los párrafos).
#let heading-level-state = state("current-heading-level", 0)

// 2. Regla show para encabezados: Actualiza estado E INDENTA el propio encabezado.
#show heading: it => {
  // Obtenemos el nivel de ESTE encabezado.
  let current_heading_level = it.level

  // Actualizamos el estado para que los párrafos siguientes sepan el nivel.
  heading-level-state.update(current_heading_level)

  // Calculamos la indentación para el propio encabezado.
  // (Nivel 1 tiene 0 indent, Nivel 2 tiene 1*indent-amount, etc.)
  let heading_indent = if current_heading_level > 1 {
    (current_heading_level - 1) * indent-amount
  } else {
    0em
  }

  // Aplicamos la indentación al encabezado usando un bloque.
  // Es importante que esto ocurra DESPUÉS de actualizar el estado.
  block(
    inset: (left: heading_indent),
    width: 100%
  )[#it] // Mostramos el contenido original del encabezado dentro del bloque indentado.
}

// 3. Regla show para párrafos: Indenta basándose en el estado (establecido por el encabezado anterior).
#show par: it => {
  // Usamos 'context' como requería el error anterior.
  context {
    // Obtenemos el nivel establecido por el encabezado más reciente.
    let level_for_paragraph = heading-level-state.get()

    // Calculamos la indentación para el párrafo.
    let paragraph_indent = if level_for_paragraph > 1 {
      (level_for_paragraph - 1) * indent-amount
    } else {
      0em
    }

    // Aplicamos la indentación al párrafo.
    block(
      inset: (left: paragraph_indent),
      width: 100%
    )[#it] // Mostramos el contenido original del párrafo.
  }
}


= Presentación

Este proyecto se enmarca en la necesidad de comprender los fundamentos de los sistemas operativos y la ejecución de software directamente sobre el hardware bare-metal, sin las abstracciones proporcionadas por bibliotecas estándar o Kits de Desarrollo de Software (SDK). El objetivo es obtener un conocimiento práctico y profundo sobre cómo inicializar un microcontrolador desde cero, gestionar recursos básicos como el tiempo de CPU y la memoria, controlar periféricos mediante acceso directo a registros, manejar interrupciones e implementar mecanismos de concurrencia simples, utilizando C y Assembler como herramientas principales.
Se busca una experiencia de aprendizaje intensiva en la arquitectura del procesador (ARM Cortex-M0+) y los periféricos del SoC (RP2040), dependiendo exclusivamente de la documentación técnica oficial (datasheets).

= Descripción general

El sistema resultante será un pequeño núcleo de software experimental (nano-kernel), diseñado específicamente para ejecutarse directamente sobre el hardware del RP2040.
Pretende ser una plataforma base que demuestra la viabilidad de implementar multi-tarea pre-emptive básica y una interfaz de consola serie interactiva.

== Funcionalidades del Producto
=== Planificación de tareas pre-emptive.
=== Consola serie interactiva (shell) con comandos básicos.
=== Control de pines GPIO.
=== Manejo de interrupciones.

== Características de los Usuarios

El sistema está destinado principalmente al desarrollador con fines educativos y de experimentación con conceptos de bajo nivel.
No posee una interfaz de usuario final más allá de la consola serie.

= Requerimientos específicos

== Requerimientos de interfaz externa

=== Interfaces de usuario
Se habilitará una interfaz de línea de comandos Shell Serie vía puerto serie con las siguientes características:
==== Comunicación vía UART0 a 115200 baudios.
==== Lectura de línea de comando.
==== Soporte para los siguientes comandos mínimos:
===== Help
Formato: `help`
Lista comandos disponibles.
===== Peek
Formato: `peek <addr_hex>`
Lee e imprime 4 de memoria en la dirección dada.
===== Poke
Formato: `poke <addr_hex> <val_hex>`
Escribe 4 bytes en la dirección dada.
===== Gpio set
Formato: `gpio set <pin> <0|1>`
Poner un pin GPIO en bajo/alto.
===== Show tasks 
Formato: `show-tasks`
Listar tareas activas y su estado.

=== Interfaces de hardware
==== Microcontrolador
Se realizará interacción directa con registros RP2040.
==== Periféricos Internos Usados
Se utilizarán al menos GPIO, UART0, TIMER, NVIC, RESETS, PADS_BANK0, IO_BANK0, SIO.
==== Periféricos Externos Mínimos
Se requiere conexión PC vía USB-Serie TTL y el LED onboard (GP25).

=== Interfaces de conexión
El Puerto Serie UART0 implementado manualmente será la interfaz primaria.

== Requerimientos funcionales

=== Requerimientos generales
==== Scheduler
Implementará planificación pre-emptive basada en tick de Timer (IRQ), política Round-Robin simple, gestión de TCBs/stacks, e invocará rutina Assembler para cambio de contexto.
==== Shell
Se ejecutará como tarea concurrente, leerá comandos desde UART, y parseará/ejecutará los comandos definidos.
==== Drivers
===== GPIO
===== UART
===== Timer
===== NVIC (Habilitación de interrupciones)

== Requerimientos de desempeño

=== Tiempos de respuesta y Uso de Recursos
==== Latencia de cambio de contexto
Objetivo $< 200 \mu s$.
==== Overhead del Scheduler
Objetivo $< 5\%$ CPU.
==== Tiempo de respuesta de la Shell
Interactivo (objetivo < 1s para comandos simples).
==== Uso de RAM
Minimizado, stacks de tamaño fijo.

== Restricciones de diseño
=== Prohibido el uso de cualquier componente del SDK C/C++ de Pico.
=== Interacción con HW solo vía definiciones manuales basadas en datasheet.
=== Sin biblioteca C estándar
Funciones auxiliares implementadas manualmente si son necesarias.
=== Cambio de contexto implementado obligatoriamente en Assembler.
=== Código de arranque y linker script desarrollados manualmente.

== Atributos del sistema de software
=== Modularidad
Se buscará una separación lógica entre módulos (scheduler, shell, drivers).
=== Testabilidad
La shell interactiva será la herramienta principal para pruebas funcionales.

== Otros requerimientos
No aplica
