When running the examples, be sure to have **oci.dll** added in the `PATH` variable:

    SET PATH=%ORACLE_HOME%/bin;%PATH%

#read_pipe.exe

Execute read_pipe:

    read_pipe.exe username/password@DB queue_name

then write into a pipe with [PL/SQL](https://raw.github.com/ReneNyffenegger/development_misc/master/c++/oci/adpoci/test/write_into_pipe.sql).

See also http://www.adp-gmbh.ch/ora/misc/oci/adpoci/read_pipe.html
