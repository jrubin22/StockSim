#CMakeLists.txt src

set(LIBRARY_NAME srcLib)
#src files
add_library(${LIBRARY_NAME}
    src1.cpp
    Portfolio.cpp
)
target_compile_definitions(${LIBRARY_NAME} PRIVATE)

target_include_directories(${LIBRARY_NAME} PRIVATE
    ../include
    #/usr/include
)

target_link_libraries(${LIBRARY_NAME} PRIVATE
-lstdc++
)

set_target_properties(${LIBRARY_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
)
