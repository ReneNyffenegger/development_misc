#JFrame

**JFrame** is one of the three generally useful *top level container* classes. The others are `JDialog` and `JApplet`.

[Simplest.java](https://raw.github.com/ReneNyffenegger/development_misc/master/java/swing/JFrame/Simplest.java) has a member whose type is a *JFrame*, initializes it, and makes it visible.

[ClassExtendsJFrame.java](https://raw.github.com/ReneNyffenegger/development_misc/master/java/swing/JFrame/ClassExtendsJFrame.java) is more or less the same as *Simplest.java*, yet, the class
itself derives from a *JFrame*.



---------

## On Top level containers.

Such a *top level container* has **content pane**. This *content pane* contains the visible things of that *top level container*.
The content pane is retrieved with `getContentPane()`. The type of the *content pane* is a `Component` (the default *content pane* is a `JComponent`).

A *top level container* can optionally have a *menu bar*.

`JInternalFrame` seems to be similr to a `JFrame`, yet, it is not a *top level container*.
