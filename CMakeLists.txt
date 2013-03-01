project(activity)

add_executable(activity log.cpp printeractivity.cpp baseactivity.cpp main.cpp)

target_link_libraries(activity boost_thread)

install(TARGETS activity RUNTIME DESTINATION bin)
