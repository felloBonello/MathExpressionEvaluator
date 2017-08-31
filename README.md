# MathExpressionEvaluator
An expression evaluator with a console interface. Any mathematical expression can be entered including boolean, integer, and real number expressions. The expression will be tokenized then it will be sent through the infix to postifx algorithm (shunting yard algorithm) and then it will be sent through an algorithm that will evaluate reverse polish notation (RPN) expressions. This will result in the answer to the original expression. This program can handle very large numbers and provides many useful math functions such as logarithm and factorial. Boost unit tests are included in the project. Polymorphism is used in this project in order to deal with different types of tokens correctly. 


http://en.wikipedia.org/wiki/Reverse_Polish_notation  
http://en.wikipedia.org/wiki/Shunting-yard_algorithm  
