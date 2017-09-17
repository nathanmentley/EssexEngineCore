#files

file(GLOB EssexEngineCore_HEADERS
    "src/System/Core/*.h"
    "src/System/Core/*/*.h"
    "src/System/Core/Utils/ImGui/*.h"
)
file(GLOB EssexEngineCore_SRC
    ${EssexEngineCore_HEADERS}
    "src/System/Core/*.cpp"
    "src/System/Core/*/*.cpp"
    "src/System/Core/Utils/ImGui/*.cpp"
)

#setup headers

file(COPY ${EssexEngineCore_HEADERS} DESTINATION "${CMAKE_BINARY_DIR}/lib/include/EssexEngineCore/")

#setup build

add_library(EssexEngineCore SHARED ${EssexEngineCore_SRC})