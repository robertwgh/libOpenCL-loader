
add_executable(test_cl_h test_cl_h.cpp)
target_link_libraries(test_cl_h cl_loader)

install(TARGETS test_cl_h DESTINATION ${EXECUTABLE_OUTPUT_PATH})

