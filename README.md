# C++ Template Meta Tutorial
This repository contains a presentation that is an introduction to C++ Template Meta Programming. All of the code in the presentation is in this repository. Much of what is shown in this presentation is no longer required to know with the increased support for template meta programming in C++11, C++14, and C++17. So why learn it? This presentation includes derivations of each of the techniques which will help get you into the mindset of template meta programming. Furthermore, while the actual code may be legacy, all of these techniques are still fundamentals and frequently used for template meta programming.

## Links
A copy of the presentation is hosted [here](https://www.zwimer.com/Template-Meta-Tutorial/Presentation.pdf). The code repository is located on github [here](https://www.github.com/zwimer/Template-Meta-Tutorial/).

## Disclaimer
C++ Template Meta is a huge and very diverse topic. It would be naive to say that this tutorial encompasses even a small portion of this topic. It is just a small introduction to some of techniques used in TMP. Furthermore, this presentation was designed to be given by someone who knows TMP. As such, while the presentation contains all necessary information, explanations may be in bullet points as it was written so that the instructor could explain each point.

## Texts
This presentation _heavily_ utilizes the following text: [Modern C++ Design](https://www.mimuw.edu.pl/~mrp/cpp/SecretCPP/Addison-Wesley%20-%20Modern%20C++%20Design.%20Generic%20Programming%20and%20Design%20Patterns%20Applied.pdf) by Andrei Alexandrescu. If you are interested in TMP, I highly recommend this book.

## Requirements
The code in this repository is compiled with clang++ version 7.0.2, and gcc 4.9.2. C++99 is required for most of the code, however some of the files require C++14. The reason different compilers and versions of C++ are used is to demonstrate examples where clarity of error messages is helpful and to demonstrate how C++ TMP has evolved from the primitive form you will learn to a more advanced and useful form which includes variadic templates among other amazing features.
