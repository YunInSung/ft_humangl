# cmake version
cmake_minimum_required(VERSION 3.27)

# set variable
set(PROJECT_NAME humanGL)
set(CMAKE_CXX_STANDARD 17)

set(WINDOW_NAME "Hello, OpenGL!")
set(WINDOW_WIDTH 640)
set(WINDOW_HEIGHT 480)

# set project
project(
	${PROJECT_NAME}
	LANGUAGES CXX
)

# set source code
# put manual
# set(SOURCE_CODE ${SOURCE_CODE}
#     ./src/main.cpp
# )
# wild card
file(GLOB_RECURSE SOURCE_CODE
    ./src/**.cpp
)

file(GLOB_RECURSE HEADER_CODE
    ./include/**.hpp
)

# start build
add_executable(${PROJECT_NAME} ${SOURCE_CODE} ${HEADER_CODE})

# dependency import
include(Dependency.cmake)

# set define
target_compile_definitions(${PROJECT_NAME} PUBLIC
WINDOW_NAME="${WINDOW_NAME}"
WINDOW_WIDTH=${WINDOW_WIDTH}
WINDOW_HEIGHT=${WINDOW_HEIGHT}
)

# include path
target_include_directories(${PROJECT_NAME} PUBLIC ./include)
target_include_directories(${PROJECT_NAME} PUBLIC ./include/glm)
# include, link for dependencies
target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC
    ${DEP_LIBS}
    "-framework CoreVideo"
    "-framework OpenGL"
    "-framework IOKit"
    "-framework Cocoa"
    "-framework Carbon"
)

# dependency check
add_dependencies(${PROJECT_NAME} ${DEP_LIST})