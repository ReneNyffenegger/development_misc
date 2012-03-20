@rem 
@rem Be sure to have %CLASSPATH% set so that
@rem it points to antlr-3.3-complete.jar

@rem --------------------------
@rem The following line creates:
@rem 
@rem     o ExpParser.java
@rem     o Exp.tokens
@rem     o ExpLexer.java
@rem

     java -cp .;%CLASSPATH% org.antlr.Tool Exp.g

@rem --------------------------
@rem Use the Test Class

     javac -cp .;%CLASSPATH% ANTLRDemo.java 

     java  -cp .;%CLASSPATH% ANTLRDemo

