CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
PROJECT(ElecardTestProject)

SET(HEADERS BmpImage.h
            Yuv420Image.h
            Yuv420Video.h)

SET(SOURCES BmpImage.cpp
            Yuv420Image.cpp
            Yuv420Video.cpp)

ADD_EXECUTABLE(${PROJECT_NAME} main.cpp ${SOURCES} ${HEADERS})
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
