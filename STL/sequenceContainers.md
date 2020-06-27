# 序列式容器

>序列容器中的元素是**可序**的，但未必是**有序**。

stl中的序列容器包含vector,list,deque,stack,queue,priority-queue队列。

## vector
- vector是一块连续的线性空间，随着元素的添加，能够动态的扩充空间。
- 由于是线性空间，vector的迭代器是随机访问迭代器。
- vector的数据结构是一块连续的线性空间，用2个迭代器start,finish指向空间中当前被使用的范围，迭代器end_of_storage指向连续空间的尾端。
- 当空间不够，vector需要动态增加大小：以原大小的**两倍**申请一块新的内存，然后将原内容拷贝到新的内存中，最后释放掉原内容。
![vector](vector.png) 

## list
- list是双向链表，不是连续空间存储，每次插入/删除一个元素，就得配置或释放以元素空间，因此list对空间的运用是精准的。
- listNode的数据结构如下，可以看到有prev指针，next指针，和数据data组成。
- ```c++
  struct _List_node_base {
    _List_node_base* _M_next;
    _List_node_base* _M_prev;
  };
  template <class _Tp>
  struct _List_node : public _List_node_base {
    _Tp _M_data;
  };
  ```
- SGI-list是一个环状链表，只需要一个list_node指针就可以表示整个list.其中头节点和尾节点之间用一个空节点来区分。
![list](list.png)
- list的迭代器是双向迭代器，具备前移和后移的能力。这是因为list的存储不是连续空间，无法做到随机存取。
- list的插入/结合操作不会造成原有的list迭代器失效，而删除操作也只有“被铲除的元素”的迭代器会失效。
## deque
- deque是双向开口的连续线性空间，也就是可以在头尾两端插入/删除
- deque允许常数时间对头端进行元素的插入或移除。
- deque没有容量的概念，deque是动态的分段连续空间组合而成的，随时可以增加一段新的空间并链接。
- deque采用一块空间(map)来作为主控，map中每个元素都是指针，指向一段连续线性空间(缓冲区)，缓冲区是deque的存储主体。如果当前的map提供的节点不足，那么需要重新配置一块更大的map。
![deque的主控](deque.png)
- deque的迭代器是随机访问迭代器，但是其实现是非常复杂的。迭代器和缓冲区、中控器的关系如下：
![deque迭代器](deque_iter.png)
- deque除了维护一个map，还维护了start、finish两个迭代器，分别指向第一个缓冲区的第一个元素和最后一个缓冲区的最后一个元素。

## stack





