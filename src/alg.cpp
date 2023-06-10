// Copyright 2021 NNTU-CS

#include <string>
#include <map>
#include <math.h>
#include "tstack.h"

std::string infx2pstfx(std::string inf) {
TStack <char, 100> stack1;
  std::string Nums = "0123456789";
  std::string StringOfOperates = "()+-*/";
  std::string OutString;
  std::string NewString;
  std::string temple;
  NewString = '(' + inf + ')';
  for (int i = 0; i < NewString.size(); ++i) {
    if (search(Nums, NewString[i])) {
      if (0 == temple.size())
        temple.push_back(NewString[i]);
      else if (search(Nums, NewString[i - 1]))
        temple.push_back(NewString[i]);
      if (i < NewString.size() - 1 && !(search(Nums, NewString[i + 1]))) {
        OutString += temple;
        OutString.push_back(' ');
        temple = "";
      }
    }
    if (search(StringOfOperates, NewString[i])) {
      if (((stack1.isEmpty()) ||
            0 == priority(NewString[i])) ||
           (priority(NewString[i]) > priority(stack1.get()))) {
              stack1.push(NewString[i]);
    } else {
        while (priority(stack1.get()) >= priority(NewString[i])) {
          OutString.push_back(stack1.get());
          OutString.push_back(' ');
          stack1.pop();
        }
        if (')' != NewString[i])
          stack1.push(NewString[i]);
        else
          stack1.pop();
       }
    }
    if (i == NewString.size() - 1 && !(stack1.isEmpty())) {
      while (!(stack1.isEmpty())) {
        if (i != NewString.size() && stack1.get() != '(') {
          OutString.push_back(' ');
          OutString.push_back(stack1.get());
        }
        stack1.pop();
      }
    }
  }
  if (' ' == OutString[OutString.size() - 1])
    OutString.resize(OutString.size() - 1);
  return OutString;
}

int eval(std::string pref) {
TStack <int, 100> stack2;
  int x = 0;
  int y = 0;
  std::string temple;
  for (int i = 0; i < pref.size(); ++i) {
    std::string Nums = "0123456789";
    std::string StringOfOperates = "+-*/";
    if (search(Nums, pref[i])) {
      int num = 0;
      if (0 == temple.size())
        temple.push_back(pref[i]);
      else if (search(Nums, pref[i - 1]))
        temple.push_back(pref[i]);
      if (i < pref.size() && !(search(Nums, pref[i + 1]))) {
        num = convertToInt(temple);
        stack2.push(num);
        temple = "";
      }
    } else if (search(StringOfOperates, pref[i])) {
        y = stack2.get();
        stack2.pop();
        x = stack2.get();
        stack2.pop();
        int res = Calculator(x, pref[i], y);
        stack2.push(res);
      }
  }
  return stack2.get();
}
