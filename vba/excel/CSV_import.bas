option explicit

'
'  Import csv_file_name
'
'  column_data_types is an array that defines the «data type» of the csv columns.
'  The elements of this array are one of:
'      xlGeneralFormat
'      xlTextFormat
'      xlSkipColumn
'      xlDMYFormat
'      xlDYMFormat
'      xlEMDFormat
'      xlMDYFormat
'      xlMYDFormat
'      xlYDMFormat
'      xlYMDFormat
'
'  See some_data_import.bas for an example.
'  See also https://github.com/ReneNyffenegger/oracle_scriptlets/blob/master/awr/AWRDataToExcel.bas
'

public sub CSV_import(csv_file_name as string, column_data_types as variant) ' {

  ' TODO: can column_data_types' data type be declared more concisely as just «variant».

    dim sh   as workSheet
    dim dest as range
    dim qt   as queryTable

    set sh   = ActiveSheet                  ' or  Application.Sheets(1)  ?
    set dest = Application.Range("$A$1")

    set qt   = sh.QueryTables.Add ( Connection  := "TEXT;" & csv_file_name, _
                                    Destination := dest )


    qt.name              = "importedData"
    qt.refreshOnFileOpen = false
    qt.adjustColumnWidth = true
    qt.textFilePlatform  = 850 ' MS-Dos ?
    qt.textFileStartRow  = 1

    qt.textFileParseType     = xlDelimited
    qt.textFileTextQualifier = xlTextQualifierDoubleQuote

 ' --------------------------------------------

    qt.textFileConsecutiveDelimiter = false
    qt.textFileTabDelimiter         = true
    qt.textFileSemicolonDelimiter   = true
    qt.textFileCommaDelimiter       = false
    qt.textFileSpaceDelimiter       = false

 ' --------------------------------------------

   ' Define the «data type» of the imported columns.

    qt.textFileColumnDataTypes = column_data_types

    qt.refresh

end sub ' }
