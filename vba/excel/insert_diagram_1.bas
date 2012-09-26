'
'      Create some sample data and create a Line Chart on them.
'
'      ..\runVBAFilesInOffice.vbs -excel insert_diagram_1 -c Go
'
option explicit

public sub Go() ' {

    dim rg_data as range

    set rg_data = fillData()

    insertDiagram      rg_data  := rg_data                , _
                       sh_chart := application.activeSheet

end sub ' }

private sub insertDiagram(rg_data as range, sh_chart as workSheet) ' {

    dim ch as Shape

    set ch = sh_chart.shapes.addChart 

    ch.chart.chartType = xlLine

    ch.chart.setSourceData source := rg_data

end sub ' }

function fillData() as range ' {

    range("b1").value = "Foo Series"
    range("c1").value = "Baz Series"

    range("a2").value = "abcd"
    range("a3").value = "efgh"
    range("a4").value = "ijkl"
    range("a5").value = "mnop"

    range("b2").value =    17 : range("c2").value =    24
    range("b3").value =     5 : range("c3").value =    21
    range("b4").value =    10 : range("c4").value =    13
    range("b5").value =    12 : range("c5").value =    15

    set fillData = range("$a1:$c5")

end function ' }
