project(activity)

add_executable(activity printeractivity.cpp baseactivity.cpp main.cpp)

target_link_libraries(activity boost_thread)

install(TARGETS activity RUNTIME DESTINATION bin)
