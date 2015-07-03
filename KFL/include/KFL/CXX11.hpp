/**
 * @file CXX11.hpp
 * @author Minmin Gong
 *
 * @section DESCRIPTION
 *
 * This source file is part of KFL, a subproject of KlayGE
 * For the latest info, see http://www.klayge.org
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * You may alternatively use this source under the terms of
 * the KlayGE Proprietary License (KPL). You can obtained such a license
 * from http://www.klayge.org/licensing/.
 */

#ifndef _KFL_CXX11_HPP
#define _KFL_CXX11_HPP

#pragma once

#ifndef KLAYGE_CXX11_CORE_NULLPTR_SUPPORT
const class nullptr_t
{
public:
	template <typename T>
	operator T*() const
	{
		return reinterpret_cast<T*>(0);
	}

	template <typename C, typename T>
	operator T C::*() const
	{
		return reinterpret_cast<T C::*>(0);
	}

private:
	void operator&() const;
} nullptr = {};
#endif

#ifdef KLAYGE_CXX11_CORE_FOREACH_SUPPORT
	#define KLAYGE_FOREACH(var, col) for (var : col)
#else
	#include <boost/foreach.hpp>
	#define KLAYGE_FOREACH(var, col) BOOST_FOREACH(var, col)
#endif
#ifdef KLAYGE_CXX11_CORE_NOEXCEPT_SUPPORT
	#define KLAYGE_NOEXCEPT noexcept
	#define KLAYGE_NOEXCEPT_IF(predicate) noexcept((predicate))
	#define KLAYGE_NOEXCEPT_EXPR(expression) noexcept((expression))
#else
	#define KLAYGE_NOEXCEPT throw()
	#define KLAYGE_NOEXCEPT_IF(predicate)
	#define KLAYGE_NOEXCEPT_EXPR(expression) false
#endif
#ifdef KLAYGE_CXX11_CORE_OVERRIDE_SUPPORT
	#define KLAYGE_OVERRIDE override
	#define KLAYGE_FINAL final
#else
	#define KLAYGE_OVERRIDE
	#define KLAYGE_FINAL
#endif

#ifdef KLAYGE_CXX11_CORE_RVALUE_REFERENCES_SUPPORT
	#include <utility>
	namespace KlayGE
	{
		using std::move;
	}
#else
	#include <boost/move/move.hpp>
	namespace KlayGE
	{
		using boost::move;
	}
#endif

#ifdef KLAYGE_CXX11_LIBRARY_ALGORITHM_SUPPORT
	#ifndef KLAYGE_PLATFORM_ANDROID
		#if defined(KLAYGE_COMPILER_GCC) && defined(__MINGW32__)
			// Fix C++ linkage problem in MinGW 4.8.2
			#include <intrin.h>
		#endif
	#endif
	#include <algorithm>
	namespace KlayGE
	{
		using std::copy_if;
	}
#else
	namespace KlayGE
	{
		template<typename InputIterator, typename OutputIterator, typename Predicate>
		OutputIterator copy_if(InputIterator first, InputIterator last,
								OutputIterator dest_first,
								Predicate p)
		{
			for (InputIterator iter = first; iter != last; ++ iter)
			{
				if (p(*iter))
				{
					*dest_first = *iter;
					++ dest_first;
				}
			}

			return dest_first;
		}
	}
#endif

#ifdef KLAYGE_CXX11_LIBRARY_ATOMIC_SUPPORT
#ifndef _M_CEE
	#include <atomic>
	namespace KlayGE
	{
		using std::atomic;
		using std::atomic_thread_fence;
		using std::atomic_signal_fence;

		using std::memory_order_relaxed;
		using std::memory_order_release;
		using std::memory_order_acquire;
		using std::memory_order_consume;
		using std::memory_order_acq_rel;
		using std::memory_order_seq_cst;
	}
