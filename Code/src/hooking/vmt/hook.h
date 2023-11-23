#pragma once
#include <cstdint>

namespace Base {
    class vft_function_data {
    public:
        vft_function_data(void* fn, size_t fn_idx) : m_function(fn), m_function_index(fn_idx) {}
    public:
        template <typename t>
        t get() {
            return t(m_function);
        }
        auto index() {
            return m_function_index + 1;
        }
    public:
        void* m_function{};
        size_t m_function_index{};
    };

    class vft {
    public:
        vft(vft_function_data* vft, size_t vft_size) : m_vft(vft), m_vft_size(vft_size) {}
        vft(std::vector<vft_function_data> vft) : m_vft(vft.data()), m_vft_size(vft.size()) {}
        vft(void* vft, size_t vft_size) : m_vft((vft_function_data*)vft), m_vft_size(vft_size) {}
    public:
        template<typename t>
        auto get() {
            return reinterpret_cast<t>(m_vft);
        }
        auto size() {
            return m_vft_size;
        }
        vft_function_data& operator[](int index) {
            return get<vft_function_data*>()[index];
        }
    private:
        vft_function_data* m_vft{};
        size_t m_vft_size{};
    };

    class vmt_hook {
    public:
        vmt_hook(vft v, vft replacement_vft) :
            m_vft(v.get<uintptr_t**>()), m_vft_size(v.size()),
            m_copy_of_original_vft(*m_vft), m_table_of_replace_functions(std::make_unique<uintptr_t[]>(m_vft_size + 1))
        {
            std::copy_n(m_copy_of_original_vft - 1, m_vft_size + 1, m_table_of_replace_functions.get());
            for (size_t i{}; i != replacement_vft.size(); ++i) {
                hook(replacement_vft[i]);
            }
        }
    public:
        void enable() {
            *m_vft = &m_table_of_replace_functions[1];
        }
        void disable() {
            for (size_t i{}; i != m_vft_size; ++i) {
                if (m_table_of_replace_functions[i + 1] != m_copy_of_original_vft[i]) {
                    m_table_of_replace_functions[i + 1] = m_copy_of_original_vft[i];
                }
            }
            *m_vft = m_copy_of_original_vft;
        }
    public:
        void hook(vft_function_data data) {
            m_table_of_replace_functions[data.index()] = data.get<uint64_t>();
        }
        void unhook(size_t index) {
            m_table_of_replace_functions[index + 1] = m_copy_of_original_vft[index];
        }
    public:
        template <typename type>
        type get_original(size_t index) {
            return type(m_copy_of_original_vft[index]);
        }
    public:
        uintptr_t** m_vft;
        size_t m_vft_size;
    public:
        uintptr_t* m_copy_of_original_vft;
        std::unique_ptr<uintptr_t[]> m_table_of_replace_functions;
    };

}