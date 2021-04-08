#define VGA_ADDR 0xb8000

void print(char*); //打印字符串
void printchar(char); //打印单字符
void video_cleanup(); //清屏
void video_move_cursor(short); //移动光标