cmake_minimum_required(VERSION 2.6)
project(projet_geomatique)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(Projet_Geomatique_SRCS Projet_Geomatique.cpp main.cpp)

qt4_automoc(${Projet_Geomatique_SRCS})
add_executable(projet_geomatique ${Projet_Geomatique_SRCS})
target_link_libraries(projet_geomatique ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

install(TARGETS projet_geomatique RUNTIME DESTINATION bin)
