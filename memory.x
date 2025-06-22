MEMORY
{
    /* RP2040 tiene 2MB de Flash comenzando en 0x10000000 */
    /* Los primeros 256 bytes son para boot2. El código de usuario comienza después. */
    FLASH (rx) : ORIGIN = 0x10000000, LENGTH = 2048K

    /* RP2040 tiene 264KB de SRAM comenzando en 0x20000000 */
    RAM (xrw)  : ORIGIN = 0x20000000, LENGTH = 264K
}

/* Definir el punto de entrada de la aplicación */
ENTRY(Reset_Handler)

/* Definir un símbolo para el tope de la pila (Stack Top). */
/* La RAM del RP2040 va de 0x20000000 a 0x20041FFF (264KB). */
/* __StackTop es el final de la RAM (dirección más alta + 1, ya que la pila crece hacia abajo). */
__StackTop = ORIGIN(RAM) + LENGTH(RAM); /* Debería ser 0x20042000 */

/* Tamaño mínimo para la pila, puedes ajustarlo según tus necesidades. */
_Min_Stack_Size = 0x400; /* Por ejemplo, 1KB */


SECTIONS
{
    /* Etapa del cargador de arranque (boot2). Típicamente 256 bytes al inicio de Flash. */
    /* Esta sección contendrá el contenido de tu archivo boot2.S (o el .o equivalente). */
    .boot2 : ALIGN(4)
    {
        KEEP(*(.boot2)) /* Mantiene la sección .boot2 del archivo boot2.S */
    } > FLASH

    /* La tabla de vectores sigue a .boot2. */
    /* Si .boot2 ocupa 0x100 bytes (256), .vectors comenzará en 0x10000100. */
    .vectors : ALIGN(4)
    {
        KEEP(*(.vectors)) /* Mantiene la sección .vectors de vector_table.S */
    } > FLASH

    /* El código del programa y otros datos de solo lectura. */
    .text : ALIGN(4)
    {
        *(.text.Reset_Handler) /* Asegura que Reset_Handler esté al principio si tiene un nombre de sección especial. */
        *(.text*)              /* Todas las demás secciones .text */
        *(.rodata*)            /* Datos de solo lectura */
        *(.ARM.exidx*)         /* Tablas de desenrollado para manejo de excepciones */
        *(.ARM.extab*)
        _etext = .;            /* Símbolo para el final del código/rodata */
    } > FLASH

    /* Sección de datos inicializados */
    /* LMA (Load Memory Address) está en Flash, VMA (Virtual Memory Address) está en RAM. */
    /* _sidata marca la LMA. */
    _sidata = LOADADDR(.data);

    .data : ALIGN(4)
    {
        _sdata = .;            /* Inicio de .data en RAM (VMA) */
        *(.data*)
        . = ALIGN(4);
        _edata = .;            /* Fin de .data en RAM (VMA) */
    } > RAM AT> FLASH          /* VMA en RAM, LMA en FLASH */


    /* Sección de datos no inicializados (BSS) */
    /* Esta sección ocupa espacio en RAM pero no en la imagen ejecutable. */
    /* Es puesta a cero por el código de arranque (startup). */
    .bss : ALIGN(4)
    {
        _sbss = .;             /* Inicio de .bss en RAM */
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;             /* Fin de .bss en RAM */
    } > RAM

    /* Región de la pila del usuario en RAM */
    /* NOLOAD porque solo es espacio reservado para la pila; no se carga desde el archivo. */
    ._user_stack (NOLOAD) : ALIGN(8)
    {
      _sstack = .; /* Inicio de la región de la pila (dirección más baja para este bloque) */
      . = . + _Min_Stack_Size;
      . = ALIGN(8);
      _estack_bottom = .; /* Fin de la región de la pila (dirección más alta para este bloque si la pila crece hacia abajo desde __StackTop) */
                          /* __StackTop se usa normalmente para inicializar SP. Este bloque es más para verificación de tamaño. */
    } > RAM


    /* Descartar secciones de bibliotecas estándar si no se usan o para ahorrar espacio */
    /DISCARD/ :
    {
        libc.a(*)
        libm.a(*)
        libgcc.a(*)
    }

    /* Sección de atributos ARM (requerida por ARM EABI) */
    .ARM.attributes 0 : { *(.ARM.attributes) }
}
