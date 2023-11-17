cmake_minimum_required(VERSION 3.5)

project(pong)

# Set the C++ standard to C++11 or higher
set(CMAKE_CXX_STANDARD 17)

# Add the raylib library
find_package(raylib REQUIRED)

# Add your source files
set(SOURCES
    main.cpp
)

# Create the executable
add_executable(pong ${SOURCES})
if (WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
if (NOT WIN32)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mwindows")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
endif()
# Link against raylib
target_link_libraries(pong PRIVATE raylib)
if(APPLE)
    target_link_libraries(snake PRIVATE "-framework OpenGL")
    target_link_libraries(snake PRIVATE "-framework Cocoa")
    target_link_libraries(snake PRIVATE "-framework IOKit")
    target_link_libraries(snake PRIVATE "-framework CoreVideo")
endif()