#endif
#else
	#ifdef KLAYGE_COMPILER_MSVC
		#pragma warning(push)
		#pragma warning(disable: 4100)
	#endif
	#include <boost/atomic.hpp>
	#ifdef KLAYGE_COMPILER_MSVC
		#pragma warning(pop)
	#endif
	namespace KlayGE
	{
		using boost::atomic;
		using boost::atomic_thread_fence;
		using boost::atomic_signal_fence;

		using boost::memory_order_relaxed;
		using boost::memory_order_release;
		using boost::memory_order_acquire;
		using boost::memory_order_consume;
		using boost::memory_order_acq_rel;
		using boost::memory_order_seq_cst;
	}
#endif

#ifdef KLAYGE_CXX11_LIBRARY_CHRONO_SUPPORT
	#include <chrono>
	namespace KlayGE
	{
		namespace chrono = std::chrono;
	}
#else
	#include <boost/chrono.hpp>
	namespace KlayGE
	{
		namespace chrono = boost::chrono;
	}
#endif

#ifdef KLAYGE_CXX11_LIBRARY_SMART_PTR_SUPPORT
	#include <functional>
	#include <memory>
	namespace KlayGE
	{
		using std::bind;
		using std::function;
		namespace placeholders
		{
			using std::placeholders::_1;
			using std::placeholders::_2;
			using std::placeholders::_3;
			using std::placeholders::_4;
			using std::placeholders::_5;
			using std::placeholders::_6;
			using std::placeholders::_7;
			using std::placeholders::_8;
			using std::placeholders::_9;
		}

		using std::shared_ptr;
		using std::weak_ptr;
		using std::enable_shared_from_this;
		using std::static_pointer_cast;
		using std::dynamic_pointer_cast;
		using std::ref;
		using std::cref;
	}

#ifdef KLAYGE_CXX11_LIBRARY_MEM_FN_SUPPORT
	namespace KlayGE
	{
		using std::mem_fn;
	}
#else
	#if defined(KLAYGE_PLATFORM_WIN32) && defined(KLAYGE_CPU_X86)
		#ifndef BOOST_MEM_FN_ENABLE_STDCALL
			#define BOOST_MEM_FN_ENABLE_STDCALL
		#endif
	#endif
	
	#include <boost/mem_fn.hpp>
	namespace KlayGE
	{
		using boost::mem_fn;
	}
#endif
#else
	#if defined(KLAYGE_PLATFORM_WIN32) && defined(KLAYGE_CPU_X86)
		#ifndef BOOST_MEM_FN_ENABLE_STDCALL
			#define BOOST_MEM_FN_ENABLE_STDCALL
		#endif
	#endif
	#include <boost/mem_fn.hpp>
	#include <boost/bind.hpp>
	#include <boost/function.hpp>
	#include <boost/ref.hpp>
	#ifdef KLAYGE_COMPILER_MSVC
		#pragma warning(push)
		#pragma warning(disable: 6011)
	#endif
	#include <boost/smart_ptr.hpp>
	#ifdef KLAYGE_COMPILER_MSVC
		#pragma warning(pop)
	#endif
	namespace KlayGE
	{
		using boost::bind;
		using boost::mem_fn;
		using boost::function;
		namespace placeholders
		{
			static boost::arg<1> _1;
			static boost::arg<2> _2;
			static boost::arg<3> _3;
			static boost::arg<4> _4;
			static boost::arg<5> _5;
			static boost::arg<6> _6;
			static boost::arg<7> _7;
			static boost::arg<8> _8;
			static boost::arg<9> _9;
		}

		using boost::shared_ptr;
		using boost::weak_ptr;
		using boost::enable_shared_from_this;
		using boost::static_pointer_cast;
		using boost::dynamic_pointer_cast;
		using boost::ref;
		using boost::cref;
	}
#endif

#if !(((defined(KLAYGE_COMPILER_GCC) || defined(KLAYGE_COMPILER_CLANG)) && (__GLIBCXX__ >= 20130531)) \
		|| defined(KLAYGE_PLATFORM_DARWIN) || defined(KLAYGE_PLATFORM_IOS) \
		|| (defined(KLAYGE_COMPILER_MSVC) && (KLAYGE_COMPILER_VERSION >= 140)))
#include <type_traits>
namespace std
{
	template <typename T>
	struct is_trivially_destructible
	{
		static const bool value = std::has_trivial_destructor<T>::value;
	};
}
#endif

#endif		// _KFL_CXX11_HPP
