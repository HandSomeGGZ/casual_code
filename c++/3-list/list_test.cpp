#include <iostream>
#include <string>
#include <list>
#include <vector>
using namespace std;

class list_test
{
private:
    /* data */
public:
    string name;
    int age;
    list_test(string a,int b);
    ~list_test();
};

list_test::list_test(string a,int b)
{
    name=a;
    age=b;
}

list_test::~list_test()
{
}


void test()
{
    // list<string> words {20};    //a list of 20 empty strings
    string a("jim");
    list_test b(a,3);
    list<list_test> words {5,b};
    list<list_test>::iterator iter_a;
    for(iter_a=words.begin();iter_a != words.end();iter_a++)
    {
        cout<<(*iter_a).name<<"\t";

        cout<<(*iter_a).age<<endl;
    }

}
void test1()
{
    // list<string> words {20};    //a list of 20 empty strings
    string a("jim");
    list_test b(a,3);
    vector<list_test> words {5,b};
    vector<list_test>::iterator iter_a;
    for(iter_a=words.begin();iter_a != words.end();iter_a++)
    {
        cout<<(*iter_a).name<<"\t";

        cout<<(*iter_a).age<<endl;
    }

}

    


int main(void)
{
    test();
    test1();
    system("pause");
}