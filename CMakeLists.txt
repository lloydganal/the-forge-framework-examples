cmake_minimum_required(VERSION 3.0.0)
project(lag-game-sdk-experimental VERSION 0.1.0 LANGUAGES CXX; C)

################################################################################
# FUNCTIONS
################################################################################

function(copy_target_required_dlibs target_name)
    add_custom_command(TARGET ${target_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${ARGN}
        $<TARGET_FILE_DIR:${target_name}>)
endfunction()


################################################################################
# LANGUAGES SETUP
################################################################################

set(CMAKE_CXX_STANDARD 17 )
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 11 )
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

set(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} 
    /SUBSYSTEM:WINDOWS 
    /ENTRY:mainCRTStartup")


################################################################################
# TARGET OUTPUT DIRECTORIES
################################################################################

set(TARGET_OUTPUT_DIR_NAME 
    ${CMAKE_GENERATOR}_${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}_${CMAKE_BUILD_TYPE})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY 
    ${PROJECT_BINARY_DIR}/${TARGET_OUTPUT_DIR_NAME}/bin)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY 
    ${PROJECT_BINARY_DIR}/${TARGET_OUTPUT_DIR_NAME}/lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 
    ${PROJECT_BINARY_DIR}/${TARGET_OUTPUT_DIR_NAME}/bin)


################################################################################
# DEPENDENCIES
################################################################################

# -----------------------------------------------------------------------------
# The-Forge v1.48
# -----------------------------------------------------------------------------
# https://github.com/ConfettiFX/The-Forge
#
# - Set 'THE_FORGE_ROOT' environment variable to The-Forge project root.
# - OS library compiled with 'NO_DEFAULT_BINDINGS' macro defined. Default 
#   Bindings works well games with basic input bindings (see ref.tf00) but 
#   revents the use of the rest of bindings. 
# 

if(!WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")
else()
	set(XINPUT "Xinput9_1_0")
	if ( ${CMAKE_SYSTEM_VERSION} LESS 6.1 )
		set(XINPUT, "xinput")
	endif()
endif()

set(THE_FORGE_COMMON_LIBRARIES 
    "$ENV{THE_FORGE_ROOT}/Examples_3/Unit_Tests/PC Visual Studio 2017/x64/Debug/OS.lib"
    "$ENV{THE_FORGE_ROOT}/Examples_3/Unit_Tests/PC Visual Studio 2017/x64/Debug/gainputstatic.lib"
    "$ENV{THE_FORGE_ROOT}/Common_3/ThirdParty/OpenSource/ags/ags_lib/lib/amd_ags_x64.lib"
    "$ENV{THE_FORGE_ROOT}/Common_3/ThirdParty/OpenSource/winpixeventruntime/bin/WinPixEventRuntime.lib"
    "${XINPUT}"
    ws2_32)

set(THE_FORGE_COMMON_REQUIRED_DLLS 
    "$ENV{THE_FORGE_ROOT}/Common_3/ThirdParty/OpenSource/ags/ags_lib/lib/amd_ags_x64.dll"
    "$ENV{THE_FORGE_ROOT}/Common_3/ThirdParty/OpenSource/winpixeventruntime/bin/WinPixEventRuntime.dll")

set(THE_FORGE_INCLUDE_DIR 
    "$ENV{THE_FORGE_ROOT}")

    
################################################################################
# TaARGETS
################################################################################

add_executable(main_test main.cpp)
target_include_directories(main_test PUBLIC ${THE_FORGE_INCLUDE_DIR})
target_link_libraries(main_test ${THE_FORGE_COMMON_LIBRARIES})
copy_target_required_dlibs(main_test ${THE_FORGE_COMMON_REQUIRED_DLLS})


# ref.tf00 : github.com/ConfettiFX/The-Forge/wiki/Input-System-Overview#all-built-in-bindings