project(example)

if (APPLE)
    if(IOS)
        set(REZERO_EXAMPLE_HEADER
            ios/AppDelegate.h
            ios/ViewController.h
        )
        set(REZERO_EXAMPLE_SRC
            ios/AppDelegate.m
            ios/main.m
            ios/ViewController.m
        )
        set(REZERO_EXAMPLE_RESOURCES
            ios/LaunchScreen.storyboard
            ios/Main.storyboard
        )

        list(APPEND REZERO_EXAMPLE_SRC ${REZERO_EXAMPLE_HEADER})

        add_executable(example MACOSX_BUNDLE
            ${REZERO_EXAMPLE_SRC}
            ${REZERO_EXAMPLE_RESOURCES}
        )

        target_link_libraries(example PUBLIC
            rezero
        )

        set(REZERO_EXAMPLE_RESOURCE_DIR ${example_SOURCE_DIR}/ios)

        set_target_properties(example PROPERTIES
            MACOSX_BUNDLE_INFO_PLIST ${PROJECT_SOURCE_DIR}/ios/Info.plist
            RESOURCE "${REZERO_EXAMPLE_RESOURCES}"
            XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "pers.dongzhong.rezero.example"
            XCODE_ATTRIBUTE_LD_RUNPATH_SEARCH_PATHS "@executable_path/Frameworks"
            XCODE_ATTRIBUTE_COPY_PHASE_STRIP NO
            XCODE_EMBED_FRAMEWORKS_CODE_SIGN_ON_COPY ON
            XCODE_EMBED_FRAMEWORKS_REMOVE_HEADERS_ON_COPY ON
            XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2"
        )
    endif()
endif()