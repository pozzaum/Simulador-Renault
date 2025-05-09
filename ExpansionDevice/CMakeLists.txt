#add_subdirectory ("../externals/CoolProps" CoolProp)

add_library(ExpDevice expansiondevice.cpp expansiondevice.h)

#target_link_libraries(ExpDevice PRIVATE CoolProp)

#target_compile_definitions(ExpDevice PRIVATE $<$<CONFIG:ExpDev_debug>:DEBUG_FLAG=1>)

target_include_directories(ExpDevice PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
