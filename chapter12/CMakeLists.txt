find_package(Threads REQUIRED)
add_executable(12.2.putenv 12.2.putenv.c)
target_link_libraries(12.2.putenv Threads::Threads)
