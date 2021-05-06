#define VGA_ADDR 0xb8000

void print(char*);
void printchar(char);
void video_cleanup();
void video_move_cursor(short);