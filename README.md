
### Ԥ����������
WIN32
_WINDOWS
_USRDLL
_CONSOLE
CURL_STATICLIB
WIN32_LEAN_AND_MEAN

### ����nlohmann-json
nlohmann-json ��¡�����أ����ø���Ŀ¼����
```shell
git clone https://github.com/nlohmann/json.git
```
���ø���Ŀ¼��E:\gitee\nlohmann-json\include


### ���벢����opensll
windowsƽ̨���� https://slproweb.com/products/Win32OpenSSL.html
ѡ�� Win64 OpenSSL v3.4.0 �� ��ѡ��Light�汾��Light�汾����lib��include
MTd: ���߳� ��̬�� Debug�汾
MT: ���߳� ��̬�� Release�汾

����Ŀ¼�� D:\apps\OpenSSL-Win64\include 
������ D:\apps\OpenSSL-Win64\lib\VC\x64\MT


### ���벢����libcurl
https://www.cnblogs.com/ligang0357/p/17188394.html


vs2022 ����ʹ��libcurl
1����������libcurl 

https://curl.se/download/curl-7.88.1.tar.gz

2����ѹִ��curlĿ¼�µ�buildconf.bat��Ȼ��cd winbuild

3������

vs�Ĺ����µ�������:(һ����һ����һ��)
D:\apps\Microsoft\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build
32λ:vcvarsall.bat x86
64λ:vcvarsall.bat x64

��һ����ִ��curlĿ¼�µ�buildconf.bat��Ȼ��cd winbuild
windows�±���(MT):
32-debug: nmake /f Makefile.vc mode=static vc=17 debug=yes rtlibcfg=static machine=x86 ENABLE_IDN=no
32-release: nmake /f Makefile.vc mode=static vc=17 debug=no rtlibcfg=static machine=x86 ENABLE_IDN=no
64-debug: nmake /f Makefile.vc mode=static vc=17 debug=yes rtlibcfg=static machine=X64 ENABLE_IDN=no
64-release: nmake /f Makefile.vc mode=static vc=17 debug=no rtlibcfg=static machine=X64 ENABLE_IDN=no

windows�±���(MD):
32-debug: nmake /f Makefile.vc mode=static vc=17 debug=yes machine=x32 ENABLE_IDN=no
32-release: nmake /f Makefile.vc mode=static vc=17 debug=no machine=x32 ENABLE_IDN=no
64-debug: nmake /f Makefile.vc mode=static vc=17 debug=yes machine=X64 ENABLE_IDN=no
64-release: nmake /f Makefile.vc mode=static vc=17 debug=no machine=X64  ENABLE_IDN=no

�ص���һ��Ҫ��ENABLE_IDN=no��Ĭ���Ǵ򿪵ģ����ӵĻ���������
X64���оͻ�AMD64
4��vs ���ð������Ŀ¼
5����Ϊlibcurl�Ǿ�̬���������Ҫ��Ԥ���������� CURL_STATICLIB
 ע�⣺
�������鿴���DLL�ĵ�����������������������VC��װĿ¼�µ�VC98\BINĿ¼����һ��dumpbin.exe�ļ��������������鿴DLL�ļ���Ϣ�ģ���������������£�CMD����dumpbin -exports dllname �������鿴DLL�ĵ��������б�
��ʹ�ö�̬��DLLʱ����MSVC�е�Code Generationѡ��ѡ��MD/MDD����Release��Debug����������ʱϵͳ���������MSVCRT.lib��MSVCR71.DLL
��ʹ�þ�̬��LIBʱ����MSVC�е�Code Genrationѡ��ѡ��MT/MTD����Release��Debug����������ʱϵͳ���������LIBCMT.lib
���棺
   ��Ҫ���ʹ�ÿ�ľ�̬�汾�Ͷ�̬�汾����һ���������ж���⸱���ᵼ�����⣬��Ϊ�����еľ�̬���ݲ�����������������������ֹ�� .exe �ļ��ڲ���ʹ�þ�̬�汾��ʹ�ö�̬�汾���ӣ������Կ���ʹ������ʱ�������������ࣩ���������磬�����ö�̬ (DLL) �汾������ʱ�����ӵ� .exe �ļ�һ��ʹ��ʱ���þ�̬���� DLL���汾������ʱ�����ӵĶ�̬���ӿ���ܵ������⡣����Ӧ�ñ�����һ�������л��ʹ����Щ��ĵ��԰汾�ͷǵ��԰汾����
��仰����˼��exe���̾�������Ҫô�����ö�̬�⣬Ҫô����̬�⣬��Ҫ�����ö�̬�����þ�̬�������������ͻ
���о��Ǳ�̬����������һ����̬�⣬Ȼ��ö�̬���ֱ�exe�����ˣ���Щ��������ɳ�ͻ


### ���벢����boost�� 
���ر���õİ汾 https://sourceforge.net/projects/boost/files/boost-binaries/
����Ŀ¼��D:\apps\boost_1_86_0
������ : D:\apps\boost_1_86_0\lib32-msvc-14.3

### ����websocketpp��������websocketpp
����ֱ�����ø���Ŀ¼����
```
git clone https://github.com/zaphoyd/websocketpp
```
����Ŀ¼���ã�D:\apps\websocketpp-0.8.2
