' 
' ..\runVBAFilesInOffice.vbs -excel groupRows -c Run
'

sub go() ' {

    cells ( 1,1) = "Some Cities"
    cells ( 2,2) =   "America"
    cells ( 3,3) =     "North America"
    cells ( 4,4) =       "USA"

    cells ( 5,5) =         "New York"
    cells ( 6,5) =         "Los Angeles"
    cells ( 7,5) =         "Houston"

    cells ( 8,4) =       "Canada"
    cells ( 9,5) =         "Toronto"

    cells (10,3) =     "South America"

    cells (11,4) =       "Brazil"
    cells (12,5) =         "Rio de Janeiro"
    cells (13,5) =         "Sao Paolo"

    cells (14,4) =       "Argentina"
    cells (15,5) =         "Boenos Aires"
    cells (16,5) =         "Corrientes"
    cells (17,5) =         "San Luis"

    cells (18,2) =   "Europe"
    cells (19,3) =     "Germany"
    cells (20,4) =       "Berlin"
    cells (21,4) =       "Stuttgart"
    cells (22,3) =     "France"
    cells (23,4) =       "Paris"
    cells (24,4) =       "Marseille"
    cells (25,4) =       "Lyon"

    activeSheet.outline.summaryRow = xlAbove

    range(rows( 5),rows( 7)).group
    range(rows( 4),rows( 9)).group

    range(rows( 9),rows( 9)).group


    range(rows(12),rows(13)).group
    range(rows(15),rows(17)).group

    range(rows(11),rows(17)).group

    range(rows( 3),rows(17)).group

    range(rows(20),rows(21)).group
    range(rows(23),rows(25)).group
    range(rows(19),rows(25)).group

end sub ' }
