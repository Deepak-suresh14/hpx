////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Thomas Heller
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cuda.h>

#include <hpx/config.hpp>

namespace hpx { namespace util { namespace hardware {

    HPX_HOST_DEVICE std::uint64_t timestamp()
    {
        std::uint64_t cur;
        asm volatile("mov.u64 %0, %%globaltimer;" : "=l"(cur));
        return cur;
    }

}}}    // namespace hpx::util::hardware