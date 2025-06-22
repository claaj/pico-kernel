.cpu cortex-m0plus
.thumb
.syntax unified

// Símbolos definidos por el linker script
.extern __StackTop     // Límite superior de la pila
.extern _sidata        // Dirección de inicio de .data en Flash (LMA)
.extern _sdata         // Dirección de inicio de .data en RAM (VMA)
.extern _edata         // Dirección de fin de .data en RAM (VMA)
.extern _sbss          // Dirección de inicio de .bss en RAM (VMA)
.extern _ebss          // Dirección de fin de .bss en RAM (VMA)

// Referencia externa a la función main de C
.extern main

// Exportar Reset_Handler
.global Reset_Handler
.type Reset_Handler, %function

.section .text.Reset_Handler, "ax", %progbits

Reset_Handler:
    // 1. Inicializar el Stack Pointer (SP).
    ldr r0, =__StackTop
    mov sp, r0

    // 2. Copiar la sección .data desde Flash a RAM.
    ldr r1, =_sidata  // r1 apunta al inicio de .data en Flash
    ldr r2, =_sdata   // r2 apunta al inicio de .data en RAM
    ldr r3, =_edata   // r3 apunta al final de .data en RAM

copy_data_loop:
    cmp r2, r3          // Compara si el puntero de destino ha alcanzado el final de .data
    bhs copy_data_done  // Si r2 >= r3, salta a copy_data_done

    ldr r0, [r1]        // Carga una palabra desde la fuente (r1)
    // Original: add r1, r1, #4
    // Corregido: usar adds
    adds r1, r1, #4     // Post-incrementa r1 (y actualiza flags)

    str r0, [r2]        // Almacena la palabra en el destino (r2)
    // Original: add r2, r2, #4
    // Corregido: usar adds
    adds r2, r2, #4     // Post-incrementa r2 (y actualiza flags)

    b copy_data_loop    // Repite
copy_data_done:

    // 3. Inicializar la sección .bss a cero en RAM.
    ldr r1, =_sbss      // r1 apunta al inicio de .bss en RAM
    ldr r2, =_ebss      // r2 apunta al final de .bss en RAM
    movs r0, #0         // r0 contendrá el valor 0

zero_bss_loop:
    cmp r1, r2          // Compara si el puntero ha alcanzado el final de .bss
    bhs zero_bss_done   // Si r1 >= r2, salta a zero_bss_done

    str r0, [r1]        // Almacena 0 en la ubicación actual de .bss
    // Original: add r1, r1, #4
    // Corregido: usar adds
    adds r1, r1, #4     // Post-incrementa r1 (y actualiza flags)

    b zero_bss_loop     // Repite
zero_bss_done:

    // 4. Saltar a la función main de C.
    bl main

    // 5. Si main retorna (no debería en una aplicación bare-metal),
    // entra en un bucle infinito.
infinite_loop:
    b infinite_loop

.size Reset_Handler, . - Reset_Handler
