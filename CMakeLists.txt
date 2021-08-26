cmake_minimum_required(VERSION 3.7.2)

set(CMAKE_USE_RELATIVE_PATHS TRUE)
project("whereami")
set("PROJECT_DESCRIPTION" "Locate the current executable and the current module/library on the file system ")
set("PROJECT_HOMEPAGE_URL" "https://github.com/gpakosz/whereami") 

set(CPACK_PACKAGE_VENDOR "Gregory Pakosz")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

set(OUR_CMAKE_MODULES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(OUR_CMAKE_3PARTY_MODULES_DIR "${OUR_CMAKE_MODULES_DIR}/thirdParty")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${OUR_CMAKE_MODULES_DIR}" "${OUR_CMAKE_3PARTY_MODULES_DIR}" "${OUR_CMAKE_3PARTY_MODULES_DIR}/Boilerplate" "${OUR_CMAKE_3PARTY_MODULES_DIR}/DoxygenUtils")


include(Boilerplate)
include(DoxygenUtils)


foreach(licFile ${CPACK_RESOURCE_FILE_LICENSE})
	if(licFile MATCHES ".*\\.WTFPL.*")
		set(CPACK_RESOURCE_FILE_LICENSE "${licFile}")
	endif()
endforeach()

set(Include_dir "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(Examples_Dir "${CMAKE_CURRENT_SOURCE_DIR}/example")

add_subdirectory("${Include_dir}")

option(WITH_EXAMPLES "Build examples" OFF)
if(WITH_EXAMPLES)
	add_subdirectory("${Examples_Dir}")
endif()

option(WITH_DOCS "Build docs" OFF)
if(WITH_DOCS)
	find_package(Doxygen REQUIRED dot)

	load_doxyfile("${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile")
	set(DOXYGEN_PROJECT_BRIEF "${CPACK_PACKAGE_DESCRIPTION}")
	set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "${CPACK_RESOURCE_FILE_README}")
	set(DOXYGEN_EXAMPLE_PATH "${Examples_Dir}")

	doxygen_document_target("docs" "${PROJECT_NAME}" "html;man")
endif()

#pass_through_cpack_vars()

include(CPack)
