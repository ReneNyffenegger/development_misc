# JTable

## ScrollableTable.java

[ScrollableTable.java](https://raw.github.com/ReneNyffenegger/development_misc/master/java/swing/JTable/ScrollableTable.java) places a `JTable` onto a `JScrollPane` so that the table's content can be scrolled.

The data displayed is read from [data.csv](https://raw.github.com/ReneNyffenegger/development_misc/master/java/swing/JTable/data.csv).

## SimpleAbstractTableModel.java

[SimpleAbstractTableModel.java](https://raw.github.com/ReneNyffenegger/development_misc/master/java/swing/JTable/SimpleAbstractTableModel.java) uses the `AbstractTableModel` interface to pass the table's data to the JTable.

## DoesJTableCache.java

[DoesJTableCache.java](https://raw.github.com/ReneNyffenegger/development_misc/master/java/swing/JTable/DoesJTableCache.java) is a table with one million rows (and one column). 
The method `getValueAt` returns the *then* current time as a string. Thus, it can be seen that JTable does not cache the values but retrieves them whenever needed.
