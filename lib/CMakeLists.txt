project(libtamp)

add_library(tamp "")
target_sources(tamp PRIVATE peterson_lock.cpp bakery_lock.cpp)
target_include_directories(tamp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# vim: tabstop=4 shiftwidth=4 softtabstop=4 expandtab
