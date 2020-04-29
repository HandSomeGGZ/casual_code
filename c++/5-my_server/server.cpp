#include <iostream>
#include <string>
#include <vector>
#include "netinet/in.h"
#include <unistd.h>
#include "string.h"
#include "sys/types.h"
#include "sys/socket.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

using namespace std;

// class User
// {
// private:
//     /* data */
//     string user_id;
//     vector <string> data_to_user;   //此为一个可变的string类型的容器,要发送给用户的数据
   
//     string des_id;
//     vector <string> data_to_des;    //拷贝此数据给des_id的data_to_user
    
// public:
//     bool flag_data_to_user; //true 表示有数据要发送给用户
//     bool flag_data_to_des;  //true 表示有数据从用户发送过来要发送给其目标用户
//     User(string new_user_id);
//     ~User();
//     int set_data_to_user(string message_data);      //在vector的后面添加一个string的成员

//     int print();
// };

// User::User(string new_user_id)
// {
//     this->user_id=new_user_id;
//     this->flag_data_to_des=false;
//     this->flag_data_to_user=false;
// }

// int User::set_data_to_user(string message_data)
// {
//     this->data_to_user.push_back(message_data);     //在数据末尾存入一个数据
//     return 0;
// }

// int User::print()
// {
//     cout << "user_id:"+this->user_id << endl;
//     if(!this->data_to_user.empty())
//     {
//         for(vector<string>::iterator it = this->data_to_user.begin(); it != this->data_to_user.end(); it++)
//         {
//             cout <<"message:"+ *it<<endl;
//         }
//         this->data_to_user.clear();     //清除已发送的数据
//     }
// }


// User::~User()
// {
// }


#define PORT 8089
#define MAX_QUE_CONN_NM 5
#define BUFFER_SIZE 1024

struct sockaddr_in server_sockaddr,client_sockaddr;

int sockfd,client_fd,linsten_fd;
int sin_ssize;

int init_server()   //绑定ip和端口等
{
    /*establish a socket connect*/
	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		// perror("socket");
        cout << "socket establish faild"<<endl;
		exit(1);
	
	}
   
    /*config the pamater about sockaddr_in*/
	server_sockaddr.sin_family = AF_INET;
	server_sockaddr.sin_port = htons(PORT);
	server_sockaddr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(server_sockaddr.sin_zero),8);
	
	// int i = 1;	//allow reuse local ip to bind with socket words
	
	if(bind(sockfd,(struct sockaddr*)&server_sockaddr,
					sizeof(struct sockaddr)) == -1)
	{
        cout << "bind  faild"<<endl;
		exit(1);
	}	
	cout << "bind  success"<<endl;
	
	if((linsten_fd=listen(sockfd,MAX_QUE_CONN_NM)) == -1)
	{
        cout << "listen  faild"<<endl;
		exit(1);
	}
    cout << "Listening...."<<endl;
    char buf_rev[1024];
    char buf_send[1024];
    int recvbytes;
    
    while(1)
    {
        /*客户端运行直接连接到服务器*/
        if((client_fd = accept(sockfd,
                (struct sockaddr*)&client_sockaddr,(socklen_t*)&sin_ssize)) == -1)
        {
            cout << "accept  faild"<<endl;
            // continue;
        }

        if(fork()==0)	//子进程 
        {	
            //创建线程
            if((recvbytes = recv( client_fd,buf_rev,BUFFER_SIZE,0)) == -1)      //阻塞接收，等待用户登录
            {
                cout << "login  faild"<<endl;
            }
            if(recvbytes>0)
            {                               //对数据进行解析提取
                buf_rev[recvbytes]='\0';
                cout << buf_rev<<endl;      //可分别对账号密码提取，实现密码登录
                
                string operation=&buf_rev[4];
                
                buf_rev[4]='\0';
                string user_id = buf_rev;
            }
            
            switch (opration)
            {
                case "login":/*验证密码*/break;
                case "register":/*账号密码写入注册文件*/break;
                default:break;
            }
            //验证密码和账户 在此对login 和register进行处理

            send(client_fd,"login success",14,0);        //告知客户端登录成功
            //User u_t(user_id);
            string fifo_path="/tmp/"+user_id;
            //用户上线就创建自己的接收管道，当写入管道不存在说明此用户不存在
            if(mkfifo(fifo_path.c_str(),O_CREAT|O_EXCL)<0)
                cout<<"can't creat fifo"<<endl;
            else
            {
                cout<<"user login success"<<endl;
            }
            int fifo_fd=open(fifo_path.c_str(),O_RDWR|O_NONBLOCK);      //打开自己的管道
            if(fifo_fd<0)
                cout <<"open fifo faild"<<endl;

            while(1)
            {
                
                recvbytes = recv( client_fd,buf_rev,BUFFER_SIZE,MSG_DONTWAIT);   //非阻塞接收，消息轮询
                
                /*设定数据格式，user_ID+des_ID+数据*/
                if(recvbytes>0)
                {
                    //写入des_ID的管道
                    buf_rev[recvbytes]='\0';
                    string message=&buf_rev[9];
                    message=user_id+message;        //告诉目标用户是谁发的消息
                    buf_rev[9]='\0';
                    string des_id=&buf_rev[5];
                    cout << "des_user:"+des_id<<endl <<"message:"+message<<endl;
                    //打开对应用户的管道，将数据写入
                    string des_fifo_path="/tmp/"+des_id;   //合成目的用户管道路径
                    int des_fifo_fd=open(des_fifo_path.c_str(),O_RDWR|O_NONBLOCK);      //打开目的用户的管道
                    if(des_fifo_fd<0)
                    {
                        cout <<"open des fifo faild"<<endl;
                        send(client_fd,"user have not login data can not send",38,0);
                    }
                    else
                    {
                        write(des_fifo_fd,message.c_str(),message.length());//将消息写入管道
                    }
                    close(des_fifo_fd);

                }
                
                /*读取自己ID对应管道的数据*/
                int n_read=read(fifo_fd,buf_send,1024);
                if(n_read>0)
                {
                    buf_send[n_read]='\0';
                    send(client_fd,buf_send,n_read+1,0);
                }
                /*发送数据*/
                
               // int sendbytes = send(client_fd,"hello world",12,0);
            }
            close(linsten_fd);
            close(client_fd);
            close(fifo_fd);
        }
        else
        {
            close(client_fd);
        }
    }

}

int main(void)
{
    init_server();
    system("pause");
}
