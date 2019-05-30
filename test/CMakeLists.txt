set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -Wno-deprecated-declarations")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wno-deprecated-declarations")

add_executable(test_cl_h test_cl_h.cpp)
target_link_libraries(test_cl_h opencl_loader)
install(TARGETS test_cl_h RUNTIME DESTINATION ${EXECUTABLE_OUTPUT_PATH})

add_executable(test_cl_hpp test_cl_hpp.cpp)
target_link_libraries(test_cl_hpp opencl_loader)
install(TARGETS test_cl_hpp RUNTIME DESTINATION ${EXECUTABLE_OUTPUT_PATH})

add_executable(clinfo clinfo.cpp)
target_link_libraries(clinfo opencl_loader)
install(TARGETS clinfo RUNTIME DESTINATION ${EXECUTABLE_OUTPUT_PATH})
