#include "src/framework/framework.h"
#include "src/fiber/fiber_helper.h"

namespace Base::Framework::animations {
    inline int speed{ 15 };
    inline void open() {
        static int og_alpha{ g_interface->m_header_text_color.a };
        static int og_alpha2{ g_interface->m_option_unselected_background_color.a };
        g_fiber_pool.queue([=] {
            g_interface->m_menu_opening_animation = true;
            g_interface->m_opened = true;
            g_interface->m_menu_alpha = 0;
            g_interface->m_header_text_color.a = 0;
            g_interface->m_option_selected_background_color.a = 0;
            g_interface->m_option_selected_background_color.a = 0;
            g_interface->m_option_unselected_text_color.a = 0;
            g_interface->m_option_selected_text_color.a = 0;
            g_interface->m_submenu_bar_background_color.a = 0;
            g_interface->m_footer_background_color.a = 0;
            g_interface->m_footer_sprite_color.a = 0;
            g_interface->m_submenu_bar_text_color.a = 0;
            g_interface->m_header_background_color.a = 0;
            g_interface->m_option_unselected_background_color.a = 0;

            while (g_interface->m_menu_alpha < og_alpha) {
                g_interface->m_menu_alpha += speed;
                g_interface->m_header_text_color.a = g_interface->m_menu_alpha;
                g_interface->m_option_selected_background_color.a = g_interface->m_menu_alpha;
                g_interface->m_option_unselected_text_color.a = g_interface->m_menu_alpha;
                g_interface->m_option_selected_text_color.a = g_interface->m_menu_alpha;
                g_interface->m_submenu_bar_background_color.a = g_interface->m_menu_alpha;
                g_interface->m_footer_background_color.a = g_interface->m_menu_alpha;
                g_interface->m_footer_sprite_color.a = g_interface->m_menu_alpha;
                g_interface->m_submenu_bar_text_color.a = g_interface->m_menu_alpha;
                g_interface->m_header_background_color.a = g_interface->m_menu_alpha;
                if (g_interface->m_menu_alpha < og_alpha2)
                    g_interface->m_option_unselected_background_color.a = g_interface->m_menu_alpha;
                fiber::current()->wait(1ms);
            }

            g_interface->m_menu_opening_animation = false;
            });
    }
    inline void close() {
        static int og_alpha{ g_interface->m_header_text_color.a };
        static int og_alpha2{ g_interface->m_option_unselected_background_color.a };
        g_fiber_pool.queue([=] {
            g_interface->m_menu_opening_animation = true;
            g_interface->m_menu_closing_animation = true;
            g_interface->m_opened = true;
            g_interface->m_menu_alpha = 255;
            while (g_interface->m_menu_alpha > 0) {
                g_interface->m_header_text_color.a -= speed;
                g_interface->m_option_selected_background_color.a -= speed;
                g_interface->m_option_unselected_text_color.a -= speed;
                g_interface->m_option_selected_text_color.a -= speed;
                g_interface->m_submenu_bar_background_color.a -= speed;
                g_interface->m_footer_background_color.a -= speed;
                g_interface->m_footer_sprite_color.a -= speed;
                g_interface->m_submenu_bar_text_color.a -= speed;
                g_interface->m_header_background_color.a -= speed;
                if (g_interface->m_option_unselected_background_color.a > speed)
                    g_interface->m_option_unselected_background_color.a -= speed;
                g_interface->m_menu_alpha -= speed;

                fiber::current()->wait(1ms);
            }
            g_interface->m_opened = false;
            g_interface->m_menu_opening_animation = false;
            g_interface->m_menu_closing_animation = false;
            });
    }
}