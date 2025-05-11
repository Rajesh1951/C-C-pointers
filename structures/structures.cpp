1. What is the difference between padding and packing in structures? How do you minimize memory waste?
  // adding refers to the extra memory bytes automatically inserted by the compiler between members of a struct to 
  // ensure that each member is properly aligned in memory according to the platform's alignment requirements 
  // (usually based on the size of the largest data type). This alignment allows the CPU to access data more 
  // efficiently
  struct Base {
    char a;   // 1 byte
    char b;   // 1 byte
    // 2 bytes padding
    int i;    // 4 bytes
    char c;   // 1 byte
    // 3 bytes padding
  };
  // Packing is the process of instructing the compiler to minimize or eliminate padding between members, 
  // typically using #pragma pack(n). For ex., #pragma pack(1) forces the compiler to align members with 1-byte 
  // boundaries, effectively removing padding.
  // to minimize memory waste reorder struct members from large to small
  struct BaseOptimized {
    int i;
    char a;
    char b;
    char c;
  };

2. Given a struct with bitfields, explain how memory alignment works and how it might differ across compilers.
  // Bitfields allow us to specify the exact number of bits allocated for struct or class members, which can 
  // help optimize memory when full-width integers are unnecessary.
  struct Base{
    int a :3;// 3bits
    int b:4; // 4bits
  };
  // We might expect a and b to be packed into 7 bits total. However, bitfield memory layout and alignment are 
  // implementation-defined and vary between compilers.

  // For bitfields:
  // The base type's size and alignment (here int, typically 4 bytes) dictate how bitfields are stored.
  // Many compilers pack multiple bitfields into the same allocation unit until the unit is full or a new alignment boundary is required.
  // Alignment of the struct itself is usually aligned to the base type's alignment (4 bytes in this case), even if only a few bits are used.
  // So even though only 7 bits are specified, sizeof(Base) is often 4 bytes on common compilers (like GCC/Clang on x86), not 1 byte.
  // Compiler differences:
  // Compilers may differ in bit ordering (LSB vs. MSB within a byte or word).
  // They may add padding between bitfields, especially when the base types differ.
  // Some compilers allow packing across bytes; others keep each bitfield aligned to the base type.
  // Because of this variability, bitfields are NOT suitable for portable binary formats or hardware register mappings. In such cases, it's better to manually use masks and shifts.
  // Finally: Bitfields can only be used with integral types (int, unsigned int, char, bool, etc.), and attempting to use floating-point or pointer types in bitfields is illegal.

// How can you force a specific memory alignment for a struct? Write a code example.
  // To force a struct to have a specific memory alignment, we can use the alignas specifier (C++11 and later) 
  // or compiler-specific extensions.
  #include <iostream>
  #include <cstddef>

  struct alignas(16) Base {
      int a;
      char b;
  };

  int main() {
      std::cout << "Alignment of Base: " << alignof(Base) << std::endl;
      std::cout << "Size of Base: " << sizeof(Base) << std::endl;
  }

  // We use force alignment because it might be requirement of hardware, for example if cpu want to load 16 
  // bytes, & the data is aligned in 4 bytes it needs 4-5 reads / it can even crash

// Explain how you’d serialize and deserialize a struct that contains both integers and char arrays.
  // serialize= packing the structure data linearly so it can be stored/sent with minimal memory
  // deserialize = reading the serialized data & bringing back to original state
  // we need this to send data over CAN, storing in DB etc.

  // for example we create a struct, store it in bin file, and read it again.

  struct Mydata{
    int age;
    char name[20];
  };
  void serialize(Mydata &data,ostream &out){
    out.write(reinterpret_cast<char*>(&data.id),sizeof(data.id));
    out.write(data.name,sizeof(data.name));
  }
  Mydata deserialize(istream &inp){
    Mydata data;
    inp.read(reinterpret_cast<char*>(&data.id),sizeof(data.id));
    inp.read(data.name,sizeof(data.name));
  }
  main(){
    Mydata og{24,"king"};
    std::ofstream ofs("data.bin",std::iostream::binary);
    serialize(og,ofs);
    ofs.close();
    std::ifstream ifs("data.bin",std::iostream::binary);
    Mydata deserializedData=deserialize(ifs);
    printf(deserializedData)
  }

// How do you write a portable struct that behaves consistently across different architectures (big vs little endian)?
  // never dump raw structs directly; always manually serialize each member in a defined byte order 
  // and use fixed-width types to guarantee consistency across architectures  

// Can you have a flexible array member in the middle of a struct? Why or why not?  
  // No, a flexible array member must be the last member of a struct. The standard prohibits placing any member 
  // after it because its size is dynamic, and anything after it would make the struct's layout undefined.

  // Note: s
  struct foo{
    int a;
    int b[]; // is a flexible array
  };
  // this flexible array cant be initialized in static memory, foo{1,{1,2}} will throw error. 
  // this struct should be intialized dynamically.

// How do you calculate the size of a struct at compile time vs runtime? Any pitfalls?
  // The size of a struct at compile-time is fully determined by the sizes of its members plus any padding added 
  // due to alignment rules. This is what sizeof() reports and it's a compile-time constant. However, if a struct 
  // contains pointers or flexible array members, the actual memory usage can grow at runtime based on dynamic 
  // allocations. A common pitfall is assuming sizeof includes dynamically allocated memory; in reality, it only 
  // counts the fixed part of the struct.

