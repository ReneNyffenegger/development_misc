'
'  ..\runVBAFilesInOffice -excel inputbox -c Go
'

option explicit

public sub Go() ' {

    ' Ask for a value and write it into cell B1

    range("a1").value = "Your answer was:" 
    range("b1").value =  inputBox("What is your answer")

end sub ' }
