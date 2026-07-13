cmake_minimum_required(VERSION 3.22)
project(juno-ds-control-center VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(C:/DEV/JUCE JUCE)

juce_add_gui_app(juno-ds-control-center
    PRODUCT_NAME "Juno DS-88 Control Center"
    ICON_BIG   "${CMAKE_CURRENT_SOURCE_DIR}/assets/logo.png"
    ICON_SMALL "${CMAKE_CURRENT_SOURCE_DIR}/assets/logo.png"
)

target_sources(juno-ds-control-center PRIVATE
    main.cpp
)

target_link_libraries(juno-ds-control-center PRIVATE
    juce::juce_gui_basics
    juce::juce_recommended_config_flags
    juce::juce_recommended_warning_flags
    juce::juce_recommended_lto_flags
    juce::juce_audio_devices
)