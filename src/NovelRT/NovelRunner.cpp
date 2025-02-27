// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>

namespace NovelRT
{
    NovelRunner::NovelRunner(int32_t displayNumber,
                             const std::string& windowTitle,
                             Windowing::WindowMode windowMode,
                             uint32_t targetFrameRate,
                             bool transparency)
        : SceneConstructionRequested(Utilities::Event<>()),
          Update(Utilities::Event<Timing::Timestamp>()),
          _exitCode(1),
          _stepTimer(Utilities::Lazy<std::unique_ptr<Timing::StepTimer>>(std::function<Timing::StepTimer*()>(
              [targetFrameRate] { return new Timing::StepTimer(targetFrameRate); }))),
          _novelWindowingService(std::make_shared<Windowing::WindowingService>()),
          _novelInteractionService(std::make_shared<Input::InteractionService>(getWindowingService())),
          _novelAudioService(std::make_shared<Audio::AudioService>()),
#if NOVELRT_INK
          _novelDotNetRuntimeService(std::make_shared<DotNet::RuntimeService>()),
#endif
          _novelRenderer(std::make_shared<Graphics::RenderingService>(getWindowingService())),
          _novelDebugService(std::make_shared<DebugService>(SceneConstructionRequested, getRenderer()))
    {
        if (!glfwInit())
        {
            const char* err = "";
            glfwGetError(&err);
            _loggingService.logError("GLFW ERROR: {}", err);
            throw Exceptions::InitialisationFailureException("Unable to continue! Cannot start without a glfw window.",
                                                             err);
        }
        _novelWindowingService->initialiseWindow(displayNumber, windowTitle, windowMode, transparency);
        _novelRenderer->initialiseRendering();
        _novelInteractionService->setScreenSize(_novelWindowingService->getWindowSize());
        _novelWindowingService->WindowTornDown += [this] { _exitCode = 0; };
    }

    int32_t NovelRunner::runNovel()
    {
        while (_exitCode)
        {
            _stepTimer.getActual()->tick(Update);
            _novelDebugService->accumulateStatistics(_stepTimer.getActual()->getFramesPerSecond(),
                                                     (uint32_t)_stepTimer.getActual()->getTotalTime().getSecondsFloat(),
                                                     _stepTimer.getActual()->getFrameCount());
            _novelRenderer->beginFrame();
            SceneConstructionRequested();
            _novelRenderer->endFrame();
            _novelInteractionService->consumePlayerInput();
            _novelInteractionService->executeClickedInteractable();
            _novelAudioService->checkSources();
        }

        _novelWindowingService->tearDown();
        return _exitCode;
    }

    std::shared_ptr<Graphics::RenderingService> NovelRunner::getRenderer() const noexcept
    {
        return _novelRenderer;
    }

    std::shared_ptr<Input::InteractionService> NovelRunner::getInteractionService() const noexcept
    {
        return _novelInteractionService;
    }

    std::shared_ptr<DebugService> NovelRunner::getDebugService() const noexcept
    {
        return _novelDebugService;
    }

    std::shared_ptr<Audio::AudioService> NovelRunner::getAudioService() const noexcept
    {
        return _novelAudioService;
    }
#if NOVELRT_INK
    std::shared_ptr<DotNet::RuntimeService> NovelRunner::getDotNetRuntimeService() const noexcept
    {
        return _novelDotNetRuntimeService;
    }
#endif
    std::shared_ptr<Windowing::WindowingService> NovelRunner::getWindowingService() const noexcept
    {
        return _novelWindowingService;
    }

    NovelRunner::~NovelRunner()
    {
        glfwTerminate();
    }
} // namespace NovelRT
