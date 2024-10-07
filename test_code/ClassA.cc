#include "ClassA.hh"
#include "ClassB.hh"

void ClassA::callB() {
  auto bInstance = ClassB();
  bool hello = true;
  bInstance.method1();
  if (hello)
    {
      interMethod1();
      hello = false;
    }
  if (hello)
    {
      interMethod2();
    }

  for (int i = 0; i < 100; i++)
    {
      bInstance.method1();
    }

  int i = 0;

  while (hello && (i < 10))
    {
      interMethod1();
      bInstance.method1();
      i++;
    }
}

void ClassA::interMethod1() {
  bool inter1 = false;
  if (inter1)
    {
      //  do nothing
    }
}

void ClassA::interMethod2() {
  bool inter2 = true;
  if (inter2)
    {
      // do nothing
    }
}
