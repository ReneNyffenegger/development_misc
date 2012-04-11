#JFrame

A **Frame** is a *top-level* window with

  * a title, and
  * a border

#JEditorPane

A **JEditorPane** can be used to display HTML or RTF.

[This example](https://raw.github.com/ReneNyffenegger/development_misc/master/java/swing/JEditorPane/GeneratedHTML.java) generates HTML and displays it.

[This example](https://raw.github.com/ReneNyffenegger/development_misc/master/java/swing/JEditorPane/HtmlLinks.java) extends *GeneratedHTML.java* in that
it has links that can be clicked.

#JTable

A **JTable** displays *tabular* data.

[ScrollableTable.java](https://raw.github.com/ReneNyffenegger/development_misc/master/java/swing/JTable/ScrollableTable.java) displays
[this csv file](https://raw.github.com/ReneNyffenegger/development_misc/master/java/swing/JTable/ScrollableTable.java).


--------------

#What is the difference between *swing* and *awt*

[Stackoverflow](http://stackoverflow.com/questions/408820/what-is-the-difference-between-swing-and-awt) says:

**awt** is a Java interface to native system GUI code present in your OS. It will not work the same on every system, although it tries.

**swing** is a more-or-less pure-Java GUI. Using awt it creates an operating system window, and then it paints pictures of buttons, labels, text,
checkboxes, etc., into that window and responds to all of your mouse-clicks, key entries, etc., deciding for itself what to do instead of letting the
operating system handle it. Thus Swing is 100% portable and the same across platforms.
