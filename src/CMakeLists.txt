set(TARGET simplecppcalculator)

add_executable(${TARGET} app.cpp)

target_compile_features(${TARGET} PUBLIC cxx_std_11)

# Include the current directory (where main.cpp is located)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})