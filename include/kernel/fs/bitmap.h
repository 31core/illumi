void bitmap_create(); //创建引导块
void bitmap_load(); //加载引导块
void bitmap_save(); //保存引导块 
int bitmap_get_used(unsigned int); //获取块是否使用
void bitmap_set_used(unsigned int); //标记block已经使用
void bitmap_set_unused(unsigned int); //标记block为可用