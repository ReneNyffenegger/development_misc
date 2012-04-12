# ConnectionCreator.java

[ConnectionCreator.java](https://raw.github.com/ReneNyffenegger/development_misc/master/java/sql/oracle/ConnectionCreator.java) is a class that specifically supports creating an *Oracle database connection*.

It's `Do` method returns this Oracle connection. It takes 5 parameters: Username, password, hostname, dbport and dbname.

The following java classes all use this ConnectionCreator class.

# CreateTable.java

[CreateTable.java](https://raw.github.com/ReneNyffenegger/development_misc/master/java/sql/oracle/CreateTable.java) creates a table with the `Statment.executeUpdate()` method.

# InsertTable.java

[InsertTable.java](https://raw.github.com/ReneNyffenegger/development_misc/master/java/sql/oracle/InsertTable.java) prepares an *sql insert statement* and uses `PreparedStatement.setString`,
`.setInt` and `.setTimestamp` to *bind* values and fills a few record into the previously created table.

# SelectTable.java

[SelectTable.java](https://raw.github.com/ReneNyffenegger/development_misc/master/java/sql/oracle/SelectTable.java) selects some of the values inserted according to a *where condition*.

# MetaData.java

[MetaData.java](https://raw.github.com/ReneNyffenegger/development_misc/master/java/sql/oracle/MetaData.java) uses `ResultSetMetaData` to determine the count of columns, their respective names
and column types.

# DropTable.java

[DropTable.java](https://raw.github.com/ReneNyffenegger/development_misc/master/java/sql/oracle/DropTable.java) finally drops the table.
