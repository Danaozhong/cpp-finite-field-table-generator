# Galois Table / Finite Field Generator

This CLI can be used to generate a [Galois table](http://www.ee.unb.ca/cgi-bin/tervo/galois3.pl) used for mathematical operations on primitive polynomials.

![build-windows](https://github.com/Danaozhong/cpp-finite-field-table-generator/actions/workflows/build-windows.yaml/badge.svg)

![build-linux](https://github.com/Danaozhong/cpp-finite-field-table-generator/actions/workflows/build-linux.yaml/badge.svg)

![build-macos](https://github.com/Danaozhong/cpp-finite-field-table-generator/actions/workflows/build-macos.yaml/badge.svg)

![tests](https://github.com/Danaozhong/cpp-finite-field-table-generator/actions/workflows/run-tests.yaml/badge.svg)

You need these tables to be able to calculate multiplications and additions of a primitive polynomial P(x).

## Example

Using this CLI to evaluate the primitive polynomial `p(x) = x^4 + x + 1` results in the addition and multiplication tables. For simplicity, only the multiplication table is shown below.
```

MULTIPLICATION TABLE
g(x)=x^4 + x^1 + x^0

*       a^-999  a^0     a^1     a^4     a^2     a^8     a^5     a^10    a^3     a^14    a^9     a^7     a^6     a^13    a^11    a^12
a^-999  0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
a^0     0       1       2       3       4       5       6       7       8       9       10      11      12      13      14      15
a^1     0       2       4       6       8       10      12      14      3       1       7       5       11      9       15      13
a^4     0       3       6       5       12      15      10      9       11      8       13      14      7       4       1       2
a^2     0       4       8       12      3       7       11      15      6       2       14      10      5       1       13      9
a^8     0       5       10      15      7       2       13      8       14      11      4       1       9       12      3       6
a^5     0       6       12      10      11      13      7       1       5       3       9       15      14      8       2       4
a^10    0       7       14      9       15      8       1       6       13      10      3       4       2       5       12      11
a^3     0       8       3       11      6       14      5       13      12      4       15      7       10      2       9       1
a^14    0       9       1       8       2       11      3       10      4       13      5       12      6       15      7       14
a^9     0       10      7       13      14      4       9       3       15      5       8       2       1       11      6       12
a^7     0       11      5       14      10      1       15      4       7       12      2       9       13      6       8       3
a^6     0       12      11      7       5       9       14      2       10      6       1       13      15      3       4       8
a^13    0       13      9       4       1       12      8       5       2       15      11      6       3       14      10      7
a^11    0       14      15      1       13      3       2       12      9       7       6       8       4       10      11      5
a^12    0       15      13      2       9       6       4       11      1       14      12      3       8       7       5       10
```

## Disclaimer

To be honest, by today I don't even know what a galois table was exactly used for, but I remember that back then the output of this tool helped me pass the university exam in Coding Theory.
Basically, I printed all possible addition/multiplication tables for all possible primitive polynomials up to degree 5, so that in the exam is just had to search for the correct table to perform the multiplications/additions in no time.


I wrote this code in 2014 as an unexperienced university student, so the code quality is not impressive. Feel free to raise a PR, if you would like to fix something.

I hope it helps you too!