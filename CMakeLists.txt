project(toy)

set( toy_src
        main.cpp
        mtrand.cpp
        uklad.cpp
    )

#include_directories ("${PROJECT_SOURCE_DIR}/MathFunctions")
#add_subdirectory (MathFunctions) 
set ( CMAKE_CXX_FLAGS "-O2 -mtune=native " )
 
# add the executable
add_executable (Tutorial ${toy_src})
#target_link_libraries (Tutorial MathFunctions)
