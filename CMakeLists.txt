cmake_minimum_required (VERSION 3.16..3.22)
project (juce_audio_plugin VERSION 0.0.1)

set (juce_dir "/Users/mitchellmcdermott/JUCE")
add_subdirectory (${juce_dir} "${PROJECT_BINARY_DIR}/juce")

option (JUCE_BUILD_EXTRAS "Build JUCE Extras" OFF)
option (JUCE_BUILD_EXAMPLES "Build JUCE Examples" OFF)
option (JUCE_GENERATE_JUCE_HEADER OFF)

file (GLOB_RECURSE SOURCE CONFIGURE_DEPENDS *.cpp)

juce_add_plugin ( ${PROJECT_NAME}
    PRODUCT_NAME ${PROJECT_NAME}
    COMPANY_NAME dev.juce
    PLUGIN_MANUFACTURER_CODE Juce
    PLUGIN_CODE Dem0
    FORMATS Standalone AU VST3
    COPY_PLUGIN_AFTER_BUILD TRUE
)

add_compile_definitions (
    JUCE_DISABLE_JUCE_VERSION_PRINTING=1
    JUCE_DISPLAY_SPLASH_SCREEN=0
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
)

if (JUCE_GENERATE_JUCE_HEADER)
    juce_generate_juce_header (${PROJECT_NAME})
endif()

target_sources ( ${PROJECT_NAME} PRIVATE ${SOURCE})

target_link_libraries ( ${PROJECT_NAME}
PRIVATE
    juce::juce_audio_utils
PUBLIC
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags
)
