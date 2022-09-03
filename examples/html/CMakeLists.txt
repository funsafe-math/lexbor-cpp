cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -fsanitize=address)

file(GLOB APP_SOURCES *.cpp)
foreach(testsourcefile ${APP_SOURCES})
  # testcase name is filename without extension
  string(REPLACE ".cpp" "" testname ${testsourcefile})
  add_executable(${testname} ${testsourcefile})
  target_link_libraries(${testname} lexbor_wrapper lexbor)
  add_test(${testname} ${testname})
endforeach(testsourcefile ${APP_SOURCES})
