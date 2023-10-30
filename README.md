# YJS

> 该项目用于测试基于YATA算法的底层结构（B+树，AVL树，以及双链表）之间的性能差异

#### 项目结构

```
├─src
│  ├─include
│  │      namespace.h
│  │
│  ├─item
│  │      id.h
│  │      Item.h
│  │
│  ├─lib
│  ├─server
│  │      doc.cpp
│  │      doc.h
│  │      transaction.h
│  │      util.cpp
│  │
│  └─struct
│          YAlloc.hpp
│          YList.cpp
│          YList.h
│          YStruct.h
│
└─test
        output_for_cin.txt
        YJS.cpp
        YJS.h
```

#### 需要进行的工作

##### 容器部分

开发者设计的底层容器需要继承YStruct.h内的YInterface类并实现通用接口。

##### 元素部分

开发者设计的容器操作的元素需要继承Item.h内ItemInterface类并添加自己结构额外需要的部分，也可以直接使用此类其余部分另行设计。

总之要按照接口规范可以接受并返回ItemInterface指针以供上层实现算法。