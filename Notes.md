# C++ high performance

## Chapter 1: A brief introduction to C++

In this chapter, I have highlighted some features and drawbacks of C++ and how
it has evolved to the state it is in today. Further, we discussed the advantages and disadvantages of C++ compared with other languages, both from the perspective of performance and robustness.
In the next chapter, we will explore some modern and essential C++ features that have had a major impact on how the language has developed.

## Chapter 2: Essential C++ techniques

In this chapter, you have learned how to use modern C++ features that will be used throughout this book. Automatic type deduction, move semantics, and lambda expressions are fundamental techniques that every C++ programmer needs to feel comfortable with today.
We also spent some time looking at error handling and how to think about bugs, along with valid states and how to recover from runtime errors. Error handling is an extremely important part of programming that is easily overlooked. Thinking about contracts between callers and callees is a way to make your code correct and avoid unnecessary defensive checks in the released version of your program.
In the next chapter, we will look into strategies for analyzing and measuring performance in C++.

## Chapter 3: Analyzing and measuring performance

In this chapter, you learned how to compare the efficiency of algorithms by using big O notation. You now know that the C++ standard library provides complexity guarantees for algorithms and data structures. All standard library algorithms specify their worst-case or average-case performance guarantees, whereas containers and iterators specify amortized or exact complexity.
You also discovered how to quantify software performance by measuring latency and throughput.
Lastly, you learned how to detect hot spots in your code by using CPU profilers and how to perform microbenchmarkings to improve isolated parts of your program.
In the next chapter, you will find out how to use data structures provided by the C++ standard library efficiently.

## Chapter 4: Data structures

In this chapter, the container types from the standard library were introduced. You learned that the way we structure data has a big impact on how efficiently we can perform certain operations on a collection of objects. The asymptotic complexity specifications of the standard library containers are key factors to consider when choosing among the different data structures.
In addition, you learned how the cache hierarchy in modern processors impacts the way we need to organize data for efficient access to memory. The importance of utilizing the cache levels efficiently cannot be stressed enough. This is one of the reasons why containers that keep their elements contiguously in memory have become the most used, such as std::vector and std::string.
In the next chapter, we will look at how we can use iterators and algorithms to operate on containers efficiently.

## Chapter 5: Algorithms

In this chapter, you learned how to use the basic concepts in the Algorithm library, the advantages of using them as building blocks instead of handwritten for-loops, and why using the standard Algorithm library is beneficial for optimizing your code at a later stage. We also discussed the guarantees and trade-offs of the standard algorithms, meaning that you can, from now on, use them with confidence.
By using the advantages of the algorithms instead of manual for-loops, your code base is well prepared for the parallelization techniques that will be discussed in the coming chapters of this book. One key feature that the standard algorithms are missing is the possibility to compose algorithms, something that was highlighted when we tried to avoid unnecessary container copies. In the next chapter, you will learn how to use views from the C++ Ranges library to overcome this limitation of standard algorithms.

## Chapter 6: Ranges and views

This chapter presented a number of motivations behind using Range views to construct algorithms. By using views, we can compose algorithms efficiently, and with a succinct syntax, using the pipe operator. You also learned what it means for a class to be a view and how to use range adaptors that turn ranges into views.
A view does not own its elements. Constructing a range view is required to be a constant time operation and all views are evaluated lazily. You have seen examples of how we can convert a container into a view, and how to materialize a view back into an owning container.
Finally, we covered a brief overview of the views that come with the standard library, and the likely future of ranges in C++.
This chapter is the last in the series about containers, iterators, algorithms, and ranges. We will now move on to memory management in C++.

## Chapter 7: Memory management

This chapter has covered a lot of ground, starting with the basics of virtual memory and finally implementing a custom allocator that can be used by containers from the standard library. A good understanding of how your program uses memory is important. Overuse of dynamic memory can be a performance bottleneck that you might need to optimize away.
Before you start implementing your own containers or custom memory allocators, bear in mind that many people before you have probably had very similar memory issues to the ones you may face. So, there is a good chance that the right tool for you is already out there in a library. Building custom memory managers that are fast, safe, and robust is a challenge.
In the next chapter, you will learn how to benefit from the newly introduced feature of C++ concepts, and how we can use template metaprogramming to have the compiler generate code for us.

## Chapter 8: Compile-time programming

