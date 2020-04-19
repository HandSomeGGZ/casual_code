#include <iostream>
#include <string>
#include <vector>
using namespace std;

// class snake_node
// {
// private:
//     /* data */
   
// public:
//     int x;
//     int y;
//     snake_node(/* args */);
//     ~snake_node();
//     void set_position(int x,int y);
// };

// snake_node::snake_node(/* args */)
// {
// }

// snake_node::~snake_node()
// {
// }
// void snake_node::set_position(int x_p,int y_p)
// {
//     x=x_p;
//     y=y_p;
// }
struct snake_node
{
    int x;
    int y;/* data */
};


class snake
{
private:
    /* data */
    vector<snake_node> my_snake;
    vector<char>interface[125];
public:
    snake(int x,int y);
    void snake_runing(int direction);
    void snake_add_node(snake_node p);
    ~snake();
};

snake::snake(int x,int y)
{
    my_snake[0].x=x;
    my_snake[0].y=y;
}

snake::~snake()
{
}

void snake::snake_add_node(snake_node p)
{
    //在尾部添加，判断尾部哪个方向能添加
    my_snake.push_back(p);          //待改
}

void snake::snake_runing(int direction)
{
    my_snake.pop_back();        //先把尾元素删掉
    snake_node new_head;
    
    switch(direction)   //生成新的头
    {
        case 'w':new_head.x=my_snake[0].x;new_head.y=my_snake[0].y++;break;
        case 's':new_head.x=my_snake[0].x;new_head.y=my_snake[0].y--;break;
        case 'a':new_head.x=my_snake[0].x--;new_head.y=my_snake[0].y;break;
        case 'd':new_head.x=my_snake[0].x++;new_head.y=my_snake[0].y;break;
        default:break;
    }
    my_snake.insert(my_snake.begin(),new_head);    //添加先的头
}

bool isValid(string s)      //括号匹配
{
    int i=0;
    if(s.empty())
        return true;
    else
    {
        i=0;
        while(i<s.length()&&(s[i]=='('||s[i]=='{'||s[i]=='['))
        {
            i++;
        }   
        if(i==0)
            return false;  
        i=i-1;
        // cout <<s[i]<<endl;
        // cout <<s[i+1]<<endl;
        if(s[i]=='(')
        {
            if(s[i+1]!=')')
                return false; 
        }
        switch(s[i])
        {
            case '(':if(s[i+1]!=')') return false;break;
            case '[':if(s[i+1]!=']') return false;break;
            case '{':if(s[i+1]!='}') return false;break;
        }
        s.erase(i,2);
        // cout <<s<<endl;
        if(isValid(s))
            return true;
        else
        {
            return false;
        }    
    }
           
}

void test(char * a)
{
    if(!(*a))
        cout << "is empty string"<<endl;
    else
    {
        cout << "not a empty string"<<endl;
    }
        
}    


int main(void)
{
    string s="(()(";
    if(isValid(s))
        cout<<"right"<<endl;
    else
    {
        cout<<"false"<<endl;
    }
    test("");
    test("a");
    system("pause");
}
