option explicit

' http://www.adp-gmbh.ch/win/vba/for_to_step.html
' 
' ..\runVBAFilesInOffice -excel for_to_step -c for_to_step
'
' Control structures: http://support.microsoft.com/kb/141762
public sub for_to_step()

  dim i as long

  for i = 10 to 22 step 3
    msgBox(i) ' 10, 13, 16, 19, 22
  next

end sub
