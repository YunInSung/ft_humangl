include(ExternalProject)

# Dependency 관련 변수 설정
set(DEP_INSTALL_DIR ${PROJECT_BINARY_DIR}/install)
set(DEP_INCLUDE_DIR ${DEP_INSTALL_DIR}/include)
set(DEP_LIB_DIR ${DEP_INSTALL_DIR}/lib)

# spdlog: fast logger library
# spdlog를 다운받아서 가져옴. 로그를 보는데 용이.
ExternalProject_Add(
    dep_spdlog
    GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
    GIT_TAG "v1.x"
    GIT_SHALLOW 1
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
    TEST_COMMAND ""
)

# Dependency 리스트 및 라이브러리 파일 리스트 추가
set(DEP_LIST ${DEP_LIST} dep_spdlog)
# OS 별 생성 파일이 .lib 와 .a 파일로 달라지므로, Mac 기준에 맞춰서 해당 디렉토리에 있는 링크를 제대로 맞춰줌.
if (APPLE)
    set(DEP_LIBS ${DEP_LIBS} libspdlog.a)
endif()
if (WIN32)
    set(DEP_LIBS ${DEP_LIBS} spdlog$<$<CONFIG:Debug>:d>)
endif()

# glfw 설치
ExternalProject_Add(
    dep_glfw
    GIT_REPOSITORY "https://github.com/glfw/glfw.git"
    GIT_TAG "3.3.8"
    GIT_SHALLOW 1
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    TEST_COMMAND ""
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR} # install 디렉토리 설정
        -DGLFW_BUILD_EXAMPLES=OFF
        -DGLFW_BUILD_TESTS=OFF
        -DGLFW_BUILD_DOCS=OFF
        #glfw example test docs를 사용하지 않겠다는 의미
)

set(DEP_LIST ${DEP_LIST} dep_glfw)
set(DEP_LIBS ${DEP_LIBS} glfw3)

# glad
ExternalProject_Add(
    dep_glad
    GIT_REPOSITORY "https://github.com/Dav1dde/glad"
    GIT_TAG "v0.1.34"
    GIT_SHALLOW 1
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
        -DGLAD_INSTALL=ON
    TEST_COMMAND ""
    )
set(DEP_LIST ${DEP_LIST} dep_glad)
set(DEP_LIBS ${DEP_LIBS} glad)

# 
ExternalProject_Add(
    dep_stb #타겟이름
    GIT_REPOSITORY "https://github.com/nothings/stb"
    GIT_TAG "master"
    GIT_SHALLOW 1
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    TEST_COMMAND ""
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy #${CMAKE_COMMAND}에 cmake가 들어간다
        ${PROJECT_BINARY_DIR}/dep_stb-prefix/src/dep_stb/stb_image.h # ${PROJECT_BINARY_DIR}/dep_stb-prefix에 stb라이브러리가 클론된다. 그 파일의 헤더파일을 
        ${DEP_INSTALL_DIR}/include/stb/stb_image.h # 이 위치로 카피한다.
)
set(DEP_LIST ${DEP_LIST} dep_stb)

# #glm
# ExternalProject_Add(
#     dep_glm #타겟이름
#     GIT_REPOSITORY "https://github.com/g-truc/glm"
#     GIT_TAG "0.9.9.8"
#     GIT_SHALLOW 1
#     UPDATE_COMMAND ""
#     PATCH_COMMAND ""
#     CONFIGURE_COMMAND ""
#     BUILD_COMMAND ""
#     TEST_COMMAND ""
#     INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory #${CMAKE_COMMAND}에 cmake가 들어간다
#         ${PROJECT_BINARY_DIR}/dep_glm-prefix/src/dep_glm/glm 
#         ${DEP_INSTALL_DIR}/include/glm
# )
# set(DEP_LIST ${DEP_LIST} dep_glm)


add_library(imgui #타겟 네임
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui.cpp
    imgui/imgui_impl_glfw.cpp
    imgui/imgui_impl_opengl3.cpp # 컴파일할 코드들
    )
target_include_directories(imgui PRIVATE ${DEP_INCLUDE_DIR})
add_dependencies(imgui ${DEP_LIST}) # 디펜던시 리스트가 우선 컴파일 되고 나서 그다음 imgui가 컴파일이 되도록 설정
set(DEP_INCLUDE_DIR ${DEP_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/imgui) #디펜던시 인클루드 디렉토리에 imgui를 넣어놓는다 :: src 파일에서 단순히 imgui를 찾지 못하므로 디펜던시 인클루드 디렉토리에 imgui를 넣는것이다.
set(DEP_LIST ${DEP_LIST} imgui) #디펜던시 리스트에 imgui를 넣는다.
set(DEP_LIBS ${DEP_LIBS} imgui) #디펜던시 라이브러리 리스트 안에 imgui를 넣는다.