In this chapter, you have learned how to use metaprogramming to generate functions and values at compile time instead of runtime. You also discovered how to do this in a modern C++ way by using templates, the constexpr, static_assert(), and if constexpr, type traits, and concepts. Moreover, with constant string hashing, you saw how to use compile-time evaluation in a practical context.
In the next chapter, you will learn how to further expand your C++ toolbox so that you can create libraries by constructing hidden proxy objects.

## Chapter 9: Essential utilities

In this chapter, you have learned how to use metaprogramming to generate functions and values at compile time instead of runtime. You also discovered how to do this in a modern C++ way by using templates, the constexpr, static_assert(), and if constexpr, type traits, and concepts. Moreover, with constant string hashing, you saw how to use compile-time evaluation in a practical context.
In the next chapter, you will learn how to further expand your C++ toolbox so that you can create libraries by constructing hidden proxy objects.

## Chapter 10: Proxy objects and lazy evaluation

In this chapter, you learned the difference between lazy evaluation and eager evaluation. You also learned how to use hidden proxy objects to implement lazy evaluation behind the scenes, meaning that you now understand how to implement lazy evaluation optimizations while preserving the easy-to-use interface of your classes. Hiding complex optimizations inside library classes instead of having them exposed in the application code makes the application code more readable and less error-prone.
In the next chapter, we will shift focus and move on to concurrent and parallel programming using C++.

## Chapter 11: Concurrency

In this chapter, you have seen how to create programs that can execute multiple threads concurrently. We also covered how to avoid data races by protecting critical sections with locks or by using atomics. You learned that C++20 comes with some useful synchronization primitives: latches, barriers, and semaphores. We then looked into execution order and the C++ memory model, which becomes important to understand when writing lock-free programs. You also discovered that immutable data structures are thread-safe. The chapter ended with some guidelines for improving performance in concurrent applications.
The next two chapters are dedicated to a completely new C++20 feature called coroutines, which allows us to write asynchronous code in a sequential style.

## Chapter 12: Coroutines and lazy generators

In this chapter, you have seen how to use C++ coroutines for building generators using the keywords co_yield and co_return. To better understand how C++ stackless coroutines differ from stackful coroutines, we compared the two and also looked at the customization points that C++ coroutines offer. This gave you a deep understanding of how flexible C++ coroutines are, as well as how they can be used to achieve efficiency. Stackless coroutines are closely related to state machines. By rewriting a traditionally implemented state machine into code that uses coroutines, we explored this relationship and you saw how well compilers can transform and optimize our coroutines to machine language.
In the next chapter, we will continue to discuss coroutines by focusing on asynchronous programming and will deepen your understanding of the co_await keyword.

## Chapter 13: Asynchronous programming with coroutines

In this chapter, you've seen how to use C++ coroutines for writing asynchronous tasks. To be able to implement the infrastructure in the form of a Task type and a sync_wait() function, you needed to fully understand the concept of awaitable types and how they can be used to customize the behavior of coroutines in C++.
By using Boost.Asio, we could build a truly minimal but fully functional concurrent server application executing on a single thread while handling multiple client sessions.
Lastly, I briefly introduced a methodology called structured concurrency and gave some directions for where you can find more information about this topic.
In the next chapter, we will move on to explore parallel algorithms, which are a way to speed up concurrent programs by utilizing multiple cores.

## Chapter 14: Parallel algorithm

In this chapter, you have learned about the complexity of handcrafting an algorithm to execute in parallel. You also now know how to analyze, measure, and tune the efficiency of parallel algorithms. The insights you gained while learning about parallel algorithms will have deepened your understanding of the requirements and the behaviors of the parallel algorithms found in the C++ standard library. C++ comes with four standard execution policies, which can be extended by compiler vendors. This opens up the door for utilizing the GPU for standard algorithms.
The next C++ standard, C++23, will most likely add increased support for parallel programming on the GPU.
You have now reached the end of the book. Congratulations! Performance is an important aspect of code quality. But too often, performance comes at the expense of other quality aspects, such as readability, maintainability, and correctness. Mastering the art of writing efficient and clean code requires practical training. My hope is that you have learned things from this book that you can incorporate into your day-to- day life while creating stunning software.
Solving performance problems usually comes down to a willingness to investigate things further. More often than not, it requires understanding the hardware and underlying OS well enough to be able to draw conclusions from measurement data.

[From here - I = the author]
This book has scratched the surface in these areas when I've felt it necessary. After writing about C++20 features in this second edition, I'm now looking forward to starting to use these features in my profession as a software developer. As I've mentioned previously, a lot of the code presented in this book is only partially supported by the compilers today. I will keep updating the GitHub repository and adding information about compiler support. Best of luck!
