#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void my_print(int val)
{
    cout<< val<<endl;
}

void test(void)
{
    vector<int> v; //声明一个vector容器
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    /*遍历容器*/
    /*1*/
    // vector<int>::iterator itBegin = v.begin();  //起始迭代器
    // vector<int>::iterator itEnd = v.end();      //结束迭代器
    // while(itBegin != itEnd)
    // {
    //     cout<<*itBegin<<endl;
    //     itBegin++;
    // }
    /*2*/
    // for(vector<int>::iterator it = v.begin(); it != v.end(); it++)
    // {
    //     cout <<*it<< endl;
    // }
    /*3*/
    //使用系统提供的算法
     for_each(v.begin(),v.end(),my_print);       //my_print 作为回调函数
}

int main(void)
{
    test();
    //system("pause");
}