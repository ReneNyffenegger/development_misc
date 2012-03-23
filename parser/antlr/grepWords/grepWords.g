grammar grepWords;

words: word+;

word: WORD {System.out.println($WORD.text);};

WORD: ('a'..'z'|'A'..'Z')+ ;
WS  : (' '|'\t'|'\n')+ {skip();} ;
