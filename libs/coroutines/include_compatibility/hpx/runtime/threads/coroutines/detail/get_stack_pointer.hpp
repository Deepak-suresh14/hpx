//  Copyright (c) 2019 Ste||ar Group
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/config.hpp>
#include <hpx/coroutines/config/defines.hpp>
#include <hpx/coroutines/detail/get_stack_pointer.hpp>

#if defined(HPX_COROUTINES_HAVE_DEPRECATION_WARNINGS)
#if defined(HPX_MSVC)
#pragma message(                                                               \
    "The header hpx/runtime/threads/coroutines/detail/get_stack_pointer.hpp is deprecated, \
    please include hpx/coroutines/detail/get_stack_pointer.hpp instead")
#else
#warning                                                                       \
    "The header hpx/runtime/threads/coroutines/detail/get_stack_pointer.hpp is deprecated, \
    please include hpx/coroutines/detail/get_stack_pointer.hpp instead"
#endif
#endif
