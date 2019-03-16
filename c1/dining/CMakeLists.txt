project(dining-philosophers)

find_package (Threads)

add_executable(dining "")
target_sources(dining PRIVATE dining.cpp)
target_link_libraries(dining PRIVATE ${CMAKE_THREAD_LIBS_INIT})

# vim: tabstop=4 shiftwidth=4 softtabstop=4 expandtab
