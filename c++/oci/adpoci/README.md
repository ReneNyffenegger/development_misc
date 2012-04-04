##cygwin

A constant frustration with cygwin are whitespaces in filenames. The following 
commands seemed to help setting ORACLE_HOME to a path containing whitespaces (`Program Files`).

    mkdir /programfiles
    mount -f "/cygdrive/c/Program Files/" /programfiles
    export ORACLE_HOME=/programfiles/....
