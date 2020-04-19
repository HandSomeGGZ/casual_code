#include <iostream>
#include <string>

using namespace std;

void test()
{
    string s1;
    string s2 ("abc");
    string s3 (4,'d');
    cout << s2 << endl;
    cout << s3 << endl;
    getline(cin ,s1);
    cout <<"you input is: "<<s1<<endl;
    cout << s1+s2 << endl;

    string::iterator iterA; //正向迭代器
    for (iterA=s1.begin();iterA != s1.end();iterA++)
    {
        cout << *iterA << endl;
    }

    string::reverse_iterator iterB; //反向迭代器
    for (iterB=s1.rbegin();iterB != s1.rend();iterB++)
    {
        cout << *iterB << endl;
    }
}

void test2(void)
{
    string s1("555");
    cout << "maxsize = " << s1.max_size() <<endl;
    cout << "size = " << s1.size() <<endl;
    cout << "capacity = " << s1.capacity() <<endl;
    cout << "length = " << s1.length() <<endl;
}
    


int main(void)
{
    test();
    test2();
    system("pause");
}