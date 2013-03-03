include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include/)

add_executable(activity log.cpp printeractivity.cpp baseactivity.cpp main.cpp)

target_link_libraries(activity boost_thread)

install(TARGETS activity RUNTIME DESTINATION bin)