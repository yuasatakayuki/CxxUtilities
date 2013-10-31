CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(CxxUtilities CXX)

INSTALL(DIRECTORY includes/CxxUtilities DESTINATION include)

message (STATUS "${PROJECT_NAME} will be installed to ${CMAKE_INSTALL_PREFIX} (give -DCMAKE_INSTALL_PREFIX=path to cmake to modify this)")