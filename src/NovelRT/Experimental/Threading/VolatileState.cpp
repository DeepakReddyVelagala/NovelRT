// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Threading/Threading.h>

namespace NovelRT::Experimental::Threading
{
    VolatileState::VolatileState() noexcept : _value(Uninitialised)
    {
    }

    void VolatileState::Transition(uint32_t from, uint32_t to)
    {
        if (TryTransition(from, to))
        {
            throw Exceptions::InvalidOperationException(
                "Transitioning between the two sepcified states failed. From: " + std::to_string(from) +
                " To: " + std::to_string(to));
        }
    }

    bool VolatileState::TryTransition(uint32_t from, uint32_t to, uint32_t* outOptionalOriginalState) noexcept
    {
        if (outOptionalOriginalState != nullptr)
        {
            *outOptionalOriginalState = _value;
        }

        return _value.compare_exchange_strong(to, from, std::memory_order_acq_rel);
    }
} // namespace NovelRT::Experimental::Threading