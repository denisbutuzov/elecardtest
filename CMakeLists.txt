CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
PROJECT(ElecardTestProject)

FIND_PACKAGE(Threads REQUIRED)

SET(HEADERS FstreamWrapper.h
            AbstractImage.h
            BmpImage.h
            Yuv420Image.h
            Yuv420Video.h)

SET(SOURCES FstreamWrapper.cpp
            AbstractImage.cpp
            BmpImage.cpp
            Yuv420Image.cpp
            Yuv420Video.cpp)

SET(LIBS Threads::Threads)

ADD_EXECUTABLE(${PROJECT_NAME} main.cpp ${SOURCES} ${HEADERS})
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBS})
