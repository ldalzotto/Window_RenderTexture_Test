cmake_minimum_required(VERSION 3.12)
project(NativeWindowTest VERSION 0.0.1)

find_package(Vulkan REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_TYPE "")

file(GLOB_RECURSE NATIVE_WINDOW_PRIVATE "./*.cpp")
file(GLOB_RECURSE NATIVE_WINDOW_PUBLIC "./*.h")

add_executable(NativeWindowTest WIN32 "./src/Main.cpp"  "src/Texture.h" "src/Texture.cpp")
