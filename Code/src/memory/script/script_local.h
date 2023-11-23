#pragma once
#include <cstddef>
#include <winnt.h>
#include <type_traits>
#include <src/rage/script/scriptIdBase.hpp>

namespace Base {
	class script_local {
	public:
		explicit script_local(rage::scrThread* thread, std::size_t index);
		explicit script_local(PVOID stack, std::size_t index);
		explicit script_local(std::size_t index);
	public:
		script_local set(rage::scrThread* thread);
		script_local set(void* stack);
	public:
		script_local at(std::ptrdiff_t index);
		script_local at(std::ptrdiff_t index, std::size_t size);
	public:
		template<typename T>
		std::enable_if_t<std::is_pointer_v<T>, T> as() {
			return static_cast<T>(get());
		}
		template<typename T>
		std::enable_if_t<std::is_lvalue_reference_v<T>, T> as(){
			return *static_cast<std::add_pointer_t<std::remove_reference_t<T>>>(get());
		}
	private:
		void* get();
		std::size_t m_index;
		PVOID m_stack;
	};
}
