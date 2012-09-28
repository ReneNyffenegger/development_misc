'
' ..\runVBAFilesInOffice.vbs -visio connect_two_rectangles -c ConnectTwoRectangles
'
public sub ConnectTwoRectangles()
 
  dim  rect1 as visio.shape
  dim  rect2 as visio.shape
  dim  line  as visio.shape
  
  set rect1 = activePage.drawRectangle(1, 4, 3, 7)
  set rect2 = activePage.drawRectangle(4, 2, 7, 3)

  rect1.text = "First"
  rect2.text = "Second"

' set line  = activePage.shapes.item  ("Dynamic connector")
  set line  = application.activeWindow.page.drop(application.connectorToolDataObject, 0, 0)

  line.cellsU("BeginX").glueTo rect1.cellsSRC(1,1,0)
  line.cellsU("EndX"  ).glueTo rect2.cellsSRC(1,1,0)


' rect1.autoConnect rect2, visAutoConnectDirRight, line
  
end sub
