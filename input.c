int get_sw(void){
  volatile int *switches = (volatile int *) 0x04000010;
  return *switches & 0x3FF;
}

int get_btn(void){
  volatile int *button = (volatile int *) 0x040000D0;
  return *button & 0x1;
}

int btn_pressed(void){
  static int prev = 0;       
  int now = get_btn();
  int edge = (now == 1 && prev == 0);
  prev = now;
  return edge;
}

int move_x(void){
    int switches = get_sw();
    int plusx  = switches & 0x1;
    int minusx = (switches >> 1) & 0x1;
    return plusx - minusx;
}

int move_y(void){
    int switches = get_sw();
    int plusy  = (switches >> 2) & 0x1;
    int minusy = (switches >> 3) & 0x1;
    return plusy - minusy;
}

int reset(void){
  int reset_switch = get_sw();
  return ((reset_switch >> 8) & 0x1) & ((reset_switch >> 9) & 0x1);
}