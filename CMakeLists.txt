cmake_minimum_required(VERSION 3.12)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_SIZE arm-none-eabi-size)

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_ASM_COMPILER_WORKS 1)

project(pico-kernel C ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Configurar elf2uf2-rs
find_program(ELF2UF2 elf2uf2-rs)
if(NOT ELF2UF2)
    message(FATAL_ERROR "elf2uf2-rs not found in PATH")
endif()

set(COMMON_FLAGS "-mcpu=cortex-m0plus -mthumb -g -O0")
set(CMAKE_C_FLAGS "${COMMON_FLAGS} -std=gnu11 -Wall -ffreestanding -nostdlib -fdata-sections -ffunction-sections")
set(CMAKE_ASM_FLAGS "${COMMON_FLAGS} -Wall -x assembler-with-cpp -fdata-sections -ffunction-sections")
set(CMAKE_EXE_LINKER_FLAGS "${COMMON_FLAGS} -Wl,-T,${CMAKE_SOURCE_DIR}/memory.x -Wl,-Map=${CMAKE_BINARY_DIR}/${PROJECT_NAME}.map -Wl,--gc-sections -nostartfiles -nodefaultlibs")

include_directories(src)

set(ASM_SOURCES
    src/boot2/boot2.S
    src/boot2/ram_cpy.S
    src/vector-table/vector_table.S
)

set(C_SOURCES
    src/main.c
    src/hal/common/common.c
    src/hal/reset/reset.c
    src/hal/xosc/xosc.c
    src/hal/pll/pll.c
    src/hal/clocks/clocks.c
    src/hal/sio/sio.c
    src/hal/io_bank/io_bank.c
    src/hal/pad_bank/pad_bank.c
    src/hal/uart/uart.c
)

add_executable(${PROJECT_NAME}.elf ${C_SOURCES} ${ASM_SOURCES})

set_target_properties(${PROJECT_NAME}.elf PROPERTIES
    LINK_DEPENDS "${CMAKE_SOURCE_DIR}/memory.x"
)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.bin
    COMMENT "Creando binario"
)
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${ELF2UF2} $<TARGET_FILE:${PROJECT_NAME}.elf> ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.uf2
    COMMENT "Creando archivo UF2"
)
