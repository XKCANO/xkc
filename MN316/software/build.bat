::工程编译批处理文件

@set tool_make=tools\toolchain\make.exe
::@set tool_make=make
@set tool_cp=tools\toolchain\cp.exe
@set tool_tee=tools\toolchain\tee.exe
@set script_dir=tools\scripts
@set log_dir=out\logs

@set param1=%1
@if "%param1%"=="" (set param1=dbrs_h0)
@if NOT "%param1%"=="dbrs_h0" ^
if not "%param1%" == "dlvs_h0" ^
if not "%param1%" == "sdlvs_h0" ^
if not "%param1%" == "dbrd_h1" ^
if not "%param1%" == "dlvd_h0" ^
goto error1
@%tool_cp% %script_dir%\feature_%param1%.mk %script_dir%\feature.mk
@if not exist %log_dir% md %log_dir%
@if /i "%2" == "demo" (
    @%tool_make% -f %script_dir%\Makefile all -e DEMO_SUPPORT=y 2>&1 | %tool_tee% %log_dir%\log.txt
)else (
    @%tool_make% -f %script_dir%\Makefile all -e DEMO_SUPPORT=n 2>&1 | %tool_tee% %log_dir%\log.txt
)
@goto exit1



:error1
@if "%param1%" == "clean" (
@%tool_make% -f %script_dir%\Makefile clean -e DEMO_SUPPORT=n 2>&1 | %tool_tee% %log_dir%\log.txt
@goto exit1
)
@echo usage:build.bat param1 [demo]
@echo   param1:
@echo  	  dbrs_h0:compile MN316 dbrs h0 version
@echo  	  dlvs_h0:compile MN316 dlvs h0 version
@echo  	  sdlvs_h0:compile MN316 sdlvs h0 version
@echo  	  dbrd_h1:compile MN316 dbrd h1 version
@echo  	  dlvd_h0:compile MN316 dlvd h0 version
@echo  	  clean:clean the project
:exit1
@goto :eof
