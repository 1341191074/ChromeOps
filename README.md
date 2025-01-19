
### 预处理器配置
WIN32
_WINDOWS
_USRDLL
_CONSOLE
CURL_STATICLIB
WIN32_LEAN_AND_MEAN

### 配置nlohmann-json
nlohmann-json 克隆到本地，配置附加目录即可
```shell
git clone https://github.com/nlohmann/json.git
```
配置附加目录：E:\gitee\nlohmann-json\include


### 编译并配置opensll
windows平台下载 https://slproweb.com/products/Win32OpenSSL.html
选择 Win64 OpenSSL v3.4.0 ， 不选择Light版本，Light版本不带lib和include
MTd: 多线程 静态库 Debug版本
MT: 多线程 静态库 Release版本

附加目录： D:\apps\OpenSSL-Win64\include 
链接器 D:\apps\OpenSSL-Win64\lib\VC\x64\MT


### 编译并配置libcurl
https://www.cnblogs.com/ligang0357/p/17188394.html


vs2022 配置使用libcurl
1、官网下载libcurl 

https://curl.se/download/curl-7.88.1.tar.gz

2、解压执行curl目录下的buildconf.bat，然后cd winbuild

3、编译

vs的工具下的命令行:(一定、一定、一定)
D:\apps\Microsoft\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build
32位:vcvarsall.bat x86
64位:vcvarsall.bat x64

下一步：执行curl目录下的buildconf.bat，然后cd winbuild
windows下编译(MT):
32-debug: nmake /f Makefile.vc mode=static vc=17 debug=yes rtlibcfg=static machine=x86 ENABLE_IDN=no
32-release: nmake /f Makefile.vc mode=static vc=17 debug=no rtlibcfg=static machine=x86 ENABLE_IDN=no
64-debug: nmake /f Makefile.vc mode=static vc=17 debug=yes rtlibcfg=static machine=X64 ENABLE_IDN=no
64-release: nmake /f Makefile.vc mode=static vc=17 debug=no rtlibcfg=static machine=X64 ENABLE_IDN=no

windows下编译(MD):
32-debug: nmake /f Makefile.vc mode=static vc=17 debug=yes machine=x32 ENABLE_IDN=no
32-release: nmake /f Makefile.vc mode=static vc=17 debug=no machine=x32 ENABLE_IDN=no
64-debug: nmake /f Makefile.vc mode=static vc=17 debug=yes machine=X64 ENABLE_IDN=no
64-release: nmake /f Makefile.vc mode=static vc=17 debug=no machine=X64  ENABLE_IDN=no

重点是一定要加ENABLE_IDN=no，默认是打开的，不加的话编译会出错
X64不行就换AMD64
4、vs 设置包含库和目录
5、因为libcurl是静态编译的所以要加预处理器定义 CURL_STATICLIB
 注意：
如果你想查看你的DLL的导出情况可以这样做，在你的VC安装目录下的VC98\BIN目录下有一个dumpbin.exe文件，它就是用来查看DLL文件信息的，你可以在命令行下（CMD）用dumpbin -exports dllname 命令来查看DLL的导出函数列表
当使用动态库DLL时，在MSVC中的Code Generation选项选择MD/MDD（依Release或Debug而定），此时系统函数会调用MSVCRT.lib与MSVCR71.DLL
当使用静态库LIB时，在MSVC中的Code Genration选项选择MT/MTD（依Release或Debug而定），此时系统函数会调用LIBCMT.lib
警告：
   不要混合使用库的静态版本和动态版本。在一个进程中有多个库副本会导致问题，因为副本中的静态数据不与其他副本共享。链接器禁止在 .exe 文件内部既使用静态版本又使用动态版本链接，但您仍可以使用运行时库的两个（或更多）副本。例如，当与用动态 (DLL) 版本的运行时库链接的 .exe 文件一起使用时，用静态（非 DLL）版本的运行时库链接的动态链接库可能导致问题。（还应该避免在一个进程中混合使用这些库的调试版本和非调试版本）。
这句话的意思是exe工程尽量保持要么都引用动态库，要么都静态库，不要又引用动态又引用静态，会容易引起冲突
还有就是别动态库中引用了一个静态库，然后该动态库又被exe引用了，这些都容易造成冲突


### 编译并配置boost。 
下载编译好的版本 https://sourceforge.net/projects/boost/files/boost-binaries/
附加目录：D:\apps\boost_1_86_0
链接器 : D:\apps\boost_1_86_0\lib32-msvc-14.3

### 配置websocketpp。已弃用websocketpp
下载直接配置附加目录即可
```
git clone https://github.com/zaphoyd/websocketpp
```
附加目录配置：D:\apps\websocketpp-0.8.2
