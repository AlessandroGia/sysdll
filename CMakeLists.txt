cmake_minimum_required(VERSION 3.20)

project(sysdll C ASM_MASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(BUILD_NO_CRT "Build executable without CRT" OFF)

set(OUTPUT_ROOT "${CMAKE_SOURCE_DIR}/out")


if (MSVC)
    if (BUILD_NO_CRT)
        message(STATUS "Building NoCRT version")
        set(OUTPUT_DIR "${OUTPUT_ROOT}/release")

        foreach(flag_var
            CMAKE_C_FLAGS_DEBUG
            CMAKE_C_FLAGS_RELWITHDEBINFO
        )
            string(REPLACE "/RTC1" "" ${flag_var} "${${flag_var}}")
            string(REPLACE "/RTCs" "" ${flag_var} "${${flag_var}}")
            string(REPLACE "/RTCu" "" ${flag_var} "${${flag_var}}")
            string(REPLACE "/RTCc" "" ${flag_var} "${${flag_var}}")

        endforeach()

        set_source_files_properties(
            asm/peb.asm
            asm/syscall.asm
            PROPERTIES LANGUAGE ASM_MASM
        )

        add_library(sysdll SHARED
            src/sysdll.c
            src/memory/mem.c
            src/nsyscall/nsyscall.c

            asm/peb.asm
            asm/syscall.asm
        )

        target_compile_options(sysdll PRIVATE
            $<$<COMPILE_LANGUAGE:C>:/W4>
            $<$<COMPILE_LANGUAGE:C>:/GS->
            $<$<COMPILE_LANGUAGE:C>:/Oi->
            $<$<AND:$<COMPILE_LANGUAGE:C>,$<CONFIG:Debug>>:/Od>
            $<$<AND:$<COMPILE_LANGUAGE:C>,$<CONFIG:Debug>>:/Zi>
            $<$<AND:$<COMPILE_LANGUAGE:C>,$<CONFIG:Release>>:/O2>
        )

        target_link_options(sysdll PRIVATE
            /NODEFAULTLIB
            /NOENTRY
            "/DEF:${CMAKE_SOURCE_DIR}/exports.def"
        )

    else()

        set(OUTPUT_DIR "${OUTPUT_ROOT}/debug")
        message(STATUS "Building with CRT version")

        set_source_files_properties(
            asm/entry.asm
            asm/peb.asm
            asm/syscall.asm
            PROPERTIES LANGUAGE ASM_MASM
        )

        add_executable(sysdll
            src/main.c
            src/sysdll.c
            src/memory/mem.c
            src/nsyscall/nsyscall.c

            asm/peb.asm
            asm/syscall.asm
        )

        target_compile_options(sysdll PRIVATE
            /W4
            /Od
            /Zi
        )

        target_link_options(sysdll PRIVATE
            /DEBUG
        )
    endif()

endif()

target_include_directories(sysdll PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(sysdll PROPERTIES

    RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${OUTPUT_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${OUTPUT_DIR}"

    ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}"

    LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}"

)
