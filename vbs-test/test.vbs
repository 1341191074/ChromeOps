'���б�����ִ�к�ʹ��ѡ��
option Explicit
dim cc
dim chrome
dim ss
'����ֵ����ʹ��SET�ؼ��ָ�ֵ
set chrome = CreateObject("ChromeOps.soft")

'�����������
call chrome.pushArgs("--remote-debugging-port=9222")
call chrome.pushArgs("--user-data-dir=E:\\test\\ud0")
'���������
'call cc.launch("C:\\Users\\Reach\\AppData\\Local\\Google\\Chrome\\Application\\chrome.exe")
'call cc.launch("C:\\Users\\Lenovo\\AppData\\Local\\Google\\Chrome\\Application\\chrome.exe",false)
'WScript.Sleep 200
ss=chrome.chromeBind("localhost",9222)
ss=chrome.findTargetList()
dim ary
ary=Split(ss,"====")
ss=ary(0)
dim tab
tab=Split(ss,"|||")
WScript.Echo tab(0)
ss=chrome.switchTab(tab(0))
call chrome.navigate("http://www.sina.com.cn", "")
WScript.Sleep 1000
dim finished 
'//0=û�м������ 1=�������
finished = chrome.isLoadingFinished()
while finished=0
    WScript.Echo "�ȴ�����"
    WScript.Sleep 500
    finished = chrome.isLoadingFinished()
wend


WScript.Echo "8����Զ��ر�"
WScript.Sleep 8000

set cc = Nothing