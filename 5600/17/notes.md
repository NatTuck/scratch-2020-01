

# Why Rust?

## Data Races

Conditions:

 - Concurrent execution
 - Shared data
 - At least one writer

Rust says that shared data can't be mutable.

Rust provides mutexes, which allow multiple threads to share and mutate data,
but mutexes naturally prevent concurrency.

## Modern Systems Programming

 - C++ has some nice features: 
   - Generics with templates
   - OO stuff like Methods
     - instance.method()
   - The whole RAII model, where you initialize in a constructor
     and cleanup in a deterministic destructor
 - But C++ has some issues:
   - You still frequently use new/delete (= malloc/free) for memory management,
     and can do stuff like double free.
   - Every pointer use might be a buffer overflow.
   - It doesn't enforce rules that could help with issues like data races.
 - Rust is basically an attempt to do C++ right, keeping the good parts and
   replacing the parts that the Rust developers don't like.

