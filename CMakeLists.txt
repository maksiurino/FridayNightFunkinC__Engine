cmake_minimum_required(VERSION 4.1)
project(FridayNightFunkinC__Engine LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ============== SFML ==============
include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

# ============== TINYXML2 ==============
FetchContent_Declare(
        tinyxml2
        GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git
        GIT_TAG 11.0.0
)
FetchContent_MakeAvailable(tinyxml2)
# --- JSON (Nlohmann) ---
FetchContent_Declare(nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

add_executable(FridayNightFunkinC__Engine src/main.cpp
        src/musicHandler.cpp
        src/musicHandler.hpp
        src/spriteHandler.cpp
        src/spriteHandler.hpp
        src/includes.hpp
)
target_compile_features(FridayNightFunkinC__Engine PRIVATE cxx_std_17)
target_link_libraries(FridayNightFunkinC__Engine PRIVATE
        SFML::Graphics
        SFML::Audio
        tinyxml2
        nlohmann_json::nlohmann_json
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT FridayNightFunkinC__Engine)

set(RESOURCE_DIRS
        resources
)

foreach(dir ${RESOURCE_DIRS})
    add_custom_command(TARGET FridayNightFunkinC__Engine POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/${dir}
            $<TARGET_FILE_DIR:FridayNightFunkinC__Engine>/${dir}
    )
endforeach()


