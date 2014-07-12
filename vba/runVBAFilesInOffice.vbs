' This script can be used to load *.bas files into an Office-Application (Excel, Word...) {
' and then execute a function in that/those *.bas files.
' 
'
' The syntax (in cmd.exe) is:
'
'   x:\foo\bar> runVBAFilesInOffice.vbs -office_application file_one file_two -c sub_name param_1 param_2 ...
'  
'      -office_application is one of (with leading hyphen):
'           "-excel"
'           "-word"
'           "-visio"
'
'
' Note, the suffix .bas must be omitted.
'
'
' So, for example, to load foo.bas and bar.bas into Excel and execute
' the function/sub baz(1,2,3), the following should be used:
'
'    c:\> runVBAFilesInOffice.vbs -excel foo bar -c baz 1 2 3
'
' ----------------------------------------------------------------------------
'
'   English
'   -------
'
'      If the error 
'
'          Programmatic access to Visual Basic Project is not trusted
'         (Code: 800A03EC)
'
'      is thrown, access should be allowed like so:
'
'          (Excel,...)                                               -> 
'           Options                                                  -> 
'           Trust Center                                             ->
'           Trust Center Settings (Button)                           ->
'           Macro Settings                                           ->
'           Trust access to the VBA project object model (check box)
'
'   German:
'   -------
'     Bei der Fehlermeldung
'
'        Microsoft Word: Dem programmatischen Zugriff auf das Visual Basic-Projekt wird nicht vertraut.
'
'   sollte auf dem Office Button (Einstellungen) in (zB) Word auf
'      (Word-)Optionen gegangen werden              -> 
'       Vertrauensstellungscenter                   -> 
'       Einstellungen für Vertrauensstellungscenter -> 
'       Einstellungen für Makros                    -> 
'       Zugriff auf das VBA-Projektobjektmodell vertrauen
'   gemacht werden.
'
'   --------------------------------------------------------------------------
'
'   Bei der Fehlermeldung in Visio (2007)
'
'        Programmzugang zu einem Visual Basic-Projekt ist deaktiviert.
'        Code: 86DB08BA
'
'    sollte in
'      Extras                    -> 
'      Vertrauensstellungscenter -> 
'      Einstellungen für Makros  ->
'    das Häckchen auf
'      Zugriff auf das VBA-Projektobjektmodell vertrauen
'    gesetzt werden.
'      
' }

option explicit

private function PathIsRelative(path) ' {
  
  dim position 
  position = inStr(path, ":")

  if position > 0 then 
     PathIsRelative = false
  else 
     PathIsRelative =  true
  end if 

end function ' }

'private declare function PathIsRelative lib "shlwapi" _
'                alias   "PathIsRelativeA"             _
'  (byVal pszPath as string) as long



                          ' .vbs doesn't allow to explicitely
                          '  define datatypes...
                          '            
dim office_app            ' as  object
dim office_doc            ' as  object
dim workbook              ' as  object
dim vb_editor             ' as  object
dim shell_obj             ' as  object
dim cur_dir               ' as  string
dim args                  ' as  string
dim function_name_to_call ' as  string
dim vbs_name_to_import    ' as  string
dim cur_param             ' as    long
dim is_visio              ' as boolean

is_visio = false

set shell_obj = createObject("WScript.Shell")
cur_dir = shell_obj.currentDirectory

set args = WScript.arguments

if args.count < 2 then 
  WScript.echo ("Insufficient number of arguments specified." & vbCrLf & "See source code for further details.")
  WScript.quit
end if

dim vb_comps

'   ---  Start Office Application and VB-Editor (corresp +/- Alt-F11)   -------+
if     args(0) = "-excel" then                                               ' |
                 set office_app = createObject("Excel.Application")          ' |
                 set office_doc = office_app.workbooks.add                   ' |
                 set vb_editor  = office_app.vbe                             ' |
                 set vb_comps   = vb_editor.activeVBProject.VBComponents     ' |
                                                                             ' |
elseif args(0) = "-word"  then                                               ' |
                 set office_app = createObject("Word.Application")           ' |
                 set office_doc = office_app.documents.add                   ' |
                 set vb_editor  = office_app.vbe                             ' |
                 set vb_comps   = office_doc.VBProject.VBComponents          ' |
                                                                             ' |
elseif args(0) = "-visio" then                                               ' |
                 set office_app = createObject("Visio.Application")          ' |
                 set office_doc = office_app.documents.add("")               ' |
                 set vb_editor  = office_app.vbe                             ' |
                 set vb_comps   = office_doc.VBProject.VBComponents          ' |
                                                                             ' |
                 is_visio       = true                                       ' |
                                                                             ' |
else                                                                         ' |
                 msgBox("First Parameter neither -excel, -word nor -visio")  ' |
                 Wscript.quit                                                ' |
                                                                             ' |
end if                                                                       ' |
                                                                             ' |
office_app.visible = true                                                    ' |
                                                                             ' |
'------------------------------------------------------------------------------+

'------------------------------------------------------------------------------+
' Type Libs                                                                    |
' ---------                                                                  ' |
'   Find them in the registry under HKEY_CLASSES_ROOT\TypeLib...             ' |
'                                                                            ' |
' Microsoft Access 11.0 Object Library:                                      ' | 
' call addReference(office_doc, "{4AFFC9A0-5F99-101B-AF4E-00AA003F0F07}")    ' |
'                                                                            ' |
' Microsoft DAO 3.6 Object Library:                                          ' |
' call addReference(office_doc, "{00025E01-0000-0000-C000-000000000046}")    ' |
'                                                                            ' |
' Microsoft Scripting Runtime:                                               ' |
  call addReference(office_doc, "{420B2830-E718-11CF-893D-00A0C9054228}")    ' |
