cmake_minimum_required(VERSION 3.10)

# Nome do projeto
project(TexturedSphere)

# Versão do padrão C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Adiciona o diretório src ao include path
include_directories(${PROJECT_SOURCE_DIR}/src)

# Adiciona o arquivo fonte
add_executable(main src/main.cpp)

# Encontra as bibliotecas necessárias
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# Liga as bibliotecas encontradas ao executável
target_link_libraries(main OpenGL::GL GLUT::GLUT)

# Define o diretório de saída para o executável
set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
