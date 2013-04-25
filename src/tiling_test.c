#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#define MY_UUID { 0xBE, 0x17, 0xC5, 0x0C, 0x83, 0x24, 0x49, 0x06, 0xAD, 0x37, 0x5C, 0x3B, 0x52, 0x9A, 0xE0, 0xE1 }

PBL_APP_INFO(MY_UUID,
	 "Tiling test app", "Vlemert",
	 1, 0, /* App version */
	 DEFAULT_MENU_ICON,
	 APP_INFO_STANDARD_APP);

BmpContainer IMG_TILE;
	 
Window window;
Layer layer;

void mainwindow_layer_draw(Layer *layer, GContext *ctx) {
	graphics_draw_bitmap_in_rect(ctx, &IMG_TILE.bmp, GRect(0, 0, 100, 100));
}


void handle_init(AppContextRef ctx) {
	(void)ctx;

	resource_init_current_app(&APP_RESOURCES);
	bmp_init_container(RESOURCE_ID_TILE, &IMG_TILE);
	
	window_init(&window, "Main window");
	
	layer_init(&layer, GRect(-5,-5,100,100));
	layer.update_proc = mainwindow_layer_draw;
	layer_add_child(&window.layer, &layer);
		
	window_stack_push(&window, true /* Animated */);
}

void handle_deinit(AppContextRef ctx) {
  (void)ctx;
  
  bmp_deinit_container(&IMG_TILE);
}

void pbl_main(void *params) {
	PebbleAppHandlers handlers = {
		.init_handler = &handle_init
	};

	app_event_loop(params, &handlers);
}