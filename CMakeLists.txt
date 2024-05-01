cmake_minimum_required(VERSION 3.28)
project(dofus_test)

set(CMAKE_CXX_STANDARD 23)

find_path(DETOURS_INCLUDE_DIRS "detours/detours.h")
find_library(DETOURS_LIBRARY detours REQUIRED)



add_library(dofus_test SHARED dll/src/main.cpp
        dll/src/HookEngine.cpp
        dll/src/packets/impl/ChatMessagePacket.cpp
        dll/src/packets/impl/PlayerInventoryPacket.cpp
        dll/src/packets/impl/MapMovementPacket.cpp
        dll/src/packets/impl/BasicPongPacket.cpp
        dll/src/packets/impl/BasicAckPacket.cpp
        dll/src/packets/impl/NoMovementPacket.cpp
        dll/src/packets/impl/MultiTabStoragePacket.cpp
        dll/src/packets/impl/MapFightCountPacket.cpp
        dll/src/packets/impl/GameContextRemoveElementPacket.cpp
        dll/src/packets/impl/UnknownPacket.cpp
        dll/src/packets/impl/BasicPingPacket.cpp
        dll/include/packets/IPacket.hpp
)
target_link_libraries(dofus_test PRIVATE ${DETOURS_LIBRARY})
target_include_directories(dofus_test PRIVATE "dll/include" ${DETOURS_INCLUDE_DIRS})
if (MSVC)
    target_compile_options(dofus_test PRIVATE /W4)
else ()
    target_compile_options(dofus_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif ()

add_executable(injector injector/src/main.cpp)
target_link_libraries(injector PRIVATE ${DETOURS_LIBRARY})
target_include_directories(injector PRIVATE ${DETOURS_INCLUDE_DIRS})