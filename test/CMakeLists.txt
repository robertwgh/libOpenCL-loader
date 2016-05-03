
add_executable(test_cl_h test_cl_h.cpp)
target_link_libraries(test_cl_h cl_loader)
install(TARGETS test_cl_h RUNTIME DESTINATION ${EXECUTABLE_OUTPUT_PATH})

add_executable(test_cl_hpp test_cl_hpp.cpp)
LINK_DIRECTORIES(/usr/local/cuda/lib64/)
target_link_libraries(test_cl_hpp cl_loader OpenCL)
install(TARGETS test_cl_hpp RUNTIME DESTINATION ${EXECUTABLE_OUTPUT_PATH})
