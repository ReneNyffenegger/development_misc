'
'  ..\runVBAFilesInOffice -excel HTTP_fetch -c Go
'
'  Fetch data from via HTTP
'

option explicit

public sub Go() ' {

    with activeSheet.queryTables.add ( _
         connection  := "URL;https://raw.github.com/ReneNyffenegger/development_misc/master/vba/excel/HTTP_fetch.bas", _
         destination :=  range("A1") )

        .refresh    backgroundQuery := false

    end with

end sub ' }
