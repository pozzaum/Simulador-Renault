find_package(Qt6 REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Mqtt)

add_library(MqttConnect STATIC
    mqttconnect.cpp
    mqttconnect.h
)

target_link_libraries(MqttConnect PUBLIC
    Qt6::Core
    Qt6::Mqtt
)


target_compile_definitions(MqttConnect PRIVATE $<$<CONFIG:MqttConnect_debug>:DEBUG_FLAG=1 DEBUG_MODE>)

target_include_directories(MqttConnect PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(MqttConnect PROPERTIES AUTOMOC ON)
