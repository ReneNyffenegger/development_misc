
'    convert a column/row pair to its address.
'
'    For example cells(3, 2).address becomes "$B$3"
'
' ..\runVBAFilesInOffice.vbs -excel row_column_to_address -c Run

option explicit

public sub Run() ' [

  dim x as long
  dim y as long
  dim w as long

  w = 20

  for x = 1 to w + 1 ' {
  for y = 1 to w + 1

      cells (y, x) = cells(y, x).address                               

  next y
  next x ' }

end sub ' }
