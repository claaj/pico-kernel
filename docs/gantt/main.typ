#import "@local/unrn-template:1.0.0": proyecto
#import "@preview/gantty:0.2.0": gantt

#show: proyecto.with(
  titulo: "Nano-Kernel Bare-Metal para RP2040",
  subtitulo: "Planificación",
  indice: false,
  fuente: "IBM Plex Sans",
  caratula: true,
  autores: ("Matías Cajal",),
  materia: "Laboratorio de Sistemas Embebidos",
  carrera: "Ingeniería en Computación",
  año: "2025",
  fecha: "1 de Mayo de 2025",
  version: "v1.0"
)

= Introducción

Este documento presenta la planificación detallada para el proyecto "Nano-Kernel Bare-Metal para RP2040", enfocado en desarrollar un núcleo de software minimalista para este microcontrolador, interactuando directamente con el hardware.

A continuación, se visualiza el cronograma del proyecto mediante un diagrama de Gantt. Este detalla las fases, tareas y plazos estimados desde la última semana de marzo hasta la segunda de junio de 2025. Dicha planificación servirá como guía para la ejecución, seguimiento y gestión eficiente del desarrollo, desde la configuración inicial hasta la entrega final del nano-kernel con sus funcionalidades clave.

#set page(flipped: true, margin: auto )
#set text(font: ("IBM Plex Sans"), size: 8pt)

#gantt(yaml("gantt.yaml"))

