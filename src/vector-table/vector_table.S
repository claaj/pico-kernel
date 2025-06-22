.cpu cortex-m0plus
.thumb
.syntax unified

// Símbolos externos (definidos en el linker script o en otros archivos ensamblador/C)
.extern __StackTop          // Definido en el linker script, tope de la RAM
.extern Reset_Handler       // Definido en main.S (código de arranque)

// Prototipos para los manejadores de excepciones y de IRQ por defecto
// Estos manejadores débiles pueden ser sobreescritos por manejadores definidos por el usuario.
.weak NMI_Handler
.weak HardFault_Handler
.weak SVC_Handler
.weak PendSV_Handler
.weak SysTick_Handler
.weak Default_IRQ_Handler   // Un manejador común para todas las IRQs no gestionadas específicamente

// Sección de la tabla de vectores
.section .vectors, "ax", %progbits // Colocar en la sección .vectors, ejecutable

.global __vector_table_start // Exportar símbolo para el inicio de la tabla de vectores

__vector_table_start:
    .word   __StackTop                  // Puntero de Pila Inicial (MSP)
    .word   Reset_Handler + 1           // Manejador de Reset (bit Thumb con +1)
    .word   NMI_Handler + 1             // Manejador de NMI
    .word   HardFault_Handler + 1       // Manejador de HardFault
    .word   0                           // Reservado (MPU Fault - no en M0+)
    .word   0                           // Reservado (Bus Fault - no en M0+)
    .word   0                           // Reservado (Usage Fault - no en M0+)
    .word   0                           // Reservado
    .word   0                           // Reservado
    .word   0                           // Reservado
    .word   0                           // Reservado
    .word   SVC_Handler + 1             // Manejador de SVCall
    .word   0                           // Reservado (Debug Monitor - no en M0+)
    .word   0                           // Reservado
    .word   PendSV_Handler + 1          // Manejador de PendSV
    .word   SysTick_Handler + 1         // Manejador de SysTick

    // Interrupciones Específicas del RP2040 (IRQ0 a IRQ31)
    .word   Default_IRQ_Handler + 1     // IRQ 0: TIMER_IRQ_0
    .word   Default_IRQ_Handler + 1     // IRQ 1: TIMER_IRQ_1
    .word   Default_IRQ_Handler + 1     // IRQ 2: TIMER_IRQ_2
    .word   Default_IRQ_Handler + 1     // IRQ 3: TIMER_IRQ_3
    .word   Default_IRQ_Handler + 1     // IRQ 4: PWM_IRQ_WRAP
    .word   Default_IRQ_Handler + 1     // IRQ 5: USBCTRL_IRQ
    .word   Default_IRQ_Handler + 1     // IRQ 6: XIP_IRQ
    .word   Default_IRQ_Handler + 1     // IRQ 7: PIO0_IRQ_0
    .word   Default_IRQ_Handler + 1     // IRQ 8: PIO0_IRQ_1
    .word   Default_IRQ_Handler + 1     // IRQ 9: PIO1_IRQ_0
    .word   Default_IRQ_Handler + 1     // IRQ 10: PIO1_IRQ_1
    .word   Default_IRQ_Handler + 1     // IRQ 11: DMA_IRQ_0
    .word   Default_IRQ_Handler + 1     // IRQ 12: DMA_IRQ_1
    .word   Default_IRQ_Handler + 1     // IRQ 13: IO_IRQ_BANK0
    .word   Default_IRQ_Handler + 1     // IRQ 14: IO_IRQ_QSPI
    .word   Default_IRQ_Handler + 1     // IRQ 15: SIO_IRQ_PROC0
    .word   Default_IRQ_Handler + 1     // IRQ 16: SIO_IRQ_PROC1
    .word   Default_IRQ_Handler + 1     // IRQ 17: CLOCKS_IRQ
    .word   Default_IRQ_Handler + 1     // IRQ 18: SPI0_IRQ
    .word   Default_IRQ_Handler + 1     // IRQ 19: SPI1_IRQ
    .word   Default_IRQ_Handler + 1     // IRQ 20: UART0_IRQ
    .word   Default_IRQ_Handler + 1     // IRQ 21: UART1_IRQ
    .word   Default_IRQ_Handler + 1     // IRQ 22: ADC_IRQ_FIFO
    .word   Default_IRQ_Handler + 1     // IRQ 23: I2C0_IRQ
    .word   Default_IRQ_Handler + 1     // IRQ 24: I2C1_IRQ
    .word   Default_IRQ_Handler + 1     // IRQ 25: RTC_IRQ

    // Las IRQs 26-31 no son usadas por periféricos en el RP2040.
    .word   0   // IRQ 26 (No usada)
    .word   0   // IRQ 27 (No usada)
    .word   0   // IRQ 28 (No usada)
    .word   0   // IRQ 29 (No usada)
    .word   0   // IRQ 30 (No usada)
    .word   0   // IRQ 31 (No usada)

.global __vector_table_end
__vector_table_end:

/*
  Definiciones de los manejadores de interrupción por defecto.
  Estos pueden ser bucles infinitos o alguna otra forma de indicar un error.
  Se declaran como .thumb_func para asegurar que son interpretados como código Thumb.
*/
.type NMI_Handler, %function
.thumb_func
NMI_Handler:
    b . // Bucle infinito
.size NMI_Handler, . - NMI_Handler

.type HardFault_Handler, %function
.thumb_func
HardFault_Handler:
    b . // Bucle infinito
.size HardFault_Handler, . - HardFault_Handler

.type SVC_Handler, %function
.thumb_func
SVC_Handler:
    b . // Bucle infinito
.size SVC_Handler, . - SVC_Handler

.type PendSV_Handler, %function
.thumb_func
PendSV_Handler:
    b . // Bucle infinito
.size PendSV_Handler, . - PendSV_Handler

.type SysTick_Handler, %function
.thumb_func
SysTick_Handler:
    b . // Bucle infinito
.size SysTick_Handler, . - SysTick_Handler

.type Default_IRQ_Handler, %function
.thumb_func
Default_IRQ_Handler:
    b . // Bucle infinito
.size Default_IRQ_Handler, . - Default_IRQ_Handler
