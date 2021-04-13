
cmake_minimum_required (VERSION 3.8)

project ("FinalProjectTemplate")

# Add source to this project's executable.
add_executable (FinalProjectTemplate "FinalProject.cpp"  "game.cpp")

# TODO: Add tests and install targets if needed.

target_include_directories(FinalProjectTemplate PUBLIC "./SFML-2.5.1/include" )
target_link_directories(FinalProjectTemplate PUBLIC "./SFML-2.5.1/lib")

target_link_libraries(FinalProjectTemplate PUBLIC "sfml-system-d" "sfml-window-d" "sfml-graphics-d" "sfml-audio-d")