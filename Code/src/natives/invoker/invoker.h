#pragma once
#include "src/Natives/Crossmap/Crossmap.h"
#include <unordered_map>
class nativeCallContext
{
protected:
	void* m_return;
	uint32_t m_arg_count;
	void* m_args;
	uint32_t m_dataCount;
	Vector3* m_script_vectors[4];
	Vector4 m_vector_results[4];

public:

	void reset() {
		m_arg_count = 0;
		m_dataCount = 0;
	}

	template<typename type>
	inline type getArgument(int index)
	{
		intptr_t* args = (intptr_t*)m_args;
		return *(type*)&args[index];
	}

	template<typename type>
	inline void setArgument(int index, type value)
	{
		intptr_t* values = (intptr_t*)m_args;
		*(type*)&values[index] = value;
	}

	template<typename type>
	inline void setResult(int index, type value)
	{
		intptr_t* return_values = (intptr_t*)m_return;
		*(type*)&return_values[index] = value;
	}

	inline int getArgumentCount()
	{
		return m_arg_count;
	}

	template<typename return_t>
	inline return_t getResult(int index)
	{
		intptr_t* return_values = (intptr_t*)m_return;
		return *(return_t*)&return_values[index];
	}

	inline void* getResultPtr() {
		return m_return;
	}

	void setVectorResults();
};
class NativeContext : public nativeCallContext
{
private:
	enum
	{
		max_native_params = 32,
		arg_size = sizeof(void*),
	};

	uint8_t m_temp_stack[max_native_params * arg_size];

public:
	inline NativeContext()
	{
		m_args = &m_temp_stack;
		m_return = &m_temp_stack;

		m_arg_count = 0;
		m_dataCount = 0;

		memset(m_temp_stack, 0, sizeof(m_temp_stack));
	}

	template <typename type>
	inline void push(type value)
	{
		if (sizeof(type) > arg_size)
			throw "Argument has an invalid size";

		else if (sizeof(type) < arg_size)
			*reinterpret_cast<uintptr_t*>(m_temp_stack + arg_size * m_arg_count) = 0;

		*reinterpret_cast<type*>(m_temp_stack + arg_size * m_arg_count) = value;
		m_arg_count++;
	}

	inline void reverse()
	{
		uintptr_t temp_values[max_native_params];
		uintptr_t* args = (uintptr_t*)m_args;

		for (uint32_t i = 0; i < m_arg_count; i++)
		{
			int target = m_arg_count - i - 1;
			temp_values[target] = args[i];
		}

		memcpy(m_temp_stack, temp_values, sizeof(m_temp_stack));
	}

	template <typename type>
	inline type getResult()
	{
		return *reinterpret_cast<type*>(m_temp_stack);
	}
};
namespace Base {
    class NativeCallContext : public rage::scrNativeCallContext {
    public:
        NativeCallContext();
    private:
        rage::scrValue m_ReturnStack[10];
        rage::scrValue m_ArgStack[100];
    };
    class Invoker {
    public:
        void cache_handlers();
        void begin();
        void end(rage::scrNativeHash hash);
        void Call(uint64_t hash, NativeCallContext* cxt);
    public:
        template <typename T>
        void push_arg(T&& arg) {
			m_call_context.PushArg(std::forward<T>(arg));
        }
        template<typename T>
        T& get_return() {
            return *m_call_context.GetReturn<T>();
        }

    public:
        NativeCallContext m_call_context{};
        std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler> m_cache{};
		bool m_is_handlers_cached{};
    };
    inline std::unique_ptr<Invoker> g_invoker{};
}

template<typename ReturnType, typename ...Args>
inline ReturnType Invoke(rage::scrNativeHash hash, Args&& ...args) {
    using namespace Base;

    g_invoker->begin();
    (g_invoker->push_arg(std::forward<Args>(args)), ...);
    g_invoker->end(hash);

    if constexpr (!std::is_void_v<ReturnType>) {
        return g_invoker->get_return<ReturnType>();
    }
}