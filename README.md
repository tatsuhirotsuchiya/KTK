# KTK: A Tool for Constructing Pairwise Covering Test Suites (Covering Arrays)

## Overview

KTK is a tool for covering arrays which can be used as test suites for all-pairs testing.

## Description

This tool implements the algorithm proposed by: 
  
* Noritaka Kobayashi, Tatsuhiro Tsuchiya, and Tohru Kikuno,
A New Method for Constructing Pair-Wise Covering Designs for Software Testing,
Information Processing Letters, Vol.81, No.2, pp.85-91, January 2002.

The algorithm constructs test suites for pair-wise testing, that is, covering arrays of strength 2, based on an algebraic approach. 

## Usage

For example, command `program 4x2 3x3 2x1` outputs a pairwise testing suite for
the case of 2 4-valued, 3 3-valued, and 1 2-valued parameters.

'-1' in the output represents the 'don't care' value.

Here is the output for the above example.

    no of parameters 6
    ranges
     4  4  3  3  3  2
    values
     0  0  0  0  0  0
     1  1  1  1  1  1
     2  2  2  2  2 -1
     3  3  0  1  2 -1
     0  1  1  2  0 -1
     1  0  2  0  1 -1
     2  3  0  2  1 -1
     3  2  1  0  2 -1
     0  2  2  1  0 -1
     1  3 -1 -1 -1 -1
     2  0 -1 -1 -1 -1
     3  1 -1 -1 -1 -1
     0  3 -1 -1 -1 -1
     1  2 -1 -1 -1 -1
     2  1 -1 -1 -1 -1
     3  0 -1 -1 -1 -1
     1  1  1  1  1  1
     2  2  2  2  2 -1
     0  0  1  1  1 -1
     1  1  2  2  2  0
     2  2  0  0  0  1
     0  0  2  2  2  1
     1  1  0  0  0 -1
     2  2  1  1  1  0
     3  3  0  0  0  0
     3  3  1  1  1  1
     3  3  2  2  2 -1
    size 27

## Licence

This tool is free software under the zlib license. 

## Author

[Tatsuhiro Tsuchiya][http://www-ise4.ist.osaka-u.ac.jp/~t-tutiya/en/]
