cmake_minimum_required(VERSION 3.20)

project(sysdll C ASM_MASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)


add_executable(sysdll
    src/sysdll.c
    src/memory/mem.c
    src/syscall/nsyscall.c

    asm/peb.asm
    asm/syscall.asm
)

target_include_directories(sysdll PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_source_files_properties(
    asm/peb.asm
    asm/syscall.asm
    PROPERTIES LANGUAGE ASM_MASM
)

if (MSVC)
    target_compile_options(sysdll PRIVATE /W4 /Zi /Od)
    target_link_options(sysdll PRIVATE /DEBUG)
endif()
