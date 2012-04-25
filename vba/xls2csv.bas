
'    runVBAFilesInOffice.vbs -excel xls2csv -c Go xls_dir csv_dir ;
'
' This script exports XLS files within a given direcdtory (first argument) to CSV files, and saves them
' into the directory given with the second argument.
'
' The third parameter is either "tab" or another string.
' If "tab", the values are seperated by a tabulator, else
' by a ",". TODO: a freely choosable character would be kinda cool.
'


option explicit

public sub Go(xls_dir_name as string, csv_dir_name as string, is_tab as string) ' {
'  iterate_files_in_folder(xls_dir_name, csv_dir_name)

   dim xls_name as string

   dim file_counter  as long


   file_counter = 1 

   xls_name = dir(xls_dir_name & "\*.xls")

    while xls_name <> ""
       call xls_2_csv(xls_dir_name, xls_name, csv_dir_name, file_counter, is_tab)
       file_counter = file_counter + 1

       xls_name = dir()
    wend
end sub ' }

private sub xls_2_csv(xls_dir_name as string, xls_name as string, csv_dir_name as string, file_counter as long, is_tab as string) ' {
    cells(file_counter, 1) = xls_name 

    dim fileFormat_ as long
    dim outFileName as string

    fileFormat_ = xlCSV
    outFileName = replace(xls_name, ".xls", ".csv")

    if  is_tab = "tab" then
        fileFormat_ = xlText
        outFileName = replace(xls_name, ".xls", ".txt")
    end if


'   don't ask if really should be saved:
    application.displayAlerts = false

'   chr$(92) is a back slash.
    workbooks.open filename          := xls_dir_name & chr$(92) & xls_name

    activeWorkbook.saveAs filename   := csv_dir_name & chr$(92) & outFileName, fileFormat := fileFormat_

    activeWindow.close

end sub ' }
