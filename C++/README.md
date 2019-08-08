# C++
复习一下C++中常见的一些基本概念和设计模式。写的会很乱，后续会进行整理分类，现阶段放在OJ里面是因为找工作整理在一起了。

## 类

### 构造函数

网上教过很多构造函数的各种事项，比如构造函数不能为const、复制构造函数导致的浅拷贝-深拷贝的问题。个人不喜欢从语言的应用层面直接理解这些问题，有点生硬地学前端的感觉，想从编译原理的角度思考一下这个语言是怎么写的。

构造函数，语法树识别到特定类型的时候执行的一个函数。之前编译原理大作业的时候写到过struct结构体的构造（很久远的事情了），struct里面的变量会在执行过程的时候进行初始化的内存分配，分配到随机的寄存器中。

    编译原理的过程是 词法=>语法=>语义=>中间代码生成=>目标代码生成

写struct的时候的做法是struct内部结构保存在一个特定的位置
    
    按照内存分配原理是分为栈、堆、全局/静态区、常量区、程序代码区。struct的定义是放在全局的未初始化区，变量在内存中排列的方式就是按照类型顺序一个一个排下去

类和struct有点类似，但是通常大家使用类的时候会有成员函数，struct也是有的但是不怎么常用，private和public缺省规则和class正好是反过来的。有函数的地方，函数的二进制流就要存到程序代码区，这个二进制流里面需要获取所有相关变量的地址。所以流程就比较清晰了，首先将所有的变量的值放在全局变量区，再将每个成员函数留个指针放在全局变量区，函数体的二进制流放到程序代码区，调用的时候直接跑二进制流。

    这里我个人的理解就和前端的动态绑定一个道理，东西框架放好了，输入不同，输出不同。这里的输入不仅仅是外界形参的输入，还有成员变量或者全局变量的地址对应的值的变化也是状态的输入（这个需要对照计算原理还是计算理论，金小刚）。

所以说到构造函数，在没有new的时候，就是程序代码区的一段流，没有执行。new对象的时候跑一遍，找哪个构造函数的函数指针规则早就写好，放进程序代码区了（c++本身干的活）。

    new对象的时候，首先在堆区分配class中的成员变量， 然后里面的成员函数还会再分配到程序代码区一次么? 这块还真不知道，猜测不需要分配了，不然一个对象一堆成员函数的内存应该吃不消，但是拿不准，放在Issue里面，以后做个实验，查一下函数地址。//TODO1

构造函数还有几种特别的形式，首先是复制构造函数。

    class A{
        private: int data;
        A ( const A &a ) {data = a.data;} //引用给个const
    }

    值拷贝，也就是深拷贝
    
还有一种是重载“=”，本质上来说这个不算是构造函数，因为构造函数是在变量完全初始化过程中的一部分，而重载“=”是在构造函数完成之后才能执行的。如果没有初始化的变量用等号请参考复制构造函数。

    A &operator=(const A &a){
        this->data = a.data;
        return *this;
    }

这里面坑有点多，因为默认的 “=” 不是这么写的，有一句比较重要

    A &operator=(const A &a){
        if (&a == this){return *this}
        //面试官因为这一句话可能刷人，嗯...不是很理解吧。

        this->data = a.data;
        return *this;
    }

    operator默认返回值是类本身的原因是想支持多元计算（连等，连加）。


当我看到

    class A{
        private: int data;
        A ( const A &a ) {
            data = a.data;
        } //引用给个const
    }

的时候，我突然感觉到有点不对，因为在别人的构造里面a可以调用自己的私有变量data。所以我基本可以确定new对象的时候成员函数没有重新拷贝到程序代码区，至少构造函数没有拷贝到程序代码区（构造函数可以查看地址么？//TODO2）。

先构造先析构，尤其是构造函数值传递的情况下。

[无敌构造俄罗斯套娃看你究竟会不会看懂就懂了的例子](https://www.cnblogs.com/xkfz007/archive/2012/05/11/2496447.html)







## 设计模式

### 单例

    template <class SingletonClass >
    class NormalSingleton{
        public:
            static SingletonClass * Instance(){
                static SingletonClass* instance = 0;
                if( !instance ){
                    instance = new SingletonClass;
                }
                return instance;
            }
            SingletonClass* operator ->() { return Instance(); }
            const SingletonClass* operator ->() const { return Instance(); }
        private:
            NormalSingleton(){ }
            ~NormalSingleton(){ }
    };


    typedef NormalSingleton< CBestPlayer >
    BestPlayer; // singleton pattern
    #define BEST_PLAYER BestPlayer::Instance()

    //void A() const {}   const指向的是this


SSL使用的方法没有顾及线程安全的问题（if判断），并且只new不delete

    class Singleton
    {
    public:
        ~Singleton(){
            std::cout<<"destructor called!"<<std::endl;
        }

        static Singleton& get_instance(){
            static Singleton instance;
            return instance;
        }
    private:
        Singleton(const Singleton&);
        Singleton& operator=(const Singleton&);
        Singleton(){
            std::cout<<"constructor called!"<<std::endl;
        }
    };

    int main(int argc, char *argv[])
    {
        Singleton& instance_1 = Singleton::get_instance();
        Singleton& instance_2 = Singleton::get_instance();
        return 0;
    }


改造成：

    template <class SingletonClass>
    class MeyersSingleton{
        public:
            static SingletonClass& get_instance(){
                static SingletonClass instance;
                return instance;
            }
    };


    typedef MeyersSingleton<A> A_agent;
    A_agent.get_instance();