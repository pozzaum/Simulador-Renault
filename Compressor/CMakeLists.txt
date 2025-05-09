
#add_subdirectory ("../externals/CoolProps" CoolProp)

#add_subdirectory ("../externals/REFPROP-cpp-wrapper/" refprop)
#add_subdirectory ("../externals/fparser/" fparser)

add_library(Compressor STATIC compressor.cpp  compressor.h)
#message(STATUS "Found REFPROP: ${REFPROP}")

target_link_libraries(Compressor PUBLIC fparser CoolProp)

target_compile_definitions(Compressor PRIVATE $<$<CONFIG:comp_debug>:DEBUG_FLAG=1 DEBUG_MODE> )

target_include_directories(Compressor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
