#include <pebble.h>

#define KEY_DATA 0
#define KEY_LINKS 1

static Window *s_main_window;
static TextLayer *s_text_layer1;
static TextLayer *s_text_layer2;
static TextLayer *s_text_layer3;
static TextLayer *s_text_layer4;
static TextLayer *s_text_layer5;
static TextLayer *s_text_layer6;
static TextLayer *s_text_layer7;
static TextLayer *s_text_layer8;
static TextLayer *s_text_layer9;

static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  static char data_buffer[64];
  static char line1[64];
  static char line2[64];
  static char line3[64];
  static char line4[64];
  static char line5[64];
  static char line6[64];
  static char line7[64];
  static char line8[64];
  static char line9[64];

  Tuple *data_tuple = dict_find(iterator, KEY_DATA);
  //Tuple *links_tuple = dict_find(iterator, KEY_LINKS);
  
  if(data_tuple) {    
    snprintf(data_buffer, sizeof(data_buffer), "%s", data_tuple->value->cstring);
    
  //  APP_LOG(APP_LOG_LEVEL_INFO, data_buffer);
    strncpy(line1, data_buffer, 35);
    text_layer_set_text(s_text_layer1, line1);
    
    strncpy(line2, data_buffer+36, 35);
    text_layer_set_text(s_text_layer2, line2);
    
    strncpy(line3, data_buffer+36, 35);
    text_layer_set_text(s_text_layer3, line3);
   }
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}


static void main_window_load(Window *window){
  static GFont s_tt_font;
  
  s_tt_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ARIAL_NORMAL_9));
  
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  s_text_layer1 = text_layer_create(GRect(2, 15, (bounds.size.w-4), 15));
  s_text_layer2 = text_layer_create(GRect(2, 30, (bounds.size.w-4), 15));
  s_text_layer3 = text_layer_create(GRect(2, 45, (bounds.size.w-4), 15));
  s_text_layer4 = text_layer_create(GRect(2, 60, (bounds.size.w-4), 15));
  s_text_layer5 = text_layer_create(GRect(2, 75, (bounds.size.w-4), 15));
  s_text_layer6 = text_layer_create(GRect(2, 90, (bounds.size.w-4), 15));
  s_text_layer7 = text_layer_create(GRect(2, 105, (bounds.size.w-4), 15));
  s_text_layer8 = text_layer_create(GRect(2, 120, (bounds.size.w-4), 15));
  s_text_layer9 = text_layer_create(GRect(2, 135, (bounds.size.w-4), 15));
  
  
  
  text_layer_set_background_color(s_text_layer1, GColorBlack);
  text_layer_set_text_color(s_text_layer1, GColorWhite);
  text_layer_set_font(s_text_layer1, s_tt_font);
  text_layer_set_text(s_text_layer1, "loading..");
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer1));
  
  text_layer_set_background_color(s_text_layer2, GColorBlack);
  text_layer_set_text_color(s_text_layer2, GColorWhite);
  text_layer_set_font(s_text_layer2, s_tt_font);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer2));

  text_layer_set_background_color(s_text_layer3, GColorBlack);
  text_layer_set_text_color(s_text_layer3, GColorWhite);
  text_layer_set_font(s_text_layer3, s_tt_font);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer3));

  text_layer_set_background_color(s_text_layer4, GColorBlack);
  text_layer_set_text_color(s_text_layer4, GColorWhite);
  text_layer_set_font(s_text_layer4, s_tt_font);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer4));

  text_layer_set_background_color(s_text_layer5, GColorBlack);
  text_layer_set_text_color(s_text_layer5, GColorWhite);
  text_layer_set_font(s_text_layer5, s_tt_font);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer5));

  text_layer_set_background_color(s_text_layer6, GColorBlack);
  text_layer_set_text_color(s_text_layer6, GColorWhite);
  text_layer_set_font(s_text_layer6, s_tt_font);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer6));

  text_layer_set_background_color(s_text_layer7, GColorBlack);
  text_layer_set_text_color(s_text_layer7, GColorWhite);
  text_layer_set_font(s_text_layer7, s_tt_font);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer7));

  text_layer_set_background_color(s_text_layer8, GColorBlack);
  text_layer_set_text_color(s_text_layer8, GColorWhite);
  text_layer_set_font(s_text_layer8, s_tt_font);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer8));

  text_layer_set_background_color(s_text_layer9, GColorBlack);
  text_layer_set_text_color(s_text_layer9, GColorWhite);
  text_layer_set_font(s_text_layer9, s_tt_font);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer9));
}

static void main_window_unload(Window *window){
  text_layer_destroy(s_text_layer1);
  text_layer_destroy(s_text_layer2);
  text_layer_destroy(s_text_layer3);
  text_layer_destroy(s_text_layer4);
  text_layer_destroy(s_text_layer5);
  text_layer_destroy(s_text_layer6);
  text_layer_destroy(s_text_layer7);
  text_layer_destroy(s_text_layer8);
  text_layer_destroy(s_text_layer9);
}


static void init(){
  s_main_window = window_create();
  
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  window_stack_push(s_main_window, true);
  
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
   
  const int inbox_size = 512;
  const int outbox_size = 64;
  app_message_open(inbox_size, outbox_size);
}

static void deinit(){
  window_destroy(s_main_window);
}

int main(){
  init();
  app_event_loop();
  deinit();
}
