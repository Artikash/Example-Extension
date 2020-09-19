cmake_minimum_required(VERSION 3.5)

cmake_policy(SET CMP0037 OLD)

add_library(Example\ Extension SHARED Extension.cpp ExtensionImpl.cpp)
add_library(Example\ Visual\ Extension SHARED VisualExtension.cpp ExtensionImpl.cpp)
