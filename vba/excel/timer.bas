'
'  ..\runVBAFilesInOffice -excel timer -c Go
'
'  Waiting a predefined amount of time for the next action.
'

option explicit

public sub Go() ' {

    msgBox "next message box in 2 seconds"

    application.onTime now + timeValue("00:00:02"), "timeReached_01"

end sub ' }

private sub timeReached_01() ' {


    msgBox "next message box in 5 seconds"
    

    application.onTime now + timeValue("00:00:05"), "timeReached_02"

end sub ' }

private sub timeReached_02() ' {

    msgBox "the end of the demo."

end sub ' }
