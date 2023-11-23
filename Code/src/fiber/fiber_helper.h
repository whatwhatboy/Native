#pragma once
#include "src/Core/Logger/Logger.h"

namespace Base {
    class fiber {
    public:
        fiber(std::function<void()> callback, std::optional<std::size_t> stack_size) : m_callback(callback), m_secondary(nullptr), m_primary(nullptr) {
            m_secondary = CreateFiber(stack_size.has_value() ? stack_size.value() : 0, [](void* param) { static_cast<fiber*>(param)->background_tick(); }, this);
        }
        ~fiber() {
            if (m_secondary)
                DeleteFiber(m_secondary);
        }
    public:
        void on_tick() {
            m_primary = GetCurrentFiber();
            if (!m_time.has_value() || m_time.value() <= std::chrono::high_resolution_clock::now())
                SwitchToFiber(m_secondary);
        }
        void wait(std::optional<std::chrono::high_resolution_clock::duration> time = std::nullopt) {
            if (time.has_value())
                m_time = std::chrono::high_resolution_clock::now() + time.value();
            else
                m_time = std::nullopt;
            SwitchToFiber(m_primary);
        }
        static fiber* current() {
            return static_cast<fiber*>(GetFiberData());
        }
    public:
        void background_tick() {
            try {
                m_callback();
            }
            catch (std::runtime_error& ex) {
            }
            while (true) {
                wait();
            }
        }
    public:
        void* m_primary;
        void* m_secondary;
        std::function<void()> m_callback;
        std::optional<std::chrono::high_resolution_clock::time_point> m_time;
    };
    class fiber_manager {
    public:
        void add(std::string name, std::function<void()> callback, std::optional<std::size_t> stack_size = std::nullopt) {
            std::lock_guard lock(m_mutex);
            m_scripts.insert({ name, std::make_unique<fiber>(callback, stack_size) });
        }
        void add(std::string name, std::function<void()> callback, uint8_t count) {
            for (uint8_t i{ count }; i; --i) {
                add(std::format("{}_{}", name, i), callback);
            }
        }
        void remove(std::string name) {
            if (auto var = m_scripts.find(name); var != m_scripts.end()) {
                m_scripts.erase(name);
            }
        }
        void remove_all() {
            std::lock_guard lock(m_mutex);
            m_scripts.clear();
        }
        void on_tick() {
            static bool ensure_main_fiber = (ConvertThreadToFiber(nullptr), true);
            if (!ensure_main_fiber) return;
            std::lock_guard lock(m_mutex);
            for (auto& v : m_scripts) {
                auto& fbr{ v.second };
                fbr->on_tick();
            }
        }
    public:
        std::recursive_mutex m_mutex;
        std::map<std::string, std::unique_ptr<fiber>> m_scripts;
    };
    inline fiber_manager g_fiber_manager;
    class dx_fiber_manager {
    public:
        void add(std::string name, std::function<void()> callback, std::optional<std::size_t> stack_size = std::nullopt) {
            std::lock_guard lock(m_mutex);
            m_scripts.insert({ name, std::make_unique<fiber>(callback, stack_size) });
        }
        void add(std::string name, std::function<void()> callback, uint8_t count) {
            for (uint8_t i{ count }; i; --i) {
                add(std::format("{}_{}", name, i), callback);
            }
        }
        void remove(std::string name) {
            if (auto var = m_scripts.find(name); var != m_scripts.end()) {
                m_scripts.erase(name);
            }
        }
        void remove_all() {
            std::lock_guard lock(m_mutex);
            m_scripts.clear();
        }
        void on_tick() {
            static bool ensure_main_fiber = (ConvertThreadToFiber(nullptr), true);
            if (!ensure_main_fiber) return;
            std::lock_guard lock(m_mutex);
            for (auto& v : m_scripts) {
                auto& fbr{ v.second };
                fbr->on_tick();
            }
        }
    public:
        std::recursive_mutex m_mutex;
        std::map<std::string, std::unique_ptr<fiber>> m_scripts;
    };
    inline dx_fiber_manager g_dx_fiber_manager;
    class fiber_pool {
    public:
        void create_fibers() {
            g_fiber_manager.add("fiber_pool", [=] {
                this->on_tick();
            }, m_number_of_fibers);
        }
        void queue(std::function<void()> func) {
            if (func) {
                std::lock_guard lock(m_mutex);
                m_jobs.emplace(std::move(func));
            }
        }
    private:
        void on_tick() {
            while (true) {
                background_tick();
                fiber::current()->wait();
            }
        }
        void background_tick() {
            std::unique_lock lock(m_mutex);
            if (!m_jobs.empty()) {
                auto job{ std::move(m_jobs.top()) };
                m_jobs.pop();
                lock.unlock();
                std::invoke(std::move(job));
            }
        }
    public:
        std::size_t m_number_of_fibers{ 10 };
        std::recursive_mutex m_mutex;
        std::stack<std::function<void()>> m_jobs{};
    };
    inline fiber_pool g_fiber_pool{};
}
