void init_IndexArea();
void LoadIndexArea();
void SaveIndexArea();
int IndexAreaGetUsed(unsigned int);
void IndexAreaSetUsed(unsigned int); //标记block已经使用
void IndexAreaSetUnused(unsigned int); //标记block为可用