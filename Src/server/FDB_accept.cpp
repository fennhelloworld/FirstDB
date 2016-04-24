/*************************************************************************
	> File Name: FDB_accept.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年04月18日 星期一 12时22分56秒
 ************************************************************************/

#include<iostream>
#include"./FDB_accept.h"
#include"./FDB_buffer.h"


Accept::Accept(int sockfd){
    
    sock_fd = sockfd;
    
    connfd_flag = 0;

    connfd = accept(sockfd,(struct sockaddr *)&client_addr,&client_addr_length);
    
    if(connfd == -1){

        std::cout << "accept error " << std::endl;

        
    }


}

int Accept::Accept_return_flag(){

    return  connfd_flag;    

}

int Accept::Accept_return(){
    
    return connfd;

}


int Accept::Accept_Write(std::string str){        /*先写进connfd  将剩余的数据写入buffer ,注册connfd 可写*/
    
    
    int length = str.length();
    const char * buf = str.c_str() ;

    int use = write(connfd,buf,length);
    
    int use_less = length - use ;

    if(use_less > 0 ){
        
        connfd_buf.connfd_write(str,use_less,length);
        //Epoll_set_EPOLLOUT(connfd);
        connfd_flag = 1;
        return use_less;

    }else if(use_less < 0){
        
        //Close(connfd);
        return -1;

    }else if(use_less == 0){

        std::cout << "success " << std::endl; 
        return 0;
    }else{
        
        std::cout << "something else" << std::endl;
        return -1;
    }
    
    
    
}



int Accept::Accept_Read(char * str){
    char buf[1024];
    //memcopy(buf,str,1024);
    int slave = read(connfd,buf,1024);
    if(slave > 0){  
        //connfd_buf.connfd_read(str);
    }


}


