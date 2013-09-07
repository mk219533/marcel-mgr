#include <cstdio>
#include <cstring>

struct base {
  virtual void call() = 0;
};

struct derived : public base {
  public:
    virtual void call() {
      printf("myclass::call()\n");
    }
};

void do_call(base *obj) {
  obj->call();
}

int main(int argc, char *argv[]) {
  base *obj = new derived, *ptr;
  ptr = obj;
  delete obj;
  char *buffer = new char[100];
  strncpy(buffer, argv[1], 100);
  do_call(ptr);

  delete[] buffer;
  

}
