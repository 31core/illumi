#define KEY_UP 1
#define KEY_DOWN 2

extern struct fifo8 key_fifo;
extern char key_caps;
extern char key_shift;

int input(char*);
char input_char();
unsigned char input_code();
