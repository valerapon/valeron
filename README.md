# valeron
My language: python + pascal + c++ = python4  
   
##### What it's include:  
1) Simple operations  
2) Variable  
3) Arrays  
4) Goto/Label constructions  
5) If/Else constructions  
6) circles While
7) Function
8) Correct checker  
9) Function   

##### How to compiler in console:    
&nbsp;&nbsp;*g++ -o main main.cpp Algorithm.cpp Lexem.cpp Number.cpp Operator.cpp Variable.cpp Label.cpp Array.cpp Function.cpp Error.cpp*  
or:  
&nbsp;&nbsp;*make*  

##### How to run:   
*./main*  

##### Syntax:
<strong>x = 1</strong> - create varable and put here 1  
<strong>y = z + x * 1</strong> - crete 2 variable: z with 0 value and y with 1 value  
<strong>x\[5\] = 6</strong> - create array \[0, 0, 0, 0, 0, 6\]  
<strong>Numerical operations:</strong>  
= + - * / % >> << ^ == != >= <= > < & |  
<strong>print x</strong> - print value  
<strong>newline</strong> - print \'\n\'  
<strong>A:</strong> - create label  
<strong>goto A</strong> - jump on label  
<strong>if/else construction:</strong>  
if x == 1 {  
&nbsp;print 1  
}  
else {  
&nbsp;print 0  
}  
<strong>while construction:</strong>  
while x < 5 {  
&nbsp;print x  
&nbsp;x = x + 1  
}  
<strong>function construction:</strong>  
def f(a)   
&nbsp;...  
endef  
  
def g()    
&nbsp;...  
return value  
endef  

## Example of program:

def F(x)  
&nbsp;&nbsp;if x <= 1 \{  
&nbsp;&nbsp;&nbsp;&nbsp;return x  
&nbsp;&nbsp;\}  
&nbsp;&nbsp;return F(x - 1) + F(x - 2)  
endef  

def g(i)  
&nbsp;&nbsp;return i * 2  
endef

def f(x, size)  
&nbsp;&nbsp;i = 0  
&nbsp;&nbsp;while i < size \{  
&nbsp;&nbsp;&nbsp;&nbsp;print x[i] + g(i)  
&nbsp;&nbsp;&nbsp;&nbsp;i = i + 1  
&nbsp;&nbsp;\}  
endef

i = 0  
while i < 5 \{  
&nbsp;&nbsp;a[i] = i  
&nbsp;&nbsp;i = i + 1  
\}  
f(a[4], 5)  
newline  
j = 1  
while j <= 10 \{  
&nbsp;&nbsp;if j % 2 == 0 \{  
&nbsp;&nbsp;&nbsp;&nbsp;print j * 2  
&nbsp;&nbsp;\}  
&nbsp;&nbsp;else \{  
&nbsp;&nbsp;&nbsp;&nbsp;print j * 3  
&nbsp;&nbsp;\}  
&nbsp;&nbsp;j = j + 1  
\}  
newline  
i = 0  
while i <= 5 \{  
&nbsp;&nbsp;print F(i)  
&nbsp;&nbsp;i = i + 1  
\}  
newline  
x = y = z = 100  
print x * y *   

## OUTPUT:  
#### result:  
0 3 6 9 12  
3 4 9 8 15 12 21 16 27 20  
0 1 1 2 3 5 
1000000  

#### postfix:  
F( x )  
x 1<=if\{  
x return   
\}  
x 1-F( )x 2-F( )+return  
endef  
g( i )  
i 2\*return   
endef  
f( x size )  
i 0=  
$while0:i size \<while \{  
xi \[i g( )+print   
i i 1+=  
\\}goto $while0  
endef  
i 0=  
\$while1:i 5<while \{  
ai \[i =  
i i 1+=  
\}goto \$while1  
a4\[5f( )  
newline  
j 1=  
\$while2:j 10<=while \{  
j 2%0==if\{   
j 2\*print   
\}  
else\{  
j 3\*print   
\}  
j j 1+=  
\}goto \$while2  
newline   
i 0=  
\$while3:i 5<=while \{  
i F( )print   
i i 1+=  
\}goto \$while3   
newline   
x y z 100===  
x y \*z \*print   

#### variable:  
i=6  
j=11  
x=100  
y=100  
z=100  

#### array:
a\[ 0 1 2 3 4 \]  

#### label:    
\$while0  
\$while1  
\$while2  
\$while3  

#### function:  
F( x )  
f( x size )  
g( i )  

