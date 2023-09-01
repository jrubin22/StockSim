set(APP_NAME test)
#src file
add_executable(${APP_NAME}
    main.cpp
)
target_compile_definitions(${APP_NAME} PRIVATE)

target_include_directories(${APP_NAME} PRIVATE
    ../include
    #/usr/include
)

target_link_libraries(${APP_NAME} PRIVATE
srcLib
-lsqlite3
-lstdc++
)

set_target_properties(${APP_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
)