cmake_minimum_required(VERSION 2.8)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include/)

add_executable(activity executor.cpp log.cpp simpleactivity.cpp baseactivity.cpp main.cpp)

target_link_libraries(activity boost_thread)

install(TARGETS activity RUNTIME DESTINATION bin)
