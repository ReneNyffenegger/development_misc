create or replace function perl_refcursor_func(p_a in number) 
  return sys_refcursor 
as
  ret sys_refcursor;
begin
  open ret for 
    select * from perl_refcursor_tab
     where a > p_a;

  return ret;
end perl_refcursor_func;
/
