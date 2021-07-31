cmake_minimum_required (VERSION 2.8)
project(OpenGLRender)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo" CACHE STRING "Configuration types" FORCE)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/*.h
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

file(GLOB_RECURSE EXT_FILES  
    ${CMAKE_SOURCE_DIR}/thirdparty/gl3w/GL/*.c
)

set(SRCS ${SRC_FILES} ${EXT_FILES})

include_directories(
  ${CMAKE_SOURCE_DIR}/src/core
  ${CMAKE_SOURCE_DIR}/thirdparty/gl3w
  ${CMAKE_SOURCE_DIR}/thirdparty/glm
)

find_package(OpenGL)

foreach(f ${SRCS})
    # Get the path of the file relative to ${DIRECTORY},
    # then alter it (not compulsory)
    file(RELATIVE_PATH SRCGR ${CMAKE_SOURCE_DIR} ${f})
    set(SRCGR "Sources/${SRCGR}")

    # Extract the folder, ie remove the filename part
    string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRCGR ${SRCGR})

    # Source_group expects \\ (double antislash), not / (slash)
    string(REPLACE / \\ SRCGR ${SRCGR})
    source_group("${SRCGR}" FILES ${f})
endforeach()

if(WIN32)
  set(GUI_TYPE WIN32)
elseif(MACOSX)
  set(GUI_TYPE MACOSX_BUNDLE)
endif()

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

SET(LINK_OPTIONS " ")
SET(EXE_NAME "OpenGLRender")

ADD_EXECUTABLE(${EXE_NAME} ${SRCS})

if(WIN32)
TARGET_LINK_LIBRARIES(${EXE_NAME} ${OPENGL_LIBRARIES})
else()
TARGET_LINK_LIBRARIES(${EXE_NAME} ${OPENGL_LIBRARIES} dl)
endif()

# GLFW
set(GLFW_DIR ${CMAKE_SOURCE_DIR}/thirdparty/glfw-3.3.4)
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory("${GLFW_DIR}")
target_link_libraries(${EXE_NAME} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${EXE_NAME} PRIVATE "${GLFW_DIR}/include")
target_compile_definitions(${EXE_NAME} PRIVATE "GLFW_INCLUDE_NONE")

# GLM
set(GLM_DIR ${CMAKE_SOURCE_DIR}/thirdparty/glm)
add_subdirectory("${GLM_DIR}")
target_link_libraries(${EXE_NAME} "glm" "${GLM_LIBRARIES}")
target_include_directories(${EXE_NAME} PRIVATE "${GLM_DIR}/include")
target_compile_definitions(${EXE_NAME} PRIVATE "GLM_INCLUDE_NONE")

#--------------------------------------------------------------------
# preproc
#--------------------------------------------------------------------
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-D__STDC_FORMAT_MACROS)
add_definitions(-DBX_CONFIG_ENABLE_MSVC_LEVEL4_WARNINGS=1)
add_definitions(-D__STDC_LIMIT_MACROS)
add_definitions(-D__STDC_CONSTANT_MACROS)
add_definitions(-DIMGUI_DISABLE_OBSOLETE_FUNCTIONS)
if(MSVC)
add_definitions(-DWIN32)
add_definitions(-D_WIN32)
#add_definitions(-DNOMINMAX)
endif()
add_definitions(-DUSE_DL_PREFIX)
add_definitions(-DGLEW_STATIC)

#--------------------------------------------------------------------
# output dirs
#--------------------------------------------------------------------

set_target_properties(${EXE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR} )
set_target_properties(${EXE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR} )
set_target_properties(${EXE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_BINARY_DIR} )
set_target_properties(${EXE_NAME} PROPERTIES DEBUG_POSTFIX "_d")
set_target_properties(${EXE_NAME} PROPERTIES RELWITHDEBINFO_POSTFIX "RelWithDebInfo")
set_target_properties(${EXE_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

if(WIN32)
set_target_properties(${EXE_NAME} PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
set_target_properties(${EXE_NAME} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:CONSOLE")
endif()