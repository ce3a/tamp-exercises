project(tests)

macro(_add_test _name)
    set(_tgt test_${_name})
    add_executable(${_tgt} ${_tgt}.cpp)
    target_link_libraries(${_tgt} Boost::unit_test_framework)
    target_compile_definitions(${_tgt} PRIVATE "BOOST_TEST_DYN_LINK=1")
    target_compile_definitions(${_tgt} PRIVATE "BOOST_TEST_MODULE=${_tgt}")
    add_test(${_name} ${_tgt})
endmacro()

find_package (Threads)

_add_test(peterson_lock)
target_link_libraries(test_peterson_lock tamp ${CMAKE_THREAD_LIBS_INIT})

_add_test(bakery_lock)
target_link_libraries(test_bakery_lock tamp ${CMAKE_THREAD_LIBS_INIT})

# vim: tabstop=4 shiftwidth=4 softtabstop=4 expandtab
