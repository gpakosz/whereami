cmake_minimum_required(VERSION 3.1)
project(whereami VERSION 1.0.0 LANGUAGES C CXX)
include(GNUInstallDirs)

option(BUILD_SHARED_LIBS "Build shared libs" ON)
option(BUILD_STATIC_LIBS "Build static libs" ON)
option(BUILD_EXAMPLES    "Build examples"    ON)

find_package(PkgConfig)

# whereami
set(CMAKE_C_STANDARD 99)
add_library(whereami OBJECT ${CMAKE_SOURCE_DIR}/src/whereami.c)
target_include_directories(whereami
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
         $<INSTALL_INTERFACE:include>)
set_target_properties(whereami PROPERTIES POSITION_INDEPENDENT_CODE ON)

if(BUILD_SHARED_LIBS)
  add_library(whereami_shared SHARED $<TARGET_OBJECTS:whereami>)
  set_target_properties(whereami_shared
    PROPERTIES VERSION ${PROJECT_VERSION}
               SOVERSION ${PROJECT_VERSION_MAJOR}
               OUTPUT_NAME whereami
               LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_LIBDIR})
  install(TARGETS whereami_shared LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()

if(BUILD_STATIC_LIBS)
  add_library(whereami_static STATIC $<TARGET_OBJECTS:whereami>)
  set_target_properties(whereami_static
    PROPERTIES OUTPUT_NAME whereami
               ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_LIBDIR})
  install(TARGETS whereami_static ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()

if(BUILD_EXAMPLES)
  add_executable(executable ${CMAKE_SOURCE_DIR}/example/executable.c
                            ${CMAKE_SOURCE_DIR}/src/whereami.c)
  target_include_directories(executable PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)
  if(CMAKE_DL_LIBS)
      target_link_libraries(executable ${CMAKE_DL_LIBS})
  endif()

  add_library(library SHARED ${CMAKE_SOURCE_DIR}/example/library.c
                             ${CMAKE_SOURCE_DIR}/src/whereami.c)
  target_include_directories(library PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)
  if(CMAKE_DL_LIBS)
      target_link_libraries(library ${CMAKE_DL_LIBS})
  endif()
endif()

install(FILES ${CMAKE_SOURCE_DIR}/src/whereami.h COMPONENT headers
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

if(PKG_CONFIG_FOUND)
  configure_file(${CMAKE_SOURCE_DIR}/pkgconfig/whereami.pc.in ${CMAKE_BINARY_DIR}/whereami.pc)
  install(FILES ${CMAKE_BINARY_DIR}/whereami.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
endif()


# whereamipp
if(CMAKE_CXX_COMPILER)
  set(CMAKE_CXX_STANDARD 11)
  add_library(whereamipp OBJECT ${CMAKE_SOURCE_DIR}/src/whereami++.cpp)
  target_include_directories(whereamipp
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
           $<INSTALL_INTERFACE:include>)
  set_target_properties(whereamipp PROPERTIES POSITION_INDEPENDENT_CODE ON)

  if(BUILD_SHARED_LIBS)
    add_library(whereamipp_shared SHARED $<TARGET_OBJECTS:whereamipp>)
    set_target_properties(whereamipp_shared
      PROPERTIES VERSION ${PROJECT_VERSION}
                 SOVERSION ${PROJECT_VERSION_MAJOR}
                 OUTPUT_NAME whereamipp
                 LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_LIBDIR})
    install(TARGETS whereamipp_shared LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
  endif()

  if(BUILD_STATIC_LIBS)
    add_library(whereamipp_static STATIC $<TARGET_OBJECTS:whereamipp>)
    set_target_properties(whereamipp_static
      PROPERTIES OUTPUT_NAME whereamipp
                 ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_LIBDIR})
    install(TARGETS whereamipp_static ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
  endif()

  if(BUILD_EXAMPLES)
    add_executable(executable-as-cxx ${CMAKE_SOURCE_DIR}/example/executable.cpp
                                     ${CMAKE_SOURCE_DIR}/src/whereami++.cpp
                                     ${CMAKE_SOURCE_DIR}/src/whereami.c)
    target_include_directories(executable-as-cxx PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)
    if(CMAKE_DL_LIBS)
        target_link_libraries(executable-as-cxx ${CMAKE_DL_LIBS})
    endif()

    add_library(library-as-cxx SHARED ${CMAKE_SOURCE_DIR}/example/library.cpp
                                      ${CMAKE_SOURCE_DIR}/src/whereami++.cpp
                                      ${CMAKE_SOURCE_DIR}/src/whereami.c)
    target_include_directories(library-as-cxx PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)
    if(CMAKE_DL_LIBS)
        target_link_libraries(library-as-cxx ${CMAKE_DL_LIBS})
    endif()

  endif()

  if(PKG_CONFIG_FOUND)
    configure_file(${CMAKE_SOURCE_DIR}/pkgconfig/whereamipp.pc.in ${CMAKE_BINARY_DIR}/whereamipp.pc)
    install(FILES ${CMAKE_BINARY_DIR}/whereamipp.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
  endif()

  install(FILES ${CMAKE_SOURCE_DIR}/src/whereami++.h COMPONENT headers
          DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
endif()
