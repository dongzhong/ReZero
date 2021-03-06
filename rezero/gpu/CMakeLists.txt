if(ANDROID)
    add_definitions("-DREZERO_GPU_OPENGL")
    set(REZERO_GPU_BACKEND_OPENGL true)
elseif(APPLE)
    if(IOS)
        add_definitions("-DREZERO_GPU_OPENGL")
        set(REZERO_GPU_BACKEND_OPENGL true)
        # TODO: Adapt Metal for future
    endif()
endif()

if(REZERO_GPU_BACKEND_OPENGL)
    set(REZERO_GPU_SPECIFIC_HEADER
        gpu/opengl/traits/trait_buffer.h
        gpu/opengl/traits/trait_command_buffer.h
        gpu/opengl/traits/trait_program.h
        gpu/opengl/traits/trait_render_pass.h
        gpu/opengl/traits/trait_render_pipeline.h
        gpu/opengl/traits/trait_shader.h
        gpu/opengl/traits/trait_texture.h
        gpu/opengl/includes.h
        gpu/opengl/state_machine_gl.h
        gpu/opengl/utils.h
    )

    set(REZERO_GPU_SPECIFIC_SRC
        gpu/opengl/buffer.cc
        gpu/opengl/command_buffer.cc
        gpu/opengl/program.cc
        gpu/opengl/render_pass.cc
        gpu/opengl/render_pipeline.cc
        gpu/opengl/shader.cc
        gpu/opengl/state_machine_gl.cc
        gpu/opengl/texture.cc
        gpu/opengl/utils.cc
    )
endif()

set(REZERO_GPU_HEADER
    ${REZERO_GPU_SPECIFIC_HEADER}
    gpu/buffer.h
    gpu/command_buffer.h
    gpu/defines.h
    gpu/depth_stencil_state.h
    gpu/device.h
    gpu/program.h
    gpu/program_state.h
    gpu/render_pass.h
    gpu/render_pass_descriptor.h
    gpu/render_pipeline.h
    gpu/shader.h
    gpu/texture.h
    gpu/types.h
    gpu/vertex_layout.h
)

set(REZERO_GPU_SRC
    ${REZERO_GPU_SPECIFIC_SRC}
    gpu/device.cc
    gpu/depth_stencil_state.cc
    gpu/program_state.cc
    gpu/render_pass_descriptor.cc
    gpu/types.cc
    gpu/vertex_layout.cc
)