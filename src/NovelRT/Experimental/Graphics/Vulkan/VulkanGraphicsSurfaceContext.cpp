// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Graphics/Vulkan/Graphics.Vulkan.h>

namespace NovelRT::Experimental::Graphics::Vulkan
{

    VulkanGraphicsSurfaceContext::VulkanGraphicsSurfaceContext(std::shared_ptr<IGraphicsSurface> surface,
                                                               const std::shared_ptr<VulkanGraphicsProvider>& provider)
        : GraphicsSurfaceContext(std::move(surface), std::static_pointer_cast<GraphicsProvider>(provider)),
          _logger(LoggingService(NovelRT::Utilities::Misc::CONSOLE_LOG_GFX)),
          _vulkanSurface(VK_NULL_HANDLE)
    {
        std::shared_ptr<IGraphicsSurface> targetSurface = GetSurface();
        switch (targetSurface->GetKind())
        {
            case GraphicsSurfaceKind::Glfw:
            {
                auto func =
                    reinterpret_cast<VkResult (*)(VkInstance, void*, const VkAllocationCallbacks*, VkSurfaceKHR*)>(
                        targetSurface->GetContextHandle());

                VkResult funcResult =
                    func(GetProvider()->GetVulkanInstance(), targetSurface->GetHandle(), nullptr, &_vulkanSurface);
                if (funcResult != VK_SUCCESS)
                {
                    throw Exceptions::InitialisationFailureException("Failed to initialise the VkSurfaceKHR.",
                                                                     funcResult);
                }

                _logger.logInfoLine("VkSurfaceKHR successfully created.");
                break;
            }
            case GraphicsSurfaceKind::Unknown:
            case GraphicsSurfaceKind::Android:
            case GraphicsSurfaceKind::Wayland:
            case GraphicsSurfaceKind::Win32:
            case GraphicsSurfaceKind::Xcb:
            case GraphicsSurfaceKind::Xlib:
            default:
                throw Exceptions::NotSupportedException(
                    "The specified graphics surface kind is not supported by this graphics implementation.");
        }
    }

    VulkanGraphicsSurfaceContext::~VulkanGraphicsSurfaceContext()
    {
        vkDestroySurfaceKHR(GetProvider()->GetVulkanInstance(), _vulkanSurface, nullptr);
        _logger.logInfoLine("VkSurface successfully destroyed.");
    }
} // namespace NovelRT::Experimental::Graphics::Vulkan
