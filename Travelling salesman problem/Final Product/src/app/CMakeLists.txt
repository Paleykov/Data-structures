add_executable(
    app
)

target_link_libraries(
    app
    PUBLIC
    code
)

target_sources(
    app
    PUBLIC
    main.cpp
)