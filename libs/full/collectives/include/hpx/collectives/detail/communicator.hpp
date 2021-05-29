//  Copyright (c) 2020-2021 Hartmut Kaiser
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <hpx/config.hpp>

#if !defined(HPX_COMPUTE_DEVICE_CODE)

#include <hpx/actions_base/component_action.hpp>
#include <hpx/assert.hpp>
#include <hpx/async_base/launch_policy.hpp>
#include <hpx/components/client.hpp>
#include <hpx/components_base/server/component_base.hpp>
#include <hpx/datastructures/any.hpp>
#include <hpx/futures/future.hpp>
#include <hpx/lcos_local/and_gate.hpp>
#include <hpx/synchronization/spinlock.hpp>
#include <hpx/thread_support/assert_owns_lock.hpp>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <mutex>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace hpx { namespace traits {

    // This type can be specialized for a particular collective operation
    template <typename Communicator, typename Operation>
    struct communication_operation;
}}    // namespace hpx::traits

namespace hpx { namespace collectives { namespace detail {

    ///////////////////////////////////////////////////////////////////////////
    class communicator_server
      : public hpx::components::component_base<communicator_server>
    {
        using mutex_type = lcos::local::spinlock;

    public:
        communicator_server()    //-V730
          : num_values_(0)
          , num_sites_(0)
          , site_(0)
          , needs_initialization_(false)
          , data_available_(false)
        {
            HPX_ASSERT(false);    // shouldn't ever be called
        }

        communicator_server(
            std::size_t num_sites, std::size_t site, std::size_t num_values)
          : data_()
          , gate_(num_sites)
          , num_values_(num_values)
          , num_sites_(num_sites)
          , site_(site)
          , needs_initialization_(true)
          , data_available_(false)
        {
            HPX_ASSERT(num_values != 0);
            HPX_ASSERT(num_sites != 0);
        }

        ///////////////////////////////////////////////////////////////////////
        // generic get action, dispatches to proper operation
        template <typename Operation, typename Result, typename... Args>
        Result get_result(std::size_t which, Args... args)
        {
            return std::make_shared<traits::communication_operation<
                communicator_server, Operation>>(*this)
                ->template get<Result>(which, std::move(args)...);
        }

        template <typename Operation, typename Result, typename... Args>
        struct communication_get_action
          : hpx::actions::make_action<Result (communicator_server::*)(
                                          std::size_t, Args...),
                &communicator_server::template get_result<Operation, Result,
                    Args...>,
                communication_get_action<Operation, Result, Args...>>::type
        {
        };

        template <typename Operation, typename Result, typename... Args>
        Result set_result(std::size_t which, Args... args)
        {
            return std::make_shared<traits::communication_operation<
                communicator_server, Operation>>(*this)
                ->template set<Result>(which, std::move(args)...);
        }

        template <typename Operation, typename Result, typename... Args>
        struct communication_set_action
          : hpx::actions::make_action<Result (communicator_server::*)(
                                          std::size_t, Args...),
                &communicator_server::template set_result<Operation, Result,
                    Args...>,
                communication_set_action<Operation, Result, Args...>>::type
        {
        };

    private:
        // re-initialize data
        template <typename T, typename Lock>
        void reinitialize_data(Lock& l)
        {
            HPX_ASSERT_OWNS_LOCK(l);
            if (needs_initialization_)
            {
                needs_initialization_ = false;
                data_ = std::vector<T>(num_values_);
            }
        }

        template <typename T, typename Lock>
        std::vector<T>& access_data(Lock& l)
        {
            HPX_ASSERT_OWNS_LOCK(l);
            reinitialize_data<T>(l);
            return hpx::any_cast<std::vector<T>&>(data_);
        }

        template <typename Lock>
        void invalidate_data(Lock& l)
        {
            HPX_ASSERT_OWNS_LOCK(l);
            if (needs_initialization_)
            {
                needs_initialization_ = true;
                data_available_ = false;
                data_.reset();
            }
        }

    private:
        template <typename Communicator, typename Operation>
        friend struct hpx::traits::communication_operation;

    private:
        mutex_type mtx_;
        hpx::unique_any_nonser data_;
        lcos::local::and_gate gate_;
        std::size_t const num_values_;
        std::size_t const num_sites_;
        std::size_t const site_;
        bool needs_initialization_;
        bool data_available_;
    };

    ///////////////////////////////////////////////////////////////////////////
    HPX_EXPORT hpx::components::client<detail::communicator_server>
    create_communicator(char const* basename,
        std::size_t num_sites = std::size_t(-1),
        std::size_t generation = std::size_t(-1),
        std::size_t this_site = std::size_t(-1), std::size_t root_site = 0,
        std::size_t num_values = std::size_t(-1));
}}}    // namespace hpx::collectives::detail

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace collectives {

    using communicator = hpx::components::client<detail::communicator_server>;
}}    // namespace hpx::collectives

#endif    // COMPUTE_HOST_CODE
