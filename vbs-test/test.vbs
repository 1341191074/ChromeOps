'���б�����ִ�к�ʹ��ѡ��
option Explicit
dim cc
dim chrome
dim ss
'����ֵ����ʹ��SET�ؼ��ָ�ֵ
set chrome = CreateObject("ChromeOps.soft")

WScript.Echo "����������������"

'�����������
call chrome.pushArgs("--remote-debugging-port=9222")
call chrome.pushArgs("--user-data-dir=E:\\test\\ud0")
'���������
'call cc.launch("C:\\Users\\Reach\\AppData\\Local\\Google\\Chrome\\Application\\chrome.exe")
'call chrome.launch("C:\\Users\\Lenovo\\AppData\\Local\\Google\\Chrome\\Application\\chrome.exe",false)
'WScript.Sleep 200
WScript.Echo "��ʼ��"
ss=chrome.chromeBind("localhost",9222)
WScript.Echo "�󶨳ɹ�"

WScript.Echo "��ʼ��ѯ"
ss=chrome.findTargetList()
dim ary
ary=Split(ss,"====")
ss=ary(0)
dim tab
tab=Split(ss,"|||")
WScript.Echo tab(0)
ss=chrome.switchTab(tab(0))


call chrome.clearBrowserCache()
'call chrome.clearBrowserCookies()

call chrome.navigate("https://www.baidu.com", "")

dim finished 
'//0=û�м������ 1=�������
finished = chrome.isLoadingFinished()
while finished=0
    WScript.Echo "�ȴ�����"
    WScript.Sleep 500
    finished = chrome.isLoadingFinished()
wend

'ss = chrome.getCookies("[""https://www.baidu.com""]")
'WScript.Echo ss

'call chrome.captureScreenshot("jpeg", 100, 0, 0, 2094, 2094, 1.0, "output.jpg")
'call chrome.captureFullScreenshot("png", 100, "output1.png")
'call chrome.captureFullScreenshot("jpeg", 100, "output2.jpg")

WScript.Echo "8����Զ��ر�"
WScript.Sleep 8000

set cc = Nothing