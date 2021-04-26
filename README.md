# Corner Grocer Inventory App

## Summarize the project and what problem it was solving.
This is a mock grocery store inventory tracking app made for learning purposes. It provides a console-based menu to choose between printing a formatted list of items purchased that day, finding out how many items of a particular type were purchased, and printing a text-based histogram of purchases. It features C++/Python interop.

## What did you do particularly well?
My familiarity with the C++ standard library is improving. My progress in that area is on display in this project. The usage of std::unique_ptr, std::move, and std::exchange are all examples.

## Where could you enhance your code? How would these improvements make your code more efficient, secure, and so on?
The main issue is that I didn't explicitly catch as many exceptions as I could have. There are a few cases where I use general exception catching to catch everything instead of only handling the specific exceptions I want to handle. This is an issue because you don't necessarily want to handle every possible exception. Usually you only want to handle the exceptions you've specifically built your code to be capable of dealing with.

## Which pieces of the code did you find most challenging to write, and how did you overcome this? What tools or resources are you adding to your support network?
Believe it or not, it was actually the Python portion that I found most challenging. It's been quite a while since I've worked with Python. I had to look up references and tutorials to refresh myself on the syntax. These sources included the offical Python documentation as well as a few tutorials, such as the official Python tutorial and the ones found on tutorialspoint and w3schools. 

## What skills from this project will be particularly transferable to other projects or course work?
I got the chance to practice more with modern C++ concepts like move constructors and self-managing pointers. I also got to explore some of the standard library headers in greater depth, including <algorithm> and <regex>.

## How did you make this program maintainable, readable, and adaptable?
It could be more maintainable if I'm being honest. If I could do it again I'd encapsulate the functions used to interface between C++ and Python into one or more classes of their own. I did encapsulate the Menu into its own class. Any changes there should have no impact on the rest of the program.
I made it readable by sticking to commmon naming conventions, commenting extensively, and choosing descriptive, self-documenting names for everything.
It is pretty adaptable. Any one of those functions could be called in another scope and would still serve their purpose without issue. There is a hard-coded dependency on "Menu.h" though, which is perhaps not ideal.
The next thing I'm planning to learn more about is design patterns, which should help with all of the above if I'm understanding correctly.
