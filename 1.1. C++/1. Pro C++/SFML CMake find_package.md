```cmake
The package sfml provides CMake targets:

    find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
    target_link_libraries(main PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

    # If you want SFML to provide an implementation of main():
    target_link_libraries(main PRIVATE sfml-main)
```
