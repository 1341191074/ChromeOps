https://www.cnblogs.com/ligang0357/p/17188394.html


vs2022 ����ʹ��libcurl
1����������libcurl 

https://curl.se/download/curl-7.88.1.tar.gz

2����ѹִ��curlĿ¼�µ�buildconf.bat��Ȼ��cd winbuild

3������
windows�±���(MT):

32-debug: nmake /f Makefile.vc mode=static vc=17 debug=yes rtlibcfg=static machine=x32 ENABLE_IDN=no

32-release: nmake /f Makefile.vc mode=static vc=17 debug=no rtlibcfg=static machine=x32 ENABLE_IDN=no

64-debug: nmake /f Makefile.vc mode=static vc=17 debug=yes rtlibcfg=static machine=X64 ENABLE_IDN=no

64-release: nmake /f Makefile.vc mode=static vc=17 debug=no rtlibcfg=static machine=X64 ENABLE_IDN=no

windows�±���(MD):

32-debug: nmake /f Makefile.vc mode=static vc=10debug=yes machine=x32 ENABLE_IDN=no

32-release: nmake /f Makefile.vc mode=static vc=10debug=no machine=x32 ENABLE_IDN=no

64-debug: nmake /f Makefile.vc mode=static vc=10debug=yes machine=X64 ENABLE_IDN=no

64-release: nmake /f Makefile.vc mode=static vc=10debug=no machine=X64  ENABLE_IDN=no

�ص���һ��Ҫ��ENABLE_IDN=no��Ĭ���Ǵ򿪵ģ����ӵĻ���������

X64���оͻ�AMD64

Boost��װ64λ��

1.  ��boost������www.boost.org������boost�⣬�Ѿ����µ�1.62.0������boost_1_62_0.zip����ѹ��ָ����·������ѡ���·����E:oost����

2.  �ӿ�ʼ->���г���->Microsoft Visual Studio 2010����Visual Studio Tools��Visual Studio x64 Win64������ʾ��

3.  �л�����ѹ·��E:oostoost_1_62_0�£�����bootstrap.bat���������빤��bjam.exe,b2.exe��

4. b2 --toolset=msvc-10.0 --build-type=complete link=static address-model=64 threading=multi variant=release

 

 

ע��vs release�汾��д debug=no��vs mt ������Ҫ�� rtlibcfg=static ����

 

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