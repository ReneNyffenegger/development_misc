' ..\runVBAFilesInOffice.vbs -excel RegExp -c RegExpTest
option explicit 

public sub RegExpTest()

  dim re as    regExp ' *  Requires "Microsoft VBScript Regular Expressions 5.5" * 
  set re = new regExp ' * {3F4DACA7-160D-11D2-A8E9-00104B365C9F}                 *
  
  re.pattern = "\d"  ' Grep numbers
  re.global  = true  ' globally, in perl this is "/g"
  
  dim result as string
  result = re.replace("abc 123 def 456", "*")
' result is            abc *** def ***
  
  msgBox (result)


' grep «word» between first and second :
  re.pattern = "[^:]+:([^:]+):.*$"
  re.global  = false

  result = re.replace("foo:bar:baz etc", "$1")
' result is                bar

  msgBox (result)

  if not re.test("doesn't match") then
  '  This one is printed
     msgBox "doesn't match"
  end if

  if re.test("foo:bar:baz etc") then
  '  This one is printed
     msgBox "foo:bar:baz etc"
  end if

'' How can be tested, if it really matched?
'  result = re.replace("doesn't match.", "$1")
'  msgBox (result) 
'
'' It can be tested like so:
'  dim matches as matchCollection
'  set matches = re.execute("doesn't match.")
'  msgBox("matches.count: " & matches.count)
'
'  set matches = re.execute("foo:bar:baz etc")
'  msgBox("matches.count: " & matches.count & ", matches(0): " & matches(0))

' grep word, number, word (seperated by :)
  re.pattern="(\w+):(\d+):(\w+):"
  dim matches as matchCollection
  set matches = re.execute("foo:42:bar:etc")
' print  foo                                42                                 bar
  msgBox(matches(0).subMatches(0) & " - " & matches(0).subMatches(1) & " - " & matches(0).subMatches(2))


' Grep first 3-digit Number
  re.pattern = " (\d{3}) "
  set matches = re.execute("1 23 456 7890")
'        456
  msgBox(matches(0).subMatches(0))
  

end sub
