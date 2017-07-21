find_package(Threads REQUIRED)
add_executable(11.1.thread-struct 11.1.thread-struct.c)
target_link_libraries(11.1.thread-struct Threads::Threads)
