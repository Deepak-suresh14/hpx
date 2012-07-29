//  Copyright (c) 2007-2012 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_PREPROCESSED_SERVER_DETAIL_APPLY_HELPER_HPP)
#define HPX_PREPROCESSED_SERVER_DETAIL_APPLY_HELPER_HPP

#if HPX_ACTION_ARGUMENT_LIMIT <= 5
#include <hpx/components/dataflow/server/detail/preprocessed/apply_helper_5.hpp>
#elif HPX_ACTION_ARGUMENT_LIMIT <= 10
#include <hpx/components/dataflow/server/detail/preprocessed/apply_helper_10.hpp>
#elif HPX_ACTION_ARGUMENT_LIMIT <= 20
#include <hpx/components/dataflow/server/detail/preprocessed/apply_helper_20.hpp>
#elif HPX_ACTION_ARGUMENT_LIMIT <= 30
#include <hpx/components/dataflow/server/detail/preprocessed/apply_helper_30.hpp>
#elif HPX_ACTION_ARGUMENT_LIMIT <= 40
#include <hpx/components/dataflow/server/detail/preprocessed/apply_helper_40.hpp>
#elif HPX_ACTION_ARGUMENT_LIMIT <= 50
#include <hpx/components/dataflow/server/detail/preprocessed/apply_helper_50.hpp>
#else
#error "HPX_ACTION_ARGUMENT_LIMIT out of bounds for preprocessed headers"
#endif

#endif
