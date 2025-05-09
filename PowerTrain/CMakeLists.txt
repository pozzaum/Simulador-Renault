add_library(PowerTrain STATIC powertrain.cpp  powertrain.h)

target_compile_definitions(PowerTrain PRIVATE $<$<CONFIG:powertrain_debug>:DEBUG_FLAG=1 DEBUG_MODE> )

target_include_directories(PowerTrain PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
