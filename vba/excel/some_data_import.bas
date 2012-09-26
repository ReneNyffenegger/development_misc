'
'      ..\runVBAFilesInOffice.vbs -excel some_data_import -c Go %CD%\some_data.csv
'
option explicit

public sub Go(filename as string) ' {

    dim sh        as WorkSheet
    dim dest      as Range           
    dim qt        as QueryTable

    set sh    = ActiveSheet ' Application.Sheets(1)
    set dest  = Application.Range("$A$1")


    set qt = sh.QueryTables.Add ( Connection  := "TEXT;" & filename, _
                                  Destination :=  dest )


    qt.name                  = "importedData"
    qt.refreshOnFileOpen     =  false
    qt.adjustColumnWidth     =  true
    qt.textFilePlatform      =  850    ' MS-Dos ?
    qt.textFileStartRow      =  1

    qt.textFileParseType     =  xlDelimited
    qt.textFileTextQualifier =  xlTextQualifierDoubleQuote

 '  --------------------------------------------

    qt.textFileConsecutiveDelimiter = false
    qt.textFileTabDelimiter         = true
    qt.textFileSemicolonDelimiter   = true
    qt.textFileCommaDelimiter       = false
    qt.textFileSpaceDelimiter       = false

 '  --------------------------------------------

   ' Define the «data type» of the imported columns.
   ' Possible values are:
   '
   ' xlGeneralFormat
   ' xlTextFormat
   ' xlSkipColumn
   ' xlDMYFormat
   ' xlDYMFormat
   ' xlEMDFormat
   ' xlMDYFormat
   ' xlMYDFormat
   ' xlYDMFormat
   ' xlYMDFormat

    qt.textFileColumnDataTypes = Array ( xlGeneralFormat , _
                                         xlGeneralFormat , _
                                         xlGeneralFormat , _
                                         xlGeneralFormat , _
                                         xlTextFormat    , _ 
                                         xlDMYFormat) 
   
    
    qt.refresh

end sub ' }
