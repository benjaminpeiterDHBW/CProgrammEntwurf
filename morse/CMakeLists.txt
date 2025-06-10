cmake_minimum_required(VERSION 3.10)
project(morse C)

# Define C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Include directories for headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# Gather all source files in src/
file(GLOB SRC_FILES "src/*.c")

# Create executable target
add_executable(morse ${SRC_FILES})

# Enable Doxygen documentation generation if available
find_package(Doxygen)
if(DOXYGEN_FOUND)
    # Input and output files for Doxygen configuration
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # Configure Doxyfile
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    # Custom target to generate docs
    add_custom_target(doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
endif()
