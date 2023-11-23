#pragma once
namespace Base::ragdoll {
    class on_q {
    public:
        bool m_enabled{ false };
        void init();
    } inline g_on_q;

    class no_ragdoll {
    public:
        bool m_enabled{ false };
        void init();
        void on_disable();
    } inline g_no_ragdoll;

    class bound_ankles {
    public:
        bool m_enabled{ false };
        void init();
        void on_disable();
    } inline g_bound_ankles;

    class fly {
    public:
        bool m_enabled{ false };
        void init();
    } inline g_fly;

    class die {
    public:
        bool m_enabled{ false };
        void tick();
    } inline g_die;

}
