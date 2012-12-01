' ..\runVBAFilesInOffice.vbs -excel WinHttp.WinHttpRequest -c getUrl www.google.com
option explicit 

public sub getUrl(url as string)

    dim winHttpReq as Object

    set winHttpReq = createObject("WinHttp.WinHttpRequest.5.1")

    winHttpReq.open "GET", url, false
    winHttpReq.send

    cells(1,1) = winHttpReq.responseText

end sub
