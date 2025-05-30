# Install script for directory: D:/Documentos/Proj Rota 2030 Renault/Codigo Novo/Simulador_renault_rota2030/externals/CoolProps

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "D:/Documentos/Proj Rota 2030 Renault/Codigo Novo/Simulador_renault_rota2030/externals/CoolProps/install_root")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/static_library/Windows/64bit_MSVC_19.29.30153.0" TYPE STATIC_LIBRARY FILES "D:/Documentos/Proj Rota 2030 Renault/Codigo Novo/Simulador_renault_rota2030/externals/CoolProps/Debug/CoolPropd.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/static_library/Windows/64bit_MSVC_19.29.30153.0" TYPE STATIC_LIBRARY FILES "D:/Documentos/Proj Rota 2030 Renault/Codigo Novo/Simulador_renault_rota2030/externals/CoolProps/Release/CoolProp.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/static_library/Windows/64bit_MSVC_19.29.30153.0" TYPE STATIC_LIBRARY FILES "D:/Documentos/Proj Rota 2030 Renault/Codigo Novo/Simulador_renault_rota2030/externals/CoolProps/MinSizeRel/CoolProp.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/static_library/Windows/64bit_MSVC_19.29.30153.0" TYPE STATIC_LIBRARY FILES "D:/Documentos/Proj Rota 2030 Renault/Codigo Novo/Simulador_renault_rota2030/externals/CoolProps/RelWithDebInfo/CoolProp.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    include("D:/Documentos/Proj Rota 2030 Renault/Codigo Novo/Simulador_renault_rota2030/externals/CoolProps/CMakeFiles/CoolProp.dir/install-cxx-module-bmi-Debug.cmake" OPTIONAL)
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    include("D:/Documentos/Proj Rota 2030 Renault/Codigo Novo/Simulador_renault_rota2030/externals/CoolProps/CMakeFiles/CoolProp.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    include("D:/Documentos/Proj Rota 2030 Renault/Codigo Novo/Simulador_renault_rota2030/externals/CoolProps/CMakeFiles/CoolProp.dir/install-cxx-module-bmi-MinSizeRel.cmake" OPTIONAL)
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    include("D:/Documentos/Proj Rota 2030 Renault/Codigo Novo/Simulador_renault_rota2030/externals/CoolProps/CMakeFiles/CoolProp.dir/install-cxx-module-bmi-RelWithDebInfo.cmake" OPTIONAL)
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/static_library" TYPE FILE FILES "D:/Documentos/Proj Rota 2030 Renault/Codigo Novo/Simulador_renault_rota2030/externals/CoolProps/include/CoolPropLib.h")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "D:/Documentos/Proj Rota 2030 Renault/Codigo Novo/Simulador_renault_rota2030/externals/CoolProps/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
