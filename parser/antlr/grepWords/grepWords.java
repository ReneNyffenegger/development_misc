import org.antlr.runtime.*;

public class grepWords {

    public static void main(String[] args) throws Exception {

        ANTLRStringStream in     = new ANTLRStringStream("foo bar baz  what   ever");
        grepWordsLexer    lexer  = new grepWordsLexer(in);
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        grepWordsParser   parser = new grepWordsParser(tokens);

        parser.words();
    }
}
