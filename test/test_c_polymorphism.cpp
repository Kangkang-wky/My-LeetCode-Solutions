#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// C++中多态实现是基于虚函数表实现的，每个具备多态性对象的内部都会有一个隐藏的虚函数表，在对象的内存中会有一个指针指向这个虚函数表
// 虚函数表里面的函数指针指向具体的函数实现，可能是父类中的实现，或是子类重写了的方法。
// C语言没有天然的多态支持，但是按照C++的实现原理，也能写出多态特性的代码。

// 下面代码就是用C实现多态。结构体Animal中有两个函数指针，eat和drink。
// Cat结构体通过组合的方式包含Animal对象，此时，Cat结构体也间接获得了eat和drink方法，通过Cat结构体实现原本Animal里面的方法。
// 创建一个Cat结构体指针，将该Cat结构体指针强转成Animal类型的指针，就可以直接调用Animal对象中的方法。

typedef struct Animal {
  void (*eat)(void *this_ptr); // 包了两个函数指针
  void (*drink)(void *this_ptr);
} Animal;

typedef struct Cat {
  Animal base; // Cat has Animal 方式
  char name[16];
  void (*say)(void *this_ptr);
} Cat;

void Say(void *this_ptr) {
  assert(this_ptr);
  Cat *cat = (Cat *)this_ptr;
  printf("I am %s\n", cat->name);
}

void CatEat(void *this_ptr) {
  assert(this_ptr);
  Cat *cat = (Cat *)this_ptr;
  cat->say(cat);

  printf("I am eating.\n");
}

void CatDrink(void *this_ptr) {
  assert(this_ptr);
  Cat *cat = (Cat *)this_ptr;
  cat->say(cat);

  printf("I am drinking.\n");
}

Cat *CatConstruct() {
  Cat *cat = reinterpret_cast<Cat *>(1, sizeof(Cat));
  strcpy(cat->name, "cat");
  cat->say = Say;

  // 这里有点像虚函数表
  // 重写的 base->drink 与 base->eat
  cat->base.drink = CatDrink;
  cat->base.eat = CatEat;
  return cat;
}

int main() {
  Animal *animal = (Animal *)CatConstruct();

  animal->eat(animal);
  animal->drink(animal);
  free(animal);
  return 0;
}
