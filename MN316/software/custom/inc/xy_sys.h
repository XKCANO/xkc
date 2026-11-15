#ifndef __XY_SYSTEM_API_H
#define __XY_SYSTEM_API_H
/*
**This function get reason for power on. @returnThe reason of the Power on, see SYS_START_STAT. 
*/
uint32_t get_sys_up_stat(void); 
/*
**指示芯片是否从深睡唤醒的，且TAU尚未超时，PS无需执行attach，PDP激活的IP保持不变 
**返回bool，XY_OK表明PDP激活的IP地址未变 
**注解该接口慎用！建议使用get_sys_up_stat接口 
*/
int is_powenon_from_deepsleep(void);
/**
**强制芯片进入深睡，不关心当前持有锁的情况，也不关心当前3GPP是否能够调度出4秒以上的空闲时间。平台内部仅保存NV，进而要求下次上电后3GPP必须执行attach流程。 
**参数abnormal_off 缺省值为0  
**警告该接口不与基站进行握手通信，类似直接断电，可达到1秒内进深睡。仅能在两个场景下使用： 
**1) 当用户启用的软件看门狗超时后，可以认为当前3GPP状态异常，调用该接口进行强制深睡.
**2) 部分客户为了健壮性考虑，要求不使用PSM模式，每次工作完毕后，调用该接口快速秒级深睡，下次再上电执行attach流程. 
*/
void xy_fast_power_off(int abnormal_off);
/**
**软重启接口，内部进行相关NV的保存后，触发芯片软重启. 
**注意软重启后RTC定时器及当前世界时间保持不变，若重启前已经获取了当前世界时间，则重启后仍然有效 
*/
void xy_reboot(void);

void xy_standby_clear(void);
void xy_standby_lock(void);
void xy_standby_unlock(void);
void xy_work_lock(int lock_type);  
void xy_work_unlock(int lock_type);

#endif

