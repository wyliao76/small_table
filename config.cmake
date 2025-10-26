set(PROJECT_NAME "template-c")
set(PROJECT_VERSION "1.0.0")
set(PROJECT_DESCRIPTION "Template C Project")
set(PROJECT_LANGUAGE "C")

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Common compiler flags
set(STANDARD_FLAGS
        -D_POSIX_C_SOURCE=200809L
        -D_XOPEN_SOURCE=700
        #-D_GNU_SOURCE
        #-D_DARWIN_C_SOURCE
        #-D__BSD_VISIBLE
        -Werror
)

# Define targets
set(EXECUTABLE_TARGETS server)
set(LIBRARY_TARGETS "")

set(server_SOURCES
        src/server.c
        src/table.c
)

set(main_HEADERS
        include/table.h
)

set(main_LINK_LIBRARIES "")

