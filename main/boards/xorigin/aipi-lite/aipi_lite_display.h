#ifndef _AIPI_LITE_DISPLAY_H_
#define _AIPI_LITE_DISPLAY_H_

#include "display/lcd_display.h"

// The status screen from the interface study: dark sea-glass, one status word, one button hint.
//   paper #f2f0e9  ink #252d31  accent #175e60  lcd #071419  screen ink #d8f3ed
class AipiLiteDisplay : public SpiLcdDisplay {
public:
    AipiLiteDisplay(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_handle_t panel,
                    int width, int height, int offset_x, int offset_y,
                    bool mirror_x, bool mirror_y, bool swap_xy);
    ~AipiLiteDisplay();

    void SetupUI() override;
    void SetChatMessage(const char* role, const char* content) override;
    void SetStatusWord(const char* word);

private:
    lv_obj_t* status_label_ = nullptr;
    lv_obj_t* hint_label_ = nullptr;
    lv_obj_t* said_label_ = nullptr;
};

#endif
