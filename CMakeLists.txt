cmake_minimum_required(VERSION 2.8)
project(caveman)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11 -pedantic -ggdb3 -pthread")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -Werror -O3")

file(GLOB SRC
  "*.cc"
)

add_executable(caveman ${SRC})
target_link_libraries(caveman ${OpenCV_LIBS})

add_custom_target(deep_clean
  COMMAND find . -iwholename '*cmake*' -not -name CMakeLists.txt -not -name cmake_deps -not -name '*Find*' -delete
  COMMAND find . -iwholename '*Makefile*' -delete
)
