if(ANDROID)
    set(REZERO_SHELL_PLATFORM_SPECIFIC_HEADER
        shell/android/engine_android.h
    )
    set(REZERO_SHELL_PLATFORM_SPECIFIC_SRC
        shell/android/engine_android.cc
        shell/android/jni_on_load.cc
    )
elseif(APPLE)

endif()

set(REZERO_SHELL_HEADER
    ${REZERO_SHELL_PLATFORM_SPECIFIC_HEADER}
    shell/engine.h
)

set(REZERO_SHELL_SRC
    ${REZERO_SHELL_PLATFORM_SPECIFIC_SRC}
    shell/engine.cc
)