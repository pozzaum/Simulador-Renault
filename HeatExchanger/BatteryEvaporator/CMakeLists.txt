add_library(BatEvap batteryevaporator.cpp batteryevaporator.h
    ../heatexchanger.cpp ../heatexchanger.h)

#target_compile_definitions(BatEvap PRIVATE $<$<CONFIG:BatEvap_debug>:DEBUG_FLAG=1>)

target_include_directories(BatEvap PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
