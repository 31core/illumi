#include <kernel/fs/file.h>


int main()
{
fs_create();
fs_init();
struct file fp;
file_create(&fp, "/kernel.sys");
return 0;
}