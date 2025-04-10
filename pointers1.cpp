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

// 21. What does a `double**` pointer mean? Write a program to demonstrate its usage.
  double pointer is pointer to a pointer variable. it stores address of a pointer variable.

// 22. Implement a function to print a **2D array using double pointers .

  //Note: m[i][j] is equivalent to *(*(m + i) + j)

  int ** my_2d(int r ,int c){
    // C

    //   int ** a=(int**)malloc(sizeof(int*)*r);
    //   for (int i = 0; i < r; i++) {
    //       a[i] = (int*)malloc(sizeof(int) * c);
    //   }

    // Cpp
    int **a = new int*[r];
    for (int i = 0; i < r; i++) {
      a[i]=new int[c];
    }
    return a;
  }
  cout<<a[i][j];
  for (int i = 0; i < rows; i++)
  {
    delete[] a[i];
  }
  delete[] a;

  // 2nd method
  int *my_2d(int r,int c){
    return new int[r*c];
  }
  cout<<a[i*cols+j];

  // 3rd method
  int (*arr)[cols] = new int[rows][cols];
  // here arr is pointer to array of size cols. for ex. (*arr)[3] means arr is pointer to array of 3 elements. arr will store address of first row, but since a pointer variable cant store address of whole array it'll store only address of first element of first row.
  // So why cant we use normal int*? 
    // bcz if pointer is of type array, pointer arithematic will be based on rows, arr+1 is arr + full row(sizeof(int)*cols) (Moves by `sizeof(int[3])`) i.e. *(arr+1)-*(arr) = sizeof(int)*3

  // 4th method
  vector<vector<int>> a= vector<rows,vector<int>(cols)>; 
  
  // 5th method
  //unique pointer builtin in memory lib in cpp 23
  unique_ptr<int>up=make_unique<int>(9);    // basic syntax. creates pointer variable up with value 9

  unique_ptr<int[]>uparr=make_unique<int[]>(5);  //array pointer, creates pointer to array of size 5

  // Extras: shared_ptr & weak_ptr

  //shared_ptr is when ownership can be shared. ownership mean the single address can be stored by multiple variables, referencing, dereferencing & value change can be done which is not possible in unique pointer.

  //weak_pointer : when we use shared pointer we can go into cyclic referencing, a points to b & b points to a. this will lead to memory leak. to avoid this one of pointer is created as weak_ptr.

//  23. How do you dynamically allocate a 3D array using pointers?  m[x][y][z]
  int***m=new int**[x];
  for (int i = 0; i < x; i++)
  {
    m[i]=new int*[y];
  }

  for (int i = 0; i < x; i++)
  {
    for (int j = 0; j < y; j++)
    {
      m[i][j]=new int[z];
    }
  }
  
// 24. Given `int **ptr;`, what is the correct way to allocate memory for an `m x n` matrix?

  int **ptr =new int*[m];
  for (int i = 0; i < m; i++)
  {
    ptr[i]=new int[n];
  }
  for (int i = 0; i < m; i++)
  {
    delete[] ptr[i];
  }
  delete ptr;

// 25. Write a program to demonstrate pointer dereferencing in `int ***ptr`.  
  int a=1,*p,**q,***r;
  p=&a;
  q=&p;
  r=&q;

// 26. 
// int x = 10, y = 20;
// int *ptr1 = &x, *ptr2 = &y;
// int **pp = &ptr1;
// *pp = ptr2;
// printf("%d", **pp);  

  20 is o/p

// 27. Write a function to **swap two rows of a dynamically allocated 2D array**.
  void swapRow(int** mat,int r1,int r2){
    int *temp=mat[r1];
    mat[r1]=mat[r2];
    mat[r2]=temp;
  } 
  //the parameter (int** mat) can be (int* mat[]) but cant be (int mat[][])
  // both int**mat & int* mat[] represent pointer to pointer to int
  // if we use int mat[][] we shd be telling the compiler about the number of columns, bcz for 2nd/next row it will allocate memory after reserving for 1st complete row. And this process happens in compile time so 2D array should be static memory. In dynamic memory its not possible.

// 28. Implement `void update(int **ptr)` to update the integer value stored at `ptr`.
  void update(int **p){
    **p=34;
  }  

// 29. Write a function that returns a pointer to an array **allocated inside the function**.
  int*  new_arr(int n){
    return new int[n];
  }  
  // dynamic memory allocation stays even after a function is out of scope, so the memory can be used/modified using pointer to that same address.
  //Note: using this method we can use local variable 

// 30. Write a function that prints elements of a jagged 2D array using `int**`.
  int **jagged(){
    int **m=new int*[3];
    for (int i = 0; i < 3; i++) {
        m[i]=new int[i+1];
    }
  }

