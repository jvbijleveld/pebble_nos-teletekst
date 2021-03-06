#include <pebble.h>
#include <functions.h>

#define KEY_DATA 0
#define KEY_LINKS 1
#define KEY_PAGE 2

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
static TextLayer *s_text_layer_detail;
static BitmapLayer *s_tt_header_layer;
static GBitmap *s_tt_header_bitmap;

static int s_selectedLine;
char *link_array[9];

static void resetLines(){
  GColor g_bg = GColorBlack;
  GColor g_txt = GColorWhite;
  
  text_layer_set_background_color(s_text_layer1, g_bg);
  text_layer_set_text_color(s_text_layer1, g_txt);
  
  text_layer_set_background_color(s_text_layer2, g_bg);
  text_layer_set_text_color(s_text_layer2, g_txt);

  text_layer_set_background_color(s_text_layer3, g_bg);
  text_layer_set_text_color(s_text_layer3, g_txt);

  text_layer_set_background_color(s_text_layer4, g_bg);
  text_layer_set_text_color(s_text_layer4, g_txt);
  
  text_layer_set_background_color(s_text_layer5, g_bg);
  text_layer_set_text_color(s_text_layer5, g_txt);
  
  text_layer_set_background_color(s_text_layer6, g_bg);
  text_layer_set_text_color(s_text_layer6, g_txt); 
  
  text_layer_set_background_color(s_text_layer7, g_bg);
  text_layer_set_text_color(s_text_layer7, g_txt);
  
  text_layer_set_background_color(s_text_layer8, g_bg);
  text_layer_set_text_color(s_text_layer8, g_txt);
  
  text_layer_set_background_color(s_text_layer9, g_bg);
  text_layer_set_text_color(s_text_layer9, g_txt); 
}

static void setSelectedLine(int lineNo){
  GColor bg_sel = GColorWhite;
  GColor txt_sel = GColorBlack;
  
  resetLines();
  if(lineNo == 1){
    text_layer_set_background_color(s_text_layer1, bg_sel);
    text_layer_set_text_color(s_text_layer1, txt_sel);
  }
  if(lineNo == 2){
    text_layer_set_background_color(s_text_layer2, bg_sel);
    text_layer_set_text_color(s_text_layer2, txt_sel);
  }
  if(lineNo == 3){
    text_layer_set_background_color(s_text_layer3, bg_sel);
    text_layer_set_text_color(s_text_layer3, txt_sel);
  }
  if(lineNo == 4){
    text_layer_set_background_color(s_text_layer4, bg_sel);
    text_layer_set_text_color(s_text_layer4, txt_sel);
  }
  if(lineNo == 5){
    text_layer_set_background_color(s_text_layer5, bg_sel);
    text_layer_set_text_color(s_text_layer5, txt_sel);
  }
  if(lineNo == 6){
    text_layer_set_background_color(s_text_layer6, bg_sel);
    text_layer_set_text_color(s_text_layer6, txt_sel);
  }
  if(lineNo == 7){
    text_layer_set_background_color(s_text_layer7, bg_sel);
    text_layer_set_text_color(s_text_layer7, txt_sel);
  }
  if(lineNo == 8){
    text_layer_set_background_color(s_text_layer8, bg_sel);
    text_layer_set_text_color(s_text_layer8, txt_sel);
  }
  if(lineNo == 9){
    text_layer_set_background_color(s_text_layer9, bg_sel);
    text_layer_set_text_color(s_text_layer9, txt_sel);
  }
}

static void getPage(char *pageNo){
  DictionaryIterator *out_iter;
  APP_LOG(APP_LOG_LEVEL_DEBUG,"getPage got %s", pageNo);

  AppMessageResult result = app_message_outbox_begin(&out_iter);
  if(result == APP_MSG_OK) {
    dict_write_cstring(out_iter, KEY_PAGE, pageNo);
    result = app_message_outbox_send();
    if(result != APP_MSG_OK) {
      APP_LOG(APP_LOG_LEVEL_ERROR, "Error sending the outbox: %d", (int)result);
    }
  } else {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Error preparing the outbox: %d", (int)result);
  }
}

