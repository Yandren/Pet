# Install script for directory: C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Assimp")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "libassimp3.0-r1264")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/lib/Debug/assimpD.lib")
  ELSEIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/lib/Release/assimp.lib")
  ELSEIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/lib/MinSizeRel/assimp.lib")
  ELSEIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/lib/RelWithDebInfo/assimp.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "libassimp3.0-r1264")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "libassimp3.0-r1264")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/bin/Debug/assimpD.dll")
  ELSEIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/bin/Release/assimp.dll")
  ELSEIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/bin/MinSizeRel/assimp.dll")
  ELSEIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/bin/RelWithDebInfo/assimp.dll")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "libassimp3.0-r1264")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "libassimp3.0-r1264-dev")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/anim.h"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/ai_assert.h"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/camera.h"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/color4.h"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/color4.inl"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/config.h"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/defs.h"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/cfileio.h"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/light.h"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/material.h"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/material.inl"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/matrix3x3.h"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/matrix3x3.inl"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/matrix4x4.h"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/matrix4x4.inl"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/mesh.h"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/postprocess.h"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/quaternion.h"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/quaternion.inl"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/scene.h"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/texture.h"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/types.h"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/vector2.h"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/vector2.inl"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/vector3.h"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/vector3.inl"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/version.h"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/cimport.h"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/importerdesc.h"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/Importer.hpp"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/DefaultLogger.hpp"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/ProgressHandler.hpp"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/IOStream.hpp"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/IOSystem.hpp"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/Logger.hpp"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/LogStream.hpp"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/NullLogger.hpp"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/cexport.h"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/Exporter.hpp"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "libassimp3.0-r1264-dev")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "libassimp3.0-r1264-dev")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/Compiler/pushpack1.h"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/../include/assimp/Compiler/poppack1.h"
    "C:/Users/dragonerdriftr/Documents/Pet/Other Libs/assimp/code/pstdint.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "libassimp3.0-r1264-dev")

