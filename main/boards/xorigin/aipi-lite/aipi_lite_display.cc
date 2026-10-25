#include "aipi_lite_display.h"
#include <esp_log.h>

// Palette from AIPi interface study 01.
#define STUDY_BG    lv_color_hex(0x071419)
#define STUDY_INK   lv_color_hex(0xD8F3ED)

static const char* TAG = "AipiLiteDisplay";

AipiLiteDisplay::AipiLiteDisplay(esp_lcd_panel_io_handle_t panel_io,
                                 esp_lcd_panel_handle_t panel, int width, int height,
                                 int offset_x, int offset_y, bool mirror_x,
                                 bool mirror_y, bool swap_xy)
    : SpiLcdDisplay(panel_io, panel, width, height, offset_x, offset_y, mirror_x,
                    mirror_y, swap_xy) {
    ESP_LOGI(TAG, "study skin installed (%dx%d)", width, height);
}

AipiLiteDisplay::~AipiLiteDisplay() = default;

void AipiLiteDisplay::SetupUI() {
    SpiLcdDisplay::SetupUI();            // stock layout first: every widget keeps its place

    DisplayLockGuard lock(this);
    lv_obj_t* screen = lv_screen_active();
    if (screen == nullptr) {
        return;
    }
    lv_obj_set_style_bg_color(screen, STUDY_BG, 0);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, 0);
    ESP_LOGI(TAG, "study colours applied to the stock layout");
}
