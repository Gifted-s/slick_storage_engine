

add_executable(ValueLogTests test_value_log.c)
target_link_libraries(ValueLogTests wisckey)
add_test(NAME ValueLogTests COMMAND ValueLogTests)


add_executable(SSTableTests test_sstables.c)
target_link_libraries(SSTableTests wisckey)
add_test(NAME SSTableTests COMMAND SSTableTests)