void builIndexPage(char *data_buffer){
  static char line1[64];
  static char line2[64];
  static char line3[64];
  static char line4[64];
  static char line5[64];
  static char line6[64];
  static char line7[64];
  static char line8[64];
  static char line9[64];
  
  layer_set_hidden((Layer *)s_text_layer_detail, true);
  
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
  strncpy(line7, data_buffer+(6*36), 35);
  text_layer_set_text(s_text_layer7, line7);
  strncpy(line8, data_buffer+(7*36), 35);
  text_layer_set_text(s_text_layer8, line8);
  strncpy(line9, data_buffer+(8*36), 35);
  text_layer_set_text(s_text_layer9, line9);
}

void buildDetailPage(char *data){
  APP_LOG(APP_LOG_LEVEL_DEBUG, "buildDetailPage: %s", data);
  text_layer_set_text(s_text_layer_detail, data);
  layer_set_hidden((Layer *)s_text_layer_detail, false);
}

static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  static char data_buffer[1024];
  static char link_buffer[64];
  
  static char link1[4];
  static char link2[4];
  static char link3[4];
  static char link4[4];
  static char link5[4];
  static char link6[4];
  static char link7[4];
  static char link8[4];
  static char link9[4];

  APP_LOG(APP_LOG_LEVEL_INFO, "inbox_received_callback");
  Tuple *data_tuple = dict_find(iterator, KEY_DATA);
  Tuple *links_tuple = dict_find(iterator, KEY_LINKS);
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "links_tuple %s", links_tuple->value->cstring);
  
  if(links_tuple){
    snprintf(link_buffer, sizeof(link_buffer), "%s", links_tuple->value->cstring);
  }
  if(data_tuple) {    
    snprintf(data_buffer, sizeof(data_buffer), "%s", data_tuple->value->cstring);
  }
  
  if(strlen(link_buffer)> 1){
      //APP_LOG(APP_LOG_LEVEL_DEBUG, "buffer %s", link_buffer);
      
      strncpy(link1, link_buffer, 3);
      strncpy(link2, link_buffer + (1*4), 3);
      strncpy(link3, link_buffer + (2*4), 3);
      strncpy(link4, link_buffer + (3*4), 3);
      strncpy(link5, link_buffer + (4*4), 3);
      strncpy(link6, link_buffer + (5*4), 3);
      strncpy(link7, link_buffer + (6*4), 3);
      strncpy(link8, link_buffer + (7*4), 3);
      strncpy(link9, link_buffer + (8*4), 3);
      
      link_array[0] = link1;
      link_array[1] = link2;
      link_array[2] = link3;
      link_array[3] = link4;
      link_array[4] = link5;
      
      builIndexPage(data_buffer);
  }else{
     buildDetailPage(data_buffer);
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

void up_single_click_handler(ClickRecognizerRef recognizer, void *context) {
  layer_set_hidden((Layer *)s_text_layer_detail, true);
  s_selectedLine--;
  if(s_selectedLine < 1){
    s_selectedLine = 9;
  }
  setSelectedLine((int) s_selectedLine);
}

void down_single_click_handler(ClickRecognizerRef recognizer, void *context) {
  layer_set_hidden((Layer *)s_text_layer_detail, true);
  s_selectedLine++;
  if(s_selectedLine > 9){
    s_selectedLine = 1;
  }
  setSelectedLine((int) s_selectedLine);
}

void select_single_click_handler(ClickRecognizerRef recognizer, void *context) {
  getPage(link_array[(int)(s_selectedLine-1)]);
}
  
void config_provider(Window *window) {
  window_single_click_subscribe(BUTTON_ID_UP, up_single_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_single_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, select_single_click_handler);
}

static void main_window_load(Window *window){
  static GFont s_tt_font;
  GColor g_def_bg = GColorBlack;
  GColor g_def_txt = GColorWhite;
  
  s_tt_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ARIAL_NORMAL_10));
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  
  s_tt_header_layer = bitmap_layer_create(GRect(0, 0, bounds.size.w, 25));
  s_tt_header_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TT_HEADER);
  bitmap_layer_set_bitmap(s_tt_header_layer, s_tt_header_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_tt_header_layer));
   
  s_text_layer1 = text_layer_create(GRect(5, 25, (bounds.size.w-6), 15));
  s_text_layer2 = text_layer_create(GRect(5, 40, (bounds.size.w-6), 15));
  s_text_layer3 = text_layer_create(GRect(5, 55, (bounds.size.w-6), 15));
  s_text_layer4 = text_layer_create(GRect(5, 70, (bounds.size.w-6), 15));
  s_text_layer5 = text_layer_create(GRect(5, 85, (bounds.size.w-6), 15));
  s_text_layer6 = text_layer_create(GRect(5, 100, (bounds.size.w-6), 15));
  s_text_layer7 = text_layer_create(GRect(5, 115, (bounds.size.w-6), 15));
  s_text_layer8 = text_layer_create(GRect(5, 130, (bounds.size.w-6), 15));
  s_text_layer9 = text_layer_create(GRect(5, 145, (bounds.size.w-6), 15));
  s_text_layer_detail = text_layer_create(GRect(5, 25, (bounds.size.w-6), (bounds.size.h-10)));

  text_layer_set_background_color(s_text_layer1, g_def_bg);
  text_layer_set_text_color(s_text_layer1, g_def_txt);
  text_layer_set_background_color(s_text_layer2, g_def_bg);
  text_layer_set_text_color(s_text_layer2, g_def_txt);
  text_layer_set_background_color(s_text_layer3, g_def_bg);
  text_layer_set_text_color(s_text_layer3, g_def_txt);
  text_layer_set_background_color(s_text_layer4, g_def_bg);
  text_layer_set_text_color(s_text_layer4, g_def_txt);
  text_layer_set_background_color(s_text_layer5, g_def_bg);
  text_layer_set_text_color(s_text_layer5, g_def_txt);
  text_layer_set_background_color(s_text_layer6, g_def_bg);
  text_layer_set_text_color(s_text_layer6, g_def_txt);
  text_layer_set_background_color(s_text_layer7, g_def_bg);
  text_layer_set_text_color(s_text_layer7, g_def_txt);
  text_layer_set_background_color(s_text_layer8, g_def_bg);
  text_layer_set_text_color(s_text_layer8, g_def_txt);
  text_layer_set_background_color(s_text_layer9, g_def_bg);
  text_layer_set_text_color(s_text_layer9, g_def_txt);
  text_layer_set_background_color(s_text_layer_detail, g_def_bg);
  text_layer_set_text_color(s_text_layer_detail, g_def_txt);
  
  text_layer_set_font(s_text_layer1, s_tt_font);
  text_layer_set_font(s_text_layer2, s_tt_font);
  text_layer_set_font(s_text_layer3, s_tt_font);
  text_layer_set_font(s_text_layer4, s_tt_font);
  text_layer_set_font(s_text_layer5, s_tt_font);
  text_layer_set_font(s_text_layer6, s_tt_font);
  text_layer_set_font(s_text_layer7, s_tt_font);
  text_layer_set_font(s_text_layer8, s_tt_font);
  text_layer_set_font(s_text_layer9, s_tt_font);
  text_layer_set_font(s_text_layer_detail, s_tt_font);
  
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer1));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer2));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer3));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer4));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer5));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer6));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer7));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer8));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer9));
  
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer_detail));
  
  layer_set_hidden((Layer *)s_text_layer_detail, true);
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
  text_layer_destroy(s_text_layer_detail);
  gbitmap_destroy(s_tt_header_bitmap);
  bitmap_layer_destroy(s_tt_header_layer);
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
   
  const int inbox_size = 1024;
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
