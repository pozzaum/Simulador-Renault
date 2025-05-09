add_library(Condenser condenser.cpp condenser.h
    ../heatexchanger.cpp ../heatexchanger.h)

#target_compile_definitions(Condenser PRIVATE $<$<CONFIG:Cond_debug>:DEBUG_FLAG=1>)

target_include_directories(Condenser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