// 31. What is a function pointer? Write a program to use it.
  // A function pointer is a pointer that points to a function instead of a data value.
  // It allows you to call functions dynamically, pass them as arguments, or store them in arrays for selection at runtime
  
  return_type (*operator)(parameters data type);  //syntax for function pointer
  
  // void functions:
  void gm(){
    cout<<"g m"<<'\n';
  }
  void gn(){
      cout<<"g n"<<'\n';
  }
  int main()
  {
      void (*func)(void);
      func=gm;
      func();
      func = gn;
      func();
      return 0;
  }

  // return type with parameters
  int add(int x,int y){
    return x+y;
  }
  int sub(int x,int y){
    return x-y;
  }
  int main()
  {
    int (*func)(int,int)=add;
    cout<<func(2,5);
    func=sub;
    cout<<func(5,89);
    return 0;
  }

  //Does function have memory?-Yes address to set of instructions but its not object/instance
  //why do we wrap *func with parenthesis? int *func(int,int) becomes declaration of function returning int*, so int (*func)(int,int) is telling func is pointer to functions.
  // why * inside ()? int*(func)(int) becomes int* func(int) function returning int* not function pointer.
  // why func=add will work? bcz of function decay. add==&add. & is not required.
  // why *func() is not used to call? *func(5) is interpreted as *(func(5)) i.e. trying to dereference the return value of func. So we'll have to use (*func)(5) this is dereferencing the func and then calling with argument. Again compiler interprets  func(5) as (*func)(5).

  int* pointer(){
    int *a = new int;
    *a=78;
    return a;
  }
  int main()
  {
    int* (*fun)(void)=pointer;
    cout<<func(); //address of a;
    cout<<*fun(); //78 value of a
  }

  //the above code is function pointer to a function returning int pointer.

// 32. Implement a function pointer array that maps different operations (add, subtract, multiply, divide).

  // Operation functions
  int add(int a, int b)      { return a + b; }
  int subtract(int a, int b) { return a - b; }
  int multiply(int a, int b) { return a * b; }
  int divide(int a, int b)   { return b != 0 ? a / b : 0; }  // Basic zero check

  int main() {
    // Array of function pointers
    int (*operations[])(int, int) = { add, subtract, multiply, divide };
    int a = 20, b = 5;
    int choice;
    cin >> choice;
    cout<< operations[choice](a, b);  // Call selected operation
    return 0;
  }

// 33. Write a function that accepts a function pointer as a callback.
  void big(int x,int y,int(*callback)(int,int)){
    cout<<callback(x,y);
  }
  int main()
  {
    big(2,3,sub);
    return 0;
  }

// 34. Write a C program to sort an array using a **custom comparator function** with function pointers.
  bool ascend(int x,int y){
    return x>y;
  }
  bool descend(int x,int y){
    return x<y;
  }
  void sort(int a[],bool(*callb)(int,int)){
    for (int i = 0; i < 5-1; i++) {
      for (int j = 0; j < 5-i-1; j++) {
        if(callb(a[j],a[j+1])){
          int t=a[j+1];
          a[j+1]=a[j];
          a[j]=t;
        }
      }
    }
  }
  int main()
  {
    int a[5]={3,2,5,1,4};
    sort(a,ascend);
    for (auto i : a) 
      cout<<i<<' ';   // 1 2 3 4 5
    
    sort(a,descend);
    for (auto i : a) 
      cout<<i<<' ';   // 5 4 3 2 1
    
    return 0;
  }

// 35. Implement a function pointer that returns a pointer to another function.
  using funcptr = int(*)(int,int); or typedef int (*funcptr)(int,int)
  funcptr decide1(const char* str){
    if(str=="add")
        return add;
    return sub;
  }

  int (*decide(const char*str))(int,int){
    if(str=="add"){
        return add;
    }
    return sub;
  }
  int main()
  {
    int (*opr)(int,int)=decide("addj");
    cout<<opr(3,2);
    return 0;
  }

// 36. Explain and demonstrate `void (*signal(int, void (*)(int)))(int)`.
  void printN(int n){
    cout<<"n is "<<n<<'\n';
  }
  void printM(int n){
    cout<<"m is "<<n<<'\n';
  }
  void (*signalf(int i, void (*callback)(int)))(int){
    callback(i);
    return i&1?printN:printM;
  }
  int main()
  {
    void (*signalo)(int)=signalf(1,printM);
    signalo(3);
    signalo = signalf(2,printN);
    signalo(4);
    return 0;
  }  
  /*output*/
  /*
  m is 1
  n is 3
  n is 2
  m is 4
  */

// 37. Write a function that takes a function pointer as an argument and calls it asynchronously using `pthread`.
// 38. Explain how function pointers are used in **virtual tables** in C.
// 39. How can function pointers be used to implement a **state machine**?

// 40. Implement a **function pointer inside a structure** and use it.
  struct emp{
    int i;
    int (*op)(int,int);
    void assg(int (*callb)(int,int)){
      op=callb;
    }
  };
  int main()
  {
    emp Emp;
    Emp.i=45;
    Emp.assg(add);
    Emp.op=sub;
    cout<<Emp.op(4,5);
    return 0;
  }

