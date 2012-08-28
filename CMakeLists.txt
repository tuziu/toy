project(toy)

set( toy_inc        
        mtrand.h
        uklad.h
        box.h
		def.h
		Cykling_Indeks.h
		heleprs.h
    )

set( toy_src
        main.cpp
        mtrand.cpp
        uklad.cpp
        box.cpp
    )

#include_directories ("${PROJECT_SOURCE_DIR}/MathFunctions")
#add_subdirectory (MathFunctions) 
set ( CMAKE_CXX_FLAGS "-O2 -mtune=native -Wall" )
#set ( CMAKE_CXX_FLAGS "-g -Wall" )
 
# add the executable
add_executable (Tutorial ${toy_src} ${toy_inc})
#target_link_libraries (Tutorial MathFunctions)
