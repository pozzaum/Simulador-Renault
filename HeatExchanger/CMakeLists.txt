add_library(HXC heatexchanger.cpp heatexchanger.h)

#target_compile_definitions(HXC PUBLIC $<$<CONFIG:HeatEx_debug>:DEBUG_FLAG=1>)

target_include_directories(HXC PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
