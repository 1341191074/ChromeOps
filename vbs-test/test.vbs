'所有变量先执行后使用选项
option Explicit
dim cc
dim chrome
dim ss
'对象值必须使用SET关键字赋值
set chrome = CreateObject("ChromeOps.soft")

'添加启动参数
call chrome.pushArgs("--remote-debugging-port=9222")
call chrome.pushArgs("--user-data-dir=E:\\test\\ud0")
'启动浏览器
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
'//0=没有加载完成 1=加载完成
finished = chrome.isLoadingFinished()
while finished=0
    WScript.Echo "等待……"
    WScript.Sleep 500
    finished = chrome.isLoadingFinished()
wend


WScript.Echo "8秒后自动关闭"
WScript.Sleep 8000

set cc = Nothing