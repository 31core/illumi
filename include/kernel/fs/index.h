void index_area_create(); //创建引导块
void index_area_load(); //加载引导块
void index_area_save(); //保存引导块 
int index_area_get_used(unsigned int); //获取块是否使用
void index_area_set_used(unsigned int); //标记block已经使用
void index_area_set_unused(unsigned int); //标记block为可用