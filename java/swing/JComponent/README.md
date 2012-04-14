#   JComponent

##  JButton

##  JInternalFrame

Sort of a `JFrame` window within another window.

Usually, *JInternalFrames* are added to a *JDesktopPane*.

[InternalFrames.java](https://raw.github.com/ReneNyffenegger/development_misc/master/java/swing/JComponent/JInternalFrame/InternalFrames.java) creates a *JDesktopPane* and places 16 *JInternalFrame* into it.

##  JLabel

##  JLayeredPane

A *JLayeredPane* handles *JComponents* and gives them a *z-Axis* value. So, JComponents placed into *JLayeredPanes* can be one atop of another.

### JDesktopPane

##  JMenuBar

##  JMenuItem

##  JOptionPane

##  JPanel

A **JPanel** is useful for grouping other *JComponents*, for simplifying their layout and drawing borders around such groups.

##  JScrollBar

##  JTabbedPane

##  JTextComponent

### JEditorPane

A **JEditorPane** can be used to display HTML or RTF.

[GeneratedHTML.java](https://raw.github.com/ReneNyffenegger/development_misc/master/java/swing/JComponent/JTextComponent/JEditorPane/GeneratedHTML.java) generates HTML and displays it.

[HtmlLinks.java](https://raw.github.com/ReneNyffenegger/development_misc/master/java/swing/JComponent/JTextComponent/JEditorPane/HtmlLinks.java) extends *GeneratedHTML.java* in that
it has links that can be clicked.


##  JToggleButton

##  JToolBar

##  JTree

----------

##  Borders

A *JComponenent* can have borders. Usually, borders are only used with *JPanels* and *JLabels*.

Borders themselves are not *JComponent*.

[SimpleBorderOnLabel.java](https://raw.github.com/ReneNyffenegger/development_misc/master/java/swing/JComponent/borders/SimpleBorderOnLabel.java) draws three labels with colored borders. The thickness of
the borders varies.
