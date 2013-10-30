cmake_minimum_required(VERSION 2.8)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include/)

set(HEADER_FILES
    ../include/executor.h
    ../include/log.h
    ../include/simpleactivity.h
    ../include/activity.h
    ../include/activityeventhandler.h
    ../include/recoverystarterqueue.h
)
add_executable(activity
               executor.cpp
               log.cpp
               simpleactivity.cpp
               activity.cpp
               main.cpp
               activityeventhandler.cpp
               recoverystarterqueue.cpp
               ${HEADER_FILES}
)

target_link_libraries(activity boost_system boost_thread)

install(TARGETS activity RUNTIME DESTINATION bin)
