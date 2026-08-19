cmake_minimum_required(VERSION 3.22)
project(WiliamStudio VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Aponte JUCE_DIR para a instalação local do JUCE ou use add_subdirectory.
add_subdirectory(${JUCE_DIR} JUCE)

juce_add_gui_app(WiliamStudio PRODUCT_NAME "Wiliam Studio")
target_sources(WiliamStudio PRIVATE Main.cpp MainComponent.cpp ChordDetector.cpp)
target_compile_definitions(WiliamStudio PRIVATE JUCE_WEB_BROWSER=0 JUCE_USE_CURL=0)
target_link_libraries(WiliamStudio PRIVATE juce::juce_gui_extra juce::juce_audio_utils)
