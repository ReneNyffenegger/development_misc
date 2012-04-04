declare
  status number;
begin
            dbms_pipe.pack_message('hello world');
  status := dbms_pipe.send_message('queue_name');
end;
/
