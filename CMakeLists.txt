cmake_minimum_required(VERSION 3.2)
project(TGBOT
        LANGUAGES C CXX
        VERSION 0.0.1
        )

### Configuration

option(TGBOT_ENABLE_TESTS "Enable building of tests" OFF)


### Sources

set(TGBOT_SOURCES
	src/Api.cpp
	src/TgTypeParser.cpp
	src/EventHandler.cpp
	src/net/Url.cpp
	src/net/HttpClient.cpp
	src/net/HttpParser.cpp
	src/net/TgLongPoll.cpp
	src/tools/StringTools.cpp
	src/tools/FileTools.cpp
	src/types/InlineQueryResult.cpp
	src/types/InputFile.cpp)


### Dependencies
set(Boost_USE_MULTITHREADED ON)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost 1.59.0 COMPONENTS system)


### Old CMake compatability

include(cmake/external-targets.cmake)

set(THREADS_INTERFACE_TARGET OFF)
if (NOT TARGET Threads::Threads)
	set(THREADS_INTERFACE_TARGET ON)
    define_threads_target()
endif ()

set(BOOST_INTERFACE_TARGET OFF)
if (NOT TARGET Boost::system)
	set(BOOST_INTERFACE_TARGET ON)
    define_boost_target(system)
endif ()

set(SSL_INTERFACE_TARGET OFF)
if (NOT TARGET OpenSSL::SSL)
	set(SSL_INTERFACE_TARGET ON)
    define_openssl_ssl_target()
    define_openssl_crypto_target()
endif ()


### Library

add_library(tgbot ${TGBOT_SOURCES})
target_link_libraries(tgbot Threads::Threads Boost::system OpenSSL::SSL OpenSSL::Crypto)
target_include_directories(tgbot PUBLIC
        $<BUILD_INTERFACE:${TGBOT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include/>)

set_property(TARGET tgbot PROPERTY CXX_STANDARD 11)
set_property(TARGET tgbot PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET tgbot PROPERTY CXX_STANDARD_EXTENSIONS OFF)


### Installation

install(TARGETS tgbot
        DESTINATION lib
        EXPORT tgbot-cpp-targets)

if (SSL_INTERFACE_TARGET)
	install(TARGETS __OpenSSL_SSL __OpenSSL_Crypto
			EXPORT tgbot-cpp-targets)
endif ()

if (BOOST_INTERFACE_TARGET)
	install(TARGETS __Boost_system
			EXPORT tgbot-cpp-targets)
endif ()

install(DIRECTORY "${TGBOT_SOURCE_DIR}/include/"
        DESTINATION include)

install(EXPORT tgbot-cpp-targets
        DESTINATION lib/cmake/tgbot-cpp)

install(FILES ${TGBOT_SOURCE_DIR}/cmake/tgbot-cpp-config.cmake
        DESTINATION lib/cmake/tgbot-cpp)


### Documentation

find_package(Doxygen)

option(TGBOT_DOCS "Generate HTML documentation (Doxygen)"     ${DOXYGEN_FOUND})

if(TGBOT_DOCS)
    if (NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is required to build documentation.")
    endif()

    if(DOXYGEN_DOT_FOUND)
        file(TO_NATIVE_PATH "${DOXYGEN_DOT_EXECUTABLE}" DOXYGEN_DOT_EXECUTABLE_)
        set(DOXYGEN_DOT_FOUND_ "YES")
    endif()

    configure_file(${TGBOT_SOURCE_DIR}/cmake/Doxyfile.in ${TGBOT_BINARY_DIR}/Doxyfile @ONLY)

    add_custom_command(OUTPUT ${TGBOT_BINARY_DIR}/docs
                       COMMAND ${DOXYGEN_EXECUTABLE} ${TGBOT_BINARY_DIR}/Doxyfile
                       WORKING_DIRECTORY ${TGBOT_BINARY_DIR}
                       COMMENT "Generating HTML documentation using Doxygen"
                       DEPENDS ${TGBOT_HEADERS} ${TGBOT_SOURCE_DIR}/cmake/Doxyfile.in ${TGBOT_SOURCE_DIR}/README.md
                       VERBATIM)

    add_custom_target(doc ALL
                      DEPENDS ${TGBOT_BINARY_DIR}/docs)

    install(DIRECTORY ${TGBOT_BINARY_DIR}/docs/ DESTINATION share/doc/tgbot)
endif()


### Examples

option(TGBOT_EXAMPLES "Build examples." OFF)

if(TGBOT_EXAMPLES)
    file(GLOB EXAMPLES
         LIST_DIRECTORIES TRUE
         RELATIVE ${TGBOT_SOURCE_DIR}/examples
         ${TGBOT_SOURCE_DIR}/examples/*/)

    foreach(example ${EXAMPLES})
        if (IS_DIRECTORY ${TGBOT_SOURCE_DIR}/examples/${example})
            message(STATUS "Example: ${example}")

            add_subdirectory(${TGBOT_SOURCE_DIR}/examples/${example})
        endif()
    endforeach()
endif()


### Tests

if (TGBOT_ENABLE_TESTS)
	enable_testing()
	add_subdirectory(test)
endif ()

