'
' call
'
'    runVBAFilesInOffice.vbs -excel indentTxtFile -c Go "%CD%\someCities.txt"
'
' where someCities.txt is the file to be «parsed».
'
' someCities.txt is read line by line.
'
' Empty lines are skipped (no actions)
'
' Lines containing a "{" with any numbers of whitespaces are not copied into excel,
' but increase indentation.
' Similar for "}" but they decrease indentation.
'
' The rest is copied into excel according to current indentation.
'

option explicit

public sub Go(input_file_name as string) ' {

    call iterate_file(input_file_name)

end sub ' }

private sub iterate_file(input_file_name as string) ' {

    dim line_read            as string
    dim line_number          as long
    dim opening_line         as long
    dim current_indent_level as long

    const file_number    = 1

    line_number          = 0
    current_indent_level = 1

    activeSheet.outline.summaryRow = xlAbove

  ' ---

  ' Regular Expressions require "Microsoft VBScript Regular Expressions 5.5"
  ' The GUID of which is {3F4DACA7-160D-11D2-A8E9-00104B365C9F}
    
    dim re_open_indent  as regExp 
    dim re_close_indent as regExp 
    dim re_empty_line   as regExp

    set re_open_indent  = new regExp 
    set re_close_indent = new regExp 
    set re_empty_line   = new regExp 

    re_open_indent.pattern  = "^\s*{\s*$"
    re_close_indent.pattern = "^\s*}\s*$"
    re_empty_line.pattern   = "^\s*$"

  ' ---

    dim line_of_group_start as collection
    set line_of_group_start = new collection

    open input_file_name for input as file_number

    do while not eof (file_number)
       line input #file_number, line_read

    '  Skip empty lines:
       if not re_empty_line.test(line_read) then

          if     re_open_indent.test(line_read) then

                 line_of_group_start.add(line_number)

                 current_indent_level = current_indent_level + 1

          elseif re_close_indent.test(line_read) then

                 opening_line = line_of_group_start.item(line_of_group_start.count) + 1

                 range(rows(opening_line), rows(line_number)).select
                 selection.rows.group


 '               msgBox (opening_line & " - " & line_number)

                 line_of_group_start.remove(line_of_group_start.count)
                 current_indent_level = current_indent_level - 1

          else
                 line_number = line_number + 1
                 cells(line_number, current_indent_level) = line_read

          end if



       end if

    loop

  ' "close" all indents:
    activeSheet.outline.showLevels rowLevels:=1

end sub ' }
