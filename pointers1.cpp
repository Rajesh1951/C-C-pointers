// 1. What happens if you dereference a NULL pointer? Write a program to demonstrate it.

  // dereferencing NULL pointer can lead to undefined behaviour;
  // The program may crash or cause a segmentation fault (SIGSEGV) because we are trying to access memory at address 0x0, which is not valid.
  int *p=NULL;
  cout<< *p;  // undefined behaviour

// 2. Given `int a[5] = {1, 2, 3, 4, 5};`, write code to access the third element using pointer arithmetic.
  cout<< a+2;

// 3. Implement a function that swaps two integers using only pointers (without using a temporary variable).
  // C
  void swap(int *p,int *q){
    *p = *p+*q;
    *q=*p-*q;
    *p = *p-*q;
  }
  int main()
  {
    int a=2,b=-3;
    swap(&a,&b);
  }
  // Cpp
  void swap(int &p,int &q){
    p = p+q;
    q=p-q;
    p = p-q;
  }
  swap(a,b);

// 4. Write a function to reverse an array **in-place** using pointers.
  while(i<j){
    swap(*(ar+ i++),*(ar + j--));
  }

// 5. Explain and write a program to demonstrate **pointer decay**.
  int a[5] = {1, 2, 3, 4, 5};
  cout<<a[1]<<*(a+1);

// 6. what will happen?
//   int arr[] = {10, 20, 30};
//  int *p = arr;
//  printf("%d", *(p++));
  // o/p: 10

// 7. Given `int arr[5]`, print the address difference between `arr` and `arr+1`. Why is there a difference?

  cout<<(char*)(arr+1) - (char*)arr;  //4 size of 1 integer

// 8. Write a program that prints the **size of a pointer** to different data types (`char*`, `int*`, `float*`).

  sizeof(char*),sizeof(int*)...
  // sizeof of every pointer variables is 8 bcz the hex address is same for all 

// 9. Explain the difference between `const int *ptr`, `int *const ptr`, and `const int *const ptr`.  
  // const int *ptr = pointer to constant int type. address held by *ptr can be changed, but value of that address cant be changed.
  // int *const ptr = constant pointer of int type address cant be changed, value of address can be changed
  // const int *const ptr = constant pointer to const int. no address & vallue change

// 10. Why does `sizeof(ptr)` not return the size of the memory allocated for the pointer?
  // ptr is variable used to store address, address of all memory type is of same size 8 bytes

// 11. Write a function that dynamically allocates memory for an array and initializes it with values.
  int *ptr = new malloc(5);
  for(int i=0;i<5;i++){
    ptr[i]=1;
  }

// 12. Implement a function that reallocates an array (similar to `realloc`) without using `realloc`.
  void * my_realloc(void *old_ptr,int n){
    if(old_ptr==nullptr){
      return (void*) malloc(n);
    }
    if(n==0){
      return (void*)0;
    }
    void *new_ptr=(void*) malloc(n);
    memcpy(new_ptr,old_ptr,n);
    free(old_ptr);
    return new_ptr;
  }  

  p=(int*)my_realloc(p,5*sizeof(int));

// 13. Write a function to free a dynamically allocated 2D array.  

  int **ptr=(int**)malloc(3*sizeof(int*)),c=1;
  for (int i = 0; i < 3; i++) {
      ptr[i]=(int*)malloc(3*sizeof(int));
  }
  for (int i = 0; i < 3;  i++) {
      for (int j = 0; j < 3; j++) {
          ptr[i][j]=c++;
      }
  }
  for (int i = 0; i < 3;  i++) {
      // cout<<ptr+i<<'\n';
      for (int j = 0; j < 3; j++) {
          // cout<<i<<' '<<ptr[i]+j<<'\n';
          cout<<ptr[i]+j<<' ';
      }
      cout<<'\n';
  }

// 14. What happens if you try to access memory after calling `free()`?

  undefined behaviour. returns junk value/segmentation fault/temporarily previous value

// 15. Write a program that causes a **memory leak** and then fixes it.
  memory leak is when memory is allocated dynamically & not freed. it stays allocated forever since it wont get destroyed after the scope of functions completes like we see in static allocated memory.

// 16. Implement a function that duplicates a string **without using `strcpy` or `strdup`**.
  char* my_strcpy(char* str,int n){
    char *new_ptr=(char*)malloc(n);
    for (int i = 0; i < n; i++) {
        new_ptr[i]=str[i];
    }
    return new_ptr;
  }  

  | Declaration                  | Modifiable? | Safe?      
  |------------                  |-------------|-------     
  | `char* str = "hello";`       | ❌ No       | ❌ Unsafe (deprecated in C++) |
  | `const char* str = "hello";` | ❌ No       | ✅ Safe, recommended |
  | `char str[] = "hello";`      | ✅ Yes      | ✅ Safe if modification is needed |
  |`char* str = (char*)malloc(6);| ✅ Yes      | ✅ Needs `free(str);` |
    strcpy(str, "hello");

// 17. Write a function that correctly resizes a dynamically allocated array.

  just write my_realloc function & copying old data should be done manually.

// 18. Explain the issue with `char *str = "hello";` and how to fix it.

  string literal in cpp/c is read-only data. In C we can modify the elements of it but the result is undefined 
  so if we are assigning the string literal we should use const char *str="hell" so we cant modify the string.
  if we need to modify the string we can store the string in modifiable memory char str[]="hell"
  when dynamic mem:
  char *s=(char*)malloc(n);
  strcpy(s,"hell")

//  19. Write a program to check if a pointer is **dangling**.

  dangling pointer are of types 
  1. pointing to freed memory (after free(ptr))
  free(ptr);
  if(ptr!=NULL){
    // POINTER IS DANGLING
  }
  ptr = NULL;   //point it to NULL
  2. pointing to memory for which scope is destroyed
  int *func(){
    int x;
    return &x;
  }
  main(){
    *p=func();  //pointing to address of x whose scope is destroyed
  }
  Here we can use static variable instead of local variable in function bcz static variables will not be 
  destroyed even if function scope has ended

// 20. Implement your own `calloc()` using `malloc()`.  
  calloc & malloc are same, they both allocate continous memory, but calloc will intialize memory with 0
  To answer this Q, just allocate using malloc, intialize with 0 using memset from <string.h> or manually

