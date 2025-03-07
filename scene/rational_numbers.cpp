#include "../include/help.h"
//numerator分子  denominator分母

class Rational {
public:
    Rational(int n=0,int d=1):num(n),den(d) {} //有参构造函数

    friend Rational operator+(const Rational &r1,const Rational &r2);//相加
    friend Rational operator-(const Rational &r1,const Rational &r2);//相减
    friend Rational operator/(const Rational &r1,const Rational &r2);//相除
    friend Rational operator*(const Rational &r1,const Rational &r2);//相乘


    void simplify();//对有理数进行化简
    void display();  //显示结果
private :
    double num;
    double den;

};
Rational operator+(const Rational &r1,const Rational &r2) {
    Rational r;
    r.num = r1.den*r2.num+r1.num*r2.den;//相加的分子等于r1分母和r2分子相乘，r1分子和r2分母相乘之和
    r.den = r1.den*r2.den;//分母等于两个有理数分母的相乘
    r.simplify();//调用simplify对结果进行化简
    return r;//将结果返回
}
Rational operator-(const Rational &r1,const Rational &r2) {
    Rational r;
    r.num = r1.num*r2.den-r1.den*r2.num;//相加的分子等于r1分母和r2分子相乘，r1分子和r2分母相乘之差
    r.den = r1.den*r2.den;//分母等于两个有理数分母的相乘
    r.simplify();
    return r;
}
Rational operator/(const Rational &r1,const Rational &r2) {
    Rational r;
    if(r1.den==0||r2.den==0||r2.num==0) {
        cout<<"分母或者除数不能为0"<<endl;
    } else if(r1.num==0) {
        cout<<"0/0"<<endl;
    } else {
        r.num = r1.num*r2.den;//相除的分子等于r1分子和r2分母相乘
        r.den = r1.den*r2.num;//分母等于两个r1分母和r2分子相乘
        r.simplify();
        return r;
    }
}
Rational operator*(const Rational &r1,const Rational &r2) {
    Rational r;
    if(r1.den==0||r2.den==0) {
        cout<<"分母不能为0"<<endl;
    } else if(r1.num==0||r2.num==0) {
        cout<<"0/0"<<endl;
    } else {
        r.num = r1.num*r2.den;//分子等于r1分子和r2分母相乘
        r.den = r1.den*r2.num;//分母等于两个r1分母和r2分子相乘
        r.simplify();
        return r;
    }
}
void Rational::simplify() {
    int i,j,temp;
    i=abs(den);
    j=abs(num);
    //如果i对j取余不为0，辗转相除法求最大公约数
    while(temp=i%j) {
        i=j;
        j=temp;
    }
    den/=j;
    num/=j;
    if(den<0) {
        den=-den;
        num=-num;
    }
}
void Rational::display() {
    if(num==0||den==0) {

    } else {
        cout<<num<<"/"<<den<<endl;
    }
}
int main() {
    Rational r;
    Rational r1(1,3),r2(0,5);
    r=r1+r2;
    r.display();
    r=r1-r2;
    r.display();
    r=r1*r2;
    r.display();
    r=r1/r2;
    r.display();
    return 0;
}
