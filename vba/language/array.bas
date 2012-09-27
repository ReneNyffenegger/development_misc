option explicit

'
' ..\runVBAFilesInOffice -excel array -c array_test
'
public sub array_test()

    dim a(0 to 2) as string

    dim i as long

    a(0) =  "foo"
    a(1) =  "bar"
    a(2) =  "baz"


 '  TODO: is there REALLY no way to do the same thing
 '        without declaring the variable
    for i = lbound(a) to ubound(a)
        msgBox a(i)
    next i

end sub
