add_library(DoubleEvap doubleevaporator.cpp doubleevaporator.h
    ../heatexchanger.cpp ../heatexchanger.h)

#target_compile_definitions(DoubleEvap PRIVATE $<$<CONFIG:DoubleEvap_debug>:DEBUG_FLAG=1>)

target_include_directories(DoubleEvap PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
