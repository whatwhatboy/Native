#pragma once
#include "src/utility/common/common.h"

namespace Base {
    template <typename t>
    concept span_compatible_type = requires(t a) {
        std::span{ a };
    };

    class byte_patch {
    public:
        template <typename t>
        byte_patch(t address, std::remove_pointer_t<std::remove_reference_t<t>> value) : m_address(address) {
            m_size = sizeof(std::remove_pointer_t<std::remove_reference_t<t>>);
            m_original_bytes = std::make_unique<uint8_t[]>(m_size);
            memcpy(m_original_bytes.get(), m_address, m_size);
            m_value = std::make_unique<uint8_t[]>(m_size);
            memcpy(m_value.get(), &value, m_size);
        }

        template <typename t, typename arr, std::size_t s>
        byte_patch(t address, std::span<arr, s> span) : m_address((void*)address) {
            m_size = span.size();
            m_original_bytes = std::make_unique<byte[]>(m_size);
            memcpy(m_original_bytes.get(), m_address, m_size);
            m_value = std::make_unique<byte[]>(m_size);
            for (int32_t i{}; i != m_size; ++i)
                m_value[i] = span[i];
        }

        virtual ~byte_patch() {
            restore();
        }

    public:
        template <typename t>
        static const std::unique_ptr<byte_patch>& make(t address, std::remove_pointer_t<std::remove_reference_t<t>> val) {
            return m_patches.emplace_back(std::unique_ptr<byte_patch>(new byte_patch(address, val)));
        }

        template <typename t, typename arr> requires span_compatible_type<arr>
        static const std::unique_ptr<byte_patch>& make(t address, arr span_compatible) {
            return m_patches.emplace_back(std::unique_ptr<byte_patch>(new byte_patch(address, std::span{ span_compatible })));
        }

    public:
        void apply() const {
            memcpy(m_address, m_value.get(), m_size);
        }

        void restore() const {
            memcpy(m_address, m_original_bytes.get(), m_size);
        }

    public:
        void remove() const {
            if (const auto val = std::find(m_patches.begin(), m_patches.end(), this); val != m_patches.end()) {
                m_patches.erase(val);
            }
        }

        static void remove_all() {
            m_patches.clear();
        }

    public:
        friend bool operator== (const std::unique_ptr<byte_patch>& a, const byte_patch* b) {
            return a->m_address == b->m_address;
        }

    protected:
        static inline std::vector<std::unique_ptr<byte_patch>> m_patches{};

    public:
        void* m_address{};
        size_t m_size{};

    public:
        std::unique_ptr<uint8_t[]> m_value{};
        std::unique_ptr<uint8_t[]> m_original_bytes{};
    };
}
