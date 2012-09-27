
' ..\runVBAFilesInOffice.vbs -excel drawSphere -c Run

option explicit

public sub Run() ' [

  dim x as long
  dim y as long
  dim w as double

  dim sphere as shape
  dim rg_dat as range

  w = 11

  for x = 1 to w ' {

      cells(1, x+1) = x - 1

      for y = 1 to w ' {

          cells(y+1, 1) = y - 1

      next y ' }

  next x ' }


  for x = 2 to w + 1 ' {
  for y = 2 to w + 1

      cells (y, x).formula = "=sqrt(1-min(1," & _
                             "(" &  (w-1) / 2 & " - " & cells(y,1).address & ") / " & (w-1)/2 & " * " & _
                             "(" &  (w-1) / 2 & " - " & cells(y,1).address & ") / " & (w-1)/2         & _
                      " + "  &                                                                   _
                             "(" &  (w-1) / 2 & " - " & cells(1,x).address & ") / " & (w-1)/2 & " * " & _
                             "(" &  (w-1) / 2 & " - " & cells(1,x).address & ") / " & (w-1)/2         & _
                             ") )"
                                

  next y
  next x ' }

  set rg_dat = range(cells(2,2).address & ":" & cells(w+1,w+1).address)

  set sphere = activeSheet.shapes.addChart

  sphere.chart.setSourceData source := rg_dat

  sphere.chart.chartType = xlSurface
  

end sub ' }
