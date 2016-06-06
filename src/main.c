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

static int s_selectedLine;

static void resetLines(){
  text_layer_set_background_color(s_text_layer1, GColorBlack);
  text_layer_set_text_color(s_text_layer1, GColorWhite);
  
  text_layer_set_background_color(s_text_layer2, GColorBlack);
  text_layer_set_text_color(s_text_layer2, GColorWhite);

  text_layer_set_background_color(s_text_layer3, GColorBlack);
  text_layer_set_text_color(s_text_layer3, GColorWhite);

  text_layer_set_background_color(s_text_layer4, GColorBlack);
  text_layer_set_text_color(s_text_layer4, GColorWhite);
  
  text_layer_set_background_color(s_text_layer5, GColorBlack);
  text_layer_set_text_color(s_text_layer5, GColorWhite);
  
  text_layer_set_background_color(s_text_layer6, GColorBlack);
  text_layer_set_text_color(s_text_layer6, GColorWhite); 
}

static void setSelectedLine(int lineNo){
  resetLines();
  if(lineNo == 1){
    text_layer_set_background_color(s_text_layer1, GColorWhite);
    text_layer_set_text_color(s_text_layer1, GColorBlack);
  }
  if(lineNo == 2){
    text_layer_set_background_color(s_text_layer2, GColorWhite);
    text_layer_set_text_color(s_text_layer2, GColorBlack);
  }
  if(lineNo == 3){
    text_layer_set_background_color(s_text_layer3, GColorWhite);
    text_layer_set_text_color(s_text_layer3, GColorBlack);
  }
  if(lineNo == 4){
    text_layer_set_background_color(s_text_layer4, GColorWhite);
    text_layer_set_text_color(s_text_layer4, GColorBlack);
  }
  if(lineNo == 5){
    text_layer_set_background_color(s_text_layer5, GColorWhite);
    text_layer_set_text_color(s_text_layer5, GColorBlack);
  }
  if(lineNo == 6){
    text_layer_set_background_color(s_text_layer6, GColorWhite);
    text_layer_set_text_color(s_text_layer6, GColorBlack);
  }
}

static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  static char data_buffer[512];
  static char line1[256];
  static char line2[256];
  static char line3[256];
  static char line4[256];
  static char line5[256];
  static char line6[256];

  Tuple *data_tuple = dict_find(iterator, KEY_DATA);
  //Tuple *links_tuple = dict_find(iterator, KEY_LINKS);
  
  if(data_tuple) {    
    snprintf(data_buffer, sizeof(data_buffer), "%s", data_tuple->value->cstring);
    
  //  APP_LOG(APP_LOG_LEVEL_INFO, data_buffer);
    strncpy(line1, data_buffer, 35);
    text_layer_set_text(s_text_layer1, line1);
    
    strncpy(line2, data_buffer+36, 35);
    text_layer_set_text(s_text_layer2, line2);
    
    strncpy(line3, data_buffer+(2*36), 35);
    text_layer_set_text(s_text_layer3, line3);
    
    strncpy(line4, data_buffer+(3*36), 35);
    text_layer_set_text(s_text_layer4, line4);
    
    strncpy(line5, data_buffer+(4*36), 35);
    text_layer_set_text(s_text_layer5, line5);
    
    strncpy(line6, data_buffer+(5*36), 35);
    text_layer_set_text(s_text_layer6, line6);
   }
  s_selectedLine = 3;
  setSelectedLine(3);
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

void up_single_click_handler(ClickRecognizerRef recognizer, void *context) {
  s_selectedLine--;
  if(s_selectedLine < 1){
    s_selectedLine = 9;
  }
  setSelectedLine((int) s_selectedLine);
}

void down_single_click_handler(ClickRecognizerRef recognizer, void *context) {
  s_selectedLine++;
  if(s_selectedLine > 9){
    s_selectedLine = 1;
  }
  setSelectedLine((int) s_selectedLine);
}
  
void config_provider(Window *window) {
  window_single_click_subscribe(BUTTON_ID_UP, up_single_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_single_click_handler);
}

static void main_window_load(Window *window){
  static GFont s_tt_font;
  
  s_tt_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ARIAL_NORMAL_9));
  
  Layer *window_layer = window_get_root_layer(window);
  
  //window_set_background_color(*window_layer, GColorBlack);
  GRect bounds = layer_get_bounds(window_layer);
   
  s_text_layer1 = text_layer_create(GRect(5, 20, (bounds.size.w-6), 15));
  s_text_layer2 = text_layer_create(GRect(5, 35, (bounds.size.w-6), 15));
  s_text_layer3 = text_layer_create(GRect(5, 50, (bounds.size.w-6), 15));

  s_text_layer4 = text_layer_create(GRect(5, 65, (bounds.size.w-6), 15));
  s_text_layer5 = text_layer_create(GRect(5, 80, (bounds.size.w-6), 15));
  s_text_layer6 = text_layer_create(GRect(5, 95, (bounds.size.w-6), 15));

  text_layer_set_font(s_text_layer1, s_tt_font);
  text_layer_set_font(s_text_layer2, s_tt_font);
  text_layer_set_font(s_text_layer3, s_tt_font);
  text_layer_set_font(s_text_layer4, s_tt_font);
  text_layer_set_font(s_text_layer5, s_tt_font);
  text_layer_set_font(s_text_layer6, s_tt_font);
  
  //text_layer_set_background_color(s_text_layer, GColorBlack);
  //text_layer_set_text_color(s_text_layer, GColorWhite);
  //text_layer_set_font(s_text_layer, s_tt_font);
  text_layer_set_text(s_text_layer1, "loading..");
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer1));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer2));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer3));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer4));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer5));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer6));
  
}

static void main_window_unload(Window *window){
  text_layer_destroy(s_text_layer1);
  text_layer_destroy(s_text_layer2);
  text_layer_destroy(s_text_layer3);
  text_layer_destroy(s_text_layer4);
  text_layer_destroy(s_text_layer5);
  text_layer_destroy(s_text_layer6);
}


static void init(){
  s_main_window = window_create();
  
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  window_set_background_color(s_main_window, GColorBlack);
  window_stack_push(s_main_window, true);
  
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
  
  window_set_click_config_provider(s_main_window, (ClickConfigProvider) config_provider);
   
  const int inbox_size = 512;
  const int outbox_size = 32;
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
