## 编译环境
* Host：Windows7及以上
* Gcc：arm-none-eabi-gcc8.3.1

## 编译方法
在SDK根目录打开cmd命令行，运行build.bat xxxxxx或build.bat xxxxxx DEMO批处理命令  
*xxxxxx表示子型号，当前支持DBRDH1/DLVDH0/DLVSH0/DBRSH0/S-DLVSH0* 
*特别注意：当前SDK不支持XGCDH2、DBRDH0两个子型号,版本烧写后不能再烧写其他AT版本或R13 OC版本*
*DEMO为可选参数，添加此参数将会编译DEMO示例* 

## 清除编译
命令行运行build.bat clean命令

## SDK结构说明
* custom 存放用户源文件
	> inc  
	> src  
	> custom.mk
* docs 文档
	> MN316 OpenCPU MANUAL
* examples 示例
	> uart  
	> spi  
	> ...  
	> examples.mk
* include 系统头文件
	> kernel  
	> lwip  
	> cmiot
* prebuild 预构建文件
	> images  
	> lib
* third-party 三方库文件
	> ...
* tools 编译工具及脚本
	> toolchain  
	> scripts  
* out 编译输出文件
	> images  
	> objs  
	> logs
* build.bat 编译批处理文件