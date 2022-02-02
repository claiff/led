#THIS FILE IS AUTO GENERATED FROM THE TEMPLATE! DO NOT CHANGE!
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.19)

# specify cross compilers and tools
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER  arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# project settings
project(Led C CXX ASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

add_compile_options(-mcpu=cortex-m3 -mthumb -mthumb-interwork)
add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)

add_compile_options( -Og )

set( DEFAULT_HEADERS 17 )

set( SOURCE_DIR src )
set( MAIN_DIR ${SOURCE_DIR}/main )
set( STARTUP_DIR ${SOURCE_DIR}/startup )
set( PERIPHERY_DIR ${SOURCE_DIR}/periphery )
set( DEVICE_DIR ${SOURCE_DIR}/device )
set( SPECIFIC_DIR ${SOURCE_DIR}/specific )
set( UTILS_DIR ${SOURCE_DIR}/utils )
set( DRAWER_DIR ${SOURCE_DIR}/drawer )
set( EFFECTS_DIR ${DRAWER_DIR}/effects )

set(PROJECT_SOURCES
        ${MAIN_DIR}/main.cpp

        ${DEVICE_DIR}/led_matrix.cpp
        ${DEVICE_DIR}/led_matrix.hpp

        ${PERIPHERY_DIR}/rcc_helper.cpp
        ${PERIPHERY_DIR}/rcc_helper.hpp
        ${PERIPHERY_DIR}/pwm.cpp
        ${PERIPHERY_DIR}/pwm.hpp
        ${PERIPHERY_DIR}/timer_irq.cpp
        ${PERIPHERY_DIR}/timer_irq.hpp
        ${PERIPHERY_DIR}/system_timer_irq.cpp
        ${PERIPHERY_DIR}/system_timer_irq.hpp
        ${PERIPHERY_DIR}/adc.cpp
        ${PERIPHERY_DIR}/adc.hpp

        ${SPECIFIC_DIR}/stm32f103xb.h
        ${SPECIFIC_DIR}/core_cm3.h
        ${SPECIFIC_DIR}/cmsis_version.h
        ${SPECIFIC_DIR}/cmsis_compiler.h
        ${SPECIFIC_DIR}/cmsis_gcc.h
        ${SPECIFIC_DIR}/system_stm32f1xx.h

        ${UTILS_DIR}/struct.hpp
        ${UTILS_DIR}/timings_converter.cpp
        ${UTILS_DIR}/timings_converter.hpp

        ${EFFECTS_DIR}/simple_color.cpp
        ${EFFECTS_DIR}/simple_color.hpp
        ${EFFECTS_DIR}/color_gradient.cpp
        ${EFFECTS_DIR}/color_gradient.hpp
        ${EFFECTS_DIR}/random_figure.cpp
        ${EFFECTS_DIR}/random_figure.hpp

        ${EFFECTS_DIR}/utils/registrator.cpp
        ${EFFECTS_DIR}/utils/registrator.hpp
        ${EFFECTS_DIR}/utils/timer_policy.cpp
        ${EFFECTS_DIR}/utils/timer_policy.hpp
        ${EFFECTS_DIR}/utils/rectangle.cpp
        ${EFFECTS_DIR}/utils/rectangle.hpp

        ${EFFECTS_DIR}/decorator/smoth_transition.hpp
        ${EFFECTS_DIR}/decorator/smoth_transition.cpp
        ${EFFECTS_DIR}/decorator/fill_random_figure.hpp
        ${EFFECTS_DIR}/decorator/fill_random_figure.cpp

        ${EFFECTS_DIR}/types/ieffect.hpp
        ${EFFECTS_DIR}/types/idecorator.hpp
        ${EFFECTS_DIR}/types/idecorator.cpp

        ${DRAWER_DIR}/cyclic.cpp
        ${DRAWER_DIR}/cyclic.hpp
        ${DRAWER_DIR}/builder/cyclic.cpp
        ${DRAWER_DIR}/builder/cyclic.hpp

        ${STARTUP_DIR}/startup_stm32f103c8tx.s
        )

include_directories( ${SOURCE_DIR} )

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F103C8TX_FLASH.ld)

add_link_options( -Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map )
add_link_options( -mcpu=cortex-m3 -mthumb -mthumb-interwork )
add_link_options( -T ${LINKER_SCRIPT} )
add_link_options( -specs=nosys.specs -specs=nano.specs -T ${LINKER_SCRIPT} )
add_executable( ${PROJECT_NAME}.elf ${PROJECT_SOURCES} ${LINKER_SCRIPT} )