void CreateIndexArea(); //创建引导块
void LoadIndexArea(); //加载引导块
void SaveIndexArea(); //保存引导块 
int IndexAreaGetUsed(unsigned int); //获取块是否使用
void IndexAreaSetUsed(unsigned int); //标记block已经使用
void IndexAreaSetUnused(unsigned int); //标记block为可用