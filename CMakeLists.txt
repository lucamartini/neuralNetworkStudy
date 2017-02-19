cmake_minimum_required(VERSION 2.8)

#
# Building in-tree is not allowed (we take care of your craziness).
#

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the source code and call cmake from there. Thank you.")
endif()

project(nn)

#---Locate the ROOT package
list(APPEND CMAKE_PREFIX_PATH /usr/share/root)
find_package(ROOT REQUIRED)

include_directories(${ROOT_INCLUDE_DIRS})

set (SRC_DIR src)
set(SOURCES
    main.cpp
    ${SRC_DIR}/perceptron.cpp
    ${SRC_DIR}/trainer.cpp
    ${SRC_DIR}/random_helper.cpp
    ${SRC_DIR}/linearfunction.cpp
    ${SRC_DIR}/neuralnetwork.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${ROOT_LIBRARIES})

