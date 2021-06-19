#define VGA_ADDR 0xb8000

void cli_print(char*);
void cli_print_char(char);
void video_cleanup();
void video_move_cursor(short);