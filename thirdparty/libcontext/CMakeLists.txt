# The libcontext library is only included inside common, so we create it as an
# object library and then add the objects to common.

# Link-time optimization (LTO) on GCC conflicts with embedded assembly (__asm),
# following GCC's recommendation to disable LTO per translation unit.
if( "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set_source_files_properties( libcontext.cpp PROPERTIES
        COMPILE_FLAGS "-fno-lto"
        )
endif()

list(APPEND LIBCONTEXT_SOURCES
    libcontext.cpp
    )

if( MSVC )
    enable_language(ASM_MASM)

    if( NOT LIBCONTEXT_USE_WINFIBER )
        if ( KICAD_BUILD_ARCH_X86 )
            set( CMAKE_ASM_MASM_FLAGS "${CMAKE_ASM_MASM_FLAGS} /safeseh" )
            list(APPEND LIBCONTEXT_SOURCES
                make_i386_ms_pe_masm.asm
                jump_i386_ms_pe_masm.asm
                )
        elseif( KICAD_BUILD_ARCH_X64 )
            list(APPEND LIBCONTEXT_SOURCES
                make_x86_64_ms_pe_masm.asm
                jump_x86_64_ms_pe_masm.asm
                )
        endif()
    else()
        add_compile_definitions(LIBCONTEXT_USE_WINFIBER)
    endif()
endif()

add_library( libcontext OBJECT
    ${LIBCONTEXT_SOURCES}
    )

target_include_directories( libcontext PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    )
