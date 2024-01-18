# Galois Table / Finite Field Generator

This CLI can be used to generate a [Galois table](http://www.ee.unb.ca/cgi-bin/tervo/galois3.pl) used for mathematical operations on primitive polynomials.

![build-windows](https://github.com/Danaozhong/cpp-finite-field-table-generator/actions/workflows/build-windows.yaml/badge.svg)

![build-linux](https://github.com/Danaozhong/cpp-finite-field-table-generator/actions/workflows/build-linux.yaml/badge.svg)

![build-macos](https://github.com/Danaozhong/cpp-finite-field-table-generator/actions/workflows/build-macos.yaml/badge.svg)

![tests](https://github.com/Danaozhong/cpp-finite-field-table-generator/actions/workflows/run-tests.yaml/badge.svg)

You need these tables to be able to calculate multiplications and additions of a primitive polynomial P(x).

To be honest, by today I don't even know what a galois table was exactly used for, but I remember that back then the output of this tool helped me pass the university exam in Coding Theory.
Basically, I printed all possible addition/multiplication tables for all possible primitive polynomials up to degree 5, so that in the exam is just had to search for the correct table to perform the multiplications/additions in no time.

I wrote this code in 2014 as an unexperienced university student, so the code quality is not impressive. Feel free to raise a PR, if you would like to fix something.

I hope it helps you too!