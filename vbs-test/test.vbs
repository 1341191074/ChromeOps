Set chrome = CreateObject("ChromeOps.soft")

'�����������
call chrome.pushArgs("--remote-debugging-port=9222")
Call chrome.pushArgs("--user-data-dir=E:\\test\\ud0")
Call chrome.launch("C:\\Users\\Reach\\AppData\\Local\\Google\\Chrome\\Application\\chrome.exe", True)
targetList = chrome.findTargetList()
uuid = chrome.parseJson(targetList)
size = chrome.getJsonArraySize(uuid)
WScript.Echo "size = " & size
For idx=0 to size-1
    ' �ڶ������������-1 ������Ϊ�Ƕ��󣬷�֮��������
    targetId = chrome.getJsonValue(uuid, idx, "targetId")
    title = chrome.getJsonValue(uuid, idx, "title")
    WScript.Echo "targetId = "&targetId&" , title = "&title
Next

isBind = chrome.switchTab(targetId)
If isBind = 1 Then 
    urls = "https://tieba.baidu.com/|https://www.baidu.com/|https://www.csdn.net/"
    'ary = Split(urls, chr(10))
    ary = Split(urls, "|")
    aryLen = UBound(ary)
    For idx = 0 To aryLen
        Call chrome.navigate(ary(idx), "")
        '//0=û�м������ 1=�������
        finished = chrome.isLoadingFinished()
        While finished = 0
        	' WScript.Echo
            WScript.Echo "�ȴ�����"
            Delay 200
            finished = chrome.isLoadingFinished()
        Wend
        picName = "e:\test\" & idx & ".jpg"
        WScript.Echo "�������"&ary(idx)&"��׼����ͼ" & picName
        'Call chrome.captureFullScreenshot("jpeg", 100, picName)
        Call chrome.captureScreenshot("jpeg", 100, 0, 0, 0, 0, 1.0, picName)
    Next
End If

Set chrome = Nothing
