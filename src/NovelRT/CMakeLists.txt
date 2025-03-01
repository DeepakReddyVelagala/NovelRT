find_package(BZip2 ${NOVELRT_BZIP2_VERSION} REQUIRED)
find_package(flac ${NOVELRT_FLAC_VERSION} REQUIRED)
find_package(Freetype ${NOVELRT_FREETYPE_VERSION} REQUIRED)
find_package(glad ${NOVELRT_GLAD_VERSION} REQUIRED
  COMPONENTS
    REPRODUCIBLE
    PROFILE core
    SPEC gl
    API gl=4.0,gles2=3.0
)
find_package(glfw3 ${NOVELRT_GLFW_VERSION} REQUIRED)
find_package(glm ${NOVELRT_GLM_VERSION} REQUIRED)
find_package(Ogg ${NOVELRT_OGG_VERSION} REQUIRED)
find_package(OpenAL ${NOVELRT_OPENAL_VERSION} REQUIRED)
find_package(Opus ${NOVELRT_Opus_VERSION} REQUIRED)
find_package(PNG ${NOVELRT_PNG_VERSION} REQUIRED)
find_package(SndFile ${NOVELRT_SNDFILE_VERISON} REQUIRED)
find_package(spdlog ${NOVELRT_SPDLOG_VERSION} REQUIRED)
find_package(Vorbis ${NOVELRT_VORBIS_VERSION} REQUIRED)
find_package(Microsoft.GSL ${NOVELRT_GSL_VERSION} REQUIRED)
find_package(Vulkan ${NOVELRT_VULKAN_VERSION} REQUIRED)
find_package(vulkan-memory-allocator ${NOVELRT_VULKAN_MEMORY_ALLOCATOR_VERSION} REQUIRED)

set(SOURCES
  Animation/SpriteAnimator.cpp

  Atom.cpp

  Audio/AudioService.cpp

  DebugService.cpp

  Ecs/Catalogue.cpp
  Ecs/ComponentBufferMemoryContainer.cpp
  Ecs/ComponentCache.cpp
  Ecs/EcsUtils.cpp
  Ecs/EntityCache.cpp
  Ecs/SparseSetMemoryContainer.cpp
  Ecs/SystemScheduler.cpp
  Ecs/UnsafeComponentView.cpp

  Experimental/EngineConfig.cpp
  Experimental/Graphics/GraphicsMemoryBlock.cpp
  Experimental/Graphics/GraphicsMemoryBlockCollection.cpp
  Experimental/Graphics/GraphicsPipeline.cpp
  Experimental/Graphics/GraphicsPipelineInput.cpp
  Experimental/Graphics/GraphicsPipelineInputElement.cpp
  Experimental/Graphics/GraphicsPipelineResource.cpp
  Experimental/Graphics/GraphicsPipelineSignature.cpp
  Experimental/Graphics/ShaderProgram.cpp
  Experimental/Graphics/Vulkan/VulkanGraphicsAdapter.cpp
  Experimental/Graphics/Vulkan/VulkanGraphicsAdapterSelector.cpp
  Experimental/Graphics/Vulkan/VulkanGraphicsBuffer.cpp
  Experimental/Graphics/Vulkan/VulkanGraphicsContext.cpp
  Experimental/Graphics/Vulkan/VulkanGraphicsDevice.cpp
  Experimental/Graphics/Vulkan/VulkanGraphicsFence.cpp
  Experimental/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.cpp
  Experimental/Graphics/Vulkan/VulkanGraphicsMemoryBlock.cpp
  Experimental/Graphics/Vulkan/VulkanGraphicsMemoryBlockCollection.cpp
  Experimental/Graphics/Vulkan/VulkanGraphicsPipeline.cpp
  Experimental/Graphics/Vulkan/VulkanGraphicsPipelineSignature.cpp
  Experimental/Graphics/Vulkan/VulkanGraphicsProvider.cpp
  Experimental/Graphics/Vulkan/VulkanGraphicsSurfaceContext.cpp
  Experimental/Graphics/Vulkan/VulkanGraphicsTexture.cpp
  Experimental/Graphics/Vulkan/VulkanShaderProgram.cpp
  Experimental/Threading/VolatileState.cpp
  Experimental/Windowing/Glfw/GlfwWindowingDevice.cpp

  Graphics/BasicFillRect.cpp
  Graphics/Camera.cpp
  Graphics/FontSet.cpp
  Graphics/ImageRect.cpp
  Graphics/RenderingService.cpp
  Graphics/RenderObject.cpp
  Graphics/RGBAConfig.cpp
  Graphics/TextRect.cpp
  Graphics/Texture.cpp

  Input/BasicInteractionRect.cpp
  Input/InteractionObject.cpp
  Input/InteractionService.cpp

  LoggingService.cpp

  Maths/GeoBounds.cpp
  Maths/QuadTree.cpp

  NovelRunner.cpp

  Timing/StepTimer.cpp

  Transform.cpp

  Utilities/Misc.cpp

  Windowing/WindowingService.cpp

  WorldObject.cpp
)

if(NOVELRT_INCLUDE_INK)
  message("NovelRT is compiling with Ink / C# Support.")
  set(SOURCES
    DotNet/RuntimeService.cpp
    Ink/InkService.cpp
    Ink/Story.cpp
    ${SOURCES}
  )
endif()

add_library(Engine SHARED ${SOURCES})

if(NOVELRT_INCLUDE_INK)
  add_dependencies(Engine Dotnet)
  target_compile_definitions(Engine PRIVATE NOVELRT_INK)
  target_link_libraries(Engine PUBLIC
    CoreCLR::nethost
  )
  find_package(Dotnet ${NOVELRT_DOTNET_VERSION} REQUIRED)
endif()

set_property(TARGET Engine PROPERTY OUTPUT_NAME "NovelRT")

if(WIN32)
  set_property(TARGET Engine PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
endif()

target_compile_features(Engine PUBLIC cxx_std_17)
target_include_directories(Engine
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(MSVC)
  target_compile_options(Engine
    PRIVATE
      /W4
      /WX
      /wd4611
      /MP
  )
  get_target_property(opts Engine COMPILE_OPTIONS)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(Engine
    PRIVATE
      -pedantic
      -pedantic-errors
      -Wall
      -Wextra
      -Werror
      -Wno-float-equal
      -Wno-padded
  )
else()
  target_compile_options(Engine
    PRIVATE
      -pedantic
      -pedantic-errors
      -Wall
      -Wextra
      -Werror
      -Wno-c++98-compat
      -Wno-c++98-compat-pedantic
      -Wno-float-equal
      -Wno-padded
      -Wno-reserved-id-macro
  )
endif()

target_link_libraries(Engine
  PUBLIC
    BZip2::BZip2
    FLAC::FLAC
    Freetype::Freetype
    glad::glad
    glfw::glfw
    glm::glm
    Ogg::Ogg
    OpenAL::OpenAL
    Opus::Opus
    PNG::PNG
    SndFile::SndFile
    spdlog::spdlog
    Vorbis::Vorbis
    Microsoft.GSL::Microsoft.GSL
    Vulkan::Vulkan
    vulkan-memory-allocator::vulkan-memory-allocator
)

if(WIN32)
  target_link_libraries(Engine
    PUBLIC
      Winmm
  )

  if(NOVELRT_INCLUDE_CONAN_PATHS)
    add_custom_command(TARGET Engine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
      ${CMAKE_BINARY_DIR}/thirdparty
      $<TARGET_FILE_DIR:Engine>)
  endif()
endif()
