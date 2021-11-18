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

# if defined(REZERO_USE_OPENGL)
# Metal coming soon...
list(APPEND REZERO_GPU_SPECIFIC_HEADER
    gpu/opengl/buffer_gl.h
    gpu/opengl/device_gl.h
    gpu/opengl/includes_gl.h
    gpu/opengl/program_gl.h
    gpu/opengl/shader_gl.h
    gpu/opengl/state_machine_gl.h
    gpu/opengl/texture_gl.h
    gpu/opengl/utils_gl.h
)

list(APPEND REZERO_GPU_SPECIFIC_SRC
    gpu/opengl/buffer_gl.cc
    gpu/opengl/device_gl.cc
    gpu/opengl/program_gl.cc
    gpu/opengl/shader_gl.cc
    gpu/opengl/state_machine_gl.cc
    gpu/opengl/texture_gl.cc
    gpu/opengl/utils_gl.cc
)

set(REZERO_GPU_HEADER
    ${REZERO_GPU_SPECIFIC_HEADER}
    gpu/context.h
    gpu/buffer.h
    gpu/device.h
    gpu/enums.h
    gpu/program.h
    gpu/shader.h
    gpu/swap_chain.h
    gpu/texture.h
    gpu/types.h
)

set(REZERO_GPU_SRC
    ${REZERO_GPU_SPECIFIC_SRC}
    gpu/context.cc
    gpu/buffer.cc
    gpu/device.cc
    gpu/program.cc
    gpu/shader.cc
    gpu/swap_chain.cc
    gpu/texture.cc
    gpu/types.cc
)