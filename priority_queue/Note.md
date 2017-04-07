# Priority_queue 开发笔记

## 开发时遇到的问题

> * 无构造函数成员：
>
>		采用记录指针，在赋值时使用拷贝构造函数new
>
> * 自我赋值：
>
> 		判断一下如果是自己赋给自己直接 return *this;
> * 语法问题：
>
> 	在class priority_queue 中定义 struct Node
> 	
> 	1 其成员函数的实现不能放在 class priority_queue中
> 	
>	2 自定义空指针null[1]如果使用template不能用static
> 		
> 		每一个priority_queue对象建立一个null指针，每一个Node开一个nflag记录一下自己的null指针。
> 		每次访问时检查flag==null?，如果不相等说明是后merge过来的，进行修正即可
