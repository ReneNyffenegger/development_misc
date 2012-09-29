' 
'  http://stackoverflow.com/a/3801102/180275
'

const forReading = 1    
const forWriting = 2

strFileName = wscript.arguments(0)
strOldText  = wscript.arguments(1)
strNewText  = wscript.arguments(2)

set objFSO = createObject("Scripting.FileSystemObject")
set objFile = objFSO.openTextFile(strFileName, forReading)
strText = objFile.readAll
objFile.Close

strNewText = Replace(strText, strOldText, strNewText)
set objFile = objFSO.openTextFile(strFileName, forWriting)
objFile.write strNewText  'WriteLine adds extra CR/LF
objFile.close
