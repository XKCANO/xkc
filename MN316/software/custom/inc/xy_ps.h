#ifndef __XY_PS_API_H
#define __XY_PS_API_H
/*
** 用来通知PS发送空的UDP报文，并携带RAI指示给基站，以快速释放链接
** 返回XY_OK is success,XY_ERR is fail
** 注解
** 当用户认为后续没有报文交互需求时，调用该接口来伴随触发RAI，以降低功耗。
** 必须设置出厂NV参数close_rai为1，否则在用户释放最后一把锁后会由芯翼平台自触发RAI 
** 警告
** 该接口慎用！！！建议用户使用如cis_ext_send_with_rai、cdp_send_syn_with_rai等接口
** PS会释放当前待发送的所有上行数据，进行需要用户确保调用该接口时已经没有待发送的上行数据。
*/
int xy_send_rai(void);

#endif