// What happens if you take the address of a packed struct and cast it to another type? Any dangers?
  // Taking the address of a packed struct and casting it to another type is dangerous because packing disables 
  // padding, which can lead to members being stored at misaligned addresses. Many architectures require certain data 
  // types to be aligned to specific boundaries (e.g., int at 4-byte). If you cast an address that isn't properly 
  // aligned, it may cause hardware faults, undefined behavior, or performance penalties due to unaligned access handling.
  
  struct Packed{
    char a;
    int b;
  };
  Packed p={'A',123};
  int *ptr=(int*)((char*)&p+1);
  // in above line if we want to get address of 'int b', we'll have to move 1 byte(since its packed) therefore 
  // (char*) is required to tell compiler its 1 byte jump. or else it'll jump sizeof(struct)

// What are anonymous structs/unions? Give a code example where it’s useful.
  // Anonymous structs/unions are unnamed aggregates whose members are promoted to the containing scope. It 
  // allows direct access to inner fields without an extra name. They’re useful in embedded programming for 
  // overlapping memory layouts, e.g., hardware register maps where both bitfield and full-word access are needed

  struct {
    int a;
    char b;
  }base;
  // using above way there will be only 1 instance base, there cant be base b2 bcz base is not struct its tag
  
  // Useful real life ex.
  struct foo{
    union{
      struct{
        uint16_t low, high;
      };
      uint32_t full;
    };
  };
  foo a;
  a.full =0xFFFEFFEF;
  cout<<a.high;   //65534
  cout << a.low;  //65519


// Can a struct contain a pointer to its own type? What are the use cases?
  // Yes, a struct can contain a pointer to its own type; this pattern is essential for building recursive data 
  // structures like linked lists, trees, and graphs. We use a pointer instead of a direct object to avoid infinite 
  // size expansion since a pointer is a fixed-size reference

// Write a struct to represent a network packet with variable-length payload. How would you handle memory safely?
  struct Data{
    int id,size;
    int *payload;
  }
  // This could be 1 possible solution but the issue,is pointer payload cant be used copied deeply without 
  // explicitly doing. 
  Data data1 = originalData;   // the payload pointer address got copied, now will have to delete both data1.
  // payload & orignalData.payload (double delete/free)

  // Other method is to use flexible array
  struct Data{
    int id,size;
    int payload[];
  };
  Data *data=new Data()
  data->payload = malloc(size);
  
  // Best way is use vector for payload
  struct Data{
    int id,size;
    vector<int>payload;
  };


// What is the difference between typedef struct and struct with a tag name?
  // The difference is that struct tagname requires using the struct keyword every time you declare a variable 
  // in C, whereas typedef struct creates an alias so you can use the name directly without the struct keyword.
  // In C++, there’s effectively no difference because struct introduces a type name directly.

  typedef struct Mystruct{
    ,,
  }Mystruct;
  // its forward declaration + typedef. Used to avoid struct while declaring objs (typedef) & forward declaration
  // or self referntial pointer

// Explain strict aliasing rules and how they can mess up accessing struct members via type punning.

  // Aliasing = multiple pointers to the same memory
  // Strict aliasing = compiler assumes different types ≠ same memory
  // Type punning = accessing memory as a different type
  // Breaks compiler’s assumptions → leads to undefined behavior

  int a = 0x40490FDB; // bit pattern for 3.141592 (float)

  float f = *(float*)&a;  // type punning
  printf("%f\n", f);      // prints 3.141593
  // type punning is done to read bit representation of diff types. 
  // #define REG (*(volatile uint32_t*)0x40000000)
  // REG = 0x01;
  // above we are considering register memory as diff type
  // And also fast serial & de-serialization

  // What messes up?
    float f=3.14f;
    int *a = (int*)&f;
    *a=0;
    printf("%f",f); // may print 3.14
    /* initially f had a float value, i cleared using 0 via int pointer. Compiler based on strict aliasing 
    rules assumes there will be no writes on float variable/memory since there is no writes using float values
     we have updated using int*. Compiler optimizes & checks the cached float value without reloading & prints
     old value.*/


    /*
    Strict aliasing rules allow the compiler to assume that pointers to different types don’t alias the same 
    memory. When we do type punning — say, accessing a float using an int* — this violates the aliasing rule and 
    can lead to undefined behavior due to compiler optimizations.

    To safely perform type punning, we should use memcpy, unions (in C), or go through char* as it’s exempt from 
    aliasing rules.
    */


// How do structs behave when passed by value vs by reference in a function? Any gotchas?
  // In C, structs are passed by value, meaning a copy is made. To avoid that, you pass a pointer to the struct.

  // In C++, you get actual references — pass by & or const & to avoid unnecessary copies.

  // Gotchas:
  // Large structs passed by value can hurt performance.
  // Modifying value-passed struct inside a function won’t affect the caller.
  // Returning structs by value is okay, but be aware of copy/move semantics in C++

// You have nested structs with both packed and unpacked members. How do you guarantee a fixed binary layout?
  // use pragma for all structs so that both inner & outer are packed & predictable. To match endianess will 
  // have to use htons or htonl or manual bit manipulation. 
  static_assert(sizeof(Outer) == EXPECTED_SIZE, "Struct layout mismatch");
  // for 

// What’s wrong with this: struct A { int x; }; struct A a = { .y = 5 };?
  // The code fails because .y is not a valid member of struct A.
  // Designated initializers require exact member names. Using a non-existent one results in a compile-time error.  

// How does sizeof() behave when applied to a struct with bitfields? Show with code.  