'
' Test CSV_Import.bas
'
' ..\runVBAFilesInOffice.vbs -excel CSV_Import some_data_import -c Go %CD%
'
option explicit

public sub Go(current_dir) ' {

    CSV_Import current_dir & "\some_data.csv"   , _
                        array ( xlGeneralFormat , _
                                xlGeneralFormat , _
                                xlGeneralFormat , _
                                xlGeneralFormat , _
                                xlTextFormat    , _ 
                                xlDMYFormat) 

end sub ' }
