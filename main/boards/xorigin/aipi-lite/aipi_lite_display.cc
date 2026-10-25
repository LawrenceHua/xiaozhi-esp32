#include "aipi_lite_display.h"
#include <esp_log.h>
#include <cstring>

#define LCD_BG      lv_color_hex(0x071419)
#define LCD_INK     lv_color_hex(0xD8F3ED)
#define LCD_ACCENT  lv_color_hex(0x175E60)
#define LCD_MUTED   lv_color_hex(0x5D686C)

static const char* TAG = "AipiLiteDisplay";

AipiLiteDisplay::AipiLiteDisplay(esp_lcd_panel_io_handle_t panel_io,
                                 esp_lcd_panel_handle_t panel, int width, int height,
                                 int offset_x, int offset_y, bool mirror_x,
                                 bool mirror_y, bool swap_xy)
    : SpiLcdDisplay(panel_io, panel, width, height, offset_x, offset_y, mirror_x,
                    mirror_y, swap_xy) {
    ESP_LOGI(TAG, "study display up (%dx%d)", width, height);
}

AipiLiteDisplay::~AipiLiteDisplay() = default;

void AipiLiteDisplay::SetupUI() {
    DisplayLockGuard lock(this);
    lv_obj_t* screen = lv_screen_active();
    lv_obj_clean(screen);
    lv_obj_set_style_bg_color(screen, LCD_BG, 0);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, 0);
    lv_obj_remove_flag(screen, LV_OBJ_FLAG_SCROLLABLE);

    // wordmark
    lv_obj_t* mark = lv_label_create(screen);
    lv_label_set_text(mark, "AIPi");
    lv_obj_set_style_text_color(mark, LCD_ACCENT, 0);
    lv_obj_set_style_text_font(mark, &lv_font_montserrat_14, 0);
    lv_obj_align(mark, LV_ALIGN_TOP_MID, 0, 10);

    // one status word, the centre of the screen
    status_label_ = lv_label_create(screen);
    lv_label_set_text(status_label_, "Ready");
    lv_obj_set_style_text_color(status_label_, LCD_INK, 0);
    lv_obj_set_style_text_font(status_label_, &lv_font_montserrat_28, 0);
    lv_obj_align(status_label_, LV_ALIGN_CENTER, 0, -8);

    // what she actually said, in one small line
    said_label_ = lv_label_create(screen);
    lv_label_set_text(said_label_, "");
    lv_obj_set_style_text_color(said_label_, LCD_MUTED, 0);
    lv_obj_set_style_text_font(said_label_, &lv_font_montserrat_14, 0);
    lv_label_set_long_mode(said_label_, LV_LABEL_LONG_DOT);
    lv_obj_set_width(said_label_, 116);
    lv_obj_set_style_text_align(said_label_, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(said_label_, LV_ALIGN_CENTER, 0, 26);

    // one button hint, bottom
    hint_label_ = lv_label_create(screen);
    lv_label_set_text(hint_label_, "Hold to talk");
    lv_obj_set_style_text_color(hint_label_, LCD_MUTED, 0);
    lv_obj_set_style_text_font(hint_label_, &lv_font_montserrat_14, 0);
    lv_obj_align(hint_label_, LV_ALIGN_BOTTOM_MID, 0, -8);

    ESP_LOGI(TAG, "study layout applied");
}

void AipiLiteDisplay::SetStatusWord(const char* word) {
    DisplayLockGuard lock(this);
    if (status_label_ && word) {
        lv_label_set_text(status_label_, word);
        lv_obj_align(status_label_, LV_ALIGN_CENTER, 0, -8);
    }
}

void AipiLiteDisplay::SetChatMessage(const char* role, const char* content) {
    DisplayLockGuard lock(this);
    if (!said_label_) return;
    if (content && std::strlen(content) > 0) {
        lv_label_set_text(said_label_, content);
    } else {
        lv_label_set_text(said_label_, "");
    }
}