'                                                                            ' |
' Microsoft VBScript Regular Expressions 5.5:                                ' |
  call addReference(office_doc, "{3F4DACA7-160D-11D2-A8E9-00104B365C9F}")    ' |
'                                                                            ' |
' Microsoft ActiveX Data Objects 2.8 Library:                                ' |
  call addReference(office_doc, "{2A75196C-D9EB-4129-B803-931327F72D5C}")    ' |
                                                                             ' |
'------------------------------------------------------------------------------+

cur_param = 1

do while args(cur_param) <> "-c" ' {
   vbs_name_to_import    = args(cur_param) & ".bas"

   dim path_to_imported_file

   if PathIsRelative(vbs_name_to_import) then
      path_to_imported_file = cur_dir & "\" & vbs_name_to_import
   else
      path_to_imported_file = vbs_name_to_import
   end if

   vb_comps.import(path_to_imported_file)

   cur_param = cur_param + 1
loop ' }

' jump over "-c"
cur_param = cur_param + 1


' --- the first argument after -c is the name of the
'     function (more accuratly: the Sub) to be called:
function_name_to_call = args(cur_param)

cur_param = cur_param + 1

dim dummy

if not is_visio then ' {
if     args.count - cur_param =  0 then ' {
 dummy = office_app.run(function_name_to_call) ' }
elseif args.count - cur_param =  1 then ' {
 dummy = office_app.run(function_name_to_call, args(cur_param)) ' }
elseif args.count - cur_param =  2 then ' {
 dummy = office_app.run(function_name_to_call, args(cur_param), args(cur_param+1)) ' }
elseif args.count - cur_param =  3 then ' {
 dummy = office_app.run(function_name_to_call, args(cur_param), args(cur_param+1), args(cur_param+2)) ' }
elseif args.count - cur_param =  4 then ' {
 dummy = office_app.run(function_name_to_call, args(cur_param), args(cur_param+1), args(cur_param+2), args(cur_param+3)) ' }
elseif args.count - cur_param =  5 then ' {
 dummy = office_app.run(function_name_to_call, args(cur_param), args(cur_param+1), args(cur_param+2), args(cur_param+3), args(cur_param+4)) ' }
elseif args.count - cur_param =  6 then ' {
 dummy = office_app.run(function_name_to_call, args(cur_param), args(cur_param+1), args(cur_param+2), args(cur_param+3), args(cur_param+4), args(cur_param+5)) ' }
elseif args.count - cur_param =  7 then ' {
 dummy = office_app.run(function_name_to_call, args(cur_param), args(cur_param+1), args(cur_param+2), args(cur_param+3), args(cur_param+4), args(cur_param+5), args(cur_param+6)) ' }
elseif args.count - cur_param =  8 then ' {
 dummy = office_app.run(function_name_to_call, args(cur_param), args(cur_param+1), args(cur_param+2), args(cur_param+3), args(cur_param+4), args(cur_param+5), args(cur_param+6), args(cur_param+7)) ' }
elseif args.count - cur_param =  9 then ' {
 dummy = office_app.run(function_name_to_call, args(cur_param), args(cur_param+1), args(cur_param+2), args(cur_param+3), args(cur_param+4), args(cur_param+5), args(cur_param+6), args(cur_param+7), args(cur_param+8)) ' }
elseif args.count - cur_param = 10 then ' {
 dummy = office_app.run(function_name_to_call, args(cur_param), args(cur_param+1), args(cur_param+2), args(cur_param+3), args(cur_param+4), args(cur_param+5), args(cur_param+6), args(cur_param+7), args(cur_param+8), args(cur_param+9)) ' }
else ' {
  msgBox "args.count - cur_param = " & (args.count - cur_param)
end if ' }
' }
else ' { Call a function in Visio:
 if      args.count - cur_param =  0 then ' {
  call office_doc.executeLine(function_name_to_call) ' }
 elseif  args.count - cur_param =  1 then ' {
  call office_doc.executeLine(function_name_to_call & " """ & args(cur_param) & """ ") ' }
 elseif  args.count - cur_param =  2 then ' {
  call office_doc.executeLine(function_name_to_call & """" & args(cur_param) & """,""" & args(cur_param+1) & """") ' }
 elseif  args.count - cur_param =  3 then ' {
  call office_doc.executeLine(function_name_to_call & """" & args(cur_param) & """,""" & args(cur_param+1) & """,""" & args(cur_param+2) & """") ' }
 elseif  args.count - cur_param =  4 then ' {
  call office_doc.executeLine(function_name_to_call & """" & args(cur_param) & """,""" & args(cur_param+1) & """,""" & args(cur_param+2) & """,""" & args(cur_param+3) & """") ' }
 else  ' {
   msgBox("Count of parameters not yet implemented for visio!")
   Wscript.quit
 end if ' }
end if ' }


set office_app = nothing

Wscript.quit

sub addReference(obj, guid)
  on error resume next

  dim refs
  set refs = obj.VBProject.References
  refs.AddFromGuid guid, 0, 0

  if err.number <> 0 then ' {

     if      err.number   =  -2147319779  then

     '       TODO:
     '       In german, the error message is «Objektbibliothek nicht registriert»

     elseif  err.number <> 32813 then

     '       one wonders what 32813 is
             msgBox "Error: " & err.number & vbNewLine & err.description

     end if

  end if ' }

end sub
