# 空间适配器 (allocator)

空间适配器用于给容器分配存储空间，空间并不是特指内存，实际上也可以是磁盘空间。再SGI-STL中，分配的对象是内存空间。
allocator主要做以下事情：
- 内存配置/释放：allocate()/deallocate()
- 对象构造/析构：construct()/destroy()

## 双层配置器
第一级配置器使用malloc()和free(),第二即配置器则视情况而定:当配置区块超过128bytes，使用第一级配置器；当配置区块小于128bytes，使用复杂的memory pool整理方式，通过空闲链表来管理内存。
