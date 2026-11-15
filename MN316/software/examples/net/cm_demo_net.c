/**
 *  @file    cm_demo_net.c
 *  @brief   OpenCPU网络相关使用示例
 *  @copyright copyright © 2021 China Mobile IOT. All rights reserved.
 *  @author by ZXW
 *  @date 2021/06/17
 */


#include "stdlib.h"
#include "stdio.h"
#include "cm_os.h"
#include "lwip/netdb.h"
#include "lwip/sockets.h"

#include "cm_demo_common.h"


/**
 *  \brief UDP测试
 *  
 *  \return 成功返回0，失败返回-1
 *  
 *  \details lwip,udp单次允许发送最大字节数为1500。
 */
int cm_test_udp(unsigned char **cmd, int len)
{

    int ret = 0;
    char ip[] = "120.27.12.119";
    short port = 2015;
    int socketid = 0;
    char test_msg[] = "udp network test\n";
    char test_rx_buf[100] = {0};
    fd_set readfds = {0};
    struct timeval tv = {.tv_sec = 5};

    socketid = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(socketid == -1)
    {
        cm_log_printf(0, "udp socket create error\n");
        return -1;
    }

    cm_demo_printf("udp socketid %d\n", socketid);

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_len = sizeof(server_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);
	
    //udp单次允许发送最大字节数为1500。
    ret = sendto(socketid, (char *)test_msg, strlen(test_msg), 0, (const struct sockaddr *)&server_addr, sizeof(server_addr));
    cm_demo_printf("udp send ret %d\n", ret);

    if(ret < 0)
    {
        cm_log_printf(0, "udp send error\n");
		return -1;
    }

    FD_SET(socketid, &readfds);
    ret = select(socketid + 1, &readfds, NULL, NULL, &tv);

    if(ret > 0)
    {
        if(FD_ISSET(socketid, &readfds))
        {
            ret = recv(socketid, test_rx_buf, sizeof(test_rx_buf), 0);
            cm_demo_printf("udp recv data,len:%d\n", ret);
        }
    }

    close(socketid);
    return 0;
}


/**
 *  \brief TCP测试
 *  
 *  \return 成功返回0，失败返回-1
 *  
 *  \details lwip
 */
int cm_test_tcp(unsigned char **cmd, int len)
{

    int ret = 0;
    char ip[] = "120.27.12.119";
    short port = 2015;
    int socketid = 0;
    char test_msg[] = "tcp network test\n";
    char test_rx_buf[100] = {0};    
    fd_set readfds = {0};
    struct timeval tv = {.tv_sec = 5};

    socketid = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(socketid == -1)
    {
        cm_log_printf(0, "tcp socket create error\n");
        return -1;
    }
    cm_demo_printf("tcp socketid %d\n", socketid);

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_len = sizeof(server_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    ret = connect(socketid, (const struct sockaddr *)&server_addr, sizeof(server_addr));

    if(ret == -1)
    {
        cm_log_printf(0, "tcp connect error\n");
        close(socketid);
        return -1;
    }

    ret = send(socketid, (char *)test_msg, strlen(test_msg), 0);
    cm_demo_printf("tcp send ret %d\n", ret);

    if(ret < 0)
    {
        cm_log_printf(0, "tcp send error\n");
    }

    FD_SET(socketid, &readfds);
    ret = select(socketid + 1, &readfds, NULL, NULL, &tv);

    if(ret > 0)
    {
        if(FD_ISSET(socketid, &readfds))
        {
            ret = recv(socketid, test_rx_buf, sizeof(test_rx_buf), 0);
            cm_demo_printf("tcp recv data,len:%d\n", ret);
        }
    }

    close(socketid);
    return 0;
}


/**
 *  \brief DNS测试
 *  
 *  \return 成功返回0，失败返回-1
 *  
 *  \details lwip
 */
int cm_test_dns(unsigned char **cmd, int len)
{

    char test_domain[] = "www.baidu.com";
    char host_ip[20] = {0};

    struct hostent *host = gethostbyname(test_domain);

    if(host == NULL)
    {
        cm_log_printf(0, "DNS error\n");
        return -1;
    }

    inet_ntop(host->h_addrtype, host->h_addr_list[0], host_ip, sizeof(host_ip));

    cm_demo_printf("host ip:%s\n", host_ip);
    return 0;
}

