#ifndef _AIPI_LITE_DISPLAY_H_
#define _AIPI_LITE_DISPLAY_H_

#include "display/lcd_display.h"

// Keeps the stock layout (status bar, chat bubbles, pairing text, emoji) and re-skins it to the
// study palette. Replacing SetupUI caused two layouts to draw into the same 128x128 screen, which
// is exactly the overlap we saw on the device. Extend, never replace.
class AipiLiteDisplay : public SpiLcdDisplay {
public:
    AipiLiteDisplay(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_handle_t panel,
                    int width, int height, int offset_x, int offset_y,
                    bool mirror_x, bool mirror_y, bool swap_xy);
    ~AipiLiteDisplay();

    void SetupUI() override;
};

#endif
