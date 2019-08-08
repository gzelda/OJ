#include <iostream>
using namespace std;
class Complex
{
private :
    double    m_real;
    double    m_imag;
    int id;
    static int counter;
public:
    //    无参数构造函数
    Complex(void)
    {
        m_real = 0.0;
        m_imag = 0.0;
        id=(++counter);
        cout<<"Complex(void):id="<<id<<endl;
    }
    //    一般构造函数（也称重载构造函数）
    Complex(double real, double imag)
    {
        m_real = real;
        m_imag = imag;
        id=(++counter);
        cout<<"Complex(double,double):id="<<id<<endl;
    }
    //    复制构造函数（也称为拷贝构造函数）
    Complex(const Complex & c)
    {
        // 将对象c中的数据成员值复制过来
        m_real = c.m_real;
        m_imag = c.m_imag;
        id=(++counter);
        cout<<"Complex(const Complex&):id="<<id<<" from id="<<c.id<<endl;
    }
    // 类型转换构造函数，根据一个指定的类型的对象创建一个本类的对象
    Complex(double r)
    {
        m_real = r;
        m_imag = 0.0;
        id=(++counter);
        cout<<"Complex(double):id="<<id<<endl;
    }
    ~Complex()
    {
        cout<<"~Complex():id="<<id<<endl;
    }
    // 等号运算符重载
    Complex &operator=( const Complex &rhs )
    {
        if ( this == &rhs ) {
            return *this;
        }
        this->m_real = rhs.m_real;
        this->m_imag = rhs.m_imag;
        cout<<"operator=(const Complex&):id="<<id<<" from id="<<rhs.id<<endl;
        return *this;
    }
};
int Complex::counter=0;
Complex test1(const Complex& c)
{
    return c;
}
Complex test2(const Complex c)
{
    return c;
}
Complex test3()
{
    static Complex c(1.0,5.0);
    return c;
}
Complex& test4()
{
    static Complex c(1.0,5.0);
    return c;
}
int main()
{
    Complex a,b;

    // 下面函数执行过程中各会调用几次构造函数，调用的是什么构造函数？
    Complex c=test1(a);
    Complex d=test2(a);

    b = test3();
    b = test4();

    Complex e=test2(1.2);
    Complex f=test1(1.2);
    Complex g=test1(Complex(1.2));

}