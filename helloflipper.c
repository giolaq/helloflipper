#include <furi.h>
#include <furi_hal.h>

#include <gui/gui.h>
#include <input/input.h>
#include <notification/notification-messages.h>

#include "helloflipper_icons.h"

typedef struct {
    uint8_t x, y;
} ImagePosition;

typedef struct {
    uint8_t x, y;
    bool active;
    uint32_t timer;
} PixelProjectile;

static ImagePosition image_position = {.x = 0, .y = 0};
static PixelProjectile pixel_projectile = {.x = 0, .y = 0, .active = false, .timer = 0};

// Screen is 128x64 px
static void app_draw_callback(Canvas* canvas, void* ctx) {
    UNUSED(ctx);

    canvas_clear(canvas);
    canvas_draw_icon(canvas, image_position.x % 128, image_position.y % 64, &I_airplane);
    if (pixel_projectile.active) {
        canvas_draw_pixel(canvas, pixel_projectile.x, pixel_projectile.y);
    }
}

static void app_input_callback(InputEvent* input_event, void* ctx) {
    furi_assert(ctx);

    FuriMessageQueue* event_queue = ctx;
    furi_message_queue_put(event_queue, input_event, FuriWaitForever);
}

static void update_pixel_projectile(uint32_t elapsed_time) {
    if (pixel_projectile.active) {
        pixel_projectile.timer += elapsed_time;
        if (pixel_projectile.timer >= 500) {
            pixel_projectile.timer -= 500;
            pixel_projectile.x += 1;
        }

        if (pixel_projectile.x >= 128) {
            pixel_projectile.active = false;
        }
    }
}

int32_t helloflipper_main(void* p) {
    UNUSED(p);
    FuriMessageQueue* event_queue = furi_message_queue_alloc(8, sizeof(InputEvent));

    ViewPort* view_port = view_port_alloc();
    view_port_draw_callback_set(view_port, app_draw_callback, view_port);
    view_port_input_callback_set(view_port, app_input_callback, event_queue);

    Gui* gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, view_port, GuiLayerFullscreen);

    InputEvent event;
    uint32_t elapsed_time;

    bool running = true;
    while(running) {
        elapsed_time = 100;
        if(furi_message_queue_get(event_queue, &event, elapsed_time) == FuriStatusOk) {
            if((event.type == InputTypePress) || (event.type == InputTypeRepeat)) {
                switch(event.key) {
                case InputKeyLeft:
                    image_position.x -= 2;
                    break;
                case InputKeyRight:
                    image_position.x += 2;
                    break;
                case InputKeyUp:
                    image_position.y -= 2;
                    break;
                case InputKeyDown:
                    image_position.y += 2;
                    break;
                case InputKeyOk:
                    if (!pixel_projectile.active) {
                        pixel_projectile.x = image_position.x % 128;
                        pixel_projectile.y = image_position.y % 64;
                        pixel_projectile.active = true;
                    }
                    break;
                default:
                    running = false;
                    break;
                }
            }
       
