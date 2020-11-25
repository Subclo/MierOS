set(KERNEL_SOURCES sources/entry.s)

add_executable(Kernel ${KERNEL_SOURCES})

add_custom_command(TARGET Kernel COMMAND make)