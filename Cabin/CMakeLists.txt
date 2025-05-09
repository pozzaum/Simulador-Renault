add_library(Cabin cabin.cpp cabin.h)

#target_link_libraries(Cabin PUBLIC CoolProp)

set(USE_WEBSOCKETS ON)

target_compile_definitions(Cabin PRIVATE $<$<CONFIG:Cab_debug>:DEBUG_FLAG=1 DEBUG_MODE>
    $<$<CONFIG:Cabin_debug>:CABIN>
    $<$<CONFIG:Cabin_release>:CABIN>
    $<$<CONFIG:All_debug>:ALL>
    $<$<CONFIG:All_release>:ALL>
    USE_WEBSOCKETS
)

target_include_directories(Cabin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
