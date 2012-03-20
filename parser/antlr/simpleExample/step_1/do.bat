@rem 
@rem Be sure to have %CLASSPATH% set so that
@rem it points to antlr-3.3-complete.jar

@set CLASSPATH=.;c:\Users\tq84\Downloads\antlr-3.3-complete.jar

@rem --------------------------
@rem The following line creates:
@rem 
@rem     o ExpParser.java
@rem     o Exp.tokens
@rem     o ExpLexer.java
@rem

     java org.antlr.Tool Exp.g

@rem --------------------------
@rem Use the Test Class

     javac ANTLRDemo.java 

     java -cp %CLASSPATH% ANTLRDemo

