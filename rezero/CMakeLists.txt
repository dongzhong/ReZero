project(rezero_core)

include(base/CMakeLists.txt)
include(library/CMakeLists.txt)
include(shell/CMakeLists.txt)

set(REZERO_VERSION 0.1)

set(REZERO_HEADER
    version.h
    ${REZERO_BASE_HEADER}
    ${REZERO_LIBRARY_HEADER}
    ${REZERO_SHELL_HEADER}
)

set(REZERO_SRC
    version.cc
    ${REZERO_BASE_SRC}
    ${REZERO_LIBRARY_SRC}
    ${REZERO_SHELL_SRC}
)

list(APPEND REZERO_SRC ${REZERO_HEADER})

if(ANDROID)
    add_library(rezero SHARED ${REZERO_SRC})

    add_definitions("-DREZERO_PLATFORM_STR=\"Android\"")

    target_link_libraries(rezero PUBLIC
        atomic
        android
        EGL
        GLESv2
        log
    )

    target_include_directories(rezero PUBLIC ${REZERO_ROOT_PATH})
elseif(APPLE)
    if(IOS)
        add_library(rezero STATIC ${REZERO_SRC})

        add_definitions("-DREZERO_PLATFORM_STR=\"iOS\"")

        target_link_libraries(rezero PUBLIC
            "-framework OpenGLES"
            "-framework QuartzCore"
            "-framework UIKit"
        )

        target_include_directories(rezero PUBLIC ${REZERO_PUBLIC_DIR})
        target_include_directories(rezero PRIVATE ${REZERO_ROOT_PATH})

        set(REZERO_ARC_SOURCES
            ${REZERO_BASE_ARC_SOURCES}
            ${REZERO_LIBRARY_ARC_SOURCES}
            ${REZERO_SHELL_ARC_SOURCES}
        )

        set_source_files_properties(${REZERO_SRC} PROPERTIES COMPILE_FLAGS -fno-objc-arc)
        set_source_files_properties(${REZERO_ARC_SOURCES} PROPERTIES COMPILE_FLAGS -fobjc-arc)

        set_target_properties(rezero PROPERTIES
            OUTPUT_NAME ReZero
            FRAMEWORK TRUE
            PUBLIC_HEADER "${REZERO_PUBLIC_HEADER}"
            MACOSX_FRAMEWORK_IDENTIFIER pers.dongzhong.rezero
            XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER pers.dongzhong.rezero
        )
    else()
        message("Rezero has no support for MacOS currently.")
    endif()
else()
    message("Unknown platform.")
endif()

add_definitions("-DREZERO_VERSION=\"${REZERO_VERSION}\"")