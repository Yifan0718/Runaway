cmake_minimum_required(VERSION 3.16)

set(FREEGLUT_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/third_party/freeglut/include")

add_library(
  Framework
  STATIC
  ObjectBase.cpp
  WorldBase.cpp
  TextBase.cpp
  GameManager.cpp
  SpriteManager.cpp
)

if(APPLE)
  # macOS-specific linking
  target_link_libraries(
    Framework 
    PUBLIC 
    SOIL 
    "-framework CoreFoundation" "-framework OpenGL" "-framework GLUT"
  )
  
  target_include_directories(
    Framework
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/src/
  )

else()
  target_link_libraries(
    Framework 
    PUBLIC 
    SOIL 
    freeglut
  )

  target_include_directories(
    Framework
    PUBLIC 
    ${FREEGLUT_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/src/
  )    
endif()
