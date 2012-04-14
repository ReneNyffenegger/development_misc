#  Layout Managers

## BorderLayout

[SimpleBorderLayout.java](https://raw.github.com/ReneNyffenegger/development_misc/master/java/swing/LayoutManagers/BorderLayout/SimpleBorderLayout.java)

## BoxLayout

[SimpleBoxLayout.java](https://raw.github.com/ReneNyffenegger/development_misc/master/java/swing/LayoutManagers/BoxLayout/SimpleBoxLayout.java)

It seems as though *BoxLayout* is the only layout manager (in swing's framework) that pays attention a *JComponent*'s requested maximum size and
a *JComponent*'s alignment hints.

## CardLayout
## FlowLayout

A **FlowLayout** places its component in a row.

The *FlowLayout* is the default layout for a *JPanel*.

## GridBagLayout

[SimpleLoginDialog.java](https://raw.github.com/ReneNyffenegger/development_misc/master/java/swing/LayoutManagers/GridBagLayout/SimpleLoginDialog.java) creates a 
`JDialog` (the class `LoginDialog` which derives from `JDialog`). This dialog adds two `JPanel`s. The *panel* created with `createNamePasswordPanel()`
uses the *GridBagLayout* layout manager in order to align the labels and the text boxes.

## GridLayout

The *GridLayout* forces all components to be the same size.

## GroupLayout
## SpringLayout

-----------


[Problem.java](https://raw.github.com/ReneNyffenegger/development_misc/master/java/swing/LayoutManagers/Problem.java) demonstrates the following "Problem": Although five *JLabels* are added to the *content pane*, only
the last one added is really displayed.
