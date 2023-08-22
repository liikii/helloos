// void __attribute__((optimize("O0"))) func() {
//    char* string = "Hello";
// }


#pragma GCC push_options
#pragma GCC optimize ("O0")

void func() {
   char* string = "Hello";
}

#pragma GCC pop_options