set(REZERO_GPU_SPECIFIC_HEADER)

set(REZERO_GPU_SPECIFIC_SRC)

if(ANDROID)
    list(APPEND REZERO_GPU_SPECIFIC_HEADER
        gpu/opengl/swap_chain_egl.h
        gpu/opengl/context_egl.h
    )

    list(APPEND REZERO_GPU_SPECIFIC_SRC
        gpu/opengl/context_egl.cc
        gpu/opengl/swap_chain_egl.cc
    )
elseif(APPLE)
    if(IOS)
        list(APPEND REZERO_GPU_SPECIFIC_HEADER
            gpu/opengl/context_eagl.h
            gpu/opengl/swap_chain_eagl.h
        )

        list(APPEND REZERO_GPU_SPECIFIC_SRC
            gpu/opengl/context_eagl.mm
            gpu/opengl/swap_chain_eagl.mm
        )
    endif()
endif()

set(REZERO_GPU_HEADER
    ${REZERO_GPU_SPECIFIC_HEADER}
    gpu/context.h
    gpu/enums.h
    gpu/swap_chain.h
    gpu/types.h
)

set(REZERO_GPU_SRC
    ${REZERO_GPU_SPECIFIC_SRC}
    gpu/context.cc
    gpu/swap_chain.cc
)