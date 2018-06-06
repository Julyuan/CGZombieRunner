cmake_minimum_required(VERSION 3.9)
project(GLUT_Learning)

set(CMAKE_CXX_STANDARD 11)

find_library(OPENGL OpenGL)
find_library(GLFW glfw)
#find_library(GLEW glew)
find_library(GLUT glut)
#configure_file("${PROJECT_SOURCE_DIR}/include/glad/glad.h")
find_library(ASSIMP assimp)

add_subdirectory(vendors)
include_directories(include vendors)

add_library(GLAD src/glad.c include/glad/glad.h)
#set(GLAD_LIB ${GLAD_LIB} GLAD)
add_library(Shader include/Shader.h src/Shader.cpp)
add_library(Mesh include/Mesh.h src/Mesh.cpp)


add_library(Model include/stb_image.h include/Model.h src/Model.cpp)
target_link_libraries(Shader ${OPENGL} GLAD)
target_link_libraries(Mesh Shader)
target_link_libraries(Model Mesh ASSIMP)


add_executable(DreamCar DreamCar.cpp include/stb_image.h include/Camera.h)
target_link_libraries(DreamCar Shader Mesh Model ${GLFW} ${OPENGL})

add_executable(mybloodcar GLUTcar.cpp)
target_link_libraries(mybloodcar ${GLUT} ${OPENGL})


