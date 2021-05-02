extern struct fifo8 key_fifo;
extern char key_caps;
extern char key_shift;

void input(char*); //输入字符串
char inputchar(); //单字符输入
unsigned char inputcode(); //获取一个输入按键的键码
