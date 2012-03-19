#include <windows.h>

/*
  g++ -DDO_TRACE -mwindows -Wall Tracer.cpp TestTracer.cpp -oTestTracer.exe
*/

#include "Tracer.h"

void aaa(int);
void bbb(int);

void ccc(int i) {
  TraceFunc("ccc");
  Trace2("i: ", i);
  if (i > 8) {
    Trace2("going to call aaa with ", i/2);
    aaa(i/2);
  }
  else {
    Trace("going to call bbb with 6");
    bbb(6);
  }
}

void bbb(int i) {
  TraceFunc("bbb");
  Trace2("i: ", i);
  if (i > 10) {
    ccc(i/3);
  }
  else {
    aaa(i/2);
  }
  ccc(10);
}

void aaa(int i) {
  TraceFunc("aaa");
  Trace2("i: ", i);
  if (i > 5) {
    Trace("i > 5, going to call bbb");
    bbb(i/2);
  }
  else {
    Trace("i <= 5, not going to call bbb");
  }
}

int main() {
  StartTrace("Trace.out");
  TraceFunc("main");
  aaa(50);
  return 0;
}
