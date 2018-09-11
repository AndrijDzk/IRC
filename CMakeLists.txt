cmake_minimum_required(VERSION 3.9)
FUNCTION(PREPEND var prefix)
   SET(listVar "")
   FOREACH(f ${ARGN})
      LIST(APPEND listVar "${prefix}/${f}")
   ENDFOREACH(f)
   SET(${var} "${listVar}" PARENT_SCOPE)
ENDFUNCTION(PREPEND)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(INC Includes)

set(COMMON_INC common)
set(COMMON_SDIR common)

set(NAME1 server)
project(${NAME1} C)

set(NAME2 client)
project(${NAME2} C)

set(LIBFT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/libft)
set(LIBFT_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/libft/CMakeFiles)

set(SDIR Srcs)

set(SOURCES1
	"parse_args.c"
	"start_server.c"
	"choose_necessary_sockets.c"
	"examine_sockets.c"
	"accept_incoming_connection.c"
	"read_incoming_data.c"
	"process_incoming_data.c"
	"send_data_to_clients.c"
	"disconnect_clients.c"
	"main.c")
PREPEND(SOURCES_REL1 ${NAME1} ${SOURCES1})
PREPEND(SOURCES_REL1 ${SDIR} ${SOURCES_REL1})

set(SOURCES2
	"main.c")
PREPEND(SOURCES_REL2 ${NAME2} ${SOURCES2})
PREPEND(SOURCES_REL2 ${SDIR} ${SOURCES_REL2})

set(COMMON_SOURCES
	"send_msg.c"
	"receive_msg.c")
PREPEND(COMMON_SOURCES_REL ${COMMON_SDIR} ${COMMON_SOURCES})
PREPEND(COMMON_SOURCES_REL ${SDIR} ${COMMON_SOURCES_REL})

set(CMAKE_C_FLAGS "-Wall -Werror -Wextra")

message("EXECUTABLE_OUTPUT_PATH - ${EXECUTABLE_OUTPUT_PATH}")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "Executable output dir" FORCE)
message("EXECUTABLE_OUTPUT_PATH - ${EXECUTABLE_OUTPUT_PATH}")

add_executable(${NAME1} ${SOURCES_REL1} ${COMMON_SOURCES_REL})
target_include_directories(${NAME1} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INC}/${NAME1})
target_include_directories(${NAME1} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INC}/${COMMON_INC})

add_executable(${NAME2} ${SOURCES_REL2} ${COMMON_SOURCES_REL})
target_include_directories(${NAME2} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INC}/${NAME2})
target_include_directories(${NAME2} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INC}/${COMMON_INC})

add_subdirectory(${LIBFT_SOURCE_DIR} ${LIBFT_BINARY_DIR})

target_link_libraries(${NAME1} libft.a)
include_directories(${LIBFT_INC})

target_link_libraries(${NAME2} libft.a)
include_directories(${LIBFT_INC})