// 41. Implement a function that **returns a pointer to a dynamically allocated struct**.
  struct emp{
    int i;
    int (*op)(int,int);
    void assg(int (*callb)(int,int)){
        op=callb;
    }
  };
  emp* eall(){
    emp* pemp=new emp;
    return pemp;
  }
  int main()
  {
    emp* Emp=eall();
    Emp->i=45;
    Emp->assg(add);
    // Emp->op=sub;
    cout<<Emp->op(4,5);
    return 0;
  }

// 42. Write a function that swaps two struct variables using pointers.

  struct Person {
    char name[50];
    int age;
  };

  void swapPersons(Person* a, Person* b) {  //deep copy
    Person temp;
    strcpy(temp.name, a->name);
    temp.age = a->age;
    strcpy(a->name, b->name);
    a->age = b->age;
    strcpy(b->name, temp.name);
    b->age = temp.age;
  }

  void main(){
    Person a,b;
    swapPersons(&a,&b);
  }

// 43. Implement a function to traverse a linked list using pointers.  
  struct Node{
    int v;
    Node *next;
  };
  void main()
  {
      Node *head=new Node{1,new Node},*p=head;
      head->next=new Node{2,new Node};
      head->next->next=new Node{3,nullptr};
      while(p){
          cout<<p->v<<' ';
          p=p->next;
      }
  }

// 44. Write a function that reverses a **linked list using pointers only**.
  Node* reverse(Node *head){
    Node *prev=nullptr,*nxt=head;
    while(head){
        nxt=head->next;
        head->next=prev;
        prev=head;
        head=nxt;
    }
    return prev;
  }

// 45. Implement a function that **deep copies a structure** containing pointers.
  struct emp{
    int i,*p;
    int (*op)(int,int);
    void assg(int (*callb)(int,int)){
        op=callb;
    }
  };
  void dcopy(emp *x,emp *y){
    emp *t;
    t->i=x->i;
    t->p=x->p;
    t->op=x->op;
    
    x->i=y->i;
    x->p=y->p;
    x->op=y->op;
    
    y->i=t->i;
    y->p=t->p;
    y->op=t->op;
    
  }
  int main()
  {
    int a=9,b=6;
    emp emp1=emp{12,&a,add},emp2=emp{35,&b,sub};
    cout<<emp1.i<<' ';
    cout<<emp1.p<<' ';
    cout<<emp1.op(2,3)<<'\n';
    cout<<emp2.i<<' ';
    cout<<emp2.p<<' ';
    cout<<emp2.op(2,3)<<'\n';
    dcopy(&emp1,&emp2);
    cout<<emp1.i<<' ';
    cout<<emp1.p<<' ';
    cout<<emp1.op(2,3)<<'\n';
    cout<<emp2.i<<' ';
    cout<<emp2.p<<' ';
    cout<<emp2.op(2,3)<<'\n';
    return 0;
  }
  
  // 46. Write a program that creates and manipulates a **structure containing an array of pointers**.
  struct emp{
    int i,*p;
    int (*op)(int,int);
    void assg(int (*callb)(int,int)){
        op=callb;
    }
    int *pa[3];
  };
  int main()
  {
    int a=4,b=9,c=5;
    emp* emp1=new emp;
    emp1->pa[0]=&a;
    emp1->pa[1]=&b;
    emp1->pa[2]=&c;
    cout<<*(emp1->pa[2])<<' '<<emp1->pa[2]<<' '<<&c;
    return 0;
  }  

// 47. Given the following struct, print the name without using the dot (`.`) operator:
// ```c
// struct Student {
//     char name[20];
//     int age;
// };
// ```
  main(){
    Student *s1=new Student{"rajs",12};
    cout<<s1->name;
  }

// 48. Write a function that sorts an array of structs based on a given field using **qsort**.
  bool ascend(int x,int y){
    return x>y;
  }
  bool descend(int x,int y){
    return x<y;
  }
  struct Student {
    int age,marks,height;
  };
  void sort(Student a[], int n, bool (*callb)(int, int))
  {
    for (int i = 0; i < n - 1; i++)
    {
      for (int j = 0; j < n - i - 1; j++)
      {
        if (callb(a[j].marks, a[j + 1].marks))
        {
          Student t = a[j + 1];
          a[j + 1] = a[j];
          a[j] = t;
        }
      }
    }
  }

  int main()
  {
    Student *s1=new Student[3];
    s1[0]=Student{12,2,999};
    s1[1]=Student{13,1,99};
    s1[2]=Student{14,3,9};
    sort(s1,3,descend);
    for (int i = 0; i < 3; i++) {
        cout<<s1[i].age<<' '<<s1[i].marks<<' '<<s1[i].height<<'\n';
    }
    return 0;
  }

// 49. Implement a function to insert a node in a **linked list** using pointers.  
  void insert(Node* head,int v){
    Node * n=new Node(v),*t;
    t=head->next;
    head->next=n;
    n->next=t;
  }

// 50. Implement a **self-referential structure** using pointers.
  //A self-referential structure is a structure that contains a pointer to another instance of the same structure. It's the core of data structures like linked lists, trees, graphs, etc.



